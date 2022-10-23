/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



static char (*s_assimilate) (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);



/*====================------------------------------------====================*/
/*===----                        local actions                         ----===*/
/*====================------------------------------------====================*/
static void      o___LOCAL___________________o (void) {;};

char
yJOBS_act_verify        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YEXEC  yLOG_info    ("allowed"   , IAM_VERIFY);
   --rce;  if (a_runas == 0 || strchr (IAM_VERIFY, a_runas) == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_assim"   , a_assimilate);
   --rce;  if (a_assimilate == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = a_assimilate;
   /*---(verify header)------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_VERIFY {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vverify, check details of local job/khronos file, but do not install");
      yURG_msg (' ', "");
   } else {
      DEBUG_YEXEC   yLOG_note    ("action requested is not a verify type, trouble");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify contents)--------------------*/
   rc = s_assimilate (a_runas, YJOBS_LOCAL, a_name, NULL, NULL);
   DEBUG_YEXEC   yLOG_value   ("assimilate", rc);
   --rce;  if (rc < 0) {
      if (a_act == ACT_CVERIFY )   yURG_msg_live ();
      if (a_act == ACT_CVERIFY )   yURG_msg ('>', "FAILED, local job/khronos file not installable, run --vverify to identify reasons");
      if (a_act == ACT_VVERIFY )   yURG_msg ('>', "FAILED, local job/khronos file not installable, the reasons are shown above");
      if (a_act == ACT_CVERIFY )   yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_act == ACT_CVERIFY )   yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, local job/khronos file installable, but installation not requested");
   if (a_act == ACT_CVERIFY )   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;

}

char       /* PURPOSE : install a local crontab file -------------------------*/
yjobs_act__intake       (cchar *a_name, cchar *a_new, cchar *a_central)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_new       [LEN_RECD]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(header)-------------------------*/
   yURG_msg ('>', "install file in central directory...");
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_new"     , a_new);
   --rce;  if (a_new        == NULL) {
      yURG_err ('f', "new job/khronos file name was null/empty");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_central" , a_central);
   --rce;  if (a_central    == NULL) {
      yURG_err ('f', "central directory name was null/empty");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make full new file name)------------*/
   snprintf (x_new, LEN_RECD, "%s%s", a_central, a_new);
   yURG_msg ('-', "central file name å%sæ", x_new);
   /*---(copy file)--------------------------*/
   snprintf (x_cmd, LEN_RECD, "cp -f %s %s > /dev/null  2>&1", a_name, x_new);
   DEBUG_YEXEC   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YEXEC   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not copy to å%sæ", a_central);
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      yURG_err ('f', "could not copy to å%sæ", a_central);
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "copied file to å%sæ", a_central);
   /*---(change ownership)-------------------*/
   snprintf (x_cmd, LEN_RECD, "chown root:root %s > /dev/null  2>&1", x_new);
   DEBUG_YEXEC   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YEXEC   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not change ownership to root");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      yURG_err ('f', "could not change ownership to root");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "changed owner and group to root");
   /*---(change permissions)-----------------*/
   snprintf (x_cmd, LEN_RECD, "chmod 0600 %s > /dev/null  2>&1", x_new);
   DEBUG_YEXEC   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YEXEC   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not change permissions to root-only write/read (0600)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_value   ("wifexited" , WIFEXITED(rc));
   if (WIFEXITED(rc) <  0) {
      yURG_err ('f', "could not change permissions to root-only write/read (0600)");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "changed permissions to root-only write/read (0600)");
   yURG_msg ('-', "SUCCESS, job/khronos file moved to central");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_act_install       (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_dir       [LEN_PATH]  = "";
   char        x_new       [LEN_PATH]  = "";
   char        x_user      [LEN_USER]  = "";
   char        x_desc      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YEXEC  yLOG_info    ("allowed"   , IAM_INSTALL);
   --rce;  if (a_runas == 0 || strchr (IAM_INSTALL, a_runas) == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_assim"   , a_assimilate);
   --rce;  if (a_assimilate == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = a_assimilate;
   /*---(install header)-----------------*/
   DEBUG_YEXEC  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_INSTALL {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vinstall, check details of local job/khronos file and install if clean");
      yURG_msg (' ', "");
   } else {
      DEBUG_YEXEC   yLOG_note    ("action requested is not an install type, trouble");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify contents)--------------------*/
   rc = s_assimilate (a_runas, YJOBS_LOCAL, a_name, x_user, x_desc);
   DEBUG_YEXEC   yLOG_value   ("assimilate", rc);
   --rce;  if (rc < 0) {
      if (a_act == ACT_CINSTALL)   yURG_msg_live ();
      if (a_act == ACT_CINSTALL)   yURG_msg ('>', "FAILED, local job/khronos file not installable, run --vinstall to identify reasons");
      if (a_act == ACT_VINSTALL)   yURG_msg ('>', "FAILED, local job/khronos file not installable, the reasons are shown above");
      if (a_act == ACT_CINSTALL)   yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(install file)-----------------------*/
   yJOBS_central_dir (a_runas, a_name, x_dir, x_user, x_new);
   DEBUG_YEXEC   yLOG_info    ("x_new"     , x_new);
   rc = yjobs_act__intake (a_name, x_new, x_dir);
   DEBUG_YEXEC   yLOG_value   ("intake"    , rc);
   --rce;  if (rc < 0) {
      if (a_act == ACT_CINSTALL)   yURG_msg_live ();
      if (a_act == ACT_CINSTALL)   yURG_msg ('>', "FAILED, local job/khronos file installable, but could not be, run --vinstall to identify reasons");
      if (a_act == ACT_VINSTALL)   yURG_msg ('>', "FAILED, local job/khronos file installable, but could not be, the reasons are shown above");
      if (a_act == ACT_CINSTALL)   yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_act == ACT_CINSTALL)   yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, local job/khronos file installed.  ready to use, restart, or --reload");
   if (a_act == ACT_CINSTALL)   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      central actions                         ----===*/
/*====================------------------------------------====================*/
static void      o___CENTRAL_________________o (void) {;};

char
yJOBS_act_check         (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YEXEC  yLOG_info    ("allowed"   , IAM_CHECK);
   --rce;  if (a_runas == 0 || strchr (IAM_CHECK, a_runas) == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_assim"   , a_assimilate);
   --rce;  if (a_assimilate == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = a_assimilate;
   /*---(verify)-------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_CHECK {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vcheck, check details of centrally installed job/khronos file");
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
      DEBUG_YEXEC   yLOG_note    ("action requested is not an check, audit, or daemon type, trouble");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg (' ', "");
   /*---(verify contents)--------------------*/
   rc = s_assimilate (a_runas, YJOBS_CENTRAL, a_name, NULL, NULL);
   DEBUG_YEXEC   yLOG_value   ("assimilate", rc);
   --rce;  if (rc < 0) {
      IF_VCENTRAL  yURG_msg ('>', "FAILED, centrally installed job/khronos file not runable, the reasons are shown above");
      IF_CCENTRAL  yURG_msg_live ();
      IF_CCHECK    yURG_msg ('>', "FAILED, centrally installed job/khronos file not runable, run --vcheck to identify reasons");
      /*> IF_CREVIEW   yURG_msg ('>', "%-30.30s  FAILED, job/khronos file not runable, run --vcheck to identify reasons", a_name);   <*/
      IF_CCENTRAL  yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   IF_VCENTRAL  yURG_msg ('>', "SUCCESS, centrally installed job/khronos file runable, all lines checked");
   IF_CCENTRAL  yURG_msg_live ();
   IF_CCHECK    yURG_msg ('>', "SUCCESS, centrally installed job/khronos file runable, all lines checked");
   IF_CCENTRAL  yURG_msg_mute ();
   /*---(footer)-------------------------*/
   if (a_act == ACT_VAUDIT || a_act == ACT_VDAEMON) {
      yURG_msg (' ', "");
      yURG_msg ('>', "COMPLETE %s ===================================", a_name);
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_dir       [LEN_PATH]  = "";
   char        x_old       [LEN_RECD]  = "";
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   DEBUG_YEXEC  yLOG_point   ("a_runas"   , a_runas);
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove header)------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_act"     , a_act);
   --rce;  IF_REMOVE {
      yURG_msg ('>', "%s", a_oneline);
      yURG_msg ('>', "  option --vremove, remove installed job/khronos file if found");
      yURG_msg (' ', "");
   } else {
      DEBUG_YEXEC   yLOG_note    ("action requested is not a remove type, trouble");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify contents)--------------------*/
   rc = yJOBS_central (a_runas, a_name, NULL, NULL, NULL, NULL);
   DEBUG_YEXEC   yLOG_value   ("central"   , rc);
   --rce;  if (rc < 0) {
      if (a_act == ACT_CREMOVE )   yURG_msg_live ();
      if (a_act == ACT_CREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not found/proper, run --vremove to identify reasons");
      if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not found/proper, the reasons are shown above");
      if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove physical)--------------------*/
   yJOBS_central_dir (a_runas, a_name, x_dir, "n/a", NULL);
   snprintf (x_old, LEN_RECD, "%s%s", x_dir, a_name);
   snprintf (x_cmd, LEN_RECD, "rm -f %s 2> /dev/null", x_old);
   DEBUG_YEXEC   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system   (x_cmd);
   DEBUG_YEXEC   yLOG_value   ("system"    , rc);
   DEBUG_YEXEC   yLOG_value   ("wifexited" , WIFEXITED(rc));
   --rce;  if (rc < 0 || WIFEXITED (rc) < 0) {
      if (a_act == ACT_CREMOVE )   yURG_msg_live ();
      if (a_act == ACT_CREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, run --vremove for reasons");
      if (a_act == ACT_VREMOVE )   yURG_msg ('>', "FAILED, installed job/khronos file not deleted, the reasons are shown above");
      if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_act == ACT_CREMOVE )   yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, installed job/khronos file uninstalled.  restart or --reload to retire");
   if (a_act == ACT_CREMOVE )   yURG_msg_mute ();
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       security audit                         ----===*/
/*====================------------------------------------====================*/
static void      o___SECURITY________________o (void) {;}

char
yjobs_act__fixdir       (char a_issue, tSTAT *s, char n, cchar *a_dir, int a_perms)
{
   char        rc          =    0;
   char        t           [LEN_TERSE] = "";
   sprintf (t, "%4o", a_perms);
   switch (a_issue) {
   case 'e' :
      DEBUG_YEXEC  yLOG_note    ("fixdir attempting create");
      yURG_msg ('+', "set to fix, directory does not exist, attempt to create");
      break;
   case 'o' :
      DEBUG_YEXEC  yLOG_note    ("fixdir attempting change owner");
      yURG_msg ('+', "set to fix, owner was not ¶root¶, attempt to change");
      break;
   case 'g' :
      DEBUG_YEXEC  yLOG_note    ("fixdir attempting change group");
      yURG_msg ('+', "set to fix, group was not ¶root¶, attempt to change");
      break;
   case 'p' :
      DEBUG_YEXEC  yLOG_note    ("fixdir attempting change permissions");
      yURG_msg ('+', "set to fix, permissions were not %s, attempt to change", t);
      break;
   }
   yURG_mkdir (a_dir, "root", "root", t);
   rc = lstat (a_dir, s);
   return rc;
}

char
yjobs_act_checkdir      (char n, cchar *a_dir, int a_perms, char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   int         x_perms     =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YEXEC   yLOG_value   ("n"         , n);
   DEBUG_YEXEC   yLOG_info    ("a_dir"     , a_dir);
   yURG_msg ('-', "checking level %d å%sæ", n, a_dir);
   /*---(check existance)----------------*/
   rc = lstat (a_dir, &s);
   DEBUG_YEXEC   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('o', &s, n, a_dir, a_perms);
      if (rc < 0) {
         yURG_err ('ü', "å%sæ directory does not exist (bad configuration)", a_dir);
         DEBUG_YEXEC   yLOG_note    ("can not open/stat directory");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (S_ISLNK (s.st_mode))  {
      yURG_err ('ü', "å%sæ actually refers to a symbolic link (security risk)", a_dir);
      DEBUG_YEXEC  yLOG_note    ("can not use a symlink");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISREG (s.st_mode))  {
      yURG_err ('ü', "å%sæ is a regular file, not a directory (bad configuration)", a_dir);
      DEBUG_YEXEC   yLOG_note    ("can not use a regular file");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISDIR (s.st_mode))  {
      yURG_err ('ü', "å%sæ is a specialty file (bad configuration)", a_dir);
      DEBUG_YEXEC   yLOG_note    ("can not use a specialty file");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('+', "å%sæ directory exists and is not a file/symlink", a_dir);
   /*---(ownership)----------------------*/
   --rce;  if (s.st_uid != 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('o', &s, n, a_dir, a_perms);
      if (s.st_uid != 0) {
         yURG_err ('ü', "å%sæ is not owned by root (security risk)", a_dir);
         DEBUG_YEXEC  yLOG_note    ("/var/spool/khronos not owned by root (security risk)");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YEXEC  yLOG_note    ("ownership is root (private)");
   --rce;  if (s.st_gid != 0) {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('g', &s, n, a_dir, a_perms);
      if (s.st_gid != 0) {
         yURG_err ('ü', "å%sæ is not root group (security risk)", a_dir);
         DEBUG_YEXEC  yLOG_note    ("/var/spool/khronos not group of root (security risk)");
         DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   yURG_msg ('+', "å%sæ directory owner and group are both root", a_dir);
   DEBUG_YEXEC  yLOG_note    ("owner and group are both root (private)");
   /*---(permissions)--------------------*/
   x_perms = s.st_mode & 07777;
   DEBUG_YEXEC   yLOG_complex ("x_perms"   , "%04o", x_perms);
   DEBUG_YEXEC   yLOG_complex ("a_perms"   , "%04o", a_perms);
   --rce;  if  (x_perms != a_perms)  {
      if (a_fix == 'y') rc = yjobs_act__fixdir ('p', &s, n, a_dir, a_perms);
      x_perms = s.st_mode & 07777;
      if  (x_perms != a_perms)  {
         yURG_err ('ü', "å%sæ perms are %04o, not the requested %04o (security risk)", a_dir, s.st_mode & 07777, a_perms);
         DEBUG_YEXEC   yLOG_note    ("permissions not set correctly (private to user)");
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   yURG_msg ('+', "å%sæ directory permissions confirmed as %04o", a_dir, a_perms);
   DEBUG_YEXEC  yLOG_note    ("permissions are appropiate (private)");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_directory     (char n, cchar *a_dir, cchar a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_dir       [LEN_DESC]  = "";
   char        r_dir       [LEN_DESC]  = "";
   char       *p           = NULL;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   strlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (l > 0 && x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YEXEC   yLOG_complex ("x_dir"     , "%2då%sæ", l, x_dir);
   /*---(stop recursion)-----------------*/
   --rce;  if (l == 0) {
      DEBUG_YEXEC   yLOG_note    ("bottomed out at root '/'");
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   strlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YEXEC   yLOG_point   ("p"         , p);
   if  (p != NULL)   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YEXEC   yLOG_complex ("r_dir"     , "%2då%sæ", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs_act_directory (n + 1, r_dir, a_fix);
   DEBUG_YEXEC   yLOG_value   ("recursed"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(tail execute)-------------------*/
   l = strlen (x_dir);
   DEBUG_YEXEC   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   rc = 0;
   if      (strcmp (x_dir, "/etc"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/lib"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/var/spool") == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/home"     ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp"      ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 01777, a_fix);
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/spool") == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  rc = yjobs_act_checkdir (n, x_dir, 0755 , a_fix);
   else                                         rc = yjobs_act_checkdir (n, x_dir, 0700 , a_fix);
   /*---(handle trouble)-----------------*/
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_act_security      (cchar a_runas, cchar a_act, cchar *a_oneline, char a_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(defense)-------------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify)-------------------------*/
   yURG_msg ('>', "%s", a_oneline);
   if (a_act == ACT_VAUDIT )  yURG_msg ('>', "  option --vaudit, check current central setup and security");
   if (a_act == ACT_VDAEMON)  yURG_msg ('>', "  option --vdaemon, verbosely launch in daemon mode");
   if (a_act == ACT_VPRICKLY) yURG_msg ('>', "  option --vprickly, verbosely launch in prickly daemon mode");
   if (a_act == ACT_VNORMAL)  yURG_msg ('>', "  option --vnormal, verbosely launch in normal mode");
   if (a_act == ACT_VSTRICT)  yURG_msg ('>', "  option --vstrict, verbosely launch in strict normal mode");
   yURG_msg (' ', "");
   yURG_msg ('>', "central directory setup/security...");
   /*---(defense)-------------------------------*/
   /*> rc = yJOBS_central_dir  (a_runas, NULL, x_orig, "n/", NULL);                   <*/
   rc = yjobs_who_location (a_runas, x_cdir, x_hdir, x_world, x_db);
   DEBUG_YEXEC   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check directories)---------------------*/
   DEBUG_YEXEC   yLOG_info    ("x_cdir"    , x_cdir);
   --rce;  if (strcmp (x_cdir, "") != 0) {
      rc = yjobs_act_directory (0, x_cdir, a_fix);
      if (rc <  0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YEXEC   yLOG_info    ("x_hdir"    , x_hdir);
   if (strcmp (x_hdir, "") != 0) {
      rc = yjobs_act_directory (0, x_hdir, a_fix);
      if (rc <  0) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)------------------------------*/
   yURG_msg ('-', "SUCCESS, central directory basic security measures confirmed");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yJOBS_security      (cchar *a_oneline) { return yjobs_act_security (g_runas, g_runmode, a_oneline, '-'); }
char yJOBS_fix           (cchar *a_oneline) { return yjobs_act_security (g_runas, g_runmode, a_oneline, 'y'); }



/*====================------------------------------------====================*/
/*===----                     review a directory                       ----===*/
/*====================------------------------------------====================*/
static void      o___REVIEW__________________o (void) {;}

char
yjobs_act__filter       (cchar *a_name, cchar *a_prefix, int a_muid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YEXEC   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || strlen (a_name) <= 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("a_name"    , a_name);
   /*---(just up/cur dirs)---------------*/
   if      (strcmp (a_name, "." ) == 0 || strcmp (a_name, "..") == 0) {
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(name quality)-------------------*/
   l = strlen (a_name);
   DEBUG_YEXEC   yLOG_value   ("l"         , l);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_name [i]) == NULL) {
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(hidden file)--------------------*/
   DEBUG_YEXEC   yLOG_char    ("first char", a_name [0]);
   --rce;  if (a_name [0] == '.') {
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(user prefix)--------------------*/
   if (a_muid != 0) {
      if (strncmp (a_name, a_prefix, strlen (a_prefix)) != 0) {
         DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs_act__prepare      (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, cchar *a_regex, char *a_prefix, char *a_dir, void *a_assimilate)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_dir       [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   DEBUG_YEXEC   yLOG_char    ("a_act"     , a_act);
   /*---(defaults)-----------------------*/
   if (a_prefix != NULL)  strcpy (a_prefix, "");
   if (a_dir    != NULL)  strcpy (a_dir   , "");
   /*---(defense)------------------------*/
   DEBUG_YEXEC  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline    == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_point   ("a_regex"   , a_regex);
   --rce;  if (a_regex == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("a_regex"   , a_regex);
   DEBUG_YEXEC   yLOG_point   ("a_muser"   , a_muser);
   --rce;  if (a_muser == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_point   ("a_prefix"  , a_prefix);
   --rce;  if (a_prefix == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC  yLOG_point   ("a_assim"   , a_assimilate);
   --rce;  if (a_assimilate == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_assimilate = a_assimilate;
   /*---(regex)--------------------------*/
   rc = yREGEX_comp (a_regex);
   DEBUG_YEXEC   yLOG_value   ("comp"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_note    ("could not compile search");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get directory)------------------*/
   rc = yJOBS_central_dir  (a_runas, NULL, a_dir, "n/a", NULL);
   DEBUG_YEXEC   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(user prefix)--------------------*/
   sprintf (a_prefix, "%s.", a_muser);
   /*---(check security)-----------------*/
   --rce;  switch (a_act) {
   case ACT_AUDIT      : case ACT_CAUDIT     : case ACT_VAUDIT     :
   case ACT_DAEMON     : case ACT_CDAEMON    : case ACT_VDAEMON    :
   case ACT_PRICKLY    : case ACT_CPRICKLY   : case ACT_VPRICKLY   :
   case ACT_NORMAL     : case ACT_CNORMAL    : case ACT_VNORMAL    :
      rc = yjobs_act_security (a_runas, a_act, a_oneline, '-');
      if (rc < 0) {
         IF_CREVIEW   yURG_msg_live ();
         IF_CREVIEW   yURG_msg ('-', "FAILED, central directory insecure, run --vaudit to identify reasons");
         IF_VREVIEW   yURG_msg ('-', "FAILED, central directory insecure, the reasons are shown above");
         IF_CREVIEW   yURG_msg_mute ();
         DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      } else {
         yURG_msg ('-', "SUCCESS, central directory basic security measures confirmed");
      }
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> review and act on global crontabs -------------------------*/
yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate)
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
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yjobs_act__prepare (a_runas, a_act, a_oneline, a_muser, a_regex, x_prefix, x_central, a_assimilate);
   DEBUG_YEXEC   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YEXEC   yLOG_info    ("x_central" , x_central);
   x_dir = opendir (x_central);
   DEBUG_YEXEC   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      /*> RUN_USER     printf ("fatal, can not open khronos central directory\n");    <*/
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk files)---------------------*/
   DEBUG_YEXEC   yLOG_note    ("walk through directory files");
   while ((x_file = readdir (x_dir)) != NULL) {
      /*---(simple filtering)-------------------*/
      rc = yjobs_act__filter (x_file->d_name, x_prefix, a_muid);
      if (rc != 0)  ++x_total;
      if (rc <= 0) {
         DEBUG_YEXEC   yLOG_note    ("not a valid job/khronos file");
         continue;
      }
      /*---(filter using regex)-----------------*/
      rc = yREGEX_filter (x_file->d_name);
      DEBUG_YEXEC   yLOG_value   ("exec"      , rc);
      if (rc <= 0) {
         DEBUG_YEXEC   yLOG_note    ("does not match regex, skipping");
         continue;
      }
      /*---(actions)----------------------------*/
      switch (a_act) {
      case ACT_LIST      :
         yURG_msg_live ();
         yURG_msg ('>', "%s", x_file->d_name);
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
      DEBUG_YEXEC   yLOG_complex ("counts"    , "%d total, %d count, %d pass", x_total, x_count, x_pass);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   DEBUG_YEXEC   yLOG_value   ("found"     , x_total);
   DEBUG_YEXEC   yLOG_value   ("processed" , x_count);
   DEBUG_YEXEC   yLOG_value   ("passed"    , x_pass);
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YEXEC   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(summary)------------------------*/
   rc = 1;
   --rce;  if (x_count <= 0) {
      DEBUG_YEXEC   yLOG_note    ("job/khronos count is zero");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but no job/khronos files found installed in central directory");
      IF_CREVIEW  yURG_msg_live ();
      IF_CREVIEW  yURG_msg ('>', "WARNING, secure, but no job/khronos files found installed in central directory");
      IF_CREVIEW  yURG_msg_mute ();
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   --rce;  if (x_count != x_pass) {
      DEBUG_YEXEC   yLOG_note    ("job/khronos count not equal passed");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);
      if (rc == 1) {
         IF_CREVIEW  yURG_msg_live ();
         IF_CREVIEW  yURG_msg ('>', "WARNING, secure, but not all job/khronos files passed, only %d of %d passed", x_pass, x_count);
         IF_CREVIEW  yURG_msg_mute ();
      }
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   --rce;  if (x_total != x_count) {
      DEBUG_YEXEC   yLOG_note    ("job/khronos count not equal to total files");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);
      if (rc == 1) {
         IF_CREVIEW  yURG_msg_live ();
         IF_CREVIEW  yURG_msg ('>', "WARNING, secure, but garbage non-job/khronos file(s) found, %d unknown of %d", x_total - x_count, x_total);
         IF_CREVIEW  yURG_msg_mute ();
      }
      rc = 0;
      IF_AUDIT    rc = rce;
      IF_PRICKLY  rc = rce;
   }
   IF_LIST   rc = 1;
   if (rc == 1) {
      DEBUG_YEXEC   yLOG_note    ("all results golden");
      yURG_msg (' ', "");
      IF_VREVIEW  yURG_msg ('>', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);
      IF_CREVIEW  yURG_msg_live ();
      IF_CREVIEW  yURG_msg ('>', "SUCCESS, environment and %d job/khronos file(s) passed all checks", x_pass);
      IF_CREVIEW  yURG_msg_mute ();
   }
   DEBUG_YEXEC   yLOG_value   ("x_count"   , x_count);
   if (rc >= 0) {
      if (x_count > 100) x_count = 100;
      rc = x_count;
   }
   DEBUG_YEXEC   yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_act__assim        (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_user      [LEN_USER]  = "";
   int         x_uid       =    0;
   char        x_desc      [LEN_DESC]  = "";
   char        x_dir       [LEN_PATH]  = "";
   /*---(default)------------------------*/
   if (r_user != NULL)  strlcpy (r_user, ""       , LEN_USER);
   if (r_desc != NULL)  strlcpy (r_desc, ""       , LEN_DESC);
   /*---(parse file)---------------------*/
   --rce;  if (a_loc == YJOBS_CENTRAL)   rc = yJOBS_central    (a_runas, a_name, &x_user, &x_uid, &x_desc, x_dir);
   else if    (a_loc == YJOBS_LOCAL  )   rc = yJOBS_acceptable (a_runas, a_name, &x_user, &x_uid, &x_desc, x_dir);
   else                                  return rce;
   --rce;  if (rc < 0)                   return rce;
   /*---(save back)----------------------*/
   if (r_user != NULL)  strlcpy (r_user, x_user, LEN_USER);
   if (r_desc != NULL)  strlcpy (r_desc, x_desc, LEN_DESC);
   /*---(trouble)------------------------*/
   if (strstr (a_name, "bad") != NULL)  return -10;
   /*---(complete)-----------------------*/
   return 0;
}



