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
 *      SEáaF·································································· security   : audit overall security, fixed security
 *             DBápÔ#óÕ························································ database   : purge all data, read db, statistics, db reporting, write db
 *                       LOálÖò················································ local file : audit file secure local, pull file, move to central, read all files, remove central file
 *                               WOáWÔ=ruÕ····································· world file : audit world security, load world, register, withdrawl, save world
 *                                          CEámcÖR×=x························· central    : move local to central, audit security of central file, pull one central file, pull all central files, clear one central file, list central files, remove central file
 *                                                      ACágnd················· actions    : gather, normal/strict, daemon/prickly
 *                                                              BEáEUBDR······· backend    : extract file, upload, backup, download, restore
 *                                                                        fy··· wrapup     : footer and yes=pass/°=fail
 */


char    g_acts_empty    [LEN_HUND]  = "··  SEá··  DBá·····  LOá···  WOá······  CEá·······  ACá···  BEá·····  ··";
char    g_acts_score    [LEN_HUND]  = "hl  SEáaF  DBápÔ#óÕ  LOálÖò  WOáWÔ=ruÕ  CEámcÖR×=x  ACágnd  BEáEUBDR  fy";

char    g_fullacts      [LEN_DESC]  = "hl aÔÕ lcÖ òmr #=ó WRf BRP UD ×we fF";

static char (*s_assimilate) (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);



/*====================------------------------------------====================*/
/*===----                        local actions                         ----===*/
/*====================------------------------------------====================*/
static void      o___LOCAL_________o (void) {;};

