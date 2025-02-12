/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*
 *   action      lvl
 *   ----------  ---  --db-in-- -secure-- --load--- --report- -intake-- --db-out- -register 
 *   verify      v�V      �         y         y         �         �         �         �       secure and load/audit
 *   local       l�L      �         y         y         y         �         �         �       secure and load/audit, and report
 *   register    b�B      �         y         y         �         �         �         y       secure and load/audit, and register
 *   update      u�U      y         y         y         �         y         y         �       secure and load/audit, and update
 *   install     i�I      y         y         y         �         y         y         y       secure and load/audit, and register and update
 *
 */

/*> static char      (*s_callback)   (char a_req, char a_full [LEN_PATH]) = NULL;     <*/

static char       *X_REPORT    = "l�L";
static char       *X_INSTALL   = "u�Ui�I";
static char       *X_REGISTER  = "b�Bi�I";



/*====================------------------------------------====================*/
/*===----                         sub-routines                         ----===*/
/*====================------------------------------------====================*/
static void      o___SUBS__________o (void) {;};

/*> char                                                                               <* 
 *> yjobs__in_readdb        (char a_mode, char a_db [LEN_LABEL], void *f_callback)     <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                        <* 
 *>    char        rce         =  -10;                                                 <* 
 *>    int         rc          =    0;                                                 <* 
 *>    char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);                 <* 
 *>    /+---(quick-out)----------------------+/                                        <* 
 *>    if (a_mode == 0 || strchr (X_INSTALL, a_mode) == NULL) {                        <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                   <* 
 *>       DEBUG_YJOBS   yLOG_sint    (a_mode);                                         <* 
 *>       DEBUG_YJOBS   yLOG_snote   (X_INSTALL);                                      <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("database read not required");                   <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                   <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(no-database)--------------------+/                                        <* 
 *>    if (a_db == NULL || strcmp (a_db, "") == 0) {                                   <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                   <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("host program does not use central database");   <* 
 *>       yjobs_ends_score (G_SCORE_DATABASE,  1, G_SCORE_SKIP);                       <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                   <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);                              <* 
 *>    DEBUG_YJOBS   yLOG_note    ("mode requires database loaded before");            <* 
 *>    rc = yjobs_ends_score (G_SCORE_DATABASE,  1, G_SCORE_FAIL);                     <* 
 *>    /+---(check call-back)----------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);                          <* 
 *>    --rce;  if (f_callback == NULL) {                                               <* 
 *>       yjobs_ends_failure (a_mode, "host program callback function is NULL");       <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                  <* 
 *>    }                                                                               <* 
 *>    /+---(call)---------------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);                                  <* 
 *>    x_callback = f_callback;                                                        <* 
 *>    rc = x_callback (YJOBS_READ, "");                                               <* 
 *>    DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                  <* 
 *>    --rce;  if (rc < 0) {                                                           <* 
 *>       yjobs_ends_failure (a_mode, "central database did not load properly");       <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                  <* 
 *>    }                                                                               <* 
 *>    /+---(score)--------------------------+/                                        <* 
 *>    rc = yjobs_ends_score (G_SCORE_DATABASE,  1, '�');                              <* 
 *>    DEBUG_YJOBS   yLOG_value   ("score"     , rc);                                  <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 1;                                                                       <* 
 *> }                                                                                  <*/

