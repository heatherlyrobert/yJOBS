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
/*---(help)-----------------*/
char          G_HLP         [LEN_DESC]  = "";
/*---(incomming)------------*/
char          G_INC         [LEN_DESC]  = "";
char          g_verify      [LEN_SHORT] = "";
char          g_localrpt    [LEN_SHORT] = "";
char          g_register    [LEN_SHORT] = "";
char          g_install     [LEN_SHORT] = "";
char          g_update      [LEN_SHORT] = "";
/*---(central)--------------*/
char          G_CEN         [LEN_DESC]  = "";
char          g_stats       [LEN_SHORT] = "";
char          g_list        [LEN_SHORT] = "";
char          g_report      [LEN_SHORT] = "";
char          g_check       [LEN_SHORT] = "";
char          g_audit       [LEN_SHORT] = "";
char          g_fix         [LEN_SHORT] = "";
char          g_only        [LEN_SHORT] = "";
/*---(outgoing)-------------*/
char          G_OUT         [LEN_DESC]  = "";
char          g_withdraw    [LEN_SHORT] = "";
char          g_clear       [LEN_SHORT] = "";
char          g_remove      [LEN_SHORT] = "";
char          g_extract     [LEN_SHORT] = "";
/*---(transfer)-------------*/
char          G_EPI         [LEN_DESC]  = "";
char          g_upload      [LEN_SHORT] = "";
char          g_download    [LEN_SHORT] = "";
/*---(execution)------------*/
char          G_GAT         [LEN_DESC]  = "";
char          g_gather      [LEN_SHORT] = "";
char          g_running     [LEN_LABEL] = "";
char          g_daemony     [LEN_LABEL] = "";
char          g_daemon      [LEN_SHORT] = "";
char          g_prickly     [LEN_SHORT] = "";
char          g_normal      [LEN_SHORT] = "";
char          g_strict      [LEN_SHORT] = "";
char          g_reload      [LEN_SHORT] = "";
/*---(actions)--------------*/
char          g_act_rdb     [LEN_HUND]  = "";
char          g_act_upd     [LEN_HUND]  = "";
char          g_act_ins     [LEN_HUND]  = "";
char          g_act_reg     [LEN_HUND]  = "";

char          g_act_sec     [LEN_HUND]  = "";
char          g_act_aud     [LEN_HUND]  = "";
char          g_act_pul     [LEN_HUND]  = "";
char          g_act_rpt     [LEN_HUND]  = "";
char          g_act_run     [LEN_HUND]  = "";
char          g_act_chk     [LEN_HUND]  = "";

char          g_act_wit     [LEN_HUND]  = "";
char          g_act_clr     [LEN_HUND]  = "";
char          g_act_rem     [LEN_HUND]  = "";
char          g_act_wdb     [LEN_HUND]  = "";
/*---(done)-----------------*/



/*
 *
 *
 *      
 *       ƒ·············· yJOBS standard request set (28) ················‚
 *            
 *                                   ƒ€€€€€€€€€‚
 *                                   Œ version Œ
 *                                   Œ about   Œ
 *           ƒ····                  3„€€€€‰€€€€…                ····‚
 *           Œ  ƒ··········‚              Œ                         Œ
 *           Œ   verify                 Œ                         Œ
 *           Œ   local                  Œ           ƒ··········‚  Œ
 *           Œ   register ‡€€>>>€€€€€€€‚ Œ ƒ€€€€>>>€€† backup     Œ
 *           Œ   update            ƒ€€ˆ€ˆ€ˆ€€‚       upload     Œ
 *           Œ   install          6Œ stats   Œ     2„··········…  Œ
 *           Œ  „··········…5        Œ list    Œ                    Œ
 *         local                     Œ report  Œ                 cloud
 *           Œ                       Œ check   Œ                    Œ
 *           Œ  ƒ··········‚4        Œ audit   Œ                    Œ
 *           Œ   withdraw          Œ fix     Œ     2ƒ··········‚  Œ
 *           Œ   clear             „€€‰€‰€‰€€…       restore    Œ
 *           Œ   remove   ‡€€<<<€€€€€€€…  „€€€€<<<€€† download   Œ
 *           Œ   extract                           „··········…  Œ
 *           Œ  „··········…                                       Œ
 *           „····                  6ƒ€€€€ˆ€€€€‚                ····…
 *                                   Œ gather  Œ
 *                                   Œ daemon  Œ
 *                                   Œ prickly Œ
 *                                   Œ normal  Œ
 *                                   Œ strict  Œ
 *                                   Œ reload  Œ
 *                                   „€€€€€€€€€…
 *
 *
 *
 *
 */


