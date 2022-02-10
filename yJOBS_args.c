/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char          g_runas       = '-';
char          g_runmode     = '-';
char          g_runfile     [LEN_PATH]  = "";
char          g_norun       = '-';
char          g_noend       = '-';


char          g_silent      [LEN_LABEL] = "";
char          g_confirm     [LEN_LABEL] = "";
char          g_verbose     [LEN_LABEL] = "";

/*---(incomming)------------*/
char          g_verify      [LEN_SHORT] = "";
char          g_register    [LEN_SHORT] = "";
char          g_install     [LEN_SHORT] = "";
char          g_update      [LEN_SHORT] = "";
/*---(central)--------------*/
char          g_list        [LEN_SHORT] = "";
char          g_check       [LEN_SHORT] = "";
char          g_audit       [LEN_SHORT] = "";
char          g_fix         [LEN_SHORT] = "";
/*---(outgoing)-------------*/
char          g_withdraw    [LEN_SHORT] = "";
char          g_clear       [LEN_SHORT] = "";
char          g_remove      [LEN_SHORT] = "";
char          g_extract     [LEN_SHORT] = "";
/*---(execution)------------*/
char          g_daemon      [LEN_SHORT] = "";
char          g_prickly     [LEN_SHORT] = "";
char          g_normal      [LEN_SHORT] = "";
char          g_strict      [LEN_SHORT] = "";

static char   s_print       [LEN_RECD]  = "";

