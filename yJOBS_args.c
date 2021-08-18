/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char          g_runas       = '-';
char          g_runmode     = '-';
char          g_runfile     [LEN_PATH]  = "";
char          g_norun       = '-';


char          g_silent      [LEN_LABEL] = "";
char          g_confirm     [LEN_LABEL] = "";
char          g_verbose     [LEN_LABEL] = "";

char          g_verify      [LEN_SHORT] = "";
char          g_install     [LEN_SHORT] = "";
char          g_list        [LEN_SHORT] = "";
char          g_check       [LEN_SHORT] = "";
char          g_audit       [LEN_SHORT] = "";
char          g_fix         [LEN_SHORT] = "";
char          g_remove      [LEN_SHORT] = "";
char          g_extract     [LEN_SHORT] = "";
char          g_daemon      [LEN_SHORT] = "";
char          g_prickly     [LEN_SHORT] = "";
char          g_normal      [LEN_SHORT] = "";

static char   s_print       [LEN_RECD]  = "";

#define     MAX_OPTS    35
typedef struct cOPTS  tOPTS;
struct cOPTS {
   char        option      [LEN_LABEL];
   char        levels      [LEN_SHORT];
   char        desc        [LEN_DESC];
   char        file        [LEN_TERSE];  /*  eos/ast/hyp  herc  khro  */
   char        run_as;
};
static const tOPTS   s_opts [MAX_OPTS] = {
   /*---(run as)-------------------------*/
   { "eos"      , "-��", "change to eos-mode"                           , "--�", IAM_EOS       },
   { "astraios" , "-��", "change to astraios-mode"                      , "--�", IAM_ASTRAIOS  },
   { "hypnos"   , "-��", "change to hypnos-mode"                        , "--�", IAM_HYPNOS    },
   { "heracles" , "-��", "change to heracles-mode"                      , "--�", IAM_HERACLES  },
   { "khronos"  , "-��", "change to khronos-mode"                       , "��-", IAM_KHRONOS   },
   /*---(unit testing)-------------------*/
   { "ueos"     , "-��", "change to unit testing eos-mode"              , "--�", IAM_UEOS      },
   { "uastraios", "-��", "change to unit testing astraios-mode"         , "--�", IAM_UASTRAIOS },
   { "uhypnos"  , "-��", "change to unit testing hypnos-mode"           , "--�", IAM_UHYPNOS   },
   { "uheracles", "-��", "change to unit testing heracles-mode"         , "--�", IAM_UHERACLES },
   { "ukhronos" , "-��", "change to unit testing khronos-mode"          , "��-", IAM_UKHRONOS  },
   /*---(actions)------------------------*/
   { "version"  , "1��", "present a short versioning string"            , "---", '�' },
   { "help"     , "2��", "present a simple help message"                , "---", '�' },
   { "verify"   , "v�V", "verify local file for correctness"            , "FFF", '�' },
   { "install"  , "i�I", "verify local file, then install centrally "   , "FFF", '�' },
   { "count"    , "l��", "count all user-applicable central files"      , "�--", '�' },
   { "list"     , "L��", "list all user-applicable central files"       , "�--", '�' },
   { "check"    , "c�C", "check central file for correctness"           , "-FF", '�' },
   { "audit"    , "a�A", "audit central environment and all its files"  , "---", '�' },
   { "fix"      , "f�F", "audit central environment and fix issues"     , "---", '�' },
   { "remove"   , "r�R", "remove file from central location"            , "�FF", '�' },
   { "extract"  , "e�E", "extract a central file to local copy"         , "�FF", '�' },
   { "daemon"   , "d�D", "execute specific file in daemon-mode"         , "��-", '�' },
   { "prickly"  , "p�P", "execute specific file in prickly daemon-mode" , "��-", '�' },
   { "normal"   , "n�N", "execute specific file in normal-mode"         , "---", '�' },
   { "reload"   , "H��", "send signal to reload daemon"                 , "��-", '�' },
   /*---(unit testing)-------------------*/
   { "norun"    , "-��", "daemons only load data"                       , "---", '�' },
   /*---(sentinal)-----------------------*/
   { ""         , "���", ""                                             , "���", '�' },
   /*---(done)---------------------------*/
};



