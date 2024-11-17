/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



static char       *X_AUDIT     = "a�A";



char yjobs__maint_prepare    (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, char r_cdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_full [LEN_PATH]) { return yjobs__share_prepare ('m', a_runas, a_mode, a_oneline, a_file, f_callback, r_cdir, r_world, r_db, r_full); }

char
yjobs__maint_secure     (char a_runas, char a_mode, char a_oneline [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (X_AUDIT, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (X_AUDIT);
      DEBUG_YJOBS   yLOG_note    ("security review not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, G_SCORE_FAIL);
   /*---(review)-------------------------*/
   rc = yjobs_act_security (a_runas, a_mode, a_oneline, '-');
   DEBUG_YJOBS   yLOG_value   ("security"  , rc);
   if (rc < 0) {
      yjobs_ends_failure (a_mode, "central security audit failed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_SECURE  ,  0, 'a');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}


char
yjobs_maint_full        (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
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
   char       *X_ALLDATA   = "#m�M";
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
   rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, x_world, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS  yLOG_info    ("x_db"      , x_db);
   DEBUG_YJOBS  yLOG_info    ("x_full"    , x_full);
   /*---(security check)-----------------*/
   --rce;  if (strchr ("a�A", a_mode) != NULL) {
      yjobs_ends_score (G_SCORE_SECURE,  0, G_SCORE_FAIL);
      g_acts_score  [G_SCORE_SECURE + 0] = G_SCORE_FAIL;
      rc = yjobs_act_security (a_runas, a_mode, a_oneline, '-');
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central security audit failed");
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
            yjobs_ends_failure (a_mode, "central database did not load properly");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_DATABASE + 1] = '�';
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
   --rce;  if (strchr ("#", a_mode) != NULL) {
      g_acts_score  [G_SCORE_DATABASE + 2] = G_SCORE_FAIL;
      DEBUG_YJOBS   yLOG_note    ("request to produce database/central file statistics");
      rc = x_callback (YJOBS_STATS   , "");
      DEBUG_YJOBS   yLOG_value   ("stats"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "database could not produce statistics");
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
   --rce;  if (strchr ("c�Ca�Ao�O", a_mode) != NULL) {
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
   --rce;  if (strchr ("c�Co�O", a_mode) != NULL) {
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
         g_acts_score  [G_SCORE_CENTRAL + 2] = '�';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_SKIP;
      }
   }
   /*---(verify config contents)---------*/
   --rce;  if (strchr ("a�A", a_mode) != NULL) {
      if (strncmp (x_cdir, "/etc/", 5) == 0) {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_PULL, x_full);
         DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
         --rce;  if (rc < 0) {
            yjobs_ends_failure (a_mode, "central contents not acceptable");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 2] = '�';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 2] = G_SCORE_SKIP;
      }
   }
   /*---(central report)-----------------*/
   --rce;  if (strchr ("m�M", a_mode) != NULL) {
      g_acts_score  [G_SCORE_DATABASE + 3] = G_SCORE_FAIL;
      rc = x_callback (YJOBS_REPORT, a_file);
      DEBUG_YJOBS   yLOG_value   ("report"    , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central report could not complete");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_DATABASE + 3] = '�';
   }
   /*---(world audit)--------------------*/
   --rce;  if (strchr ("a�A", a_mode) != NULL) {
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
   --rce;  if (strchr ("f�F", a_mode) != NULL) {
      g_acts_score  [G_SCORE_SECURE + 1] = G_SCORE_FAIL;
      rc = yjobs_act_security (a_runas, a_mode, a_oneline, 'y');
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central security fix failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_SECURE + 1] = 'f';
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_ends_footer (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_maint             (void) { return yjobs_maint_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