#define     MAX_OPTS    45
typedef struct cOPTS  tOPTS;
struct cOPTS {
   char        option      [LEN_LABEL];
   char        levels      [LEN_SHORT];
   char        desc        [LEN_DESC];
   char        file        [LEN_TERSE];  /*  eos/ast/hyp  herc  khro  poly */
   char        run_as;
};
static const tOPTS   s_opts [MAX_OPTS] = {
   /*---(run as)-------------------------*/
   { "eos"      , "-··", "change to eos-mode"                           , "--··", IAM_EOS       },
   { "astraios" , "-··", "change to astraios-mode"                      , "--··", IAM_ASTRAIOS  },
   { "hypnos"   , "-··", "change to hypnos-mode"                        , "--··", IAM_HYPNOS    },
   { "heracles" , "-··", "change to heracles-mode"                      , "--··", IAM_HERACLES  },
   { "khronos"  , "-··", "change to khronos-mode"                       , "··-·", IAM_KHRONOS   },
   { "polymnia" , "-··", "change to polymnia-mode"                      , "···-", IAM_POLYMNIA  },
   /*---(unit testing)-------------------*/
   { "ueos"     , "-··", "change to unit testing eos-mode"              , "--··", IAM_UEOS      },
   { "uastraios", "-··", "change to unit testing astraios-mode"         , "--··", IAM_UASTRAIOS },
   { "uhypnos"  , "-··", "change to unit testing hypnos-mode"           , "--··", IAM_UHYPNOS   },
   { "uheracles", "-··", "change to unit testing heracles-mode"         , "--··", IAM_UHERACLES },
   { "ukhronos" , "-··", "change to unit testing khronos-mode"          , "··-·", IAM_UKHRONOS  },
   { "upolymnia", "-··", "change to unit testing polymnia-mode"         , "···-", IAM_UPOLYMNIA },
   /*---(information)--------------------*/
   { "version"  , "1··", "present a short versioning string"            , "---·", '·' },
   { "help"     , "2··", "present a simple help message"                , "---·", '·' },
   { "stats"    , "3··", "give basic information about database"        , "----", '·' },
   /*---(upward)-------------------------*/
   { "verify"   , "vÿV", "verify local file for correctness"            , "FFF-", '·' },
   { "register" , "béB", "verify local file and register centrally"     , "···-", '·' },
   { "install"  , "iðI", "verify local file, then install centrally"    , "FFF-", '·' },
   { "update"   , "uûU", "update central with single file"              , "···-", '·' },
   /*---(central)------------------------*/
   { "count"    , "l··", "count all user-applicable central files"      , "·--·", '·' },
   { "list"     , "L··", "list all user-applicable central files"       , "·--·", '·' },
   { "report"   , "?··", "report on central database"                   , "···F", '·' },
   { "check"    , "cýC", "check central file for correctness"           , "-FF-", '·' },
   { "audit"    , "aèA", "audit central environment and all its files"  , "----", '·' },
   { "fix"      , "füF", "audit central environment and fix issues"     , "----", '·' },
   /*---(elsewhere)----------------------*/
   { "upload"   , "···", "from central to elsewhere"                    , "····", '·' },
   { "download" , "···", "to central from elsewhere"                    , "····", '·' },
   /*---(downward)-----------------------*/
   { "withdraw" , "qþQ", "unregister centrally"                         , "···F", '·' },
   { "clear"    , "xõX", "clear file from central location"             , "···F", '·' },
   { "remove"   , "røR", "remove file from central location"            , "·FFF", '·' },
   { "extract"  , "eìE", "extract a central file to local copy"         , "·FF·", '·' },
   /*---(execution)----------------------*/
   { "daemon"   , "dëD", "execute specific file in daemon-mode"         , "··-·", '·' },
   { "prickly"  , "p÷P", "execute specific file in prickly daemon-mode" , "··-·", '·' },
   { "normal"   , "nôN", "execute specific file in normal-mode"         , "----", '·' },
   { "strict"   , "sùS", "execute specific file in strict normal-mode"  , "----", '·' },
   { "reload"   , "H··", "send signal to reload daemon"                 , "··-·", '·' },
   /*---(unit testing)-------------------*/
   { "norun"    , "-··", "daemons only load data"                       , "---·", '·' },
   /*---(sentinal)-----------------------*/
   { ""         , "···", ""                                             , "····", '·' },
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
   strlcpy (g_silent  , "", LEN_LABEL);
   strlcpy (g_confirm , "", LEN_LABEL);
   strlcpy (g_verbose , "", LEN_LABEL);
   /*---(incomming)----------------------*/
   strlcpy (g_verify  , "", LEN_SHORT);
   strlcpy (g_register, "", LEN_SHORT);
   strlcpy (g_install , "", LEN_SHORT);
   strlcpy (g_update  , "", LEN_SHORT);
   /*---(central)------------------------*/
   strlcpy (g_list    , "", LEN_SHORT);
   strlcpy (g_check   , "", LEN_SHORT);
   strlcpy (g_audit   , "", LEN_SHORT);
   strlcpy (g_fix     , "", LEN_SHORT);
   /*---(outgoing)-----------------------*/
   strlcpy (g_clear   , "", LEN_SHORT);
   strlcpy (g_withdraw, "", LEN_SHORT);
   strlcpy (g_remove  , "", LEN_SHORT);
   strlcpy (g_extract , "", LEN_SHORT);
   /*---(execution)----------------------*/
   strlcpy (g_daemon  , "", LEN_SHORT);
   strlcpy (g_prickly , "", LEN_SHORT);
   strlcpy (g_normal  , "", LEN_SHORT);
   strlcpy (g_strict  , "", LEN_SHORT);
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args__single      (char *a_levels, char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =  '·';
   char        t           [LEN_SHORT] = "";
   /*---(defense)------------------------*/
   --rce;  if (a_levels == NULL)              return rce;
   --rce;  if (strlen (a_levels) != 3)        return rce;
   --rce;  if (n        <  0)                 return rce;
   --rce;  if (n        >  2)                 return rce;
   /*---(get current)--------------------*/
   c = a_levels [n];
   if (c == '·')                      return 0;
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
   case 'v' :   strlcat (g_verify  , t, LEN_SHORT);   break;
   case 'b' :   strlcat (g_register, t, LEN_SHORT);   break;
   case 'i' :   strlcat (g_install , t, LEN_SHORT);   break;
   case 'u' :   strlcat (g_update  , t, LEN_SHORT);   break;
   case 'l' :   strlcat (g_list    , t, LEN_SHORT);   break;
   case 'L' :   strlcat (g_list    , t, LEN_SHORT);   break;
   case 'c' :   strlcat (g_check   , t, LEN_SHORT);   break;
   case 'a' :   strlcat (g_audit   , t, LEN_SHORT);   break;
   case 'f' :   strlcat (g_fix     , t, LEN_SHORT);   break;
   case 'x' :   strlcat (g_clear   , t, LEN_SHORT);   break;
   case 'q' :   strlcat (g_withdraw, t, LEN_SHORT);   break;
   case 'r' :   strlcat (g_remove  , t, LEN_SHORT);   break;
   case 'e' :   strlcat (g_extract , t, LEN_SHORT);   break;
   case 'd' :   strlcat (g_daemon  , t, LEN_SHORT);   break;
   case 'p' :   strlcat (g_prickly , t, LEN_SHORT);   break;
   case 'n' :   strlcat (g_normal  , t, LEN_SHORT);   break;
   case 's' :   strlcat (g_strict  , t, LEN_SHORT);   break;
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
   char        c           =  '·';
   char        t           [LEN_SHORT] = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
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
   g_noend   = '-';
   if (a_runfile != NULL) strcpy (g_runfile, a_runfile);
   else                   strcpy (g_runfile, "");
   DEBUG_YEXEC  yLOG_info    ("g_silent"  , g_silent);
   DEBUG_YEXEC  yLOG_info    ("g_confirm" , g_confirm);
   DEBUG_YEXEC  yLOG_info    ("g_verbose" , g_verbose);
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
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
   char        c           =  '·';
   char        f           =  '·';
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(pointer defense)----------------*/
   DEBUG_YEXEC  yLOG_point   ("a_runmode" , a_runmode);
   --rce;  if (a_runmode == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_runfile" , a_runfile);
   --rce;  if (a_runfile == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("i"         , i);
   --rce;  if (i         == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_arg"     , a_arg);
   --rce;  if (a_arg     == NULL) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(check reload)-------------------*/
   if (strcmp (g_silent, "") == 0) {
      DEBUG_YEXEC  yLOG_note    ("first run, will call init");
      rc = yJOBS_args_init (*a_runas, *a_runmode, a_runfile);
   }
   /*---(unit testing stuff)-------------*/
   if (strcmp (a_arg, "--norun") == 0) {
      g_norun = 'y';
      DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(value defense)------------------*/
   DEBUG_YEXEC  yLOG_value   ("len"       , strlen (a_arg));
   --rce;  if (strlen (a_arg) <= 4) {
      yURG_err ('F', "option å%sæ too short, must be > 4 chars", a_arg);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (strncmp (a_arg, "--", 2) != 0) {
      yURG_err ('F', "option å%sæ must start with the prefix å--æ", a_arg);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (*a_runmode != '-') {
      yURG_err ('F', "run action already set (%c), can not update to å%sæ", *a_runmode, a_arg);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(walk options)-------------------*/
   for (j = 0; j < MAX_OPTS; ++j) {
      p = s_opts [j].option;
      if (p [0] == '\0')  break;
      if (strcmp (a_arg + 2, p) == 0) {
         DEBUG_YEXEC  yLOG_note    ("found silent option");
         c = s_opts [j].levels [0];
         break;
      }
      if (a_arg [2] == 'c' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YEXEC  yLOG_note    ("found confirm option");
         c = s_opts [j].levels [1];
         break;
      }
      if (a_arg [2] == 'v' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YEXEC  yLOG_note    ("found verbose option");
         c = s_opts [j].levels [2];
         break;
      }
   }
   /*---(handle failure)-----------------*/
   --rce;  if (c == '·') {
      yURG_err ('F', "option å%sæ not found in database", a_arg);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(handle runas changes)-----------*/
   --rce;  if (c == '-') {
      if (s_opts [j].run_as == '·') {
         yURG_err ('F', "option å%sæ used as a mode change, but not legal", a_arg);
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
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
      case IAM_POLYMNIA  : case IAM_UPOLYMNIA :
         f = s_opts [j].file [3];
         break;
      }
      if (f == '·') {
         yURG_err ('F', "can not change from å%cæ mode using å%sæ", *a_runas, a_arg);
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
         return rce;
      }
      *a_runas = g_runas = s_opts [j].run_as;
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
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
   case IAM_POLYMNIA  : case IAM_UPOLYMNIA :
      f = s_opts [j].file [3];
      break;
   }
   /*---(handle option not allowed)------*/
   --rce;  if (f == '·') {
      yURG_err ('F', "action å%sæ not allowed for run-as (%c)", a_arg, *a_runas);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(handle simple option)-----------*/
   if (f == '-') {
      if (strchr (IAM_ETC, *a_runas) != NULL) {
         IF_CENTRAL {
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
      DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle file flag)---------------*/
   --rce;  if (f != 'F') {
      yURG_err ('F', "action å%sæ not configured correctly", a_arg);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (a_next == NULL) {
      yURG_err ('F', "action å%sæ requires a file name as an argument", a_arg);
      yjobs_args__clearmode (a_runas, a_runmode, a_runfile);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   strlcpy (a_runfile, a_next, LEN_PATH);
   strlcpy (g_runfile, a_next, LEN_PATH);
   ++(*i);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yJOBS_final             (int a_uid)
{
   char        rce         =  -10;
   /*---(setup location)-----------------*/
   if (strchr (IAM_UNIT, g_runas) != NULL) {
      DEBUG_YEXEC  yLOG_note    ("unit testing, run output and errors to tmp file");
      yURG_msg_tmp  ();
      yURG_err_tmp  (); 
   } else {
      DEBUG_YEXEC  yLOG_note    ("normal, run output and errors to stdout, strerr");
      yURG_msg_std  ();
      yURG_err_std  ();
   }
   /*---(check for illegal)--------------*/
   --rce;  if (g_runas == '-' || g_runmode == '-') {
      yURG_msg_mute ();
      yURG_err_mute ();
      return rce;
   }
   /*---(setup verbosity)----------------*/
   IF_SILENT {
      DEBUG_YEXEC  yLOG_note    ("silent, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_CONFIRM {
      DEBUG_YEXEC  yLOG_note    ("confirm, muting output and errors until summary");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_VERBOSE {
      DEBUG_YEXEC  yLOG_note    ("verbose, turning on all output and errors");
      yURG_msg_live ();
      yURG_err_live ();
   }
   else {
      DEBUG_YEXEC  yLOG_note    ("unknown, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   /*---(check security for all)---------*/
   --rce;  if (a_uid != 0) {
      IF_AUDIT {
         DEBUG_YEXEC  yLOG_note    ("audit, caudit, and vaudit require root privlege");
         yURG_err ('F', "--audit, --caudit, and --vaudit require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_FIX   {
         DEBUG_YEXEC  yLOG_note    ("fix, cfix, and vfix require root privlege");
         yURG_err ('F', "--fix, --cfix, and --vfix require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_DAEMON {
         DEBUG_YEXEC  yLOG_note    ("daemon, cdaemon, and vdaemon require root privlege");
         yURG_err ('F', "--daemon, --cdaemon, and --vdaemon require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_PRICKLY {
         DEBUG_YEXEC  yLOG_note    ("prickly, cprickly, and vprickly require root privlege");
         yURG_err ('F', "--prickly, --cprickly, and --vprickly require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_NORMAL  {
         DEBUG_YEXEC  yLOG_note    ("normal, cnormal, and vnormal require root privlege");
         yURG_err ('F', "--normal, --cnormal, and --vnormal require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_STRICT  {
         DEBUG_YEXEC  yLOG_note    ("strict, cnormal, and vnormal require root privlege");
         yURG_err ('F', "--strict, --cstrict, and --vstrict require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (g_runmode == ACT_RELOAD)  {
         DEBUG_YEXEC  yLOG_note    ("reload require root privlege");
         yURG_err ('F', "--reload requires root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check security for /etc apps)---*/
   --rce;  if (a_uid != 0 && strchr (IAM_ETC, g_runas) != NULL) {
      IF_INSTALL {
         DEBUG_YEXEC  yLOG_note    ("install, cinstall, and vinstall require root privlege");
         yURG_err ('F', "--install, --cinstall, and --vinstall require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_CHECK   {
         DEBUG_YEXEC  yLOG_note    ("check, ccheck, and vcheck require root privlege");
         yURG_err ('F', "--check, --ccheck, and --vcheck require root privlege");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
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

CHECK  char  yJOBS_ifsilent   (void) { if (strchr (g_silent  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifverbose  (void) { if (strchr (g_verbose , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifconfirm  (void) { if (strchr (g_confirm , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifhelp     (void) { if (g_runmode == ACT_HELP)                  return 1; else return 0; }
CHECK  char  yJOBS_ifversion  (void) { if (g_runmode == ACT_VERSION)               return 1; else return 0; }
CHECK  char  yJOBS_ifstats    (void) { if (g_runmode == ACT_STATS)                 return 1; else return 0; }

CHECK  char  yJOBS_ifverify   (void) { if (strchr (g_verify  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifregister (void) { if (strchr (g_register, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifinstall  (void) { if (strchr (g_install , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifupdate   (void) { if (strchr (g_update  , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_iflist     (void) { if (strchr (g_list    , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifcheck    (void) { if (strchr (g_check   , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifaudit    (void) { if (strchr (g_audit   , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_iffix      (void) { if (strchr (g_fix     , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifwithdraw (void) { if (strchr (g_withdraw, g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifclear    (void) { if (strchr (g_clear   , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifremove   (void) { if (strchr (g_remove  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifextract  (void) { if (strchr (g_extract , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifdaemon   (void) { if (strchr (g_daemon  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifprickly  (void) { if (strchr (g_prickly , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifnormal   (void) { if (strchr (g_normal  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifstrict   (void) { if (strchr (g_strict  , g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifnorun    (void) { if (g_norun == 'y')                         return 1; else return 0; }
CHECK  char  yJOBS_ifnoend    (void) { if (g_noend == 'y')                         return 1; else return 0; }



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
   strncpy  (unit_answer, "ARGS             : question ot understood", LEN_RECD);
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "args"          )  == 0) {
      sprintf (s, "%2då%.22sæ", strlen (g_silent) , g_silent);
      sprintf (t, "%2då%.16sæ", strlen (g_confirm), g_confirm);
      sprintf (u, "%2då%.16sæ", strlen (g_verbose), g_verbose);
      snprintf (unit_answer, LEN_HUND, "ARGS args        : %-26.26s  %-21.21s  %s", s, t, u);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

