/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                         data audits                          ----===*/
/*====================------------------------------------====================*/
static void      o___DATA_____________o (void) {;};

char         /*-> check security, but not content ----------------------------*/
yjobs_maint_secure      (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_config [LEN_LABEL], char a_hdir [LEN_DESC], char a_db [LEN_LABEL], char a_world [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   /*---(config directory)---------------*/
   rc = yjobs_dir_secure      (a_runas, a_mode, "configuration", a_cdir, NULL , NULL);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check main config)--------------*/
   rc = yjobs_config_secure   (a_runas, a_mode, a_cdir, a_config);
   DEBUG_YJOBS   yLOG_value   ("conf_sec"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(central directory)--------------*/
   rc = yjobs_dir_secure      (a_runas, a_mode, "central data" , a_hdir, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check database)-----------------*/
   rc = yjobs_db_secure       (a_runas, a_mode, a_hdir, a_db);
   DEBUG_YJOBS   yLOG_value   ("db_sec"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check world)--------------------*/
   rc = yjobs_world_secure    (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("world_sec" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_check      (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_file [LEN_LABEL], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_user      [LEN_USER]  = "";
   int         x_uid       =    0;
   char        x_fix       =  '-';
   char        x_full      [LEN_PATH]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_chk, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_chk);
      DEBUG_YJOBS   yLOG_snote   ("single file review not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "configuration single file review...");
   /*---(default)------------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  1, G_SCORE_SKIP);                <*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, G_SCORE_SKIP);                <*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
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
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir == NULL || a_cdir [0] == '\0') {
      yURG_err ('f', "could not identify configuration directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration directory is å%sæ", a_cdir);
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file  == NULL || a_file [0] == '\0') {
      yURG_err ('f', "could not identify configuration file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration file is å%sæ", a_file);
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(prepare)------------------------*/
   sprintf (x_full, "%s%s", a_cdir, a_file);
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   yURG_msg ('-', "fully qualified file name å%sæ", x_full);
   /*---(check file)---------------------*/
   /*> rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);     <*/
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> if (strstr  (x_full, "/etc/") != NULL)       rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  1, 'e');   <*/
   /*> else                                         rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  1, 'c');   <*/
   DEBUG_YJOBS   yLOG_value   ("post-score", rc);
   /*---(verify contents-----------------*/
   rc = x_callback (YJOBS_PULL , x_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   /*> if      (rc >  1)  { rc_final = RC_WARNING;  rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, 'Ö');          }   <*/
   /*> else if (rc == 1)  { rc_final = RC_POSITIVE; rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, 'Ö');          }   <*/
   /*> else if (rc == 0)  { rc_final = RC_POSITIVE; rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, 'Ö');          }   <*/
   /*> else               { rc_final = RC_FATAL;    rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, G_SCORE_FAIL); }   <*/
   /*---(clear data)---------------------*/
   rc = x_callback (YJOBS_PURGE, x_full);
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   if (rc < 0)  {
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else if (rc >= 4) {
      yURG_msg ('-', "warning, trouble with audit, see details above");
   }
   /*---(wrap up)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_central    (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL], char a_database [LEN_LABEL], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_fix       =  '-';
   char        x_hdir      [LEN_DESC]  = "";
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("configuration audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(title)---------------------------------*/
   yURG_msg ('>', "central data directory setup/security review...");
   DEBUG_YJOBS   yLOG_char    ("c_hardfail", c_hardfail);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   /*> rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);                <*/
   /*> if (x_fix == 'y')  rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  1, G_SCORE_FAIL);   <*/
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_hdir"    , a_hdir);
   --rce;  if (a_hdir       == NULL) {
      yURG_err ('f', "central data directory is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "", "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "", "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_hdir"    , a_hdir);
   --rce;  if (strcmp (a_hdir, "") == 0) {
      DEBUG_YJOBS   yLOG_point   ("a_world"   , a_world);
      if (a_world    != NULL && a_world [0]    != '\0') {
         yURG_err ('f', "configured for world file, but no central data directory (illegal setup)");
         yjobs_ends_failure (a_mode, "", "host program configuration is illegal");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_database != NULL && a_database [0] != '\0') {
         yURG_err ('f', "configured for database, but no central data directory (illegal setup)");
         yjobs_ends_failure (a_mode, "", "host program configuration is illegal");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "skipping, no central data directory specified for application");
      /*> rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  0, 'a');                      <*/
      /*> if (x_fix == 'y')  rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  1, 'f');   <*/
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check directory)-----------------------*/
   /*> rc = yjobs_dir_single (0, a_hdir, x_fix);                                      <*/
   DEBUG_YJOBS   yLOG_value   ("single"    , rc);
   --rce;  if (rc <  0) {
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "warning, central data directory has issues");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 4;
   } else if (rc == RC_REPAIR) {
      yURG_msg ('-', "repaired, central data directory basic security measures updated");
      rc_final = RC_REPAIR;
   } else {
      yURG_msg ('-', "success, central data directory basic security measures confirmed");
      rc_final = RC_POSITIVE;
   }
   /*---(audit world file)----------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_world"   , a_world);
   if (a_world == NULL || strcmp (a_world, "") == 0) {
      yURG_msg ('>', "audit the central world file...");
      yURG_msg ('-', "no world file specified for this host");
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  0, G_SCORE_SKIP);                <*/
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  1, G_SCORE_SKIP);                <*/
   } else {
      DEBUG_YJOBS   yLOG_info    ("a_world"   , a_world);
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  0, G_SCORE_FAIL);                <*/
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  1, G_SCORE_FAIL);                <*/
      /*---(check file)-------------------------*/
      rc = yjobs_central_data (a_hdir, a_world, x_fix);
      DEBUG_YJOBS   yLOG_value   ("data"      , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "world file does not exist or is not properly secured");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  0, 'w');                         <*/
      /*---(check contents)---------------------*/
      rc = yjobs_world_audit (a_runas, a_mode, a_hdir, a_world);
      DEBUG_YJOBS   yLOG_value   ("world"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "world file content audit failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      /*> rc = yjobs_ends_score_OLD (G_SCORE_WORLD,  1, 'Ô');                         <*/
   }
   /*---(audit database)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_database", a_database);
   if (strcmp (a_database, "") == 0) {
      yURG_msg ('>', "audit the central database...");
      yURG_msg ('-', "no database specified for this host");
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  0, G_SCORE_SKIP);             <*/
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  1, G_SCORE_SKIP);             <*/
   } else {
      DEBUG_YJOBS   yLOG_info    ("a_database", a_database);
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  0, G_SCORE_FAIL);             <*/
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  1, G_SCORE_FAIL);             <*/
      /*---(check file)-------------------------*/
      rc = yjobs_central_data (a_hdir, a_database, x_fix);
      DEBUG_YJOBS   yLOG_value   ("database"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "database does not exist or is not properly secured");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      /*---(check contents)---------------------*/
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      --rce;  if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "central database could not be read");
         DEBUG_YJOBS   yLOG_note    ("FATAL, central database could not be read");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  1, 'Ô');                      <*/
      /*---(wrap)-------------------------------*/
      rc = x_callback (YJOBS_PURGE, "");
      DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
      /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  0, 'p');                      <*/
   }
   /*---(score end)----------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  0, 'a');                         <*/
   if (x_fix == 'y')  {
      /*> if (rc_final == RC_REPAIR)  rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  1, 'F');   <*/
      /*> else                        rc = yjobs_ends_score_OLD (G_SCORE_SECURE  ,  1, 'f');   <*/
   }
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_stats      (char a_mode, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode != ACT_STATS) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_schar   (a_mode);
      DEBUG_YJOBS   yLOG_schar   (ACT_STATS);
      DEBUG_YJOBS   yLOG_snote   ("statistics not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(default)------------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  2, G_SCORE_FAIL);                <*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "", "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_note    ("FATAL, host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("request to produce database/central file statistics");
   x_callback = f_callback;
   rc = x_callback (YJOBS_STATS, "");
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "database could not produce statistics");
      DEBUG_YJOBS   yLOG_note    ("FATAL, database could not produce statistics");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  2, '#');                         <*/
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs__maint_report     (char a_mode, char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_rpt, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_rpt);
      DEBUG_YJOBS   yLOG_snote   ("central data reporting not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(default)------------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  3, G_SCORE_FAIL);                <*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "", "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_note    ("FATAL, host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("request to produce database/central data report");
   x_callback = f_callback;
   rc = x_callback (YJOBS_REPORT, a_file);
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "central data/host could not produce report");
      DEBUG_YJOBS   yLOG_note    ("FATAL, central data/host could not produce report");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   /*> rc = yjobs_ends_score_OLD (G_SCORE_DATABASE,  3, 'ó');                         <*/
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}


