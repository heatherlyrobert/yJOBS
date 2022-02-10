/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"




/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

static char yJOBS_ver [LEN_HUND] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yJOBS_version      (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yJOBS_ver, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yJOBS_ver;
}



/*====================------------------------------------====================*/
/*===----                      simple identification                   ----===*/
/*====================------------------------------------====================*/
static void      o___IDENTIFY________________o (void) {;};

char
yJOBS_runas             (char *a_runas, char *a_name)
{
   char        rce         =  -10;
   --rce;  if (a_name == NULL)  return rce;
   if (a_runas != NULL)  *a_runas = '-';
   if      (strcmp  (a_name, "eos_unit"                   ) == 0)    g_runas = IAM_UEOS;
   else if (strncmp (a_name, "eos"                    ,  3) == 0)    g_runas = IAM_EOS;
   else if (strncmp (a_name, "/sbin/eos"              ,  9) == 0)    g_runas = IAM_EOS;
   else if (strcmp  (a_name, "init"                       ) == 0)    g_runas = IAM_EOS;
   else if (strcmp  (a_name, "astraios_unit"              ) == 0)    g_runas = IAM_UASTRAIOS;
   else if (strncmp (a_name, "astraios"               ,  8) == 0)    g_runas = IAM_ASTRAIOS;
   else if (strncmp (a_name, "/sbin/astraios"         , 14) == 0)    g_runas = IAM_ASTRAIOS;
   else if (strcmp  (a_name, "shutdown"                   ) == 0)    g_runas = IAM_ASTRAIOS;
   else if (strcmp  (a_name, "halt"                       ) == 0)    g_runas = IAM_ASTRAIOS;
   else if (strcmp  (a_name, "restart"                    ) == 0)    g_runas = IAM_ASTRAIOS;
   else if (strcmp  (a_name, "hypnos_unit"                ) == 0)    g_runas = IAM_UHYPNOS;
   else if (strncmp (a_name, "hypnos"                 ,  6) == 0)    g_runas = IAM_HYPNOS;
   else if (strncmp (a_name, "/sbin/hypnos"           , 12) == 0)    g_runas = IAM_HYPNOS;
   else if (strcmp  (a_name, "heracles_unit"              ) == 0)    g_runas = IAM_UHERACLES;
   else if (strncmp (a_name, "heracles"               ,  8) == 0)    g_runas = IAM_HERACLES;
   else if (strncmp (a_name, "/sbin/heracles"         , 14) == 0)    g_runas = IAM_HERACLES;
   else if (strcmp  (a_name, "H"                          ) == 0)    g_runas = IAM_HERACLES;
   else if (strcmp  (a_name, "/sbin/H"                    ) == 0)    g_runas = IAM_HERACLES;
   else if (strcmp  (a_name, "khronos_unit"               ) == 0)    g_runas = IAM_UKHRONOS;
   else if (strncmp (a_name, "khronos"                ,  7) == 0)    g_runas = IAM_KHRONOS;
   else if (strncmp (a_name, "/sbin/khronos"          , 13) == 0)    g_runas = IAM_KHRONOS;
   else if (strcmp  (a_name, "cron"                       ) == 0)    g_runas = IAM_KHRONOS;
   else if (strcmp  (a_name, "crontab"                    ) == 0)    g_runas = IAM_KHRONOS;
   else if (strcmp  (a_name, "polymnia_unit"              ) == 0)    g_runas = IAM_UPOLYMNIA;
   else if (strncmp (a_name, "polymnia"               ,  7) == 0)    g_runas = IAM_POLYMNIA;
   else if (strcmp  (a_name, "/usr/local/bin/polymnia"    ) == 0)    g_runas = IAM_POLYMNIA;
   else {
      return -10;
   }
   if (a_runas != NULL)  *a_runas = g_runas;
   return 0;
}

