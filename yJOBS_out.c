/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                     sub-function support                     ----===*/
/*====================------------------------------------====================*/
static void      o___SUBS_______________o (void) {;};

/*> char                                                                                                                                                                                                                        <* 
 *> yjobs__out_prepare      (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, char r_cdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_full [LEN_PATH])   <* 
 *> {                                                                                                                                                                                                                           <* 
 *>    return yjobs_share_prepare (__FUNCTION__, 'o', a_runas, a_mode, a_oneline, a_file, f_callback, r_cdir, r_world, r_db, r_full);                                                                                           <* 
 *> }                                                                                                                                                                                                                           <*/

/*> char                                                                              <* 
 *> yjobs__out_readdb       (char a_mode, char a_db [LEN_LABEL], void *f_callback)    <* 
 *> {                                                                                 <* 
 *>    return yjobs_share_readdb  (__FUNCTION__, 'o', a_mode, a_db, f_callback);      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> yjobs__out_writedb      (char a_mode, char a_db [LEN_LABEL], void *f_callback)    <* 
 *> {                                                                                 <* 
 *>    return yjobs_share_writedb (__FUNCTION__, 'o', a_mode, a_db, f_callback);      <* 
 *> }                                                                                 <*/

char
yjobs__out_remove       (char a_mode, char a_db [LEN_LABEL], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_rem, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_rdb);
      DEBUG_YJOBS   yLOG_note    ("data content removal not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(no-database)--------------------*/
   if (a_db == NULL || strcmp (a_db, "") == 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_note    ("host program does not use central database");
      yjobs_ends_score (G_SCORE_CENTRAL ,  4, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  4, G_SCORE_FAIL);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   x_callback = f_callback;
   rc = x_callback (YJOBS_CLEAR, "");
   DEBUG_YJOBS   yLOG_value   ("clear"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "contents could not be cleared");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_CENTRAL ,  4, '×');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__out_withdraw     (char a_runas, char a_mode, char a_file [LEN_PATH], char a_world [LEN_LABEL], void *f_testcall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_testcall)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_wit, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_wit);
      DEBUG_YJOBS   yLOG_note    ("withdraw not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(no-database)--------------------*/
   if (a_world == NULL || strcmp (a_world, "") == 0) {
      if (strchr ("béB", a_mode) != NULL) {
         DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
         DEBUG_YJOBS   yLOG_note    ("host program requested register specifcally, but does not use world file");
         yjobs_ends_score (G_SCORE_WORLD   ,  0, G_SCORE_FAIL);
         yjobs_ends_failure (a_mode, "requested register, but host does not use world file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_snote   ("host program does not use world file");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   /*---(call)---------------------------*/
   DEBUG_YJOBS   yLOG_point   ("f_testcall", f_testcall);
   if (f_testcall != NULL) {  /* special testing outlet */
      x_testcall = f_testcall;
      rc = x_testcall (ACT_WITHDRAW, "");
   }
   else {
      rc = yjobs_world_withdraw (a_runas, a_file);
   }
   /*---(handle trouble)-----------------*/
   DEBUG_YJOBS   yLOG_value   ("withdraw"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "can not withdraw in world file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
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
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_share_prepare ("yjobs__out_prepare", 'o', a_runas, a_mode, a_oneline, a_file, f_callback, NULL, x_world, x_db, x_full);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read database)------------------*/
   rc = yjobs_share_readdb  ("yjobs__out_readdb", 'o', a_mode, x_db, f_callback);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove data)--------------------*/
   rc = yjobs__out_remove   (a_mode, x_db, f_callback);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }


   /*---(write database)-----------------*/
   rc = yjobs_share_writedb  ("yjobs__out_writedb", 'o', a_mode, x_db, f_callback);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(withdraw from world)------------*/
   rc = yjobs__out_withdraw (a_runas, a_mode, x_full, x_world, NULL);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(footer)-------------------------*/
   rc = yjobs_ends_success (a_mode);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



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
   --rce;  if (strchr ("xõXrøR", a_mode) != NULL) {
      if (strcmp (x_db, "") != 0) {
         g_acts_score  [G_SCORE_CENTRAL  + 4] = G_SCORE_FAIL;
         rc = x_callback (YJOBS_CLEAR, x_full);
         DEBUG_YJOBS   yLOG_value   ("clear"     , rc);
         --rce;  if (rc < 0) {
            yjobs_ends_failure (a_mode, "contents could not be cleared");
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
               yjobs_ends_failure (a_mode, "contents could not be cleared");
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
      yURG_msg (':', "%s", a_oneline);
      yURG_msg (':', "  option --vremove, remove installed job/khronos file if found");
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
      if (a_act == ACT_CREMOVE )   yURG_msg (':', "FAILED, installed job/khronos file not found/proper, run --vremove to identify reasons");
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
      if (a_act == ACT_CREMOVE )   yURG_msg (':', "FAILED, installed job/khronos file not deleted, run --vremove for reasons");
      if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, the reasons are shown above");
      if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_act == ACT_CREMOVE )   yURG_msg_live ();
   yURG_msg (':', "SUCCESS, installed job/khronos file uninstalled.  restart or --reload to retire");
   if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}


