/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



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
char          g_allmode     [LEN_HUND]  = "";
char          g_silent      [LEN_DESC]  = "";
char          g_confirm     [LEN_DESC]  = "";
char          g_verbose     [LEN_DESC]  = "";
/*---(incomming)------------*/
char          g_verify      [LEN_SHORT] = "";
char          g_localrpt    [LEN_SHORT] = "";
char          g_register    [LEN_SHORT] = "";
char          g_install     [LEN_SHORT] = "";
char          g_update      [LEN_SHORT] = "";
/*---(central)--------------*/
char          g_stats       [LEN_SHORT] = "";
char          g_list        [LEN_SHORT] = "";
char          g_report      [LEN_SHORT] = "";
char          g_check       [LEN_SHORT] = "";
char          g_audit       [LEN_SHORT] = "";
char          g_fix         [LEN_SHORT] = "";
char          g_only        [LEN_SHORT] = "";
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
char          g_running     [LEN_LABEL] = "";
char          g_daemony     [LEN_LABEL] = "";
char          g_daemon      [LEN_SHORT] = "";
char          g_prickly     [LEN_SHORT] = "";
char          g_normal      [LEN_SHORT] = "";
char          g_strict      [LEN_SHORT] = "";
char          g_reload      [LEN_SHORT] = "";
/*---(done)-----------------*/



/*
 *
 *
 *      
 *       ·············· yJOBS standard request set (28) ················
 *            
 *                                   
 *                                    version 
 *                                    about   
 *           ····                  3                ····
 *             ··········                                       
 *              verify                                          
 *              local                             ··········  
 *              register >>>  >>> backup     
 *              update                   upload     
 *              install          6 stats        2··········  
 *             ··········5         list                        
 *         local                      report                   cloud
 *                                   check                       
 *             ··········4         audit                       
 *              withdraw           fix          2··········  
 *              clear                    restore    
 *              remove   <<<  <<< download   
 *              extract                           ··········  
 *             ··········                                       
 *           ····                  6                ····
 *                                    gather  
 *                                    daemon  
 *                                    prickly 
 *                                    normal  
 *                                    strict  
 *                                    reload  
 *                                   
 *
 *
 *
 *
 */


