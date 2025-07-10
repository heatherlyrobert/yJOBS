/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*
 *   action      lvl
 *   ----------  ---  --db-in-- -secure-- --load--- --report- -intake-- --db-out- -register 
 *   verify      vÑV      ·         y         y         ·         ·         ·         ·       secure and load/audit
 *   local       lòL      ·         y         y         y         ·         ·         ·       secure and load/audit, and report
 *   register    béB      ·         y         y         ·         ·         ·         y       secure and load/audit, and register
 *   update      uûU      y         y         y         ·         y         y         ·       secure and load/audit, and update
 *   install     iðI      y         y         y         ·         y         y         y       secure and load/audit, and register and update
 *
 */

/*> static char      (*s_callback)   (char a_req, char a_full [LEN_PATH]) = NULL;     <*/




/*====================------------------------------------====================*/
/*===----                         sub-routines                         ----===*/
/*====================------------------------------------====================*/
static void      o___SUBS__________o (void) {;};

char
yjobs_in__secure        (char a_runas, char a_mode, char a_dir [LEN_PATH], char a_file [LEN_PATH], char r_fuser [LEN_USER])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_prefix    [LEN_TERSE] = "";
   char        x_suffix    [LEN_TERSE] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuid      =   -1;
   char       *x_fatal     = "file/dir security is problematic";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_complex ("a_args"    , "%c %c", a_runas, a_mode);
   /*---(score)--------------------------*/
   yURG_msg ('>', "local file/dir verification and security check (VERIFY)...");
   ySCORE_mark ("LTYPE"    , G_SCORE_FAIL);
   ySCORE_mark ("LSECURE"  , G_SCORE_FAIL);
   /*---(default)------------------------*/
   if (r_fuser  != NULL)  strcpy (r_fuser , "");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL || a_dir  [0] == '\0') {
      yjobs_ends_failure (a_mode, "local directory name is NULL/empty", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      yjobs_ends_failure (a_mode, "local file name is NULL/empty", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   /*---(directory)----------------------*/
   --rce;  if (strcmp (a_file, "") == 0) {
      DEBUG_YJOBS   yLOG_note    ("directory given");
      ySCORE_mark ("LTYPE"    , 'd');
      /*---(filter)----------------------*/
      DEBUG_YJOBS   yLOG_info    ("IAM_DIRS"  , IAM_DIRS);
      if (strchr (IAM_DIRS, a_runas) == NULL) {
         yjobs_ends_failure (a_mode, "requester (not polymnia/metis) can not request a directory, only a file", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(verify)----------------------*/
      rc = yAUDIT_localdir (a_dir, x_full, &x_fuid, r_fuser);
      DEBUG_YJOBS   yLOG_value   ("localdir"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(done)------------------------*/
   }
   /*---(file)---------------------------*/
   else {
      DEBUG_YJOBS   yLOG_note    ("file given");
      ySCORE_mark ("LTYPE"    , 'r');
      /*---(filter)----------------------*/
      DEBUG_YJOBS   yLOG_info    ("IAM_FILES" , IAM_FILES);
      if (strchr (IAM_FILES, a_runas) == NULL) {
         yjobs_ends_failure (a_mode, "requester (polymnia) can only request a directory, not a file", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(get program values)----------*/
      rc = yjobs_who_naming (a_runas, NULL, NULL, x_prefix, NULL, x_suffix, NULL);
      DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
      --rce;  if (rc < 0) {
         yjobs_ends_failure (a_mode, "can not retreive application naming data", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YJOBS   yLOG_info    ("x_prefix"  , x_prefix);
      DEBUG_YJOBS   yLOG_info    ("x_suffix"  , x_suffix);
      /*---(verify)----------------------*/
      rc = yAUDIT_local (a_dir, a_file, x_prefix, x_suffix, x_full, &x_fuid, r_fuser);
      DEBUG_YJOBS   yLOG_value   ("local"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(done)------------------------*/
   }
   /*---(score)--------------------------*/
   ySCORE_mark ("LSECURE"  , 's');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(save key data)------------------*/
   yURG_msg ('-', "success, local file/dir exists and security is acceptable");
   rc = yjobs_saveback (YJOBS_LOCAL, r_fuser, x_fuid, "", a_file, a_dir, x_full);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_in__pull          (char a_runas, char a_mode, void *f_callback, char a_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_flag     =    1;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   char        x_audit     =  '-';
   char       *x_fatal     = "trouble with local data pull";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(check audit)--------------------*/
   if (yJOBS_ifaudit ())  x_audit = 'y';
   if (yJOBS_iffix ())    x_audit = 'y';
   /*---(score)--------------------------*/
   yURG_msg ('>', "read source/configuration file into environment (PULL)...");
   if (x_audit == 'y')  ySCORE_mark ("LAUDIT"   , G_SCORE_FAIL);
   else                 ySCORE_mark ("LPULL"    , G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   x_callback = f_callback;
   rc = rc_flag = x_callback (YJOBS_PULL, a_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "local file unreadable or contents unacceptable", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_value   ("rc_flag"   , rc_flag);
   /*---(score)--------------------------*/
   if (x_audit == 'y')  ySCORE_mark ("LAUDIT"   , 'a');
   else                 ySCORE_mark ("LPULL"    , 'Ö');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(check for audit)----------------*/
   if (x_audit == 'y') {
      yURG_msg ('>', "audit-only, purge file after read (PURGE)...");
      DEBUG_YJOBS   yLOG_note    ("audit-only, purge file after read");
      rc = x_callback (YJOBS_PURGE, "");
      DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_flag;
}

char
yjobs_in__report        (char a_runas, char a_mode, void *f_callback, char a_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   char       *x_fatal     = "trouble with local report";
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || yJOBS_iflocalrpt () != 1) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   ("local report not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(score)--------------------------*/
   yURG_msg ('>', "create report from locally collected data (LOCALRPT)...");
   ySCORE_mark ("LREPORT"  , G_SCORE_FAIL);
   /*---(default)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   x_callback = f_callback;
   rc = x_callback (YJOBS_LOCALRPT, a_full);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "local report did not complete successfully", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   ySCORE_mark ("LREPORT"  , 'ò');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_in__name          (char a_runas, char a_mode, char a_file [LEN_PATH], char a_fuser [LEN_USER], char a_conf [LEN_LABEL], char r_new [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_cpre      [LEN_TERSE] = "";
   char       *p           = NULL;
   char        x_new       [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_new != NULL)  ystrlcpy (r_new , "", LEN_PATH);
   /*---(get prefix)---------------------*/
   rc = yjobs_who_naming (a_runas, NULL, NULL, NULL, x_cpre, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cpre"    , x_cpre);
   /*---(fixed central name)-------------*/
   --rce;  if (a_conf != NULL && strcmp (a_conf, "") != 0) {
      DEBUG_YJOBS   yLOG_note    ("central name is specific and fixed");
      ystrlcpy (x_new , a_conf, LEN_DESC);
   }
   /*---(changable prefix)---------------*/
   else if (strcmp (x_cpre, "(USER).") == 0) {
      DEBUG_YJOBS   yLOG_note    ("central prefix changes to user name");
      DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
      p = strchr (a_file, '.');
      DEBUG_YJOBS   yLOG_point   ("p"         , p);
      if (p == NULL) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YJOBS   yLOG_info    ("a_fuser"   , a_fuser);
      sprintf (x_new , "%s%s", a_fuser, p);
   }
   /*---(save-back)----------------------*/
   DEBUG_YJOBS   yLOG_info    ("x_new"     , x_new);
   if (r_new != NULL)  ystrlcpy (r_new , x_new, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_in__intake        (char a_runas, char a_mode, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_fuser [LEN_USER], char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], char a_db [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_cmd       [LEN_RECD]  = "";
   char        x_new       [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_msg       [LEN_HUND]  = "";
   char       *x_fatal     = "trouble with file intake";
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || (yJOBS_ifupdate () == 0 && yJOBS_ifinstall () == 0)) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   ("local to central copy not required");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(uses database)------------------*/
   if (a_db != NULL && strcmp (a_db, "") != 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_snote   ("host program uses central database, not files");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(score)------------------------------*/
   yURG_msg ('>', "install file in configuration directory (MOVE)...");
   ySCORE_mark ("LMOVE"    , G_SCORE_FAIL);
   yURG_msg ('-', "local file name %2då%sæ", strlen (a_file), a_file);
   /*---(get central info)-------------------*/
   rc = yjobs_in__name (a_runas, a_mode, a_file, a_fuser, a_conf, x_new);
   DEBUG_YJOBS   yLOG_value   ("name"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "could not create configuration name", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_new"     , x_new);
   /*---(make full new file name)------------*/
   rc = yENV_name_full (a_cdir, x_new, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "could not create full name", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(copy file)--------------------------*/
   snprintf (x_cmd, LEN_RECD, "cp -f %s %s > /dev/null  2>&1", a_file, x_full);
   DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      sprintf (x_msg, "could not copy (system) to å%sæ", a_cdir);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      sprintf (x_msg, "could not copy (wifexited) to å%sæ", a_cdir);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-updates)----------------------*/
   rc = chown (x_full, 0, 0);
   DEBUG_YJOBS   yLOG_value   ("chown"     , rc);
   rc = chmod (x_full, 0600);
   DEBUG_YJOBS   yLOG_value   ("chmod"     , rc);
   /*---(confirmmation)----------------------*/
   rc = yAUDIT_reg (YENV_FIX, YENV_STANDARD, a_cdir, x_new, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("exists"    , rc);
   --rce;  if (rc < 0) {
      sprintf (x_msg, "file could not be confirmed in configuration location (%3d)", rc);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(summary)----------------------------*/
   yURG_msg ('-', "success, file confirmed as moved to configuration directory");
   ySCORE_mark ("LMOVE"    , 'm');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_in__register      (char a_runas, char a_mode, char a_file [LEN_PATH], char a_hdir [LEN_DESC], char a_world [LEN_LABEL], void *f_testcall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_testcall)   (char a_req, char a_full [LEN_PATH]);
   char       *x_fatal     = "trouble registering local file/dir";
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_reg, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_reg);
      DEBUG_YJOBS   yLOG_snote   ("register not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(no-database)--------------------*/
   if (a_world == NULL || strcmp (a_world, "") == 0) {
      if (strchr ("béB", a_mode) != NULL) {
         DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
         DEBUG_YJOBS   yLOG_note    ("host program requested register specifcally, but does not use world file");
         yURG_msg ('>', "register file/dir in world file (REGISTER)...");
         ySCORE_mark ("LREG"     , G_SCORE_FAIL);
         yjobs_ends_failure (a_mode, "requested register, but host does not use world file", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_snote   ("host program does not use world file");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(scoring)------------------------*/
   yURG_msg ('>', "register file/dir in world file (REGISTER)...");
   ySCORE_mark ("LREG"     , G_SCORE_FAIL);
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_point   ("f_testcall", f_testcall);
   if (f_testcall != NULL) {  /* special testing outlet */
      x_testcall = f_testcall;
      rc = x_testcall (ACT_REGISTER, "");
   }
   else {
      rc = yjobs_world_register (a_runas, a_mode, a_file, a_hdir, a_world);
   }
   /*---(handle trouble)-----------------*/
   DEBUG_YJOBS   yLOG_value   ("register"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "could not register in world file", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(scoring)------------------------*/
   ySCORE_mark ("LREG"     , 'r');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER___________o (void) {;};

char
yjobs_in_full           (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   char        rc_warn     =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_conf      [LEN_LABEL] = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_lpre      [LEN_TERSE] = "";
   char        x_cpre      [LEN_TERSE] = "";
   char        x_suf       [LEN_TERSE] = "";
   char        x_cwd       [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_ends_prepare (a_runas, a_mode, a_oneline, a_file, f_callback, NULL, NULL, x_cdir, x_conf, x_hdir, x_db, x_world, x_lpre, x_cpre, x_suf, x_cwd, x_dir, x_file, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_db_read        (a_runas, a_mode, x_hdir, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(verify local)-------------------*/
   rc = yjobs_in__secure   (a_runas, a_mode, x_cwd, x_file, x_fuser);
   DEBUG_YJOBS   yLOG_value   ("verify"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(pull local)---------------------*/
   rc = yjobs_in__pull     (a_runas, a_mode, f_callback, x_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(write report)-------------------*/
   rc = yjobs_in__report   (a_runas, a_mode, f_callback, x_full);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(local to central)---------------*/
   rc = yjobs_in__intake   (a_runas, a_mode, x_dir, x_file, x_fuser, x_cdir, x_conf, x_db);
   DEBUG_YJOBS   yLOG_value   ("intake"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(pull local)---------------------*/
   rc = yjobs_db_write       (a_runas, a_mode, x_hdir, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("writedb"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(register)-----------------------*/
   rc = yjobs_in__register (a_runas, a_mode, x_full, x_hdir, x_world, NULL);
   DEBUG_YJOBS   yLOG_value   ("register"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(footer)-------------------------*/
   switch (rc_final) {
   case RC_ACK      :
   case RC_POSITIVE :  rc = yjobs_ends_success  (a_mode);                    rc = RC_POSITIVE;  break;
   case RC_OVERRIDE :  rc = yjobs_ends_approved (a_mode);                    rc = RC_OVERRIDE;  break;
   case RC_REPAIR   :  rc = yjobs_ends_repaired (a_mode);                    rc = RC_REPAIR;    break;
   case RC_WARNING  :  rc = yjobs_ends_warning  (a_mode);                    rc = RC_WARNING;   break;
   case RC_FATAL    :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = RC_FATAL;     break;
   default          :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = rce;          break;
   }
   DEBUG_YJOBS   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char yjobs_in                (void) { return yjobs_in_full   (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


