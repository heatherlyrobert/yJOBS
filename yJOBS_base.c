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
   {  IAM_EOS        , IAM_UEOS       , "eos"      , "/sbin/"             , "eos-rhododactylos (rosy-fingered dawn)"            , "-·· F···F ------· ··· ·· ···· ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "eos."       , "eos."       , ".conf"      , "eos.conf"        , ""                         , ""                         , ""                    , '·' , ""                    },
   {  IAM_ASTRAIOS   , IAM_UASTRAIOS  , "astraios" , "/sbin/"             , "astraios-aeolus (sparkling wind-father)"           , "-·· F···F ------· ··· ·· ···· ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "astraios."  , "astraios."  , ".conf"      , "astraios.conf"   , ""                         , ""                         , ""                    , '·' , ""                    },
   {  IAM_HYPNOS     , IAM_UHYPNOS    , "hypnos"   , "/sbin/"             , "hypnos-epidotes (giver of sleep)"                  , "-·· F···F ------· ··· ·· ···· ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hypnos."    , "hypnos."    , ".conf"      , "hypnos.conf"     , ""                         , ""                         , ""                    , '·' , ""                    }, 
   {  IAM_HERACLES   , IAM_UHERACLES  , "heracles" , "/sbin/"             , "heracles-promachus (leader in battle)"             , "-·· F··FF ---F--· ··· ·· ·FF· ···--· -" , 'y', 'y', "/var/spool/heracles/"     , "/tmp/spool/heracles/"     , "job."       , "(USER)."    , ""           , ""                , ""                         , ""                         , ""                    , '·' , ""                    }, 
   {  IAM_KHRONOS    , IAM_UKHRONOS   , "khronos"  , "/usr/sbin/"         , "khronos-anileis (merciless time)"                  , "--· F···F ---F--· ··· ·· ·FF· ·----- -" , 'y', 'y', "/var/spool/khronos/"      , "/tmp/spool/khronos/"      , "khronos."   , "(USER)."    , ""           , ""                , "/var/lib/khronos/"        , "/tmp/lib/khronos/"        , ""                    , '·' , ""                    }, 
   {  IAM_POLYMNIA   , IAM_UPOLYMNIA  , "polymnia" , "/usr/local/bin/"    , "polymnia-hymnos (many praises)"                    , "--· FFFFF -·F·--· ··· ·· ---· -··--· -" , '·', '·', ""                         , ""                         , ""           , ""           , ""           , ""                , "/var/lib/polymnia/"       , "/tmp/lib/polymnia/"       , "world.ctrl"          , 'U' , "polymnia.db"         }, 
   {  IAM_METIS      , IAM_UMETIS     , "metis"    , "/usr/local/bin/"    , "metis-okeanides (wise-counsel)"                    , "-·· FFFFF -·F·--· ··· ·· FFF· -··--· -" , 'y', '·', ""                         , ""                         , ""           , ""           , ".tasks"     , ""                , "/var/lib/metis/"          , "/tmp/lib/metis/"          , "world.ctrl"          , 'o' , "metis.db"            },
   {  IAM_HELIOS     , IAM_UHELIOS    , "helios"   , "/usr/bin/"          , "helios-phaeton (radiant)"                          , "-·· F···F ---·--· ··· ·· ···· -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "helios."    , "helios."    , ".conf"      , "helios.conf"     , "/var/lib/helios/"         , "/tmp/lib/helios/"         , ""                    , 'o' , "helios.db"           }, 
   {  IAM_HERMES     , IAM_UHERMES    , "hermes"   , "/sbin/"             , "hermes-diactoros (messenger of gods)"              , "-·· F···F --F·--· ··· ·· ···· -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hermes."    , "hermes."    , ".conf"      , "hermes.conf"     , "/var/lib/hermes/"         , "/tmp/lib/hermes/"         , ""                    , 'o' , "hermes.db"           }, 
   {  IAM_THEMIS     , IAM_UTHEMIS    , "themis"   , "/sbin/"             , "themis-euboulos (divine law)"                      , "-·· F···F --F·--· ··· ·· ···· -··--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "themis."    , "themis."    , ".conf"      , "themis.conf"     , "/var/lib/themis/"         , "/tmp/lib/themis/"         , ""                    , 'o' , "themis.db"           }, 
   {  IAM_GREGG      , IAM_UGREGG     , "gregg"    , "/usr/local/bin/"    , "athene-makhanitis (skilled inventor)"              , "-·· ·FF·· --FF--F ··· ·· FF·· -··--· -" , 'y', 'y', "/var/lib/gregg/"          , "/tmp/lib/gregg/"          , ""           , ""           , ".dict"      , ""                , "/var/lib/gregg/"          , "/tmp/lib/gregg/"          , ""                    , '·' , "gregg.db"            }, 
   {  IAM_OUROBOROS  , IAM_UOUROBOROS , "ouroboros", "/usr/local/bin/"    , "ouroboros-aperantos (tail-eater)"                  , "--· FF·F· -·F·--· ··· ·· ···· -··--· -" , '·', '·', ""                         , ""                         , ""           , ""           , ""           , ""                , "/var/lib/polymnia/"       , "/tmp/lib/polymnia/"       , "world.ctrl"          , '·' , "ouroboros.tdb"       }, 
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
      if (g_whos [i].w_abbr == 0)         break;
      sprintf (t, "%c", g_whos [i].w_abbr);
      ystrlcat (g_valid, t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].w_cdir) == 0) ystrlcat (g_etc, t, LEN_DESC);
      sprintf (t, "%c", g_whos [i].w_unit);
      ystrlcat (g_valid, t, LEN_DESC);
      ystrlcat (g_unit , t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].w_cdir) == 0) ystrlcat (g_etc, t, LEN_DESC);
   }
   return 0;
}