char
yjobs__in_dir           (char a_runas, char a_mode, char a_file [LEN_PATH], char r_fuser [LEN_USER], char r_fdir [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   int         l           =    0;
   char       *p           = NULL;
   char        x_user      [LEN_LABEL] = "";
   int         x_uid       =    0;
   char        t           [LEN_PATH]  = "";
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_complex ("a_args"    , "%c %c", a_runas, a_mode);
   yURG_msg ('>', "verify local directory...");
   /*---(default)------------------------*/
   if (r_fuser  != NULL)  strcpy (r_fuser , "");
   if (r_fdir   != NULL)  strcpy (r_fdir  , "");
   if (r_full   != NULL)  strcpy (r_full  , "");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yURG_err ('f', "passed a null or empty directory name string");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "directory name �%s� is not null or empty", a_file);
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   --rce;  if (strcmp (a_file, "dir") == 0) {
      yURG_msg ('-', "requested �dir� for current directory (preferred)");
   } else  if (strcmp (a_file, "/")   == 0) {
      yURG_msg ('-', "requested �/� for current directory (preferred)");
   } else  if (a_file [0] == '/') {
      yURG_msg ('-', "requested specific directory (not allowed, ignored)");
   } else {
      yURG_err ('f', "did not request directory with �dir�, �/�, or absolute path");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get security data)--------------*/
   rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, NULL, x_user, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "currently running as �%s� (%d)", x_user, x_uid);
   ystrlcpy (myJOBS.m_user, x_user, LEN_USER);
   myJOBS.m_uid = x_uid;
   /*---(directories)--------------------*/
   if (strchr (g_unit, a_runas) == NULL)  {
      yURG_msg ('-', "running in normal production execution environment");
      DEBUG_YJOBS  yLOG_note    ("normal execution");
      strcpy (myJOBS.m_root, "/root");
      strcpy (myJOBS.m_home, "/home/");
   } else {
      yURG_msg ('-', "running in unit testing execution environment");
      DEBUG_YJOBS  yLOG_snote   ("unittest execution");
      strcpy (myJOBS.m_root, "/tmp/root");
      strcpy (myJOBS.m_home, "/tmp/home/");
   }
   DEBUG_YJOBS  yLOG_info    ("m_root"    , myJOBS.m_root);
   DEBUG_YJOBS  yLOG_info    ("m_home"    , myJOBS.m_home);
   yURG_msg ('-', "using �%s� and �%s� as allowed directory prefixes", myJOBS.m_root, myJOBS.m_home);
   /*---(check directory)----------------*/
   p = getcwd (x_fdir, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      yURG_err ('f', "can not obtain current working directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (strcmp (x_fdir, "/") !=  0)  ystrlcat (x_fdir, "/", LEN_PATH);
   DEBUG_YJOBS   yLOG_info    ("x_fdir"    , x_fdir);
   yURG_msg ('-', "current working directory is �%s�", x_fdir);
   /*---(filter locations)---------------*/
   --rce;  if (strncmp (x_fdir, myJOBS.m_root, strlen (myJOBS.m_root)) == 0) {
      yURG_msg ('-', "directory is under root, so valid");
      strcpy (x_fuser, "root");
   } else  if (strncmp (x_fdir, myJOBS.m_home, strlen (myJOBS.m_home)) == 0) {
      yURG_msg ('-', "directory is under home, so valid");
      ystrlcpy (t, x_fdir, LEN_PATH);
      rc = lstat (x_fdir, &s);
      DEBUG_YJOBS  yLOG_value   ("stat"      , rc);
      if (rc < 0) {
         yURG_err ('f', "can not access the current directory using lstat");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YJOBS  yLOG_value   ("value"     , s.st_uid);
      x_uid = s.st_uid;
      rc = yENV_user_data ('i', x_fuser, &x_uid, NULL, NULL, NULL);
      yURG_msg ('-', "ownership is �%s� (%d)", x_fuser, x_uid);
      DEBUG_YJOBS  yLOG_value   ("user_data" , rc);
      if (rc < 0) {
         yURG_err ('f', "can not access user data using yENV_user_data");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      yURG_err ('f', "only allowed under root or home directories");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(summary)------------------------*/
   yURG_msg ('-', "success, directory is allowed");
   /*---(save back)----------------------*/
   if (r_fuser  != NULL)  strcpy (r_fuser , x_fuser);
   if (r_fdir   != NULL)  strcpy (r_fdir  , x_fdir);
   if (r_full   != NULL)  strcpy (r_full  , x_fdir);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__in_verify        (char a_runas, char a_mode, char a_file [LEN_PATH], char r_fuser [LEN_USER], char r_fdir [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS   yLOG_complex ("a_args"    , "%c %c", a_runas, a_mode);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_LOCAL,  0, G_SCORE_FAIL);
   if (r_fuser  != NULL)  strcpy (r_fuser , "");
   if (r_fdir   != NULL)  strcpy (r_fdir  , "");
   if (r_full   != NULL)  strcpy (r_full  , "");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yjobs_ends_failure (a_mode, "local file name is null/empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   l = strlen (a_file);
   DEBUG_YJOBS   yLOG_value   ("l"         , l);
   /*---(directory)----------------------*/
   --rce;  if (strcmp (a_file, "dir") == 0 || a_file [0] == '/') {
      DEBUG_YJOBS   yLOG_note    ("directory given");
      /*---(filter)----------------------*/
      DEBUG_YJOBS   yLOG_info    ("IAM_DIRS"  , IAM_DIRS);
      if (strchr (IAM_DIRS, a_runas) == NULL) {
         yjobs_ends_failure (a_mode, "requester (not polymnia/metis) can not request directory");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(verify)----------------------*/
      rc = yjobs__in_dir    (a_runas, a_mode, a_file, r_fuser, r_fdir, r_full);
      DEBUG_YJOBS   yLOG_value   ("local"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "local file not proper and/or secure");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(score)-----------------------*/
      rc = yjobs_ends_score (G_SCORE_LOCAL,  0, 'd');
      DEBUG_YJOBS   yLOG_value   ("score"     , rc);
      /*---(done)------------------------*/
   }
   /*---(file)---------------------------*/
   else {
      DEBUG_YJOBS   yLOG_note    ("file given");
      /*---(filter)----------------------*/
      DEBUG_YJOBS   yLOG_info    ("IAM_FILES" , IAM_FILES);
      if (strchr (IAM_FILES, a_runas) == NULL) {
         yjobs_ends_failure (a_mode, "requester (polymnia) can only request a directory, not a file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(verify)----------------------*/
      rc = yjobs_local_old  (a_runas, a_file, r_fuser, NULL, NULL, r_fdir);
      DEBUG_YJOBS   yLOG_value   ("local"     , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "local file not proper and/or secure");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(saveback)--------------------*/
      if (r_full != NULL) {
         if (rc == 1)  strlcpy (r_full, a_file, LEN_PATH);
         else          sprintf (r_full, "%s%s", r_fdir, a_file);
      }
      /*---(score)-----------------------*/
      rc = yjobs_ends_score (G_SCORE_LOCAL,  0, 'l');
      DEBUG_YJOBS   yLOG_value   ("score"     , rc);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__in_pull          (char a_mode, void *f_callback, char a_full [LEN_PATH])
{
   /*---(design notes)-------------------*/
   /*   all local files are always read, even if only to verify
   */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_flag     =    1;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_LOCAL,  1, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   x_callback = f_callback;
   rc = rc_flag = x_callback (YJOBS_PULL, a_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "local file unreadable or contents unacceptable");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_value   ("rc_flag"   , rc_flag);
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_LOCAL,  1, '�');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_flag;
}

char
yjobs__in_report        (char a_mode, void *f_callback, char a_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (X_REPORT, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (X_REPORT);
      DEBUG_YJOBS   yLOG_snote   ("local report not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   rc = yjobs_ends_score (G_SCORE_LOCAL,  2, G_SCORE_FAIL);
   DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);
   /*---(check call-back)----------------*/
   DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   x_callback = f_callback;
   rc = x_callback (YJOBS_LOCALRPT, a_full);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "local report could not complete");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(score)--------------------------*/
   rc = yjobs_ends_score (G_SCORE_LOCAL,  2, '�');
   DEBUG_YJOBS   yLOG_value   ("score"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs__in_intake        (char a_runas, char a_mode, char a_file [LEN_PATH], char a_db [LEN_LABEL], char a_fuser [LEN_USER])
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
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (X_INSTALL, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (X_INSTALL);
      DEBUG_YJOBS   yLOG_snote   ("local to central copy not required");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(uses database)------------------*/
   if (a_db != NULL && strcmp (a_db, "") != 0) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_snote   ("host program uses central database, not files");
      yjobs_ends_score (G_SCORE_CENTRAL ,  0, G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "install file in central directory...");
   g_acts_score  [G_SCORE_CENTRAL + 0] = G_SCORE_FAIL;
   /*---(get central info)-------------------*/
   rc = yjobs_central_dirs (a_runas, a_mode, a_file, a_fuser, x_fdir, x_fnew);
   DEBUG_YJOBS   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_fdir"    , x_fdir);
   DEBUG_YJOBS   yLOG_info    ("x_fnew"    , x_fnew);
   /*---(make full new file name)------------*/
   sprintf (x_full, "%s%s", x_fdir, x_fnew);
   yURG_msg ('-', "central file name �%s�", x_full);
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(copy file)--------------------------*/
   snprintf (x_cmd, LEN_RECD, "cp -f %s %s > /dev/null  2>&1", a_file, x_full);
   DEBUG_YJOBS   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YJOBS   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not copy to �%s�", x_fdir);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      yURG_err ('f', "could not copy to �%s�", x_fdir);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "copied file to �%s�", x_fdir);
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
   g_acts_score  [G_SCORE_CENTRAL + 0] = 'm';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                               <* 
 *> yjobs__in_writedb       (char a_mode, char a_db [LEN_LABEL], void *f_callback)     <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                        <* 
 *>    char        rce         =  -10;                                                 <* 
 *>    int         rc          =    0;                                                 <* 
 *>    char      (*x_callback)   (char a_req, char a_full [LEN_PATH]);                 <* 
 *>    /+---(quick-out)----------------------+/                                        <* 
 *>    if (a_mode == 0 || strchr (X_INSTALL, a_mode) == NULL) {                        <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                   <* 
 *>       DEBUG_YJOBS   yLOG_sint    (a_mode);                                         <* 
 *>       DEBUG_YJOBS   yLOG_snote   (X_INSTALL);                                      <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("database write not required");                  <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                   <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(no-database)--------------------+/                                        <* 
 *>    if (a_db == NULL || strcmp (a_db, "") == 0) {                                   <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                   <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("host program does not use central database");   <* 
 *>       yjobs_ends_score (G_SCORE_DATABASE,  4, G_SCORE_SKIP);                       <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                   <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);                              <* 
 *>    DEBUG_YJOBS   yLOG_note    ("mode requires database written after");            <* 
 *>    rc = yjobs_ends_score (G_SCORE_DATABASE,  4, G_SCORE_FAIL);                     <* 
 *>    /+---(check call-back)----------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_point   ("callback"  , f_callback);                          <* 
 *>    --rce;  if (f_callback == NULL) {                                               <* 
 *>       yjobs_ends_failure (a_mode, "host program callback function is NULL");       <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                  <* 
 *>    }                                                                               <* 
 *>    /+---(call)---------------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_value   ("pre-score" , rc);                                  <* 
 *>    x_callback = f_callback;                                                        <* 
 *>    rc = x_callback (YJOBS_WRITE, "");                                              <* 
 *>    DEBUG_YJOBS   yLOG_value   ("write db"  , rc);                                  <* 
 *>    --rce;  if (rc < 0) {                                                           <* 
 *>       yjobs_ends_failure (a_mode, "central database did not save properly");       <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                  <* 
 *>    }                                                                               <* 
 *>    /+---(score)--------------------------+/                                        <* 
 *>    rc = yjobs_ends_score (G_SCORE_DATABASE,  4, '�');                              <* 
 *>    DEBUG_YJOBS   yLOG_value   ("score"     , rc);                                  <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 1;                                                                       <* 
 *> }                                                                                  <*/

char
yjobs__in_register      (char a_runas, char a_mode, char a_file [LEN_PATH], char a_world [LEN_LABEL], void *f_testcall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char      (*x_testcall)   (char a_req, char a_full [LEN_PATH]);
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_reg, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_reg);
      DEBUG_YJOBS   yLOG_snote   ("register not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(no-database)--------------------*/
   if (a_world == NULL || strcmp (a_world, "") == 0) {
      if (strchr ("b�B", a_mode) != NULL) {
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
      rc = x_testcall (ACT_REGISTER, "");
   }
   else {
      rc = yjobs_world_register (a_runas, a_file);
   }
   /*---(handle trouble)-----------------*/
   DEBUG_YJOBS   yLOG_value   ("register"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "can not register in world file");
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
yjobs_in_full           (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   char        rc_warn     =    0;
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_fuser     [LEN_USER]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yjobs_share_prepare ("yjobs__in_prepare", 'i', a_runas, a_mode, a_oneline, a_file, f_callback, NULL, NULL, x_world, x_db, x_full);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(read database)------------------*/
   rc = yjobs_share_readdb   ("yjobs__in_readdb", 'i', a_mode, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("readdb"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(verify local)-------------------*/
   rc = yjobs__in_verify   (a_runas, a_mode, a_file, x_fuser, x_fdir, x_full);
   DEBUG_YJOBS   yLOG_value   ("verify"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(pull local)---------------------*/
   rc = yjobs__in_pull     (a_mode, f_callback, x_full);
   DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(write report)-------------------*/
   rc = yjobs__in_report   (a_mode, f_callback, x_full);
   DEBUG_YJOBS   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(local to central)---------------*/
   rc = yjobs__in_intake   (a_runas, a_mode, a_file, x_db, x_fuser);
   DEBUG_YJOBS   yLOG_value   ("intake"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull local)---------------------*/
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   rc = yjobs_share_writedb  ("yjobs__in_writedb", 'i', a_mode, x_db, f_callback);
   DEBUG_YJOBS   yLOG_value   ("writedb"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if      (rc > rc_final)  rc_final = rc;
   else if (rc < 0)         rc_final = RC_FATAL;
   DEBUG_YJOBS   yLOG_value   ("rc_final"  , rc_final);
   /*---(register)-----------------------*/
   rc = yjobs__in_register (a_runas, a_mode, a_file, x_world, NULL);
   DEBUG_YJOBS   yLOG_value   ("register"  , rc);
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
   case RC_FATAL    :  rc = yjobs_ends_failure  (a_mode, "serious errors");  rc = RC_FATAL;     break;
   default          :  rc = yjobs_ends_failure  (a_mode, "serious errors");  rc = rce;          break;
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

char yjobs_in                (void) { return yjobs_in_full   (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

/*> char                                                                                                                           <* 
 *> yjobs_incomming_full    (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)   <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    char        rc          =    0;                                                                                             <* 
 *>    char        x_world     [LEN_LABEL] = "";                                                                                   <* 
 *>    char        x_db        [LEN_LABEL] = "";                                                                                   <* 
 *>    char        x_full      [LEN_PATH]  = "";                                                                                   <* 
 *>    char        x_len       =    0;                                                                                             <* 
 *>    char       *p           = NULL;                                                                                             <* 
 *>    /+> char      (*s_callback)   (cchar a_req, cchar *a_full);                        <+/                                      <* 
 *>    char        x_fuser     [LEN_USER]  = "";                                                                                   <* 
 *>    int         x_fuid      =   -1;                                                                                             <* 
 *>    char        x_fdesc     [LEN_DESC]  = "";                                                                                   <* 
 *>    char        x_fdir      [LEN_PATH]  = "";                                                                                   <* 
 *>    char        x_fnew      [LEN_DESC]  = "";                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);                                                                                   <* 
 *>    DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);                                                                          <* 
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
 *>    s_callback = f_callback;                                                                                                    <* 
 *>    /+---(show header)--------------------+/                                                                                    <* 
 *>    rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, NULL, NULL, x_world, x_db, NULL, x_full);                       <* 
 *>    DEBUG_YJOBS   yLOG_value   ("header"    , rc);                                                                              <* 
 *>    if (rc < 0) {                                                                                                               <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);                                                                         <* 
 *>    DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);                                                                            <* 
 *>    /+---(database)-----------------------+/                                                                                    <* 
 *>    --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_note    ("requested database load");                                                                  <* 
 *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
 *>          DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");                                                <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_FAIL;                                                                  <* 
 *>          rc = s_callback (YJOBS_READ, "");                                                                                     <* 
 *>          DEBUG_YJOBS   yLOG_value   ("read db"   , rc);                                                                        <* 
 *>          if (rc < 0) {                                                                                                         <* 
 *>             yjobs_ends_failure (a_mode, "central database did not load properly");                                             <* 
 *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
 *>             return rce;                                                                                                        <* 
 *>          }                                                                                                                     <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = '�';                                                                           <* 
 *>       } else {                                                                                                                 <* 
 *>          g_acts_score  [G_SCORE_DATABASE + 1] = G_SCORE_SKIP;                                                                  <* 
 *>       }                                                                                                                        <* 
 *>    }                                                                                                                           <* 
 *>    /+---(security on file)---------------+/                                                                                    <* 
 *>    --rce;  if (a_file == NULL || a_file [0] == '\0') {                                                                         <* 
 *>       yjobs_ends_failure (a_mode, "local file name is null/empty");                                                            <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    x_len = strlen (a_file);                                                                                                    <* 
 *>    g_acts_score  [G_SCORE_LOCAL + 0] = G_SCORE_FAIL;                                                                           <* 
 *>    --rce;  if (a_file [x_len - 1] == '/') {                                                                                    <* 
*>       DEBUG_YJOBS   yLOG_note    ("directory given");                                                                          <* 
*>       if (strchr (IAM_DIRS, a_runas) == NULL) {                                                                                <* 
   *>          yjobs_ends_failure (a_mode, "requester (not polymnia/metis) can not request directory");                              <* 
      *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
      *>          return rce;                                                                                                           <* 
      *>       }                                                                                                                        <* 
      *>       g_acts_score  [G_SCORE_LOCAL + 0] = 'd';                                                                                 <* 
      *>    } else {                                                                                                                    <* 
         *>       DEBUG_YJOBS   yLOG_note    ("file given");                                                                               <* 
            *>       if (strchr (IAM_FILES, a_runas) == NULL) {                                                                               <* 
               *>          yjobs_ends_failure (a_mode, "polymnia can only request directory, not a file");                                       <* 
                  *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
                  *>          return rce;                                                                                                           <* 
                  *>       }                                                                                                                        <* 
                  *>       rc = yjobs_local_old  (a_runas, a_file, x_fuser, &x_fuid, x_fdesc, x_fdir);                                              <* 
                  *>       DEBUG_YJOBS   yLOG_value   ("local"     , rc);                                                                           <* 
                  *>       if (rc < 0) {                                                                                                            <* 
                     *>          yjobs_ends_failure (a_mode, "local file not proper and/or secure");                                                   <* 
                        *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
                        *>          return rce;                                                                                                           <* 
                        *>       }                                                                                                                        <* 
                        *>       if (rc == 1)  strlcpy (x_full, a_file, LEN_PATH);                                                                        <* 
                        *>       g_acts_score  [G_SCORE_LOCAL + 0] = 'l';                                                                                 <* 
                        *>    }                                                                                                                           <* 
                        *>    /+---(load/audit)---------------------+/                                                                                    <* 
                        *>    g_acts_score  [G_SCORE_LOCAL + 1] = G_SCORE_FAIL;                                                                           <* 
                        *>    rc = s_callback (YJOBS_PULL, x_full);                                                                                       <* 
                        *>    DEBUG_YJOBS   yLOG_value   ("pull"      , rc);                                                                              <* 
                        *>    --rce;  if (rc < 0) {                                                                                                       <* 
                           *>       yjobs_ends_failure (a_mode, "local contents not acceptable");                                                            <* 
                              *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
                              *>       return rce;                                                                                                              <* 
                              *>    }                                                                                                                           <* 
                              *>    g_acts_score  [G_SCORE_LOCAL + 1] = '�';                                                                                    <* 
                              *>    /+---(local report)-------------------+/                                                                                    <* 
                              *>    --rce;  if (strchr (X_REPORT, a_mode) != NULL) {                                                                            <* 
                                 *>       g_acts_score  [G_SCORE_LOCAL + 2] = G_SCORE_FAIL;                                                                        <* 
                                    *>       rc = s_callback (YJOBS_LOCALRPT, a_file);                                                                                <* 
                                    *>       DEBUG_YJOBS   yLOG_value   ("localrpt"  , rc);                                                                           <* 
                                    *>       if (rc < 0) {                                                                                                            <* 
                                       *>          yjobs_ends_failure (a_mode, "local report could not complete");                                                       <* 
                                          *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
                                          *>          return rce;                                                                                                           <* 
                                          *>       }                                                                                                                        <* 
                                          *>       g_acts_score  [G_SCORE_LOCAL + 2] = '�';                                                                                 <* 
                                          *>    }                                                                                                                           <* 
                                          *>    /+---(intake file)--------------------+/                                                                                    <* 
                                          *>    --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {                                                                           <* 
                                             *>       if (strcmp (x_db, "") == 0) {                                                                                            <* 
                                                *>          /+ score update is in world function +/                                                                               <* 
                                                   *>          rc = yjobs__in_intake (a_runas, a_mode, a_file, x_db, x_fuser);                                                       <* 
                                                   *>          DEBUG_YJOBS   yLOG_value   ("intake"    , rc);                                                                        <* 
                                                   *>          --rce; if (rc < 0) {                                                                                                  <* 
                                                      *>             yjobs_ends_failure (a_mode, "file could not be moved appopriately");                                               <* 
                                                         *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
                                                         *>             return rce;                                                                                                        <* 
                                                         *>          }                                                                                                                     <* 
                                                         *>       } else {                                                                                                                 <* 
                                                            *>          g_acts_score  [G_SCORE_CENTRAL + 0] = G_SCORE_SKIP;                                                                   <* 
                                                               *>       }                                                                                                                        <* 
                                                               *>    }                                                                                                                           <* 
                                                               *>    /+---(write database)-----------------+/                                                                                    <* 
                                                               *>    --rce;  if (strchr (X_INSTALL, a_mode) != NULL) {                                                                           <* 
                                                                  *>       if (strcmp (x_db, "") != 0) {                                                                                            <* 
                                                                     *>          DEBUG_YJOBS   yLOG_note    ("option requires database saved after");                                                  <* 
                                                                        *>          g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_FAIL;                                                                  <* 
                                                                        *>          rc = s_callback (YJOBS_WRITE, "");                                                                                    <* 
                                                                        *>          DEBUG_YJOBS   yLOG_value   ("write db"  , rc);                                                                        <* 
                                                                        *>          if (rc < 0) {                                                                                                         <* 
                                                                           *>             yjobs_ends_failure (a_mode, "central database could not save properly");                                           <* 
                                                                              *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
                                                                              *>             return rce;                                                                                                        <* 
                                                                              *>          }                                                                                                                     <* 
                                                                              *>          g_acts_score  [G_SCORE_DATABASE + 4] = '�';                                                                           <* 
                                                                              *>       } else {                                                                                                                 <* 
                                                                                 *>          g_acts_score  [G_SCORE_DATABASE + 4] = G_SCORE_SKIP;                                                                  <* 
                                                                                    *>       }                                                                                                                        <* 
                                                                                    *>    }                                                                                                                           <* 
                                                                                    *>    /+---(register)-----------------------+/                                                                                    <* 
                                                                                    *>    --rce;  if (strchr (X_REGISTER, a_mode) != NULL) {                                                                          <* 
                                                                                       *>       if (strcmp (x_world, "") != 0) {                                                                                         <* 
                                                                                          *>          /+ score update is in world function +/                                                                               <* 
                                                                                             *>          rc = yjobs_world_register (a_runas, a_file);                                                                          <* 
                                                                                             *>          DEBUG_YJOBS   yLOG_value   ("register"  , rc);                                                                        <* 
                                                                                             *>          if (rc < 0) {                                                                                                         <* 
                                                                                                *>             yjobs_ends_failure (a_mode, "can not register in world file");                                                     <* 
                                                                                                   *>             DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                    <* 
                                                                                                   *>             return rce;                                                                                                        <* 
                                                                                                   *>          }                                                                                                                     <* 
                                                                                                   *>       } else if (strchr ("b�B", a_mode) != NULL) {                                                                             <* 
                                                                                                      *>          g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_FAIL;                                                                     <* 
                                                                                                         *>          yjobs_ends_failure (a_mode, "requested register specifically, but no world file");                                    <* 
                                                                                                         *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
                                                                                                         *>          return rce;                                                                                                           <* 
                                                                                                         *>       } else {                                                                                                                 <* 
                                                                                                            *>          g_acts_score  [G_SCORE_WORLD + 0] = G_SCORE_SKIP;                                                                     <* 
                                                                                                               *>          g_acts_score  [G_SCORE_WORLD + 1] = G_SCORE_SKIP;                                                                     <* 
                                                                                                               *>          g_acts_score  [G_SCORE_WORLD + 3] = G_SCORE_SKIP;                                                                     <* 
                                                                                                               *>          g_acts_score  [G_SCORE_WORLD + 5] = G_SCORE_SKIP;                                                                     <* 
                                                                                                               *>       }                                                                                                                        <* 
                                                                                                               *>    }                                                                                                                           <* 
                                                                                                               *>    /+---(show footer)--------------------+/                                                                                    <* 
                                                                                                               *>    if (rc > 0)  yURG_err (' ', "");                                                                                            <* 
                                                                                                               *>    rc = yjobs_ends_success (a_mode);                                                                                            <* 
                                                                                                               *>    /+---(complete)-----------------------+/                                                                                    <* 
                                                                                                               *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                                  <* 
                                                                                                               *>    return 0;                                                                                                                   <* 
                                                                                                               *> }                                                                                                                              <*/




                                                                                                               /*====================------------------------------------====================*/
                                                                                                               /*===----                   unit testing support                       ----===*/
                                                                                                               /*====================------------------------------------====================*/
                                                                                                               static void      o___UNITTEST______o (void) {;};

