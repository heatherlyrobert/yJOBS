/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                        directory list                        ----===*/
/*====================------------------------------------====================*/
static void      o___LIST____________________o (void) {;};

char
yjobs_dir_list          (char a_type, char a_path [LEN_PATH], char r_list [LEN_MASS])
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
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "f_nodel"  );
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else                                         rc = yENV_audit_centraldir (a_fix, x_dir, "d_tight"  );
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
   --rce; if (strncmp (a_label, "conf", 4) == 0)  { x_use = 'c'; yENV_score_mark ("FDSEC"    , '°'); if (x_fix == 'F')  yENV_score_mark ("FDFIX"    , '°'); }
   else   if (strncmp (a_label, "cent", 4) == 0)  { x_use = 'd'; yENV_score_mark ("CSECURE"  , '°'); if (x_fix == 'F')  yENV_score_mark ("CFIX"     , '°'); }
   else {
      DEBUG_YJOBS   yLOG_note    ("can not interpret a_label");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_char    ("x_use"     , x_use);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL) {
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
      if      (x_use == 'c') {  yENV_score_mark ("FDSEC"    , '-'); if (x_fix == 'F')  yENV_score_mark ("FDFIX"    , '-');  }
      else if (x_use == 'd') {  yENV_score_mark ("CSECURE"  , '-'); if (x_fix == 'F')  yENV_score_mark ("CFIX"     , '-');  }
      yURG_msg ('>', "auditing %s directory...", a_label);
      snprintf (t, LEN_HUND, "skipping, not configured for %s directory", a_label);
      yURG_msg ('-', t);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(score)---------------------------------*/
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
      yENV_score_mark ("FDSEC"    , 's');
      if (x_fix != '-') {
         if (rc == RC_REPAIR)  yENV_score_mark ("FDFIX"    , 'f');
         else                  yENV_score_mark ("FDFIX"    , '-');  /* nothing to do */
      }
   } else if (x_use == 'd') {
      yENV_score_mark ("CSECURE"  , 's');
      if (x_fix != '-') {
         if (rc == RC_REPAIR)  yENV_score_mark ("CFIX"     , 'f');
         else                  yENV_score_mark ("CFIX"     , '-');  /* nothing to do */
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
      return 0;
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
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__dir_multi        (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char       *p           = NULL;
   char       *q           = ",";  
   char       *r           = NULL;
   int         rc_final    =    0;
   char        x_prefix    [LEN_USER]  = "";
   int         x_all       =    0;
   int         x_total     =    0;
   int         x_count     =    0;
   int         x_pass      =    0;
   int         x_warns     =    0;
   int         x_error     =    0;
   char        x_list      [LEN_MASS]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_config"  , a_config);
   --rce;  if (a_config == NULL || a_config [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_config"  , a_config);
   DEBUG_YJOBS   yLOG_point   ("a_cname"   , a_cname);
   --rce;  if (a_cname  == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cname"   , a_cname);
   DEBUG_YJOBS   yLOG_point   ("a_user"    , a_user);
   --rce;  if (a_user   == NULL || a_user [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_user"    , a_user);
   /*---(quick-out)----------------------*/
   --rce;  if (a_cname [0] != '\0') {
      DEBUG_YJOBS   yLOG_note    ("configuation file specified, use single");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather)-------------------------*/
   rc = yjobs_dir_list (YENV_REG, a_config, x_list);
   DEBUG_YJOBS   yLOG_point   ("list"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   sprintf (x_prefix, "%s.", a_user);
   DEBUG_YJOBS   yLOG_info    ("x_prefix"  , x_prefix);
   if (strcmp ("root", a_user) == 0) {
      yURG_msg ('-', "file filtering will see everything (root)");
   } else {
      yURG_msg ('-', "file filtering prefix is å%sæ", x_prefix);
   }
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   p = strtok_r (x_list, q, &r);
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   while (p != NULL) {
      /*---(header)-----------------------------*/
      DEBUG_YJOBS   yLOG_info    ("file"      , p);
      /*---(ignore-standards)-------------------*/
      if (p [0] == '.') {
         switch (p [1]) {
         case '.'  : case '\0' :
            p = strtok_r (NULL, q, &r);
            DEBUG_YJOBS   yLOG_point   ("p"         , p);
            continue;
            break;
         }
      }
      ++x_all;
      /*---(simple filtering)-------------------*/
      rc = yjobs__dir_filter (p, x_prefix, a_uid);
      DEBUG_YJOBS   yLOG_value   ("filter"    , rc);
      if (rc != 0)  ++x_total;
      if (rc <= 0) {
         DEBUG_YJOBS   yLOG_note    ("not a valid job/khronos file");
         p = strtok_r (NULL, q, &r);
         DEBUG_YJOBS   yLOG_point   ("p"         , p);
         continue;
      }
      rc = yjobs__share_single   (a_runas, a_mode, a_config, p, a_user, a_uid, f_callback);
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
      ++x_count;
      DEBUG_YJOBS   yLOG_complex ("counts"    , "%d all  , %d total, %d count, %d pass , %d warns, %d error", x_all, x_total, x_count, x_pass, x_warns, x_error);
      /*---(next)------------------------*/
      p = strtok_r (NULL, q, &r);
      DEBUG_YJOBS   yLOG_point   ("p"         , p);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   yURG_msg ('>', "summary of central file review...");
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
yjobs_dir_review        (char a_runas, char a_mode, void *f_callback, char c_flag, char c_fail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   char        x_user      [LEN_USER]  = "";
   int         x_uid       =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_conf      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "configuration central file review...");
   /*---(running as)---------------------*/
   rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, NULL, x_user, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "currently running as å%sæ (%d)", x_user, x_uid);
   /*---(directory)-----------------------------*/
   rc = yjobs_who_location (a_runas, x_cdir, x_conf, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      yURG_err ('f', "could not identify configuration directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration directory is å%sæ", x_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   yURG_msg ('-', "configuration file name is å%sæ", x_conf);
   DEBUG_YJOBS   yLOG_info    ("x_conf"    , x_conf);
   /*---(handle zero)---------------------------*/
   if (strcmp (x_cdir, "") == 0) {
      yURG_msg ('-', "skipping, zero configuration for application");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle file)---------------------------*/
   --rce;  if (strcmp (x_conf, "") != 0) {
      yURG_msg ('-', "single-file configuration set-up");
      rc = yjobs__share_single   (a_runas, a_mode, x_cdir, x_conf, x_user, x_uid, f_callback);
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
      yURG_msg ('-', "multiple-file configuration set-up");
      rc = yjobs__dir_multi (a_runas, a_mode, x_cdir, x_conf, x_user, x_uid, f_callback);
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




