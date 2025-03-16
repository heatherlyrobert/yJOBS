/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char
yjobs_share_prepare     (char a_func [LEN_TITLE], char a_area, char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_cwd [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_error     [LEN_HUND]  = "";
   /*---(default)------------------------*/
   strcpy (g_acts_score, g_acts_empty);
   if (r_cdir  != NULL)  strcpy (r_cdir , "");
   if (r_hdir  != NULL)  strcpy (r_hdir , "");
   if (r_world != NULL)  strcpy (r_world, "");
   if (r_db    != NULL)  strcpy (r_db   , "");
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (a_func);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS   yLOG_info    ("g_valid"   , g_valid);
   if (a_runas == 0 || strchr (g_valid, a_runas)  == NULL) {
      sprintf (x_error, "runas (%c) not recognized or valid", ychrvisible (a_runas));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_info    ("g_allmode" , g_allmode);
   if (a_mode  == 0 || strchr (g_allmode, a_mode) == NULL) {
      sprintf (x_error, "mode (%c) not recognized or valid", ychrvisible (a_mode));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yjobs_ends_failure (a_mode, "descriptive \"oneline\" string is NULL or empty");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      yjobs_ends_failure (a_mode, "local file/directory is NULL");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(help find bad calls)------------*/
   rc = 0;
   DEBUG_YJOBS  yLOG_char    ("a_area"    , a_area);
   --rce;  switch (a_area) {
   case 'h'  : if (strchr (G_HLP, a_mode) == NULL)  rc = -1;      break;
   case 'i'  : if (strchr (G_INC, a_mode) == NULL)  rc = -1;      break;
   case 'm'  : if (strchr (G_CEN, a_mode) == NULL)  rc = -1;      break;
   case 'o'  : if (strchr (G_OUT, a_mode) == NULL)  rc = -1;      break;
   case 'e'  : if (strchr (G_EPI, a_mode) == NULL)  rc = -1;      break;
   case 'g'  : if (strchr (G_GAT, a_mode) == NULL)  rc = -1;      break;
   default   :
                  yjobs_ends_failure (a_mode, "area provided does not match any area [himoeg]");
                  DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
                  return rce;
   }
   DEBUG_YJOBS  yLOG_value   ("match"     , rc);
   --rce;  if (rc < 0) {
      sprintf (x_error, "requested mode (%c) does not match area (%c)", ychrvisible (a_mode), ychrvisible (a_area));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(show header)--------------------*/
   rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, r_cdir, r_hdir, r_world, r_db, r_cwd, r_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return 1;
}

char
yjobs_share_readdb      (char a_func [LEN_TITLE], char a_area, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_rdb, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (a_func);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_rdb);
      DEBUG_YJOBS   yLOG_snote   ("database read not requested");
      DEBUG_YJOBS   yLOG_sexit   (a_func);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (a_func);
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DAUDIT ] = G_SCORE_FAIL;
   g_acts_score  [G_SCORE_DREAD  ] = G_SCORE_FAIL;
   /*---(no-database)--------------------*/
   if (a_db == NULL || strcmp (a_db, "") == 0) {
      DEBUG_YJOBS   yLOG_note    ("host program does not use central database");
      yURG_msg ('>', "verify audit and reading of the database...");
      yURG_msg ('-', "skipping, host program does not use a central database");
      g_acts_score  [G_SCORE_DAUDIT ] = G_SCORE_SKIP;
      g_acts_score  [G_SCORE_DREAD  ] = G_SCORE_SKIP;
      DEBUG_YJOBS   yLOG_exit    (a_func);
      return RC_ACK;
   }
   /*---(audit database)-----------------*/
   yURG_msg ('>', "audit existance and security of database...");
   /*---(audit databasee)----------------*/
   rc = yENV_audit_reg ('-', 'n', a_hdir, a_db, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "database is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DAUDIT ] = 's';
   yURG_msg ('-', "success, database exists and security is appropriate");
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_note    ("mode requires database loaded before");
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   x_callback = f_callback;
   rc = x_callback (YJOBS_READ, "");
   DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "central database did not load properly");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   rc_final = rc;
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DREAD  ] = 'Ô';
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return RC_POSITIVE;
}

char
yjobs_share_writedb     (char a_func [LEN_TITLE], char a_area, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_wdb, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (a_func);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_wdb);
      DEBUG_YJOBS   yLOG_snote   ("database write not required");
      DEBUG_YJOBS   yLOG_sexit   (a_func);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (a_func);
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DAUDIT ] = G_SCORE_FAIL;
   g_acts_score  [G_SCORE_DWRITE ] = G_SCORE_FAIL;
   /*---(no-database)--------------------*/
   if (a_db == NULL || strcmp (a_db, "") == 0) {
      DEBUG_YJOBS   yLOG_note    ("host program does not use central database");
      yURG_msg ('>', "verify audit and writing of the database...");
      yURG_msg ('-', "skipping, host program does not use a central database");
      g_acts_score  [G_SCORE_DAUDIT ] = G_SCORE_SKIP;
      g_acts_score  [G_SCORE_DWRITE ] = G_SCORE_SKIP;
      DEBUG_YJOBS   yLOG_exit    (a_func);
      return RC_ACK;
   }
   /*---(audit database)-----------------*/
   yURG_msg ('>', "audit existance and security of database...");
   /*---(audit database)-----------------*/
   rc = yENV_audit_reg ('-', 'n', a_hdir, a_db, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "database is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DAUDIT ] = 's';
   yURG_msg ('-', "success, database exists and security is appropriate");
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_note    ("mode requires database written after");
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   x_callback = f_callback;
   rc = x_callback (YJOBS_WRITE, "");
   DEBUG_YJOBS   yLOG_value   ("write db"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "central database did not save properly");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   rc_final = rc;
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_DWRITE ] = 'Õ';
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return rc_final;
}

