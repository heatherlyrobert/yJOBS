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
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (strncmp (a_dir, "/tmp/", 5) != 0) {
      DEBUG_YJOBS   yLOG_note    ("can't mess  around outside /tmp");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   strlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YJOBS   yLOG_complex ("x_dir"     , "%2då%sæ", l, x_dir);
   /*---(stop recursion)-----------------*/
   if (l < 7)  {
      DEBUG_YJOBS   yLOG_note    ("too short");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(head execute)-------------------*/
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   yURG_rmdir (x_dir);
   /*---(peal next layer)----------------*/
   strlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   if  (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YJOBS   yLOG_complex ("r_dir"     , "%2då%sæ", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs__unit_rmdir_one (r_dir);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_info    ("a_dir"     , a_dir);
   --rce;  if (strncmp (a_dir, "/tmp/", 5) != 0) {
      DEBUG_YJOBS   yLOG_note    ("can't mess  around outside /tmp");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy to local)------------------*/
   strlcpy (x_dir, a_dir, LEN_DESC);
   l = strlen (x_dir);
   if (x_dir [l - 1] == '/')  x_dir [--l] = '\0';
   DEBUG_YJOBS   yLOG_complex ("x_dir"     , "%2då%sæ", l, x_dir);
   /*---(stop recursion)-----------------*/
   if (l < 7)  {
      DEBUG_YJOBS   yLOG_note    ("too short");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(peal next layer)----------------*/
   strlcpy (r_dir, x_dir, LEN_DESC);
   p = strrchr (r_dir, '/');
   DEBUG_YJOBS   yLOG_point   ("p"         , p);
   if  (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = '\0';
   l = strlen (r_dir);
   DEBUG_YJOBS   yLOG_complex ("r_dir"     , "%2då%sæ", l, r_dir);
   /*---(recurse)------------------------*/
   rc = yjobs__unit_mkdir_one (r_dir);
   DEBUG_YJOBS   yLOG_value   ("recursed"  , rc);
   /*---(tail execute)-------------------*/
   l = strlen (x_dir);
   DEBUG_YJOBS   yLOG_complex ("executing" , "%2då%sæ", l, x_dir);
   if      (strcmp (x_dir, "/tmp/spool") == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  yURG_mkdir (x_dir, "root", "root", "0755");
   else                                         yURG_mkdir (x_dir, "root", "root", "0700");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(remove all)---------------------*/
   for (i = 0;  i < MAX_WHO; ++i) {
      rc = yjobs_who_by_index (i, x_cdir, x_hdir, NULL, NULL);
      DEBUG_YJOBS   yLOG_complex ("index"     , "%2d å%sæ å%sæ", i, x_cdir, x_hdir);
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
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(create all)---------------------*/
   for (i = 0;  i < MAX_WHO; ++i) {
      rc = yjobs_who_by_index (i, x_cdir, x_hdir, NULL, NULL);
      DEBUG_YJOBS   yLOG_complex ("index"     , "%2d å%sæ å%sæ", i, x_cdir, x_hdir);
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
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
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
   --rce;  if (a_loc == YJOBS_CENTRAL)   rc = yjobs_central_old (a_runas, '-', a_name, &x_user, &x_uid, &x_desc, x_dir);
   else if    (a_loc == YJOBS_LOCAL  )   rc = yjobs_local_old   (a_runas, a_name, &x_user, &x_uid, &x_desc, x_dir);
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

char
yjobs_callback          (cchar a_req, cchar *a_data)
{
   switch (a_req) {
   case YJOBS_READ      :
      g_fullacts  [ 4] = 'Ô';
      break;
   case YJOBS_STATS     :
      g_fullacts  [15] = '#';
      break;
   case YJOBS_WRITE     :
      g_fullacts  [ 5] = 'Õ';
      break;
   case YJOBS_PULL      :
      g_fullacts  [ 9] = 'Ö';
      break;
   case YJOBS_CLEAR     :
      g_fullacts  [30] = '×';
      break;
   case YJOBS_LOCALRPT  :
      g_fullacts  [11] = 'ò';
      break;
   case YJOBS_REPORT    :
      g_fullacts  [17] = 'ó';
      break;
   case YJOBS_EXTRACT   :
      g_fullacts  [32] = 'e';
      break;
   case YJOBS_PURGE     :
      g_fullacts  [25] = 'P';
      break;
   }
   return 0;
}



char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_quiet       (void)
{
   yURG_err_none ();
   yURG_msg_none ();
   yjobs_runas ("khronos", NULL);
   yJOBS_rmdirs ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_loud        (void)
{
   yLOGS_begin   ("yJOBS", YLOG_SYS, YLOG_NOISE);
   yURG_by_name  ("yjobs", YURG_ON);
   yURG_err_none ();
   yURG_msg_none ();
   yjobs_runas ("khronos", NULL);
   yJOBS_rmdirs ();
   DEBUG_YJOBS  yLOG_info     ("yJOBS"     , yJOBS_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yjobs__unit_end         (void)
{
   yjobs_runas ("", NULL);
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
      snprintf (unit_answer, LEN_RECD, "yJOBS w_file     : %c  %-10p  %c  %2d  %2då%sæ",
            (myJOBS.w_file == NULL) ? '-' : 'y', myJOBS.w_file,
            x_exist, c, strlen (myJOBS.w_full), myJOBS.w_full);
   }
   else if (strcmp (a_question, "w_entry"   )     == 0) {
      yjobs_world__by_index (n, &u);
      if (u != NULL)   sprintf  (t, "%2då%sæ", strlen (u->path), u->path);
      else             sprintf  (t, "··åæ");
      snprintf (unit_answer, LEN_RECD, "yJOBS w_entry    : %2d  %s", n, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



