/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                       local file review                      ----===*/
/*====================------------------------------------====================*/
static void      o___LOCAL___________________o (void) {;};

char
yjobs_prepare            (char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir)
{
   /*---(returns)-------------------------*/
   if (r_fuser != NULL)  strcpy (r_fuser, "");
   if (r_fuid  != NULL)  *r_fuid = -1;
   if (r_fdesc != NULL)  strcpy (r_fdesc, "");
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   /*---(globals)-------------------------*/
   myJOBS.f_loc  = '-';
   strcpy (myJOBS.f_user, "");
   myJOBS.f_uid  = -1;
   strcpy (myJOBS.f_desc, "");
   strcpy (myJOBS.f_file, "");
   strcpy (myJOBS.f_dir , "");
   strcpy (myJOBS.f_full, "");
   /*---(complete)-----------------------*/
   return 0;
}

char
yjobs_saveback           (cchar a_loc, cchar *a_fuser, int a_fuid, char *a_fdesc, char *a_fname, char *a_fdir, char *a_full)
{
   /*---(globals)-------------------------*/
   myJOBS.f_loc  = a_loc;
   ystrlcpy (myJOBS.f_user, a_fuser, LEN_USER);
   myJOBS.f_uid  = a_fuid;
   ystrlcpy (myJOBS.f_desc, a_fdesc, LEN_DESC);
   ystrlcpy (myJOBS.f_file, a_fname, LEN_DESC);
   ystrlcpy (myJOBS.f_dir , a_fdir , LEN_PATH);
   ystrlcpy (myJOBS.f_full, a_full , LEN_PATH);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     central file review                      ----===*/
/*====================------------------------------------====================*/
static void      o___CENTRAL_________________o (void) {;};

char
yjobs__file_fix         (char a_full [LEN_PATH], char a_issue, int a_perms, tSTAT *r_stat)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_name      [LEN_USER]  = "";
   int         x_perms     =    0;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("r_stat"    , r_stat);
   --rce;  if (r_stat == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_point   ("a_full"    , a_full);
   --rce;  if (a_full == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_full"    , a_full);
   x_type = yENV_exists (a_full);
   --rce;  if (x_type != 'r') {
      DEBUG_YJOBS   yLOG_note    ("filesystem entry is not a file");
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
      /*> case 'e' :                                                                     <* 
       *>    DEBUG_YJOBS   yLOG_note    ("fixfile attempting create");                   <* 
       *>    yURG_msg ('1', "file does not exist, attempting to create");                <* 
       *>    break;                                                                      <*/
   case 'o' :
      DEBUG_YJOBS   yLOG_note    ("fixfile attempting change owner");
      rc = yENV_user_data  ('i', x_name, &(r_stat->st_uid), NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      if (strcmp (x_name, "") == 0)  strcpy (x_name, "((unknown))");
      yURG_msg ('1', "owner is å%sæ not årootæ, attempting to change", x_name);
      break;
   case 'g' :
      DEBUG_YJOBS   yLOG_note    ("fixfile attempting change group");
      rc = yENV_group_data ('i', x_name, &(r_stat->st_gid), NULL, NULL, NULL, NULL, NULL);
      yURG_msg ('1', "group is å%sæ not årootæ, attempting to change", x_name);
      break;
   case 'p' :
      DEBUG_YJOBS   yLOG_note    ("fixfile attempting change permissions");
      x_perms = (r_stat->st_mode) & 07777;
      rc = yENV_perms_data ('i', NULL, &x_perms, x_name);
      yURG_msg ('1', "permissions are å%sæ not å%sæ, attempting to change", x_name, t);
      break;
   default  :
      DEBUG_YJOBS   yLOG_note    ("no such a_issue option allowed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(handle update)------------------*/
   rc = yENV_touch (a_full, "root", "root", t);
   DEBUG_YJOBS   yLOG_char    ("touch"     , rc);
   --rce;  if (rc == '-') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset stat)---------------------*/
   rc = lstat (a_full, r_stat);
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
yjobs_central_data      (char a_dir [LEN_PATH], char a_name [LEN_LABEL], char c_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   tSTAT       s;
   char        x_full      [LEN_PATH]  = "";
   int         x_perms     =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   DEBUG_YJOBS  yLOG_char    ("c_fix"     , c_fix);
   /*---(prepare)------------------------*/
   yURG_msg ('>', "central data file check...");
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL || a_dir [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   yURG_msg ('-', "directory name å%sæ", a_dir);
   DEBUG_YJOBS   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_name"    , a_name);
   yURG_msg ('-', "file name å%sæ", a_name);
   sprintf (x_full, "%s%s", a_dir, a_name);
   yURG_msg ('-', "fully qualified name å%sæ", x_full);
   /*---(name quality)-------------------*/
   /*> rc = yjobs__name_quality (a_name);                                             <*/
   DEBUG_YJOBS   yLOG_value   ("quality"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check existance)----------------*/
   /*> rc = yjobs__stat_exists (a_dir, a_name, &s);                                   <*/
   DEBUG_YJOBS  yLOG_value   ("exists"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ownership)----------------------*/
   --rce;  if (s.st_uid != 0) {
      if (c_fix == 'y') rc = yjobs__file_fix (x_full, 'o', 0600, &s);
      if (s.st_uid != 0) {
         yURG_err ('f', "å%sæ is not owned by root (security risk)", a_name);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not owned by root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   DEBUG_YJOBS  yLOG_note    ("ownership is root (private)");
   --rce;  if (s.st_gid != 0) {
      if (c_fix == 'y') rc = yjobs__file_fix (x_full, 'g', 0600, &s);
      if (s.st_gid != 0) {
         yURG_err ('f', "å%sæ is not in root group (security risk)", a_name);
         DEBUG_YJOBS  yLOG_note    ("/var/spool/khronos not group of root (security risk)");
         DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   yURG_msg ('-', "å%sæ file owner and group are both root", a_name);
   DEBUG_YJOBS  yLOG_note    ("owner and group are both root (private)");
   /*---(permissions)--------------------*/
   x_perms = s.st_mode & 07777;
   DEBUG_YJOBS   yLOG_complex ("x_perms"   , "%04o", x_perms);
   --rce;  if  (x_perms != 0600)  {
      if (c_fix == 'y') rc = yjobs__file_fix (x_full, 'p', 0600, &s);
      x_perms = s.st_mode & 07777;
      if  (x_perms != 0600)  {
         yURG_err ('f', "å%sæ perms are %04o, not the requested %04o (security risk)", a_name, s.st_mode & 07777, 0600);
         DEBUG_YJOBS   yLOG_note    ("permissions not set correctly (private to user)");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
   }
   yURG_msg ('-', "å%sæ file permissions confirmed as %04o", a_name, 0600);
   DEBUG_YJOBS  yLOG_note    ("permissions are appropiate (private)");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}



/*====================------------------------------------====================*/
/*===----                        data accessor                         ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSOR________________o (void) {;};

char
yJOBS_filedata          (char *r_runas, char *r_mode, char *r_floc, char *r_fname, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_fdir, char *r_full)
{
   if (r_runas != NULL)  *r_runas  = myJOBS.m_runas;
   if (r_mode  != NULL)  *r_mode   = myJOBS.m_mode;
   if (r_floc  != NULL)  *r_floc   = myJOBS.f_loc;
   if (r_fname != NULL)  ystrlcpy (r_fname, myJOBS.f_file, LEN_DESC);
   if (r_fuser != NULL)  ystrlcpy (r_fuser, myJOBS.f_user, LEN_USER);
   if (r_fuid  != NULL)  *r_fuid   = myJOBS.f_uid;
   if (r_fdesc != NULL)  ystrlcpy (r_fdesc, myJOBS.f_desc, LEN_DESC);
   if (r_fdir  != NULL)  ystrlcpy (r_fdir , myJOBS.f_dir , LEN_PATH);
   if (r_full  != NULL)  ystrlcpy (r_full , myJOBS.f_full, LEN_PATH);
   return 0;
}

char
yjobs_file_secure       (char a_runas, char a_mode, char a_title [LEN_LABEL], char a_mark [LEN_TERSE], char a_fix [LEN_TERSE], char a_dir [LEN_DESC], char a_file [LEN_LABEL], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_fix       = YENV_NONE;
   char        x_msg       [LEN_HUND]  = "";
   char        x_secure    =  '-';
   char        x_loc       =  '-';
   /*---(quick-out)----------------------*/
   if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_sint    (a_mode);
      DEBUG_YJOBS   yLOG_snote   (g_act_aud);
      DEBUG_YJOBS   yLOG_snote   ("audit/fix not requested");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(non-duplication)----------------*/
   x_secure = ySCORE_value (myJOBS.m_yscore, a_mark);
   if (x_secure == 's') {
      DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
      DEBUG_YJOBS   yLOG_schar   (a_title);
      DEBUG_YJOBS   yLOG_snote   ("already secured");
      DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(score)--------------------------*/
   yURG_msg ('>', "audit %s existance and security...", a_title);
   /*---(quick-out with yURG)------------*/
   if (a_file == NULL || a_file [0] == '\0') {
      yURG_msg ('-', "skipping, not configured for %s", a_title);
      return RC_ACK;
   }
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, a_mark, G_SCORE_FAIL);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = YENV_FIX;
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   if (x_fix == YENV_FIX)  ySCORE_mark (myJOBS.m_yscore, a_fix, G_SCORE_SKIP);
   /*---(check file)---------------------*/
   if      (strstr (a_dir, "/etc/")   != NULL)  x_loc = 'c';
   else if (strstr (a_dir, "/spool/") != NULL)  x_loc = 'c';
   if (x_loc == 'c')  rc = yAUDIT_central (x_fix, a_dir, a_file, a_prefix, a_suffix, NULL, NULL, NULL);
   else               rc = yAUDIT_reg     (x_fix, YENV_STANDARD, a_dir, a_file, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      sprintf (x_msg, "%s is not proper and/or secure", a_title);
      yjobs_ends_failure (a_mode, "", x_msg);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(score)--------------------------*/
   ySCORE_mark (myJOBS.m_yscore, a_mark, 's');
   if (rc == RC_REPAIR)   ySCORE_mark (myJOBS.m_yscore, a_fix, 'f');
   yURG_msg ('-', "success, %s exists and security is appropriate", a_title);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char yjobs_db_secure         (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL])     { return yjobs_file_secure (a_runas, a_mode, "central database", "DSECURE", "DFIX" , a_hdir, a_db    , "", ""); }
char yjobs_world_secure      (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL])  { return yjobs_file_secure (a_runas, a_mode, "world file"      , "WSECURE", "WFIX" , a_hdir, a_world , "", ""); }
char yjobs_config_secure     (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_conf [LEN_LABEL], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE])   { return yjobs_file_secure (a_runas, a_mode, "shared configuration"  , "FFSEC"  , "FFFIX", a_cdir, a_conf, a_prefix, a_suffix); }
char yjobs_spool_secure      (char a_runas, char a_mode, char a_title [LEN_LABEL], char a_cdir [LEN_DESC], char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE])   { return yjobs_file_secure (a_runas, a_mode, a_title, "FFSEC"  , "FFFIX", a_cdir, a_file, a_prefix, a_suffix); }

char
yjobs_file_review       (char a_runas, char a_mode, char a_reason, int a_seq, char a_cdir [LEN_DESC], char a_file [LEN_PATH], char a_prefix [LEN_TERSE],  char a_suffix [LEN_TERSE], void *f_callback, char c_fail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    0;
   char        x_full      [LEN_PATH]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_prefix    [LEN_TERSE] = "";
   char        x_suffix    [LEN_TERSE] = "";
   char       *x_fatal     = "file review handled bad file/data";
   char        x_mark      [LEN_TERSE] = "";
   char        x_title     [LEN_LABEL] = "";
   char        x_loc       =  '-';
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_reason"  , a_reason);
   --rce;  switch (a_reason) {
   case '=' :  ystrlcpy (x_mark, "FLIST" , LEN_TERSE);  break;
   case 's' :  ystrlcpy (x_mark, "FFSEC" , LEN_TERSE);  break;
   case 'p' :  ystrlcpy (x_mark, "FONLY" , LEN_TERSE);  break;
   case 'a' :  ystrlcpy (x_mark, "FAUDIT", LEN_TERSE);  break;
   default  :
               ySCORE_mark (myJOBS.m_yscore, "FFSEC", G_SCORE_FAIL);
               sprintf (x_msg, "reason code (%d/%c) is illegal å=spaæ", a_reason, a_reason);
               yjobs_ends_failure (a_mode, x_msg, x_fatal);
               DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
   }
   ySCORE_mark (myJOBS.m_yscore, x_mark, G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);
   --rce;  if (a_cdir == NULL || a_cdir [0] == '\0') {
      yjobs_ends_failure (a_mode, "configuration directory name is NULL/empty", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);
   DEBUG_YJOBS   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yjobs_ends_failure (a_mode, "configuration file name is NULL/empty", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS   yLOG_point   ("f_callback", f_callback);
   --rce;  if (a_reason != '=' && a_reason != 's') {
      if (f_callback == NULL) {
         yjobs_ends_failure (a_mode, "host callback function is NULL", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_callback = f_callback;
   }
   /*---(prepare)------------------------*/
   if (a_prefix != NULL)  ystrlcpy (x_prefix, a_prefix, LEN_TERSE);
   if (a_suffix != NULL)  ystrlcpy (x_suffix, a_suffix, LEN_TERSE);
   if (strstr (a_cdir, "/spool/") != NULL) {
      sprintf (x_title, "spool file (%d)", a_seq);
      x_loc = 's';
   } else {
      sprintf (x_title, "shared configuration");
   }
   /*---(get full)-----------------------*/
   rc = yENV_name_full (a_cdir, a_file, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0)  {
      yjobs_ends_failure (a_mode, "full name could not be created", x_fatal);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(save-back)----------------------*/
   rc = yjobs_saveback (YJOBS_CENTRAL, "root", 0, "", a_file, a_cdir, x_full);
   /*---(list)---------------------------*/
   --rce;  if (a_reason == '=') {
      DEBUG_YJOBS   yLOG_note    ("handle as list");
      ySCORE_mark (myJOBS.m_yscore, x_mark, '=');
      if (!yJOBS_ifverbose ()) yURG_msg_live ();
      yURG_msg (':', "%s", x_full);
      if (!yJOBS_ifverbose ()) yURG_msg_mute ();
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
      /*---(done)---------------------------*/
   }
   /*---(secure)-------------------------*/
   --rce;  if (a_reason == 's') {
      DEBUG_YJOBS   yLOG_note    ("handle as security");
      if (x_loc == 's')  rc = yjobs_spool_secure   (a_runas, a_mode, x_title, a_cdir, a_file, x_prefix, x_suffix);
      else               rc = yjobs_config_secure  (a_runas, a_mode, a_cdir, a_file, x_prefix, x_suffix);
      DEBUG_YJOBS   yLOG_value   ("central"   , rc);
      --rce;  if (rc < 0)  {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ySCORE_mark (myJOBS.m_yscore, x_mark, 's');
      /*---(complete)-----------------------*/
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rc;
      /*---(done)---------------------------*/
   }
   /*---(pull)---------------------------*/
   --rce;  if (a_reason == 'p' || a_reason == 'a') {
      DEBUG_YJOBS   yLOG_note    ("handle as pull/audit");
      /*---(callback)-----------------------*/
      yURG_msg ('>', "read %s into environment (PULL)...", x_title);
      rc = x_callback (YJOBS_PULL , x_full);
      DEBUG_YJOBS   yLOG_value   ("pull"      , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "host read/pull ended with errors", x_fatal);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ySCORE_mark (myJOBS.m_yscore, x_mark, 'Ö');
      /*---(check for audit)----------------*/
      if (a_reason == 'a') {
         yURG_msg ('>', "audit-only, purge %s after reading (PURGE)...", x_title);
         DEBUG_YJOBS   yLOG_note    ("audit-only, purge file after read");
         rc = x_callback (YJOBS_PURGE, "");
         DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
         if (rc < 0) {
            yjobs_ends_failure (a_mode, "host read/pull ended with errors", x_fatal);
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         ySCORE_mark (myJOBS.m_yscore, x_mark, 'a');
      }
      /*---(complete)-----------------------*/
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
      /*---(done)---------------------------*/
   }
   /*---(trouble)------------------------*/
   --rce;
   DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}



