/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"




char
yjobs__share_single     (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    0;
   char        x_full      [LEN_PATH]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_pre       [LEN_TERSE] = "";
   char        x_suf       [LEN_TERSE] = "";
   int         x_uid       =    0;
   char        x_user      [LEN_USER]  = "";
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
   /*> sprintf (x_full, "%s%s", a_config, a_cname);                                   <*/
   /*---(naming standards)---------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   rc = yjobs_who_naming (a_runas, NULL, NULL, NULL, x_pre, x_suf, NULL);
   DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(title)--------------------------*/
   yURG_msg ('>', "central file security check...");
   /*---(security review)----------------*/
   DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
   rc = yENV_audit_central (YENV_NONE, a_config, a_cname, x_pre, x_suf, x_full, &x_uid, x_user);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "success, central file secure/acceptable");
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(save key data)------------------*/
   rc = yjobs_saveback (YJOBS_LOCAL, x_user, x_uid, "", a_cname, a_config, x_full);
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


