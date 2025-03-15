/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                     sub-function support                     ----===*/
/*====================------------------------------------====================*/
static void      o___SUBS_______________o (void) {;};

char
yjobs__out_clear        (char a_mode, char a_db [LEN_LABEL], char a_file [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_clr, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_clr);
      DEBUG_YJOBS   yLOG_snote   ("database content clearing not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "database clearing of single file or project...");
   /*---(no-database)--------------------*/
   if (a_db == NULL || strcmp (a_db, "") == 0) {
      DEBUG_YJOBS   yLOG_note    ("host program does not use central database");
      yURG_msg ('-', "skipping, host program does not use central database");
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  4, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   yURG_msg ('-', "host database å%sæ", a_db);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  4, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(file name)----------------------*/
   --rce;  if (a_file == NULL || strcmp (a_file, "") == 0) {
      yURG_err ('f', "host program callback function is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "portion to clear å%sæ", a_file);
   /*---(call)---------------------------*/
   rc = x_callback (YJOBS_CLEAR, a_file);
   DEBUG_YJOBS   yLOG_value   ("clear"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "contents could not be cleared");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc_final = rc;
   /*---(score)--------------------------*/
   if (rc_final == RC_POSITIVE) {
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  4, 'x');
      DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs__out_delete       (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_file [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_etc       =  '-';
   char        x_old       [LEN_RECD]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_clr, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_clr);
      DEBUG_YJOBS   yLOG_snote   ("file deletion not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "central data file deletion...");
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  6, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(set etc)-------------------------------*/
   if (a_cdir != NULL && strstr  (a_cdir, "/etc/") != NULL)    x_etc = 'y';
   DEBUG_YJOBS   yLOG_char    ("x_etc"     , x_etc);
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir       == NULL) {
      yURG_err ('f', "configuration directory is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   /*---(quick-out)----------------------*/
   --rce;  if (strcmp (a_cdir, "") == 0) {
      yURG_msg ('-', "skipping, no configuration directory specified for application");
      rc = yjobs_ends_score (G_SCORE_CENTRAL ,  6, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   yURG_msg ('-', "central directory å%sæ", a_cdir);
   /*---(quick-out)----------------------*/
   --rce;  if (x_etc == 'y') {
      yURG_err ('f', "skipping, single-file configuration can not be deleted, only replaced");
      yjobs_ends_failure (a_mode, "/etc program can not deleted conf file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check file)---------------------*/
   --rce;  if (a_file == NULL || strcmp (a_file, "") == 0) {
      yURG_err ('f', "configuration file to be deleted is NULL");
      yjobs_ends_failure (a_mode, "requested null/empty file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "configuration file å%sæ", a_file);
   /*---(validate file)----------------------*/
   rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   if (rc < 0) {
      yjobs_ends_failure (a_mode, "central file not proper and/or existant");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(delete physical)--------------------*/
   yURG_msg ('>', "central data file removal (part II)...");
   snprintf (x_old, LEN_RECD, "%s%s", a_cdir, a_file);
   yURG_msg ('-', "absolute file name å%sæ", x_old);
   DEBUG_YJOBS   yLOG_info    ("x_old"     , x_old);
   snprintf (x_cmd, LEN_RECD, "rm -f %s  > /dev/null  2>&1", x_old);
   DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));
   --rce;  if (rc < 0 || WIFEXITED (rc) < 0) {
      yURG_err ('f', "central file could not be deleted");
      yjobs_ends_failure (a_mode, "central file could not be deleted");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify)-----------------------------*/
   --rce;  if (yENV_exists (x_old) != '-') {
      yURG_err ('f', "central file still exists");
      yjobs_ends_failure (a_mode, "central file still exists");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "success, file deleted", x_old);
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  6, 'X');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs__out_withdraw     (char a_runas, char a_mode, char a_file [LEN_PATH], char a_world [LEN_LABEL], void *f_testcall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char      (*x_testcall)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_wit, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_wit);
      DEBUG_YJOBS   yLOG_snote   ("withdraw not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "withdraw from world file...");
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  1, G_SCORE_FAIL);
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  3, G_SCORE_FAIL);
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  4, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(defense)-------------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_world"   , a_world);
   --rce;  if (a_world      == NULL) {
      yURG_err ('f', "world file configuration is NULL (illegal setup)");
      yjobs_ends_failure (a_mode, "host program configuration is illegal");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_world"   , a_world);
   /*---(quick-out)----------------------*/
   --rce;  if (strcmp (a_world, "") == 0) {
      yURG_msg ('-', "skipping, no world file configuration specified for application");
      rc = yjobs_ends_score (G_SCORE_WORLD   ,  1, G_SCORE_SKIP);
      rc = yjobs_ends_score (G_SCORE_WORLD   ,  3, G_SCORE_SKIP);
      rc = yjobs_ends_score (G_SCORE_WORLD   ,  4, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   yURG_msg ('-', "central world file å%sæ", a_world);
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_point   ("f_testcall", f_testcall);
   if (f_testcall != NULL) {  /* special testing outlet */
      x_testcall = f_testcall;
      rc = x_testcall (ACT_WITHDRAW, "");
   }
   else {
      /*> rc = yjobs_world_withdraw (a_runas, a_mode, a_file);                        <*/
   }
   rc_final = rc;
   /*---(handle trouble)-----------------*/
   DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "can not withdraw from world file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update score)-------------------*/
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  1, 'Ô');
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  3, 'u');
   rc = yjobs_ends_score (G_SCORE_WORLD   ,  4, 'Õ');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER___________o (void) {;};

char
yjobs_out_full          (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
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
   rc = yjobs_share_prepare ("yjobs__out_prepare", 'o', a_runas, a_mode, a_oneline, a_file, f_callback, x_cdir, x_hdir, x_world, x_db, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_share_readdb   ("yjobs__out_readdb", 'o', a_mode, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(clear data)---------------------*/
   rc = yjobs__out_clear    (a_mode, x_db, a_file, f_callback);
   DEBUG_YJOBS   yLOG_value   ("clear"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(write database)-----------------*/
   rc = yjobs_share_writedb  ("yjobs__out_writedb", 'o', a_mode, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("writedb"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(delete file)--------------------*/
   rc = yjobs__out_delete   (a_runas, a_mode, x_cdir, a_file);
   DEBUG_YJOBS   yLOG_value   ("delete"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(withdraw from world)------------*/
   rc = yjobs__out_withdraw (a_runas, a_mode, x_full, x_world, NULL);
   DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);
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

char yjobs_out               (void) { return yjobs_out_full (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


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
   /*> /+---(default)------------------------+/                                       <* 
    *> ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);                               <* 
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
    *> DEBUG_YJOBS   yLOG_value   ("location"  , rc);                                                            <* 
    *> if (rc < 0) {                                                                                             <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
    *>    return rce;                                                                                            <* 
    *> }                                                                                                         <*/
   /*---(load database)----------------------*/
   /*> --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {                               <* 
    *>    if (strcmp (x_db, "") != 0) {                                                  <* 
    *>       DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");      <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;                        <* 
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
   /*---(remove database contents)-----------*/
   /*> --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                               <* 
    *>    if (strcmp (x_db, "") != 0) {                                               <* 
    *>       g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_FAIL;                     <* 
    *>       rc = x_callback (YJOBS_CLEAR, x_full);                                   <* 
    *>       DEBUG_YJOBS   yLOG_value   ("clear"     , rc);                           <* 
    *>       --rce;  if (rc < 0) {                                                    <* 
    *>          yjobs_ends_failure (a_mode, "contents could not be cleared");         <* 
    *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                       <* 
    *>          return rce;                                                           <* 
    *>       }                                                                        <* 
    *>       g_acts_score  [G_SCORE_CENTRAL  + 4] = '×';                              <* 
    *>    } else {                                                                    <* 
    *>       g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_SKIP;                     <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(verify file)------------------------*/
   --rce;  if (strchr ("xõXrøReìE", a_mode) != NULL) {
      if (strcmp (a_file, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_FAIL;
         rc = yjobs_central_old  (a_runas, a_mode, a_file, NULL, NULL, NULL, NULL);
         DEBUG_YJOBS   yLOG_value   ("central"   , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "central file not proper and/or secure");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_CENTRAL  + 1] = 'c';
      } else {
         g_acts_score  [G_SCORE_CENTRAL  + 1] = G_SCORE_SKIP;
      }
   }
   /*---(remove file)------------------------*/
   /*> --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                               <* 
    *>    if (strcmp (x_db, "") == 0) {                                               <* 
    *>       if (strstr (x_cdir, "/spool/") != NULL) {                                <* 
    *>          g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_FAIL;                  <* 
    *>          snprintf (x_old, LEN_PATH, "%s%s", x_cdir, a_file);                   <* 
    *>          snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);           <* 
    *>          DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);                     <* 
    *>          rc = system   (x_cmd);                                                <* 
    *>          DEBUG_YJOBS   yLOG_value   ("system"    , rc);                        <* 
    *>          --rce;  if (rc < 0) {                                                 <* 
    *>             yjobs_ends_failure (a_mode, "contents could not be cleared");      <* 
    *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                    <* 
    *>             return rce;                                                        <* 
    *>          }                                                                     <* 
    *>          g_acts_score  [G_SCORE_CENTRAL  + 6] = 'x';                           <* 
    *>       } else {                                                                 <* 
    *>          g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;                  <* 
    *>       }                                                                        <* 
    *>    } else {                                                                    <* 
    *>       g_acts_score  [G_SCORE_CENTRAL  + 6] = G_SCORE_SKIP;                     <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(extract from database)--------------*/
   --rce;  if (strchr ("eìE", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         g_acts_score  [G_SCORE_BACKEND  + 0] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_EXTRACT, x_full);
         DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "could not extract from database");
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
            yjobs_ends_failure (a_mode, "could not copy from central");
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         g_acts_score  [G_SCORE_BACKEND  + 0] = 'E';
      }
   }
   /*---(write database)---------------------*/
   /*> --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {                                    <* 
    *>    if (strcmp (x_db, "") != 0) {                                                    <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_FAIL;                          <* 
    *>       DEBUG_YJOBS   yLOG_note    ("option requires database saved after");          <* 
    *>       rc = x_callback (YJOBS_WRITE, "");                                            <* 
    *>       DEBUG_YJOBS   yLOG_value   ("write db"  , rc);                                <* 
    *>       if (rc < 0) {                                                                 <* 
    *>          yjobs_ends_failure (a_mode, "central database could not save properly");   <* 
    *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>          return rce;                                                                <* 
    *>       }                                                                             <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 4] = 'Õ';                                   <* 
    *>    } else {                                                                         <* 
    *>       g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_SKIP;                          <* 
    *>    }                                                                                <* 
    *> }                                                                                   <*/
   /*---(withdraw)---------------------------*/
   /*> --rce;  if (strchr ("qþQrøR", a_mode) != NULL && strcmp (x_world, "") != 0) {   <* 
    *>    rc = yjobs_world_withdraw (a_runas, a_file);                                 <* 
    *>    DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);                               <* 
    *>    if (rc < 0) {                                                                <* 
    *>       yjobs_ends_failure (a_mode, "can not withdraw from world file");          <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                           <* 
    *>       return rce;                                                               <* 
    *>    }                                                                            <* 
    *>    g_fullacts [30] = 'w';                                                       <* 
    *> }                                                                               <*/
   /*---(show footer)--------------------*/
   /*> if (rc > 0)  yURG_err (' ', "");                                               <* 
    *> rc = yjobs_ends_success (a_mode);                                               <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_outgoing          (void) { return yjobs_outgoing_full    (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }


