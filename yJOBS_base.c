/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


tLOCAL myJOBS = { '-', '-' };


/*
 *
 *       ƒ€€€€€€€€€€€€€€€€€€€ 11 system daemon/utils designed for yJOBS €€€€€€€€€€€€€€€€€€€€€€€‚
 *       Œ                                                                                     Œ
 *       Œ  eos           system start-up             eos-rhododactylos (rosy-fingered dawn)   Œ
 *       Œ  astraios      system shut-down            astraios-aeolus (sparkling wind-father)  Œ
 *       Œ  hypnos        system hybernation          hypnos-epidotes (giver of sleep)         Œ
 *       Œ                                                                                     Œ
 *       Œ  heracles      requested job execution     heracles-promachus (leader in battle)    Œ
 *       Œ  khronos       scheduled job execution     khronos-anileis (merciless time)         Œ
 *       Œ                                                                                     Œ
 *       Œ  polymnia      source code analysis        polymnia-hymnos (many praises)           Œ
 *       Œ  metis         task management             metis-okeanides (wise-counsel)           Œ
 *       Œ  ouroboros     test sequencer              ouroboros-aperantos (tail-eater)         Œ
 *       Œ                                                                                     Œ
 *       Œ  helios        file location               helios-phaeton (radiant)                 Œ
 *       Œ  hermes        executable control          hermes-diactoros (messenger of gods)     Œ
 *       Œ  themis        configuration control       themis-euboulos (divine law)             Œ
 *       Œ                                                                                     Œ
 *       ‡€€€€€€€€€€€€€€€€€€€€ examples of specifically excluded daemons €€€€€€€€€€€€€€€€€€€€€€†
 *       Œ                                                                                     Œ
 *       Œ  kharon        process one                 kharon-charopos (the ferryman)           Œ
 *       Œ  hestia        getty daemon                hestia-polyolbos (full of blessings)     Œ
 *       Œ                                                                                     Œ
 *       „€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€…
 *
 *
 *
 */

