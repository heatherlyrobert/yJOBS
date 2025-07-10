/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                         data audits                          ----===*/
/*====================------------------------------------====================*/
static void      o___DATA_____________o (void) {;};

char         /*-> check security, but not content ----------------------------*/
yjobs_maint_secure      (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], char a_hdir [LEN_DESC], char a_db [LEN_LABEL], char a_world [LEN_LABEL], char a_cpre [LEN_TERSE], char a_suf [LEN_TERSE], int a_ruid, char a_ruser [LEN_USER])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    = RC_POSITIVE;
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_sec, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_sec);
      DEBUG_YJOBS   yLOG_snote   ("securing environment not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(config directory)---------------*/
   rc = yjobs_dir_secure      (a_runas, a_mode, "configuration", a_cdir, NULL , NULL);
   DEBUG_YJOBS   yLOG_value   ("config_dir", rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check main config)--------------*/
   rc = yjobs_dir_all_secure (a_runas, a_mode, a_cdir, a_conf, a_cpre, a_suf, a_ruid, a_ruser);
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
   DEBUG_YJOBS   yLOG_value   ("home_dir"  , rc);
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
   yjobs_yscore_init ();
   rc = ySCORE_audit ();
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
   char        x_db        [LEN_LABEL] = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_cpre      [LEN_TERSE] = "";
   char        x_suf       [LEN_TERSE] = "";
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
   rc = yjobs_ends_prepare (a_runas, a_mode, a_oneline, a_file, &x_ruid, x_ruser, f_callback, x_cdir, x_conf, x_hdir, x_db, x_world, NULL, x_cpre, x_suf, NULL, NULL, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check system security)----------*/
   rc = yjobs_maint_secure      (a_runas, a_mode, x_cdir, x_conf, x_hdir, x_db, x_world, x_cpre, x_suf, x_ruid, x_ruser);
   DEBUG_YJOBS   yLOG_value   ("secure"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(audit all)----------------------*/
   rc = yjobs_dir_all_audit     (a_runas, a_mode, x_cdir, x_conf, x_ruid, x_ruser, f_callback);
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check sinsle)-------------------*/
   rc = yjobs_dir_one_check     (a_runas, a_mode, x_cdir, x_conf, x_cpre, x_suf, x_ruid, x_ruser, f_callback);
   DEBUG_YJOBS   yLOG_value   ("check"     , rc);
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


