/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char
yjobs__unit_rmdir_one   (char *a_dir)
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
   --rce;  if (strncmp (a_dir, "/tmp/", 5) != 0) {
      DEBUG_YEXEC   yLOG_note    ("can't mess  around outside /tmp");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   strlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YEXEC   yLOG_complex ("x_dir"     , "%2d�%s�", l, x_dir);
   /*---(stop recursion)-----------------*/
   if (l < 7)  {
      DEBUG_YEXEC   yLOG_note    ("too short");
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(head execute)-------------------*/
   DEBUG_YEXEC   yLOG_complex ("executing" , "%2d�%s�", l, x_dir);
   yURG_rmdir (x_dir);
   /*---(peal next layer)----------------*/
   strlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YEXEC   yLOG_point   ("p"         , p);
   if  (p == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YEXEC   yLOG_complex ("r_dir"     , "%2d�%s�", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs__unit_rmdir_one (r_dir);
   DEBUG_YEXEC   yLOG_value   ("recursed"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs__unit_mkdir_one   (char *a_dir)
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
   --rce;  if (strncmp (a_dir, "/tmp/", 5) != 0) {
      DEBUG_YEXEC   yLOG_note    ("can't mess  around outside /tmp");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   strlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YEXEC   yLOG_complex ("x_dir"     , "%2d�%s�", l, x_dir);
   /*---(stop recursion)-----------------*/
   if (l < 7)  {
      DEBUG_YEXEC   yLOG_note    ("too short");
      DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   strlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YEXEC   yLOG_point   ("p"         , p);
   if  (p == NULL) {
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YEXEC   yLOG_complex ("r_dir"     , "%2d�%s�", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs__unit_mkdir_one (r_dir);
   DEBUG_YEXEC   yLOG_value   ("recursed"  , rc);
   /*---(tail execute)-------------------*/
   l = strlen (x_dir);
   DEBUG_YEXEC   yLOG_complex ("executing" , "%2d�%s�", l, x_dir);
   if      (strcmp (x_dir, "/tmp/spool") == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else                                         yURG_mkdir (x_dir, "root", "root", "0700");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_rmdirs            (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_hdir      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(remove all)---------------------*/
   for (i = 0;  i < MAX_WHO; ++i) {
      rc = yjobs_who_by_index (i, x_cdir, x_hdir, NULL, NULL);
      DEBUG_YEXEC   yLOG_complex ("index"     , "%2d �%s� �%s�", i, x_cdir, x_hdir);
      if (rc < 0)  break;
      yjobs__unit_rmdir_one (x_cdir);
      yjobs__unit_rmdir_one (x_hdir);
   }
   /*---(user accounts)------------------*/
   yURG_rmdir ("/tmp/root"         );
   yURG_rmdir ("/tmp/home/member"  );
   yURG_rmdir ("/tmp/home/machine" );
   yURG_rmdir ("/tmp/home/monkey"  );
   yURG_rmdir ("/tmp/home"         );
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_mkdirs            (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_hdir      [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YEXEC   yLOG_enter   (__FUNCTION__);
   /*---(create all)---------------------*/
   for (i = 0;  i < MAX_WHO; ++i) {
      rc = yjobs_who_by_index (i, x_cdir, x_hdir, NULL, NULL);
      DEBUG_YEXEC   yLOG_complex ("index"     , "%2d �%s� �%s�", i, x_cdir, x_hdir);
      if (rc < 0)  break;
      yjobs__unit_mkdir_one (x_cdir);
      yjobs__unit_mkdir_one (x_hdir);
   }
   /*---(user accounts)------------------*/
   yURG_mkdir ("/tmp/root"         , "root"   , "root"  , "0700");
   yURG_mkdir ("/tmp/home"         , "root"   , "root"  , "0755");
   yURG_mkdir ("/tmp/home/member"  , "member" , "users" , "0700");
   yURG_mkdir ("/tmp/home/machine" , "machine", "users" , "0700");
   yURG_mkdir ("/tmp/home/monkey"  , "monkey" , "users" , "0700");
   /*---(complete)-----------------------*/
   DEBUG_YEXEC   yLOG_exit    (__FUNCTION__);
   return 0;
}



char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_quiet       (void)
{
   yURG_err_none ();
   yURG_msg_none ();
   yJOBS_runas ("khronos", NULL);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_loud        (void)
{
   yLOGS_begin   ("yJOBS", YLOG_SYS, YLOG_NOISE);
   yURG_name     ("yjobs", YURG_ON);
   yURG_err_none ();
   yURG_msg_none ();
   yJOBS_runas ("khronos", NULL);
   DEBUG_YEXEC  yLOG_info     ("yJOBS"     , yJOBS_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yjobs__unit_end         (void)
{
   yJOBS_wrap    ();
   yLOGS_end     ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     unittest accessor                        ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSOR________________o (void) {;};

char*
yjobs__unit             (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_exist     =  '-';
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   tWORLD     *u           = NULL;
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "yJOBS            : question not understood", LEN_RECD);
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "w_count"   )     == 0) {
      snprintf (unit_answer, LEN_RECD, "yJOBS w_count    : %3dn", yjobs_world__count ());
   }
   else if (strcmp (a_question, "w_file"    )     == 0) {
      c = yURG_peek_count (myJOBS.w_full);
      if      (c  <  0)  x_exist = '-';
      else               x_exist = 'y';
      snprintf (unit_answer, LEN_RECD, "yJOBS w_file     : %c  %-10p  %c  %2d  %2d�%s�",
            (myJOBS.w_file == NULL) ? '-' : 'y', myJOBS.w_file,
            x_exist, c, strlen (myJOBS.w_full), myJOBS.w_full);
   }
   else if (strcmp (a_question, "w_entry"   )     == 0) {
      yjobs_world__by_index (n, &u);
      if (u != NULL)   sprintf  (t, "%2d�%s�", strlen (u->path), u->path);
      else             sprintf  (t, "����");
      snprintf (unit_answer, LEN_RECD, "yJOBS w_entry    : %2d  %s", n, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