const tWHO  g_whos [MAX_WHO] = {
   /* primary--------  unittest-------  name------ , installed----------- , description----------------------------------------    allowed-actions-----------------  */
   /* 123456789-12345, 123456789-12345,  123456789 ,  123456789-123456789 ,  123456789-123456789-123456789-123456789-123456789- ,  123 vlbui #=mcafo ktw yz qxre gdpnsh -  , loc  cen  ---config-dir------------- , ---testing-dir------------   lpre--------   cpre--------   lsuf--------   cname------------   home-dir------------------ , unit-home-dir------------- , world-file----------- , upd ,  database------------ , */
   {  IAM_EOS        , IAM_UEOS       , "eos"      , "/sbin/"             , "eos-rhododactylos (rosy-fingered dawn)"            , "-·· F··FF ···---· ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "eos."       , "eos."       , ".conf"      , "eos.conf"        , ""                         , ""                         , ""                    , '·' , ""                    },
   {  IAM_ASTRAIOS   , IAM_UASTRAIOS  , "astraios" , "/sbin/"             , "astraios-aeolus (sparkling wind-father)"           , "-·· F··FF ···---· ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "astraios."  , "astraios."  , ".conf"      , "astraios.conf"   , ""                         , ""                         , ""                    , '·' , ""                    },
   {  IAM_HYPNOS     , IAM_UHYPNOS    , "hypnos"   , "/sbin/"             , "hypnos-epidotes (giver of sleep)"                  , "-·· F··FF ···---· ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hypnos."    , "hypnos."    , ".conf"      , "hypnos.conf"     , ""                         , ""                         , ""                    , '·' , ""                    }, 
   {  IAM_HERACLES   , IAM_UHERACLES  , "heracles" , "/sbin/"             , "heracles-promachus (leader in battle)"             , "-·· F··FF --·F--· ··· ·· ·FFF ···--· -" , 'y', 'y', "/var/spool/heracles/"     , "/tmp/spool/heracles/"     , "job."       , "(USER)."    , ""           , ""                , ""                         , ""                         , ""                    , '·' , ""                    }, 
   {  IAM_KHRONOS    , IAM_UKHRONOS   , "khronos"  , "/usr/sbin/"         , "khronos-anileis (merciless time)"                  , "--· F··FF --FF--· ··· ·· ·FFF ·----- -" , 'y', 'y', "/var/spool/khronos/"      , "/tmp/spool/khronos/"      , "khronos."   , "(USER)."    , ""           , ""                , "/var/lib/khronos/"        , "/tmp/lib/khronos/"        , ""                    , '·' , ""                    }, 
   {  IAM_POLYMNIA   , IAM_UPOLYMNIA  , "polymnia" , "/usr/local/bin/"    , "polymnia-hymnos (many praises)"                    , "--· FFFFF --F·--· ··· ·· ---· -··--· -" , '·', '·', ""                         , ""                         , ""           , ""           , ""           , ""                , "/var/lib/polymnia/"       , "/tmp/lib/polymnia/"       , "world.ctrl"          , 'U' , "polymnia.db"         }, 
   {  IAM_METIS      , IAM_UMETIS     , "metis"    , "/usr/local/bin/"    , "metis-okeanides (wise-counsel)"                    , "-·· FFFFF --F---· ··· ·· FFFF -··--· -" , 'y', '·', ""                         , ""                         , ""           , ""           , ".tasks"     , ""                , "/var/lib/metis/"          , "/tmp/lib/metis/"          , "world.ctrl"          , 'o' , "metis.db"            },
   {  IAM_HELIOS     , IAM_UHELIOS    , "helios"   , "/usr/bin/"          , "helios-phaeton (radiant)"                          , "-·· F··FF -·----· ··· ·· ···- -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "helios."    , "helios."    , ".conf"      , "helios.conf"     , "/var/lib/helios/"         , "/tmp/lib/helios/"         , ""                    , 'o' , "helios.db"           }, 
   {  IAM_HERMES     , IAM_UHERMES    , "hermes"   , "/sbin/"             , "hermes-diactoros (messenger of gods)"              , "-·· F··FF -·F---· ··· ·· ···- -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hermes."    , "hermes."    , ".conf"      , "hermes.conf"     , "/var/lib/hermes/"         , "/tmp/lib/hermes/"         , ""                    , 'o' , "hermes.db"           }, 
   {  IAM_THEMIS     , IAM_UTHEMIS    , "themis"   , "/sbin/"             , "themis-euboulos (divine law)"                      , "-·· F··FF -·F---· ··· ·· ···- -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "themis."    , "themis."    , ".conf"      , "themis.conf"     , "/var/lib/themis/"         , "/tmp/lib/themis/"         , ""                    , 'o' , "themis.db"           }, 
   {  IAM_GREGG      , IAM_UGREGG     , "gregg"    , "/usr/local/bin/"    , "athene-makhanitis (skilled inventor)"              , "-·· ·FF·· --FF--F ··· ·· F··· -··--· -" , 'y', 'y', "/var/lib/gregg/"          , "/tmp/lib/gregg/"          , ""           , ""           , ".dict"      , ""                , "/var/lib/gregg/"          , "/tmp/lib/gregg/"          , "world.ctrl"          , '·' , "gregg.db"            }, 
   {  IAM_OUROBOROS  , IAM_UOUROBOROS , "ouroboros", "/usr/local/bin/"    , "ouroboros-aperantos (tail-eater)"                  , "--· FF·F· ------· ··· ·· ···· -··--· -" , '·', '·', ""                         , ""                         , ""           , ""           , ""           , ""                , "/var/lib/polymnia/"       , "/tmp/lib/polymnia/"       , "world.ctrl"          , '·' , "ouroboros.tdb"       }, 
   {  0              , 0              , "--end--"  , "--end--"            , "--end--"                                           , "··· ····· ······· ··· ·· ···· ······ ·" , '·', '·', "--end--"                  , "--end--"                  , ""           , ""           , ""           , ""                , ""                         , ""                         , ""                    , '·' , ""                    }, 
};

static const char *g_nada = "";


/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY____________o (void) {;}

static char yJOBS_ver [LEN_HUND] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yJOBS_version      (void)
{
   char        t [LEN_LABEL] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", LEN_LABEL);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", LEN_LABEL);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", LEN_LABEL);
#else
   strncpy (t, "[unknown    ]", LEN_LABEL);
#endif
   snprintf (yJOBS_ver, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yJOBS_ver;
}



/*====================------------------------------------====================*/
/*===----                      who table access                        ----===*/
/*====================------------------------------------====================*/
static void      o___WHO_TABLE__________o (void) {;}

char
yjobs_who_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   /*---(default)------------------------*/
   ystrlcat (g_valid   , "", LEN_DESC);
   ystrlcat (g_unit    , "", LEN_DESC);
   ystrlcat (g_etc     , "", LEN_DESC);
   /*---(load)---------------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      sprintf (t, "%c", g_whos [i].abbr);
      ystrlcat (g_valid, t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].cdir) == 0) ystrlcat (g_etc, t, LEN_DESC);
      sprintf (t, "%c", g_whos [i].unit);
      ystrlcat (g_valid, t, LEN_DESC);
      ystrlcat (g_unit , t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].cdir) == 0) ystrlcat (g_etc, t, LEN_DESC);
   }
   return 0;
}

char
yjobs_who_naming        (cchar a_runas, char *a_local, char *a_central, char *a_lpre, char *a_cpre, char *a_lsuf, char *a_cname)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (a_local   != NULL)  *a_local   = '·';
   if (a_central != NULL)  *a_central = '·';
   if (a_lpre    != NULL)  ystrlcpy (a_lpre , "", LEN_LABEL);
   if (a_cpre    != NULL)  ystrlcpy (a_cpre , "", LEN_LABEL);
   if (a_lsuf    != NULL)  ystrlcpy (a_lsuf , "", LEN_LABEL);
   if (a_cname   != NULL)  ystrlcpy (a_cname, "", LEN_DESC);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if      (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         if (a_local   != NULL)  *a_local   = g_whos [i].local;
         if (a_central != NULL)  *a_central = g_whos [i].central;
         if (a_lpre    != NULL)  ystrlcpy (a_lpre , g_whos [i].lpre , LEN_LABEL);
         if (a_cpre    != NULL)  ystrlcpy (a_cpre , g_whos [i].cpre , LEN_LABEL);
         if (a_lsuf    != NULL)  ystrlcpy (a_lsuf , g_whos [i].lsuf , LEN_LABEL);
         if (a_cname   != NULL)  ystrlcpy (a_cname, g_whos [i].cname, LEN_LABEL);
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   return rce;
}

char
yjobs_who_location      (cchar a_runas, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char *r_update, char r_db [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_cdir   != NULL)  ystrlcpy (r_cdir , "", LEN_DESC);
   if (r_hdir   != NULL)  ystrlcpy (r_hdir , "", LEN_DESC);
   if (r_world  != NULL)  ystrlcpy (r_world, "", LEN_LABEL);
   if (r_update != NULL)  *r_update = '·';
   if (r_db     != NULL)  ystrlcpy (r_db   , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if (a_runas == g_whos [i].abbr) {
         if (r_cdir   != NULL)  ystrlcpy (r_cdir , g_whos [i].cdir , LEN_DESC);
         if (r_hdir   != NULL)  ystrlcpy (r_hdir , g_whos [i].hdir , LEN_DESC);
         if (r_world  != NULL)  ystrlcpy (r_world, g_whos [i].world, LEN_LABEL);
         if (r_update != NULL)  *r_update = g_whos [i].update;
         if (r_db     != NULL)  ystrlcpy (r_db   , g_whos [i].db   , LEN_LABEL);
         return 0;
      }
      if (a_runas == g_whos [i].unit) {
         if (r_cdir   != NULL)  ystrlcpy (r_cdir , g_whos [i].udir , LEN_DESC);
         if (r_hdir   != NULL)  ystrlcpy (r_hdir , g_whos [i].uhdir, LEN_DESC);
         if (r_world  != NULL)  ystrlcpy (r_world, g_whos [i].world, LEN_LABEL);
         if (r_update != NULL)  *r_update = g_whos [i].update;
         if (r_db     != NULL)  ystrlcpy (r_db   , g_whos [i].db   , LEN_LABEL);
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   return rce;
}

char
yjobs_who_by_index      (char n, char *a_cdir, char *a_hdir, char *a_world, char *a_db)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (a_cdir  != NULL)  ystrlcpy (a_cdir , "", LEN_DESC);
   if (a_hdir  != NULL)  ystrlcpy (a_hdir , "", LEN_DESC);
   if (a_world != NULL)  ystrlcpy (a_world, "", LEN_LABEL);
   if (a_db    != NULL)  ystrlcpy (a_db   , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if (i != n)                       continue;
      if (a_cdir  != NULL)  ystrlcpy (a_cdir , g_whos [i].udir , LEN_DESC);
      if (a_hdir  != NULL)  ystrlcpy (a_hdir , g_whos [i].uhdir, LEN_DESC);
      if (a_world != NULL)  ystrlcpy (a_world, g_whos [i].world, LEN_LABEL);
      if (a_db    != NULL)  ystrlcpy (a_db   , g_whos [i].db   , LEN_LABEL);
      return 0;
   }
   /*---(complete)-----------------------*/
   return rce;
}

char
yjobs_who_action        (cchar a_runas, cchar a_opt)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(defense)------------------------*/
   if (a_opt <  0)  return '·';
   if (a_opt > 35)  return '·';
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if      (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         return g_whos [i].acts [a_opt];
      }
   }
   /*---(complete)-----------------------*/
   return '·';
}

char
yjobs_who_testing       (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if      (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         return g_whos [i].unit;
      }
   }
   /*---(complete)-----------------------*/
   return '?';
}