char
yJOBS_iam               (char a_iam, char *a_print)
{
   char        rce         =  -10;
   --rce;  if (a_print == NULL)  return rce;
   switch (a_iam) {
   case IAM_EOS       : case IAM_UEOS      :
      strlcpy (a_print, "eos-rhododactylos (rosy-fingered dawn)" , LEN_HUND);
      break;
   case IAM_ASTRAIOS  : case IAM_UASTRAIOS :
      strlcpy (a_print, "astraios-aeolus (sparkling wind-father)", LEN_HUND);
      break;
   case IAM_HYPNOS    : case IAM_UHYPNOS   :
      strlcpy (a_print, "hypnos-epidotes (giver of sleep)"       , LEN_HUND);
      break;
   case IAM_HERACLES  : case IAM_UHERACLES :
      strlcpy (a_print, "heracles-promachus (leader in battle)"  , LEN_HUND);
      break;
   case IAM_KHRONOS   : case IAM_UKHRONOS  :
      strlcpy (a_print, "khronos-anileis (merciless time)"       , LEN_HUND);
      break;
   case IAM_POLYMNIA  : case IAM_UPOLYMNIA :
      strlcpy (a_print, "polymnia-hymnos (many praises)"         , LEN_HUND);
      break;
   default               :
      strlcpy (a_print, "unknown"                                , LEN_HUND);
      return -10;
      break;
   }
   return 0;
}

char
yJOBS_mode              (char a_mode, char *a_print)
{
   char        rce         =  -10;
   char        x_flag      =  '-';
   --rce;  if (a_print == NULL)  return rce;
   switch (a_mode) {
   case ACT_VERSION  :
      strcpy (a_print, "version");
      break;
   case ACT_HELP     :
      strcpy (a_print, "usage");
      break;
   case ACT_STATS    :
      strcpy (a_print, "stats");
      break;
   case CASE_VERIFY  :
      strcpy (a_print, "verify");
      break;
   case CASE_REGISTER:
      strcpy (a_print, "register");
      break;
   case CASE_INSTALL :
      strcpy (a_print, "install");
      break;
   case CASE_UPDATE  :
      strcpy (a_print, "update");
      break;
   case CASE_LIST    :
      strcpy (a_print, "list");
      break;
   case CASE_REPORT  :
      strcpy (a_print, "report");
      break;
   case CASE_CHECK   :
      strcpy (a_print, "check");
      break;
   case CASE_AUDIT   :
      strcpy (a_print, "audit");
      break;
   case CASE_FIX     :
      strcpy (a_print, "fix");
      break;
   case CASE_CLEAR   :
      strcpy (a_print, "clear");
      break;
   case CASE_WITHDRAW:
      strcpy (a_print, "withdraw");
      break;
   case CASE_REMOVE  :
      strcpy (a_print, "remove");
      break;
   case CASE_EXTRACT :
      strcpy (a_print, "extract");
      break;
   case CASE_DAEMON  :
      strcpy (a_print, "daemon");
      break;
   case CASE_PRICKLY :
      strcpy (a_print, "prickly");
      break;
   case CASE_NORMAL  :
      strcpy (a_print, "normal");
      break;
   case CASE_STRICT  :
      strcpy (a_print, "strict");
      break;
   case ACT_RELOAD   :
      strcpy (a_print, "reload");
      break;
   default           :
      strcpy (a_print, "unknown");
      x_flag = 'y';
      break;
   }
   IF_SILENT         strcat (a_print, " (silent)");
   else IF_CONFIRM   strcat (a_print, " (confirm)");
   else IF_VERBOSE   strcat (a_print, " (verbose)");
   else {
      strcat (a_print, " (unknown)");
      x_flag = 'y';
   }
   if (x_flag == 'y') return -10;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char          unit_answer [LEN_RECD];

char*            /*--> unit test accessor ------------------------------*/
yjobs_base__unit        (char *a_question)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "BASE             : question not understood", LEN_RECD);
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "mode"    )        == 0) {
      yJOBS_iam  (g_runas  , s);
      yJOBS_mode (g_runmode, t);
      snprintf (unit_answer, LEN_RECD, "BASE mode        : iam (%c) %-18.18s, run (%c) %-18.18s, å%sæ", g_runas, s, g_runmode, t, g_runfile);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_quiet       (void)
{
   yLOGS_begin ("yJOBS", YLOG_SYS, YLOG_QUIET);
   yURG_err_none ();
   yURG_msg_none ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_loud        (void)
{
   yLOGS_begin   ("yJOBS", YLOG_SYS, YLOG_NOISE);
   yURG_name     ("yjobs", YURG_ON);
   yURG_err_none ();
   yURG_msg_none ();
   DEBUG_YEXEC  yLOG_info     ("yJOBS"     , yJOBS_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yjobs__unit_end         (void)
{
   yLOGS_end     ();
   return 0;
}





