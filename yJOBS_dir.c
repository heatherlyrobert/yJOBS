/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                        directory list                        ----===*/
/*====================------------------------------------====================*/
static void      o___LIST____________________o (void) {;};

char
yjobs_dir__sorted       (char a_type, char a_path [LEN_PATH], char r_list [LEN_MASS])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_full      [LEN_PATH]  = "";
   char        x_type      =  '-';
   int         l           =    0;
   int         t           =    0;
   int         c           =    0;
   char        x_skip      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_list != NULL)  strcpy (r_list, "(n/a)");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL || a_path [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_path"    , a_path);
   DEBUG_YJOBS   yLOG_point   ("r_list"    , r_list);
   --rce;  if (r_list  == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("r_list"    , r_list);
   /*---(prepare)------------------------*/
   ystrlcpy (r_list, ","           , LEN_MASS);
   /*---(open dir)-----------------------*/
   x_dir = opendir (a_path);
   DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      yURG_err ('f', "could not open directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "successfully openned directory");
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   x_file = readdir (x_dir);
   strcpy (r_list, "");
   DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      /*---(filter)----------------------*/
      l = strlen (x_file->d_name);
      if (l == 1 && strcmp (x_file->d_name, "." ) == 0)  x_skip = 'y';
      if (l == 2 && strcmp (x_file->d_name, "..") == 0)  x_skip = 'y';
      /*---(types)-----------------------*/
      rc = yENV_name_full (a_path, x_file->d_name, NULL, x_full);
      if (rc < 0)  x_skip = 'y';
      else {
         x_type = yENV_exists (x_full);
         if (x_type < 0)  x_skip = 'y';
         else {
            if (a_type != YENV_ANY) switch (a_type) {
            case YENV_HARD : case YENV_REG  :
               if (x_type != YENV_HARD && x_type != YENV_REG) x_skip = 'y';
               break;
            default  :
               if (x_type != a_type)  x_skip = 'y';
               break;
            }
         }
      }
      /*---(concatenate)-----------------*/
      DEBUG_YJOBS   yLOG_complex ("d_name"    , "%c  %3då%sæ", x_skip, l, x_file->d_name);
      ++t;
      if (x_skip == '-') {
         ystrlcat (r_list, x_file->d_name, LEN_MASS);
         ystrlcat (r_list, ","           , LEN_MASS);
         ++c;
      }
      /*---(next)------------------------*/
      x_skip = '-';
      x_file = readdir (x_dir);
      DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(sort)---------------------------*/
   rc = ySORT_string (r_list);
   DEBUG_YJOBS   yLOG_point   ("sort"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix)----------------------------*/
   DEBUG_YJOBS   yLOG_value   ("read"      , t);
   DEBUG_YJOBS   yLOG_value   ("kept"      , c);
   if (c > 99)  c = 99;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                       directory audit                        ----===*/
/*====================------------------------------------====================*/
static void      o___AUDIT___________________o (void) {;};

char
yjobs_dir__secure       (char a_label [LEN_LABEL], char a_dir [LEN_DESC], char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_dir       [LEN_DESC]  = "";
   char        x_next      [LEN_DESC]  = "";
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   ystrlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (l > 0 && x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YJOBS   yLOG_complex ("x_dir"     , "%2då%sæ", l, x_dir);
   c = ystrldcnt (x_dir, '/', LEN_DESC);
   /*---(stop recursion)-----------------*/
   --rce;  if (l == 0) {
      DEBUG_YJOBS   yLOG_note    ("bottomed out at root '/'");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   ystrlcpy (x_next, x_dir, LEN_DESC);
   p = strrchr (x_next, '/');
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   if  (p != NULL)   p [0] = '\0';
   l = strlen (x_next);
   DEBUG_YJOBS   yLOG_complex ("x_next"    , "%2då%sæ", l, x_next);
   /*---(recurse)------------------------*/
   rc = yjobs_dir__secure (a_label, x_next, a_fix);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(tail execute)-------------------*/
   yURG_msg ('>', "auditing %s directory level (%d)...", a_label, c);
   l = strlen (x_dir);
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   rc = 0;
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "f_nodel"  );
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yAUDIT_centraldir (a_fix, x_dir, "d_normal" );
   else                                         rc = yAUDIT_centraldir (a_fix, x_dir, "d_tight"  );
   /*---(handle trouble)-----------------*/
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(finish)----------------------*/
   yURG_msg ('-', "success, %s directory acceptable", a_label);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_dir_secure        (char a_runas, char a_mode, char a_label [LEN_LABEL], char a_dir [LEN_DESC], char *r_use, char *r_good)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_fix       =  '-';
   char        x_which     =  '-';
   char        t           [LEN_HUND]  = "";
   char        x_use       =  '-';
   /*---(defaults)-----------------------*/
   if (r_use  != NULL)  *r_use  = '-';
   if (r_good != NULL)  *r_good = '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   (a_label);
      DEBUG_YJOBS   yLOG_snote   ("audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)    x_fix = 'F';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_label"   , a_label);
   /*---(score)--------------------------*/
   --rce; if (strncmp (a_label, "conf", 4) == 0)  { x_use = 'c'; }
   else   if (strncmp (a_label, "cent", 4) == 0)  { x_use = 'd'; }
   else {
      DEBUG_YJOBS   yLOG_note    ("can not interpret a_label");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_char    ("x_use"     , x_use);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL) {
      if      (x_use == 'c') {  ySCORE_mark ("FDSEC"    , '°'); }
      else if (x_use == 'd') {  ySCORE_mark ("CSECURE"  , '°'); }
      yURG_msg ('>', "auditing %s directory...", a_label);
      yURG_err ('f', "%s directory is NULL", a_label);
      snprintf (t, LEN_HUND, "%s directory is not secure/proper", a_label);
      yjobs_ends_failure (a_mode, "", t);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(no directory given)-------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   if (strcmp (a_dir, "")  == 0) {
      yURG_msg ('>', "auditing %s directory...", a_label);
      snprintf (t, LEN_HUND, "skipping, not configured for %s directory", a_label);
      yURG_msg ('-', t);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(score)---------------------------------*/
   --rce; if (x_use == 'c')  { ySCORE_mark ("FDSEC"    , '°'); if (x_fix == 'F')  ySCORE_mark ("FDFIX"    , '°'); }
   else   if (x_use == 'd')  { ySCORE_mark ("CSECURE"  , '°'); if (x_fix == 'F')  ySCORE_mark ("CFIX"     , '°'); }
   if (r_use  != NULL)  *r_use  = 'y';
   /*---(call audit)----------------------------*/
   rc = yjobs_dir__secure (a_label, a_dir, x_fix);
   DEBUG_YJOBS   yLOG_value   ("dir"       , rc);
   --rce;  if (rc < 0) {
      snprintf (t, LEN_HUND, "%s directory is not secure/proper", a_label);
      yjobs_ends_failure (a_mode, "", t);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)---------------------------------*/
   if        (x_use == 'c') {
      ySCORE_mark ("FDSEC"    , 's');
      if (x_fix != '-') {
         if (rc == RC_REPAIR)  ySCORE_mark ("FDFIX"    , 'f');
         else                  ySCORE_mark ("FDFIX"    , '-');  /* nothing to do */
      }
   } else if (x_use == 'd') {
      ySCORE_mark ("CSECURE"  , 's');
      if (x_fix != '-') {
         if (rc == RC_REPAIR)  ySCORE_mark ("CFIX"     , 'f');
         else                  ySCORE_mark ("CFIX"     , '-');  /* nothing to do */
      }
   }
   if (r_good != NULL)  *r_good = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       directory review                       ----===*/
/*====================------------------------------------====================*/
static void      o___REVIEW__________________o (void) {;};

char
yjobs__dir_filter       (char a_name [LEN_HUND], char a_prefix [LEN_TERSE], int a_muid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_name"    , a_name);
   /*---(just up/cur dirs)---------------*/
   if      (strcmp (a_name, "." ) == 0 || strcmp (a_name, "..") == 0) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(name quality)-------------------*/
   l = strlen (a_name);
   DEBUG_YJOBS   yLOG_value   ("l"         , l);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_name [i]) == NULL) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(hidden file)--------------------*/
   DEBUG_YJOBS   yLOG_char    ("first char", a_name [0]);
   --rce;  if (a_name [0] == '.') {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(user prefix)--------------------*/
   if (a_muid != 0) {
      if (strncmp (a_name, a_prefix, strlen (a_prefix)) != 0) {
         DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs__dir_multi        (char a_runas, char a_mode, char a_reason, char a_cdir [LEN_DESC], char a_prefix [LEN_TERSE],  char a_suffix [LEN_TERSE], int a_ruid, char a_ruser [LEN_USER], void *f_callback, char c_fail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char       *p           = NULL;
   char       *q           = ",";  
   char       *r           = NULL;
   int         rc_final    =    0;
   char        x_filter    [LEN_USER]  = "";
   int         x_all       =    0;
   int         x_total     =    0;
   int         x_count     =    0;
   int         x_pass      =    0;
   int         x_warns     =    0;
   int         x_error     =    0;
   char        x_list      [LEN_MASS]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(gather)-------------------------*/
   rc = yjobs_dir__sorted (YENV_REG, a_cdir, x_list);
   DEBUG_YJOBS   yLOG_point   ("list"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   sprintf (x_filter, "%s.", a_ruser);
   DEBUG_YJOBS   yLOG_info    ("x_filter"  , x_filter);
   if (strcmp ("root", a_ruser) == 0) {
      yURG_msg ('-', "file filtering will see everything (root)");
   } else {
      yURG_msg ('-', "file filtering prefix is å%sæ", x_filter);
   }
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   p = strtok_r (x_list, q, &r);
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   while (p != NULL) {
      /*---(header)-----------------------------*/
      DEBUG_YJOBS   yLOG_info    ("file"      , p);
      ++x_all;
      /*---(simple filtering)-------------------*/
      rc = yjobs__dir_filter (p, x_filter, a_ruid);
      DEBUG_YJOBS   yLOG_value   ("filter"    , rc);
      if (rc != 0)  ++x_total;
      if (rc <= 0) {
         DEBUG_YJOBS   yLOG_note    ("not a valid job/khronos file");
         p = strtok_r (NULL, q, &r);
         DEBUG_YJOBS   yLOG_point   ("p"         , p);
         continue;
      }
      /*---(handle)-----------------------------*/
      rc = yjobs_file_review (a_runas, a_mode, a_reason, ++x_count, a_cdir, p, a_prefix, a_suffix, f_callback, c_fail);
      DEBUG_YJOBS   yLOG_value   ("single"    , rc);
      if (rc < 0) rc = RC_FATAL;
      switch (rc) {
      case RC_ACK      :
      case RC_POSITIVE :
      case RC_OVERRIDE :
      case RC_REPAIR   : ++x_pass;   break;
      case RC_WARNING  : ++x_warns;  break;
      case RC_FATAL    : ++x_error;  break;
      }
      DEBUG_YJOBS   yLOG_complex ("counts"    , "%d all  , %d total, %d count, %d pass , %d warns, %d error", x_all, x_total, x_count, x_pass, x_warns, x_error);
      /*---(next)------------------------*/
      p = strtok_r (NULL, q, &r);
      DEBUG_YJOBS   yLOG_point   ("p"         , p);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   switch (a_reason) {
   case  's' :  yURG_msg ('>', "summary of central files security review...");   break;
   case  'p' :  yURG_msg ('>', "summary of central files pulling data...");      break;
   case  'a' :  yURG_msg ('>', "summary of central files content audit...");     break;
   }
   DEBUG_YJOBS   yLOG_complex ("FINAL"     , "%d all  , %d total, %d count, %d pass , %d warns, %d error", x_all, x_total, x_count, x_pass, x_warns, x_error);
   if      (x_all   == 0)  { yURG_msg ('-', "empty, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);           ; rc_final = RC_POSITIVE; }
   else if (x_count == 0)  { yURG_msg ('-', "nothing to see, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);  ; rc_final = RC_POSITIVE; }
   else if (x_error >  0)  { yURG_msg ('-', "ERRORS, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);          ; rc_final = RC_FATAL;    }
   else if (x_warns >  0)  { yURG_msg ('-', "warning, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);         ; rc_final = RC_WARNING;  }
   else                    { yURG_msg ('-', "success, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);         ; rc_final = RC_POSITIVE; }
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(return nunbers)-----------------*/
   DEBUG_YJOBS   yLOG_value   ("x_count"   , x_count);
   if (rc >= 0) {
      if (x_count > 100) x_count = 100;
      rc = x_count;
   }
   DEBUG_YJOBS   yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char         /*--> review central files --------------------------------------*/
yjobs_dir_full          (char a_runas, char a_mode, char a_reason, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE], int a_ruid, char a_ruser [LEN_USER], void *f_callback, char c_fail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   char        x_msg       [LEN_HUND]  = "";
   char       *x_fatal     = "file review handled bad file/data";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_reason"  , a_reason);
   --rce;  switch (a_reason) {
   case '=' :  break;
   case 's' :  yURG_msg ('>', "central configuration files security review...");   break;
   case 'p' :  yURG_msg ('>', "central configuration files pulling all data...");  break;
   case 'a' :  yURG_msg ('>', "central configuration files content audit...");     break;
   default  :
               sprintf (x_msg, "reason code (%d/%c) is illegal å=spaæ", a_reason, a_reason);
               yjobs_ends_failure (a_mode, x_msg, x_fatal);
               DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
   }
   /*---(handle zero)---------------------------*/
   if (strcmp (a_cdir, "") == 0) {
      yURG_msg ('-', "skipping, zero configuration (etc or spool) for application");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(running as)---------------------*/
   yURG_msg ('-', "currently running as å%sæ (%d)", a_ruser, a_ruid);
   yURG_msg ('-', "configuration directory is å%sæ", a_cdir);
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   DEBUG_YJOBS   yLOG_info    ("a_conf"    , a_conf);
   /*---(handle file)---------------------------*/
   --rce;  if (a_conf != NULL && strcmp (a_conf, "") != 0) {
      yURG_msg ('-', "single-file (etc) configuration set-up");
      yURG_msg ('-', "configuration file name is å%sæ", a_conf);
      rc = yjobs_file_review (a_runas, a_mode, a_reason, 1, a_cdir, a_conf, a_prefix, a_suffix, f_callback, c_fail);
      DEBUG_YJOBS   yLOG_value   ("single"    , rc);
      if (rc < 0)  {
         if (c_fail == 'y') {
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else if (rc >= 3) {
         yURG_msg ('-', "warning, trouble with audit, see details above");
      }
   }
   /*---(multiple files)------------------------*/
   else {
      yURG_msg ('-', "multiple-file (spool) configuration set-up");
      rc = yjobs__dir_multi (a_runas, a_mode, a_reason, a_cdir, a_prefix, a_suffix, a_ruid, a_ruser, f_callback, c_fail);
      DEBUG_YJOBS   yLOG_value   ("multiple"  , rc);
      if (rc < 0)  {
         if (c_fail == 'y') {
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else if (rc >= 3) {
         yURG_msg ('-', "warning, trouble with audit, see details above");
      }
   }
   /*---(wrap up)------------------------*/
   rc_final = rc;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char yjobs_dir_all_list   (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], int a_ruid, char a_ruser [LEN_USER])     { return yjobs_dir_full (a_runas, a_mode, '=', a_cdir, a_conf, "", "", a_ruid, a_ruser, NULL, '-'); }

char
yjobs_dir_all_pull  (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], int a_ruid, char a_ruser [LEN_USER], void *f_callback) 
{ 
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_pul, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_pul);
      DEBUG_YJOBS   yLOG_snote   ("pulling data not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(call)---------------------------*/
   return yjobs_dir_full (a_runas, a_mode, 'p', a_cdir, a_conf, "", "", a_ruid, a_ruser, f_callback, 'y');
}

char
yjobs_dir_all_secure (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE], int a_ruid, char a_ruser [LEN_USER]) 
{
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_sec, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_sec);
      DEBUG_YJOBS   yLOG_snote   ("securing environment not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(call)---------------------------*/
   return yjobs_dir_full (a_runas, a_mode, 's', a_cdir, a_conf, a_prefix, a_suffix, a_ruid, a_ruser, NULL, '-');
}

char
yjobs_dir_all_audit     (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], int a_ruid, char a_ruser [LEN_USER], void *f_callback)
{
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("auditing configuration content not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(call)---------------------------*/
   return yjobs_dir_full (a_runas, a_mode, 'a', a_cdir, a_conf, "", "", a_ruid, a_ruser, f_callback, '-');
}

char
yjobs_dir_one_check     (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_file [LEN_PATH], char a_cpre [LEN_TERSE], char a_suf [LEN_TERSE], int a_ruid, char a_ruser [LEN_USER], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode != ACT_CHECK) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_schar   (a_mode);
      DEBUG_YJOBS   yLOG_schar   (ACT_CHECK);
      DEBUG_YJOBS   yLOG_snote   ("checking one file not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(check security)-----------------*/
   rc = yjobs_dir_all_secure (a_runas, a_mode, a_cdir, a_file, a_cpre, a_suf, a_ruid, a_ruser);
   DEBUG_YJOBS   yLOG_value   ("check_sec" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check security)-----------------*/
   rc = yjobs_dir_all_audit  (a_runas, a_mode, a_cdir, a_file, a_ruid, a_ruser, f_callback);
   DEBUG_YJOBS   yLOG_value   ("check_aud" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



