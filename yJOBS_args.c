/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char          g_runas       = '-';
char          g_runmode     = '-';
char          g_runfile     [LEN_PATH]  = "";
char          g_oneline     [LEN_HUND]  = "";
char          g_norun       = '-';
char          g_noend       = '-';


/*---(validity)-------------*/
char          g_local       [LEN_DESC]  = "";
char          g_central     [LEN_DESC]  = "";
/*---(validity)-------------*/
char          g_valid       [LEN_DESC]  = "";
char          g_unit        [LEN_DESC]  = "";
char          g_etc         [LEN_DESC]  = "";
/*---(verbosity)------------*/
char          g_silent      [LEN_DESC]  = "";
char          g_confirm     [LEN_DESC]  = "";
char          g_verbose     [LEN_DESC]  = "";
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
/*---(transfer)-------------*/
char          g_upload      [LEN_SHORT] = "";
char          g_download    [LEN_SHORT] = "";
/*---(execution)------------*/
char          g_gather      [LEN_SHORT] = "";
char          g_daemon      [LEN_SHORT] = "";
char          g_prickly     [LEN_SHORT] = "";
char          g_normal      [LEN_SHORT] = "";
char          g_strict      [LEN_SHORT] = "";
char          g_reload      [LEN_SHORT] = "";




#define     MAX_OPTS    60
typedef struct cOPTS  tOPTS;
struct cOPTS {
   char        option      [LEN_LABEL];
   char        levels      [LEN_SHORT];
   char        desc        [LEN_DESC];
   char        offset;
   char        where;
};
static const tOPTS   s_opts [MAX_OPTS] = {
   /*---(information)--------------------*/
   { "version"  , "1··", "present a short versioning string"            ,   0, YJOBS_NEITHER  },
   { "help"     , "2··", "present a simple help message"                ,   1, YJOBS_NEITHER  },
   { "stats"    , "3··", "give basic information about database"        ,   2, YJOBS_NEITHER  },
   /*---(upward)-------------------------*/
   { "verify"   , "vÑV", "verify local file for correctness"            ,   4, YJOBS_LOCAL    },
   { "register" , "béB", "verify local file and register centrally"     ,   5, YJOBS_LOCAL    },
   { "update"   , "uûU", "update central with single file"              ,   6, YJOBS_LOCAL    },
   { "install"  , "iðI", "verify local file, then install centrally"    ,   7, YJOBS_LOCAL    },
   /*---(central)------------------------*/
   { "count"    , "l··", "count all user-applicable central files"      ,   9, YJOBS_CENTRAL  },
   { "list"     , "L··", "list all user-applicable central files"       ,  10, YJOBS_CENTRAL  },
   { "report"   , "ò··", "report on central database"                   ,  11, YJOBS_CENTRAL  },
   { "check"    , "cýC", "check central file for correctness"           ,  12, YJOBS_CENTRAL  },
   { "audit"    , "aèA", "audit central environment and all its files"  ,  13, YJOBS_CENTRAL  },
   { "fix"      , "füF", "audit central environment and fix issues"     ,  14, YJOBS_CENTRAL  },
   /*---(epic)---------------------------*/
   { "backup"   , "kñK", "backup the central system"                    ,  16, YJOBS_CENTRAL  },
   { "restore"  , "túT", "restore the central system from backup"       ,  17, YJOBS_CENTRAL  },
   { "purge"    , "wÿW", "wipe clean entire central system"             ,  18, YJOBS_CENTRAL  },
   /*---(elsewhere)----------------------*/
   { "upload"   , "yïY", "from elsewhere to central"                    ,  20, YJOBS_CENTRAL  },
   { "download" , "zíZ", "from central to elsewhere"                    ,  21, YJOBS_CENTRAL  },
   /*---(downward)-----------------------*/
   { "withdraw" , "qþQ", "unregister centrally"                         ,  23, YJOBS_CENTRAL  },
   { "clear"    , "xõX", "clear file from central location"             ,  24, YJOBS_CENTRAL  },
   { "remove"   , "røR", "remove file from central location"            ,  25, YJOBS_CENTRAL  },
   { "extract"  , "eìE", "extract a central file to local copy"         ,  26, YJOBS_CENTRAL  },
   /*---(execution)----------------------*/
   { "gather"   , "gêG", "execute system-wide data gather"              ,  28, YJOBS_NEITHER  },
   { "daemon"   , "dëD", "execute specific file in daemon-mode"         ,  29, YJOBS_NEITHER  },
   { "prickly"  , "p÷P", "execute specific file in prickly daemon-mode" ,  30, YJOBS_NEITHER  },
   { "normal"   , "nôN", "execute specific file in normal-mode"         ,  31, YJOBS_NEITHER  },
   { "strict"   , "sùS", "execute specific file in strict normal-mode"  ,  32, YJOBS_NEITHER  },
   { "reload"   , "hîH", "send signal to reload daemon"                 ,  33, YJOBS_NEITHER  },
   /*---(unit testing)-------------------*/
   { "testing"  , "j··", "change to test directories"                   ,  35, YJOBS_NEITHER  },
   { "norun"    , "-··", "daemons only load data"                       ,   0, YJOBS_NEITHER  },
   /*---(sentinal)-----------------------*/
   { ""         , "···", ""                                             ,   0, YJOBS_NEITHER  },
   /*---(done)---------------------------*/
};



