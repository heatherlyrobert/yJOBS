/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



static char       *X_AUDIT     = "aèA";



char
yjobs__maint_secure     (char a_runas, char a_mode, char a_oneline [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_fix       =  '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("security review/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(prepare)------------------------*/
   if (strchr (g_fix, a_mode) != NULL)  x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);
   if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_FAIL);
   /*---(review)-------------------------*/
   rc = yjobs_dir_review (a_runas, a_mode, a_oneline, x_fix);
   DEBUG_YJOBS   yLOG_value   ("security"  , rc);
   if (rc < 0) {
      if (x_fix != 'y')  yjobs_ends_failure (a_mode, "central security audit failed");
      else               yjobs_ends_failure (a_mode, "central security fix failed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, 'a');
   if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'f');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_maint_security    (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
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
    *> if (a_mode == ACT_VAUDIT )  yURG_msg ('>', "  option --vaudit, check current central setup and security");    <* 
    *> if (a_mode == ACT_VDAEMON)  yURG_msg ('>', "  option --vdaemon, verbosely launch in daemon mode");            <* 
    *> if (a_mode == ACT_VPRICKLY) yURG_msg ('>', "  option --vprickly, verbosely launch in prickly daemon mode");   <* 
    *> if (a_mode == ACT_VNORMAL)  yURG_msg ('>', "  option --vnormal, verbosely launch in normal mode");            <* 
    *> if (a_mode == ACT_VSTRICT)  yURG_msg ('>', "  option --vstrict, verbosely launch in strict normal mode");     <* 
    *> yURG_msg (' ', "");                                                                                          <*/
   yURG_msg ('>', "central directory setup/security...");
   /*---(defense)-------------------------------*/
   /*> rc = yjobs_central_dirs  (a_runas, a_mode, NULL, "n/a", x_orig, NULL);                   <*/
   rc = yjobs_who_location (a_runas, x_cdir, x_hdir, x_world, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check directories)---------------------*/
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   --rce;  if (strcmp (x_cdir, "") != 0) {
      rc = yjobs_dir_single (0, x_cdir, a_fix);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = rc;
   }
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   if (strcmp (x_hdir, "") != 0) {
      rc = yjobs_dir_single (0, x_hdir, a_fix);
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

char
yjobs__maint_stats      (char a_mode, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode != ACT_STATS) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_schar   (a_mode);
      DEBUG_YJOBS   yLOG_schar   (ACT_STATS);
      DEBUG_YJOBS   yLOG_snote   ("statistics not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_DATABASE,  2, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_note    ("FATAL, host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("request to produce database/central file statistics");
   x_callback = f_callback;
   rc = x_callback (YJOBS_STATS, "");
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "database could not produce statistics");
      DEBUG_YJOBS   yLOG_note    ("FATAL, database could not produce statistics");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_DATABASE,  2, '#');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

/*> char                                                                                                        <* 
 *> yjobs__maint_files      (char a_mode, char a_cdir [LEN_DESC], char a_world [LEN_LABEL], void *f_callback)   <* 
 *> {                                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                 <* 
 *>    char        rce         =  -10;                                                                          <* 
 *>    int         rc          =    0;                                                                          <* 
 *>    /+---(quick-out)----------------------+/                                                                 <* 
 *>    if (a_mode == 0 || strchr (g_act_pul, a_mode) == NULL) {                                                 <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                                            <* 
 *>       DEBUG_YJOBS   yLOG_schar   (a_mode);                                                                  <* 
 *>       DEBUG_YJOBS   yLOG_snote   (g_act_pul);                                                               <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("list not requested");                                                    <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                                            <* 
 *>       return 0;                                                                                             <* 
 *>    }                                                                                                        <* 
 *>    /+---(header)-------------------------+/                                                                 <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                                               <* 
 *>    DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);                                                       <* 
 *>    /+---(config)-------------------------+/                                                                 <* 
 *>    --rce;  if (strchr ("=", a_mode) != NULL)  {                                                             <* 
 *>       if (strcmp  (a_world, "") != 0) {                                                                     <* 
 *>          g_acts_score  [G_SCORE_WORLD   + 2] = G_SCORE_FAIL;                                                <* 
 *>          rc = yjobs_world_list (a_runas);                                                                   <* 
 *>          if (rc < 0) {                                                                                      <* 
 *>             yjobs_ends_failure (a_mode, "world list did not run");                                          <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
 *>             return rce;                                                                                     <* 
 *>          }                                                                                                  <* 
 *>          g_acts_score  [G_SCORE_WORLD   + 2] = '=';                                                         <* 
 *>       } else if (strstr  (a_cdir, "/spool/") != NULL) {                                                     <* 
 *>          /+ run list of central files +/                                                                    <* 
 *>          g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;                                                <* 
 *>          DEBUG_YJOBS   yLOG_value   ("list"      , rc);                                                     <* 
 *>          if (rc < 0) {                                                                                      <* 
 *>             yjobs_ends_failure (a_mode, "central list did not run");                                        <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
 *>             return rce;                                                                                     <* 
 *>          }                                                                                                  <* 
 *>          g_acts_score  [G_SCORE_CENTRAL + 5] = '=';                                                         <* 
 *>       } else {                                                                                              <* 
 *>          g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;                                                <* 
 *>          yjobs_ends_failure (a_mode, "program neither file-based or spool based");                          <* 
 *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                    <* 
 *>          return rce;                                                                                        <* 
 *>       }                                                                                                     <* 
 *>    }                                                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                 <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                               <* 
 *>    return RC_POSITIVE;                                                                                      <* 
 *> }                                                                                                           <*/

char
yjobs__maint_config     (char a_runas, char a_mode, char a_cdir [LEN_DESC], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_fix       =  '-';
   char        x_etc       =  '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("configuration audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("c_hardfail", c_hardfail);
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir       == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   /*---(title)---------------------------------*/
   yURG_msg ('>', "configuration directory setup/security review...");
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_SKIP);
   if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_SKIP);
   /*---(no configuration)----------------------*/
   if (strcmp (a_cdir, "") == 0) {
      yURG_msg ('-', "skipping, no configuration directory specified for application");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "configuration audit not provided host callback function");
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_note    ("FATAL, host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set etc)-------------------------------*/
   if (strstr  (a_cdir, "/etc/") != NULL)    x_etc = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_etc"     , x_etc);
   /*---(default score)-------------------------*/
   if (a_mode != '=')  {
      rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);
      if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_FAIL);
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, G_SCORE_SKIP);
      if (x_etc == 'y')    rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, G_SCORE_SKIP);
      else                 rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, G_SCORE_SKIP);
   } else {
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  5, G_SCORE_FAIL);
   }
   /*---(check directory)-----------------------*/
   rc = yjobs_dir_single (0, a_cdir, x_fix);
   DEBUG_YJOBS   yLOG_value   ("single"    , rc);
   --rce;  if (rc <  0) {
      yjobs_ends_score (G_SCORE_CENTRAL ,  1, G_SCORE_FAIL);
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "warning, configuration directory has issues");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_FATAL;
   } else if (rc == RC_REPAIR) {
      yURG_msg ('-', "repaired, configuration directory basic security measures updated");
      rc_final = RC_REPAIR;
   } else {
      yURG_msg ('-', "success, configuration directory basic security measures confirmed");
      rc_final = RC_POSITIVE;
   }
   if (x_etc == 'y')   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, 'e');
   else                rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, 'c');
   DEBUG_YJOBS   yLOG_value   ("post-score", rc);
   /*---(check files)---------------------------*/
   rc = yjobs_share_review (__FUNCTION__, 'm', a_runas, a_mode, f_callback, '-');
   DEBUG_YJOBS   yLOG_value   ("files"     , rc);
   if (rc <  0) {
      if (a_mode != '=') {
         if (x_etc == 'y')  rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, G_SCORE_FAIL);
         else               rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, G_SCORE_FAIL);
      } else {
         rc = yjobs_ends_score (G_SCORE_CENTRAL ,  5, G_SCORE_FAIL);
      }
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   if (rc > rc_final)  rc_final = rc;
   /*---(score end)----------------------*/
   if (a_mode != '=') {
      if (x_etc == 'y') {
         DEBUG_YJOBS   yLOG_note    ("retain data from /etc/ config file");
         rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, 'Ö');
      } else {
         if (a_mode != 0 && strchr (g_act_kep, a_mode) != NULL) {
            DEBUG_YJOBS   yLOG_note    ("retain data from all file pulls");
            rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, 'R');
         } else {
            DEBUG_YJOBS   yLOG_note    ("purge each file pulled");
            rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, 'r');
         }
      }
   } else {
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  5, '=');
   }
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_check      (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_file [LEN_LABEL], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_user      [LEN_USER]  = "";
   int         x_uid       =    0;
   char        x_fix       =  '-';
   char        x_full      [LEN_PATH]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_chk, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_chk);
      DEBUG_YJOBS   yLOG_snote   ("single file review not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "configuration single file review...");
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, G_SCORE_SKIP);
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, G_SCORE_SKIP);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(running as)---------------------*/
   rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, NULL, x_user, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "currently running as å%sæ (%d)", x_user, x_uid);
   /*---(directory)-----------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir == NULL || a_cdir [0] == '\0') {
      yURG_err ('f', "could not identify configuration directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration directory is å%sæ", a_cdir);
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file  == NULL || a_file [0] == '\0') {
      yURG_err ('f', "could not identify configuration file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration file is å%sæ", a_file);
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(prepare)------------------------*/
   sprintf (x_full, "%s%s", a_cdir, a_file);
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   yURG_msg ('-', "fully qualified file name å%sæ", x_full);
   /*---(check file)---------------------*/
   rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (strstr  (x_full, "/etc/") != NULL)       rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, 'e');
   else                                         rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, 'c');
   DEBUG_YJOBS   yLOG_value   ("post-score", rc);
   /*---(verify contents-----------------*/
   rc = x_callback (YJOBS_PULL , x_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   if      (rc >  1)  { rc_final = RC_WARNING;  rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, 'Ö');          }
   else if (rc == 1)  { rc_final = RC_POSITIVE; rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, 'Ö');          }
   else if (rc == 0)  { rc_final = RC_POSITIVE; rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, 'Ö');          }
   else               { rc_final = RC_FATAL;    rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, G_SCORE_FAIL); }
   /*---(clear data)---------------------*/
   rc = x_callback (YJOBS_PURGE, x_full);
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   if (rc < 0)  {
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else if (rc >= 4) {
      yURG_msg ('-', "warning, trouble with audit, see details above");
   }
   /*---(wrap up)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_central    (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL], char a_database [LEN_LABEL], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_fix       =  '-';
   char        x_hdir      [LEN_DESC]  = "";
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("configuration audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(title)---------------------------------*/
   yURG_msg ('>', "central data directory setup/security review...");
   /*---(get location data)--------------*/
   rc = yjobs_who_location (a_runas, NULL, x_hdir, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (strcmp (x_hdir, "") == 0) {
      yURG_msg ('-', "skipping, no central data directory specified for application");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)  x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   /*---(check directory)-----------------------*/
   rc = yjobs_dir_single (0, x_hdir, x_fix);
   DEBUG_YJOBS   yLOG_value   ("single"    , rc);
   --rce;  if (rc <  0) {
      if (c_hardfail == 'y') {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "warning, central data directory has issues");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 4;
   } else if (rc == RC_REPAIR) {
      yURG_msg ('-', "repaired, central data directory basic security measures updated");
      rc_final = RC_REPAIR;
   } else {
      yURG_msg ('-', "success, central data directory basic security measures confirmed");
      rc_final = RC_POSITIVE;
   }
   /*---(audit world file)----------------------*/
   if (strcmp (a_world, "") == 0) {
      yURG_msg ('>', "audit the central world file...");
      yURG_msg ('-', "no world file specified for this host");
   } else {
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, G_SCORE_FAIL);
      rc = yjobs_world_audit (a_runas);
      DEBUG_YJOBS   yLOG_value   ("world"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "world file content audit failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, 'w');
   }
   /*---(audit database)------------------------*/
   if (strcmp (a_database, "") == 0) {
      yURG_msg ('>', "audit the central database...");
      yURG_msg ('-', "no database specified for this host");
   } else {
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, G_SCORE_FAIL);
      rc = yjobs_world_audit (a_runas);
      DEBUG_YJOBS   yLOG_value   ("database"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "database content audit failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, 'w');
   }
   /*---(score end)----------------------*/
   if (a_mode != '=')  {
      rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, 'a');
      if (x_fix == 'y')  {
         if (rc_final == RC_REPAIR)  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'F');
         else                        rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'f');
      }
      DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__maint_report     (char a_mode, char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_rpt, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_rpt);
      DEBUG_YJOBS   yLOG_snote   ("central data reporting not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_DATABASE,  3, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_note    ("FATAL, host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("request to produce database/central data report");
   x_callback = f_callback;
   rc = x_callback (YJOBS_REPORT, a_file);
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "central data/host could not produce report");
      DEBUG_YJOBS   yLOG_note    ("FATAL, central data/host could not produce report");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_DATABASE,  3, 'ó');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER___________o (void) {;};

