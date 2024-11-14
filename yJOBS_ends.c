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
 *  hl········································································· prepare    : header and location lookup
 *      SEáaf·································································· security   : audit overall security, fixed security
 *             DBápÔ#óÕ························································ database   : purge all data, read db, statistics, db reporting, write db
 *                       LOálÖò················································ local file : audit file secure local, pull file, move to central, read all files, remove central file
 *                               WOáwÔ=ruÕ····································· world file : audit world security, load world, register, withdrawl, save world
 *                                          CEámcÖr×=x························· central    : move local to central, audit security of central file, pull one central file, pull all central files, clear one central file, list central files, remove central file
 *                                                      ACágnd················· actions    : gather, normal/strict, daemon/prickly
 *                                                              BEáEUBDR······· backend    : extract file, upload, backup, download, restore
 *                                                                        fy··· wrapup     : footer and yes=pass/°=fail
 */


char    g_acts_empty    [LEN_HUND]  = "··  SEá··  DBá·····  LOá···  WOá······  CEá·······  ACá···  BEá·····  ··";
char    g_acts_full     [LEN_HUND]  = "hl  SEáaf  DBápÔ#óÕ  LOálÖò  WOáwÔ=ruÕ  CEámcÖr×=x  ACágnd  BEáEUBDR  fy";

char    g_acts_score    [LEN_HUND]  = "                                                                        ";

char    g_fullacts      [LEN_DESC]  = "hl aÔÕ lcÖ òmr #=ó WRf BRP UD ×we fF";

static char (*s_assimilate) (cchar a_runas, cchar a_loc, cchar *a_file, char *r_user, char *r_desc);

static struct {
   char        s_pos;
   char        s_section;
   uchar       s_valid     [LEN_TERSE];
   char        s_desc      [LEN_DESC];
} s_scores [LEN_HUND] = {

   {  0, G_SCORE_PREPARE   , "°h-·"    , "printing of the title lines"      },
   {  1, G_SCORE_PREPARE   , "°l·"     , "default location lookup"          },

   {  7, G_SCORE_SECURE    , "°a·"     , "general security audit"           },
   {  8, G_SCORE_SECURE    , "°f·"     , "general security update/fix"      },

   { 14, G_SCORE_DATABASE  , "°p·"     , "purge all data in memory"         },
   { 15, G_SCORE_DATABASE  , "°Ô-·"    , "read database"                    },
   { 16, G_SCORE_DATABASE  , "°#·"     , "database statistics"              },
   { 17, G_SCORE_DATABASE  , "°ó·"     , "database reporting"               },
   { 18, G_SCORE_DATABASE  , "°Õ-·"    , "write database"                   },

   { 24, G_SCORE_LOCAL     , "°dl·"    , "audit local file/directory"       },
   { 25, G_SCORE_LOCAL     , "°Ö·"     , "pull/read local file"             },
   { 26, G_SCORE_LOCAL     , "°ò·"     , "move local file to central"       },

   { 32, G_SCORE_WORLD     , "°w-·"    , "audit world file"                 },
   { 33, G_SCORE_WORLD     , "°Ô-·"    , "read world file"                  },
   { 34, G_SCORE_WORLD     , "°=·"     , "register a world entry"           },
   { 35, G_SCORE_WORLD     , "°r-·"    , "withdraw a world entry"           },
   { 36, G_SCORE_WORLD     , "°Õ-·"    , "wrote world file"                 },

   { 43, G_SCORE_CENTRAL   , "°m-·"    , "move local to central"            },
   { 44, G_SCORE_CENTRAL   , "°ce-·"   , "audit security of central"        },
   { 45, G_SCORE_CENTRAL   , "°Ö-·"    , "pull/load central file"           },
   { 46, G_SCORE_CENTRAL   , "°r-·"    , ""                                 },
   { 47, G_SCORE_CENTRAL   , "°×-·"    , "clear central file"               },
   { 48, G_SCORE_CENTRAL   , "°=·"     , "list central files"               },
   { 49, G_SCORE_CENTRAL   , "°x-·"    , "remove central file"              },

   { 55, G_SCORE_ACTION    , "°g·"     , "gather local files"               },
   { 56, G_SCORE_ACTION    , "°n·"     , "normal/strict mode"               },
   { 57, G_SCORE_ACTION    , "°d·"     , "daemon/prickly mode"              },

   { 63, G_SCORE_BACKEND   , "°E-·"    , "extract a central file"           },
   { 64, G_SCORE_BACKEND   , "°U-·"    , "upload a central file"            },
   { 65, G_SCORE_BACKEND   , "°B-·"    , "backup a central file"            },
   { 66, G_SCORE_BACKEND   , "°D-·"    , "download a central file"          },
   { 67, G_SCORE_BACKEND   , "°R-·"    , "restore a central file"           },

   { 70, G_SCORE_JUDGE     , "°f-·"    , "print footer on output"           },
   { 71, G_SCORE_JUDGE     , "°y!·"    , "final judgement"                  },

   { -1, -1                , ""        , "end-of-entries"                   },
};