/*====================------------------------------------====================*/
/*===----                      simple identification                   ----===*/
/*====================------------------------------------====================*/
static void      o___IDENTIFY___________o (void) {;};

char
yjobs_runas             (cchar *a_name, char *r_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_qual      [LEN_HUND]  = "";
   char        x_debug     [LEN_HUND]  = "";
   char        x_quald     [LEN_HUND]  = "";
   char        x_unit      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   myJOBS.m_runas   = IAM_DEFAULT;
   if (r_runas != NULL)  *r_runas = IAM_DEFAULT;
   /*---(prepare)------------------------*/
   rc = yjobs_world_init ();
   DEBUG_YJOBS  yLOG_point   ("world"     , rc);
   rc = yjobs_args_init (r_runas, NULL, NULL);
   DEBUG_YJOBS  yLOG_point   ("args"      , rc);
   /*---(clear summary)------------------*/
   for (i = 0; i < MAX_SUMM; ++i)   myJOBS.m_summary [i] = g_nada;
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_name"    , a_name);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0) {
         DEBUG_YJOBS  yLOG_note    ("runas entry never found");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(naming)----------------------*/
      sprintf (x_qual , "%s%s"   , g_whos [i].inst, g_whos [i].name);
      sprintf (x_debug, "%s_debug", g_whos [i].name);
      sprintf (x_quald, "%s%s_debug"   , g_whos [i].inst, g_whos [i].name);
      sprintf (x_unit , "%s_unit", g_whos [i].name);
      DEBUG_YJOBS  yLOG_complex ("naming"    , "%s, %s, %s, %s, %s, %s", g_whos [i].inst, g_whos [i].name, x_qual, x_debug, x_quald, x_unit);
      /*---(normal)----------------------*/
      if (strcmp (a_name, g_whos [i].name) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].name, g_whos [i].abbr, g_whos [i].unit);
         myJOBS.m_runas = g_whos [i].abbr;
         DEBUG_YJOBS  yLOG_char    ("normal"    , myJOBS.m_runas);
         break;
      }
      /*---(qualified)-------------------*/
      if (strcmp (a_name, x_qual) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].name, g_whos [i].abbr, g_whos [i].unit);
         myJOBS.m_runas = g_whos [i].abbr;
         DEBUG_YJOBS  yLOG_char    ("qualified" , myJOBS.m_runas);
         break;
      }
      /*---(debug)-----------------------*/
      if (strcmp (a_name, x_debug) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].name, g_whos [i].abbr, g_whos [i].unit);
         myJOBS.m_runas = g_whos [i].abbr;
         DEBUG_YJOBS  yLOG_char    ("debug"     , myJOBS.m_runas);
         break;
      }
      /*---(qualified)-------------------*/
      if (strcmp (a_name, x_quald) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].name, g_whos [i].abbr, g_whos [i].unit);
         myJOBS.m_runas = g_whos [i].abbr;
         DEBUG_YJOBS  yLOG_char    ("qualified" , myJOBS.m_runas);
         break;
      }
      /*---(unittest)--------------------*/
      if (strcmp (a_name, x_unit) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].name, g_whos [i].abbr, g_whos [i].unit);
         myJOBS.m_runas = g_whos [i].unit;
         DEBUG_YJOBS  yLOG_char    ("unittest"  , myJOBS.m_runas);
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (r_runas != NULL)  *r_runas = myJOBS.m_runas;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_runas             (cchar *a_name, char *r_runas, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   va_list     x_args;
   int         i           =    0;
   char        n           =    0;
   uchar      *x_str       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(call runas)---------------------*/
   rc =  yjobs_runas (a_name, r_runas);
   DEBUG_YJOBS  yLOG_value   ("runas"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse extra data)---------------*/
   va_start   (x_args, r_runas);
   for (i = 0; i < MAX_SUMM; ++i) {
      x_str = (char *) va_arg (x_args, int*);
      if (x_str == NULL)  break;
      ++n;
      myJOBS.m_summary [i] = x_str;
      DEBUG_YJOBS  yLOG_complex ("summary"   , "%2d å%sæ", i, myJOBS.m_summary [i]);
   }
   va_end     (x_args);
   /*---(summary)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("n"         , n);
   myJOBS.m_nsummary = n;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
yjobs_iam               (char a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   ystrlcpy (g_print, "unknown"         , LEN_HUND);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0) g_print;
      if (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         ystrlcpy (g_print, g_whos [i].desc, LEN_HUND);
         break;
      }
   }
   /*---(complete)-----------------------*/
   return g_print;
}

