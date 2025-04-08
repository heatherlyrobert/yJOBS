/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"

char
yjobs_run__pull_all     (char a_runas, char a_mode, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(full all files)------------------------*/
   rc = yjobs_dir_review (a_runas, a_mode, f_callback, YENV_NONE, YENV_NONE);
   DEBUG_YJOBS   yLOG_value   ("files"     , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_run_full          (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   char        rc_warn     =    0;
   int         x_ruid      =   -1;
   char        x_ruser     [LEN_USER]  = "";
   char        x_cdir      [LEN_DESC]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_cwd       [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   char        x_cuse      =  '-';
   char        x_cgood     =  '-';
   char        x_duse      =  '-';
   char        x_dgood     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_ends_prepare (a_runas, a_mode, a_oneline, a_file, f_callback, &x_ruid, x_ruser, x_cdir, NULL, x_hdir, x_world, x_db, x_cwd, x_dir, x_file, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(config directory)---------------*/
   rc = yjobs_dir_secure      (a_runas, a_mode, "configuration", x_cdir, &x_cuse , &x_cgood);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(central directory)--------------*/
   rc = yjobs_dir_secure      (a_runas, a_mode, "central data" , x_hdir, &x_duse , &x_dgood);
   DEBUG_YJOBS   yLOG_value   ("config dir", rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_db_read        (a_runas, a_mode, x_hdir, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_run__pull_all  (a_runas, a_mode, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
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
   case RC_POSITIVE :  rc = yjobs_ends_success  (a_mode);                    rc = RC_POSITIVE;  break;
   case RC_OVERRIDE :  rc = yjobs_ends_approved (a_mode);                    rc = RC_OVERRIDE;  break;
   case RC_REPAIR   :  rc = yjobs_ends_repaired (a_mode);                    rc = RC_REPAIR;    break;
   case RC_WARNING  :  rc = yjobs_ends_warning  (a_mode);                    rc = RC_WARNING;   break;
   case RC_FATAL    :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = RC_FATAL;     break;
   default          :  rc = yjobs_ends_failure  (a_mode, "", "serious errors");  rc = rce;          break;
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

char yjobs_run   (void) { return yjobs_run_full     (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

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
   /*> if (strchr (g_running, a_mode) != NULL)  yENV_score_clear ();                  <* 
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
   /*> rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, NULL, NULL, NULL, NULL, NULL, x_full);   <* 
    *> DEBUG_YJOBS   yLOG_value   ("header"    , rc);                                                                     <* 
    *> if (rc < 0) {                                                                                                      <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
    *>    return rce;                                                                                                     <* 
    *> }                                                                                                                  <*/
   /*---(check for full database)------------*/
   /*> rc = yjobs_who_location (a_runas, NULL, x_hdir, NULL, NULL, x_db);             <* 
    *> DEBUG_YJOBS   yLOG_value   ("location"  , rc);                                 <* 
    *> --rce;  if (rc <  0) {                                                         <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*> --rce;  if (strcmp (x_db, "") != 0)   {                                             <* 
    *>    DEBUG_YJOBS   yLOG_note    ("option requires central database loaded before");   <* 
    *>    rc = x_callback (YJOBS_READ, "");                                                <* 
    *>    DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                   <* 
    *>    if (rc < 0) {                                                                    <* 
    *>       yjobs_ends_failure (a_mode, "central database did not load properly");        <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                               <* 
    *>       return rce;                                                                   <* 
    *>    }                                                                                <* 
    *>    g_fullacts  [20] = 'R';                                                          <* 
    *> }                                                                                   <*/
   /*---(load all files)---------------------*/
   /*> --rce;  if (strchr ("kK", a_runas) != NULL) {                                  <* 
    *>    DEBUG_YJOBS   yLOG_note    ("option requires all files loaded before");     <* 
    *>    rc = yjobs_running__pull (a_runas, a_mode, x_cdir, x_callback);             <* 
    *>    DEBUG_YJOBS   yLOG_value   ("read files", rc);                              <* 
    *>    g_fullacts  [20] = 'R';                                                     <* 
    *> }                                                                              <*/
   /*---(verify file)------------------------*/
   /*> --rce;  if (strchr ("eEhH", a_runas) != NULL) {                                                      <* 
    *>    /+> rc = yjobs_central_old  (a_runas, a_mode, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);   <+/   <* 
    *>    DEBUG_YJOBS   yLOG_value   ("central"   , rc);                                                    <* 
    *>    if (rc < 0) {                                                                                     <* 
    *>       yjobs_ends_failure (a_mode, "central file not proper and/or secure");                          <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                <* 
    *>       return rce;                                                                                    <* 
    *>    }                                                                                                 <* 
    *>    g_fullacts  [ 8] = 'c';                                                                           <* 
    *> }                                                                                                    <*/
   /*---(load specific file)-----------------*/
   /*> --rce;  if (strchr ("eEhH", a_runas) != NULL) {                                <* 
    *>    rc = x_callback (YJOBS_PULL, x_full);                                       <* 
    *>    DEBUG_YJOBS   yLOG_value   ("pull"      , rc);                              <* 
    *>    --rce;  if (rc < 0) {                                                       <* 
    *>       yjobs_ends_failure (a_mode, "local contents not acceptable");            <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(show footer)--------------------*/
   /*> if (strchr (g_running, a_mode) != NULL) {                                      <* 
    *>    if (rc > 0)  yURG_err (' ', "");                                            <* 
    *>    rc = yjobs_ends_success (a_mode);                                           <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_running           (void) { return yjobs_running_full     (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

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
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
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
      /*> rc = yjobs_central_old  (a_runas, a_mode, x_name, NULL, NULL, NULL, NULL);   <*/
      DEBUG_YJOBS   yLOG_value   ("central"   , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "local file not proper and/or secure");
         continue;
      }
      /*---(verify contents)--------------------*/
      rc = x_callback (YJOBS_PULL, x_full);
      DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
      --rce;  if (rc < 0) {
         yjobs_ends_failure (a_mode, "", "local contents not acceptable");
         continue;
      }
      /*---(clear old contents)-----------------*/
      /*> if (strchr (g_audit, a_mode) != NULL || strchr ("hH", a_runas) == NULL) {   <* 
       *>    rc = x_callback (YJOBS_PURGE, NULL);                                     <* 
       *>    DEBUG_YJOBS   yLOG_value   ("purge"     , rc);                           <* 
       *>    --rce;  if (rc < 0) {                                                    <* 
       *>       yjobs_ends_failure (a_mode, "could not clear read data");              <* 
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