char
yjobs_who__base         (char a_runas, char *r_base, char *r_unit, char r_name [LEN_TERSE], char r_inst [LEN_LABEL], char r_desc [LEN_DESC], char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL], char *r_update, char *r_local, char *r_central, char r_lpre [LEN_LABEL], char r_cpre [LEN_LABEL], char r_lsuf [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_base    != NULL)  *r_base   = '·';
   if (r_unit    != NULL)  *r_unit   = '·';
   if (r_name    != NULL)  ystrlcpy (r_name , "", LEN_TERSE);
   if (r_inst    != NULL)  ystrlcpy (r_inst , "", LEN_TERSE);
   if (r_desc    != NULL)  ystrlcpy (r_desc , "", LEN_DESC);
   if (r_cdir    != NULL)  ystrlcpy (r_cdir , "", LEN_DESC);
   if (r_conf    != NULL)  ystrlcpy (r_conf , "", LEN_LABEL);
   if (r_hdir    != NULL)  ystrlcpy (r_hdir , "", LEN_DESC);
   if (r_db      != NULL)  ystrlcpy (r_db   , "", LEN_LABEL);
   if (r_world   != NULL)  ystrlcpy (r_world, "", LEN_LABEL);
   if (r_update  != NULL)  *r_update  = '·';
   if (r_local   != NULL)  *r_local   = '·';
   if (r_central != NULL)  *r_central = '·';
   if (r_lpre    != NULL)  ystrlcpy (r_lpre , "", LEN_LABEL);
   if (r_cpre    != NULL)  ystrlcpy (r_cpre , "", LEN_LABEL);
   if (r_lsuf    != NULL)  ystrlcpy (r_lsuf , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      /*---(filter)----------------------*/
      if (g_whos [i].w_abbr == 0)         break;
      if (a_runas != g_whos [i].w_abbr && a_runas != g_whos [i].w_unit)   continue;
      /*---(basics)----------------------*/
      if (r_base    != NULL)  *r_base   = g_whos [i].w_abbr;
      if (r_unit    != NULL)  *r_unit   = g_whos [i].w_unit;
      if (r_name    != NULL)  ystrlcpy (r_name , g_whos [i].w_name , LEN_TERSE);
      if (r_inst    != NULL)  ystrlcpy (r_inst , g_whos [i].w_inst , LEN_LABEL);
      if (r_desc    != NULL)  ystrlcpy (r_desc , g_whos [i].w_desc , LEN_DESC);
      /*---(directories)-----------------*/
      if (a_runas == g_whos [i].w_abbr) {
         if (r_cdir    != NULL)  ystrlcpy (r_cdir , g_whos [i].w_cdir , LEN_DESC);
         if (r_hdir    != NULL)  ystrlcpy (r_hdir , g_whos [i].w_hdir , LEN_DESC);
      } else {
         if (r_cdir    != NULL)  ystrlcpy (r_cdir , g_whos [i].w_ucdir, LEN_DESC);
         if (r_hdir    != NULL)  ystrlcpy (r_hdir , g_whos [i].w_uhdir, LEN_DESC);
      }
      /*---(major files)-----------------*/
      if (r_conf    != NULL)  ystrlcpy (r_conf , g_whos [i].w_conf , LEN_LABEL);
      if (r_db      != NULL)  ystrlcpy (r_db   , g_whos [i].w_db   , LEN_LABEL);
      if (r_world   != NULL)  ystrlcpy (r_world, g_whos [i].w_world, LEN_LABEL);
      /*---(specifics)-------------------*/
      if (r_update  != NULL)  *r_update  = g_whos [i].w_update;
      if (r_local   != NULL)  *r_local   = g_whos [i].w_local;
      if (r_central != NULL)  *r_central = g_whos [i].w_central;
      if (r_lpre    != NULL)  ystrlcpy (r_lpre , g_whos [i].w_lpre , LEN_LABEL);
      if (r_cpre    != NULL)  ystrlcpy (r_cpre , g_whos [i].w_cpre , LEN_LABEL);
      if (r_lsuf    != NULL)  ystrlcpy (r_lsuf , g_whos [i].w_lsuf , LEN_LABEL);
      /*---(done)------------------------*/
      return 0;
   }
   /*---(complete)-----------------------*/
   return rce;
}

