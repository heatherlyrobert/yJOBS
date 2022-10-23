/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


static char (*s_runner) (void);

char
yJOBS_driver            (char *a_oneline, char *a_user, int a_uid, void *a_assimilate, void *a_runner)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(route action)-------------------*/
   --rce;  switch (g_runmode) {
   case CASE_VERIFY     :
      rc = yJOBS_act_verify  (g_runas, g_runmode, a_oneline, g_runfile, a_assimilate);
      break;
   case CASE_INSTALL    :
      rc = yJOBS_act_install (g_runas, g_runmode, a_oneline, g_runfile, a_assimilate);
      break;
   case CASE_CHECK      :
      rc = yJOBS_act_check   (g_runas, g_runmode, a_oneline, g_runfile, a_assimilate);
      break;
   case CASE_REMOVE     :
      rc = yJOBS_act_remove  (g_runas, g_runmode, a_oneline, g_runfile);
      break;
   case CASE_LIST       :
      rc = yJOBS_act_review  (g_runas, g_runmode, a_oneline, a_user, a_uid, "*", a_assimilate);
      break;
   case CASE_AUDIT      :
      rc = yJOBS_act_review  (g_runas, g_runmode, a_oneline, a_user, a_uid, "*", a_assimilate);
      break;
   case CASE_DAEMON     :
   case CASE_PRICKLY    :
      DEBUG_YEXEC   yLOG_note    ("processing a DAEMON/PRICKLY action");
      rc = yJOBS_act_review  (g_runas, g_runmode, a_oneline, a_user, a_uid, "*", a_assimilate);
      DEBUG_YEXEC   yLOG_value   ("review"    , rc);
      DEBUG_YEXEC   yLOG_char    ("g_norun"   , g_norun);
      IF_STRICT {
         if (rc < 0) {
            DEBUG_YEXEC   yLOG_note    ("prickly mode must exit");
            DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
            return rce;
         }
      }
      DEBUG_YEXEC   yLOG_point   ("a_runner"  , a_runner);
      IF_NORUN  break;
      if (a_runner != NULL) {
         DEBUG_YEXEC   yLOG_note    ("running the executer");
         s_runner = a_runner;
         rc = s_runner ();
      }
      break;
   case CASE_NORMAL     :
   case CASE_STRICT     :
      DEBUG_YEXEC   yLOG_note    ("processing a NORMAL/STRICT action");
      rc = yJOBS_act_check   (g_runas, g_runmode, a_oneline, g_runfile, a_assimilate);
      DEBUG_YEXEC   yLOG_value   ("check"     , rc);
      DEBUG_YEXEC   yLOG_char    ("g_norun"   , g_norun);
      IF_STRICT {
         if (rc < 0) {
            DEBUG_YEXEC   yLOG_note    ("strict mode must exit");
            DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
            return rce;
         }
      }
      DEBUG_YEXEC   yLOG_point   ("a_runner"  , a_runner);
      IF_NORUN  break;
      if (a_runner != NULL) {
         DEBUG_YEXEC   yLOG_note    ("running the executer");
         s_runner = a_runner;
         rc = s_runner ();
      }
      /* then, run in foreground                          */
      /*  damaged crontabs don't effect this one as they did not assimilate */
      break;
   default              :
      rc = rce;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return rc;
}
