/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char
yjobs__unit_environ     (char a_runas, char a_mode, char a_file [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_out       [LEN_HUND]  = "";
   char        n           =    0;
   char        f           =  '?';
   char        x_base      =  '-';
   /*---(clear all)----------------------*/
   yJOBS_reset (NULL, NULL, NULL);
   ySCORE_clear (myJOBS.m_yscore);
   /*---(runas)--------------------------*/
   --rce;  if (a_runas == 0)  return rce;
   ystrlcpy (x_out, yjobs_iam  (a_runas), LEN_HUND);
   --rce;  if (strcmp (x_out, "unknown") == 0)  return rce;
   myJOBS.m_runas = a_runas;
   ySCORE_mark (myJOBS.m_yscore, "RUNAS"    , G_SCORE_FAIL);
   ySCORE_mark (myJOBS.m_yscore, "ENV"      , '·');
   yjobs_args_data (myJOBS.m_runas, NULL, &x_base, NULL, NULL, NULL);
   if (x_base > 0 && x_base != '-')  {
      ySCORE_mark (myJOBS.m_yscore, "RUNAS"    , x_base);
      if (strchr (YSTR_UPPER, a_runas) != NULL)  ySCORE_mark (myJOBS.m_yscore, "ENV"      , 'u');
   }
   /*---(masking)------------------------*/
   yjobs_runas_masking (a_runas);
   /*---(mode)---------------------------*/
   --rce;  if (a_mode  == 0)  return rce;
   ystrlcpy (x_out, yjobs_mode (a_mode ), LEN_HUND);
   --rce;  if (strcmp (x_out, "unknown (unknown)") == 0)  return rce;
   myJOBS.m_mode  = a_mode;
   ySCORE_mark (myJOBS.m_yscore, "MODE"     , G_SCORE_FAIL);
   ySCORE_mark (myJOBS.m_yscore, "NOISE"    , '·');
   yjobs_args_data (a_mode, NULL, &x_base, NULL, NULL, NULL);
   if (x_base > 0 && x_base != '-')   ySCORE_mark (myJOBS.m_yscore, "MODE"     , x_base);
   /*---(set verbosity)------------------*/
   yURG_msg_tmp  (); 
   yURG_msg_mute (); 
   yURG_err_tmp  (); 
   yURG_err_mute (); 
   ySCORE_mark (myJOBS.m_yscore, "NOISE"    , '-');
   if (yJOBS_ifconfirm ()) {
      if (x_base > 0 && x_base != '-')  ySCORE_mark (myJOBS.m_yscore, "NOISE"    , 'c');
   }
   if (yJOBS_ifverbose ()) {
      if (x_base > 0 && x_base != '-')  ySCORE_mark (myJOBS.m_yscore, "NOISE"    , '!');
      yURG_msg_live ();
      yURG_err_live ();
   }
   /*---(file)---------------------------*/
   n = yjobs_args_offset (a_mode);
   --rce;  if (n < 0)  return rce;
   f = yjobs_who_action (a_runas, n);
   ySCORE_mark (myJOBS.m_yscore, "FILE"     , f);
   --rce;  if (f == '¢')  return rce;
   --rce;  if (f == '·')  return rce;
   --rce;  if (f == 'F' && a_file == NULL)  return rce;
   --rce;  if (f == 'F' && strcmp (a_file, "") == 0)  return rce;
   myJOBS.m_flag  = f;
   /*---(set file)-----------------------*/
   yjobs_who_location      (a_runas, myJOBS.m_dir, NULL, NULL, NULL, NULL);
   if (f == 'F' && a_file != NULL) {
      ystrlcpy (myJOBS.m_file, a_file, LEN_DESC);
   }
   sprintf (myJOBS.m_full, "%s%s", myJOBS.m_dir, myJOBS.m_file);
   /*---(complete)-----------------------*/
   return 0;
}

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
   char        x_cmd       [LEN_FULL]  = "";
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
   ystrlcpy (x_dir, a_dir, LEN_DESC);
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
   yENV_rmdir_fully (x_dir);
   /*---(peal next layer)----------------*/
   ystrlcpy (r_dir, x_dir, LEN_DESC);
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
   ystrlcpy (x_dir, a_dir, LEN_DESC);
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
   ystrlcpy (r_dir, x_dir, LEN_DESC);
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
   if      (strcmp (x_dir, "/tmp/spool") == 0)  yENV_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/lib"  ) == 0)  yENV_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/etc"  ) == 0)  yENV_mkdir (x_dir, "root", "root", "0755");
   else if (strcmp (x_dir, "/tmp/home" ) == 0)  yENV_mkdir (x_dir, "root", "root", "0755");
   else                                         yENV_mkdir (x_dir, "root", "root", "0700");
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
      rc = yjobs_who_by_index (i, x_cdir, NULL, x_hdir, NULL, NULL);
      DEBUG_YJOBS   yLOG_complex ("index"     , "%2d å%sæ å%sæ", i, x_cdir, x_hdir);
      if (rc < 0)  break;
      if (strcmp (x_cdir , "") != 0)  yjobs__unit_rmdir_one (x_cdir);
      if (strcmp (x_hdir , "") != 0)  yjobs__unit_rmdir_one (x_hdir);
   }
   /*---(user accounts)------------------*/
   yENV_rmdir_fully ("/tmp/root"                 );
   yENV_rmdir_fully ("/tmp/home/member/c_quani"  );
   yENV_rmdir_fully ("/tmp/home/member"          );
   yENV_rmdir_fully ("/tmp/home/machine"         );
   yENV_rmdir_fully ("/tmp/home/monkey"          );
   yENV_rmdir_fully ("/tmp/home"                 );
   yENV_rmdir_fully ("/tmp/spool"                );
   yENV_rmdir_fully ("/tmp/lib"                  );
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
      rc = yjobs_who_by_index (i, x_cdir, NULL, x_hdir, NULL, NULL);
      DEBUG_YJOBS   yLOG_complex ("index"     , "%2d å%sæ å%sæ", i, x_cdir, x_hdir);
      if (rc < 0)  break;
      yjobs__unit_mkdir_one (x_cdir);
      yjobs__unit_mkdir_one (x_hdir);
   }
   /*---(user accounts)------------------*/
   yENV_mkdir ("/tmp/root"                 , "root"   , "root"  , "0700");
   yENV_mkdir ("/tmp/home"                 , "root"   , "root"  , "0755");
   yENV_mkdir ("/tmp/home/member"          , "member" , "users" , "0700");
   yENV_mkdir ("/tmp/home/machine"         , "member" , "users" , "0700");
   yENV_mkdir ("/tmp/home/monkey"          , "member" , "users" , "0700");
   yENV_mkdir ("/tmp/home/member/c_quani"  , "member" , "users" , "0700");
   yENV_mkdir ("/tmp/spool"                , "root"   , "root"  , "0755");
   yENV_mkdir ("/tmp/lib"                  , "root"   , "root"  , "0755");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                                                       <* 
 *> yjobs_act__assim        (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc)                            <* 
 *> {                                                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                <* 
 *>    char        rce         =  -10;                                                                                         <* 
 *>    char        rc          =    0;                                                                                         <* 
 *>    char        x_user      [LEN_USER]  = "";                                                                               <* 
 *>    int         x_uid       =    0;                                                                                         <* 
 *>    char        x_desc      [LEN_DESC]  = "";                                                                               <* 
 *>    char        x_dir       [LEN_PATH]  = "";                                                                               <* 
 *>    /+---(default)------------------------+/                                                                                <* 
 *>    if (r_user != NULL)  ystrlcpy (r_user, ""       , LEN_USER);                                                            <* 
 *>    if (r_desc != NULL)  ystrlcpy (r_desc, ""       , LEN_DESC);                                                            <* 
 *>    /+---(parse file)---------------------+/                                                                                <* 
 *>    --rce;  if (a_loc == YJOBS_CENTRAL)   rc = yjobs_central_old (a_runas, '-', a_name, &x_user, &x_uid, &x_desc, x_dir);   <* 
 *>    else if    (a_loc == YJOBS_LOCAL  )   rc = yjobs_local_old   (a_runas, a_name, &x_user, &x_uid, &x_desc, x_dir);        <* 
 *>    else                                  return rce;                                                                       <* 
 *>    --rce;  if (rc < 0)                   return rce;                                                                       <* 
 *>    /+---(save back)----------------------+/                                                                                <* 
 *>    if (r_user != NULL)  ystrlcpy (r_user, x_user, LEN_USER);                                                               <* 
 *>    if (r_desc != NULL)  ystrlcpy (r_desc, x_desc, LEN_DESC);                                                               <* 
 *>    /+---(trouble)------------------------+/                                                                                <* 
 *>    if (strstr (a_name, "bad") != NULL)  return -10;                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                                <* 
 *>    return 0;                                                                                                               <* 
 *> }                                                                                                                          <*/