char
yjobs_act_header        (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar *a_name, char *r_cdir, char *r_world, char *r_update, char *r_db, char *r_cwd, char *r_full)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_cwd       [LEN_PATH]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   /*---(pre-header)---------------------*/
   yURG_msg ('>', "%s", a_oneline);
   /*---(actual header)------------------*/
   switch (a_mode) {     /*---(incomming 5)-----------------*/
   case CASE_VERIFY   :  yURG_msg ('>', "  option --vverify   : check details, but not register, update, or install");    break;
   case CASE_LOCALRPT :  yURG_msg ('>', "  option --vlocal    : verify and perform a specific report on local data");     break;
   case CASE_REGISTER :  yURG_msg ('>', "  option --vregister : verify and add to world, but not update or install");     break;
   case CASE_UPDATE   :  yURG_msg ('>', "  option --vupdate   : verify and update global, but not register");             break;
   case CASE_INSTALL  :  yURG_msg ('>', "  option --vinstall  : complete intake of verify, update global, and register"); break;
                         /*---(maintain 6)------------------*/
   case CASE_STATS    :  break;  /* no verbose option */
   case CASE_LIST     :  break;  /* no verbose option */
   case CASE_REPORT   :  yURG_msg ('>', "  option --vreport   : search, process, or report from central information");    break;
   case CASE_CHECK    :  yURG_msg ('>', "  option --vcheck    : verify details of centrally installed file");             break;
   case CASE_AUDIT    :  yURG_msg ('>', "  option --vaudit    : check central setup, files, and security");               break;
   case CASE_FIX      :  yURG_msg ('>', "  option --vfix      : repair central directories and security");                break;
   case CASE_ONLY     :  yURG_msg ('>', "  option --vonly     : execute with single central file");                       break;
                         /*---(epic 3)----------------------*/
                         /*---(elsewhere 2)-----------------*/
                         /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW :  yURG_msg ('>', "  option --vwithdraw : remove from world, but not contents/file from central");  break;
   case CASE_CLEAR    :  yURG_msg ('>', "  option --vclear    : remove contents/file from central, but not world");       break;
   case CASE_REMOVE   :  yURG_msg ('>', "  option --vremove   : remove both from central contents and world");            break;
   case CASE_EXTRACT  :  yURG_msg ('>', "  option --vextract  : make a local copy of a central file/entry");              break;
                         /*---(execution 6)-----------------*/
   case CASE_GATHER   :  yURG_msg ('>', "  option --vgather   : verify and update all entries from world file");          break;
   case CASE_DAEMON   :  yURG_msg ('>', "  option --vdaemon   : verbosely launch in daemon mode");                        break;
   case CASE_PRICKLY  :  yURG_msg ('>', "  option --vprickly  : verbosely launch in prickly daemon mode");                break;
   case CASE_NORMAL   :  yURG_msg ('>', "  option --vnormal   : verbosely launch in normal mode");                        break;
   case CASE_STRICT   :  yURG_msg ('>', "  option --vstrict   : verbosely launch in strict normal mode");                 break;
   }
   g_acts_score  [G_SCORE_PREPARE + 0] = 'h';
   /*---(get central files)--------------*/
   g_acts_score  [G_SCORE_PREPARE + 1] = G_SCORE_FAIL;
   rc = yjobs_who_location (a_runas, x_cdir, NULL, x_world, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , x_cdir , LEN_PATH);
   if (r_world != NULL)  ystrlcpy (r_world, x_world, LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , x_db   , LEN_LABEL);
   /*---(get current working dir)--------*/
   p = getcwd (x_cwd, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   if (r_cwd   != NULL)  ystrlcpy (r_cwd  , x_cwd  , LEN_PATH);
   if (r_full  != NULL) {
      if      (strchr (g_local  , a_mode) != NULL)   sprintf (r_full , "%s/%s", x_cwd , a_name);
      else if (strchr (g_central, a_mode) != NULL)   sprintf (r_full , "%s/%s", x_cdir, a_name);
   }
   g_acts_score  [G_SCORE_PREPARE + 1] = 'l';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_footer        (cchar a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   g_acts_score  [G_SCORE_JUDGE + 0] = 'f';
   /*---(write actual header)------------*/
   switch (a_mode) {    /*---(incomming 5)-----------------*/
   case CASE_VERIFY   : yURG_msg ('>', "%sSUCCESS, read and verified local, but update/installation not requested%s"         , BOLD_GRN, BOLD_OFF);  break;
   case CASE_LOCALRPT : yURG_msg ('>', "%sSUCCESS, verified and specific report completed on local data%s"                   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_REGISTER : yURG_msg ('>', "%sSUCCESS, verified and registered local, but update/installation not requested%s"   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_UPDATE   : yURG_msg ('>', "%sSUCCESS, verified and updated, but registration not requested%s"                   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_INSTALL  : yURG_msg ('>', "%sSUCCESS, full install of verification, update, and registration%s"                 , BOLD_GRN, BOLD_OFF);  break;
                        /*---(central 6)-------------------*/
   case CASE_CHECK    : yURG_msg ('>', "%sSUCCESS, centrally installed file is runable, all lines checked%s"                 , BOLD_GRN, BOLD_OFF);  break;
   case CASE_AUDIT    : yURG_msg ('>', "%sSUCCESS, environment and all central files passed relevent checks%s"               , BOLD_GRN, BOLD_OFF);  break;
   case CASE_FIX      : yURG_msg ('>', "%sSUCCESS, central directory basic security measures confirmed%s"                    , BOLD_GRN, BOLD_OFF);  break;
   case CASE_ONLY     : yURG_msg ('>', "%sSUCCESS, central execution on single file confirmed%s"                             , BOLD_GRN, BOLD_OFF);  break;
                        /*---(epic 3)----------------------*/
                        /*---(elsewhere 2)-----------------*/
                        /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW : yURG_msg ('>', "%sSUCCESS, registered local withdrawn from world, but clear/remove not requested%s"  , BOLD_GRN, BOLD_OFF);  break;
   case CASE_CLEAR    : yURG_msg ('>', "%sSUCCESS, installed file/dir cleared from database, but withdraw not requested%s"   , BOLD_GRN, BOLD_OFF);  break;
   case CASE_REMOVE   : yURG_msg ('>', "%sSUCCESS, installed file/dir cleared from database and withdrawn from world%s"      , BOLD_GRN, BOLD_OFF);  break;
   case CASE_EXTRACT  : yURG_msg ('>', "%sSUCCESS, installed file/dir contents extracted to local file%s"                    , BOLD_GRN, BOLD_OFF);  break;
                        /*---(execution 6)-----------------*/
   case CASE_GATHER   : yURG_msg ('>', "%sSUCCESS, world registry entries have been gathered/updated in the database%s"      , BOLD_GRN, BOLD_OFF);  break;
   }
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   g_acts_score  [G_SCORE_JUDGE + 1] = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_failure       (cchar a_mode, cchar *a_text)
{
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   /*---(pre-footer)---------------------*/
   yURG_msg (' ', "");
   /*---(actual footer)------------------*/
   yURG_msg ('>', "%sFAILED, %s, the reasons are shown above%s", BOLD_ERR, a_text, BOLD_OFF);
   if (strchr (g_confirm , a_mode)  != NULL) {
      yURG_msg_live ();
      yURG_msg ('>', "%sFAILED, %s, run verbosely to identify reasons%s" BOLD_ERR, a_text, BOLD_OFF);
      yURG_msg_mute ();
   }
   g_acts_score  [G_SCORE_JUDGE + 1] = '!';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    imncomming actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___INCOMMING__________o (void) {;};

/*
 *   action      lvl
 *   ----------  ---  --db-in-- -secure-- --load--- --report- -intake-- --db-out- -register 
 *   verify      vÑV      ·         y         y         ·         ·         ·         ·       secure and load/audit
 *   local       lòL      ·         y         y         y         ·         ·         ·       secure and load/audit, and report
 *   register    béB      ·         y         y         ·         ·         ·         y       secure and load/audit, and register
 *   update      uûU      y         y         y         ·         y         y         ·       secure and load/audit, and update
 *   install     iðI      y         y         y         ·         y         y         y       secure and load/audit, and register and update
 *
 */

char       /* PURPOSE : install a local crontab file -------------------------*/
yjobs_incomming_move    (cchar a_runas, cchar a_mode, cchar a_file [LEN_PATH], cchar *a_fuser)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_new       [LEN_RECD]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   int         x_fuid      =  -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_fnew      [LEN_DESC]  = "";
   char        x_full      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "install file in central directory...");
   g_acts_score  [G_SCORE_CENTRAL + 0] = G_SCORE_FAIL;
   /*---(get central info)-------------------*/
   rc = yjobs_central_dirs (a_runas, a_mode, a_file, a_fuser, x_fdir, x_fnew);
   DEBUG_YJOBS   yLOG_info    ("x_fdir"    , x_fdir);
   DEBUG_YJOBS   yLOG_info    ("x_fnew"    , x_fnew);
   /*---(make full new file name)------------*/
   sprintf (x_full, "%s%s", x_fdir, x_fnew);
   yURG_msg ('-', "central file name å%sæ", x_full);
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(copy file)--------------------------*/
   snprintf (x_cmd, LEN_RECD, "cp -f %s %s > /dev/null  2>&1", a_file, x_full);
   DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not copy to å%sæ", x_fdir);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      yURG_err ('f', "could not copy to å%sæ", x_fdir);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "copied file to å%sæ", x_fdir);
   /*---(change ownership)-------------------*/
   rc = chown (x_full, 0, 0);
   DEBUG_YJOBS   yLOG_value   ("chown"     , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not change ownership to root");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "changed owner and group to root");
   /*---(change permissions)-----------------*/
   rc = chmod (x_full, 0600);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not change permissions to root-only write/read (0600)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "changed permissions to root-only write/read (0600)");
   /*---(summary)----------------------------*/
   yURG_msg ('-', "success, job/khronos file moved to central");
   yURG_msg (' ', "");
   g_acts_score  [G_SCORE_CENTRAL + 0] = 'm';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_incomming_full    (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_len       =    0;
   char       *p           = NULL;
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_fuser     [LEN_USER]  = "";
   int         x_fuid      =   -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_fnew      [LEN_DESC]  = "";
   char       *X_REPORT    = "lòL";
   char       *X_INSTALL   = "uûUiðI";
   char       *X_REGISTER  = "béBiðI";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   /*---(default)------------------------*/
   ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, NULL, x_world, NULL, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   /*---(database)-----------------------*/
   --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("requested database load");
      if (strcmp (x_db, "") != 0) {
         DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");
         g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_READ, "");
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central database did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 1] = 'Ô';
      } else {
         g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;
      }
   }
   /*---(security on file)---------------*/
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yjobs_act_failure (a_mode, "local file name is null/empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_file);
   g_acts_score  [G_SCORE_LOCAL + 0] = G_SCORE_FAIL;
   --rce;  if (a_file [x_len - 1] == '/') {
      DEBUG_YJOBS   yLOG_note    ("directory given");
      if (strchr (IAM_DIRS, a_runas) == NULL) {
         yjobs_act_failure (a_mode, "requester (not polymnia/metis) can not request directory");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_LOCAL + 0] = 'd';
   } else {
      DEBUG_YJOBS   yLOG_note    ("file given");
      if (strchr (IAM_FILES, a_runas) == NULL) {
         yjobs_act_failure (a_mode, "polymnia can only request directory, not a file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yjobs_local_old  (a_runas, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);
      DEBUG_YJOBS   yLOG_value   ("local"     , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "local file not proper and/or secure");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc == 1)  strlcpy (x_full, a_file, LEN_PATH);
      g_acts_score  [G_SCORE_LOCAL + 0] = 'l';
   }
   /*---(load/audit)---------------------*/
   g_acts_score  [G_SCORE_LOCAL + 1] = G_SCORE_FAIL;
   rc = x_callback (YJOBS_PULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0) {
      yjobs_act_failure (a_mode, "local contents not acceptable");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_acts_score  [G_SCORE_LOCAL + 1] = 'Ö';
   /*---(local report)-------------------*/
   --rce;  if (strchr (X_REPORT, a_mode) != NULL) {
      g_acts_score  [G_SCORE_LOCAL + 2] = G_SCORE_FAIL;
      rc = x_callback (YJOBS_LOCALRPT, a_file);
      DEBUG_YJOBS   yLOG_value   ("localrpt"  , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "local report could not complete");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_LOCAL + 2] = 'ò';
   }
   /*---(intake file)--------------------*/
   --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {
      if (strcmp (x_db, "") == 0) {
         /* score update is in world function */
         rc = yjobs_incomming_move (a_runas, a_mode, a_file, x_fuser);
         DEBUG_YJOBS   yLOG_value   ("intake"    , rc);
         --rce; if (rc < 0) {
            yjobs_act_failure (a_mode, "file could not be moved appopriately");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 0] = G_SCORE_SKIP;
      }
   }
   /*---(write database)-----------------*/
   --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         DEBUG_YJOBS   yLOG_note    ("option requires database saved after");
         g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_WRITE, "");
         DEBUG_YJOBS   yLOG_value   ("write db"  , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central database could not save properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 4] = 'Õ';
      } else {
         g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_SKIP;
      }
   }
   /*---(register)-----------------------*/
   --rce;  if (strchr (X_REGISTER, a_mode) != NULL) {
      if (strcmp (x_world, "") != 0) {
         /* score update is in world function */
         rc = yjobs_world_register (a_runas, a_file);
         DEBUG_YJOBS   yLOG_value   ("register"  , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "can not register in world file");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else if (strchr ("béB", a_mode) != NULL) {
         g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_FAIL;
         yjobs_act_failure (a_mode, "requested register specifically, but no world file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      } else {
         g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_SKIP;
         g_acts_score  [G_SCORE_WORLD + 1] = G_SCORE_SKIP;
         g_acts_score  [G_SCORE_WORLD + 3] = G_SCORE_SKIP;
         g_acts_score  [G_SCORE_WORLD + 5] = G_SCORE_SKIP;
      }
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_act_footer (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_incomming         (void) { return yjobs_incomming_full   (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }



/*====================------------------------------------====================*/
/*===----                      maintain actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___MAINTAIN___________o (void) {;};

char
yjobs_maintain_full     (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char       *p           = NULL;
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_fuser     [LEN_USER]  = "";
   int         x_fuid      =   -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_fnew      [LEN_DESC]  = "";
   char       *X_ALLDATA   = "#móM";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, x_cdir, x_world, NULL, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS  yLOG_info    ("x_db"      , x_db);
   DEBUG_YJOBS  yLOG_info    ("x_full"    , x_full);
   /*---(security check)-----------------*/
   --rce;  if (strchr ("aèA", a_mode) != NULL) {
      g_acts_score  [G_SCORE_SECURE + 0] = G_SCORE_FAIL;
      rc = yjobs_act_security (a_runas, a_mode, a_oneline, '-');
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central security audit failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_SECURE + 0] = 'a';
   }
   /*---(database)-----------------------*/
   --rce;  if (strchr (X_ALLDATA, a_mode) != NULL) {
      g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;
      if (strcmp (x_db, "") != 0) {
         DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");
         rc = x_callback (YJOBS_READ, "");
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central database did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 1] = 'Ô';
      } else {
         g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;
      }
   }
   /*---(load all files)-----------------*/
   --rce;  if (strchr (X_ALLDATA, a_mode) != NULL) {
      g_acts_score  [G_SCORE_CENTRAL + 3] = G_SCORE_FAIL;
      if (strchr ("kK", a_runas) != NULL) {
         DEBUG_YJOBS   yLOG_note    ("option requires all central files loaded before");
         rc = yjobs_running__pull (a_runas, a_mode, x_cdir, x_callback);
         DEBUG_YJOBS   yLOG_value   ("read files", rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "all central files did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 3] = 'R';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 3] = G_SCORE_SKIP;
      }
   }
   /*---(database statistics)------------*/
   --rce;  if (strchr ("#", a_mode) != NULL) {
      g_acts_score  [G_SCORE_DATABASE + 2] = G_SCORE_FAIL;
      DEBUG_YJOBS   yLOG_note    ("request to produce database/central file statistics");
      rc = x_callback (YJOBS_STATS   , "");
      DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "database could not produce statistics");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_DATABASE + 2] = '#';
   }
   /*---(list)---------------------------*/
   --rce;  if (strchr ("=", a_mode) != NULL)  {
      if (strcmp  (x_world, "") != 0) {
         g_acts_score  [G_SCORE_WORLD   + 2] = G_SCORE_FAIL;
         rc = yjobs_world_list (a_runas);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "world list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD   + 2] = '=';
      } else if (strstr  (x_cdir, "/spool/") != NULL) {
         /* run list of central files */
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         DEBUG_YJOBS   yLOG_value   ("list"      , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 5] = '=';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         yjobs_act_failure (a_mode, "program neither file-based or spool based");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(verify file security)-----------*/
   --rce;  if (strchr ("cýCaèAoöO", a_mode) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("option to verify central file security");
      DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
      if (strcmp (a_file, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL + 1] = G_SCORE_FAIL;
         rc = yjobs_central_old  (a_runas, a_mode, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);
         DEBUG_YJOBS   yLOG_value   ("central"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central file not proper and/or secure");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (strncmp (x_full, "/etc/", 5) == 0)   g_acts_score  [G_SCORE_CENTRAL + 1] = 'e';
         else                                     g_acts_score  [G_SCORE_CENTRAL + 1] = 'c';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 1] = G_SCORE_SKIP;
      }
   }
   /*---(verify file contents)-----------*/
   --rce;  if (strchr ("cýCoöO", a_mode) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("option to verify central file contents");
      DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
      if (strcmp (a_file, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_PULL, x_full);
         DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
         --rce;  if (rc < 0) {
            yjobs_act_failure (a_mode, "central contents not acceptable");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 2] = 'Ö';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_SKIP;
      }
   }
   /*---(verify config contents)---------*/
   --rce;  if (strchr ("aèA", a_mode) != NULL) {
      if (strncmp (x_cdir, "/etc/", 5) == 0) {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_PULL, x_full);
         DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
         --rce;  if (rc < 0) {
            yjobs_act_failure (a_mode, "central contents not acceptable");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 2] = 'Ö';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_SKIP;
      }
   }
   /*---(central report)-----------------*/
   --rce;  if (strchr ("móM", a_mode) != NULL) {
      g_acts_score  [G_SCORE_DATABASE + 3] = G_SCORE_FAIL;
      rc = x_callback (YJOBS_REPORT, a_file);
      DEBUG_YJOBS   yLOG_value   ("report"    , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central report could not complete");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_DATABASE + 3] = 'ó';
   }
   /*---(world audit)--------------------*/
   --rce;  if (strchr ("aèA", a_mode) != NULL) {
      if (strcmp (x_world, "") != 0) {
         g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_FAIL;
         rc = yjobs_world_audit (a_runas);
         DEBUG_YJOBS   yLOG_value   ("world"     , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "world file content audit failed");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD + 0] = 'W';
      }
   }
   /*---(fix)----------------------------*/
   --rce;  if (strchr ("füF", a_mode) != NULL) {
      g_acts_score  [G_SCORE_SECURE + 1] = G_SCORE_FAIL;
      rc = yjobs_act_security (a_runas, a_mode, a_oneline, 'y');
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central security fix failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_SECURE + 1] = 'F';
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_act_footer (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_maintain          (void) { return yjobs_maintain_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

char
yJOBS_act_check         (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar *a_name, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_info    ("allowed"   , IAM_CHECK);
   --rce;  if (a_runas == 0 || strchr (IAM_CHECK, a_runas) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_assim"   , a_assimilate);
   --rce;  if (a_assimilate == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = a_assimilate;
   /*---(verify)-------------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_CHECK {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vcheck, check details of centrally installed job/khronos file");
   } else IF_AUDIT   {
      yURG_msg ('>', "CHECKING %s ===================================", a_name);
   } else IF_DAEMON  {
      yURG_msg ('>', "CHECKING %s ===================================", a_name);
   } else IF_PRICKLY {
      yURG_msg ('>', "CHECKING %s ===================================", a_name);
   } else IF_NORMAL  {
      yURG_msg ('>', "CHECKING %s ===================================", a_name);
   } else IF_STRICT  {
      yURG_msg ('>', "CHECKING %s ===================================", a_name);
   } else {
      DEBUG_YJOBS   yLOG_note    ("action requested is not an check, audit, or daemon type, trouble");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg (' ', "");
   /*---(verify contents)--------------------*/
   rc = s_assimilate (a_runas, YJOBS_CENTRAL, a_name, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("assimilate", rc);
   --rce;  if (rc < 0) {
      IF_VCENTRAL  yURG_msg ('>', "FAILED, centrally installed job/khronos file not runable, the reasons are shown above");
      IF_CCENTRAL  yURG_msg_live ();
      IF_CCHECK    yURG_msg (':', "FAILED, centrally installed job/khronos file not runable, run --vcheck to identify reasons");
      /*> IF_CREVIEW   yURG_msg ('>', "%-30.30s  FAILED, job/khronos file not runable, run --vcheck to identify reasons", a_name);   <*/
      IF_CCENTRAL  yURG_msg_mute ();
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   IF_VCENTRAL  yURG_msg ('>', "SUCCESS, centrally installed job/khronos file runable, all lines checked");
   IF_CCENTRAL  yURG_msg_live ();
   IF_CCHECK    yURG_msg (':', "SUCCESS, centrally installed job/khronos file runable, all lines checked");
   IF_CCENTRAL  yURG_msg_mute ();
   /*---(footer)-------------------------*/
   if (a_act == ACT_VAUDIT || a_act == ACT_VDAEMON) {
      yURG_msg (' ', "");
      yURG_msg ('>', "COMPLETE %s ===================================", a_name);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      outgoing actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___OUTGOING___________o (void) {;};

char
yjobs_outgoing_full     (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char       *p           = NULL;
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_old       [LEN_PATH]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, x_cdir, x_world, NULL, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(load database)----------------------*/
   --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");
         g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_READ, "");
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central database did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 1] = 'Ô';
      } else {
         g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;
      }
   }
   /*---(remove database contents)-----------*/
   --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_CLEAR, x_full);
         DEBUG_YJOBS   yLOG_value   ("clear"     , rc);
         --rce;  if (rc < 0) {
            yjobs_act_failure (a_mode, "contents could not be cleared");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL  + 4] = '×';
      } else {
         g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_SKIP;
      }
   }
   /*---(verify file)------------------------*/
   --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {
      if (strcmp (a_file, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_FAIL;
         rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);
         DEBUG_YJOBS   yLOG_value   ("central"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central file not proper and/or secure");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL  + 1] = 'c';
      } else {
         g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_SKIP;
      }
   }
   /*---(remove file)------------------------*/
   --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {
      if (strcmp (x_db, "") == 0) {
         if (strstr (x_cdir, "/spool/") != NULL) {
            g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_FAIL;
            snprintf (x_old, LEN_PATH, "%s%s", x_cdir, a_file);
            snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);
            DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
            rc = system   (x_cmd);
            DEBUG_YJOBS   yLOG_value   ("system"    , rc);
            --rce;  if (rc < 0) {
               yjobs_act_failure (a_mode, "contents could not be cleared");
               DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
            }
            g_acts_score  [G_SCORE_CENTRAL  + 6] = 'x';
         } else {
            g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;
         }
      } else {
         g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;
      }
   }
   /*---(extract from database)--------------*/
   --rce;  if (strchr ("eìE", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         g_acts_score  [G_SCORE_BACKEND  + 0] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_EXTRACT, x_full);
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "could not extract from database");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_BACKEND  + 0] = 'e';
      }
   }
   /*---(extract file)-----------------------*/
   --rce;  if (strchr ("eìE", a_mode) != NULL) {
      if (strcmp (x_db, "") == 0) {
         g_acts_score  [G_SCORE_BACKEND  + 0] = G_SCORE_FAIL;
         /* copy file down */
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "could not copy from central");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_BACKEND  + 0] = 'E';
      }
   }
   /*---(write database)---------------------*/
   --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_FAIL;
         DEBUG_YJOBS   yLOG_note    ("option requires database saved after");
         rc = x_callback (YJOBS_WRITE, "");
         DEBUG_YJOBS   yLOG_value   ("write db"  , rc);
         if (rc < 0) {
            yjobs_act_failure (a_mode, "central database could not save properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 4] = 'Õ';
      } else {
         g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_SKIP;
      }
   }
   /*---(withdraw)---------------------------*/
   --rce;  if (strchr ("qþQrøR", a_mode) != NULL && strcmp (x_world, "") != 0) {
      rc = yjobs_world_withdraw (a_runas, a_file);
      DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "can not withdraw from world file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_fullacts [30] = 'w';
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_act_footer (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_outgoing          (void) { return yjobs_outgoing_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

char
yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_dir       [LEN_PATH]  = "";
   char        x_old       [LEN_RECD]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_point   ("a_runas"   , a_runas);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove header)------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_REMOVE {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vremove, remove installed job/khronos file if found");
      yURG_msg (' ', "");
   } else {
      DEBUG_YJOBS   yLOG_note    ("action requested is not a remove type, trouble");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify contents)--------------------*/
   rc = yjobs_central_old (a_runas, a_act, a_name, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      if (a_act == ACT_CREMOVE )   yURG_msg_live ();
      if (a_act == ACT_CREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not found/proper, run --vremove to identify reasons");
      if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not found/proper, the reasons are shown above");
      if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove physical)--------------------*/
   yjobs_central_dirs (a_runas, a_act, a_name, "n/a", x_dir, NULL);
   snprintf (x_old, LEN_RECD, "%s%s", x_dir, a_name);
   snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);
   DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));
   --rce;  if (rc < 0 || WIFEXITED (rc) < 0) {
      if (a_act == ACT_CREMOVE )   yURG_msg_live ();
      if (a_act == ACT_CREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, run --vremove for reasons");
      if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, the reasons are shown above");
      if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_act == ACT_CREMOVE )   yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, installed job/khronos file uninstalled.  restart or --reload to retire");
   if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       security audit                         ----===*/
/*====================------------------------------------====================*/
static void      o___SECURITY___________o (void) {;}

char
yjobs_act__fixdir       (char a_issue, tSTAT *s, char n, cchar *a_dir, int a_perms)
{
   char        rc          =    0;
   char        t           [LEN_TERSE] = "";
   sprintf (t, "%4o", a_perms);
   switch (a_issue) {
   case 'e' :
      DEBUG_YJOBS  yLOG_note    ("fixdir attempting create");
      yURG_msg ('+', "set to fix, directory does not exist, attempt to create");
      break;
   case 'o' :
      DEBUG_YJOBS  yLOG_note    ("fixdir attempting change owner");
      yURG_msg ('+', "set to fix, owner was not ¶root¶, attempt to change");
      break;
   case 'g' :
      DEBUG_YJOBS  yLOG_note    ("fixdir attempting change group");
      yURG_msg ('+', "set to fix, group was not ¶root¶, attempt to change");
      break;
   case 'p' :
      DEBUG_YJOBS  yLOG_note    ("fixdir attempting change permissions");
      yURG_msg ('+', "set to fix, permissions were not %s, attempt to change", t);
      break;
   }
   yURG_mkdir (a_dir, "root", "root", t);
   rc = lstat (a_dir, s);
   return rc;
}

char
yjobs_act_checkdir      (char n, cchar *a_dir, int a_perms, char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   int         x_perms     =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("n"         , n);
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   yURG_msg ('-', "checking level %d å%sæ", n, a_dir);
   /*---(check existance)----------------*/
   rc = lstat (a_dir, &s);
   DEBUG_YJOBS   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('o', &s, n, a_dir, a_perms);
      if (rc < 0) {
         yURG_err ('ü', "å%sæ directory does not exist (bad configuration)", a_dir);
         DEBUG_YJOBS   yLOG_note    ("can not open/stat directory");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (S_ISLNK (s.st_mode))  {
      yURG_err ('ü', "å%sæ actually refers to a symbolic link (security risk)", a_dir);
      DEBUG_YJOBS  yLOG_note    ("can not use a symlink");
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISREG (s.st_mode))  {
      yURG_err ('ü', "å%sæ is a regular file, not a directory (bad configuration)", a_dir);
      DEBUG_YJOBS   yLOG_note    ("can not use a regular file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISDIR (s.st_mode))  {
      yURG_err ('ü', "å%sæ is a specialty file (bad configuration)", a_dir);
      DEBUG_YJOBS   yLOG_note    ("can not use a specialty file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "å%sæ directory exists and is not a file/symlink", a_dir);
   /*---(ownership)----------------------*/
   --rce;  if (s.st_uid != 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('o', &s, n, a_dir, a_perms);
      if (s.st_uid != 0) {
         yURG_err ('ü', "å%sæ is not owned by root (security risk)", a_dir);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not owned by root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YJOBS  yLOG_note    ("ownership is root (private)");
   --rce;  if (s.st_gid != 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('g', &s, n, a_dir, a_perms);
      if (s.st_gid != 0) {
         yURG_err ('ü', "å%sæ is not root group (security risk)", a_dir);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not group of root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   yURG_msg ('-', "å%sæ directory owner and group are both root", a_dir);
   DEBUG_YJOBS  yLOG_note    ("owner and group are both root (private)");
   /*---(permissions)--------------------*/
   x_perms = s.st_mode & 07777;
   DEBUG_YJOBS   yLOG_complex ("x_perms"   , "%04o", x_perms);
   DEBUG_YJOBS   yLOG_complex ("a_perms"   , "%04o", a_perms);
   --rce;  if  (x_perms != a_perms)  {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('p', &s, n, a_dir, a_perms);
      x_perms = s.st_mode & 07777;
      if  (x_perms != a_perms)  {
         yURG_err ('ü', "å%sæ perms are %04o, not the requested %04o (security risk)", a_dir, s.st_mode & 07777, a_perms);
         DEBUG_YJOBS   yLOG_note    ("permissions not set correctly (private to user)");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   yURG_msg ('-', "å%sæ directory permissions confirmed as %04o", a_dir, a_perms);
   DEBUG_YJOBS  yLOG_note    ("permissions are appropiate (private)");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_directory     (char n, cchar *a_dir, cchar a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_dir       [LEN_DESC]  = "";
   char        r_dir       [LEN_DESC]  = "";
   char       *p           = NULL;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   ystrlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (l > 0 && x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YJOBS   yLOG_complex ("x_dir"     , "%2då%sæ", l, x_dir);
   /*---(stop recursion)-----------------*/
   --rce;  if (l == 0) {
      DEBUG_YJOBS   yLOG_note    ("bottomed out at root '/'");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   ystrlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   if  (p != NULL)   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YJOBS   yLOG_complex ("r_dir"     , "%2då%sæ", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs_act_directory (n + 1, r_dir, a_fix);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(tail execute)-------------------*/
   l = strlen (x_dir);
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   rc = 0;
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 01777, a_fix);
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else                                         rc = yjobs_act_checkdir (n, x_dir, 0700 , a_fix);
   /*---(handle trouble)-----------------*/
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_security      (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify)-------------------------*/
   /*> yURG_msg ('>', "%s", a_oneline);                                                                             <* 
    *> if (a_act == ACT_VAUDIT )  yURG_msg ('>', "  option --vaudit, check current central setup and security");    <* 
    *> if (a_act == ACT_VDAEMON)  yURG_msg ('>', "  option --vdaemon, verbosely launch in daemon mode");            <* 
    *> if (a_act == ACT_VPRICKLY) yURG_msg ('>', "  option --vprickly, verbosely launch in prickly daemon mode");   <* 
    *> if (a_act == ACT_VNORMAL)  yURG_msg ('>', "  option --vnormal, verbosely launch in normal mode");            <* 
    *> if (a_act == ACT_VSTRICT)  yURG_msg ('>', "  option --vstrict, verbosely launch in strict normal mode");     <* 
    *> yURG_msg (' ', "");                                                                                          <*/
   yURG_msg ('>', "central directory setup/security...");
   /*---(defense)-------------------------------*/
   /*> rc = yjobs_central_dirs  (a_runas, a_act, NULL, "n/a", x_orig, NULL);                   <*/
   rc = yjobs_who_location (a_runas, x_cdir, x_hdir, x_world, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check directories)---------------------*/
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   --rce;  if (strcmp (x_cdir, "") != 0) {
      rc = yjobs_act_directory (0, x_cdir, a_fix);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   if (strcmp (x_hdir, "") != 0) {
      rc = yjobs_act_directory (0, x_hdir, a_fix);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)------------------------------*/
   yURG_msg ('-', "SUCCESS, central directory basic security measures confirmed");
   /*> yURG_msg (' ', "");                                                            <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yJOBS_security      (void) { return yjobs_act_security (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, '-'); }
char yJOBS_fix           (void) { return yjobs_act_security (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, 'y'); }



/*====================------------------------------------====================*/
/*===----                     review a directory                       ----===*/
/*====================------------------------------------====================*/
static void      o___REVIEW_____________o (void) {;}

char
yjobs_act__filter       (cchar *a_name, cchar *a_prefix, int a_muid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || strlen (a_name) <= 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_name"    , a_name);
   /*---(just up/cur dirs)---------------*/
   if      (strcmp (a_name, "." ) == 0 || strcmp (a_name, "..") == 0) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(name quality)-------------------*/
   l = strlen (a_name);
   DEBUG_YJOBS   yLOG_value   ("l"         , l);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_name [i]) == NULL) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(hidden file)--------------------*/
   DEBUG_YJOBS   yLOG_char    ("first char", a_name [0]);
   --rce;  if (a_name [0] == '.') {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(user prefix)--------------------*/
   if (a_muid != 0) {
      if (strncmp (a_name, a_prefix, strlen (a_prefix)) != 0) {
         DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs_act__prepare      (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar a_muser [LEN_USER], cchar *a_regex, char *r_prefix, char *r_dir, void *f_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_dir       [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_act"     , a_act);
   yURG_msg ('>', "central directory review preparation...");
   /*---(defaults)-----------------------*/
   if (r_prefix != NULL)  strcpy (r_prefix, "");
   if (r_dir    != NULL)  strcpy (r_dir   , "");
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_info    ("g_valid"   , g_valid);
   --rce;  if (a_runas == '\0' || strchr (g_valid   , a_runas) == NULL) {
      yURG_err ('f', "a_runas (%c) is not recognized in set å%sæ", a_runas, g_valid);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "a_runas (%c) is acceptable å%sæ", a_runas, g_valid);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yURG_err ('f', "a_oneline is null/empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "a_oneline has been accepted å%sæ", a_oneline);
   DEBUG_YJOBS   yLOG_point   ("a_regex"   , a_regex);
   --rce;  if (a_regex == NULL) {
      yURG_err ('f', "a_regex is null");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_regex"   , a_regex);
   yURG_msg ('-', "a_regex has been accepted å%sæ", a_regex);
   DEBUG_YJOBS   yLOG_point   ("a_muser"   , a_muser);
   --rce;  if (a_muser == NULL) {
      yURG_err ('f', "a_muser is null");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "a_muser has been accepted å%sæ", a_muser);
   DEBUG_YJOBS   yLOG_point   ("r_dir"     , r_dir);
   --rce;  if (r_dir == NULL) {
      yURG_err ('f', "r_dir is null");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_point   ("r_prefix"  , r_prefix);
   --rce;  if (r_prefix == NULL) {
      yURG_err ('f', "r_prefix is null");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_assim"   , f_assimilate);
   --rce;  if (f_assimilate == NULL) {
      yURG_err ('f', "f_assimilate is null");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = f_assimilate;
   /*---(regex)--------------------------*/
   rc = yREGEX_comp (a_regex);
   DEBUG_YJOBS   yLOG_value   ("comp"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("could not compile search");
      yURG_err ('f', "yREGEX_comp did not accept a_regex å%sæ", a_regex);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "regex compiled successfully");
   /*---(get directory)------------------*/
   rc = yjobs_central_dirs  (a_runas, a_act, NULL, "n/a", r_dir, NULL);
   DEBUG_YJOBS   yLOG_info    ("r_dir"     , r_dir);
   --rce;  if (rc < 0) {
      yURG_err ('f', "central dirs location identification failed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "success, preparation is complete");
   /*---(user prefix)--------------------*/
   sprintf (r_prefix, "%s.", a_muser);
   /*---(check security)-----------------*/
   --rce;  switch (a_act) {
   case ACT_AUDIT      : case ACT_CAUDIT     : case ACT_VAUDIT     :
   case ACT_DAEMON     : case ACT_CDAEMON    : case ACT_VDAEMON    :
   case ACT_PRICKLY    : case ACT_CPRICKLY   : case ACT_VPRICKLY   :
   case ACT_NORMAL     : case ACT_CNORMAL    : case ACT_VNORMAL    :
      rc = yjobs_act_security (a_runas, a_act, a_oneline, '-');
      if (rc < 0) {
         IF_CREVIEW   yURG_msg_live ();
         IF_CREVIEW   yURG_msg ('-', "FAILED, central directory insecure, run --vaudit to identify reasons");
         IF_VREVIEW   yURG_msg ('-', "FAILED, central directory insecure, the reasons are shown above");
         IF_CREVIEW   yURG_msg_mute ();
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> review and act on global crontabs -------------------------*/
yJOBS_act_review        (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar a_muser [LEN_USER], int a_muid, cchar *a_regex, void *f_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   int         x_total     =    0;
   int         x_count     =    0;
   int         x_pass      =    0;
   char        x_prefix    [LEN_USER]  = "";
   char        x_central   [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yjobs_act__prepare (a_runas, a_act, a_oneline, a_muser, a_regex, x_prefix, x_central, f_assimilate);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_central" , x_central);
   x_dir = opendir (x_central);
   DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      /*> RUN_USER     printf ("fatal, can not open khronos central directory\n");    <*/
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   while ((x_file = readdir (x_dir)) != NULL) {
      /*---(simple filtering)-------------------*/
      rc = yjobs_act__filter (x_file->d_name, x_prefix, a_muid);
      if (rc != 0)  ++x_total;
      if (rc <= 0) {
         DEBUG_YJOBS   yLOG_note    ("not a valid job/khronos file");
         continue;
      }
      /*---(filter using regex)-----------------*/
      rc = yREGEX_filter (x_file->d_name);
      DEBUG_YJOBS   yLOG_value   ("exec"      , rc);
      if (rc <= 0) {
         DEBUG_YJOBS   yLOG_note    ("does not match regex, skipping");
         continue;
      }
      /*---(actions)----------------------------*/
      switch (a_act) {
      case ACT_LIST      :
         yURG_msg_live ();
         yURG_msg (':', "%s", x_file->d_name);
         yURG_msg_mute ();
         rc = 0;
         break;
      case ACT_AUDIT     : case ACT_CAUDIT    : case ACT_VAUDIT    :
      case ACT_NORMAL    : case ACT_CNORMAL   : case ACT_VNORMAL   :
      case ACT_DAEMON    : case ACT_CDAEMON   : case ACT_VDAEMON   :
      case ACT_PRICKLY   : case ACT_CPRICKLY  : case ACT_VPRICKLY  :
         yURG_msg (' ', "");
         rc = yJOBS_act_check   (a_runas, a_act, a_oneline, x_file->d_name, s_assimilate);
         break;
      }
      ++x_count;
      if (rc >= 0)  ++x_pass;
      DEBUG_YJOBS   yLOG_complex ("counts"    , "%d total, %d count, %d pass", x_total, x_count, x_pass);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("found"     , x_total);
   DEBUG_YJOBS   yLOG_value   ("processed" , x_count);
   DEBUG_YJOBS   yLOG_value   ("passed"    , x_pass);
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(summary)------------------------*/
   rc = 1;
   --rce;  if (x_count <= 0) {
      DEBUG_YJOBS   yLOG_note    ("job/khronos count is zero");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but no job/khronos files found installed in central directory");
      IF_CREVIEW  yURG_msg_live ();
      IF_CREVIEW  yURG_msg (':', "WARNING, secure, but no job/khronos files found installed in central directory");
      IF_CREVIEW  yURG_msg_mute ();
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   --rce;  if (x_count != x_pass) {
      DEBUG_YJOBS   yLOG_note    ("job/khronos count not equal passed");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);
      if (rc == 1) {
         IF_CREVIEW  yURG_msg_live ();
         IF_CREVIEW  yURG_msg (':', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);
         IF_CREVIEW  yURG_msg_mute ();
      }
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   --rce;  if (x_total != x_count) {
      DEBUG_YJOBS   yLOG_note    ("job/khronos count not equal to total files");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);
      if (rc == 1) {
         IF_CREVIEW  yURG_msg_live ();
         IF_CREVIEW  yURG_msg (':', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);
         IF_CREVIEW  yURG_msg_mute ();
      }
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   IF_LIST   rc = 1;
   if (rc == 1) {
      DEBUG_YJOBS   yLOG_note    ("all results golden");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);
      IF_CREVIEW  yURG_msg_live ();
      IF_CREVIEW  yURG_msg (':', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);
      IF_CREVIEW  yURG_msg_mute ();
   }
   DEBUG_YJOBS   yLOG_value   ("x_count"   , x_count);
   if (rc >= 0) {
      if (x_count > 100) x_count = 100;
      rc = x_count;
   }
   DEBUG_YJOBS   yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      outgoing actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___AUDIT_________o (void) {;};

char         /*--> review and act on global crontabs -------------------------*/
yjobs_running__pull     (cchar a_runas, cchar a_mode, cchar *a_cdir, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   int         x_total     =    0;
   int         x_pass      =    0;
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_cwd       [LEN_PATH];
   char        x_name      [LEN_DESC];
   char        x_full      [LEN_PATH];
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   --rce;  switch (a_runas) {
   case  IAM_KHRONOS   : case  IAM_UKHRONOS  :
   case  IAM_HERACLES  : case  IAM_UHERACLES :
      break;
   default :
      DEBUG_YJOBS   yLOG_note    ("runas does not need/allow central file review");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(get current working dir)--------*/
   p = getcwd (x_cwd, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   rc = chdir (a_cdir);
   DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);
   /*---(open directory)-----------------*/
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   x_dir = opendir (a_cdir);
   DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      /*> RUN_USER     printf ("fatal, can not open khronos central directory\n");    <*/
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   while ((x_file = readdir (x_dir)) != NULL) {
      /*---(filter)-----------------------------*/
      if (strcmp (x_file->d_name, "."    ) == 0)  continue;
      if (strcmp (x_file->d_name, ".."   ) == 0)  continue;
      /*---(prepare)----------------------------*/
      ++x_total;
      ystrlcpy (x_name, x_file->d_name, LEN_DESC);
      sprintf (x_full, "%s%s", a_cdir, x_file->d_name);
      /*---(verify file)------------------------*/
      rc = yjobs_central_old  (a_runas, a_mode, x_name, NULL, NULL, NULL, NULL);
      DEBUG_YJOBS   yLOG_value   ("central"   , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "local file not proper and/or secure");
         continue;
      }
      /*---(verify contents)--------------------*/
      rc = x_callback (YJOBS_PULL, x_full);
      DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
      --rce;  if (rc < 0) {
         yjobs_act_failure (a_mode, "local contents not acceptable");
         continue;
      }
      /*---(clear old contents)-----------------*/
      /*> if (strchr (g_audit, a_mode) != NULL || strchr ("hH", a_runas) == NULL) {   <* 
       *>    rc = x_callback (YJOBS_PURGE, NULL);                                     <* 
       *>    DEBUG_YJOBS   yLOG_value   ("purge"     , rc);                           <* 
       *>    --rce;  if (rc < 0) {                                                    <* 
       *>       yjobs_act_failure (a_mode, "could not clear read data");              <* 
       *>       continue;                                                             <* 
       *>    }                                                                        <* 
       *> }                                                                           <*/
      /*---(next)------------------------*/
      ++x_pass;
      DEBUG_YJOBS   yLOG_complex ("counts"    , "%d total, %d pass", x_total, x_pass);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("found"     , x_total);
   DEBUG_YJOBS   yLOG_value   ("passed"    , x_pass);
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = chdir (x_cwd);
   DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

/*> char                                                                              <* 
 *> yjobs_daemonize         (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    int         rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    int         x_running   =    0;                                                <* 
 *>    int         x_uid       =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_ENVI   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(check for other)----------------+/                                       <* 
 *>    x_running  = yEXEC_find ("khronos", NULL);                                     <* 
 *>    x_running += yEXEC_find ("khronos_debug", NULL);                               <* 
 *>    DEBUG_ENVI   yLOG_value   ("x_running" , x_running);                           <* 
 *>    --rce;  if (x_running > 1) {                                                   <* 
 *>       printf ("program is already running in daemon mode\n");                     <* 
 *>       DEBUG_ENVI   yLOG_note    ("program is already running in daemon mode");    <* 
 *>       DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(check for user)-----------------+/                                       <* 
 *>    DEBUG_ENVI   yLOG_value   ("my.m_uid"  , my.m_uid);                            <* 
 *>    --rce;  if (my.m_uid != 0) {                                                   <* 
 *>       printf ("only root can run daemon mode\n");                                 <* 
 *>       DEBUG_ENVI   yLOG_note    ("only root can run daemon mode");                <* 
 *>       DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(fork off and die)---------------+/                                       <* 
 *>    DEBUG_ENVI   yLOG_value   ("logger"    , yLOGS_lognum ());                     <* 
 *>    rc = yEXEC_daemon (yLOGS_lognum (), &(my.m_pid));                              <* 
 *>    DEBUG_ENVI   yLOG_value   ("daemon"    , rc);                                  <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       printf ("program could not be daemonized\n");                               <* 
 *>       DEBUG_ENVI   yLOG_note    ("program could not be daemonized");              <* 
 *>       DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(signals)-------------------------------+/                                <* 
 *>    yEXEC_signal (YEXEC_HARD, YEXEC_NO, YEXEC_NO, EXEC_comm, "stdsig");            <* 
 *>    DEBUG_ENVI   yLOG_value   ("signals"   , rc);                                  <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       printf ("program sigals could not be set properly\n");                      <* 
 *>       DEBUG_ENVI   yLOG_note    ("program signals cound not be set properly");    <* 
 *>       DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(complete)------------------------------+/                                <* 
 *>    DEBUG_ENVI   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
yjobs_running_full      (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_fuser     [LEN_USER]  = "";
   int         x_fuid      =   -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (strchr (g_running, a_mode) != NULL)  ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, NULL, NULL, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for full database)------------*/
   rc = yjobs_who_location (a_runas, NULL, x_hdir, NULL, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strcmp (x_db, "") != 0)   {
      DEBUG_YJOBS   yLOG_note    ("option requires central database loaded before");
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central database did not load properly");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_fullacts  [20] = 'R';
   }
   /*---(load all files)---------------------*/
   --rce;  if (strchr ("kK", a_runas) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("option requires all files loaded before");
      rc = yjobs_running__pull (a_runas, a_mode, x_cdir, x_callback);
      DEBUG_YJOBS   yLOG_value   ("read files", rc);
      g_fullacts  [20] = 'R';
   }
   /*---(verify file)------------------------*/
   --rce;  if (strchr ("eEhH", a_runas) != NULL) {
      rc = yjobs_central_old  (a_runas, a_mode, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);
      DEBUG_YJOBS   yLOG_value   ("central"   , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central file not proper and/or secure");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_fullacts  [ 8] = 'c';
   }
   /*---(load specific file)-----------------*/
   --rce;  if (strchr ("eEhH", a_runas) != NULL) {
      rc = x_callback (YJOBS_PULL, x_full);
      DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
      --rce;  if (rc < 0) {
         yjobs_act_failure (a_mode, "local contents not acceptable");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(show footer)--------------------*/
   if (strchr (g_running, a_mode) != NULL) {
      if (rc > 0)  yURG_err (' ', "");
      rc = yjobs_act_footer (a_mode);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_running           (void) { return yjobs_running_full     (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


char
yjobs_gather_full       (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_fuser     [LEN_USER]  = "";
   int         x_fuid      =   -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_update    =  '·';
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (strchr (g_running, a_mode) != NULL)  ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, NULL, NULL, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for full database)------------*/
   rc = yjobs_who_location (a_runas, NULL, x_hdir, NULL, &x_update, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_update == 'U' && strcmp (x_db, "") != 0)   {
      DEBUG_YJOBS   yLOG_note    ("option requires central database loaded before");
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      if (rc < 0) {
         yjobs_act_failure (a_mode, "central database did not load properly");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_fullacts  [20] = 'R';
   }
   /*---(gather all data)--------------------*/
   --rce;  if (strchr ("lL", a_runas) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("option requires all files loaded before");
      rc = x_callback (YJOBS_GATHER, "");
      DEBUG_YJOBS   yLOG_value   ("gather"    , rc);
      --rce;  if (rc < 0) {
         yjobs_act_failure (a_mode, "local contents not acceptable");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*> g_fullacts  [20] = 'R';                                                     <*/
   }
   /*---(show footer)--------------------*/
   if (strchr (g_running, a_mode) != NULL) {
      if (rc > 0)  yURG_err (' ', "");
      rc = yjobs_act_footer (a_mode);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char yjobs_gather            (void) { return yjobs_gather_full      (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


