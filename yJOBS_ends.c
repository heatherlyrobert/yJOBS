/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


/*
 * METIS § dv4·· § maintain audit shuold set all central files owner and perms            § N9Q5G9 §  · §
 *
 */

/*
 *  0         1         2         3         4         5         6         7         8
 *  -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
 *  hl············································································· ··prepare    : header and location lookup
 *      SEáafcd······································································ security   : audit overall security, fixed security
 *               DBásaÔ#óÕ··························································· database   : purge all data, read db, statistics, db reporting, write db
 *                          LOálÖò··················································· local file : audit file secure local, pull file, move to central, read all files, remove central file
 *                                  WOásaeÔ=rÕ······································· world file : audit world security, check entry, load world, report, register/withdrawl, save world
 *                                              CEáamÖr×=x··························· central    : move local to central, audit security of central file, pull one central file, pull all central files, clear one central file, list central files, remove central file
 *                                                          ACágnd··················· actions    : gather, normal/strict, daemon/prickly
 *                                                                  BEásaEUBDR······· backend    : extract file, upload, backup, download, restore
 *                                                                              fy··· wrapup     : footer and yes=pass/°=fail
 */


char    g_acts_score    [LEN_HUND]  = "                                                                        ";

char    g_fullacts      [LEN_DESC]  = "hl aÔÕ lcÖ òmr #=ó WRf BRP UD ×we fF";



/*====================------------------------------------====================*/
/*===----                          topmost                             ----===*/
/*====================------------------------------------====================*/
static void      o___HEADER________o (void) {;};