char
yjobs_callback          (cchar a_req, cchar *a_data)
{
   switch (a_req) {
   case YJOBS_READ      : case YJOBS_STATS     : case YJOBS_REPORT    : case YJOBS_PURGE     : case YJOBS_WRITE     :
      yURG_msg ('-', "skipping, host-based action (must string-test downstream)");
      return RC_POSITIVE;
      break;
   case YJOBS_PULL      :
      if (a_data == NULL)  return -1;
      yURG_msg ('-', "skipping, host-based action (must string-test downstream)");
      g_fullacts  [ 9] = 'Ö';
      return RC_POSITIVE;
      break;
   case ACT_REGISTER    :
      yURG_msg ('-', "skipping, over-riding detail for testing purposes");
      return RC_POSITIVE;
      break;
   case ACT_WITHDRAW    :
      yURG_msg ('>', "testing-stub to withdraw project from world file...");
      yURG_msg ('-', "skipping, over-riding detail for testing purposes");
      return RC_POSITIVE;
      break;
   case YJOBS_CLEAR     :
      /*> g_fullacts  [30] = '×';                                                     <*/
      yURG_msg ('>', "host-based clearing of select database contents (clear)...");
      if (strcmp (a_data, "(fail)") != 0) {
         yURG_msg ('-', "skipping, host-based action (must string-test downstream)");
         return RC_POSITIVE;
      } else {
         yURG_err ('w', "skipping, host-based action (but, simulating non-existant data)");
         return RC_WARNING;
      }
      return RC_POSITIVE;
      break;
   case YJOBS_LOCALRPT  :
      if (a_data == NULL)  return -1;
      yURG_msg ('-', "skipping, host-based action (must string-test downstream)");
      return RC_POSITIVE;
      break;
   case YJOBS_EXTRACT   :
      /*> g_fullacts  [32] = 'e';                                                     <*/
      return RC_POSITIVE;
      break;
   default           :
      return -1;
      break;
   }
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
      c = yENV_lines (myJOBS.w_full);
      if      (c  <  0)  x_exist = '-';
      else               x_exist = 'y';
      sprintf (t, "%-10.10p", myJOBS.w_file);
      snprintf (unit_answer, LEN_RECD, "yJOBS w_file     : %c  %-10.10s  %c  %2d  %2då%sæ",
            (myJOBS.w_file == NULL) ? '-' : 'y', t,
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