char
yjobs_who_naming        (char a_runas, char *r_local, char *r_central, char r_lpre [LEN_LABEL], char r_cpre [LEN_LABEL], char r_lsuf [LEN_LABEL], char r_conf [LEN_LABEL])
{
   return yjobs_who__base (a_runas, NULL, NULL, NULL, NULL, NULL, NULL, r_conf, NULL, NULL, NULL, NULL, r_local, r_central, r_lpre, r_cpre, r_lsuf);
}

char
yJOBS_configured        (char a_runas, char *r_unit, char r_name [LEN_TERSE], char r_desc [LEN_DESC], char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL])
{
   return yjobs_who__base (a_runas, NULL, r_unit, r_name, NULL, r_desc, r_cdir, r_conf, r_hdir, r_db, r_world, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yjobs_who_location      (char a_runas, char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL])
{
   return yjobs_who__base (a_runas, NULL, NULL, NULL, NULL, NULL, r_cdir, r_conf, r_hdir, r_db, r_world, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yjobs_who_base          (char a_runas, char *r_base)
{
   return yjobs_who__base (a_runas, r_base, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yjobs_who_by_index      (char n, char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , "", LEN_DESC);
   if (r_conf  != NULL)  ystrlcpy (r_conf , "", LEN_LABEL);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , "", LEN_DESC);
   if (r_world != NULL)  ystrlcpy (r_world, "", LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].w_abbr == 0)       break;
      if (i != n)                       continue;
      return yjobs_who__base (g_whos [i].w_unit, NULL, NULL, NULL, NULL, NULL, r_cdir, r_conf, r_hdir, r_db, r_world, NULL, NULL, NULL, NULL, NULL, NULL);
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
      if (g_whos [i].w_abbr == 0)         break;
      if      (a_runas == g_whos [i].w_abbr || a_runas == g_whos [i].w_unit) {
         return g_whos [i].w_acts [a_opt];
      }
   }
   /*---(complete)-----------------------*/
   return '·';
}

char
yjobs_who_by_action     (char a_runas, char a_mode, char a_label [LEN_TERSE])
{
   char        rc          =    0;
   char        n           =    0;
   n  = yjobs_args_offset (a_mode);
   rc = yjobs_who_action (a_runas, n);
   if (rc == '-')  rc = a_mode;
   if (rc == '·')  rc = '-';
   yENV_score_mark (a_label, rc);
   if (rc == '-')  return 1;
   return 0;
}

char
yjobs_who_testing       (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].w_abbr == 0)         break;
      if      (a_runas == g_whos [i].w_abbr || a_runas == g_whos [i].w_unit) {
         return g_whos [i].w_unit;
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
yjobs_runas             (char a_name [LEN_TERSE], char *r_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_qual      [LEN_HUND]  = "";
   char        x_debug     [LEN_HUND]  = "";
   char        x_quald     [LEN_HUND]  = "";
   char        x_unit      [LEN_HUND]  = "";
   char        x_base      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(scoring)------------------------*/
   yjobs_ends_init ();
   yENV_score_mark ("RUNAS"    , G_SCORE_FAIL);
   yENV_score_mark ("ENV"      , '·');
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
      yENV_score_mark ("JUDGE"    , G_SCORE_FAIL);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_name"    , a_name);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].w_abbr == 0) {
         DEBUG_YJOBS  yLOG_note    ("runas entry never found");
         yENV_score_mark ("JUDGE"    , G_SCORE_FAIL);
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(naming)----------------------*/
      sprintf (x_qual , "%s%s"   , g_whos [i].w_inst, g_whos [i].w_name);
      sprintf (x_debug, "%s_debug", g_whos [i].w_name);
      sprintf (x_quald, "%s%s_debug"   , g_whos [i].w_inst, g_whos [i].w_name);
      sprintf (x_unit , "%s_unit", g_whos [i].w_name);
      DEBUG_YJOBS  yLOG_complex ("naming"    , "%s, %s, %s, %s, %s, %s", g_whos [i].w_inst, g_whos [i].w_name, x_qual, x_debug, x_quald, x_unit);
      /*---(normal)----------------------*/
      if (strcmp (a_name, g_whos [i].w_name) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].w_name, g_whos [i].w_abbr, g_whos [i].w_unit);
         myJOBS.m_runas = g_whos [i].w_abbr;
         DEBUG_YJOBS  yLOG_char    ("normal"    , myJOBS.m_runas);
         break;
      }
      /*---(qualified)-------------------*/
      if (strcmp (a_name, x_qual) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].w_name, g_whos [i].w_abbr, g_whos [i].w_unit);
         myJOBS.m_runas = g_whos [i].w_abbr;
         DEBUG_YJOBS  yLOG_char    ("qualified" , myJOBS.m_runas);
         break;
      }
      /*---(debug)-----------------------*/
      if (strcmp (a_name, x_debug) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].w_name, g_whos [i].w_abbr, g_whos [i].w_unit);
         myJOBS.m_runas = g_whos [i].w_abbr;
         DEBUG_YJOBS  yLOG_char    ("debug"     , myJOBS.m_runas);
         yENV_score_mark ("ENV"      , 'd');
         break;
      }
      /*---(qualified)-------------------*/
      if (strcmp (a_name, x_quald) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].w_name, g_whos [i].w_abbr, g_whos [i].w_unit);
         myJOBS.m_runas = g_whos [i].w_abbr;
         DEBUG_YJOBS  yLOG_char    ("qualified" , myJOBS.m_runas);
         yENV_score_mark ("ENV"      , 'd');
         break;
      }
      /*---(unittest)--------------------*/
      if (strcmp (a_name, x_unit) == 0) {
         DEBUG_YJOBS  yLOG_complex ("found"     , "%s, normal=%c, unittest=%c", g_whos [i].w_name, g_whos [i].w_abbr, g_whos [i].w_unit);
         myJOBS.m_runas = g_whos [i].w_unit;
         DEBUG_YJOBS  yLOG_char    ("unittest"  , myJOBS.m_runas);
         yENV_score_mark ("ENV"      , 'u');
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(score)--------------------------*/
   yjobs_args_data (myJOBS.m_runas, NULL, &x_base, NULL, NULL, NULL);
   if (x_base != '-')  yENV_score_mark ("RUNAS"    , x_base);
   yjobs_runas_masking (myJOBS.m_runas);
   /*---(save-back)----------------------*/
   if (r_runas != NULL)  *r_runas = myJOBS.m_runas;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_runas_masking         (char a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_conf      [LEN_LABEL] = "";
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        c           =   0;
   /*---(masking)------------------------*/
   rc = yjobs_who_location (a_runas, x_cdir, x_conf, x_hdir, x_db, x_world);
   if      (strcmp  (x_cdir , "") == 0)         yENV_score_mask ("CFá ", "FLIST");
   else {
      if (strstr (x_cdir , "/etc/") != NULL)    yENV_score_mark ("FSTYLE"  , 'e');
      else                                      yENV_score_mark ("FSTYLE"  , 's');
      if      (strcmp (x_conf, "") == 0)        yENV_score_mark ("FCOUNT"  , '*');
      else                                      yENV_score_mark ("FCOUNT"  , '1');
   }
   if (strcmp (x_hdir , "") == 0)   yENV_score_mask ("CDá ", "CAUDIT");
   if (strcmp (x_world, "") == 0)   yENV_score_mask ("WOá ", "WWRITE");
   if (strcmp (x_db   , "") == 0)   yENV_score_mask ("DBá ", "DWRITE");
   /*---(actions)------------------------*/
   c = 0;
   c += yjobs_who_by_action (a_runas, 'g', "GATHER");
   c += yjobs_who_by_action (a_runas, 'n', "NORMAL");
   c += yjobs_who_by_action (a_runas, 'd', "DAEMON");
   if (c == 3)  yENV_score_mask ("ACá ", "DAEMON");
   /*---(backend)------------------------*/
   c = 0;
   c += yjobs_who_by_action (a_runas, 'e', "EXTRACT");
   c += yjobs_who_by_action (a_runas, 'y', "UPLOAD");
   c += yjobs_who_by_action (a_runas, 'k', "BACKUP");
   c += yjobs_who_by_action (a_runas, 'z', "DOWNLOAD");
   c += yjobs_who_by_action (a_runas, 't', "RESTORE");
   if (c == 5)  yENV_score_mask ("BEá ", "RESTORE");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_runas             (char a_name [LEN_TERSE], char *r_runas, ...)
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
      if (g_whos [i].w_abbr == 0) g_print;
      if (a_runas == g_whos [i].w_abbr || a_runas == g_whos [i].w_unit) {
         ystrlcpy (g_print, g_whos [i].w_desc, LEN_HUND);
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





