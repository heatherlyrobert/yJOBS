/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                            naming                            ----===*/
/*====================------------------------------------====================*/
static void      o___NAMING__________________o (void) {;};

char
yjobs__name_quality     (uchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   uchar      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || strlen (a_name) <= 0) {
      yURG_err ('f', "file name can not be null or empty (blatant error)");
      DEBUG_YEXEC   yLOG_note    ("file name can not be null or empty");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("a_name"    , a_name);
   yURG_msg ('-', "name å%sæ is not empty/null", a_name);
   /*---(path)---------------------------*/
   p = strchr (a_name, '/');
   DEBUG_YEXEC   yLOG_point   ("/"         , p);
   --rce;  if (p != NULL) {
      yURG_err ('f', "file name can not include relative/absolute path (security risk)");
      DEBUG_YEXEC   yLOG_note    ("file name can not include relative/absolute path (security risk)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_note    ("file name is pathless/local");
   yURG_msg ('-', "file name is pathless/local");
   /*---(name length)--------------------*/
   l = strlen (a_name);
   DEBUG_YEXEC   yLOG_value   ("l"         , l);
   --rce;  if (l <  7) {
      yURG_err ('f', "file name can not be shorter than 7 chars (lazy)");
      DEBUG_YEXEC   yLOG_note    ("file name can not be shorter than 7 chars (lazy)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (l >= LEN_DESC) {
      yURG_err ('f', "file name can not be longer than 50 chars (security risk)");
      DEBUG_YEXEC   yLOG_note    ("file name can not be longer than 50 chars (security risk)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_note    ("file name is of acceptable length (7-50 chars)");
   yURG_msg ('-', "file name is of acceptable length (7-50 chars)");
   /*---(name quality)-------------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_name [i]) == NULL) {
         yURG_err ('f', "file name has an illegal character (%c) at position %d (security risk)", a_name [i], i);
         DEBUG_YEXEC   yLOG_complex ("bad char"  , "can not include %c at %d", a_name [i], i);
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YEXEC   yLOG_note    ("all name characters are acceptable");
   yURG_msg ('-', "all the file name characters are legal [A-Za-z0-9_.]");
   /*---(hidden file)--------------------*/
   DEBUG_YEXEC   yLOG_char    ("first char", a_name [0]);
   --rce;  if (a_name [0] == '.') {
      yURG_err ('f', "file can not be hidden, lead period (security risk)");
      DEBUG_YEXEC   yLOG_note    ("file can not be hidden");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "file is not hidden, no lead period");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__name_local       (cchar a_runas, uchar *a_name, uchar *r_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_local     =  '·';
   char        x_pre       [LEN_LABEL] = "";
   char        x_suf       [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   int         l           =    0;
   int         c           =    0;
   int         x_rem       =    0;
   uchar      *x_beg       = NULL;
   uchar      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_desc != NULL)  strlcpy (r_desc, "", LEN_DESC);
   /*---(find)---------------------------*/
   DEBUG_YEXEC   yLOG_char    ("a_runas"   , a_runas);
   rc = yjobs_who_naming (a_runas, &x_local, NULL, x_pre, NULL, x_suf, NULL);
   DEBUG_YEXEC   yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "can not find legal runas record for (%c) in who table", a_runas);
      DEBUG_YEXEC   yLOG_complex ("bad runas" , "can not find legal runas record for (%c) in who table", a_runas);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify local type)--------------*/
   DEBUG_YEXEC   yLOG_char    ("allowed"   , x_local);
   --rce;  if (x_local != 'y') {
      yURG_err ('f', "this runas does not support any local files");
      DEBUG_YEXEC   yLOG_complex ("illegal"   , "this runas does not support local files");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(at least one period)------------*/
   c = strldcnt (a_name, '.', LEN_RECD);
   DEBUG_YEXEC   yLOG_value   ("periods"   , c);
   x_beg = a_name;
   x_rem = strlen (a_name);
   DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   DEBUG_YEXEC   yLOG_info    ("x_beg"     , x_beg);
   /*---(check prefix)-------------------*/
   --rce;  if (strcmp (x_pre, "") != 0)  {
      DEBUG_YEXEC   yLOG_info    ("x_pre"     , x_pre);
      --rce;  if (c < 1) {
         yURG_err ('f', "prefix-style name does not have at least one separator/periods (illegal)");
         DEBUG_YEXEC   yLOG_note    ("name must have exactly one separator/period");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      p = strchr (a_name, '.');
      l = p - a_name + 1;
      strlcpy (t, a_name, l + 1);
      DEBUG_YEXEC   yLOG_info    ("t"         , t);
      --rce;  if (strcmp (t, x_pre) != 0) {
         yURG_err ('f', "name prefix å%sæ does not match local standard å%sæ (illegal)", t, x_pre);
         DEBUG_YEXEC   yLOG_note    ("file prefix does not match local stanard");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name prefix å%sæ matches local standard å%sæ", t, x_pre);
      DEBUG_YEXEC   yLOG_note    ("file prefix matches standard");
      x_rem -= strlen (x_pre);
      x_beg  = p + 1;
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
      DEBUG_YEXEC   yLOG_info    ("x_beg"     , x_beg);
   }
   /*---(check suffix)-------------------*/
   --rce;  if (strcmp (x_suf, "") != 0)  {
      DEBUG_YEXEC   yLOG_info    ("x_suf"     , x_suf);
      --rce;  if (c < 1) {
         yURG_err ('f', "suffix-style name does not have at least one separator/periods (illegal)");
         DEBUG_YEXEC   yLOG_note    ("name must have exactly one separator/period");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      p = strrchr (a_name, '.');
      strlcpy (t, p, LEN_LABEL);
      DEBUG_YEXEC   yLOG_info    ("t"         , t);
      if (strcmp (t, x_suf) != 0) {
         yURG_err ('f', "name suffix å%sæ does not match local standard å%sæ (illegal)", t, x_suf);
         DEBUG_YEXEC   yLOG_note    ("file suffix does not match local stanard");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name suffix å%sæ matches local standard å%sæ", t, x_suf);
      DEBUG_YEXEC   yLOG_note    ("file suffix matches stanard");
      x_rem -= strlen (x_suf);
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(remaining description)----------*/
   --rce;  if (x_rem < 3) {
      yURG_err ('f', "file description can not be shorter than 3 characters (lazy)");
      DEBUG_YEXEC   yLOG_note    ("description too short (< 3 chars)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "name description is adequate length (>= 3 characters)");
   /*---(save-back)----------------------*/
   DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   DEBUG_YEXEC   yLOG_info    ("x_beg"     , x_beg);
   if (r_desc != NULL && x_rem >= 1)  strlcpy (r_desc, x_beg, x_rem + 1);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__name_central     (cchar a_runas, uchar *a_name, uchar *r_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_central   =  '·';
   char        x_pre       [LEN_LABEL] = "";
   char        x_suf       [LEN_LABEL] = "";
   char        x_name      [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   int         l           =    0;
   int         c           =    0;
   int         x_rem       =    0;
   uchar      *x_beg       = NULL;
   uchar      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_desc != NULL)  strlcpy (r_desc, "", LEN_DESC);
   /*---(find)---------------------------*/
   DEBUG_YEXEC   yLOG_char    ("a_runas"   , a_runas);
   rc = yjobs_who_naming (a_runas, NULL, &x_central, NULL, x_pre, x_suf, x_name);
   DEBUG_YEXEC   yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "can not find legal runas record for (%c) in who table", a_runas);
      DEBUG_YEXEC   yLOG_complex ("bad runas" , "can not find legal runas record for (%c) in who table", a_runas);
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify local type)--------------*/
   DEBUG_YEXEC   yLOG_char    ("allowed"   , x_central);
   --rce;  if (x_central != 'y') {
      yURG_err ('f', "this runas does not support any central files");
      DEBUG_YEXEC   yLOG_complex ("illegal"   , "this runas does not support central files");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(at least one period)------------*/
   c = strldcnt (a_name, '.', LEN_RECD);
   DEBUG_YEXEC   yLOG_value   ("periods"   , c);
   x_beg = a_name;
   x_rem = strlen (a_name);
   /*---(check prefix)-------------------*/
   --rce;  if (strcmp (x_pre, "(USER).") == 0)  {
      --rce;  if (c < 1) {
         yURG_err ('f', "prefix-style name does not have at least one separator/periods (illegal)");
         DEBUG_YEXEC   yLOG_note    ("name must have exactly one separator/period");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      p = strchr (a_name, '.');
      l = p - a_name + 1;
      strlcpy (t, a_name, l);
      rc = yEXEC_userdata (t, NULL, NULL, NULL, NULL);
      DEBUG_YEXEC   yLOG_value   ("userdata"  , rc);
      --rce;  if (rc < 0) {
         yURG_err ('f', "name prefix å%sæ does not match a valid system user (illegal)", t);
         DEBUG_YEXEC   yLOG_note    ("file prefix does not match a valid system user");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name prefix å%sæ matches a valid system user", t);
      DEBUG_YEXEC   yLOG_note    ("file prefix matches a valid system user");
      x_rem -= l;
      x_beg  = p + 1;
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   } else if (strcmp (x_pre, "") != 0)  {
      DEBUG_YEXEC   yLOG_info    ("x_pre"     , x_pre);
      --rce;  if (c < 1) {
         yURG_err ('f', "prefix-style name does not have at least one separator/periods (illegal)");
         DEBUG_YEXEC   yLOG_note    ("name must have exactly one separator/period");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      p = strchr (a_name, '.');
      l = p - a_name + 1;
      strlcpy (t, a_name, l + 1);
      DEBUG_YEXEC   yLOG_info    ("t"         , t);
      --rce;  if (strcmp (t, x_pre) != 0) {
         yURG_err ('f', "name prefix å%sæ does not match central standard å%sæ (illegal)", t, x_pre);
         DEBUG_YEXEC   yLOG_note    ("file prefix does not match central stanard");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name prefix å%sæ matches central standard å%sæ", t, x_pre);
      DEBUG_YEXEC   yLOG_note    ("file prefix matches standard");
      x_rem -= strlen (x_pre);
      x_beg  = p + 1;
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
      DEBUG_YEXEC   yLOG_info    ("x_beg"     , x_beg);
   }
   /*---(check suffix)-------------------*/
   --rce;  if (strcmp (x_suf, "") != 0)  {
      DEBUG_YEXEC   yLOG_info    ("x_suf"     , x_suf);
      --rce;  if (c < 1) {
         yURG_err ('f', "suffix-style name does not have at least one separator/periods (illegal)");
         DEBUG_YEXEC   yLOG_note    ("name must have exactly one separator/period");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      p = strrchr (a_name, '.');
      strlcpy (t, p, LEN_LABEL);
      DEBUG_YEXEC   yLOG_info    ("t"         , t);
      if (strcmp (t, x_suf) != 0) {
         yURG_err ('f', "name suffix å%sæ does not match central standard å%sæ (illegal)", t, x_suf);
         DEBUG_YEXEC   yLOG_note    ("file suffix does not match central stanard");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name suffix å%sæ matches central standard å%sæ", t, x_suf);
      DEBUG_YEXEC   yLOG_note    ("file suffix matches stanard");
      x_rem -= strlen (x_suf);
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(check fullname)-----------------*/
   --rce;  if (strcmp (x_name, "") != 0)  {
      DEBUG_YEXEC   yLOG_info    ("x_name"    , x_name);
      if (strcmp (a_name, x_name) != 0) {
         yURG_err ('f', "name å%sæ does not match central standard å%sæ (illegal)", a_name, x_name);
         DEBUG_YEXEC   yLOG_note    ("name does not match central stanard");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name å%sæ matches central standard å%sæ", a_name, x_name);
      DEBUG_YEXEC   yLOG_note    ("file matches standard");
      x_rem  = 0;
      DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(remaining description)----------*/
   else {
      --rce;  if (x_rem < 3) {
         yURG_err ('f', "file description can not be shorter than 3 characters (lazy)");
         DEBUG_YEXEC   yLOG_note    ("description too short (< 3 chars)");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "name description is adequate length (>= 3 characters)");
   }
   /*---(save-back)----------------------*/
   DEBUG_YEXEC   yLOG_value   ("x_rem"     , x_rem);
   DEBUG_YEXEC   yLOG_info    ("x_beg"     , x_beg);
   if (r_desc != NULL && x_rem >= 1)  strlcpy (r_desc, x_beg, x_rem + 1);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__naming           (cchar a_runas, cchar a_loc, uchar *a_name, uchar *r_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   int         c           =    0;
   uchar      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_desc != NULL)  strlcpy (r_desc, "", LEN_DESC);
   /*---(name quality)-------------------*/
   rc = yjobs__name_quality (a_name);
   DEBUG_YEXEC   yLOG_value   ("quality"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check local)--------------------*/
   --rce;  if (a_loc == YJOBS_LOCAL) {
      rc = yjobs__name_local   (a_runas, a_name, r_desc);
      DEBUG_YEXEC   yLOG_value   ("quality"   , rc);
      if (rc < 0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check central)------------------*/
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      rc = yjobs__name_central (a_runas, a_name, r_desc);
      DEBUG_YEXEC   yLOG_value   ("quality"   , rc);
      if (rc < 0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           location                           ----===*/
/*====================------------------------------------====================*/
static void      o___LOCATION________________o (void) {;};

char
yjobs__loc_prepare      (cchar a_runas, cchar a_loc, cchar *a_home, cchar *a_root, uchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_fuser != NULL)   strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid  = -1;
   if (r_dir   != NULL)   strcpy (r_dir  , "");
   /*---(defense : home)-----------------*/
   DEBUG_YEXEC   yLOG_point   ("a_home"    , a_home);
   --rce;  if (a_home  == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_home);
   DEBUG_YEXEC   yLOG_complex ("a_home"    , "%2då%sæ", l, a_home);
   --rce;  if (l < 5) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense : root)-----------------*/
   DEBUG_YEXEC   yLOG_point   ("a_root"    , a_root);
   --rce;  if (a_root  == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_root);
   DEBUG_YEXEC   yLOG_complex ("a_root"    , "%2då%sæ", l, a_root);
   --rce;  if (l < 5) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense : name)-----------------*/
   DEBUG_YEXEC   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name  == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("a_name"    , a_name);
   /*---(defense : muser)----------------*/
   DEBUG_YEXEC   yLOG_point   ("a_muser"   , a_muser);
   --rce;  if (a_muser == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("a_muser"   , a_muser);
   DEBUG_YEXEC   yLOG_value   ("a_muid"    , a_muid);
   DEBUG_YEXEC   yLOG_point   ("r_fuser"   , r_fuser);
   /*---(defense : returns)--------------*/
   --rce;  if (r_fuser == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_point   ("r_fuid"    , r_fuid);
   --rce;  if (r_fuid  == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_point   ("r_dir"     , r_dir);
   --rce;  if (r_dir   == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__loc_local        (cchar *a_home, cchar *a_root, cchar *a_muser, int a_muid, char *r_fuser, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_PATH]  = "";
   int         l           =    0;
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(check directory)----------------*/
   p = getcwd (r_dir, LEN_PATH);
   DEBUG_YEXEC   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      yURG_err ('f', "can not obtain current working directory");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcat (r_dir, "/", LEN_PATH);
   DEBUG_YEXEC   yLOG_info    ("r_dir"     , r_dir);
   yURG_msg ('-', "current working directory is å%sæ", r_dir);
   /*---(check normal install)-----------*/
   --rce;  if (a_muid != 0) {
      sprintf (t, "%s%s", a_home, a_muser);
      DEBUG_YEXEC   yLOG_info    ("expect"    , t);
      l = strlen (t);
      if (strncmp (r_dir, t, l) != 0) {
         yURG_err ('f', "user not in or below their own home directory (security risk)");
         DEBUG_YEXEC   yLOG_note    ("user not in or below their own home directory");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcpy (r_fuser, a_muser, LEN_USER);
      yURG_msg ('-', "normal user file in or below their own home directory");
   }
   /*---(check root install)-------------*/
   --rce;  if (a_muid == 0) {
      DEBUG_YEXEC   yLOG_note    ("root user verifying");
      sprintf (t, "%s", a_root);
      l = strlen (t);
      DEBUG_YEXEC   yLOG_complex ("cdir"      , "%2d å%sæ vs å%sæ", l, t, r_dir);
      if (strncmp (r_dir, t, l) == 0) {
         DEBUG_YEXEC   yLOG_note    ("root in root user home directory tree");
         strlcpy (r_fuser, "root", LEN_USER);
         yURG_msg ('-', "root user file in or below årootæ home directory");
      } else {
         sprintf (t, "%s", a_home);
         l = strlen (t);
         if (strncmp (r_dir, t, l) == 0) {
            DEBUG_YEXEC   yLOG_note    ("root in another user home directory tree");
            strlcpy  (s, r_dir + l, LEN_PATH);
            strldchg (s, '/', '\0', LEN_PATH);
            strlcpy (r_fuser, s, LEN_USER);
            if (strcmp (r_fuser, "machine") == 0) {
               DEBUG_YEXEC   yLOG_note    ("change machine user to root");
               strlcpy (r_fuser, "root", LEN_USER);
               yURG_msg ('-', "root user file in or below å%sæ home directory, so use årootæ as user", s);
            } else {
               yURG_msg ('-', "root user file in or below å%sæ home directory", s);
            }
         } else {
            yURG_err ('f', "root, but not in or below any valid user home directory (security risk)");
            DEBUG_YEXEC   yLOG_note    ("root, but not in or below a valid user home directory");
            DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__loc_central      (cchar a_runas, uchar *a_name, char *r_fuser, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(check directory)----------------*/
   yjobs_who_location      (a_runas, r_dir, NULL, NULL, NULL);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("r_dir"     , r_dir);
   yURG_msg ('-', "central storage directory is å%sæ", r_dir);
   /*---(verify user)--------------------*/
   switch (a_runas) {
   case IAM_HERACLES  : case IAM_UHERACLES :
   case IAM_KHRONOS   : case IAM_UKHRONOS  :
      strlcpy  (s      , a_name   , LEN_USER);
      strldchg (s      , '.', '\0', LEN_USER);
      strlcpy  (r_fuser, s        , LEN_USER);
      yURG_msg ('-', "central file prefix is å%sæ", r_fuser);
      break;
   default :
      strlcpy  (r_fuser, "root"   , LEN_USER);
      yURG_msg ('-', "all non-job files require root access");
      break;
   }
   DEBUG_YEXEC   yLOG_info    ("r_fuser"    , r_fuser);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
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
   char        s           [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   rc = yjobs__loc_prepare  (a_runas, a_loc, a_home, a_root, a_name, a_muser, a_muid, r_fuser, r_fuid, r_dir);
   DEBUG_YEXEC   yLOG_value   (__FUNCTION__, rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle local)-------------------*/
   --rce;  if (a_loc == YJOBS_LOCAL) {
      rc = yjobs__loc_local     (a_home, a_root, a_muser, a_muid, r_fuser, r_dir);
      DEBUG_YEXEC   yLOG_value   (__FUNCTION__, rc);
      if (rc < 0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(handle central)-----------------*/
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      rc = yjobs__loc_central   (a_runas, a_name, r_fuser, r_dir);
      DEBUG_YEXEC   yLOG_value   (__FUNCTION__, rc);
      if (rc < 0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check for registered)-----------*/
   rc = yEXEC_userdata (r_fuser, r_fuid, NULL, NULL, NULL);
   DEBUG_YEXEC   yLOG_value   ("userdata"  , rc);
   if (rc < 0) {
      if (a_loc == YJOBS_LOCAL) {
         yURG_err ('f', "user directory not associated with a registered user (security risk)");
      } else {
         yURG_err ('f', "user name prefix å%sæ not registered on system (security risk)", r_fuser);
      }
      DEBUG_YEXEC   yLOG_note    ("user is not registered in the system");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_value   ("*r_fuid"   , *r_fuid);
   yURG_msg ('-', "file user is registered with system, %s, uid %d", r_fuser, *r_fuid);
   /*---(name prefix)--------------------*/
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
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          statistics                          ----===*/
/*====================------------------------------------====================*/
static void      o___STATS___________________o (void) {;};

char
yjobs__stat_exists      (cchar *a_dir, uchar *a_name, tSTAT *r_stat)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(get stats)----------------------*/
   DEBUG_YEXEC  yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YEXEC  yLOG_info    ("a_name"    , a_name);
   sprintf (x_full, "%s%s", a_dir, a_name);
   DEBUG_YEXEC  yLOG_info    ("x_full"    , x_full);
   rc = lstat (x_full, r_stat);
   DEBUG_YEXEC  yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "actual entry could not be located in å%sæ", a_dir);
      DEBUG_YEXEC   yLOG_note    ("actual file could not be found");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "located the actual entry in å%sæ", a_dir);
   /*---(check file type)----------------*/
   --rce;  if (S_ISDIR (r_stat->st_mode))  {
      yURG_err ('f', "entry actually refers to a directory (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can not use a directory");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("not a directory");
   --rce;  if (S_ISLNK (r_stat->st_mode))  {
      yURG_err ('f', "entry actually refers to a symbolic link (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can not use a symlink");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("not a symlink");
   --rce;  if (!S_ISREG (r_stat->st_mode))  {
      yURG_err ('f', "entry is not a regular file (security risk)");
      DEBUG_YEXEC  yLOG_note    ("can only use regular files");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("confirmed as regular file");
   yURG_msg ('-', "entry is confirmed as a regular file, not a symlink/directory");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__stat_local       (tSTAT *a_stat, int a_muid, int a_uid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(file vs dir owner)--------------*/
   --rce;  if (a_stat->st_uid != a_uid) {
      yURG_err ('f', "file owner does not match directory owner (security risk)");
      DEBUG_YEXEC  yLOG_note    ("file owner does not match directory owner (security risk)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(owner vs looker)----------------*/
   --rce;  if (a_muid == 0) {
      yURG_msg ('-', "running as root, can verify/install any user file");
   } else if (a_muid == a_stat->st_uid) {
      yURG_msg ('-', "run-time user matches file ownership");
   } else {
      yURG_err ('f', "run-time user does not match file owner (security risk)");
      DEBUG_YEXEC  yLOG_note    ("file owner does not match home directory owner (security risk)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(user-group match)---------------*/
   --rce;  if (a_stat->st_uid != a_stat->st_gid) {
      yURG_err ('f', "file owner and group do not match (security risk)");
      DEBUG_YEXEC  yLOG_note    ("central file owner and group do not match (security risk)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "file owner and group match");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__stat_central     (tSTAT *a_stat, cchar *a_muser, int a_muid, uchar *a_user)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(check)--------------------------*/
   --rce;  if (a_muid == 0) {
      yURG_msg ('-', "running as root, can audit any files");
   } else if (strcmp (a_muser, a_user) == 0) {
      yURG_msg ('-', "prefix matches user å%sæ, can audit this file", a_muser);
   } else {
      yURG_err ('f', "user prefix on file å%sæ does not match run-time user (security risk)", a_user);
      DEBUG_YEXEC  yLOG_note    ("file owner is not runtime user");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_stat->st_uid != 0) {
      yURG_err ('f', "central file owner is not root (security risk)");
      DEBUG_YEXEC  yLOG_note    ("central file owner is not root (security risk)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_stat->st_gid != 0) {
      yURG_err ('f', "central file group is not root (security risk)");
      DEBUG_YEXEC  yLOG_note    ("central file group is not root (security risk)");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "central owner and group are both root");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(check existance)----------------*/
   rc = yjobs__stat_exists (a_dir, a_name, &s);
   DEBUG_YEXEC  yLOG_value   ("exists"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_complex ("owner"     , "user %4d, run %4d, own %4d", a_uid, a_muid, s.st_uid);
   /*---(check local)--------------------*/
   --rce;  if (a_loc == YJOBS_LOCAL) {
      rc = yjobs__stat_local  (&s, a_muid, a_uid);
      DEBUG_YEXEC  yLOG_value   ("local"     , rc);
      if (rc < 0) {
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check central)------------------*/
   --rce;  if (a_loc == YJOBS_CENTRAL) {
      rc = yjobs__stat_central  (&s, a_muser, a_muid, a_user);
      DEBUG_YEXEC  yLOG_value   ("central"   , rc);
      if (rc < 0) {
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(permissions)--------------------*/
   DEBUG_YEXEC   yLOG_value   ("perms"     , s.st_mode & 00777);
   if  ((s.st_mode & 00777) != 00600)  {
      yURG_err ('f', "file permissions are not owner-only read/write 0600 (security risk)");
      DEBUG_YEXEC   yLOG_note    ("permissions not 0600 (private to user)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_note    ("permissions are 0600 (private)");
   yURG_msg ('-', "file permissions confirmed as owner-only write/read (0600)");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "local file verification...");
   /*---(defaults)-----------------------*/
   DEBUG_YEXEC   yLOG_point   ("r_fuid"    , r_fuid);
   if (r_fuser != NULL)  strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid = -1;
   if (r_fdesc != NULL)  strcpy (r_fdesc, "");
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   /*---(naming)-------------------------*/
   rc = yjobs__naming (a_runas, YJOBS_LOCAL, a_name, r_fdesc);
   DEBUG_YEXEC  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify user)--------------------*/
   rc = yjobs__location (a_runas, YJOBS_LOCAL, a_home, a_root, a_name, a_muser, a_muid, x_fuser, &x_fuid, x_cwd);
   DEBUG_YEXEC  yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_value   ("x_fuid"    , x_fuid);
   /*---(stats)--------------------------*/
   rc = yjobs__stats (YJOBS_LOCAL, x_cwd, a_name, a_muser, a_muid, x_fuser, x_fuid);
   DEBUG_YEXEC  yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   if (r_fuser != NULL)  strlcpy (r_fuser, x_fuser, LEN_USER);
   if (r_fuid  != NULL) {
      *r_fuid = x_fuid;
      DEBUG_YEXEC   yLOG_value   ("*r_fuid"   , *r_fuid);
   }
   if (r_dir   != NULL)  strlcpy (r_dir  , x_cwd, LEN_PATH);
   /*---(finish)-------------------------*/
   yURG_msg ('-', "SUCCESS, job/khronos file acceptable");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_local_dir         (cchar a_runas, char *a_root, char *a_home)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_senter  (__FUNCTION__);
   /*---(directories)--------------------*/
   DEBUG_YEXEC  yLOG_schar   (a_runas);
   DEBUG_YEXEC  yLOG_snote   (g_unit);
   --rce;  if (strchr (g_unit, a_runas) == NULL)  {
      DEBUG_YEXEC  yLOG_snote   ("normal");
      strcpy (a_root, "/root");
      strcpy (a_home, "/home/");
   } else {
      DEBUG_YEXEC  yLOG_snote   ("unittest");
      strcpy (a_root, "/tmp/root");
      strcpy (a_home, "/tmp/home/");
   }
   /*---(report-out)---------------------*/
   DEBUG_YEXEC  yLOG_snote   (a_root);
   DEBUG_YEXEC  yLOG_snote   (a_home);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_sexit   (__FUNCTION__);
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
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(action)-------------------------*/
   DEBUG_YEXEC   yLOG_point   ("r_fuid"    , r_fuid);
   if (rc >= 0) {
      rc = yJOBS_local_dir       (a_runas, x_root, x_home);
      DEBUG_YEXEC  yLOG_value   ("dir"       , rc);
   }
   if (rc >= 0) {
      rc = yEXEC_whoami          (NULL, NULL, &x_uid, NULL, &x_user, 'n');
      DEBUG_YEXEC  yLOG_value   ("whoami"    , rc);
   }
   if (rc >= 0) {
      rc = yJOBS_acceptable_full (a_runas, x_home, x_root, a_name, x_user, x_uid, r_fuser, r_fuid, r_fdesc, r_dir);
      DEBUG_YEXEC  yLOG_value   ("acceptable", rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "central file check...");
   /*---(defaults)-----------------------*/
   if (r_fuser != NULL)  strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid = -1;
   if (r_fdesc != NULL)  strcpy (r_fdesc, "");
   /*---(naming)-------------------------*/
   rc = yjobs__naming (a_runas, YJOBS_CENTRAL, a_name, r_fdesc);
   DEBUG_YEXEC  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify user)--------------------*/
   rc = yjobs__location (a_runas, YJOBS_CENTRAL, "·····", "·····", a_name, a_muser, a_muid, x_fuser, &x_fuid, x_cwd);
   DEBUG_YEXEC  yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(stats)--------------------------*/
   rc = yjobs__stats (YJOBS_CENTRAL, a_central, a_name, a_muser, a_muid, x_fuser, x_fuid);
   DEBUG_YEXEC  yLOG_value   ("stats"     , rc);
   --rce;  if (rc < 0) {
      yURG_msg (' ', "");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   if (r_fuser != NULL)  strlcpy (r_fuser, x_fuser, LEN_USER);
   if (r_fuid  != NULL)  *r_fuid = x_fuid;
   /*> if (r_fdesc != NULL)  strlcpy (r_fdesc, a_name + strlen (x_fuser) + 1 , LEN_DESC);   <*/
   /*---(finish)-------------------------*/
   yURG_msg ('-', "SUCCESS, job/khronos file acceptable");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_central_dir       (cchar a_runas, cchar *a_name, char *r_dir, char *a_user, char *r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char        t           [LEN_PATH]  = "";
   char        x_dir       [LEN_DESC]  = "";
   char        x_central   =  '·';
   char        x_lpre      [LEN_LABEL] = "";
   char        x_cpre      [LEN_LABEL] = "";
   char        x_name      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_dir  != NULL)  strlcpy (r_dir  , "", LEN_DESC);
   if (r_file != NULL)  strlcpy (r_file , "", LEN_DESC);
   /*---(directory)----------------------*/
   rc = yjobs_who_location      (a_runas, x_dir, NULL, NULL, NULL);
   DEBUG_YEXEC  yLOG_value   ("location"  , rc);
   if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check if file too)--------------*/
   if (r_dir  != NULL)  strlcpy (r_dir  , x_dir, LEN_DESC);
   if (r_file == NULL) {
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(files)--------------------------*/
   rc = yjobs_who_naming (a_runas, NULL, &x_central, x_lpre, x_cpre, NULL, x_name);
   DEBUG_YEXEC  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_char    ("x_central" , x_central);
   --rce;  if (x_central != 'y') {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fixed central name)-------------*/
   --rce;  if (strcmp (x_name, "") != 0) {
      DEBUG_YEXEC   yLOG_note    ("central name is specific and fixed");
      strlcpy (r_file, x_name, LEN_DESC);
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(changable prefix)---------------*/
   --rce;  if (strcmp (x_cpre, "(USER)") == 0) {
      DEBUG_YEXEC   yLOG_note    ("central prefix changes to user name");
      DEBUG_YEXEC   yLOG_info    ("a_name"    , a_name);
      p = strchr (a_name, '.');
      DEBUG_YEXEC   yLOG_point   ("p"         , p);
      if (p == NULL) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YEXEC   yLOG_info    ("a_user"    , a_user);
      sprintf (r_file, "%s%s", a_user, p);
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(default)------------------------*/
   DEBUG_YEXEC   yLOG_note    ("name remains the same");
   strcpy (r_file, a_name);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
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
   char        x_file      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(action)-------------------------*/
   rc = yEXEC_whoami (NULL, NULL, &x_uid, NULL, &x_user, 'n');
   DEBUG_YEXEC  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not identify current user (yEXEC_whoami)");
      return rce;
   }
   rc = yJOBS_central_dir (a_runas, a_name, x_center, x_user, x_file);
   DEBUG_YEXEC  yLOG_value   ("dir"       , rc);
   if (rc < 0) {
      yURG_err ('f', "could not identify central directory");
      return rce;
   }
   if (r_dir   != NULL)  strlcpy (r_dir, x_center, LEN_PATH);
   rc = yJOBS_central_full (a_runas, x_center, x_file, x_user, x_uid, r_fuser, r_fuid, r_fdesc);
   DEBUG_YEXEC  yLOG_value   ("central"   , rc);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return rc;
}




