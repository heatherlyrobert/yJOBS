/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char
yjobs__dir_fix          (char a_dir [LEN_PATH], char a_issue, int a_perms, tSTAT *r_stat)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("r_stat"    , r_stat);
   --rce;  if (r_stat == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("d-", yENV_exists (a_dir)) == NULL) {
      DEBUG_YJOBS   yLOG_note    ("filesystem entry is not a directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("a_perms"   , a_perms);
   rc = yENV_perms_data ('i', NULL, &a_perms, t);
   DEBUG_YJOBS   yLOG_value   ("perms"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("t"         , t);
   /*---(messages)-----------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_issue"   , a_issue);
   --rce;  switch (a_issue) {
   case 'e' :
      DEBUG_YJOBS   yLOG_note    ("fixdir attempting create");
      yURG_msg ('1', "directory does not exist, attempting to create");
      break;
   case 'o' :
      DEBUG_YJOBS   yLOG_note    ("fixdir attempting change owner");
      yURG_msg ('1', "owner is not �root�, attempting to change");
      break;
   case 'g' :
      DEBUG_YJOBS   yLOG_note    ("fixdir attempting change group");
      yURG_msg ('1', "group is not �root�, attempting to change");
      break;
   case 'p' :
      DEBUG_YJOBS   yLOG_note    ("fixdir attempting change permissions");
      yURG_msg ('1', "permissions are not �%s�, attempting to change", t);
      break;
   default  :
      DEBUG_YJOBS   yLOG_note    ("no such a_issue option allowed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(handle update)------------------*/
   rc = yENV_mkdir (a_dir, "root", "root", t);
   DEBUG_YJOBS   yLOG_char    ("mkdir"     , rc);
   --rce;  if (rc == '-') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset stat)---------------------*/
   rc = lstat (a_dir, r_stat);
   DEBUG_YJOBS   yLOG_value   ("lstat"     , rc);
   DEBUG_YJOBS   yLOG_point   ("r_stat"    , r_stat);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_REPAIR;
}

char
yjobs__dir_check         (char a_level, char a_dir [LEN_PATH], int a_perms, char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    1;
   tSTAT       s;
   int         x_perms     =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_value   ("a_level"   , a_level);
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   yURG_msg ('-', "checking level %d �%s�", a_level, a_dir);
   /*---(check existance)----------------*/
   rc = lstat (a_dir, &s);
   DEBUG_YJOBS   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      if (a_fix == 'y') rc = yjobs__dir_fix (a_dir, 'e', a_perms, &s);
      if (rc < 0) {
         yURG_err ('f', "�%s� directory does not exist (bad configuration)", a_dir);
         DEBUG_YJOBS   yLOG_note    ("can not open/stat directory");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   --rce;  if (S_ISLNK (s.st_mode))  {
      yURG_err ('f', "�%s� actually refers to a symbolic link (security risk)", a_dir);
      DEBUG_YJOBS  yLOG_note    ("can not use a symlink");
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISREG (s.st_mode))  {
      yURG_err ('f', "�%s� is a regular file, not a directory (bad configuration)", a_dir);
      DEBUG_YJOBS   yLOG_note    ("can not use a regular file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISDIR (s.st_mode))  {
      yURG_err ('f', "�%s� is a specialty file (bad configuration)", a_dir);
      DEBUG_YJOBS   yLOG_note    ("can not use a specialty file");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "�%s� directory exists and is not a file/symlink", a_dir);
   /*---(ownership)----------------------*/
   --rce;  if (s.st_uid != 0) {
      if (a_fix == 'y') rc = yjobs__dir_fix (a_dir, 'o', a_perms, &s);
      if (s.st_uid != 0) {
         yURG_err ('f', "�%s� is not owned by root (security risk)", a_dir);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not owned by root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   DEBUG_YJOBS  yLOG_note    ("ownership is root (private)");
   --rce;  if (s.st_gid != 0) {
      if (a_fix == 'y') rc = yjobs__dir_fix (a_dir, 'g', a_perms, &s);
      if (s.st_gid != 0) {
         yURG_err ('f', "�%s� is not in root group (security risk)", a_dir);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not group of root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   yURG_msg ('-', "�%s� directory owner and group are both root", a_dir);
   DEBUG_YJOBS  yLOG_note    ("owner and group are both root (private)");
   /*---(permissions)--------------------*/
   x_perms = s.st_mode & 07777;
   DEBUG_YJOBS   yLOG_complex ("x_perms"   , "%04o", x_perms);
   DEBUG_YJOBS   yLOG_complex ("a_perms"   , "%04o", a_perms);
   --rce;  if  (x_perms != a_perms)  {
      if (a_fix == 'y') rc = yjobs__dir_fix (a_dir, 'p', a_perms, &s);
      x_perms = s.st_mode & 07777;
      if  (x_perms != a_perms)  {
         yURG_err ('f', "�%s� perms are %04o, not the requested %04o (security risk)", a_dir, s.st_mode & 07777, a_perms);
         DEBUG_YJOBS   yLOG_note    ("permissions not set correctly (private to user)");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   yURG_msg ('-', "�%s� directory permissions confirmed as %04o", a_dir, a_perms);
   DEBUG_YJOBS  yLOG_note    ("permissions are appropiate (private)");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yjobs_dir_single        (char a_level, char a_dir [LEN_PATH], char a_fix)
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
   DEBUG_YJOBS   yLOG_complex ("x_dir"     , "%2d�%s�", l, x_dir);
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
   DEBUG_YJOBS   yLOG_complex ("r_dir"     , "%2d�%s�", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs_dir_single (a_level + 1, r_dir, a_fix);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(tail execute)-------------------*/
   l = strlen (x_dir);
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2d�%s�", l, x_dir);
   rc = 0;
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 01777, a_fix);
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yjobs__dir_check (a_level, x_dir, 0755 , a_fix);
   else                                         rc = yjobs__dir_check (a_level, x_dir, 0700 , a_fix);
   /*---(handle trouble)-----------------*/
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_dir_review        (char a_runas, char a_act, char a_oneline [LEN_HUND], char a_fix)
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
   /*---(defense)-------------------------------*/
   rc = yjobs_who_location (a_runas, x_cdir, x_hdir, x_world, NULL, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check configuration dir)---------------*/
   yURG_msg ('>', "configuration directory setup/security review...");
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   --rce;  if (strcmp (x_cdir, "") != 0) {
      rc = yjobs_dir_single (0, x_cdir, a_fix);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "success, configuration directory basic security measures confirmed");
   } else {
      yURG_msg ('-', "skipping, no configuration directory specified for application");
   }
   /*---(check central data dir)----------------*/
   yURG_msg ('>', "central data directory setup/security review...");
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   if (strcmp (x_hdir, "") != 0) {
      rc = yjobs_dir_single (0, x_hdir, a_fix);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "success, central data directory basic security measures confirmed");
   } else {
      yURG_msg ('-', "skipping, no central data directory specified for application");
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yJOBS_security      (void) { return yjobs_dir_review (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, '-'); }
char yJOBS_fix           (void) { return yjobs_dir_review (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, 'y'); }


char
yjobs_dir_list          (char a_path [LEN_PATH], char r_list [LEN_MASS])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         rc_final    =    0;
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_list != NULL)  strcpy (r_list, "");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL || a_path [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_path"    , a_path);
   DEBUG_YJOBS   yLOG_point   ("r_list"    , r_list);
   --rce;  if (r_list  == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("r_list"    , r_list);
   /*---(prepare)------------------------*/
   ystrlcpy (r_list, ","           , LEN_MASS);
   /*---(open dir)-----------------------*/
   x_dir = opendir (a_path);
   DEBUG_YJOBS   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      yURG_err ('f', "could not open directory");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "successfully openned directory");
   /*---(walk files)---------------------*/
   DEBUG_YJOBS   yLOG_note    ("walk through directory files");
   x_file = readdir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      /*---(concatenate)-----------------*/
      DEBUG_YJOBS   yLOG_info    ("d_name"    , x_file->d_name);
      ystrlcat (r_list, x_file->d_name, LEN_MASS);
      ystrlcat (r_list, ","           , LEN_MASS);
      /*---(next)------------------------*/
      x_file = readdir (x_dir);
      DEBUG_YJOBS   yLOG_point   ("x_file"    , x_file);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YJOBS   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(sort)---------------------------*/
   rc = ySORT_string (r_list);
   DEBUG_YJOBS   yLOG_point   ("sort"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

