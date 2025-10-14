/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                       helper function                        ----===*/
/*====================------------------------------------====================*/
static void      o___HELPER_____________o (void) {;}

char
yjobs_db__check         (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_msg       [LEN_HUND]  = "";
   char       *x_fatal     = "host-program specific configuration is illegal";
   /*---(trouble)------------------------*/
   --rce;  if (a_hdir == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "configured central data directory name is NULL", LEN_HUND);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      ySCORE_mark (myJOBS.m_yscore, "CSECURE"  , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_db   == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "configured central database name is NULL", LEN_HUND);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      ySCORE_mark (myJOBS.m_yscore, "DSECURE"  , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(perfect miss)-------------------*/
   if (strcmp (a_hdir, "") == 0 && strcmp (a_db  , "") == 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "skipping, host program does not use ANY central data", LEN_HUND);
      yURG_msg ('-', x_msg);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(just no database)---------------*/
   if (strcmp (a_hdir, "") != 0 && strcmp (a_db  , "") == 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "skipping, host program does not use a central database", LEN_HUND);
      yURG_msg ('-', x_msg);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(more trouble)-------------------*/
   --rce;  if (strcmp (a_hdir, "") == 0 && strcmp (a_db  , "") != 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "central data directory empty, while configured for central database", LEN_HUND);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      ySCORE_mark (myJOBS.m_yscore, "DSECURE"  , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(callback)-----------------------*/
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      strlcpy (x_msg, "host-program callback function is NULL", LEN_HUND);
      DEBUG_YJOBS   yLOG_snote   (x_msg);
      ySCORE_mark (myJOBS.m_yscore, "CALL"     , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, x_msg, "host-program specific configuration is illegal");
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                         security                             ----===*/
/*====================------------------------------------====================*/
static void      o___SECURITY___________o (void) {;}


char
yjobs_db_read           (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   char        x_audit     =  '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_rdb, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_rdb);
      DEBUG_YJOBS   yLOG_snote   ("database read not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "read the central database (READ)...");
   /*---(check audit)--------------------*/
   if (yJOBS_ifaudit ())  x_audit = 'y';
   if (yJOBS_iffix ())    x_audit = 'y';
   /*---(check request)------------------*/
   rc = yjobs_db__check (a_runas, a_mode, a_hdir, a_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("check"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == RC_ACK) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(score)--------------------------*/
   if (x_audit == '-')  ySCORE_mark (myJOBS.m_yscore, "DREAD"    , G_SCORE_FAIL);
   else                 ySCORE_mark (myJOBS.m_yscore, "DAUDIT"   , G_SCORE_FAIL);
   /*---(convert callback----------------*/
   x_callback = f_callback;
   DEBUG_YJOBS   yLOG_point   ("callback"  , x_callback);
   /*---(call)---------------------------*/
   rc = x_callback (YJOBS_READ, "");
   DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "host reports database did not load properly", "trouble reading database");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   if (x_audit == '-')  ySCORE_mark (myJOBS.m_yscore, "DREAD"    , 'Ô');
   else                 ySCORE_mark (myJOBS.m_yscore, "DAUDIT"   , 'a');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(check for audit)----------------*/
   if (x_audit == 'y') {
      yURG_msg ('>', "audit-only, purge database after read");
      DEBUG_YJOBS   yLOG_note    ("audit-only, purge database after read");
      rc = x_callback (YJOBS_PURGE, "");
      DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_db_write          (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   char        x_audit     =  '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_wdb, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_wdb);
      DEBUG_YJOBS   yLOG_snote   ("database write not required");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(check for audit, reduntant)-----*/
   if (yJOBS_ifaudit ())  x_audit = 'y';
   if (yJOBS_iffix ())    x_audit = 'y';
   if (x_audit == 'y') {
      ySCORE_mark (myJOBS.m_yscore, "DWRITE"   , 'a');
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_snote   ("audit-only, database not to be written");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "write the central database (WRITE)...");
   /*---(check request)------------------*/
   rc = yjobs_db__check (a_runas, a_mode, a_hdir, a_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("check"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == RC_ACK) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "DWRITE"   , G_SCORE_FAIL);
   /*---(convert callback----------------*/
   x_callback = f_callback;
   DEBUG_YJOBS   yLOG_point   ("callback"  , x_callback);
   /*---(call)---------------------------*/
   rc = x_callback (YJOBS_WRITE, "");
   DEBUG_YJOBS   yLOG_value   ("write db"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "host reports database did not save properly", "trouble writing database");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "DWRITE"   , 'Õ');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}


