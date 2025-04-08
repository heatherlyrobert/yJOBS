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
      rc = yENV_user_data  ('i', x_name, &(r_stat->st_uid), NULL, NULL, NULL);
      if (strcmp (x_name, "") == 0)  strcpy (x_name, "((unknown))");
      yURG_msg ('1', "owner is å%sæ not årootæ, attempting to change", x_name);
      break;
   case 'g' :
      DEBUG_YJOBS   yLOG_note    ("fixfile attempting change group");
      rc = yENV_group_data ('i', x_name, &(r_stat->st_gid));
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

char
yjobs_central_dirs      (cchar a_runas, cchar a_mode, cchar *a_file, cchar *a_user, char *r_cdir, char *r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char        t           [LEN_PATH]  = "";
   char        x_cdir      [LEN_DESC]  = "";
   char        x_central   =  '·';
   char        x_lpre      [LEN_LABEL] = "";
   char        x_cpre      [LEN_LABEL] = "";
   char        x_name      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (myJOBS.m_dir , "", LEN_PATH);
   if (r_cdir != NULL)  ystrlcpy (r_cdir , "", LEN_PATH);
   if (r_new  != NULL)  ystrlcpy (r_new  , "", LEN_DESC);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_point   ("r_cdir"    , r_cdir);
   --rce;  if (r_cdir  == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_schar   (a_runas);
   --rce;  if (strchr (g_valid, a_runas) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(directory)----------------------*/
   rc = yjobs_who_location      (a_runas, x_cdir, NULL, NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("location"  , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (myJOBS.m_dir , x_cdir, LEN_PATH);
   if (r_cdir != NULL)  ystrlcpy (r_cdir , x_cdir, LEN_PATH);
   /*---(check if file too)--------------*/
   if (r_new  == NULL) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(files)--------------------------*/
   rc = yjobs_who_naming (a_runas, NULL, &x_central, x_lpre, x_cpre, NULL, x_name);
   DEBUG_YJOBS  yLOG_value   ("naming"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("x_central" , x_central);
   --rce;  if (x_central != 'y') {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("x_lpre"    , x_lpre);
   DEBUG_YJOBS  yLOG_info    ("x_cpre"    , x_cpre);
   DEBUG_YJOBS  yLOG_info    ("x_name"    , x_name);
   /*---(fixed central name)-------------*/
   --rce;  if (strcmp (x_name, "") != 0) {
      DEBUG_YJOBS   yLOG_note    ("central name is specific and fixed");
      ystrlcpy (r_new , x_name, LEN_DESC);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(changable prefix)---------------*/
   --rce;  if (strcmp (x_cpre, "(USER).") == 0) {
      if (strchr (g_local, a_mode) != NULL) {
         DEBUG_YJOBS   yLOG_note    ("central prefix changes to user name");
         DEBUG_YJOBS   yLOG_info    ("a_file"    , a_file);
         p = strchr (a_file, '.');
         DEBUG_YJOBS   yLOG_point   ("p"         , p);
         if (p == NULL) {
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_YJOBS   yLOG_info    ("a_user"    , a_user);
         sprintf (r_new , "%s%s", a_user, p);
         DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(default)------------------------*/
   DEBUG_YJOBS   yLOG_note    ("name remains the same");
   strcpy (r_new , a_file);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
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

/*> char                                                                                                             <* 
 *> yjobs__maint_config     (char a_runas, char a_mode, char a_cdir [LEN_DESC], void *f_callback, char c_hardfail)   <* 
 *> {                                                                                                                <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                      <* 
 *>    char        rce         =  -10;                                                                               <* 
 *>    int         rc          =    0;                                                                               <* 
 *>    char        rc_final    =    1;                                                                               <* 
 *>    char        x_fix       =  '-';                                                                               <* 
 *>    char        x_etc       =  '-';                                                                               <* 
 *>    char      (*x_callback)   (cchar a_req, cchar *a_full);                                                       <* 
 *>    /+---(quick-out)----------------------+/                                                                      <* 
 *>    if (a_mode == 0 || strchr (g_act_aud, a_mode) == NULL) {                                                      <* 
 *>       DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);                                                                 <* 
 *>       DEBUG_YJOBS   yLOG_sint    (a_mode);                                                                       <* 
 *>       DEBUG_YJOBS   yLOG_snote   (g_act_aud);                                                                    <* 
 *>       DEBUG_YJOBS   yLOG_snote   ("configuration audit/fix not requested");                                      <* 
 *>       DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);                                                                 <* 
 *>       return 0;                                                                                                  <* 
 *>    }                                                                                                             <* 
 *>    /+---(header)-------------------------+/                                                                      <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                                                    <* 
 *>    /+---(title)---------------------------------+/                                                               <* 
 *>    yURG_msg ('>', "configuration directory setup/security review...");                                           <* 
 *>    DEBUG_YJOBS   yLOG_char    ("c_hardfail", c_hardfail);                                                        <* 
 *>    /+---(defense)------------------------+/                                                                      <* 
 *>    DEBUG_YJOBS   yLOG_point   ("a_cdir"    , a_cdir);                                                            <* 
 *>    --rce;  if (a_cdir  == NULL) {                                                                                <* 
 *>       yjobs_ends_failure (a_mode, "configuration directory is null");                                            <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                            <* 
 *>       return rce;                                                                                                <* 
 *>    }                                                                                                             <* 
 *>    DEBUG_YJOBS   yLOG_info    ("a_cdir"    , a_cdir);                                                            <* 
 *>    --rce;  if (strcmp (a_cdir, "") == 0) {                                                                       <* 
 *>       yURG_msg ('-', "skipping, no configuration directory specified for application");                          <* 
 *>       DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                 <* 
 *>       return 0;                                                                                                  <* 
 *>    }                                                                                                             <* 
 *>    /+---(set fix)-------------------------------+/                                                               <* 
 *>    if (strchr (g_fix, a_mode) != NULL)       x_fix = 'f';                                                        <* 
 *>    DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);                                                             <* 
 *>    if (a_cdir != NULL && strstr  (a_cdir, "/etc/") != NULL)    x_etc = 'y';                                      <* 
 *>    DEBUG_YJOBS   yLOG_char    ("x_etc"     , x_etc);                                                             <* 
 *>    /+---(check files)---------------------------+/                                                               <* 
 *>    rc = yjobs_dir_review (__FUNCTION__, 'm', a_runas, a_mode, f_callback, x_fix, '-');                           <* 
 *>    DEBUG_YJOBS   yLOG_value   ("files"     , rc);                                                                <* 
 *>    if (rc <  0) {                                                                                                <* 
 *>       if (a_mode != '=') {                                                                                       <* 
 *>          /+> if (x_etc == 'y')  rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, G_SCORE_FAIL);   <+/            <* 
 *>          /+> else               rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  3, G_SCORE_FAIL);   <+/            <* 
 *>       } else {                                                                                                   <* 
 *>          /+> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  5, G_SCORE_FAIL);          <+/                        <* 
 *>       }                                                                                                          <* 
 *>       if (c_hardfail == 'y') {                                                                                   <* 
 *>          DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                                                         <* 
 *>          return rce;                                                                                             <* 
 *>       }                                                                                                          <* 
 *>    }                                                                                                             <* 
 *>    if (rc > rc_final)  rc_final = rc;                                                                            <* 
 *>    /+---(score end)----------------------+/                                                                      <* 
 *>    if (x_etc == 'y') {                                                                                           <* 
 *>       DEBUG_YJOBS   yLOG_note    ("retain data from /etc/ config file");                                         <* 
 *>       /+> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  2, 'Ö');                      <+/                        <* 
 *>    } else {                                                                                                      <* 
 *>       if (a_mode != 0 && strchr (g_act_kep, a_mode) != NULL) {                                                   <* 
 *>          DEBUG_YJOBS   yLOG_note    ("retain data from all file pulls");                                         <* 
 *>          /+> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  3, 'R');                   <+/                        <* 
 *>       } else if (x_etc != 'y') {                                                                                 <* 
 *>          DEBUG_YJOBS   yLOG_note    ("purge each file pulled");                                                  <* 
 *>          /+> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  3, 'r');                   <+/                        <* 
 *>       }                                                                                                          <* 
 *>    }                                                                                                             <* 
 *>    if (a_mode == '=') {                                                                                          <* 
 *>       /+> rc = yjobs_ends_score_OLD (G_SCORE_CENTRAL ,  5, '=');                      <+/                        <* 
 *>    }                                                                                                             <* 
 *>    DEBUG_YJOBS   yLOG_value   ("score"     , rc);                                                                <* 
 *>    /+---(complete)-----------------------+/                                                                      <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                                                    <* 
 *>    return rc_final;                                                                                              <* 
 *> }                                                                                                                <*/

char
yjobs_file_secure       (char a_runas, char a_mode, char a_title [LEN_LABEL], char a_mark [LEN_TERSE], char a_fix [LEN_TERSE], char a_dir [LEN_DESC], char a_file [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_fix       = YENV_NONE;
   char        x_msg       [LEN_HUND]  = "";
   char        x_secure    =  '-';
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
   x_secure = yENV_score_value (a_mark);
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
   yURG_msg ('>', "audit existance and security of %s...", a_title);
   yENV_score_mark (a_mark, G_SCORE_FAIL);
   /*---(set fix)-------------------------------*/
   if (strchr (g_fix, a_mode) != NULL)       x_fix = YENV_FIX;
   DEBUG_YJOBS   yLOG_char    ("x_fix"     , x_fix);
   if (x_fix == YENV_FIX)  yENV_score_mark (a_fix, G_SCORE_SKIP);
   /*---(audit databasee)----------------*/
   rc = yENV_audit_reg (x_fix, YENV_NORMAL, a_dir, a_file, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      sprintf (x_msg, "%s is not proper and/or secure", a_title);
      yjobs_ends_failure (a_mode, "", x_msg);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(score)--------------------------*/
   yENV_score_mark (a_mark, 's');
   if (rc == RC_REPAIR)   yENV_score_mark (a_fix, 'f');
   yURG_msg ('-', "success, %s exists and security is appropriate", a_title);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char yjobs_db_secure         (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_db [LEN_LABEL])     { return yjobs_file_secure (a_runas, a_mode, "central database", "DSECURE", "DFIX" , a_hdir, a_db); }
char yjobs_world_secure      (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL])  { return yjobs_file_secure (a_runas, a_mode, "world file"      , "WSECURE", "WFIX" , a_hdir, a_world); }
char yjobs_config_secure     (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_config [LEN_LABEL]) { return yjobs_file_secure (a_runas, a_mode, "central config"  , "FFSEC"  , "FFFIX", a_cdir, a_config); }