char
yjobs_maint_full        (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_share_prepare ("yjobs__maint_prepare", 'm', a_runas, a_mode, a_oneline, a_file, f_callback, x_cdir, x_hdir, x_world, x_db, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check/load config)--------------*/
   rc = yjobs__maint_config   (a_runas, a_mode, x_cdir, f_callback, '-');
   DEBUG_YJOBS   yLOG_value   ("config"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check sinsle)-------------------*/
   rc = yjobs__maint_check    (a_runas, a_mode, x_cdir, a_file, f_callback, '-');
   DEBUG_YJOBS   yLOG_value   ("check"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(check/load data)----------------*/
   rc = yjobs__maint_central  (a_runas, a_mode, x_hdir, x_world, x_db, f_callback, '-');
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_share_readdb   ("yjobs__maint_readdb", 'm', a_mode, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(generate statistics)------------*/
   rc = yjobs__maint_stats    (a_mode, f_callback);
   DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(generate report)----------------*/
   rc = yjobs__maint_report   (a_mode, a_file, f_callback);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(footer)-------------------------*/
   switch (rc_final) {
   case RC_ACK      :
   case RC_POSITIVE :  rc = yjobs_ends_success  (a_mode);                    rc = RC_POSITIVE;   break;
   case RC_OVERRIDE :  rc = yjobs_ends_approved (a_mode);                    rc = RC_OVERRIDE;   break;
   case RC_REPAIR   :  rc = yjobs_ends_repaired (a_mode);                    rc = RC_REPAIR;     break;
   case RC_WARNING  :  rc = yjobs_ends_warning  (a_mode);                    rc = RC_WARNING;    break;
   case RC_FATAL    :  rc = yjobs_ends_failure  (a_mode, "serious errors");  rc = RC_FATAL;      break;
   default          :  rc = yjobs_ends_failure  (a_mode, "serious errors");  rc = rce;           break;
   }
   DEBUG_YJOBS   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_maint_full_OLD    (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
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
   /*> ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);                               <* 
    *> /+---(defense)------------------------+/                                       <* 
    *> DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);                             <* 
    *> DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);                           <* 
    *> --rce;  if (a_oneline == NULL) {                                               <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);                          <* 
    *> --rce;  if (f_callback == NULL) {                                              <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> x_callback = f_callback;                                                       <*/
   /*---(show header)--------------------*/
   /*> rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, x_world, x_db, NULL, x_full);   <* 
    *> DEBUG_YJOBS   yLOG_value   ("header"    , rc);                                                            <* 
    *> if (rc < 0) {                                                                                             <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
    *>    return rce;                                                                                            <* 
    *> }                                                                                                         <*/
   /*> DEBUG_YJOBS  yLOG_info    ("x_world"   , x_world);                             <* 
    *> DEBUG_YJOBS  yLOG_info    ("x_db"      , x_db);                                <* 
    *> DEBUG_YJOBS  yLOG_info    ("x_full"    , x_full);                              <*/
   /*---(security check)-----------------*/
   /*> --rce;  if (strchr ("aèA", a_mode) != NULL) {                                  <* 
    *>    yjobs_ends_score (G_SCORE_SECURE,  0, G_SCORE_FAIL);                        <* 
    *>    g_acts_score  [G_SCORE_SECURE + 0] = G_SCORE_FAIL;                          <* 
    *>    rc = yjobs_dir_review (a_runas, a_mode, a_oneline, '-');                    <* 
    *>    DEBUG_YJOBS   yLOG_value   ("security"  , rc);                              <* 
    *>    if (rc < 0) {                                                               <* 
    *>       yjobs_ends_failure (a_mode, "central security audit failed");            <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *>    g_acts_score  [G_SCORE_SECURE + 0] = 'a';                                   <* 
    *> }                                                                              <*/
   /*---(database)-----------------------*/
   /*> --rce;  if (strchr (X_ALLDATA, a_mode) != NULL) {                                 <* 
    *>    g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;                           <* 
    *>    if (strcmp (x_db, "") != 0) {                                                  <* 
    *>       DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");      <* 
    *>       rc = x_callback (YJOBS_READ, "");                                           <* 
    *>       DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                              <* 
    *>       if (rc < 0) {                                                               <* 
    *>          yjobs_ends_failure (a_mode, "central database did not load properly");   <* 
    *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>          return rce;                                                              <* 
    *>       }                                                                           <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 1] = 'Ô';                                 <* 
    *>    } else {                                                                       <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;                        <* 
    *>    }                                                                              <* 
    *> }                                                                                 <*/
   /*---(load all files)-----------------*/
   --rce;  if (strchr (X_ALLDATA, a_mode) != NULL) {
      g_acts_score  [G_SCORE_CENTRAL + 3] = G_SCORE_FAIL;
      if (strchr ("kK", a_runas) != NULL) {
         DEBUG_YJOBS   yLOG_note    ("option requires all central files loaded before");
         rc = yjobs_running__pull (a_runas, a_mode, x_cdir, x_callback);
         DEBUG_YJOBS   yLOG_value   ("read files", rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "all central files did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 3] = 'R';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 3] = G_SCORE_SKIP;
      }
   }
   /*---(database statistics)------------*/
   /*> --rce;  if (strchr ("#", a_mode) != NULL) {                                              <* 
    *>    g_acts_score  [G_SCORE_DATABASE + 2] = G_SCORE_FAIL;                                  <* 
    *>    DEBUG_YJOBS   yLOG_note    ("request to produce database/central file statistics");   <* 
    *>    rc = x_callback (YJOBS_STATS   , "");                                                 <* 
    *>    DEBUG_YJOBS   yLOG_value   ("stats"     , rc);                                        <* 
    *>    if (rc < 0) {                                                                         <* 
    *>       yjobs_ends_failure (a_mode, "database could not produce statistics");              <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                    <* 
    *>       return rce;                                                                        <* 
    *>    }                                                                                     <* 
    *>    g_acts_score  [G_SCORE_DATABASE + 2] = '#';                                           <* 
    *> }                                                                                        <*/
   /*---(list)---------------------------*/
   --rce;  if (strchr ("=", a_mode) != NULL)  {
      if (strcmp  (x_world, "") != 0) {
         g_acts_score  [G_SCORE_WORLD   + 2] = G_SCORE_FAIL;
         rc = yjobs_world_list (a_runas);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "world list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD   + 2] = '=';
      } else if (strstr  (x_cdir, "/spool/") != NULL) {
         /* run list of central files */
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         DEBUG_YJOBS   yLOG_value   ("list"      , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "central list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 5] = '=';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         yjobs_ends_failure (a_mode, "program neither file-based or spool based");
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
            yjobs_ends_failure (a_mode, "central file not proper and/or secure");
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
            yjobs_ends_failure (a_mode, "central contents not acceptable");
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
            yjobs_ends_failure (a_mode, "central contents not acceptable");
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
         yjobs_ends_failure (a_mode, "central report could not complete");
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
            yjobs_ends_failure (a_mode, "world file content audit failed");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD + 0] = 'w';
      }
   }
   /*---(fix)----------------------------*/
   /*> --rce;  if (strchr ("füF", a_mode) != NULL) {                                  <* 
    *>    g_acts_score  [G_SCORE_SECURE + 1] = G_SCORE_FAIL;                          <* 
    *>    rc = yjobs_dir_review (a_runas, a_mode, a_oneline, 'y');                    <* 
    *>    DEBUG_YJOBS   yLOG_value   ("security"  , rc);                              <* 
    *>    if (rc < 0) {                                                               <* 
    *>       yjobs_ends_failure (a_mode, "central security fix failed");              <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *>    g_acts_score  [G_SCORE_SECURE + 1] = 'f';                                   <* 
    *> }                                                                              <*/
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_ends_success (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_maint             (void) { return yjobs_maint_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