/*====================------------------------------------====================*/
/*===----                      argument processing                     ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;};

char
yjobs_args__empty       (void)
{
   /*---(verbosity)----------------------*/
   strlcpy (g_silent , "", LEN_LABEL);
   strlcpy (g_confirm, "", LEN_LABEL);
   strlcpy (g_verbose, "", LEN_LABEL);
   /*---(usage)--------------------------*/
   strlcpy (g_verify , "", LEN_SHORT);
   strlcpy (g_install, "", LEN_SHORT);
   strlcpy (g_list   , "", LEN_SHORT);
   strlcpy (g_check  , "", LEN_SHORT);
   strlcpy (g_audit  , "", LEN_SHORT);
   strlcpy (g_fix    , "", LEN_SHORT);
   strlcpy (g_remove , "", LEN_SHORT);
   strlcpy (g_extract, "", LEN_SHORT);
   strlcpy (g_daemon , "", LEN_SHORT);
   strlcpy (g_prickly, "", LEN_SHORT);
   strlcpy (g_normal , "", LEN_SHORT);
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args__single      (char *a_levels, char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =  '�';
   char        t           [LEN_SHORT] = "";
   /*---(defense)------------------------*/
   --rce;  if (a_levels == NULL)              return rce;
   --rce;  if (strlen (a_levels) != 3)        return rce;
   --rce;  if (n        <  0)                 return rce;
   --rce;  if (n        >  2)                 return rce;
   /*---(get current)--------------------*/
   c = a_levels [n];
   if (c == '�')                      return 0;
   if (c == ' ')                      return 0;
   if (c == '-')                      return 0;
   /*---(can not be in any place)--------*/
   --rce;  if (strchr (g_silent , c) != NULL) return rce;
   --rce;  if (strchr (g_confirm, c) != NULL) return rce;
   --rce;  if (strchr (g_verbose, c) != NULL) return rce;
   /*---(load correctly)-----------------*/
   sprintf (t, "%c", c);
   switch (n) {
   case  0  :   strlcat (g_silent , t, LEN_LABEL);   break;
   case  1  :   strlcat (g_confirm, t, LEN_LABEL);   break;
   case  2  :   strlcat (g_verbose, t, LEN_LABEL);   break;
   }
   /*---(load by action)-----------------*/
   switch (a_levels [0]) {
   case 'v' :   strlcat (g_verify , t, LEN_SHORT);   break;
   case 'i' :   strlcat (g_install, t, LEN_SHORT);   break;
   case 'l' :   strlcat (g_list   , t, LEN_SHORT);   break;
   case 'L' :   strlcat (g_list   , t, LEN_SHORT);   break;
   case 'c' :   strlcat (g_check  , t, LEN_SHORT);   break;
   case 'a' :   strlcat (g_audit  , t, LEN_SHORT);   break;
   case 'f' :   strlcat (g_fix    , t, LEN_SHORT);   break;
   case 'r' :   strlcat (g_remove , t, LEN_SHORT);   break;
   case 'e' :   strlcat (g_extract, t, LEN_SHORT);   break;
   case 'd' :   strlcat (g_daemon , t, LEN_SHORT);   break;
   case 'p' :   strlcat (g_prickly, t, LEN_SHORT);   break;
   case 'n' :   strlcat (g_normal , t, LEN_SHORT);   break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yJOBS_args_init         (char a_runas, char a_runmode, char *a_runfile)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   char        c           =  '�';
   char        t           [LEN_SHORT] = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   yjobs_args__empty ();
   for (i = 0; i < MAX_OPTS; ++i) {
      p = s_opts [i].levels;
      if (p [0] == '\0')  break;
      if (rc >= 0)  rc = yjobs_args__single (p, 0);
      if (rc >= 0)  rc = yjobs_args__single (p, 1);
      if (rc >= 0)  rc = yjobs_args__single (p, 2);
      if (rc <  0)  break;
   }
   g_runas   = a_runas;
   g_runmode = a_runmode;
   g_norun   = '-';
   if (a_runfile != NULL) strcpy (g_runfile, a_runfile);
   else                   strcpy (g_runfile, "");
   DEBUG_PROG  yLOG_info    ("g_silent"  , g_silent);
   DEBUG_PROG  yLOG_info    ("g_confirm" , g_confirm);
   DEBUG_PROG  yLOG_info    ("g_verbose" , g_verbose);
   DEBUG_PROG  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_args__clearmode   (char *a_runas, char *a_runmode, char *a_runfile)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_runas   == NULL)  return rce;
   --rce;  if (a_runmode == NULL)  return rce;
   --rce;  if (a_runfile == NULL)  return rce;
   /*---(defaults)-----------------------*/
   g_runas = *a_runas;
   *a_runmode = g_runmode = '-';
   strlcpy (a_runfile, "", LEN_PATH);
   strlcpy (g_runfile, "", LEN_PATH);
   /*---(complete)-----------------------*/
   return 0;
}