/*====================------------------------------------====================*/
/*===----                           scoring                            ----===*/
/*====================------------------------------------====================*/
static void      o___SCORE_________o (void) {;};

char
yjobs_ends_clear        (void)
{
   DEBUG_YJOBS  yLOG_senter  (__FUNCTION__);
   ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   DEBUG_YJOBS  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yjobs_ends_score        (char a_section, char a_offset, uchar a_result)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_pos       =   -1;
   char        x_check     =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_section" , a_section);
   --rce;  if (a_section < 0 || a_section >= LEN_HUND - 10) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_value   ("a_offset"  , a_offset);
   --rce;  if (a_offset  < 0 || a_offset  >= 10) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(position)-----------------------*/
   x_check = a_section + a_offset;
   DEBUG_YJOBS  yLOG_value   ("x_check"   , x_check);
   --rce;  if (x_check   < 0 || x_check   >= LEN_HUND) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < LEN_HUND; ++i) {
      if (s_scores [i].s_section == -1)         break;
      if (s_scores [i].s_section != a_section)  continue;
      if (s_scores [i].s_pos     != x_check)    continue;
      x_pos = s_scores [i].s_pos;
      break;
   }
   DEBUG_YJOBS  yLOG_value   ("x_pos"     , x_pos);
   --rce;  if (x_pos     <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(character)----------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_result"  , a_result);
   --rce;  if (a_result  < 32) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("s_valid"   , s_scores [i].s_valid);
   if (strchr (s_scores [i].s_valid, (uchar) a_result) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("a_result"  , a_result);
   /*---(update)-------------------------*/
   DEBUG_YJOBS  yLOG_info    ("before"    , g_acts_score);
   g_acts_score [x_pos] = a_result;
   DEBUG_YJOBS  yLOG_info    ("after"     , g_acts_score);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          topmost                             ----===*/
/*====================------------------------------------====================*/
static void      o___HEADER________o (void) {;};

char
yjobs__ends_titles      (char a_mode, char a_oneline [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  0, G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_verbose" , g_verbose);
   if (strchr (g_verbose , a_mode) == NULL) {
      yjobs_ends_score (G_SCORE_PREPARE,  0, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(pre-header)---------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
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
   case CASE_INSTALL  :  yURG_msg (':', "  option --vinstall  : complete intake of verify, update global, and register"); break;
                         /*---(maintain 6)------------------*/
   case CASE_STATS    :  break;  /* no verbose option */
   case CASE_LIST     :  break;  /* no verbose option */
   case CASE_REPORT   :  yURG_msg (':', "  option --vreport   : search, process, or report from central information");    break;
   case CASE_CHECK    :  yURG_msg (':', "  option --vcheck    : verify details of centrally installed file");             break;
   case CASE_AUDIT    :  yURG_msg (':', "  option --vaudit    : check central setup, files, and security");               break;
   case CASE_FIX      :  yURG_msg (':', "  option --vfix      : repair central directories and security");                break;
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
   case CASE_DAEMON   :  yURG_msg (':', "  option --vdaemon   : verbosely launch in daemon mode");                        break;
   case CASE_PRICKLY  :  yURG_msg (':', "  option --vprickly  : verbosely launch in prickly daemon mode");                break;
   case CASE_NORMAL   :  yURG_msg (':', "  option --vnormal   : verbosely launch in normal mode");                        break;
   case CASE_STRICT   :  yURG_msg (':', "  option --vstrict   : verbosely launch in strict normal mode");                 break;

   default            :
      DEBUG_YJOBS   yLOG_note    ("mode is illegal or not-recognized");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(update score)-------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  0, 'h');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__ends_locations   (char a_runas, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  1, G_SCORE_FAIL);
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , ""     , LEN_PATH);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , ""     , LEN_PATH);
   if (r_world != NULL)  ystrlcpy (r_world, ""     , LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , ""     , LEN_LABEL);
   /*---(get location data)--------------*/
   rc = yjobs_who_location (a_runas, x_cdir, x_hdir, x_world, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   /*---(save-back)----------------------*/
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , x_cdir , LEN_PATH);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , x_hdir , LEN_PATH);
   if (r_world != NULL)  ystrlcpy (r_world, x_world, LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , x_db   , LEN_LABEL);
   /*---(update score)-------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  1, 'l');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__ends_cwd         (char a_mode, char a_file [LEN_PATH], char a_cdir [LEN_PATH], char r_cwd [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_cwd       [LEN_PATH]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  1, G_SCORE_FAIL);
   if (r_cwd   != NULL)  ystrlcpy (r_cwd  , ""     , LEN_PATH);
   if (r_full  != NULL)  ystrlcpy (r_full , ""     , LEN_PATH);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL || a_file [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("a_cdir"    , a_cdir);
   /*> --rce;  if (a_cdir    == NULL) {                                               <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_YJOBS  yLOG_info    ("a_cdir"    , a_cdir);                              <*/
   /*---(get current working dir)--------*/
   p = getcwd (x_cwd, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   /*---(save-back)----------------------*/
   if (r_cwd   != NULL) {
      ystrlcpy (r_cwd  , x_cwd  , LEN_PATH);
   }
   if (r_full  != NULL) {
      if      (a_file [0] == '/')                    snprintf (r_full , LEN_PATH, "%s"   , a_file);
      else if (strchr (g_local  , a_mode) != NULL)   snprintf (r_full , LEN_PATH, "%s/%s", x_cwd , a_file);
      else if (strchr (g_central, a_mode) != NULL)   snprintf (r_full , LEN_PATH, "%s/%s", a_cdir, a_file);
   }
   DEBUG_YJOBS   yLOG_info    ("r_full"    , r_full);
   /*---(update score)-------------------*/
   yjobs_ends_score (G_SCORE_PREPARE,  1, 'l');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends_header       (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_cwd [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   /*---(titles)-------------------------*/
   rc = yjobs__ends_titles (a_mode, a_oneline);
   DEBUG_YJOBS   yLOG_value   ("titles"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get central files)--------------*/
   rc = yjobs__ends_locations (a_runas, r_cdir, r_hdir, r_world, r_db);
   DEBUG_YJOBS   yLOG_value   ("locations" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get current working dir)--------*/
   rc = yjobs__ends_cwd       (a_mode, a_file, r_cdir, r_cwd, r_full);
   DEBUG_YJOBS   yLOG_value   ("cwd"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          footer                              ----===*/
/*====================------------------------------------====================*/
static void      o___FOOTER________o (void) {;};

char
yjobs_ends_footer       (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yjobs_ends_score (G_SCORE_JUDGE,  0, G_SCORE_FAIL);
   yjobs_ends_score (G_SCORE_JUDGE,  1, '!');
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pre-score)----------------------*/
   yjobs_ends_score (G_SCORE_JUDGE,  1, 'y');
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      yjobs_ends_score (G_SCORE_JUDGE,  0, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(write actual header)------------*/
   switch (a_mode) {    /*---(incomming 5)-----------------*/
   case CASE_VERIFY   : yURG_msg (':', "%sSUCCESS, read and verified local, but no register, update, or install requested%s" , BOLD_GRN, BOLD_OFF);  break;
   case CASE_LOCALRPT : yURG_msg (':', "%sSUCCESS, verified and specific report completed on local data%s"                   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_REGISTER : yURG_msg (':', "%sSUCCESS, verified and registered local, but no update or install requested%s"      , BOLD_GRN, BOLD_OFF);  break;
   case CASE_UPDATE   : yURG_msg (':', "%sSUCCESS, verified and updated, but registration not requested%s"                   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_INSTALL  : yURG_msg (':', "%sSUCCESS, full install of verification, update, and registration%s"                 , BOLD_GRN, BOLD_OFF);  break;
                        /*---(central 6)-------------------*/
   case CASE_CHECK    : yURG_msg (':', "%sSUCCESS, centrally installed file is runable, all lines checked%s"                 , BOLD_GRN, BOLD_OFF);  break;
   case CASE_AUDIT    : yURG_msg (':', "%sSUCCESS, environment and all central files passed relevent checks%s"               , BOLD_GRN, BOLD_OFF);  break;
   case CASE_FIX      : yURG_msg (':', "%sSUCCESS, central directory basic security measures confirmed%s"                    , BOLD_GRN, BOLD_OFF);  break;
   case CASE_ONLY     : yURG_msg (':', "%sSUCCESS, central execution on single file confirmed%s"                             , BOLD_GRN, BOLD_OFF);  break;
                        /*---(epic 3)----------------------*/
                        /*---(elsewhere 2)-----------------*/
                        /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW : yURG_msg (':', "%sSUCCESS, registered local withdrawn from world, but clear/remove not requested%s"  , BOLD_GRN, BOLD_OFF);  break;
   case CASE_CLEAR    : yURG_msg (':', "%sSUCCESS, installed file/dir cleared from database, but withdraw not requested%s"   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_REMOVE   : yURG_msg (':', "%sSUCCESS, installed file/dir cleared from database and withdrawn from world%s"      , BOLD_GRN, BOLD_OFF);  break;
   case CASE_EXTRACT  : yURG_msg (':', "%sSUCCESS, installed file/dir contents extracted to local file%s"                    , BOLD_GRN, BOLD_OFF);  break;
                        /*---(execution 6)-----------------*/
   case CASE_GATHER   : yURG_msg (':', "%sSUCCESS, world registry entries have been gathered/updated in the database%s"      , BOLD_GRN, BOLD_OFF);  break;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   yjobs_ends_score (G_SCORE_JUDGE,  0, 'f');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends_failure      (char a_mode, char a_hint [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yjobs_ends_score (G_SCORE_JUDGE,  0, G_SCORE_FAIL);
   yjobs_ends_score (G_SCORE_JUDGE,  1, '!');
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_hint"    , a_hint);
   --rce;  if (a_hint == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_hint"    , a_hint);
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      yjobs_ends_score (G_SCORE_JUDGE,  0, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(actual footer)------------------*/
   if (strchr (g_verbose , a_mode)  != NULL) yURG_msg (':', "%sFAILED, %s, the reasons are shown above%s"      , BOLD_ERR, a_hint, BOLD_OFF);
   else                                      yURG_msg (':', "%sFAILED, %s, run verbosely to identify reasons%s", BOLD_ERR, a_hint, BOLD_OFF);
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   yjobs_ends_score (G_SCORE_JUDGE,  0, 'f');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}