char
yjobs__share_filter     (char a_name [LEN_HUND], char a_prefix [LEN_TERSE], int a_muid)
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
yjobs__share_single     (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    0;
   char        x_full      [LEN_PATH]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
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
   --rce;  if (a_cname  == NULL || a_cname [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cname"   , a_cname);
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(prepare)------------------------*/
   sprintf (x_full, "%s%s", a_config, a_cname);
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(verify)-------------------------*/
   rc = yjobs_central_old  (a_runas, a_mode, a_cname, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle)-------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   switch (a_mode) {
   case CASE_STATS :
   case CASE_FIX   :
   case CASE_ONLY  :
      rc_final = RC_POSITIVE;
      break;
   case ACT_LIST :
      if (!yJOBS_ifverbose ()) yURG_msg_live ();
      yURG_msg (':', "%s", x_full);
      if (!yJOBS_ifverbose ()) yURG_msg_mute ();
      rc_final = RC_POSITIVE;
      break;
   default         :
      rc = x_callback (YJOBS_PULL , x_full);
      DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
      switch (rc) {
      case RC_ACK      :
      case RC_POSITIVE :
      case RC_OVERRIDE :
      case RC_REPAIR   :
      case RC_WARNING  :
         rc_final = rc;
         break;
      default :
         rc_final = RC_FATAL;
      }
   }
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(clear data)---------------------*/
   if        (strstr (a_config, "/etc/") != NULL) {
      DEBUG_YJOBS   yLOG_note    ("retain data from /etc/ config file");
   } else if (a_mode != 0 && strchr (g_act_kep, a_mode) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("retain data from all file pulls");
   } else {
      DEBUG_YJOBS   yLOG_note    ("purge each file pulled");
      rc = x_callback (YJOBS_PURGE, x_full);
      DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__share_multiple   (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback)
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
   rc = yjobs_dir_list (a_config, x_list);
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
      rc = yjobs__share_filter (p, x_prefix, a_uid);
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

char
yjobs__share_multi_OLD  (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_prefix    [LEN_USER]  = "";
   int         x_all       =    0;
   int         x_total     =    0;
   int         x_count     =    0;
   int         x_pass      =    0;
   int         x_warns     =    0;
   int         x_error     =    0;
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
   /*---(open dir)-----------------------*/
   x_dir = opendir (a_config);
   DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      yURG_err ('f', "could not open configuration directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "successfully openned configuration directory");
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
   x_file = readdir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      /*---(header)-----------------------------*/
      DEBUG_YJOBS   yLOG_info    ("d_name"    , x_file->d_name);
      /*---(ignore-standards)-------------------*/
      if (x_file->d_name [0] == '.') {
         switch (x_file->d_name [1]) {
         case '.'  : case '\0' :
            x_file = readdir (x_dir);
            DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
            continue;
            break;
         }
      }
      ++x_all;
      /*---(simple filtering)-------------------*/
      rc = yjobs__share_filter (x_file->d_name, x_prefix, a_uid);
      DEBUG_YJOBS   yLOG_value   ("filter"    , rc);
      if (rc != 0)  ++x_total;
      if (rc <= 0) {
         DEBUG_YJOBS   yLOG_note    ("not a valid job/khronos file");
         x_file = readdir (x_dir);
         DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
         continue;
      }
      rc = yjobs__share_single   (a_runas, a_mode, a_config, x_file->d_name, a_user, a_uid, f_callback);
      DEBUG_YJOBS   yLOG_value   ("single"    , rc);
      if (rc < 0) rc = 3;
      switch (rc) {
      case 1   : ++x_pass;   break;
      case 3   : ++x_warns;  break;
      case 4   : ++x_error;  break;
      }
      ++x_count;
      DEBUG_YJOBS   yLOG_complex ("counts"    , "%d all  , %d total, %d count, %d pass , %d warns, %d error", x_all, x_total, x_count, x_pass, x_warns, x_error);
      /*---(next)------------------------*/
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
   /*---(summary)------------------------*/
   yURG_msg ('>', "summary of central file review...");
   DEBUG_YJOBS   yLOG_complex ("FINAL"     , "%d all  , %d total, %d count, %d pass , %d warns, %d error", x_all, x_total, x_count, x_pass, x_warns, x_error);
   if      (x_all   == 0)  { yURG_msg ('-', "empty, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);           ; rc_final = 0; }
   else if (x_count == 0)  { yURG_msg ('-', "nothing to see, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);  ; rc_final = 0; }
   else if (x_error >  0)  { yURG_msg ('-', "ERRORS, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);          ; rc_final = 4; }
   else if (x_warns >  0)  { yURG_msg ('-', "warning, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);         ; rc_final = 3; }
   else                    { yURG_msg ('-', "success, all %d, total %d, count %d, pass  %d, warns %d, error %d", x_all, x_total, x_count, x_pass, x_warns, x_error);         ; rc_final = 1; }
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
yjobs_share_review      (char a_func [LEN_TITLE], char a_area, char a_runas, char a_mode, void *f_callback, char a_fail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   char        x_user      [LEN_USER]  = "";
   int         x_uid       =    0;
   char        x_config    [LEN_PATH]  = "";
   char        x_prefix    [LEN_USER]  = "";
   char        x_cname     [LEN_DESC]  = "";
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   int         x_total     =    0;
   int         x_count     =    0;
   int         x_pass      =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (a_func);
   /*---(header)-------------------------*/
   yURG_msg ('>', "configuration central file review...");
   /*---(running as)---------------------*/
   rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, NULL, x_user, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   yURG_msg ('-', "currently running as å%sæ (%d)", x_user, x_uid);
   /*---(directory)-----------------------------*/
   rc = yjobs_who_location (a_runas, x_config, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      yURG_err ('f', "could not identify configuration directory");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   yURG_msg ('-', "configuration directory is å%sæ", x_config);
   DEBUG_YJOBS   yLOG_info    ("x_config"  , x_config);
   /*---(file)----------------------------------*/
   rc = yjobs_who_naming   (a_runas, NULL, NULL, NULL, NULL, NULL, x_cname);
   DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
   --rce;  if (rc <  0) {
      yURG_err ('f', "could not identify configuration file name");
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   yURG_msg ('-', "configuration file name is å%sæ", x_cname);
   DEBUG_YJOBS   yLOG_info    ("x_cname"   , x_cname);
   /*---(handle zero)---------------------------*/
   if (strcmp (x_config, "") == 0) {
      yURG_msg ('-', "skipping, zero configuration for application");
      DEBUG_YJOBS   yLOG_exit    (a_func);
      return 0;
   }
   /*---(handle file)---------------------------*/
   --rce;  if (strcmp (x_cname, "") != 0) {
      yURG_msg ('-', "single-file configuration set-up");
      rc = yjobs__share_single   (a_runas, a_mode, x_config, x_cname, x_user, x_uid, f_callback);
      DEBUG_YJOBS   yLOG_value   ("single"    , rc);
      if (rc < 0)  {
         if (a_fail == 'y') {
            DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
            return rce;
         }
      } else if (rc >= 3) {
         yURG_msg ('-', "warning, trouble with audit, see details above");
      }
   }
   /*---(multiple files)------------------------*/
   else {
      yURG_msg ('-', "multiple-file configuration set-up");
      rc = yjobs__share_multiple (a_runas, a_mode, x_config, x_cname, x_user, x_uid, f_callback);
      DEBUG_YJOBS   yLOG_value   ("multiple"  , rc);
      if (rc < 0)  {
         if (a_fail == 'y') {
            DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
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
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return rc_final;
}

/*> char         /+--> review central files --------------------------------------+/                                                                        <* 
 *> yjobs__maint_review_OLD (char a_runas, char a_act, char a_oneline [LEN_HUND], char a_muser [LEN_USER], int a_muid, char *a_regex, void *f_assimilate)   <* 
 *> {                                                                                                                                                       <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                             <* 
 *>    char        rce         =  -10;                                                                                                                      <* 
 *>    int         rc          =    0;                                                                                                                      <* 
 *>    DIR        *x_dir       = NULL;                                                                                                                      <* 
 *>    tDIRENT    *x_file      = NULL;                                                                                                                      <* 
 *>    int         x_total     =    0;                                                                                                                      <* 
 *>    int         x_count     =    0;                                                                                                                      <* 
 *>    int         x_pass      =    0;                                                                                                                      <* 
 *>    char        x_prefix    [LEN_USER]  = "";                                                                                                            <* 
 *>    char        x_central   [LEN_PATH]  = "";                                                                                                            <* 
 *>    /+---(header)-------------------------+/                                                                                                             <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                                                                                           <* 
 *>    /+---(defense)------------------------+/                                                                                                             <* 
 *>    rc = yjobs_act__prepare (a_runas, a_act, a_oneline, a_muser, a_regex, x_prefix, x_central, f_assimilate);                                            <* 
 *>    DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);                                                                                                       <* 
 *>    --rce;  if (rc < 0)  {                                                                                                                               <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                                   <* 
 *>       return rce;                                                                                                                                       <* 
 *>    }                                                                                                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_info    ("x_central" , x_central);                                                                                                <* 
 *>    x_dir = opendir (x_central);                                                                                                                         <* 
 *>    DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);                                                                                                    <* 
 *>    --rce;  if (x_dir == NULL) {                                                                                                                         <* 
 *>       /+> RUN_USER     printf ("fatal, can not open khronos central directory\n");    <+/                                                               <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                                   <* 
 *>       return rce;                                                                                                                                       <* 
 *>    }                                                                                                                                                    <* 
 *>    /+---(walk files)---------------------+/                                                                                                             <* 
 *>    DEBUG_YJOBS   yLOG_note    ("walk through directory files");                                                                                         <* 
 *>    while ((x_file = readdir (x_dir)) != NULL) {                                                                                                         <* 
 *>       /+---(simple filtering)-------------------+/                                                                                                      <* 
 *>       rc = yjobs_act__filter (x_file->d_name, x_prefix, a_muid);                                                                                        <* 
 *>       if (rc != 0)  ++x_total;                                                                                                                          <* 
 *>       if (rc <= 0) {                                                                                                                                    <* 
 *>          DEBUG_YJOBS   yLOG_note    ("not a valid job/khronos file");                                                                                   <* 
 *>          continue;                                                                                                                                      <* 
 *>       }                                                                                                                                                 <* 
 *>       /+---(filter using regex)-----------------+/                                                                                                      <* 
 *>       rc = yREGEX_filter (x_file->d_name);                                                                                                              <* 
 *>       DEBUG_YJOBS   yLOG_value   ("exec"      , rc);                                                                                                    <* 
 *>       if (rc <= 0) {                                                                                                                                    <* 
 *>          DEBUG_YJOBS   yLOG_note    ("does not match regex, skipping");                                                                                 <* 
 *>          continue;                                                                                                                                      <* 
 *>       }                                                                                                                                                 <* 
 *>       /+---(actions)----------------------------+/                                                                                                      <* 
 *>       switch (a_act) {                                                                                                                                  <* 
 *>       case ACT_LIST      :                                                                                                                              <* 
 *>          yURG_msg_live ();                                                                                                                              <* 
 *>          yURG_msg (':', "%s", x_file->d_name);                                                                                                          <* 
 *>          yURG_msg_mute ();                                                                                                                              <* 
 *>          rc = 0;                                                                                                                                        <* 
 *>          break;                                                                                                                                         <* 
 *>       case ACT_AUDIT     : case ACT_CAUDIT    : case ACT_VAUDIT    :                                                                                    <* 
 *>       case ACT_NORMAL    : case ACT_CNORMAL   : case ACT_VNORMAL   :                                                                                    <* 
 *>       case ACT_DAEMON    : case ACT_CDAEMON   : case ACT_VDAEMON   :                                                                                    <* 
 *>       case ACT_PRICKLY   : case ACT_CPRICKLY  : case ACT_VPRICKLY  :                                                                                    <* 
 *>          yURG_msg (' ', "");                                                                                                                            <* 
 *>          rc = yJOBS_act_check   (a_runas, a_act, a_oneline, x_file->d_name, s_assimilate);                                                              <* 
 *>          break;                                                                                                                                         <* 
 *>       }                                                                                                                                                 <* 
 *>       ++x_count;                                                                                                                                        <* 
 *>       if (rc >= 0)  ++x_pass;                                                                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_complex ("counts"    , "%d total, %d count, %d pass", x_total, x_count, x_pass);                                               <* 
 *>       /+---(done)------------------------+/                                                                                                             <* 
 *>    }                                                                                                                                                    <* 
 *>    /+---(summary)------------------------+/                                                                                                             <* 
 *>    DEBUG_YJOBS   yLOG_value   ("found"     , x_total);                                                                                                  <* 
 *>    DEBUG_YJOBS   yLOG_value   ("processed" , x_count);                                                                                                  <* 
*>    DEBUG_YJOBS   yLOG_value   ("passed"    , x_pass);                                                                                                   <* 
*>    /+---(close)--------------------------+/                                                                                                             <* 
*>    rc = closedir (x_dir);                                                                                                                               <* 
*>    DEBUG_YJOBS   yLOG_point   ("close"     , rc);                                                                                                       <* 
*>    --rce;  if (rc < 0) {                                                                                                                                <* 
   *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                                   <* 
      *>       return rce;                                                                                                                                       <* 
      *>    }                                                                                                                                                    <* 
      *>    /+---(summary)------------------------+/                                                                                                             <* 
      *>    rc = 1;                                                                                                                                              <* 
      *>    --rce;  if (x_count <= 0) {                                                                                                                          <* 
         *>       DEBUG_YJOBS   yLOG_note    ("job/khronos count is zero");                                                                                         <* 
            *>       yURG_msg (' ', "");                                                                                                                               <* 
            *>       IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but no job/khronos files found installed in central directory");                                     <* 
            *>       IF_CREVIEW  yURG_msg_live ();                                                                                                                     <* 
            *>       IF_CREVIEW  yURG_msg (':', "WARNING, secure, but no job/khronos files found installed in central directory");                                     <* 
            *>       IF_CREVIEW  yURG_msg_mute ();                                                                                                                     <* 
            *>       rc = 0;                                                                                                                                           <* 
            *>       IF_AUDIT    rc = rce;                                                                                                                             <* 
            *>       IF_PRICKLY  rc = rce;                                                                                                                             <* 
            *>    }                                                                                                                                                    <* 
            *>    --rce;  if (x_count != x_pass) {                                                                                                                     <* 
               *>       DEBUG_YJOBS   yLOG_note    ("job/khronos count not equal passed");                                                                                <* 
                  *>       yURG_msg (' ', "");                                                                                                                               <* 
                  *>       IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);                       <* 
                  *>       if (rc == 1) {                                                                                                                                    <* 
                     *>          IF_CREVIEW  yURG_msg_live ();                                                                                                                  <* 
                        *>          IF_CREVIEW  yURG_msg (':', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);                    <* 
                        *>          IF_CREVIEW  yURG_msg_mute ();                                                                                                                  <* 
                        *>       }                                                                                                                                                 <* 
                        *>       rc = 0;                                                                                                                                           <* 
                        *>       IF_AUDIT    rc = rce;                                                                                                                             <* 
                        *>       IF_PRICKLY  rc = rce;                                                                                                                             <* 
                        *>    }                                                                                                                                                    <* 
                        *>    --rce;  if (x_total != x_count) {                                                                                                                    <* 
                           *>       DEBUG_YJOBS   yLOG_note    ("job/khronos count not equal to total files");                                                                        <* 
                              *>       yURG_msg (' ', "");                                                                                                                               <* 
                              *>       IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);           <* 
                              *>       if (rc == 1) {                                                                                                                                    <* 
                                 *>          IF_CREVIEW  yURG_msg_live ();                                                                                                                  <* 
                                    *>          IF_CREVIEW  yURG_msg (':', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);        <* 
                                    *>          IF_CREVIEW  yURG_msg_mute ();                                                                                                                  <* 
                                    *>       }                                                                                                                                                 <* 
                                    *>       rc = 0;                                                                                                                                           <* 
                                    *>       IF_AUDIT    rc = rce;                                                                                                                             <* 
                                    *>       IF_PRICKLY  rc = rce;                                                                                                                             <* 
                                    *>    }                                                                                                                                                    <* 
                                    *>    IF_LIST   rc = 1;                                                                                                                                    <* 
                                    *>    if (rc == 1) {                                                                                                                                       <* 
                                       *>       DEBUG_YJOBS   yLOG_note    ("all results golden");                                                                                                <* 
                                          *>       yURG_msg (' ', "");                                                                                                                               <* 
                                          *>       IF_VREVIEW  yURG_msg ('>', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);                                          <* 
                                          *>       IF_CREVIEW  yURG_msg_live ();                                                                                                                     <* 
                                          *>       IF_CREVIEW  yURG_msg (':', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);                                          <* 
                                          *>       IF_CREVIEW  yURG_msg_mute ();                                                                                                                     <* 
                                          *>    }                                                                                                                                                    <* 
                                          *>    DEBUG_YJOBS   yLOG_value   ("x_count"   , x_count);                                                                                                  <* 
                                          *>    if (rc >= 0) {                                                                                                                                       <* 
                                             *>       if (x_count > 100) x_count = 100;                                                                                                                 <* 
                                                *>       rc = x_count;                                                                                                                                     <* 
                                                *>    }                                                                                                                                                    <* 
                                                *>    DEBUG_YJOBS   yLOG_value   ("rc"        , rc);                                                                                                       <* 
                                                *>    /+---(complete)-----------------------+/                                                                                                             <* 
                                                *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                                                           <* 
                                                *>    return rc;                                                                                                                                           <* 
                                                *> }                                                                                                                                                       <*/


