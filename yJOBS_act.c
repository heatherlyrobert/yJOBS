/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


static char (*s_assimilate) (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);
/* test */


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
   /*> yENV_score_clear ();                                                           <*/
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
   /*> rc = yjobs_ends_prepare (a_runas, a_mode, a_oneline, a_file, f_callback, x_cdir, NULL, NULL, x_world, x_db, NULL, NULL, NULL, x_full);   <*/
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
      /*> yjobs_ends_score_OLD (G_SCORE_SECURE,  0, G_SCORE_FAIL);                    <*/
      g_acts_score  [G_SCORE_SECURE + 0] = G_SCORE_FAIL;
      /*> rc = yjobs_dir_review (a_runas, a_mode, a_oneline, '-');                    <*/
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "central security audit failed");
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
            yjobs_ends_failure (a_mode, "", "central database did not load properly");
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
            yjobs_ends_failure (a_mode, "", "all central files did not load properly");
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
         yjobs_ends_failure (a_mode, "", "database could not produce statistics");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_DATABASE + 2] = '#';
   }
   /*---(list)---------------------------*/
   --rce;  if (strchr ("=", a_mode) != NULL)  {
      if (strcmp  (x_world, "") != 0) {
         g_acts_score  [G_SCORE_WORLD   + 2] = G_SCORE_FAIL;
         /*> rc = yjobs_world_list (a_runas, a_mode);                                 <*/
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "", "world list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD   + 2] = '=';
      } else if (strstr  (x_cdir, "/spool/") != NULL) {
         /* run list of central files */
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         DEBUG_YJOBS   yLOG_value   ("list"      , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "", "central list did not run");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL + 5] = '=';
      } else {
         g_acts_score  [G_SCORE_CENTRAL + 5] = G_SCORE_FAIL;
         yjobs_ends_failure (a_mode, "", "program neither file-based or spool based");
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
         /*> rc = yjobs_central_old  (a_runas, a_mode, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);   <*/
         DEBUG_YJOBS   yLOG_value   ("central"   , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "", "central file not proper and/or secure");
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
            yjobs_ends_failure (a_mode, "", "central contents not acceptable");
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
            yjobs_ends_failure (a_mode, "", "central contents not acceptable");
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
         yjobs_ends_failure (a_mode, "", "central report could not complete");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_DATABASE + 3] = 'ó';
   }
   /*---(world audit)--------------------*/
   --rce;  if (strchr ("aèA", a_mode) != NULL) {
      if (strcmp (x_world, "") != 0) {
         g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_FAIL;
         /*> rc = yjobs_world_audit (a_runas, a_mode);                                <*/
         DEBUG_YJOBS   yLOG_value   ("world"     , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "", "world file content audit failed");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_WORLD + 0] = 'w';
      }
   }
   /*---(fix)----------------------------*/
   --rce;  if (strchr ("füF", a_mode) != NULL) {
      g_acts_score  [G_SCORE_SECURE + 1] = G_SCORE_FAIL;
      /*> rc = yjobs_dir_review (a_runas, a_mode, a_oneline, 'y');                    <*/
      DEBUG_YJOBS   yLOG_value   ("security"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "central security fix failed");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_acts_score  [G_SCORE_SECURE + 1] = 'f';
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_ends_success (a_mode);
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
      yURG_msg (':', "%s", a_oneline);
      yURG_msg (':', "  option --vcheck, check details of centrally installed job/khronos file");
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

/*> char                                                                                                                           <* 
 *> yjobs_outgoing_full     (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)   <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    char        rc          =    0;                                                                                             <* 
 *>    char        x_cdir      [LEN_DESC]  = "";                                                                                   <* 
 *>    char        x_world     [LEN_LABEL] = "";                                                                                   <* 
 *>    char        x_db        [LEN_LABEL] = "";                                                                                   <* 
 *>    char        x_full      [LEN_PATH]  = "";                                                                                   <* 
 *>    char       *p           = NULL;                                                                                             <* 
 *>    char      (*x_callback)   (cchar a_req, cchar *a_full);                                                                     <* 
 *>    char        x_old       [LEN_PATH]  = "";                                                                                   <* 
 *>    char        x_cmd       [LEN_RECD]  = "";                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);                                                                                   <* 
 *>    /+---(default)------------------------+/                                                                                    <* 
 *>    ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);                                                                            <* 
 *>    /+---(defense)------------------------+/                                                                                    <* 
 *>    DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);                                                                          <* 
 *>    DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);                                                                        <* 
 *>    --rce;  if (a_oneline == NULL) {                                                                                            <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);                                                                       <* 
 *>    --rce;  if (f_callback == NULL) {                                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    x_callback = f_callback;                                                                                                    <* 
 *>    /+---(show header)--------------------+/                                                                                    <* 
 *>    rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, x_world, x_db, NULL, x_full);                     <* 
 *>    DEBUG_YJOBS   yLOG_value   ("location"  , rc);                                                                              <* 
 *>    if (rc < 0) {                                                                                                               <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(load database)----------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {                                                                         <* 
 *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
 *>          DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");                                                <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;                                                                  <* 
 *>          rc = x_callback (YJOBS_READ, "");                                                                                     <* 
 *>          DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "", "central database did not load properly");                                             <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = 'Ô';                                                                           <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(remove database contents)-----------+/                                                                                <* 
 *>    --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                                                                            <* 
 *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_FAIL;                                                                  <* 
 *>          rc = x_callback (YJOBS_CLEAR, x_full);                                                                                <* 
 *>          DEBUG_YJOBS   yLOG_value   ("clear"     , rc);                                                                        <* 
 *>          --rce;  if (rc < 0) {                                                                                                 <* 
 *>             yjobs_ends_failure (a_mode, "", "contents could not be cleared");                                                      <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 4] = '×';                                                                           <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(verify file)------------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {                                                                         <* 
 *>       if (strcmp (a_file, "") != 0) {                                                                                          <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_FAIL;                                                                  <* 
 *>          rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);                                            <* 
 *>          DEBUG_YJOBS   yLOG_value   ("central"   , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "", "central file not proper and/or secure");                                              <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 1] = 'c';                                                                           <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(remove file)------------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                                                                            <* 
 *>       if (strcmp (x_db, "") == 0) {                                                                                            <* 
 *>          if (strstr (x_cdir, "/spool/") != NULL) {                                                                             <* 
 *>             g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_FAIL;                                                               <* 
 *>             snprintf (x_old, LEN_PATH, "%s%s", x_cdir, a_file);                                                                <* 
 *>             snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);                                                        <* 
 *>             DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);                                                                  <* 
 *>             rc = system   (x_cmd);                                                                                             <* 
 *>             DEBUG_YJOBS   yLOG_value   ("system"    , rc);                                                                     <* 
 *>             --rce;  if (rc < 0) {                                                                                              <* 
 *>                yjobs_ends_failure (a_mode, "", "contents could not be cleared");                                                   <* 
 *>                DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
 *>                return rce;                                                                                                     <* 
 *>             }                                                                                                                  <* 
 *>             g_acts_score  [G_SCORE_CENTRAL  + 6] = 'x';                                                                        <* 
 *>          } else {                                                                                                              <* 
 *>             g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;                                                               <* 
 *>          }                                                                                                                     <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(extract from database)--------------+/                                                                                <* 
 *>    --rce;  if (strchr ("eìE", a_mode) != NULL) {                                                                               <* 
 *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
 *>          g_acts_score  [G_SCORE_BACKEND  + 0] = G_SCORE_FAIL;                                                                  <* 
 *>          rc = x_callback (YJOBS_EXTRACT, x_full);                                                                              <* 
 *>          DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "", "could not extract from database");                                                    <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_BACKEND  + 0] = 'e';                                                                           <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(extract file)-----------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("eìE", a_mode) != NULL) {                                                                               <* 
 *>       if (strcmp (x_db, "") == 0) {                                                                                            <* 
 *>          g_acts_score  [G_SCORE_BACKEND  + 0] = G_SCORE_FAIL;                                                                  <* 
 *>          /+ copy file down +/                                                                                                  <* 
 *>          DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "", "could not copy from central");                                                        <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_BACKEND  + 0] = 'E';                                                                           <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(write database)---------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                                                                            <* 
 *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_FAIL;                                                                  <* 
 *>          DEBUG_YJOBS   yLOG_note    ("option requires database saved after");                                                  <* 
 *>          rc = x_callback (YJOBS_WRITE, "");                                                                                    <* 
 *>          DEBUG_YJOBS   yLOG_value   ("write db"  , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "", "central database could not save properly");                                           <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 4] = 'Õ';                                                                           <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(withdraw)---------------------------+/                                                                                <* 
 *>    --rce;  if (strchr ("qþQrøR", a_mode) != NULL && strcmp (x_world, "") != 0) {                                               <* 
 *>       rc = yjobs_world_withdraw (a_runas, a_file);                                                                             <* 
 *>       DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);                                                                           <* 
 *>       if (rc < 0) {                                                                                                            <* 
 *>          yjobs_ends_failure (a_mode, "", "can not withdraw from world file");                                                      <* 
 *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
 *>          return rce;                                                                                                           <* 
 *>       }                                                                                                                        <* 
 *>       g_fullacts [30] = 'w';                                                                                                   <* 
 *>    }                                                                                                                           <* 
 *>    /+---(show footer)--------------------+/                                                                                    <* 
 *>    if (rc > 0)  yURG_err (' ', "");                                                                                            <* 
 *>    rc = yjobs_ends_success (a_mode);                                                                                            <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                                  <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/

/*> char yjobs_outgoing          (void) { return yjobs_outgoing_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }   <*/

/*> char                                                                                                                                           <* 
 *> yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar *a_name)                                                <* 
 *> {                                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                    <* 
 *>    char        rce         =  -10;                                                                                                             <* 
 *>    int         rc          =    0;                                                                                                             <* 
 *>    char        x_dir       [LEN_PATH]  = "";                                                                                                   <* 
 *>    char        x_old       [LEN_RECD]  = "";                                                                                                   <* 
 *>    char        x_cmd       [LEN_RECD]  = "";                                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                                                                                  <* 
 *>    DEBUG_YJOBS  yLOG_point   ("a_runas"   , a_runas);                                                                                          <* 
 *>    /+---(defense)------------------------+/                                                                                                    <* 
 *>    DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);                                                                                        <* 
 *>    --rce;  if (a_oneline    == NULL) {                                                                                                         <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                              <* 
 *>    }                                                                                                                                           <* 
 *>    /+---(remove header)------------------+/                                                                                                    <* 
 *>    DEBUG_YJOBS  yLOG_point   ("a_act"     , a_act);                                                                                            <* 
 *>    --rce;  IF_REMOVE {                                                                                                                         <* 
 *>       yURG_msg (':', "%s", a_oneline);                                                                                                         <* 
 *>       yURG_msg (':', "  option --vremove, remove installed job/khronos file if found");                                                        <* 
 *>       yURG_msg (' ', "");                                                                                                                      <* 
 *>    } else {                                                                                                                                    <* 
 *>       DEBUG_YJOBS   yLOG_note    ("action requested is not a remove type, trouble");                                                           <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                              <* 
 *>    }                                                                                                                                           <* 
 *>    /+---(verify contents)--------------------+/                                                                                                <* 
 *>    rc = yjobs_central_old (a_runas, a_act, a_name, NULL, NULL, NULL, NULL);                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_value   ("central"   , rc);                                                                                              <* 
 *>    --rce;  if (rc < 0) {                                                                                                                       <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg_live ();                                                                                           <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg (':', "FAILED, installed job/khronos file not found/proper, run --vremove to identify reasons");   <* 
 *>       if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not found/proper, the reasons are shown above");         <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg_mute ();                                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                              <* 
 *>    }                                                                                                                                           <* 
 *>    /+---(remove physical)--------------------+/                                                                                                <* 
 *>    yjobs_central_dirs (a_runas, a_act, a_name, "n/a", x_dir, NULL);                                                                            <* 
 *>    snprintf (x_old, LEN_RECD, "%s%s", x_dir, a_name);                                                                                          <* 
 *>    snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);                                                                                 <* 
 *>    DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);                                                                                           <* 
 *>    rc = system   (x_cmd);                                                                                                                      <* 
 *>    DEBUG_YJOBS   yLOG_value   ("system"    , rc);                                                                                              <* 
 *>    DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));                                                                                   <* 
 *>    --rce;  if (rc < 0 || WIFEXITED (rc) < 0) {                                                                                                 <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg_live ();                                                                                           <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg (':', "FAILED, installed job/khronos file not deleted, run --vremove for reasons");                <* 
 *>       if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, the reasons are shown above");              <* 
 *>       if (a_act == ACT_CREMOVE )   yURG_msg_mute ();                                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                              <* 
 *>    }                                                                                                                                           <* 
 *>    if (a_act == ACT_CREMOVE )   yURG_msg_live ();                                                                                              <* 
 *>    yURG_msg (':', "SUCCESS, installed job/khronos file uninstalled.  restart or --reload to retire");                                          <* 
 *>    if (a_act == ACT_CREMOVE )   yURG_msg_mute ();                                                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                                                  <* 
 *>    return 0;                                                                                                                                   <* 
 *> }                                                                                                                                              <*/



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
   /*> rc = yjobs_central_dirs  (a_runas, a_act, NULL, "n/a", r_dir, NULL);           <*/
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
      /*> rc = yjobs_dir_review (a_runas, a_act, a_oneline, '-');                     <*/
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

/*> char         /+--> review and act on global crontabs -------------------------+/             <* 
 *> yjobs_running__pull     (cchar a_runas, cchar a_mode, cchar *a_cdir, void *f_callback)       <* 
 *> {                                                                                            <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                  <* 
 *>    char        rce         =  -10;                                                           <* 
 *>    int         rc          =    0;                                                           <* 
 *>    DIR        *x_dir       = NULL;                                                           <* 
 *>    tDIRENT    *x_file      = NULL;                                                           <* 
 *>    int         x_total     =    0;                                                           <* 
 *>    int         x_pass      =    0;                                                           <* 
 *>    char      (*x_callback)   (cchar a_req, cchar *a_full);                                   <* 
 *>    char        x_cwd       [LEN_PATH];                                                       <* 
 *>    char        x_name      [LEN_DESC];                                                       <* 
 *>    char        x_full      [LEN_PATH];                                                       <* 
 *>    char       *p           = NULL;                                                           <* 
 *>    /+---(header)-------------------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                                <* 
 *>    /+---(defense)------------------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);                                       <* 
 *>    --rce;  switch (a_runas) {                                                                <* 
 *>    case  IAM_KHRONOS   : case  IAM_UKHRONOS  :                                               <* 
 *>    case  IAM_HERACLES  : case  IAM_UHERACLES :                                               <* 
 *>       break;                                                                                 <* 
 *>    default :                                                                                 <* 
 *>       DEBUG_YJOBS   yLOG_note    ("runas does not need/allow central file review");          <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return rce;                                                                            <* 
 *>       break;                                                                                 <* 
 *>    }                                                                                         <* 
 *>    DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);                                     <* 
 *>    --rce;  if (f_callback == NULL) {                                                         <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return rce;                                                                            <* 
 *>    }                                                                                         <* 
 *>    x_callback = f_callback;                                                                  <* 
 *>    /+---(get current working dir)--------+/                                                  <* 
 *>    p = getcwd (x_cwd, LEN_PATH);                                                             <* 
 *>    DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);                                             <* 
 *>    if (p == NULL) {                                                                          <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return rce;                                                                            <* 
 *>    }                                                                                         <* 
 *>    DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);                                         <* 
 *>    rc = chdir (a_cdir);                                                                      <* 
 *>    DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);                                            <* 
 *>    /+---(open directory)-----------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);                                        <* 
 *>    x_dir = opendir (a_cdir);                                                                 <* 
 *>    DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);                                         <* 
 *>    --rce;  if (x_dir == NULL) {                                                              <* 
 *>       /+> RUN_USER     printf ("fatal, can not open khronos central directory\n");    <+/    <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return rce;                                                                            <* 
 *>    }                                                                                         <* 
 *>    /+---(walk files)---------------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_note    ("walk through directory files");                              <* 
 *>    while ((x_file = readdir (x_dir)) != NULL) {                                              <* 
 *>       /+---(filter)-----------------------------+/                                           <* 
 *>       if (strcmp (x_file->d_name, "."    ) == 0)  continue;                                  <* 
 *>       if (strcmp (x_file->d_name, ".."   ) == 0)  continue;                                  <* 
 *>       /+---(prepare)----------------------------+/                                           <* 
 *>       ++x_total;                                                                             <* 
 *>       ystrlcpy (x_name, x_file->d_name, LEN_DESC);                                           <* 
 *>       sprintf (x_full, "%s%s", a_cdir, x_file->d_name);                                      <* 
 *>       /+---(verify file)------------------------+/                                           <* 
 *>       /+> rc = yjobs_central_old  (a_runas, a_mode, x_name, NULL, NULL, NULL, NULL);   <+/   <* 
 *>       DEBUG_YJOBS   yLOG_value   ("central"   , rc);                                         <* 
 *>       if (rc < 0) {                                                                          <* 
 *>          yjobs_ends_failure (a_mode, "", "local file not proper and/or secure");                 <* 
 *>          continue;                                                                           <* 
 *>       }                                                                                      <* 
 *>       /+---(verify contents)--------------------+/                                           <* 
 *>       rc = x_callback (YJOBS_PULL, x_full);                                                  <* 
 *>       DEBUG_YJOBS   yLOG_value   ("pull"      , rc);                                         <* 
 *>       --rce;  if (rc < 0) {                                                                  <* 
 *>          yjobs_ends_failure (a_mode, "", "local contents not acceptable");                       <* 
 *>          continue;                                                                           <* 
 *>       }                                                                                      <* 
 *>       /+---(clear old contents)-----------------+/                                           <* 
 *>       /+> if (strchr (g_audit, a_mode) != NULL || strchr ("hH", a_runas) == NULL) {   <*     <* 
 *>        *>    rc = x_callback (YJOBS_PURGE, NULL);                                     <*     <* 
 *>        *>    DEBUG_YJOBS   yLOG_value   ("purge"     , rc);                           <*     <* 
 *>        *>    --rce;  if (rc < 0) {                                                    <*     <* 
 *>        *>       yjobs_ends_failure (a_mode, "", "could not clear read data");              <*    <* 
 *>        *>       continue;                                                             <*     <* 
 *>        *>    }                                                                        <*     <* 
 *>        *> }                                                                           <+/    <* 
 *>       /+---(next)------------------------+/                                                  <* 
 *>       ++x_pass;                                                                              <* 
 *>       DEBUG_YJOBS   yLOG_complex ("counts"    , "%d total, %d pass", x_total, x_pass);       <* 
 *>       /+---(done)------------------------+/                                                  <* 
 *>    }                                                                                         <* 
 *>    /+---(summary)------------------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_value   ("found"     , x_total);                                       <* 
 *>    DEBUG_YJOBS   yLOG_value   ("passed"    , x_pass);                                        <* 
 *>    /+---(close)--------------------------+/                                                  <* 
 *>    rc = closedir (x_dir);                                                                    <* 
 *>    DEBUG_YJOBS   yLOG_point   ("close"     , rc);                                            <* 
 *>    --rce;  if (rc < 0) {                                                                     <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return rce;                                                                            <* 
 *>    }                                                                                         <* 
 *>    rc = chdir (x_cwd);                                                                       <* 
 *>    DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);                                            <* 
 *>    /+---(complete)-----------------------+/                                                  <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                <* 
 *>    return rc;                                                                                <* 
 *> }                                                                                            <*/

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