char
yjobs__maint_scoring    (char a_runas, char a_mode)
{
   char        rc          =    0;
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("scoring table audit not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*> if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg_mute ();                   <*/
   yjobs_ends_init ();
   rc = yENV_score_audit ();
   /*> if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg_live ();                   <*/
   return rc;
}


/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER___________o (void) {;};

char
yjobs_maint_full        (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   int         x_ruid      =   -1;
   char        x_ruser     [LEN_USER]  = "";
   char        x_cdir      [LEN_DESC]  = "";
   char        x_conf      [LEN_LABEL] = "";
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_cuse      =  '-';
   char        x_cgood     =  '-';
   char        x_duse      =  '-';
   char        x_dgood     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_ends_prepare (a_runas, a_mode, a_oneline, a_file, &x_ruid, x_ruser, f_callback, x_cdir, x_conf, x_hdir, x_world, x_db, NULL, NULL, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check system security)----------*/
   rc = yjobs_maint_secure      (a_runas, a_mode, x_cdir, x_conf, x_hdir, x_db, x_world, f_callback);
   DEBUG_YJOBS   yLOG_value   ("secure"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check sinsle)-------------------*/
   /*> rc = yjobs__maint_check    (a_runas, a_mode, x_cdir, a_file, f_callback, '-');   <* 
    *> DEBUG_YJOBS   yLOG_value   ("check"     , rc);                                   <* 
    *> --rce;  if (rc < 0) {                                                            <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                               <* 
    *>    return rce;                                                                   <* 
    *> }                                                                                <* 
    *> if      (rc > rc_final)  rc_final = rc;                                          <* 
    *> else if (rc < 0)         rc_final = RC_FATAL;                                    <*/
   /*> DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);                           <*/
   /*---(check/load data)----------------*/
   /*> rc = yjobs__maint_central  (a_runas, a_mode, x_hdir, x_world, x_db, f_callback, '-');   <* 
    *> DEBUG_YJOBS   yLOG_value   ("central"   , rc);                                          <* 
    *> --rce;  if (rc < 0) {                                                                   <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                      <* 
    *>    return rce;                                                                          <* 
    *> }                                                                                       <* 
    *> if      (rc > rc_final)  rc_final = rc;                                                 <* 
    *> else if (rc < 0)         rc_final = RC_FATAL;                                           <*/
   /*> DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);                           <*/
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
   /*---(generate statistics)------------*/
   rc = yjobs__maint_stats    (a_mode, f_callback);
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(generate report)----------------*/
   rc = yjobs__maint_report   (a_mode, a_file, f_callback);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(scoring audit)------------------*/
   rc = yjobs__maint_scoring  (a_runas, a_mode);
   DEBUG_YJOBS   yLOG_value   ("scoring"   , rc);
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
   case RC_POSITIVE :  rc = yjobs_ends_success  (a_mode);                    rc = RC_POSITIVE;   break;
   case RC_OVERRIDE :  rc = yjobs_ends_approved (a_mode);                    rc = RC_OVERRIDE;   break;
   case RC_REPAIR   :  rc = yjobs_ends_repaired (a_mode);                    rc = RC_REPAIR;     break;
   case RC_WARNING  :  rc = yjobs_ends_warning  (a_mode);                    rc = RC_WARNING;    break;
   case RC_FATAL    :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = RC_FATAL;      break;
   default          :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = rce;           break;
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

char yjobs_maint             (void) { return yjobs_maint_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