#define     MAX_OPTS    60
typedef struct cOPTS  tOPTS;
struct cOPTS {
   /*---(main)--------------*/
   char        o_cat;
   char        o_option    [LEN_LABEL];
   char        o_levels    [LEN_SHORT];
   char        o_desc      [LEN_DESC];
   char        o_offset;
   /*---(actions)-----------*/
   char        o_readdb;
   char        o_update;
   char        o_install;
   char        o_register;

   char        o_secure;
   char        o_audit;
   char        o_pull;
   char        o_report;
   char        o_run;
   char        o_check;

   char        o_withdraw;
   char        o_clear;
   char        o_remove;
   char        o_writedb;
   /*---(other)-------------*/
   char        o_where;
   char        o_notes     [LEN_FULL];
   /*---(done)--------------*/
};
static const tOPTS   s_opts [MAX_OPTS] = {
   /*---(informational 3)---------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'h' , "version"  , "1··", "present a short versioning string"            ,   0,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'h' , "about"    , "2··", "key information about program"                ,   1,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'h' , "help"     , "3··", "present a simple help message"                ,   2,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   /*---(incomming 5)-------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'i' , "verify"   , "vÑV", "verify local file for correctness"            ,   4,   '·', 'y', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_LOCAL    , "" },
   { 'i' , "local"    , "lòL", "report on local file content"                 ,   5,   '·', 'y', '·', '·',   '·', '·', '·', 'y', '·', '·',   '·', '·', '·', '·',   YJOBS_LOCAL    , "" },
   { 'i' , "register" , "béB", "verify local file and register centrally"     ,   6,   '·', 'y', '·', 'y',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_LOCAL    , "" },
   { 'i' , "update"   , "uûU", "update central with single local file"        ,   7,   'y', 'y', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', 'y',   YJOBS_LOCAL    , "" },
   { 'i' , "install"  , "iðI", "verify local file, then update centrally"     ,   8,   'y', 'y', 'y', 'y',   'y', '·', '·', '·', '·', '·',   '·', '·', '·', 'y',   YJOBS_LOCAL    , "" },
   /*---(maintain 5)--------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'm' , "stats"    , "#··", "information about database and environment"   ,  10,   'y', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "list"     , "=··", "list of executable content"                   ,  11,   '·', '·', '·', '·',   '·', '·', 'y', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "report"   , "móM", "report on central database"                   ,  12,   'y', '·', '·', '·',   '·', '·', 'y', 'y', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "audit"    , "aèA", "audit central environment and all its files"  ,  14,   '·', '·', '·', '·',   'y', 'y', 'y', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "fix"      , "füF", "audit central environment and fix issues"     ,  15,   '·', '·', '·', '·',   'y', 'y', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "check"    , "cýC", "check central file for correctness"           ,  13,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', 'y',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'm' , "only"     , "oöO", "run on single central data file"              ,  16,   '·', '·', '·', '·',   '·', '·', '·', '·', 'y', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   /*---(epic)--------------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'e' , "backup"   , "kñK", "backup the central system"                    ,  18,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'e' , "restore"  , "túT", "restore the central system from backup"       ,  19,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'e' , "purge"    , "wÿW", "wipe clean entire central system"             ,  20,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   /*---(elsewhere)---------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'e' , "upload"   , "yïY", "from elsewhere to central"                    ,  22,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'e' , "download" , "zíZ", "from central to elsewhere"                    ,  23,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   /*---(outgoing 5)--------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'o' , "withdraw" , "qþQ", "unregister centrally"                         ,  25,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   'y', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   { 'o' , "clear"    , "xõX", "clear file from central location"             ,  26,   'y', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', 'y', '·', 'y',   YJOBS_CENTRAL  , "" },
   { 'o' , "remove"   , "røR", "unregister and clear from central location"   ,  27,   'y', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   'y', 'y', 'y', 'y',   YJOBS_CENTRAL  , "" },
   { 'o' , "extract"  , "eìE", "extract a central file to local copy"         ,  28,   'y', '·', '·', '·',   '·', '·', '·', '·', '·', 'y',   '·', '·', '·', '·',   YJOBS_CENTRAL  , "" },
   /*---(execution)---------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'g' , "gather"   , "gêG", "execute system-wide data gather"              ,  30,   'y', '·', '·', '·',   'y', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "if host uses world file (like polymnia), calls successive pulls (ACT_PULL) for world each entry.  if not (like helios), calls gather (ACT_GATHER) once." },
   { 'g' , "daemon"   , "dëD", "execute specific file in daemon-mode"         ,  31,   'y', '·', '·', '·',   'y', '·', 'y', '·', 'y', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'g' , "prickly"  , "p÷P", "execute specific file in prickly daemon-mode" ,  32,   'y', '·', '·', '·',   'y', 'y', 'y', '·', 'y', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'g' , "normal"   , "nôN", "execute specific file in normal-mode"         ,  33,   'y', '·', '·', '·',   'y', '·', 'y', '·', 'y', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'g' , "strict"   , "sùS", "execute specific file in strict normal-mode"  ,  34,   'y', '·', '·', '·',   'y', 'y', 'y', '·', 'y', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'g' , "reload"   , "hîH", "send signal to reload daemon"                 ,  35,   'y', '·', '·', '·',   'y', '·', 'y', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   /*---(unit testing)------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { 'u' , "testing"  , "j··", "change to test directories"                   ,  37,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   { 'u' , "norun"    , "-··", "daemons only load data"                       ,   0,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   /*---(sentinal)----------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
   { '·' , ""         , "···", ""                                             ,   0,   '·', '·', '·', '·',   '·', '·', '·', '·', '·', '·',   '·', '·', '·', '·',   YJOBS_NEITHER  , "" },
   /*---(done)--------------------------------                                  seq    rdb  upd  ins  reg    sec  aud  pul  rpt  run  chk    wit  clr  rem  wdb    file-loc----- */
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
      if (strcmp (s_opts [i].o_option, "") == 0)  break;
      DEBUG_YJOBS  yLOG_complex ("current"   , "%2d, %s, %s", i, s_opts [i].o_levels, s_opts [i].o_option);
      if (strchr (s_opts [i].o_levels, a_mode) != NULL) {
         ystrlcpy (a_name, s_opts [i].o_option, LEN_LABEL);
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
   /*---(help)---------------------------*/
   ystrlcpy (G_HLP     , "", LEN_DESC);
   /*---(incomming)----------------------*/
   ystrlcpy (G_INC     , "", LEN_DESC);
   ystrlcpy (g_verify  , "", LEN_SHORT);
   ystrlcpy (g_local   , "", LEN_SHORT);
   ystrlcpy (g_register, "", LEN_SHORT);
   ystrlcpy (g_install , "", LEN_SHORT);
   ystrlcpy (g_update  , "", LEN_SHORT);
   /*---(central)------------------------*/
   ystrlcpy (G_CEN     , "", LEN_DESC);
   ystrlcpy (g_list    , "", LEN_SHORT);
   ystrlcpy (g_stats   , "", LEN_SHORT);
   ystrlcpy (g_report  , "", LEN_SHORT);
   ystrlcpy (g_check   , "", LEN_SHORT);
   ystrlcpy (g_audit   , "", LEN_SHORT);
   ystrlcpy (g_fix     , "", LEN_SHORT);
   ystrlcpy (g_only    , "", LEN_SHORT);
   /*---(cloud)--------------------------*/
   ystrlcpy (G_EPI     , "", LEN_DESC);
   ystrlcpy (g_upload  , "", LEN_SHORT);
   ystrlcpy (g_download, "", LEN_SHORT);
   /*---(outgoing)-----------------------*/
   ystrlcpy (G_OUT     , "", LEN_DESC);
   ystrlcpy (g_withdraw, "", LEN_SHORT);
   ystrlcpy (g_clear   , "", LEN_SHORT);
   ystrlcpy (g_remove  , "", LEN_SHORT);
   ystrlcpy (g_extract , "", LEN_SHORT);
   /*---(execution)----------------------*/
   ystrlcpy (G_GAT     , "", LEN_DESC);
   ystrlcpy (g_gather  , "", LEN_SHORT);
   ystrlcpy (g_running , "", LEN_LABEL);
   ystrlcpy (g_daemony , "", LEN_LABEL);
   ystrlcpy (g_daemon  , "", LEN_SHORT);
   ystrlcpy (g_prickly , "", LEN_SHORT);
   ystrlcpy (g_normal  , "", LEN_SHORT);
   ystrlcpy (g_strict  , "", LEN_SHORT);
   ystrlcpy (g_reload  , "", LEN_SHORT);
   /*---(actions)------------------------*/
   ystrlcpy (g_act_rdb , "", LEN_HUND);
   ystrlcpy (g_act_upd , "", LEN_HUND);
   ystrlcpy (g_act_ins , "", LEN_HUND);
   ystrlcpy (g_act_reg , "", LEN_HUND);

   ystrlcpy (g_act_sec , "", LEN_HUND);
   ystrlcpy (g_act_aud , "", LEN_HUND);
   ystrlcpy (g_act_pul , "", LEN_HUND);
   ystrlcpy (g_act_rpt , "", LEN_HUND);
   ystrlcpy (g_act_run , "", LEN_HUND);
   ystrlcpy (g_act_chk , "", LEN_HUND);

   ystrlcpy (g_act_wit , "", LEN_HUND);
   ystrlcpy (g_act_clr , "", LEN_HUND);
   ystrlcpy (g_act_rem , "", LEN_HUND);
   ystrlcpy (g_act_wdb , "", LEN_HUND);
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_args__single      (char *a_levels, char a_cat, char n, char a_run, char a_where)
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
   /*---(load by category)---------------*/
   switch (a_cat) {
   case  'h'         :   ystrlcat (G_HLP     , t, LEN_DESC);   break;
   case  'i'         :   ystrlcat (G_INC     , t, LEN_DESC);   break;
   case  'm'         :   ystrlcat (G_CEN     , t, LEN_DESC);   break;
   case  'o'         :   ystrlcat (G_OUT     , t, LEN_DESC);   break;
   case  'g'         :   ystrlcat (G_GAT     , t, LEN_DESC);   break;
   case  'e'         :   ystrlcat (G_EPI     , t, LEN_DESC);   break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs__args_actions     (char a_cat, char a_field, char a_levels [LEN_SHORT], char b_global [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_levels    [LEN_SHORT] = "";
   /*---(update)-------------------------*/
   if (a_field == 'y') {
      /*---(convenience spacing)---------*/
      if (strlen (b_global) != 0) {
         if (b_global [98] != a_cat)  ystrlcat (b_global, "·", LEN_HUND);
      }
      /*---(concatinate)-----------------*/
      ystrlcat  (x_levels , a_levels, LEN_SHORT);
      ystrlddel (x_levels, '·'      , LEN_SHORT);
      ystrlcat  (b_global , x_levels, LEN_HUND);
      /*---(prepare for next)------------*/
      b_global [98] = a_cat;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                              <* 
 *> yjobs_args_actions      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    for (i = 0; i < MAX_OPTS; ++i) {                                               <* 
 *>       if (s_opts [i].o_cat = '-')  break;                                         <* 
 *>    }                                                                              <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

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
      /*---(singles)---------------------*/
      p = s_opts [i].o_levels;
      DEBUG_YJOBS  yLOG_complex ("current"   , "%2d, %s, %s", i, s_opts [i].o_levels, s_opts [i].o_option);
      if (p [0] == '\0')  break;
      if (rc >= 0)  rc = yjobs_args__single (p, s_opts [i].o_cat, 0, s_opts [i].o_run, s_opts [i].o_where);
      DEBUG_YJOBS  yLOG_value   ("0"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, s_opts [i].o_cat, 1, s_opts [i].o_run, s_opts [i].o_where);
      DEBUG_YJOBS  yLOG_value   ("1"         , rc);
      if (rc >= 0)  rc = yjobs_args__single (p, s_opts [i].o_cat, 2, s_opts [i].o_run, s_opts [i].o_where);
      DEBUG_YJOBS  yLOG_value   ("2"         , rc);
      if (rc <  0)  break;
      /*---(actions)---------------------*/
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_readdb   , s_opts [i].o_levels, g_act_rdb);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_update   , s_opts [i].o_levels, g_act_upd);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_install  , s_opts [i].o_levels, g_act_ins);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_register , s_opts [i].o_levels, g_act_reg);

      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_secure   , s_opts [i].o_levels, g_act_sec);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_audit    , s_opts [i].o_levels, g_act_aud);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_pull     , s_opts [i].o_levels, g_act_pul);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_report   , s_opts [i].o_levels, g_act_rpt);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_run      , s_opts [i].o_levels, g_act_run);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_check    , s_opts [i].o_levels, g_act_chk);

      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_withdraw , s_opts [i].o_levels, g_act_wit);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_clear    , s_opts [i].o_levels, g_act_clr);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_remove   , s_opts [i].o_levels, g_act_rem);
      yjobs__args_actions (s_opts [i].o_cat, s_opts [i].o_writedb  , s_opts [i].o_levels, g_act_wdb);
      /*---(done)------------------------*/
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
yjobs_args_offset       (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char       *p           = NULL;
   int         l           =    0;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(find action)--------------------*/
   for (i = 0; i < MAX_OPTS; ++i) {
      p = s_opts [i].o_levels;
      if (p [0] == '\0')  break;
      l = strlen (p);
      DEBUG_YJOBS  yLOG_complex ("loop"      , "%2d, %2då%sæ", i, l, p);
      if      (l > 0 && p [0] != '·' && p [0] == a_mode)  n = s_opts [i].o_offset;
      else if (l > 1 && p [1] != '·' && p [1] == a_mode)  n = s_opts [i].o_offset;
      else if (l > 2 && p [2] != '·' && p [2] == a_mode)  n = s_opts [i].o_offset;
      if (n >= 0) {
         DEBUG_YJOBS  yLOG_value   ("FOUND"     , n);
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return n;
}

char
yJOBS_noise             (char a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char       *a           = NULL;          /* current argument               */
   char        l           =    0;
   int         j           =    0;
   char       *p           = NULL;
   char        x_noise     =  '?';
   char        x_args      =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_argc"    , a_argc);
   --rce;  if (a_argc <= 1) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return x_noise;
   }
   --rce;  if (a_argv == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return x_noise;
   }
   /*---(walk args)-----------------------------*/
   --rce;  for (i = 1; i < a_argc; ++i) {
      /*---(prepare)---------------------*/
      a = a_argv [i];
      if (a == NULL) {
         DEBUG_PROG   yLOG_note    ("FATAL, found a null argument, really bad news");
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(debugging--------------------*/
      if (a [0] == '@')       continue;
      /*---(yJOBS arguments)-------------*/
      ++x_args;
      DEBUG_ARGS  yLOG_info     ("argument"  , a);
      /*---(find action)--------------------*/
      for (j = 0; j < MAX_OPTS; ++j) {
         DEBUG_YJOBS  yLOG_value   ("loop"      , j);
         p = s_opts [j].o_option;
         if (p [0] == '\0')  break;
         l = strlen (a);
         if (l >= 4 && strcmp (a + 2, p) == 0) {
            DEBUG_YJOBS  yLOG_info    ("silent"    , s_opts [j].o_option);
            if (x_noise == '?')  x_noise = '·';
            break;
         }
         if (l >= 5 && a [2] == 'c' && strcmp (a + 3, p) == 0) {
            DEBUG_YJOBS  yLOG_info    ("confirm"   , s_opts [j].o_option);
            if (x_noise != 'V')  x_noise = 'c';
            break;
         }
         if (l >= 5 && a [2] == 'v' && strcmp (a + 3, p) == 0) {
            DEBUG_YJOBS  yLOG_info    ("verbose"   , s_opts [j].o_option);
            x_noise = 'V';
            break;
         }
      }
      /*---(done)------------------------*/
   }
   DEBUG_YJOBS  yLOG_value   ("x_args"    , x_args);
   DEBUG_YJOBS  yLOG_char    ("x_noise"   , x_noise);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return x_noise;
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
      p = s_opts [j].o_option;
      if (p [0] == '\0')  break;
      if (strcmp (a_arg + 2, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("silent"    , s_opts [j].o_option);
         c = s_opts [j].o_levels [0];
         x_noise = '-';
         break;
      }
      if (a_arg [2] == 'c' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("confirm"   , s_opts [j].o_option);
         c = s_opts [j].o_levels [1];
         x_noise = 'c';
         break;
      }
      if (a_arg [2] == 'v' && strcmp (a_arg + 3, p) == 0) {
         DEBUG_YJOBS  yLOG_info    ("verbose"   , s_opts [j].o_option);
         c = s_opts [j].o_levels [2];
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
   if (n       != NULL)  *n       = s_opts [j].o_offset;
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
      DEBUG_YJOBS  yLOG_note    ("not allowed");
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
      IF_CONFIRM  yURG_err_live ();
      yURG_err ('F', "action å%sæ requires a file name as an argument", a_arg);
      IF_CONFIRM  yURG_err_mute ();
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
      yURG_msg_atmp ();
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