#define     MAX_OPTS    60
typedef struct cOPTS  tOPTS;
struct cOPTS {
   char        option      [LEN_LABEL];
   char        levels      [LEN_SHORT];
   char        desc        [LEN_DESC];
   char        offset;
   char        run;
   char        where;
};
static const tOPTS   s_opts [MAX_OPTS] = {
   /*---(informational 3)---------------                                  seq  run  file-loc----- */
   { "version"  , "1··", "present a short versioning string"            ,   0, '-', YJOBS_NEITHER  },
   { "about"    , "2··", "key information about program"                ,   1, '-', YJOBS_NEITHER  },
   { "help"     , "3··", "present a simple help message"                ,   2, '-', YJOBS_NEITHER  },
   /*---(incomming 5)--------------------*/
   { "verify"   , "vÑV", "verify local file for correctness"            ,   4, '-', YJOBS_LOCAL    },
   { "local"    , "lòL", "report on local file content"                 ,   5, '-', YJOBS_LOCAL    },
   { "register" , "béB", "verify local file and register centrally"     ,   6, '-', YJOBS_LOCAL    },
   { "update"   , "uûU", "update central with single local file"        ,   7, '-', YJOBS_LOCAL    },
   { "install"  , "iðI", "verify local file, then update centrally"     ,   8, '-', YJOBS_LOCAL    },
   /*---(maintain 6)---------------------*/
   { "stats"    , "#··", "information about database and environment"   ,  10, '-', YJOBS_CENTRAL  },
   { "list"     , "=··", "list of executable content"                   ,  11, '-', YJOBS_CENTRAL  },
   { "report"   , "móM", "report on central database"                   ,  12, '-', YJOBS_CENTRAL  },
   { "check"    , "cýC", "check central file for correctness"           ,  13, '-', YJOBS_CENTRAL  },
   { "audit"    , "aèA", "audit central environment and all its files"  ,  14, '-', YJOBS_CENTRAL  },
   { "fix"      , "füF", "audit central environment and fix issues"     ,  15, '-', YJOBS_CENTRAL  },
   { "only"     , "oöO", "run on single central data file"              ,  16, 'y', YJOBS_CENTRAL  },
   /*---(epic)---------------------------*/
   { "backup"   , "kñK", "backup the central system"                    ,  18, '-', YJOBS_CENTRAL  },
   { "restore"  , "túT", "restore the central system from backup"       ,  19, '-', YJOBS_CENTRAL  },
   { "purge"    , "wÿW", "wipe clean entire central system"             ,  20, '-', YJOBS_CENTRAL  },
   /*---(elsewhere)----------------------*/
   { "upload"   , "yïY", "from elsewhere to central"                    ,  22, '-', YJOBS_CENTRAL  },
   { "download" , "zíZ", "from central to elsewhere"                    ,  23, '-', YJOBS_CENTRAL  },
   /*---(outgoing 4)---------------------*/
   { "withdraw" , "qþQ", "unregister centrally"                         ,  25, '-', YJOBS_CENTRAL  },
   { "clear"    , "xõX", "clear file from central location"             ,  26, '-', YJOBS_CENTRAL  },
   { "remove"   , "røR", "unregister and clear from central location"   ,  27, '-', YJOBS_CENTRAL  },
   { "extract"  , "eìE", "extract a central file to local copy"         ,  28, '-', YJOBS_CENTRAL  },
   /*---(execution)----------------------*/
   { "gather"   , "gêG", "execute system-wide data gather"              ,  30, '-', YJOBS_NEITHER  },
   { "daemon"   , "dëD", "execute specific file in daemon-mode"         ,  31, 'y', YJOBS_NEITHER  },
   { "prickly"  , "p÷P", "execute specific file in prickly daemon-mode" ,  32, 'y', YJOBS_NEITHER  },
   { "normal"   , "nôN", "execute specific file in normal-mode"         ,  33, 'y', YJOBS_NEITHER  },
   { "strict"   , "sùS", "execute specific file in strict normal-mode"  ,  34, 'y', YJOBS_NEITHER  },
   { "reload"   , "hîH", "send signal to reload daemon"                 ,  35, '-', YJOBS_NEITHER  },
   /*---(unit testing)-------------------*/
   { "testing"  , "j··", "change to test directories"                   ,  37, '-', YJOBS_NEITHER  },
   { "norun"    , "-··", "daemons only load data"                       ,   0, '-', YJOBS_NEITHER  },
   /*---(sentinal)-----------------------*/
   { ""         , "···", ""                                             ,   0, '-', YJOBS_NEITHER  },
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
         ystrlcpy (a_name, s_opts [i].option, LEN_LABEL);
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
   ystrlcpy (g_local   , "", LEN_DESC);
   ystrlcpy (g_central , "", LEN_DESC);
   /*---(validity)-----------------------*/
   ystrlcpy (g_valid   , "", LEN_DESC);
   ystrlcpy (g_unit    , "", LEN_DESC);
   ystrlcpy (g_etc     , "", LEN_DESC);
   /*---(verbosity)----------------------*/
   ystrlcpy (g_allmode , "", LEN_HUND);
   ystrlcpy (g_silent  , "", LEN_DESC);
   ystrlcpy (g_confirm , "", LEN_DESC);
   ystrlcpy (g_verbose , "", LEN_DESC);
   /*---(incomming)----------------------*/
   ystrlcpy (g_verify  , "", LEN_SHORT);
   ystrlcpy (g_local   , "", LEN_SHORT);
   ystrlcpy (g_register, "", LEN_SHORT);
   ystrlcpy (g_install , "", LEN_SHORT);
   ystrlcpy (g_update  , "", LEN_SHORT);
   /*---(central)------------------------*/
   ystrlcpy (g_list    , "", LEN_SHORT);
   ystrlcpy (g_stats   , "", LEN_SHORT);
   ystrlcpy (g_report  , "", LEN_SHORT);
   ystrlcpy (g_check   , "", LEN_SHORT);
   ystrlcpy (g_audit   , "", LEN_SHORT);
   ystrlcpy (g_fix     , "", LEN_SHORT);
   ystrlcpy (g_only    , "", LEN_SHORT);
   /*---(cloud)--------------------------*/
   ystrlcpy (g_upload  , "", LEN_SHORT);
   ystrlcpy (g_download, "", LEN_SHORT);
   /*---(outgoing)-----------------------*/
   ystrlcpy (g_withdraw, "", LEN_SHORT);
   ystrlcpy (g_clear   , "", LEN_SHORT);
   ystrlcpy (g_remove  , "", LEN_SHORT);
   ystrlcpy (g_extract , "", LEN_SHORT);
   /*---(transfer)-----------------------*/
   ystrlcpy (g_upload  , "", LEN_SHORT);
   ystrlcpy (g_download, "", LEN_SHORT);
   /*---(execution)----------------------*/
   ystrlcpy (g_gather  , "", LEN_SHORT);
   ystrlcpy (g_running , "", LEN_LABEL);
   ystrlcpy (g_daemony , "", LEN_LABEL);
   ystrlcpy (g_daemon  , "", LEN_SHORT);
   ystrlcpy (g_prickly , "", LEN_SHORT);
   ystrlcpy (g_normal  , "", LEN_SHORT);
   ystrlcpy (g_strict  , "", LEN_SHORT);
   ystrlcpy (g_reload  , "", LEN_SHORT);
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args__single      (cchar *a_levels, cchar n, cchar a_run, cchar a_where)
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
   ystrlcat (g_allmode, t, LEN_HUND);
   switch (n) {
   case  0  :   ystrlcat (g_silent , t, LEN_DESC);    break;
   case  1  :   ystrlcat (g_confirm, t, LEN_DESC);    break;
   case  2  :   ystrlcat (g_verbose, t, LEN_DESC);    break;
   }
   if (a_run == 'y')        ystrlcat (g_running, t, LEN_LABEL);
   switch (a_where) {
   case  YJOBS_LOCAL    :   ystrlcat (g_local  , t, LEN_DESC);    break;
   case  YJOBS_CENTRAL  :   ystrlcat (g_central, t, LEN_DESC);    break;
   }
   /*---(load by action)-----------------*/
   switch (a_levels [0]) {

   case ACT_VERIFY   :   ystrlcat (g_verify  , t, LEN_SHORT);   break;
   case ACT_LOCALRPT :   ystrlcat (g_localrpt, t, LEN_SHORT);   break;
   case ACT_REGISTER :   ystrlcat (g_register, t, LEN_SHORT);   break;
   case ACT_INSTALL  :   ystrlcat (g_install , t, LEN_SHORT);   break;
   case ACT_UPDATE   :   ystrlcat (g_update  , t, LEN_SHORT);   break;

   case ACT_STATS    :   ystrlcat (g_stats   , t, LEN_SHORT);   break;
   case ACT_LIST     :   ystrlcat (g_list    , t, LEN_SHORT);   break;
   case ACT_REPORT   :   ystrlcat (g_report  , t, LEN_SHORT);   break;
   case ACT_CHECK    :   ystrlcat (g_check   , t, LEN_SHORT);   break;
   case ACT_AUDIT    :   ystrlcat (g_audit   , t, LEN_SHORT);   break;
   case ACT_FIX      :   ystrlcat (g_fix     , t, LEN_SHORT);   break;
   case ACT_ONLY     :   ystrlcat (g_only    , t, LEN_SHORT);   break;

   case ACT_UPLOAD   :   ystrlcat (g_upload  , t, LEN_SHORT);   break;
   case ACT_DOWNLOAD :   ystrlcat (g_download, t, LEN_SHORT);   break;

   case ACT_WITHDRAW :   ystrlcat (g_withdraw, t, LEN_SHORT);   break;
   case ACT_CLEAR    :   ystrlcat (g_clear   , t, LEN_SHORT);   break;
   case ACT_REMOVE   :   ystrlcat (g_remove  , t, LEN_SHORT);   break;
   case ACT_EXTRACT  :   ystrlcat (g_extract , t, LEN_SHORT);   break;

   case ACT_GATHER   :   ystrlcat (g_gather  , t, LEN_SHORT);   break;
   case ACT_DAEMON   :   ystrlcat (g_daemon  , t, LEN_SHORT);   ystrlcat (g_daemony , t, LEN_LABEL);   break;
   case ACT_PRICKLY  :   ystrlcat (g_prickly , t, LEN_SHORT);   ystrlcat (g_daemony , t, LEN_LABEL);   break;
   case ACT_NORMAL   :   ystrlcat (g_normal  , t, LEN_SHORT);   break;
   case ACT_STRICT   :   ystrlcat (g_strict  , t, LEN_SHORT);   break;
   case ACT_RELOAD   :   ystrlcat (g_reload  , t, LEN_SHORT);   break;

   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args_init         (char *r_runas, char *r_mode, char *r_file)
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
      if (rc >= 0)  rc = yjobs_args__single (p, 0, s_opts [i].run, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("0"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, 1, s_opts [i].run, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("1"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, 2, s_opts [i].run, s_opts [i].where);
      DEBUG_YJOBS  yLOG_value   ("2"         , rc);
      if (rc <  0)  break;
   }
   if (r_runas != NULL)   *r_runas = myJOBS.m_runas;
   myJOBS.m_mode = YJOBS_NEITHER;
   if (r_mode  != NULL)   *r_mode  = myJOBS.m_mode;
   myJOBS.m_flag = '·';
   ystrlcpy (myJOBS.m_file, "", LEN_PATH);
   ystrlcpy (myJOBS.m_dir , "", LEN_PATH);
   ystrlcpy (myJOBS.m_full, "", LEN_PATH);
   if (r_file  != NULL)   ystrlcpy (r_file, myJOBS.m_file, LEN_PATH);
   g_norun   = YJOBS_NEITHER;
   g_noend   = YJOBS_NEITHER;
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   DEBUG_YJOBS  yLOG_info    ("g_confirm" , g_confirm);
   DEBUG_YJOBS  yLOG_info    ("g_verbose" , g_verbose);
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_args__clearmode   (char *r_runas, char *r_mode, char *r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defaults)-----------------------*/
   if (r_runas != NULL)  *r_runas   = myJOBS.m_runas;
   myJOBS.m_mode = YJOBS_NEITHER;
   if (r_mode  != NULL)  *r_mode = YJOBS_NEITHER;
   myJOBS.m_flag = '·';
   ystrlcpy (myJOBS.m_file, "", LEN_PATH);
   ystrlcpy (myJOBS.m_dir , "", LEN_PATH);
   ystrlcpy (myJOBS.m_full, "", LEN_PATH);
   if (r_file  != NULL)  ystrlcpy (r_file, "", LEN_PATH);
   /*---(hide errors again)--------------*/
   yURG_err_mute ();
   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   return 0;
}

char yJOBS_reset  (char *r_runas, char *r_mode, char *r_file) { return yjobs_args__clearmode (r_runas, r_mode, r_file); }

char
yjobs_args__prepare     (int *b_pos, char *a_arg, char *a_next, char *r_runas, char *r_mode, char *r_file)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   DEBUG_YJOBS  yLOG_point   ("r_runas"   , r_runas);
   if (r_runas != NULL)   *r_runas = myJOBS.m_runas;
   DEBUG_YJOBS  yLOG_point   ("r_mode"    , r_mode);
   if (r_mode  != NULL)   *r_mode  = myJOBS.m_mode;
   DEBUG_YJOBS  yLOG_point   ("r_file"    , r_file);
   if (r_file  != NULL)   ystrlcpy (r_file, myJOBS.m_file, LEN_PATH);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_complex ("runas"     , "%c  å%sæ", myJOBS.m_runas, g_valid);
   --rce;  if (yJOBS_ifvalid () == 0) {
      DEBUG_YJOBS   yLOG_note    ("runas not recognized");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("b_pos"     , b_pos);
   --rce;  if (b_pos     == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_arg"     , a_arg);
   --rce;  if (a_arg     == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_next"    , a_next);
   /*---(check reload)-------------------*/
   if (strcmp (g_silent, "") == 0) {
      DEBUG_YJOBS  yLOG_note    ("first run, will call init");
      rc = yjobs_args_init (r_runas, r_mode, r_file);
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
   /*> --rce;  if (myJOBS.m_mode != '-') {                                                               <* 
    *>    yURG_err ('F', "run action already set (%c), can not update to å%sæ", myJOBS.m_mode, a_arg);   <* 
    *>    DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rc);                                                  <* 
    *>    return rce;                                                                                    <* 
    *> }                                                                                                 <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_args__find        (char *a_arg, char *n, char *r_runas, char *r_noise)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         j           =    0;
   char       *p           = NULL;
   char        c           =  '?';
   char        x_runas     =  '?';
   char        x_noise     =  '?';
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (n       != NULL)  *n       = -1;
   if (r_noise != NULL)  *r_noise = '-';
   /*---(find action)--------------------*/
   for (j = 0; j < MAX_OPTS; ++j) {
      DEBUG_YJOBS  yLOG_value   ("loop"      , j);
      p = s_opts [j].option;
      if (p [0] == '\0')  break;
      if (strcmp (a_arg + 2, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("silent"    , s_opts [j].option);
         c = s_opts [j].levels [0];
         x_noise = '-';
         break;
      }
      if (a_arg [2] == 'c' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("confirm"   , s_opts [j].option);
         c = s_opts [j].levels [1];
         x_noise = 'c';
         break;
      }
      if (a_arg [2] == 'v' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("verbose"   , s_opts [j].option);
         c = s_opts [j].levels [2];
         x_noise = 'V';
         break;
      }
   }
   /*---(handle non-existant)------------*/
   DEBUG_YJOBS  yLOG_char    ("c"         , c);
   --rce;  if (c == '?') {
      yURG_msg ('-', "action å%sæ not found in database, maybe program specific", a_arg);
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return c;
   }
   /*---(handle not-allowed)-------------*/
   DEBUG_YJOBS  yLOG_char    ("c"         , c);
   --rce;  if (c == '·') {
      yURG_err ('F', "action å%sæ, (%c) not allowed", a_arg, a_arg [2]);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return '·';
   }
   /*---(testing)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , myJOBS.m_runas);
   x_runas = yjobs_who_testing (myJOBS.m_runas);
   DEBUG_YJOBS  yLOG_char    ("x_runas"   , x_runas);
   --rce;  if (c == ACT_TESTING) {
      if (x_runas == '?') {
         yURG_err ('F', "testing version of for run-as (%c) not found", myJOBS.m_runas);
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return '·';
      }
      myJOBS.m_runas = x_runas;
      if (r_runas != NULL)  *r_runas = x_runas;
   }
   /*---(save-back)----------------------*/
   if (n       != NULL)  *n       = s_opts [j].offset;
   if (r_noise != NULL)  *r_noise = x_noise;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yJOBS_argument          (int *b_pos, cchar *a_arg, cchar *a_next, char *r_runas, char *r_mode, char *r_file)
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
   char        x_noise     =  '·';
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_args__prepare (b_pos, a_arg, a_next, r_runas, r_mode, r_file);
   DEBUG_YJOBS  yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (rc == 1) {
      DEBUG_YJOBS  yLOG_note    ("selected --norun mode");
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(walk options)-------------------*/
   x_act = yjobs_args__find (a_arg, &n, r_runas, &x_noise);
   DEBUG_YJOBS  yLOG_char    ("x_act"     , x_act);
   if (x_act == '?') {
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (x_act == '·') {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_act == ACT_TESTING) {
      DEBUG_YJOBS  yLOG_note    ("handled --testing runas change");
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_YJOBS  yLOG_char    ("x_noise"   , x_noise);
   if (x_noise == 'V') {
      DEBUG_YJOBS  yLOG_note    ("turn on err and msg live");
      yURG_msg_live ();
      yURG_err_live ();
   }
   --rce;  if (myJOBS.m_mode != '-') {
      yURG_err ('F', "run action already set (%c), can not update to å%sæ", myJOBS.m_mode, a_arg);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get file flag)------------------*/
   f = yjobs_who_action (myJOBS.m_runas, n);
   DEBUG_YJOBS  yLOG_char    ("f"         , f);
   --rce;  if (f == '?') {
      yURG_err ('F', "runas (%c) not found in g_whos database", myJOBS.m_runas);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (f == '·') {
      yURG_err ('F', "action å%sæ not allowed for runas (%c)", a_arg, myJOBS.m_runas);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle run mode changes)--------*/
   myJOBS.m_mode = x_act;
   myJOBS.m_flag = f;
   if (r_mode != NULL)  *r_mode = x_act;
   /*---(handle simple option)-----------*/
   if (f == '-') {
      DEBUG_YJOBS  yLOG_note    ("simple actions");
      if (strchr (g_central, x_act) != NULL) {
         if (strchr (g_etc, myJOBS.m_runas) != NULL) {
            rc = yjobs_who_naming (myJOBS.m_runas, NULL, NULL, NULL, NULL, NULL, x_file);
            ystrlcpy (myJOBS.m_file, x_file, LEN_PATH);
            if (r_file != NULL)  ystrlcpy (r_file, x_file, LEN_PATH);
         }
      }
      DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_YJOBS  yLOG_note    ("complex actions");
   /*---(handle file flag)---------------*/
   --rce;  if (f != 'F') {
      yURG_err ('F', "action å%sæ not configured correctly", a_arg);
      yjobs_args__clearmode (r_runas, r_mode, r_file);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_next"    , a_next);
   --rce;  if (a_next == NULL) {
      DEBUG_YJOBS  yLOG_note    ("null a_next option");
      yURG_err ('F', "action å%sæ requires a file name as an argument", a_arg);
      yjobs_args__clearmode (r_runas, r_mode, r_file);
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (myJOBS.m_file, a_next, LEN_PATH);
   DEBUG_YJOBS  yLOG_info    ("m_file"    , myJOBS.m_file);
   if (r_file != NULL)  ystrlcpy (r_file   , a_next, LEN_PATH);
   ++(*b_pos);
   DEBUG_YJOBS  yLOG_value   ("b_pos"     , *b_pos);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs_final_full        (int a_uid)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(setup location)-----------------*/
   if (strchr (g_unit, myJOBS.m_runas) != NULL) {
      DEBUG_YJOBS  yLOG_note    ("unit testing, run output and errors to tmp file");
      yURG_msg_tmp  ();
      yURG_err_tmp  (); 
   } else {
      DEBUG_YJOBS  yLOG_note    ("normal, run output and errors to stdout, strerr");
      yURG_msg_std  ();
      yURG_err_std  ();
   }
   /*---(check for illegal)--------------*/
   --rce;  if (myJOBS.m_runas == '-' || myJOBS.m_mode == '-') {
      DEBUG_YJOBS  yLOG_note    ("illegal runas or mode, muting all");
      yURG_msg_mute ();
      yURG_err_mute ();
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
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
      if (myJOBS.m_mode == ACT_RELOAD)  {
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

char
yjobs_final             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_user      [LEN_LABEL] = "";
   int         x_uid       =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(action)-------------------------*/
   rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, NULL, x_user, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_value   ("x_uid"     , x_uid);
   DEBUG_YJOBS  yLOG_info    ("x_user"    , x_user);
   /*---(call final)---------------------*/
   rc = yjobs_final_full (x_uid);
   DEBUG_YJOBS  yLOG_value   ("final"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char  yJOBS_final       (int a_uid)   { return yjobs_final_full (a_uid); }



/*====================------------------------------------====================*/
/*===----                      simple short-cuts                       ----===*/
/*====================------------------------------------====================*/
static void      o___SHORTCUT________________o (void) {;};

char  yJOBS_ifvalid    (void) { if (strchr (g_valid   , myJOBS.m_runas) != NULL)  return 1; else return 0; }
char  yJOBS_ifunit     (void) { if (strchr (g_unit    , myJOBS.m_runas) != NULL)  return 1; else return 0; }
char  yJOBS_ifetc      (void) { if (strchr (g_etc     , myJOBS.m_runas) != NULL)  return 1; else return 0; }

char  yJOBS_ifallmode  (void) { if (strchr (g_allmode , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifsilent   (void) { if (strchr (g_silent  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifconfirm  (void) { if (strchr (g_confirm , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifverbose  (void) { if (strchr (g_verbose , myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifhelp     (void) { if (myJOBS.m_mode == ACT_HELP)                    return 1; else return 0; }
char  yJOBS_ifversion  (void) { if (myJOBS.m_mode == ACT_VERSION)                 return 1; else return 0; }

char  yJOBS_ifverify   (void) { if (strchr (g_verify  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_iflocalrpt (void) { if (strchr (g_localrpt, myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifregister (void) { if (strchr (g_register, myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifinstall  (void) { if (strchr (g_install , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifupdate   (void) { if (strchr (g_update  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifstats    (void) { if (strchr (g_stats   , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_iflist     (void) { if (strchr (g_list    , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifreport   (void) { if (strchr (g_report  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifcheck    (void) { if (strchr (g_check   , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifaudit    (void) { if (strchr (g_audit   , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_iffix      (void) { if (strchr (g_fix     , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifonly     (void) { if (strchr (g_only    , myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifupload   (void) { if (strchr (g_upload  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifdownload (void) { if (strchr (g_download, myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifwithdraw (void) { if (strchr (g_withdraw, myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifclear    (void) { if (strchr (g_clear   , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifremove   (void) { if (strchr (g_remove  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifextract  (void) { if (strchr (g_extract , myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifgather   (void) { if (strchr (g_gather  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifrunning  (void) { if (strchr (g_running , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifdaemony  (void) { if (strchr (g_daemony , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifdaemon   (void) { if (strchr (g_daemon  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifprickly  (void) { if (strchr (g_prickly , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifnormal   (void) { if (strchr (g_normal  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifstrict   (void) { if (strchr (g_strict  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }
char  yJOBS_ifreload   (void) { if (strchr (g_reload  , myJOBS.m_mode)  != NULL)  return 1; else return 0; }

char  yJOBS_ifnorun    (void) { if (g_norun == 'y')                               return 1; else return 0; }
char  yJOBS_ifnoend    (void) { if (g_noend == 'y')                               return 1; else return 0; }



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
      sprintf (s, "%2då%.35sæ", strlen (g_silent) , g_silent);
      sprintf (t, "%2då%.30sæ", strlen (g_confirm), g_confirm);
      sprintf (u, "%2då%.30sæ", strlen (g_verbose), g_verbose);
      snprintf (unit_answer, LEN_RECD, "ARGS args        : %-39.39s %-34.34s %s", s, t, u);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