/*====================------------------------------------====================*/
/*===----                      argument processing                     ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;};

char
yjobs_args_info         (char a_mode, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_mode == 0 || a_mode == '-' || a_mode == '·') {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk options)-------------------*/
   for (i = 0; i < MAX_OPTS; ++i) {
      if (strcmp (s_opts [i].option, "") == 0)  break;
      DEBUG_YJOBS  yLOG_complex ("current"   , "%2d, %s, %s", i, s_opts [i].levels, s_opts [i].option);
      if (strchr (s_opts [i].levels, a_mode) != NULL) {
         strlcpy (a_name, s_opts [i].option, LEN_LABEL);
         DEBUG_YJOBS  yLOG_info    ("option"    , a_name);
         DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(fall-out)-----------------------*/
   --rce;
   DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char
yjobs_args__empty       (void)
{
   /*---(location)-----------------------*/
   strlcpy (g_local   , "", LEN_DESC);
   strlcpy (g_central , "", LEN_DESC);
   /*---(validity)-----------------------*/
   strlcpy (g_valid   , "", LEN_DESC);
   strlcpy (g_unit    , "", LEN_DESC);
   strlcpy (g_etc     , "", LEN_DESC);
   /*---(verbosity)----------------------*/
   strlcpy (g_silent  , "", LEN_DESC);
   strlcpy (g_confirm , "", LEN_DESC);
   strlcpy (g_verbose , "", LEN_DESC);
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
   /*---(transfer)-----------------------*/
   strlcpy (g_upload  , "", LEN_SHORT);
   strlcpy (g_download, "", LEN_SHORT);
   /*---(execution)----------------------*/
   strlcpy (g_gather  , "", LEN_SHORT);
   strlcpy (g_daemon  , "", LEN_SHORT);
   strlcpy (g_prickly , "", LEN_SHORT);
   strlcpy (g_normal  , "", LEN_SHORT);
   strlcpy (g_strict  , "", LEN_SHORT);
   strlcpy (g_reload  , "", LEN_SHORT);
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args__single      (char *a_levels, char n, char a_where)
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
   case  0  :   strlcat (g_silent , t, LEN_DESC);    break;
   case  1  :   strlcat (g_confirm, t, LEN_DESC);    break;
   case  2  :   strlcat (g_verbose, t, LEN_DESC);    break;
   }
   switch (a_where) {
   case  YJOBS_LOCAL    :   strlcat (g_local  , t, LEN_DESC);    break;
   case  YJOBS_CENTRAL  :   strlcat (g_central, t, LEN_DESC);    break;
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
   case 'y' :   strlcat (g_upload  , t, LEN_SHORT);   break;
   case 'z' :   strlcat (g_download, t, LEN_SHORT);   break;
   case 'g' :   strlcat (g_gather  , t, LEN_SHORT);   break;
   case 'd' :   strlcat (g_daemon  , t, LEN_SHORT);   break;
   case 'p' :   strlcat (g_prickly , t, LEN_SHORT);   break;
   case 'n' :   strlcat (g_normal  , t, LEN_SHORT);   break;
   case 's' :   strlcat (g_strict  , t, LEN_SHORT);   break;
   case 'h' :   strlcat (g_reload  , t, LEN_SHORT);   break;
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
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   yjobs_args__empty ();
   yjobs_who_init    ();
   for (i = 0; i < MAX_OPTS; ++i) {
      p = s_opts [i].levels;
      DEBUG_YJOBS  yLOG_complex ("current"   , "%2d, %s, %s", i, s_opts [i].levels, s_opts [i].option);
      if (p [0] == '\0')  break;
      if (rc >= 0)  rc = yjobs_args__single (p, 0, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("0"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, 1, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("1"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, 2, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("2"         , rc);
      if (rc <  0)  break;
   }
   g_runas   = a_runas;
   g_runmode = a_runmode;
   g_norun   = '-';
   g_noend   = '-';
   if (a_runfile != NULL) strcpy (g_runfile, a_runfile);
   else                   strcpy (g_runfile, "");
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   DEBUG_YJOBS  yLOG_info    ("g_confirm" , g_confirm);
   DEBUG_YJOBS  yLOG_info    ("g_verbose" , g_verbose);
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
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
yjobs_args__prepare     (char *a_runas, char *a_runmode, char *a_runfile, int *i, char *a_arg, char *a_next)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(pointer defense)----------------*/
   DEBUG_YJOBS  yLOG_point   ("a_runmode" , a_runmode);
   --rce;  if (a_runmode == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_runfile" , a_runfile);
   --rce;  if (a_runfile == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("i"         , i);
   --rce;  if (i         == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_arg"     , a_arg);
   --rce;  if (a_arg     == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check reload)-------------------*/
   if (strcmp (g_silent, "") == 0) {
      DEBUG_YJOBS  yLOG_note    ("first run, will call init");
      rc = yJOBS_args_init (*a_runas, *a_runmode, a_runfile);
   }
   /*---(unit testing stuff)-------------*/
   if (strcmp (a_arg, "--norun") == 0) {
      g_norun = 'y';
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(value defense)------------------*/
   DEBUG_YJOBS  yLOG_value   ("len"       , strlen (a_arg));
   --rce;  if (strlen (a_arg) <= 4) {
      yURG_err ('F', "option å%sæ too short, must be > 4 chars", a_arg);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (strncmp (a_arg, "--", 2) != 0) {
      yURG_err ('F', "option å%sæ must start with the prefix å--æ", a_arg);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (*a_runmode != '-') {
      yURG_err ('F', "run action already set (%c), can not update to å%sæ", *a_runmode, a_arg);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_args__find        (char *a_runas, char *a_arg, char *n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         j           =    0;
   char       *p           = NULL;
   char        c           =  '?';
   char        x_runas     =  '?';
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (n != NULL)  *n = -1;
   /*---(find action)--------------------*/
   for (j = 0; j < MAX_OPTS; ++j) {
      p = s_opts [j].option;
      if (p [0] == '\0')  break;
      if (strcmp (a_arg + 2, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("silent"    , s_opts [j].option);
         c = s_opts [j].levels [0];
         break;
      }
      if (a_arg [2] == 'c' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("confirm"   , s_opts [j].option);
         c = s_opts [j].levels [1];
         break;
      }
      if (a_arg [2] == 'v' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("verbose"   , s_opts [j].option);
         c = s_opts [j].levels [2];
         break;
      }
   }
   /*---(handle non-existant)------------*/
   DEBUG_YJOBS  yLOG_char    ("c"         , c);
   --rce;  if (c == '?') {
      yURG_err ('F', "action å%sæ not found in database", a_arg);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return '·';
   }
   /*---(handle not-allowed)-------------*/
   DEBUG_YJOBS  yLOG_char    ("c"         , c);
   --rce;  if (c == '·') {
      yURG_err ('F', "action å%sæ, (%c) not allowed", a_arg, a_arg [2]);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return '·';
   }
   /*---(testing)------------------------*/
   x_runas = yjobs_who_testing (*a_runas);
   --rce;  if (c == ACT_TESTING) {
      if (x_runas == '?') {
         yURG_err ('F', "testing version of for run-as (%c) not found", *a_runas);
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return '·';
      }
      *a_runas = g_runas = x_runas;
   } else {
      if (x_runas == '?') {
         yURG_err ('F', "current runas (%c) is not found", *a_runas);
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return '·';
      }
   }
   /*---(save-back)----------------------*/
   if (n != NULL)  *n = s_opts [j].offset;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yJOBS_argument          (int *i, cchar *a_arg, cchar *a_next, char *r_runas, char *r_mode, char *r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         j           =    0;
   char       *p           = NULL;
   char        x_act       =  '·';
   char        n           =   -1;
   char        f           =  '·';
   char        x_file      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_args__prepare (r_runas, r_mode, r_file, i, a_arg, a_next);
   DEBUG_YJOBS  yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (rc == 1) {
      DEBUG_YJOBS  yLOG_note    ("selected --norun mode");
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(walk options)-------------------*/
   x_act = yjobs_args__find (r_runas, a_arg, &n);
   DEBUG_YJOBS  yLOG_char    ("x_act"     , x_act);
   --rce;  if (x_act == '·') {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_act == ACT_TESTING) {
      DEBUG_YJOBS  yLOG_note    ("handled --testing runas change");
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle run as changnes)---------*/
   g_runas = *r_runas;
   /*---(get file flag)------------------*/
   f = yjobs_who_action (*r_runas, n);
   DEBUG_YJOBS  yLOG_char    ("f"         , f);
   --rce;  if (f == '?') {
      yURG_err ('F', "runas (%c) not found in g_whos database", *r_runas);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (f == '·') {
      yURG_err ('F', "action å%sæ not allowed for runas (%c)", a_arg, *r_runas);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle run mode changes)--------*/
   *r_mode = g_runmode = x_act;
   /*---(handle simple option)-----------*/
   if (f == '-') {
      if (strchr (g_central, x_act) != NULL) {
         if (strchr (g_etc, *r_runas) != NULL) {
            rc = yjobs_who_naming (*r_runas, NULL, NULL, NULL, NULL, NULL, x_file);
            strlcpy (r_file, x_file, LEN_DESC);
            strlcpy (g_runfile, x_file, LEN_DESC);
         }
      }
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle file flag)---------------*/
   --rce;  if (f != 'F') {
      yURG_err ('F', "action å%sæ not configured correctly", a_arg);
      yjobs_args__clearmode (r_runas, r_mode, r_file);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   --rce;  if (a_next == NULL) {
      yURG_err ('F', "action å%sæ requires a file name as an argument", a_arg);
      yjobs_args__clearmode (r_runas, r_mode, r_file);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   strlcpy (r_file   , a_next, LEN_PATH);
   strlcpy (g_runfile, a_next, LEN_PATH);
   ++(*i);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yJOBS_final             (int a_uid)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(setup location)-----------------*/
   if (strchr (g_unit, g_runas) != NULL) {
      DEBUG_YJOBS  yLOG_note    ("unit testing, run output and errors to tmp file");
      yURG_msg_tmp  ();
      yURG_err_tmp  (); 
   } else {
      DEBUG_YJOBS  yLOG_note    ("normal, run output and errors to stdout, strerr");
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
      DEBUG_YJOBS  yLOG_note    ("silent, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_CONFIRM {
      DEBUG_YJOBS  yLOG_note    ("confirm, muting output and errors until summary");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   else IF_VERBOSE {
      DEBUG_YJOBS  yLOG_note    ("verbose, turning on all output and errors");
      yURG_msg_live ();
      yURG_err_live ();
   }
   else {
      DEBUG_YJOBS  yLOG_note    ("unknown, muting all output and errors");
      yURG_msg_mute ();
      yURG_err_mute ();
   }
   /*---(check security for all)---------*/
   --rce;  if (a_uid != 0) {
      IF_AUDIT {
         DEBUG_YJOBS  yLOG_note    ("audit, caudit, and vaudit require root privlege");
         yURG_err ('F', "--audit, --caudit, and --vaudit require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_FIX   {
         DEBUG_YJOBS  yLOG_note    ("fix, cfix, and vfix require root privlege");
         yURG_err ('F', "--fix, --cfix, and --vfix require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_DAEMON {
         DEBUG_YJOBS  yLOG_note    ("daemon, cdaemon, and vdaemon require root privlege");
         yURG_err ('F', "--daemon, --cdaemon, and --vdaemon require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_PRICKLY {
         DEBUG_YJOBS  yLOG_note    ("prickly, cprickly, and vprickly require root privlege");
         yURG_err ('F', "--prickly, --cprickly, and --vprickly require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_NORMAL  {
         DEBUG_YJOBS  yLOG_note    ("normal, cnormal, and vnormal require root privlege");
         yURG_err ('F', "--normal, --cnormal, and --vnormal require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_STRICT  {
         DEBUG_YJOBS  yLOG_note    ("strict, cnormal, and vnormal require root privlege");
         yURG_err ('F', "--strict, --cstrict, and --vstrict require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (g_runmode == ACT_RELOAD)  {
         DEBUG_YJOBS  yLOG_note    ("reload require root privlege");
         yURG_err ('F', "--reload requires root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check security for /etc apps)---*/
   --rce;  if (a_uid != 0 && yJOBS_ifetc ()) {
      IF_INSTALL {
         DEBUG_YJOBS  yLOG_note    ("install, cinstall, and vinstall require root privlege");
         yURG_err ('F', "--install, --cinstall, and --vinstall require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      IF_CHECK   {
         DEBUG_YJOBS  yLOG_note    ("check, ccheck, and vcheck require root privlege");
         yURG_err ('F', "--check, --ccheck, and --vcheck require root privlege");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      simple short-cuts                       ----===*/
/*====================------------------------------------====================*/
static void      o___SHORTCUT________________o (void) {;};

CHECK  char  yJOBS_ifvalid    (void) { if (strchr (g_valid   , g_runas  ) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifunit     (void) { if (strchr (g_unit    , g_runas  ) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifetc      (void) { if (strchr (g_etc     , g_runas  ) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifsilent   (void) { if (strchr (g_silent  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifconfirm  (void) { if (strchr (g_confirm , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifverbose  (void) { if (strchr (g_verbose , g_runmode) != NULL)  return 1; else return 0; }

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

CHECK  char  yJOBS_ifupload   (void) { if (strchr (g_upload  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifdownload (void) { if (strchr (g_download, g_runmode) != NULL)  return 1; else return 0; }

CHECK  char  yJOBS_ifgather   (void) { if (strchr (g_gather  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifdaemon   (void) { if (strchr (g_daemon  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifprickly  (void) { if (strchr (g_prickly , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifnormal   (void) { if (strchr (g_normal  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifstrict   (void) { if (strchr (g_strict  , g_runmode) != NULL)  return 1; else return 0; }
CHECK  char  yJOBS_ifreload   (void) { if (strchr (g_reload  , g_runmode) != NULL)  return 1; else return 0; }

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
      sprintf (s, "%2då%.30sæ", strlen (g_silent) , g_silent);
      sprintf (t, "%2då%.25sæ", strlen (g_confirm), g_confirm);
      sprintf (u, "%2då%.25sæ", strlen (g_verbose), g_verbose);
      snprintf (unit_answer, LEN_RECD, "ARGS args        : %-34.34s %-29.29s %s", s, t, u);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