char
yJOBS_args_handle       (char *a_runas, char *a_runmode, char *a_runfile, int *i, char *a_arg, char *a_next)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         j           =    0;
   char       *p           = NULL;
   char        c           =  '�';
   char        f           =  '�';
   /*---(pointer defense)----------------*/
   --rce;  if (a_runmode == NULL)  return rce;
   --rce;  if (a_runfile == NULL)  return rce;
   --rce;  if (i         == NULL)  return rce;
   --rce;  if (a_arg     == NULL)  return rce;
   /*---(check reload)-------------------*/
   if (strcmp (g_silent, "") == 0) {
      rc = yJOBS_args_init (*a_runas, *a_runmode, a_runfile);
   }
   /*---(value defense)------------------*/
   --rce;  if (strlen (a_arg) <= 4) {
      yURG_err ('F', "option �%s� too short, must be > 4 chars", a_arg);
      return rce;
   }
   --rce;  if (strncmp (a_arg, "--", 2) != 0) {
      yURG_err ('F', "option �%s� must start with the prefix �--�", a_arg);
      return rce;
   }
   --rce;  if (*a_runmode != '-') {
      yURG_err ('F', "run action already set (%c), can not update to �%s�", *a_runmode, a_arg);
      return rce;
   }
   /*---(unit testing stuff)-------------*/
   if (strcmp (a_arg, "--norun") == 0) {
      g_norun = 'y';
      return 1;
   }
   /*---(walk options)-------------------*/
   for (j = 0; j < MAX_OPTS; ++j) {
      p = s_opts [j].option;
      if (p [0] == '\0')  break;
      if (strcmp (a_arg + 2, p) == 0) {
         c = s_opts [j].levels [0];
         break;
      }
      if (a_arg [2] == 'c' && strcmp (a_arg + 3, p) == 0) {
         c = s_opts [j].levels [1];
         break;
      }
      if (a_arg [2] == 'v' && strcmp (a_arg + 3, p) == 0) {
         c = s_opts [j].levels [2];
         break;
      }
   }
   /*---(handle failure)-----------------*/
   --rce;  if (c == '�') {
      yURG_err ('F', "option �%s� not found in database", a_arg);
      return rce;
   }
   /*---(handle runas changes)-----------*/
   --rce;  if (c == '-') {
      if (s_opts [j].run_as == '�') {
         yURG_err ('F', "option �%s� used as a mode change, but not legal", a_arg);
         return rce;
      }
      /*---(get file flag)------------------*/
      switch (*a_runas) {
      case IAM_EOS       : case IAM_UEOS      :
      case IAM_ASTRAIOS  : case IAM_UASTRAIOS :
      case IAM_HYPNOS    : case IAM_UHYPNOS   :
         f = s_opts [j].file [0];
         break;
      case IAM_HERACLES  : case IAM_UHERACLES :
         f = s_opts [j].file [1];
         break;
      case IAM_KHRONOS   : case IAM_UKHRONOS  :
         f = s_opts [j].file [2];
         break;
      }
      if (f == '�') {
         yURG_err ('F', "can not change from �%c� mode using �%s�", *a_runas, a_arg);
         return rce;
      }
      *a_runas = g_runas = s_opts [j].run_as;
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      return 2;
   }
   /*---(handle run mode changes)--------*/
   *a_runmode = g_runmode = c;
   /*---(get file flag)------------------*/
   switch (*a_runas) {
   case IAM_EOS       : case IAM_UEOS      :
   case IAM_ASTRAIOS  : case IAM_UASTRAIOS :
   case IAM_HYPNOS    : case IAM_UHYPNOS   :
      f = s_opts [j].file [0];
      break;
   case IAM_HERACLES  : case IAM_UHERACLES :
      f = s_opts [j].file [1];
      break;
   case IAM_KHRONOS   : case IAM_UKHRONOS  :
      f = s_opts [j].file [2];
      break;
   }
   /*---(handle option not allowed)------*/
   --rce;  if (f == '�') {
      yURG_err ('F', "action �%s� not allowed for run-as (%c)", a_arg, *a_runas);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      return rce;
   }
   /*---(handle simple option)-----------*/
   if (f == '-') {
      if (strchr (IAM_ETC, *a_runas) != NULL) {
         IF_CHECK {
            switch (*a_runas) {
            case IAM_EOS       : case IAM_UEOS      :
               strlcpy (a_runfile, "eos.conf", LEN_PATH);
               strlcpy (g_runfile, "eos.conf", LEN_PATH);
               break;
            case IAM_ASTRAIOS  : case IAM_UASTRAIOS :
               strlcpy (a_runfile, "astraios.conf", LEN_PATH);
               strlcpy (g_runfile, "astraios.conf", LEN_PATH);
               break;
            case IAM_HYPNOS    : case IAM_UHYPNOS   :
               strlcpy (a_runfile, "hypnos.conf", LEN_PATH);
               strlcpy (g_runfile, "hypnos.conf", LEN_PATH);
               break;
            }
         }
      }
      return 0;
   }
   /*---(handle file flag)---------------*/
   --rce;  if (f != 'F') {
      yURG_err ('F', "action �%s� not configured correctly", a_arg);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      return rce;
   }
   --rce;  if (a_next == NULL) {
      yURG_err ('F', "action �%s� requires a file name as an argument", a_arg);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      return rce;
   }
   strlcpy (a_runfile, a_next, LEN_PATH);
   strlcpy (g_runfile, a_next, LEN_PATH);
   ++(*i);
   /*---(complete)-----------------------*/
   return 1;
}