char* yJOBS_iam  (void) { return yjobs_iam (myJOBS.m_runas); }

char*
yjobs_mode              (char a_mode)
{
   char        rce         =  -10;
   char        rc          =    0;
   ystrlcpy (g_print, "unknown (unknown)", LEN_LABEL);
   rc = yjobs_args_info         (a_mode, g_print);
   if (rc >= 0)  {
      if      (strchr (g_silent , a_mode) != NULL)  ystrlcat (g_print, " (silent)" , LEN_DESC);
      else if (strchr (g_confirm, a_mode) != NULL)  ystrlcat (g_print, " (confirm)", LEN_DESC);
      else if (strchr (g_verbose, a_mode) != NULL)  ystrlcat (g_print, " (verbose)", LEN_DESC);
      else                                          ystrlcat (g_print, " (unknown)", LEN_DESC);
   }
   return g_print;
}

char* yJOBS_mode (void) { return yjobs_mode (myJOBS.m_mode); }

char
yJOBS_wrap              (void)
{
   yjobs_world__purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST___________o (void) {;};

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
      ystrlcpy (s, yJOBS_iam  (), LEN_RECD);
      ystrlcpy (t, yJOBS_mode (), LEN_RECD);
      snprintf (unit_answer, LEN_RECD, "BASE mode        : iam (%c) %-18.18s, run (%c) %-18.18s, å%sæ", myJOBS.m_runas, s, myJOBS.m_mode, t, myJOBS.m_file);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}





