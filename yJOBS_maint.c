/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                      directory audits                        ----===*/
/*====================------------------------------------====================*/
static void      o___DIRECTORY________o (void) {;};

char
yjobs_maint__dir        (char a_label [LEN_LABEL], char a_dir [LEN_DESC], char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_dir       [LEN_DESC]  = "";
   char        x_next      [LEN_DESC]  = "";
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
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
   c = ystrldcnt (x_dir, '/', LEN_DESC);
   /*---(stop recursion)-----------------*/
   --rce;  if (l == 0) {
      DEBUG_YJOBS   yLOG_note    ("bottomed out at root '/'");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   ystrlcpy (x_next, x_dir, LEN_DESC);
   p = strrchr (x_next, '/');
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   if  (p != NULL)   p [0] = '\0';
   l = strlen (x_next);
   DEBUG_YJOBS   yLOG_complex ("x_next"    , "%2då%sæ", l, x_next);
   /*---(recurse)------------------------*/
   rc = yjobs_maint__dir (a_label, x_next, a_fix);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(tail execute)-------------------*/
   yURG_msg ('>', "auditing %s directory level (%d)...", a_label, c);
   l = strlen (x_dir);
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   rc = 0;
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "f_nodel"  );
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yENV_audit_centraldir (a_fix, x_dir, "d_normal" );
   else                                         rc = yENV_audit_centraldir (a_fix, x_dir, "d_tight"  );
   /*---(handle trouble)-----------------*/
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(finish)----------------------*/
   yURG_msg ('-', "success, %s directory acceptable", a_label);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_maint_dir         (char a_runas, char a_mode, char a_label [LEN_LABEL], char a_dir [LEN_DESC], char *r_use, char *r_good)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_fix       =  '-';
   char        x_etc       =  '-';
   char        x_which     =  '-';
   char        t           [LEN_HUND]  = "";
   char        x_use       =  '-';
   /*---(defaults)-----------------------*/
   if (r_use  != NULL)  *r_use  = '-';
   if (r_good != NULL)  *r_good = '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   (a_label);
      DEBUG_YJOBS   yLOG_snote   ("audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_label"   , a_label);
   /*---(score)--------------------------*/
   --rce; if (strncmp (a_label, "conf", 4) == 0)  { x_use = 'c';  g_acts_score  [G_SCORE_SCONF  ] = '-';  }
   else if   (strncmp (a_label, "cent", 4) == 0)  { x_use = 'd';  g_acts_score  [G_SCORE_SDATA  ] = '-';  }
   else {
      DEBUG_YJOBS   yLOG_note    ("can not interpret a_label");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_char    ("x_use"     , x_use);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL) {
      yURG_msg ('>', "auditing %s directory...", a_label);
      yURG_err ('f', "%s directory is NULL", a_label);
      snprintf (t, LEN_HUND, "%s directory is not secure/proper", a_label);
      yjobs_ends_failure (a_mode, t);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(no directory given)-------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   if (strcmp (a_dir, "")  == 0) {
      yURG_msg ('>', "auditing %s directory...", a_label);
      snprintf (t, LEN_HUND, "skipping, not configured for %s directory", a_label);
      yURG_msg ('-', t);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(score)---------------------------------*/
   if      (x_use == 'c')  g_acts_score  [G_SCORE_SCONF  ] = '°';
   else if (x_use == 'd')  g_acts_score  [G_SCORE_SDATA  ] = '°';
   if (r_use  != NULL)  *r_use  = 'y';
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'F';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   if (a_dir != NULL && strstr  (a_dir, "/etc/") != NULL)    x_etc = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_etc"     , x_etc);
   /*---(call audit)----------------------------*/
   rc = yjobs_maint__dir  (a_label, a_dir, x_fix);
   DEBUG_YJOBS   yLOG_value   ("dir"       , rc);
   --rce;  if (rc < 0) {
      snprintf (t, LEN_HUND, "%s directory is not secure/proper", a_label);
      yjobs_ends_failure (a_mode, t);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)---------------------------------*/
   if        (x_use == 'c') {
      if (rc == RC_REPAIR)  g_acts_score  [G_SCORE_SCONF  ] = 'C';
      else                  g_acts_score  [G_SCORE_SCONF  ] = 'c';
   } else if (x_use == 'd') {
      if (rc == RC_REPAIR)  g_acts_score  [G_SCORE_SDATA  ] = 'D';
      else                  g_acts_score  [G_SCORE_SDATA  ] = 'd';
   }
   if (r_good != NULL)  *r_good = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         data audits                          ----===*/
/*====================------------------------------------====================*/
static void      o___DATA_____________o (void) {;};

char
yjobs__maint_config     (char a_runas, char a_mode, char a_cdir [LEN_DESC], void *f_callback, char c_hardfail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    =    1;
   char        x_fix       =  '-';
   char        x_etc       =  '-';
   char      (*x_callback)   (cchar a_req, cchar *a_full);
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
   yURG_msg ('>', "configuration directory setup/security review...");
   DEBUG_YJOBS   yLOG_char    ("c_hardfail", c_hardfail);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir  == NULL || a_cdir  [0] == '\0') {
      yjobs_ends_failure (a_mode, "configuration directory is null/empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   if (a_cdir != NULL && strstr  (a_cdir, "/etc/") != NULL)    x_etc = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_etc"     , x_etc);
   /*---(verify)----------------------*/
   /*> rc = yENV_audit_localdir (a_dir, r_full, NULL, r_fuser);                              <* 
    *> /+> rc = yjobs__in_dir    (a_runas, a_mode, a_file, r_fuser, r_fdir, r_full);   <+/   <* 
    *> DEBUG_YJOBS   yLOG_value   ("localdir"  , rc);                                        <* 
    *> if (rc < 0) {                                                                         <* 
    *>    yjobs_ends_failure (a_mode, "local file not proper and/or secure");                <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                    <* 
    *>    return rce;                                                                        <* 
    *> }                                                                                     <*/







   /*---(set defaults)--------------------------*/
   if (a_mode != '=')  {
      rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);
      if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_FAIL);
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  1, G_SCORE_SKIP);
      if (x_etc == 'y')    rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, G_SCORE_SKIP);
      else                 rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, G_SCORE_SKIP);
   } else {
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  5, G_SCORE_FAIL);
   }
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir       == NULL) {
      yURG_err ('f', "configuration directory is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(quick-out)----------------------*/
   --rce;  if (strcmp (a_cdir, "") == 0) {
      yURG_msg ('-', "skipping, no configuration directory specified for application");
      rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_SKIP);
      if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
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
   if (x_etc == 'y') {
      DEBUG_YJOBS   yLOG_note    ("retain data from /etc/ config file");
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  2, 'Ö');
   } else {
      if (a_mode != 0 && strchr (g_act_kep, a_mode) != NULL) {
         DEBUG_YJOBS   yLOG_note    ("retain data from all file pulls");
         rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, 'R');
      } else if (x_etc != 'y') {
         DEBUG_YJOBS   yLOG_note    ("purge each file pulled");
         rc = yjobs_ends_score (G_SCORE_CENTRAL ,  3, 'r');
      }
   }
   if (a_mode == '=') {
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
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
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
   DEBUG_YJOBS   yLOG_char    ("c_hardfail", c_hardfail);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);
   if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, G_SCORE_FAIL);
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_hdir"    , a_hdir);
   --rce;  if (a_hdir       == NULL) {
      yURG_err ('f', "central data directory is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_hdir"    , a_hdir);
   --rce;  if (strcmp (a_hdir, "") == 0) {
      DEBUG_YJOBS   yLOG_point   ("a_world"   , a_world);
      if (a_world    != NULL && a_world [0]    != '\0') {
         yURG_err ('f', "configured for world file, but no central data directory (illegal setup)");
         yjobs_ends_failure (a_mode, "host program configuration is illegal");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_database != NULL && a_database [0] != '\0') {
         yURG_err ('f', "configured for database, but no central data directory (illegal setup)");
         yjobs_ends_failure (a_mode, "host program configuration is illegal");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "skipping, no central data directory specified for application");
      rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, 'a');
      if (x_fix == 'y')  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'f');
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check directory)-----------------------*/
   rc = yjobs_dir_single (0, a_hdir, x_fix);
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
   DEBUG_YJOBS   yLOG_point   ("a_world"   , a_world);
   if (a_world == NULL || strcmp (a_world, "") == 0) {
      yURG_msg ('>', "audit the central world file...");
      yURG_msg ('-', "no world file specified for this host");
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, G_SCORE_SKIP);
      rc = yjobs_ends_score (G_SCORE_WORLD,  1, G_SCORE_SKIP);
   } else {
      DEBUG_YJOBS   yLOG_info    ("a_world"   , a_world);
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, G_SCORE_FAIL);
      rc = yjobs_ends_score (G_SCORE_WORLD,  1, G_SCORE_FAIL);
      /*---(check file)-------------------------*/
      rc = yjobs_central_data (a_hdir, a_world, x_fix);
      DEBUG_YJOBS   yLOG_value   ("data"      , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "world file does not exist or is not properly secured");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      rc = yjobs_ends_score (G_SCORE_WORLD,  0, 'w');
      /*---(check contents)---------------------*/
      rc = yjobs_world_audit (a_runas, a_mode, a_hdir, a_world);
      DEBUG_YJOBS   yLOG_value   ("world"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "world file content audit failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      rc = yjobs_ends_score (G_SCORE_WORLD,  1, 'Ô');
   }
   /*---(audit database)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_database", a_database);
   if (strcmp (a_database, "") == 0) {
      yURG_msg ('>', "audit the central database...");
      yURG_msg ('-', "no database specified for this host");
      rc = yjobs_ends_score (G_SCORE_DATABASE,  0, G_SCORE_SKIP);
      rc = yjobs_ends_score (G_SCORE_DATABASE,  1, G_SCORE_SKIP);
   } else {
      DEBUG_YJOBS   yLOG_info    ("a_database", a_database);
      rc = yjobs_ends_score (G_SCORE_DATABASE,  0, G_SCORE_FAIL);
      rc = yjobs_ends_score (G_SCORE_DATABASE,  1, G_SCORE_FAIL);
      /*---(check file)-------------------------*/
      rc = yjobs_central_data (a_hdir, a_database, x_fix);
      DEBUG_YJOBS   yLOG_value   ("database"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "database does not exist or is not properly secured");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      /*---(check contents)---------------------*/
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      --rce;  if (rc < 0) {
         yjobs_ends_failure (a_mode, "central database could not be read");
         DEBUG_YJOBS   yLOG_note    ("FATAL, central database could not be read");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc > rc_final)  rc_final = rc;
      rc = yjobs_ends_score (G_SCORE_DATABASE,  1, 'Ô');
      /*---(wrap)-------------------------------*/
      rc = x_callback (YJOBS_PURGE, "");
      DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
      rc = yjobs_ends_score (G_SCORE_DATABASE,  0, 'p');
   }
   /*---(score end)----------------------*/
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, 'a');
   if (x_fix == 'y')  {
      if (rc_final == RC_REPAIR)  rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'F');
      else                        rc = yjobs_ends_score (G_SCORE_SECURE  ,  1, 'f');
   }
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
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
   char        x_cuse      =  '-';
   char        x_cgood     =  '-';
   char        x_duse      =  '-';
   char        x_dgood     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_share_prepare ("yjobs__maint_prepare", 'm', a_runas, a_mode, a_oneline, a_file, f_callback, x_cdir, x_hdir, x_world, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(config directory)---------------*/
   rc = yjobs_maint_dir       (a_runas, a_mode, "configuration", x_cdir, &x_cuse , &x_cgood);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
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
   /*---(central directory)--------------*/
   rc = yjobs_maint_dir       (a_runas, a_mode, "central data" , x_hdir, &x_duse , &x_dgood);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
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
   rc = yjobs_share_readdb   ("yjobs__maint_readdb", 'm', a_mode, x_hdir, x_db, f_callback);
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

char yjobs_maint             (void) { return yjobs_maint_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