char
yJOBS_final             (int a_uid)
{
   char        rce         =  -10;
   /*---(setup location)-----------------*/
   if (strchr (IAM_UNIT, g_runas) != NULL) {
      DEBUG_INPT  yLOG_note    ("unit testing, run output and errors to tmp file");
      yURG_msg_tmp  ();
      yURG_err_tmp  (); 
   } else {
      DEBUG_INPT  yLOG_note    ("normal, run output and errors to stdout, strerr");
      yURG_msg_std  ();
      yURG_err_std  ();
   }
   /*---(setup verbosity)----------------*/
   IF_SILENT {
      DEBUG_INPT  yLOG_note    ("silent, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_CONFIRM {
      DEBUG_INPT  yLOG_note    ("confirm, muting output and errors until summary");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_VERBOSE {
      DEBUG_INPT  yLOG_note    ("verbose, turning on all output and errors");
      yURG_msg_live ();
      yURG_err_live ();
   }
   else {
      DEBUG_INPT  yLOG_note    ("unknown, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   /*---(check security for all)---------*/
   --rce;  if (a_uid != 0) {
      IF_AUDIT {
         DEBUG_INPT  yLOG_note    ("audit, caudit, and vaudit require root privlege");
         yURG_err ('F', "--audit, --caudit, and --vaudit require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_FIX   {
         DEBUG_INPT  yLOG_note    ("fix, cfix, and vfix require root privlege");
         yURG_err ('F', "--fix, --cfix, and --vfix require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_DAEMON {
         DEBUG_INPT  yLOG_note    ("daemon, cdaemon, and vdaemon require root privlege");
         yURG_err ('F', "--daemon, --cdaemon, and --vdaemon require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_PRICKLY {
         DEBUG_INPT  yLOG_note    ("prickly, cprickly, and vprickly require root privlege");
         yURG_err ('F', "--prickly, --cprickly, and --vprickly require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_NORMAL  {
         DEBUG_INPT  yLOG_note    ("normal, cnormal, and vnormal require root privlege");
         yURG_err ('F', "--normal, --cnormal, and --vnormal require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (g_runmode == ACT_RELOAD)  {
         DEBUG_INPT  yLOG_note    ("reload require root privlege");
         yURG_err ('F', "--reload requires root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check security for /etc apps)---*/
   --rce;  if (a_uid != 0 && strchr (IAM_ETC, g_runas) != NULL) {
      IF_INSTALL {
         DEBUG_INPT  yLOG_note    ("install, cinstall, and vinstall require root privlege");
         yURG_err ('F', "--install, --cinstall, and --vinstall require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_CHECK   {
         DEBUG_INPT  yLOG_note    ("check, ccheck, and vcheck require root privlege");
         yURG_err ('F', "--check, --ccheck, and --vcheck require root privlege");
         DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      simple short-cuts                       ----===*/
/*====================------------------------------------====================*/
static void      o___SHORTCUT________________o (void) {;};

CHECK  char  yJOBS_ifsilent  (void) { if (strchr (g_silent , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifverbose (void) { if (strchr (g_verbose, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifconfirm (void) { if (strchr (g_confirm, g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifhelp    (void) { if (g_runmode == ACT_HELP)                  return 1; else return 0; }
CHECK  char  yJOBS_ifversion (void) { if (g_runmode == ACT_VERSION)               return 1; else return 0; }
CHECK  char  yJOBS_ifverify  (void) { if (strchr (g_verify , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifinstall (void) { if (strchr (g_install, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_iflist    (void) { if (strchr (g_list   , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifcheck   (void) { if (strchr (g_check  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifaudit   (void) { if (strchr (g_audit  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_iffix     (void) { if (strchr (g_fix    , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifremove  (void) { if (strchr (g_remove , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifextract (void) { if (strchr (g_extract, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifdaemon  (void) { if (strchr (g_daemon , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifprickly (void) { if (strchr (g_prickly, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifnormal  (void) { if (strchr (g_normal , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifnorun   (void) { if (g_norun != 'y')                         return 1; else return 0; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*            /*--> unit test accessor ------------------------------*/
yjobs_args__unit        (char *a_question)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "ARGS             : question not understood", LEN_RECD);
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "args"          )  == 0) {
      sprintf (s, "%2d�%.15s�", strlen (g_silent) , g_silent);
      sprintf (t, "%2d�%.15s�", strlen (g_confirm), g_confirm);
      sprintf (u, "%2d�%.15s�", strlen (g_verbose), g_verbose);
      snprintf (unit_answer, LEN_HUND, "ARGS args        : %-20.20s  %-20.20s  %s", s, t, u);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

