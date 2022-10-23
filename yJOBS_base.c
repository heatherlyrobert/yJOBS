/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


tLOCAL myJOBS;


const tWHO  g_whos [MAX_WHO] = {
   /* primary--------  unittest-------  name------ , installed----------- , description----------------------------------------    allowed-actions-----------------  */
   /* 123456789-12345, 123456789-12345,  123456789 ,  123456789-123456789 ,  123456789-123456789-123456789-123456789-123456789- ,  123 vbui lLòcaf ktw yz qxre gdpnsh -  , loc  cen   123456789-123456789-12345 ,  123456789-123456789-12345   lpre--------   cpre--------   lsuf--------   cname------------   home-dir------------------ , unit-home-dir------------- , world-file----------- ,  database------------ , */
   {  IAM_EOS        , IAM_UEOS       , "eos"      , "/sbin/"             , "eos-rhododactylos (rosy-fingered dawn)"            , "--· F··F ···--- ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "eos."       , "eos."       , ".conf"      , "eos.conf"        , ""                         , ""                         , ""                    , ""                    },
   {  IAM_ASTRAIOS   , IAM_UASTRAIOS  , "astraios" , "/sbin/"             , "astraios-aeolus (sparkling wind-father)"           , "--· F··F ···--- ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "astraios."  , "astraios."  , ".conf"      , "astraios.conf"   , ""                         , ""                         , ""                    , ""                    },
   {  IAM_HYPNOS     , IAM_UHYPNOS    , "hypnos"   , "/sbin/"             , "hypnos-epidotes (giver of sleep)"                  , "--· F··F ···--- ··· ·· ···- ···--· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hypnos."    , "hypnos."    , ".conf"      , "hypnos.conf"     , ""                         , ""                         , ""                    , ""                    }, 
   {  IAM_HERACLES   , IAM_UHERACLES  , "heracles" , "/sbin/"             , "heracles-promachus (leader in battle)"             , "--- F··F --·F-- ··· ·· ·FFF ···--· -" , 'y', 'y', "/var/spool/heracles/"     , "/tmp/spool/heracles/"     , "job."       , "(USER)."    , ""           , ""                , ""                         , ""                         , ""                    , ""                    }, 
   {  IAM_KHRONOS    , IAM_UKHRONOS   , "khronos"  , "/sbin/"             , "khronos-anileis (merciless time)"                  , "--- F··F --·F-- ··· ·· ·FFF ·----- -" , 'y', 'y', "/var/spool/khronos/"      , "/tmp/spool/khronos/"      , "khronos."   , "(USER)."    , ""           , ""                , ""                         , ""                         , ""                    , ""                    }, 
   {  IAM_POLYMNIA   , IAM_UPOLYMNIA  , "polymnia" , "/usr/local/bin/"    , "polymnia-hymnos (many praises)"                    , "-·- ---- ··F--- ··· ·· ---· -····· -" , '·', '·', ""                         , ""                         , ""           , ""           , ""           , ""                , "/var/lib/polymnia/"       , "/tmp/lib/polymnia/"       , "world.txt"           , "polymnia.db"         }, 
   {  IAM_METIS      , IAM_UMETIS     , "metis"    , "/usr/local/bin/"    , "metis-okeanides (wise-counsel)"                    , "-·- FFFF ··F--- ··· ·· FFFF ------ -" , 'y', '·', ""                         , ""                         , ""           , ""           , ".tasks"     , ""                , "/var/lib/metis/"          , "/tmp/lib/metis/"          , "world.txt"           , "metis.db"            },
   {  IAM_HELIOS     , IAM_UHELIOS    , "helios"   , "/sbin/"             , "helios-phaeton (radiant)"                          , "-·- F··F ···--- ··· ·· ···- -····· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "helios."    , "helios."    , ".conf"      , "helios.conf"     , "/var/lib/helios/"         , "/tmp/lib/helios/"         , ""                    , "helios.db"           }, 
   {  IAM_HERMES     , IAM_UHERMES    , "hermes"   , "/sbin/"             , "hermes-diactoros (messenger of gods)"              , "-·- F··F ···--- ··· ·· ···- -····· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "hermes."    , "hermes."    , ".conf"      , "hermes.conf"     , "/var/lib/hermes/"         , "/tmp/lib/hermes/"         , ""                    , ""                    }, 
   {  IAM_THEMIS     , IAM_UTHEMIS    , "themis"   , "/sbin/"             , "themis-euboulos (divine law)"                      , "-·- F··F ···--- ··· ·· ···- -····· -" , 'y', 'y', "/etc/"                    , "/tmp/etc/"                , "themis."    , "themis."    , ".conf"      , "themis.conf"     , "/var/lib/themis/"         , "/tmp/lib/themis/"         , ""                    , ""                    }, 
   {  0              , 0              , "--end--"  , "--end--"            , "--end--"                                           , "··· ···· ······ ··· ·· ···· ······ ·" , '·', '·', "--end--"                  , "--end--"                  , ""           , ""           , ""           , ""                , ""                         , ""                         , ""                    , ""                    }, 
};



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

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
static void      o___WHO_TABLE_______________o (void) {;}

char
yjobs_who_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   /*---(default)------------------------*/
   strlcat (g_valid   , "", LEN_DESC);
   strlcat (g_unit    , "", LEN_DESC);
   strlcat (g_etc     , "", LEN_DESC);
   /*---(load)---------------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      sprintf (t, "%c", g_whos [i].abbr);
      strlcat (g_valid, t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].cdir) == 0) strlcat (g_etc, t, LEN_DESC);
      sprintf (t, "%c", g_whos [i].unit);
      strlcat (g_valid, t, LEN_DESC);
      strlcat (g_unit , t, LEN_DESC);
      if (strcmp ("/etc/", g_whos [i].cdir) == 0) strlcat (g_etc, t, LEN_DESC);
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
   if (a_lpre    != NULL)  strlcpy (a_lpre , "", LEN_LABEL);
   if (a_cpre    != NULL)  strlcpy (a_cpre , "", LEN_LABEL);
   if (a_lsuf    != NULL)  strlcpy (a_lsuf , "", LEN_LABEL);
   if (a_cname   != NULL)  strlcpy (a_cname, "", LEN_DESC);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if      (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         if (a_local   != NULL)  *a_local   = g_whos [i].local;
         if (a_central != NULL)  *a_central = g_whos [i].central;
         if (a_lpre    != NULL)  strlcpy (a_lpre , g_whos [i].lpre , LEN_LABEL);
         if (a_cpre    != NULL)  strlcpy (a_cpre , g_whos [i].cpre , LEN_LABEL);
         if (a_lsuf    != NULL)  strlcpy (a_lsuf , g_whos [i].lsuf , LEN_LABEL);
         if (a_cname   != NULL)  strlcpy (a_cname, g_whos [i].cname, LEN_LABEL);
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   return rce;
}

char
yjobs_who_location      (cchar a_runas, char *a_cdir, char *a_hdir, char *a_world, char *a_db)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (a_cdir  != NULL)  strlcpy (a_cdir , "", LEN_DESC);
   if (a_hdir  != NULL)  strlcpy (a_hdir , "", LEN_DESC);
   if (a_world != NULL)  strlcpy (a_world, "", LEN_LABEL);
   if (a_db    != NULL)  strlcpy (a_db   , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if (a_runas == g_whos [i].abbr) {
         if (a_cdir  != NULL)  strlcpy (a_cdir , g_whos [i].cdir , LEN_DESC);
         if (a_hdir  != NULL)  strlcpy (a_hdir , g_whos [i].hdir , LEN_DESC);
         if (a_world != NULL)  strlcpy (a_world, g_whos [i].world, LEN_LABEL);
         if (a_db    != NULL)  strlcpy (a_db   , g_whos [i].db   , LEN_LABEL);
         return 0;
      }
      if (a_runas == g_whos [i].unit) {
         if (a_cdir  != NULL)  strlcpy (a_cdir , g_whos [i].udir , LEN_DESC);
         if (a_hdir  != NULL)  strlcpy (a_hdir , g_whos [i].uhdir, LEN_DESC);
         if (a_world != NULL)  strlcpy (a_world, g_whos [i].world, LEN_LABEL);
         if (a_db    != NULL)  strlcpy (a_db   , g_whos [i].db   , LEN_LABEL);
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
   if (a_cdir  != NULL)  strlcpy (a_cdir , "", LEN_DESC);
   if (a_hdir  != NULL)  strlcpy (a_hdir , "", LEN_DESC);
   if (a_world != NULL)  strlcpy (a_world, "", LEN_LABEL);
   if (a_db    != NULL)  strlcpy (a_db   , "", LEN_LABEL);
   /*---(walk data)----------------------*/
   for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0)         break;
      if (i != n)                       continue;
      if (a_cdir  != NULL)  strlcpy (a_cdir , g_whos [i].udir , LEN_DESC);
      if (a_hdir  != NULL)  strlcpy (a_hdir , g_whos [i].uhdir, LEN_DESC);
      if (a_world != NULL)  strlcpy (a_world, g_whos [i].world, LEN_LABEL);
      if (a_db    != NULL)  strlcpy (a_db   , g_whos [i].db   , LEN_LABEL);
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
static void      o___IDENTIFY________________o (void) {;};

char
yJOBS_runas             (cchar *a_name, char *r_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        t           [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (g_runas == IAM_DEFAULT) {
      rc = yjobs_world_init ();
   }
   /*---(default)------------------------*/
   if (r_runas != NULL)  *r_runas = IAM_DEFAULT;
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
      /*---(normal)----------------------*/
      if (strcmp (a_name, g_whos [i].name) == 0) {
         DEBUG_YJOBS  yLOG_note    ("found an unqualified normal entry");
         g_runas = g_whos [i].abbr;
         break;
      }
      /*---(qualified)-------------------*/
      sprintf (t, "%s%s"   , g_whos [i].inst, g_whos [i].name);
      if (strcmp (a_name, t) == 0) {
         DEBUG_YJOBS  yLOG_note    ("found an qualified normal entry");
         g_runas = g_whos [i].abbr;
         break;
      }
      /*---(debug)-----------------------*/
      sprintf (t, "%s_debug", g_whos [i].name);
      if (strcmp (a_name, t) == 0) {
         DEBUG_YJOBS  yLOG_note    ("found a debugging entry");
         g_runas = g_whos [i].abbr;
         break;
      }
      /*---(unittest)--------------------*/
      sprintf (t, "%s_unit", g_whos [i].name);
      if (strcmp (a_name, t) == 0) {
         DEBUG_YJOBS  yLOG_note    ("found a unit testing entry");
         g_runas = g_whos [i].unit;
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (r_runas != NULL)  *r_runas = g_runas;
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
   strlcpy (g_print, "unknown"         , LEN_HUND);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i < MAX_WHO; ++i) {
      if (g_whos [i].abbr == 0) g_print;
      if (a_runas == g_whos [i].abbr || a_runas == g_whos [i].unit) {
         strlcpy (g_print, g_whos [i].desc, LEN_HUND);
         break;
      }
   }
   /*---(complete)-----------------------*/
   return g_print;
}

char* yJOBS_iam  (void) { return yjobs_iam (g_runas); }

char*
yjobs_mode              (char a_mode)
{
   char        rce         =  -10;
   char        rc          =    0;
   char        x_flag      =  '-';
   strlcpy (g_print, "unknown (unknown)", LEN_LABEL);
   rc = yjobs_args_info         (a_mode, g_print);
   if (rc >= 0)  {
      IF_SILENT         strcat (g_print, " (silent)");
      else IF_CONFIRM   strcat (g_print, " (confirm)");
      else IF_VERBOSE   strcat (g_print, " (verbose)");
      else {
         strcat (g_print, " (unknown)");
         x_flag = 'y';
      }
   }
   return g_print;
}

char* yJOBS_mode (void) { return yjobs_iam (g_runmode); }

char
yJOBS_wrap              (void)
{
   yjobs_world__purge ();
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
      strlcpy (s, yJOBS_iam  (), LEN_RECD);
      strlcpy (t, yJOBS_mode (), LEN_RECD);
      snprintf (unit_answer, LEN_RECD, "BASE mode        : iam (%c) %-18.18s, run (%c) %-18.18s, å%sæ", g_runas, s, g_runmode, t, g_runfile);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}





