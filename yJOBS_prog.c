/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char
yJOBS_driver            (char a_runas, char a_mode, char *a_oneline, char *a_file, char *a_user, int a_uid, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(route action)-------------------*/
   --rce;  switch (a_mode) {
   case ACT_VERIFY     : case ACT_CVERIFY    : case ACT_VVERIFY    :
      rc = yJOBS_act_verify  (a_runas, a_mode, a_oneline, a_file, a_assimilate);
      break;
   case ACT_INSTALL    : case ACT_CINSTALL   : case ACT_VINSTALL   :
      rc = yJOBS_act_install (a_runas, a_mode, a_oneline, a_file, a_assimilate);
      break;
   case ACT_CHECK      : case ACT_CCHECK     : case ACT_VCHECK     :
      rc = yJOBS_act_check   (a_runas, a_mode, a_oneline, a_file, a_assimilate);
      break;
   case ACT_REMOVE     : case ACT_CREMOVE    : case ACT_VREMOVE    :
      rc = yJOBS_act_remove  (a_runas, a_mode, a_oneline, a_file);
      break;
   case ACT_LIST       : case ACT_COUNT      :
      rc = yJOBS_act_review  (a_runas, a_mode, a_oneline, a_user, a_uid, "*", a_assimilate);
      break;
   case ACT_AUDIT      : case ACT_CAUDIT     : case ACT_VAUDIT     :
      rc = yJOBS_act_review  (a_runas, a_mode, a_oneline, a_user, a_uid, "*", a_assimilate);
      break;
   case ACT_DAEMON     : case ACT_CDAEMON    : case ACT_VDAEMON    :
      rc = yJOBS_act_review  (a_runas, a_mode, a_oneline, a_user, a_uid, "*", a_assimilate);
      IF_NORUN  break;
      /* launch daemon, unless security breach or no crontabs */
      /*  damaged crontabs don't effect this one as they did not assimilate */
      break;
   case ACT_PRICKLY    : case ACT_CPRICKLY   : case ACT_VPRICKLY   :
      rc = yJOBS_act_review  (a_runas, a_mode, a_oneline, a_user, a_uid, "*", a_assimilate);
      IF_NORUN  break;
      /* then, if passed perfectly, launch in daemon mode */
      /* ANYTHING damaged or funky caused a no launch     */
      break;
   case ACT_NORMAL     : case ACT_CNORMAL    : case ACT_VNORMAL    :
      rc = yJOBS_act_review  (a_runas, a_mode, a_oneline, a_user, a_uid, "*", a_assimilate);
      IF_NORUN  break;
      /* then, run in foreground                          */
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return rc;
}