char
yjobs_ends__titles      (char a_runas, char a_mode, char a_oneline [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "HEADER"   , G_SCORE_FAIL);
   ySCORE_mark (myJOBS.m_yscore, "NOISE"    , G_SCORE_SKIP);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      yjobs_ends_failure (a_mode, "", "called with NULL mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      yjobs_ends_failure (a_mode, "", "called with an invalid mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_verbose" , g_verbose);
   if (strchr (g_verbose , a_mode) == NULL) {
      ySCORE_mark (myJOBS.m_yscore, "HEADER"   , G_SCORE_SKIP);
      if (strchr (g_confirm , a_mode) != NULL) ySCORE_mark (myJOBS.m_yscore, "NOISE"    , 'c');
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   ySCORE_mark (myJOBS.m_yscore, "NOISE"    , '!');
   /*---(pre-header)---------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yjobs_ends_failure (a_mode, "", "called with NULL/empty oneline");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   yURG_msg (':', "%s", a_oneline);
   /*---(actual header)------------------*/
   --rce;  switch (a_mode) {     /*---(incomming 5)-----------------*/
   case CASE_VERIFY   :  yURG_msg (':', "  option --vverify   : check details, but not register, update, or install");    break;
   case CASE_LOCALRPT :  yURG_msg (':', "  option --vlocal    : verify and perform a specific report on local data");     break;
   case CASE_REGISTER :  yURG_msg (':', "  option --vregister : verify and add to world, but not update or install");     break;
   case CASE_UPDATE   :  yURG_msg (':', "  option --vupdate   : verify and update global, but not register");             break;
   case CASE_INSTALL  :  yURG_msg (':', "  option --vinstall  : complete intake of verification, update, and registration"); break;
                         /*---(maintain 6)------------------*/
   case CASE_STATS    :  break;  /* no verbose option */
   case CASE_LIST     :  break;  /* no verbose option */
   case CASE_REPORT   :  yURG_msg (':', "  option --vreport   : search, process, or report from central information");    break;
   case CASE_CHECK    :  yURG_msg (':', "  option --vcheck    : verify details of centrally installed file");             break;
   case CASE_AUDIT    :  yURG_msg (':', "  option --vaudit    : check central setup, files, and security");               break;
   case CASE_FIX      :  yURG_msg (':', "  option --vfix      : check and repair central setup, files, and security");    break;
   case CASE_ONLY     :  yURG_msg (':', "  option --vonly     : execute with single central file");                       break;
                         /*---(epic 3)----------------------*/
                         /*---(elsewhere 2)-----------------*/
                         /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW :  yURG_msg (':', "  option --vwithdraw : remove from world, but not contents/file from central");  break;
   case CASE_CLEAR    :  yURG_msg (':', "  option --vclear    : remove contents/file from central, but not world");       break;
   case CASE_REMOVE   :  yURG_msg (':', "  option --vremove   : remove both from central contents and world");            break;
   case CASE_EXTRACT  :  yURG_msg (':', "  option --vextract  : make a local copy of a central file/entry");              break;
                         /*---(execution 6)-----------------*/
   case CASE_GATHER   :  yURG_msg (':', "  option --vgather   : verify and update all entries from world file");          break;
   case CASE_DAEMON   :  yURG_msg (':', "  option --vdaemon   : verbosely launch in background daemon mode");             break;
   case CASE_PRICKLY  :  yURG_msg (':', "  option --vprickly  : verbosely launch in prickly daemon mode");                break;
   case CASE_NORMAL   :  yURG_msg (':', "  option --vnormal   : verbosely launch in normal/non-daemon mode");             break;
   case CASE_STRICT   :  yURG_msg (':', "  option --vstrict   : verbosely launch in strict normal/non-daemon mode");      break;

   default            :
                         yjobs_ends_failure (a_mode, "", "called with an unrecognized mode");
                         DEBUG_YJOBS   yLOG_note    ("mode is illegal or not-recognized");
                         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
                         return rce;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(update score)-------------------*/
   ySCORE_mark (myJOBS.m_yscore, "HEADER"   , 'h');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs_ends__locations   (char a_runas, char a_mode, char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_conf      [LEN_LABEL] = "";
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "LOCS"     , G_SCORE_FAIL);
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , ""     , LEN_DESC);
   if (r_conf  != NULL)  ystrlcpy (r_conf , ""     , LEN_LABEL);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , ""     , LEN_DESC);
   if (r_world != NULL)  ystrlcpy (r_world, ""     , LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , ""     , LEN_LABEL);
   /*---(get location data)--------------*/
   rc = yJOBS_configured   (a_runas, NULL, NULL, NULL, x_cdir, x_conf, x_hdir, x_db, x_world);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "can not retrieve location information for runas");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_conf"    , x_conf);
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   /*---(save-back)----------------------*/
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , x_cdir , LEN_DESC);
   if (r_conf  != NULL)  ystrlcpy (r_conf , x_conf , LEN_LABEL);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , x_hdir , LEN_DESC);
   if (r_world != NULL)  ystrlcpy (r_world, x_world, LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , x_db   , LEN_LABEL);
   /*---(update score)-------------------*/
   ySCORE_mark (myJOBS.m_yscore, "LOCS"     , 'l');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends__cwd         (char a_runas, char a_mode, char a_file [LEN_PATH], char a_cdir [LEN_DESC], char r_cwd [LEN_PATH], char r_dir [LEN_PATH], char r_file [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        rce         =  -10;
   char        x_cwd       [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char       *p           = NULL;
   char        l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "CWD"      , G_SCORE_FAIL);
   /*---(default)------------------------*/
   if (r_cwd   != NULL)  ystrlcpy (r_cwd  , ""     , LEN_PATH);
   if (r_dir   != NULL)  ystrlcpy (r_dir  , ""     , LEN_PATH);
   if (r_file  != NULL)  ystrlcpy (r_file , ""     , LEN_PATH);
   if (r_full  != NULL)  ystrlcpy (r_full , ""     , LEN_PATH);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      yjobs_ends_failure (a_mode, "", "called with NULL mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      yjobs_ends_failure (a_mode, "", "called with an invalid mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      yjobs_ends_failure (a_mode, "", "called with a NULL file name");
      DEBUG_YJOBS   yLOG_note    ("a_file is null (FATAL)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_file [0] == '\0') {
      DEBUG_YJOBS   yLOG_note    ("a_file is empty (warning)");
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("a_cdir"    , a_cdir);
   /*---(get current working dir)--------*/
   p = getcwd (x_cwd, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      yjobs_ends_failure (a_mode, "", "system call getcwd failed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   /*---(test split)---------------------*/
   rc = yENV_name_split (a_file, NULL, x_dir, x_file);
   DEBUG_YJOBS   yLOG_value   ("split"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "file name could not be split");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_dir"     , x_dir);
   DEBUG_YJOBS   yLOG_info    ("x_file"    , x_file);
   /*---(directory)----------------------*/
   if (strcmp (x_dir, "") == 0) {
      switch (a_mode) {
      case CASE_VERIFY   : case CASE_LOCALRPT : case CASE_REGISTER :
      case CASE_UPDATE   : case CASE_INSTALL  : case CASE_WITHDRAW :
         ystrlcpy (x_dir, x_cwd, LEN_PATH);
         break;
      case CASE_CHECK    : case CASE_ONLY     : case CASE_REMOVE   :
      case CASE_EXTRACT  :
      default :
         ystrlcpy (x_dir, a_cdir, LEN_PATH);
         break;
      }
      l = strlen (x_dir);
      if (x_dir [l - 1] != '/')  ystrlcat (x_dir, "/", LEN_PATH);
   }
   DEBUG_YJOBS   yLOG_info    ("x_dir"     , x_dir);
   DEBUG_YJOBS   yLOG_info    ("x_file"    , x_file);
   /*---(full)---------------------------*/
   rc = yENV_name_full (x_dir, x_file, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "file name could not be joined");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(save-back)----------------------*/
   if (r_cwd   != NULL)   ystrlcpy (r_cwd  , x_cwd  , LEN_PATH);
   if (r_dir   != NULL)   ystrlcpy (r_dir  , x_dir  , LEN_PATH);
   if (r_file  != NULL)   ystrlcpy (r_file , x_file , LEN_PATH);
   if (r_full  != NULL)   ystrlcpy (r_full , x_full , LEN_PATH);
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "CWD"      , '¤');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends_prepare      (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, int *r_ruid, char r_ruser [LEN_USER], char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL], char r_lpre [LEN_TERSE], char r_cpre [LEN_TERSE], char r_suf [LEN_TERSE], char r_cwd [LEN_PATH], char r_dir [LEN_PATH], char r_file [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_msg       [LEN_HUND]  = "";
   char       *x_fatal     = "trouble preparing for execution";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ruid  != NULL)  *r_ruid  = -1;
   if (r_ruser != NULL)  strcpy (r_ruser, "");
   if (r_cdir  != NULL)  strcpy (r_cdir , "");
   if (r_conf  != NULL)  strcpy (r_conf , "");
   if (r_hdir  != NULL)  strcpy (r_hdir , "");
   if (r_db    != NULL)  strcpy (r_db   , "");
   if (r_world != NULL)  strcpy (r_world, "");
   if (r_lpre  != NULL)  strcpy (r_lpre , "");
   if (r_cpre  != NULL)  strcpy (r_cpre , "");
   if (r_suf   != NULL)  strcpy (r_suf  , "");
   if (r_cwd   != NULL)  strcpy (r_cwd  , "");
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   if (r_file  != NULL)  strcpy (r_file , "");
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense - runas)----------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS   yLOG_info    ("g_valid"   , g_valid);
   --rce;  if (a_runas == 0 || strchr (g_valid, a_runas)  == NULL) {
      ySCORE_mark (myJOBS.m_yscore, "RUNAS"    , G_SCORE_FAIL);
      ySCORE_mark (myJOBS.m_yscore, "ENV"      , '·');
      sprintf (x_msg, "runas (%d/%c) not recognized or valid", a_runas, ychrvisible (a_runas));
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense - mode)-----------------*/
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (a_mode  == 0 || strchr (g_allmode, a_mode) == NULL) {
      ySCORE_mark (myJOBS.m_yscore, "MODE"     , G_SCORE_FAIL);
      ySCORE_mark (myJOBS.m_yscore, "NOISE"    , '·');
      sprintf (x_msg, "mode (%d/%c) not recognized or valid", a_mode, ychrvisible (a_mode));
      yjobs_ends_failure (a_mode, x_msg, x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense - oneline)--------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      ySCORE_mark (myJOBS.m_yscore, "ONE"      , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "descriptive oneline string is NULL/empty", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   /*---(defense - file)-----------------*/
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      ySCORE_mark (myJOBS.m_yscore, "FILE"     , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "requested file/directory is NULL", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   /*---(defense - callback)-------------*/
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      ySCORE_mark (myJOBS.m_yscore, "CALL"     , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "host program callback function is NULL", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(security)-----------------------*/
   rc = yENV_whoami           (NULL, NULL, r_ruid, NULL, NULL, r_ruser, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      ySCORE_mark (myJOBS.m_yscore, "RUSER"    , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "could not identify current user (yENV_whoami)", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ySCORE_mark (myJOBS.m_yscore, "RUSER"    , 'u');
   /*---(titles)-------------------------*/
   rc = yjobs_ends__titles (a_runas, a_mode, a_oneline);
   DEBUG_YJOBS   yLOG_value   ("titles"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get central files)--------------*/
   rc = yjobs_ends__locations (a_runas, a_mode, r_cdir, r_conf, r_hdir, r_world, r_db);
   DEBUG_YJOBS   yLOG_value   ("locations" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get current working dir)--------*/
   rc = yjobs_ends__cwd       (a_runas, a_mode, a_file, r_cdir, r_cwd, r_dir, r_file, r_full);
   DEBUG_YJOBS   yLOG_value   ("cwd"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get program values)-------------*/
   rc = yjobs_who_naming (a_runas, NULL, NULL, r_lpre, r_cpre, r_suf, NULL);
   DEBUG_YJOBS   yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "can not retreive prefix/suffix data", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                          footer                              ----===*/
/*====================------------------------------------====================*/
static void      o___FOOTER________o (void) {;};

char
yjobs_ends__footer      (char a_func [LEN_TITLE], char a_mode, char a_prefix [LEN_TERSE], char a_color [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_suffix    [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (a_func);
   /*---(default)------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , G_SCORE_FAIL);
   ySCORE_mark (myJOBS.m_yscore, "JUDGE"    , G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_prefix"  , a_prefix);
   /*---(pre-score)----------------------*/
   ySCORE_mark (myJOBS.m_yscore, "JUDGE"    , 'Ï');
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (a_func);
      return 0;
   }
   /*---(prepare)------------------------*/
   if (strcmp (a_prefix, "APPROVED") == 0)  strcpy (x_suffix, "; USES over-rides");
   if (strcmp (a_prefix, "REPAIRED") == 0)  strcpy (x_suffix, "; MUST investigate");
   if (strcmp (a_prefix, "WARNING")  == 0)  strcpy (x_suffix, "; BUT, issues outstanding");
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(write actual header)------------*/
   switch (a_mode) {    /*---(incomming 5)-----------------*/
   case CASE_VERIFY   : yURG_msg (':', "%s%s, read and verified local, but no register, update, or install requested%s%s" , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_LOCALRPT : yURG_msg (':', "%s%s, verified and specific report completed on local data%s%s"                   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_REGISTER : yURG_msg (':', "%s%s, verified and registered local, but no update or install requested%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_UPDATE   : yURG_msg (':', "%s%s, verified and updated, but registration not requested%s%s"                   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_INSTALL  : yURG_msg (':', "%s%s, full install of verification, update, and registration%s%s"                 , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(central 6)-------------------*/
   case CASE_CHECK    : yURG_msg (':', "%s%s, centrally installed file is runable, all lines checked%s%s"                 , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_AUDIT    : yURG_msg (':', "%s%s, environment and all central files passed relevent checks%s%s"               , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_FIX      : yURG_msg (':', "%s%s, environment and all central files passed relevent checks%s%s"               , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_ONLY     : yURG_msg (':', "%s%s, central execution on single file confirmed%s%s"                             , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(epic 3)----------------------*/
                        /*---(elsewhere 2)-----------------*/
                        /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW : yURG_msg (':', "%s%s, registered local withdrawn from world, but clear/remove not requested%s%s"  , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_CLEAR    : yURG_msg (':', "%s%s, installed file/dir cleared from database, but withdraw not requested%s%s"   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_REMOVE   : yURG_msg (':', "%s%s, installed file/dir cleared from database and withdrawn from world%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_EXTRACT  : yURG_msg (':', "%s%s, installed file/dir contents extracted to local file%s%s"                    , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(execution 6)-----------------*/
   case CASE_GATHER   : yURG_msg (':', "%s%s, world registry entries have been gathered/updated in the database%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , 'f');
   if (strcmp (a_prefix, "WARNING") == 0)  rc = 1;
   DEBUG_YJOBS  yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return rc;
}

char yjobs_ends_success      (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "SUCCESS" , BOLD_GRN); }
char yjobs_ends_approved     (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "APPROVED", BOLD_BLU); }
char yjobs_ends_repaired     (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "REPAIRED", BOLD_PUR); }
char yjobs_ends_warning      (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "WARNING" , BOLD_YEL); }

char
yjobs_ends_failure      (char a_mode, char a_message [LEN_HUND], char a_final [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , G_SCORE_FAIL);
   ySCORE_mark (myJOBS.m_yscore, "JUDGE"    , G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      a_mode = ACT_CVERIFY;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      a_mode = ACT_CVERIFY;
   }
   DEBUG_YJOBS  yLOG_point   ("a_message" , a_message);
   --rce;  if (a_message == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_message" , a_message);
   DEBUG_YJOBS  yLOG_point   ("a_final"   , a_final);
   --rce;  if (a_final == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_final"   , a_final);
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(message)------------------------*/
   if (strcmp (a_message, "") != 0)    yURG_err ('f', a_message);
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(actual footer)------------------*/
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (':', "%sFAILED, %s, the reasons are shown above%s"      , BOLD_ERR, a_final, BOLD_OFF);
   else                                       yURG_msg (':', "%sFAILED, %s, run verbosely to identify reasons%s", BOLD_ERR, a_final, BOLD_OFF);
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, "FOOTER"   , 'f');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}




