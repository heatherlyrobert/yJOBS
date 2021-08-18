/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                          shared support                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;};

char
yjobs__naming           (uchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   int         c           =    0;
   uchar      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || strlen (a_name) <= 0) {
      yURG_err ('f', "file name can not be null or empty (blatant error)");
      DEBUG_INPT   yLOG_note    ("file name can not be null or empty");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
   yURG_msg ('-', "name å%sæ is not empty/null", a_name);
   /*---(path)---------------------------*/
   p = strchr (a_name, '/');
   DEBUG_INPT   yLOG_point   ("/"         , p);
   --rce;  if (p != NULL) {
      yURG_err ('f', "file name can not include relative/absolute path (security risk)");
      DEBUG_INPT   yLOG_note    ("file name can not include relative/absolute path (security risk)");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_note    ("cronfile name is path local (pathless)");
   yURG_msg ('-', "file name is pathless/local");
   /*---(name quality)-------------------*/
   l = strlen (a_name);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_name [i]) == NULL) {
         yURG_err ('f', "file name has an illegal character (%c) at position %d (security risk)", a_name [i], i);
         DEBUG_INPT   yLOG_complex ("bad char"  , "can not include %c at %d", a_name [i], i);
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_INPT   yLOG_note    ("all name characters are acceptable");
   yURG_msg ('-', "all the file name characters are legal [A-Za-z0-9_.]");
   /*---(hidden file)--------------------*/
   DEBUG_INPT   yLOG_char    ("first char", a_name [0]);
   --rce;  if (a_name [0] == '.') {
      yURG_err ('f', "file can not be a hidden file, lead period (security risk)");
      DEBUG_INPT   yLOG_note    ("file can not be a hidden file");
      DEBUG_INPT  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "file is not a hidden file, no lead period");
   /*---(exactly one period)-------------*/
   c = strldcnt (a_name, '.', LEN_RECD);
   DEBUG_INPT   yLOG_value   ("periods"   , c);
   --rce;  if (c < 1) {
      yURG_err ('f', "file name does not have at least one separator/period (standard)");
      DEBUG_INPT   yLOG_note    ("name must have exactly one separator/period");
      DEBUG_INPT  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "file has at least one separator/period");
   /*---(description length)-------------*/
   p = strchr (a_name, '.');
   c = p - a_name;
   --rce;  if (c < 3) {
      yURG_err ('f', "file prefix can not be shorter than 3 characters (illegal)");
      DEBUG_INPT   yLOG_note    ("prefix too short (< 3 chars)");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "name prefix is adequate length, >= 3 characters");
   c = l - c - 1;
   --rce;  if (c < 3) {
      yURG_err ('f', "file description can not be shorter than 3 characters (lazy)");
      DEBUG_INPT   yLOG_note    ("description too short (< 3 chars)");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "name description is adequate length, >= 3 characters");
   /*---(complete)-----------------------*/
   DEBUG_INPT  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__location         (cchar a_runas, cchar a_loc, cchar *a_home, cchar *a_root, uchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cwd       [LEN_PATH]  = "";
   char       *p           = NULL;
   char        t           [LEN_HUND]  = "";
   char        x_user      [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   --rce;  if (a_home  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_home"    , a_home);
   --rce;  if (a_root  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_root"    , a_root);
   --rce;  if (a_name  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
   DEBUG_INPT  yLOG_point   ("a_muser"   , a_muser);
   --rce;  if (a_muser == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_muser"   , a_muser);
   DEBUG_INPT   yLOG_value   ("a_muid"    , a_muid);
   DEBUG_INPT   yLOG_point   ("r_fuser"   , r_fuser);
   --rce;  if (r_fuser == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (r_fuser, "");
   DEBUG_INPT   yLOG_point   ("r_fuid"    , r_fuid);
   --rce;  if (r_fuid  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *r_fuid  = -1;
   --rce;  if (r_dir   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (r_dir, "");
   /*---(check directory)----------------*/
   p = getcwd (r_dir, LEN_PATH);
   DEBUG_INPT   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      yURG_err ('f', "can not obtain current working directory");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_loc == YJOBS_LOCAL)  strlcat (r_dir, "/", LEN_PATH);
   DEBUG_INPT   yLOG_info    ("r_dir"     , r_dir);
   yURG_msg ('-', "current working directory is å%sæ", r_dir);
   /*---(check normal install)-----------*/
   --rce;  if (a_loc == YJOBS_LOCAL && a_muid != 0) {
      sprintf (t, "%s%s", a_home, a_muser);
      DEBUG_INPT   yLOG_info    ("expect"    , t);
      /*> yURG_msg ('-', "compare to å%sæ", t);                                       <*/
      l = strlen (t);
      if (strncmp (r_dir, t, l) != 0) {
         yURG_err ('f', "user not in or below their own home directory (security risk)");
         DEBUG_INPT   yLOG_note    ("user not in or below their own home directory");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcpy (r_fuser, a_muser, LEN_USER);
      yURG_msg ('-', "normal user file in or below their own home directory");
   }
   /*---(check root install)-------------*/
   --rce;  if (a_loc == YJOBS_LOCAL && a_muid == 0) {
      DEBUG_INPT   yLOG_note    ("root user verifying");
      sprintf (t, "%s", a_root);
      l = strlen (t);
      DEBUG_INPT   yLOG_complex ("cdir"      , "%2d å%sæ vs å%sæ", l, t, r_dir);
      if (strncmp (r_dir, t, l) == 0) {
         DEBUG_INPT   yLOG_note    ("root in root user home directory tree");
         strlcpy (r_fuser, "root", LEN_USER);
         yURG_msg ('-', "root user file in or below root home directory");
      } else {
         sprintf (t, "%s", a_home);
         l = strlen (t);
         if (strncmp (r_dir, t, l) == 0) {
            DEBUG_INPT   yLOG_note    ("root in another user home directory tree");
            strlcpy  (x_user, r_dir + l, LEN_PATH);
            strldchg (x_user, '/', '\0', LEN_PATH);
            strlcpy (r_fuser, x_user, LEN_USER);
            yURG_msg ('-', "root user file in or below %s users home directory", x_user);
         } else {
            yURG_err ('f', "root, but not in or below any valid user home directory (security risk)");
            DEBUG_INPT   yLOG_note    ("root, but not in or below a valid user home directory");
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   }
   /*---(check central audit)------------*/
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      /*---(verify user)--------------------*/
      switch (a_runas) {
      case IAM_EOS       : case IAM_UEOS      :
      case IAM_ASTRAIOS  : case IAM_UASTRAIOS :
      case IAM_HYPNOS    : case IAM_UHYPNOS   :
         strcpy (x_user , "root");
         strcpy (r_fuser, "root");
         break;
      case IAM_HERACLES  : case IAM_UHERACLES :
      case IAM_KHRONOS   : case IAM_UKHRONOS  :
         strlcpy  (x_user, a_name, LEN_USER);
         strldchg (x_user, '.', '\0', LEN_USER);
         strlcpy  (r_fuser, x_user, LEN_USER);
         break;
      }
      yURG_msg ('-', "central file prefix is å%sæ", r_fuser);
   }
   DEBUG_INPT   yLOG_info    ("r_fuser"    , r_fuser);
   /*---(check for registered)-----------*/
   rc = yEXEC_userdata (r_fuser, r_fuid, NULL, NULL, NULL);
   DEBUG_INPT   yLOG_value   ("userdata"  , rc);
   if (rc < 0) {
      if (a_loc == YJOBS_LOCAL) {
         yURG_err ('f', "user directory not associated with a registered user (security risk)");
      } else {
         yURG_err ('f', "user name prefix å%sæ not registered on system (security risk)", r_fuser);
      }
      DEBUG_INPT   yLOG_note    ("user is not registered in the system");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "file user is registered with system, %s, uid %d", r_fuser, *r_fuid);
   /*---(name prefix)--------------------*/
   --rce;  if (a_loc == YJOBS_LOCAL) {
      if (strchr ("Kk", a_runas) != NULL)  strcpy (t, "khronos.");
      else                                 strcpy (t, "job.");
      if (strncmp (a_name, t, strlen (t)) != 0) {
         yURG_err ('f', "local file name must be prefixed with å%sæ (standard)", t);
         DEBUG_INPT   yLOG_note    ("name does not begin with khronos/job");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name is prefixed appropriately with å%sæ", t);
   }
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      if (a_muid != 0) {
         if (strcmp (a_muser, r_fuser) != 0) {
            yURG_err ('f', "run-time user å%sæ can not review this file (security risk)", a_muser);
            DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         yURG_msg ('-', "run-time user has the appropriate access");
      } else {
         yURG_msg ('-', "run-time is root, so all access is allowed");
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__stats            (cchar a_loc, cchar *a_dir, uchar *a_name, cchar *a_muser, int a_muid, uchar *a_user, int a_uid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_PATH]  = "";
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(get stats)----------------------*/
   DEBUG_YEXEC  yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YEXEC  yLOG_info    ("a_name"    , a_name);
   sprintf (x_full, "%s%s", a_dir, a_name);
   DEBUG_YEXEC  yLOG_info    ("x_full"    , x_full);
   rc = lstat (x_full, &s);
   DEBUG_YEXEC  yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "actual file could not be located in å%sæ", a_dir);
      DEBUG_INPT   yLOG_note    ("actual file could not be found");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "located the actual file in å%sæ", a_dir);
   /*---(check file type)----------------*/
   --rce;  if (S_ISDIR (s.st_mode))  {
      yURG_err ('f', "file actually refers to a directory (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can not use a directory");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("not a directory");
   --rce;  if (S_ISLNK (s.st_mode))  {
      yURG_err ('f', "file actually refers to a symbolic link (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can not use a symlink");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("not a symlink");
   --rce;  if (!S_ISREG (s.st_mode))  {
      yURG_err ('f', "file is not a regular file (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can only use regular files");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("confirmed as regular file");
   yURG_msg ('-', "file is confirmed as a regular file, not a symlink/directory");
   /*---(ownership)----------------------*/
   DEBUG_YEXEC  yLOG_complex ("owner"     , "user %4d, run %4d, own %4d", a_uid, a_muid, s.st_uid);
   --rce;  if (a_loc == YJOBS_LOCAL) {
      if (s.st_uid != a_uid) {
         yURG_err ('f', "file owner does not match home directory owner (security risk)");
         DEBUG_YEXEC  yLOG_note    ("file owner does not match home directory owner (security risk)");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_muid == 0) {
         yURG_msg ('-', "running as root, can verify/install any user file");
      } else if (a_muid == s.st_uid) {
         yURG_msg ('-', "run-time user matches file ownership");
      } else {
         yURG_err ('f', "run-time user does not match file owner (security risk)");
         DEBUG_YEXEC  yLOG_note    ("file owner does not match home directory owner (security risk)");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      if (a_muid == 0) {
         yURG_msg ('-', "running as root, can audit any files");
      } else if (strcmp (a_muser, a_user) == 0) {
         yURG_msg ('-', "prefix matches user å%sæ, can audit this file", a_muser);
      } else {
         yURG_err ('f', "user prefix in file name does not match run-time user (security risk)");
         DEBUG_YEXEC  yLOG_note    ("file owner is not runtime user");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (s.st_uid != 0 || s.st_gid != 0) {
         yURG_err ('f', "central file owner/group is not root (security risk)");
         DEBUG_YEXEC  yLOG_note    ("central contab file owner/group is not root (security risk)");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "central owner and group is root");
   }
   /*---(permissions)--------------------*/
   DEBUG_ENVI   yLOG_value   ("perms"     , s.st_mode & 00777);
   if  ((s.st_mode & 00777) != 00600)  {
      yURG_err ('f', "file permissions are not owner-only read/write 0600 (security risk)");
      DEBUG_ENVI   yLOG_note    ("permissions not 0600 (private to user)");
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("permissions are 0600 (private)");
   yURG_msg ('-', "file permissions confirmed as owner-only write/read (0600)");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       local file review                      ----===*/
/*====================------------------------------------====================*/
static void      o___LOCAL___________________o (void) {;};

char
yJOBS_acceptable_full    (cchar a_runas, cchar *a_home, cchar *a_root, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cwd       [LEN_PATH]  = "";
   char        x_fuser     [LEN_LABEL] = "";
   int         x_fuid      =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "local file verification...");
   /*---(defaults)-----------------------*/
   if (r_fuser != NULL)  strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid = -1;
   if (r_fdesc != NULL)  strcpy (r_fdesc, "");
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   /*---(naming)-------------------------*/
   rc = yjobs__naming (a_name);
   DEBUG_INPT  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify user)--------------------*/
   rc = yjobs__location (a_runas, YJOBS_LOCAL, a_home, a_root, a_name, a_muser, a_muid, x_fuser, &x_fuid, x_cwd);
   DEBUG_INPT  yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(stats)--------------------------*/
   rc = yjobs__stats (YJOBS_LOCAL, x_cwd, a_name, a_muser, a_muid, x_fuser, x_fuid);
   DEBUG_INPT  yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   if (r_fuser != NULL)  strlcpy (r_fuser, x_fuser, LEN_USER);
   if (r_fuid  != NULL)  *r_fuid = x_fuid;
   if (r_fdesc != NULL)  strlcpy (r_fdesc, a_name + 8, LEN_DESC);
   if (r_dir   != NULL)  strlcpy (r_dir  , x_cwd, LEN_PATH);
   /*---(finish)-------------------------*/
   yURG_msg ('-', "SUCCESS, job/khronos file acceptable");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_local_dir         (cchar a_runas, char *a_root, char *a_home)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(directories)--------------------*/
   --rce;  switch (a_runas) {
   case IAM_KHRONOS  : case IAM_EOS  : case IAM_ASTRAIOS  : case IAM_HYPNOS  : case IAM_HERACLES  :
      strcpy (a_root, "/root");
      strcpy (a_home, "/home/");
      break;
   case IAM_UKHRONOS : case IAM_UEOS : case IAM_UASTRAIOS : case IAM_UHYPNOS : case IAM_UHERACLES :
      strcpy (a_root, "/tmp/yJOBS/root");
      strcpy (a_home, "/tmp/yJOBS/");
      break;
   default  :
      yURG_err ('f', "a_runas (%c) is not recognized", a_runas);
      return rce;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yJOBS_acceptable         (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir)
{
   char        rc          =    0;
   char        x_user      [LEN_LABEL] = "";
   char        x_root      [LEN_PATH]  = "";
   char        x_home      [LEN_PATH]  = "";
   int         x_uid       =    0;
   if (rc >= 0) rc = yJOBS_local_dir       (a_runas, x_root, x_home);
   if (rc >= 0) rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, &x_user, 'n');
   if (rc >= 0) rc = yJOBS_acceptable_full (a_runas, x_home, x_root, a_name, x_user, x_uid, r_fuser, r_fuid, r_fdesc, r_dir);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                     central file review                      ----===*/
/*====================------------------------------------====================*/
static void      o___CENTRAL_________________o (void) {;};

char
yJOBS_central_full       (cchar a_runas, cchar *a_central, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cwd       [LEN_PATH]  = "";
   char        x_fuser     [LEN_LABEL] = "";
   int         x_fuid      =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "central file check...");
   /*---(defaults)-----------------------*/
   if (r_fuser != NULL)  strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid = -1;
   if (r_fdesc != NULL)  strcpy (r_fdesc, "");
   /*---(naming)-------------------------*/
   rc = yjobs__naming (a_name);
   DEBUG_INPT  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify user)--------------------*/
   rc = yjobs__location (a_runas, YJOBS_CENTRAL, "n/a", "n/a", a_name, a_muser, a_muid, x_fuser, &x_fuid, x_cwd);
   DEBUG_INPT  yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(stats)--------------------------*/
   rc = yjobs__stats (YJOBS_CENTRAL, a_central, a_name, a_muser, a_muid, x_fuser, x_fuid);
   DEBUG_INPT  yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   if (r_fuser != NULL)  strlcpy (r_fuser, x_fuser, LEN_USER);
   if (r_fuid  != NULL)  *r_fuid = x_fuid;
   if (r_fdesc != NULL)  strlcpy (r_fdesc, a_name + strlen (x_fuser) + 1 , LEN_DESC);
   /*---(finish)-------------------------*/
   yURG_msg ('-', "SUCCESS, job/khronos file acceptable");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_central_dir       (cchar a_runas, cchar *a_name, char *a_dir, char *a_user, char *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   char        t           [LEN_PATH]  = "";
   /*---(directories)--------------------*/
   --rce;  switch (a_runas) {
   case IAM_KHRONOS  :
      strcpy (a_dir, "/var/spool/khronos/");
      break;
   case IAM_UKHRONOS :
      strcpy (a_dir, "/tmp/yJOBS/khronos/");
      break;
   case IAM_EOS  : case IAM_ASTRAIOS  : case IAM_HYPNOS  :
      strcpy (a_dir, "/etc/");
      break;
   case IAM_UEOS : case IAM_UASTRAIOS : case IAM_UHYPNOS :
      strcpy (a_dir, "/tmp/yJOBS/etc/");
      break;
   case IAM_HERACLES  :
      strcpy (a_dir, "/var/spool/heracles/");
      break;
   case IAM_UHERACLES :
      strcpy (a_dir, "/tmp/yJOBS/heracles/");
      break;
   default  :
      yURG_err ('f', "a_runas (%c) is not recognized", a_runas);
      return rce;
      break;
   }
   /*---(check if file too)--------------*/
   if (a_file == NULL)  return 0;
   /*---(files)--------------------------*/
   --rce;  switch (a_runas) {
   case IAM_KHRONOS   : case IAM_UKHRONOS  :
      DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
      if (strncmp (a_name, "khronos.", 8) == 0) {
         p = strchr (a_name, '.');
         DEBUG_INPT   yLOG_point   ("p"         , p);
         if (p == NULL)  return rce;
         DEBUG_INPT   yLOG_info    ("a_user"    , a_user);
         sprintf (a_file, "%s%s", a_user, p);
      } else {
         strcpy (a_file, a_name);
      }
      DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
      break;
   case IAM_EOS       : case IAM_UEOS      : 
      strlcpy (a_file, "eos.conf"     , LEN_PATH);
      break;
   case IAM_ASTRAIOS  : case IAM_UASTRAIOS : 
      strlcpy (a_file, "asterios.conf", LEN_PATH);
      break;
   case IAM_HYPNOS    : case IAM_UHYPNOS   : 
      strlcpy (a_file, "hypnos.conf"  , LEN_PATH);
      break;
   case IAM_HERACLES  : case IAM_UHERACLES : 
      DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
      if (strncmp (a_name, "job.", 4) == 0) {
         p = strchr (a_name, '.');
         DEBUG_INPT   yLOG_point   ("p"         , p);
         if (p == NULL)  return rce;
         DEBUG_INPT   yLOG_info    ("a_user"    , a_user);
         sprintf (a_file, "%s%s", a_user, p);
      } else {
         strcpy (a_file, a_name);
      }
      DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
      break;
   default  :
      yURG_err ('f', "a_runas (%c) is not recognized", a_runas);
      return rce;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yJOBS_central            (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir)
{
   char        rce         =  -10;
   char        rc          =    0;
   char        x_user      [LEN_LABEL] = "";
   int         x_uid       =    0;
   char        x_center    [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   rc = yEXEC_whoami (NULL, NULL, &x_uid, NULL, &x_user, 'n');
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      return rce;
   }
   rc = yJOBS_central_dir (a_runas, a_name, x_center, x_user, x_file);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify central directory");
      return rce;
   }
   if (r_dir   != NULL)  strlcpy (r_dir, x_center, LEN_PATH);
   rc = yJOBS_central_full (a_runas, x_center, x_file, x_user, x_uid, r_fuser, r_fuid, r_fdesc);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char
yJOBS__unit_rmdir       (void)
{
   yURG_rmdir ("/tmp/yJOBS/");
   return 0;
}

char
yJOBS__unit_mkdir       (void)
{
   /*---(clear test dirs)----------------*/
   yJOBS__unit_rmdir ();
   /*---(leave if not unit test)---------*/
   switch (g_runas) {
   case IAM_UEOS      : case IAM_UASTRAIOS : case IAM_UHYPNOS   : case IAM_UHERACLES : case IAM_UKHRONOS  :
      break;
   default            :
      return 0;
      break;
   }
   /*---(set up base)--------------------*/
   yURG_mkdir ("/tmp/yJOBS/"       , "root"   , "root"  , "0755");
   /*---(set up central)-----------------*/
   switch (g_runas) {
   case IAM_UEOS      : case IAM_UASTRAIOS : case IAM_UHYPNOS   :
      yURG_mkdir ("/tmp/yJOBS/etc"     , "root"   , "root"  , "0700");
      break;
   case IAM_UHERACLES :
      yURG_mkdir ("/tmp/yJOBS/heracles", "root"   , "root"  , "0700");
      break;
   case IAM_UKHRONOS  :
      yURG_mkdir ("/tmp/yJOBS/khronos" , "root"   , "root"  , "0700");
      break;
   }
   /*---(set up locals)------------------*/
   yURG_mkdir ("/tmp/yJOBS/root"   , "root"   , "root"  , "0700");
   yURG_mkdir ("/tmp/yJOBS/member" , "member" , "root"  , "0700");
   yURG_mkdir ("/tmp/yJOBS/machine", "machine", "root"  , "0700");
   yURG_mkdir ("/tmp/yJOBS/monkey" , "monkey" , "root"  , "0700");
   /*---(complete)-----------------------*/
   return 0;
}


