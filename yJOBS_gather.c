/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


char
yjobs_gather_full       (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_PATH], void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_fuser     [LEN_USER]  = "";
   int         x_fuid      =   -1;
   char        x_fdesc     [LEN_DESC]  = "";
   char        x_fdir      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_hdir      [LEN_PATH]  = "";
   char        x_update    =  '·';
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (strchr (g_running, a_mode) != NULL)  ystrlcpy (g_acts_score, g_acts_empty, LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, x_cdir, NULL, NULL, NULL, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for full database)------------*/
   rc = yjobs_who_location (a_runas, NULL, x_hdir, NULL, &x_update, x_db);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc <  0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_update == 'U' && strcmp (x_db, "") != 0)   {
      DEBUG_YJOBS   yLOG_note    ("option requires central database loaded before");
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central database did not load properly");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      g_fullacts  [20] = 'R';
   }
   /*---(gather all data)--------------------*/
   --rce;  if (strchr ("lL", a_runas) != NULL) {
      DEBUG_YJOBS   yLOG_note    ("option requires all files loaded before");
      rc = x_callback (YJOBS_GATHER, "");
      DEBUG_YJOBS   yLOG_value   ("gather"    , rc);
      --rce;  if (rc < 0) {
         yjobs_ends_failure (a_mode, "local contents not acceptable");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*> g_fullacts  [20] = 'R';                                                     <*/
   }
   /*---(show footer)--------------------*/
   if (strchr (g_running, a_mode) != NULL) {
      if (rc > 0)  yURG_err (' ', "");
      rc = yjobs_ends_success (a_mode);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char yjobs_gather            (void) { return yjobs_gather_full      (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

char
yjobs_world_full        (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar *a_file, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char      (*x_callback)   (cchar a_req, cchar *a_full);
   char        x_world     [LEN_DESC]  = "";
   char        x_db        [LEN_DESC]  = "";
   char        x_cwd       [LEN_PATH]  = "";
   char        x_path      [LEN_PATH]  = "";
   tWORLD     *x_curr      = NULL;
   int         c           =    0;
   char       *p           = NULL;
   /*---(quick-out)----------------------*/
   if (a_runas == IAM_HELIOS)  return 0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (g_fullacts , "·· ··· ··· ··· ··· ··· ··· ·· ··· ··", LEN_DESC);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_char    ("m_runas"   , a_runas);
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("e_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_callback = f_callback;
   /*---(show header)--------------------*/
   rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, NULL, NULL, x_world, x_db, x_cwd, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_fullacts  [1] = 'l';
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   /*---(load database)----------------------*/
   --rce;  if (strchr ("gêG", a_mode) != NULL && strcmp (x_db, "") != 0) {
      DEBUG_YJOBS   yLOG_note    ("option requires database loaded before");
      rc = x_callback (YJOBS_READ, "");
      DEBUG_YJOBS   yLOG_value   ("read db"   , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central database did not load properly");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   yURG_msg ('>', "import world file...");
   /*> rc = yjobs_world__import (a_runas, a_mode);                                    <*/
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   yURG_msg (' ', "");
   /*---(walk-through)-------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
   rc = yjobs_world__by_cursor (YDLST_HEAD, &x_curr);
   while (rc >= 0 && x_curr != NULL) {
      DEBUG_YJOBS   yLOG_point ("x_curr"   , x_curr);
      /*---(parse path/name)----------------*/
      DEBUG_YJOBS   yLOG_info  ("->path"    , x_curr->path);
      ystrlcpy (x_path, x_curr->path, LEN_PATH);
      p = strrchr (x_path, '/');
      if (p != NULL)  p [0] = '\0';
      DEBUG_YJOBS   yLOG_info  ("path"      , x_path);
      /*---(return to current)--------------*/
      rc = chdir (x_path);
      DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);
      if (rc <  0) {
         yURG_msg ('>', "read and verify current project (pre-PULL)");
         yURG_msg ('-', "current project path %2då%sæ", strlen (x_curr->path), x_curr->path);
         yURG_err ('w', "can not locate requested directory");
         yURG_msg (' ', "");
      } else {
         rc = x_callback (YJOBS_PULL, x_curr->path);
         DEBUG_YJOBS   yLOG_value   ("callback"  , rc);
      }
      IF_CONFIRM {
         yURG_msg_live ();
         if (rc >= 0)  yURG_msg     ('>', "%4d  %s", ++c, x_curr->path);
         else          yURG_msg     ('>', "%s%4d  %s%s", BOLD_RED, ++c, x_curr->path, BOLD_OFF);
         yURG_msg_mute ();
      }
      /*---(next)---------------------------*/
      rc = yjobs_world__by_cursor (YDLST_NEXT, &x_curr);
      /*---(done)---------------------------*/
   }
   /*---(write database)---------------------*/
   --rce;  if (strchr ("gêG", a_mode) != NULL && strcmp (x_db, "") != 0) {
      DEBUG_YJOBS   yLOG_note    ("option requires database saved after");
      rc = x_callback (YJOBS_WRITE, "");
      DEBUG_YJOBS   yLOG_value   ("write db"  , rc);
      if (rc < 0) {
         yjobs_ends_failure (a_mode, "central database could not save properly");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(return to current)--------------*/
   rc = chdir (x_cwd);
   DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(show footer)--------------------*/
   if (rc > 0)  yURG_err (' ', "");
   rc = yjobs_ends_success (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_world             (void) { return yjobs_world_full  (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

char
yJOBS_world_system       (char a_runas, char a_mode, void *a_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      [LEN_RECD]  = "";
   char       *p           = NULL;
   tWORLD     *x_world     = NULL;
   int         c           =    0;
   char      (*g_callback) (char *a_path);
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_callback", a_callback);
   --rce;  if (a_callback == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save present directory)---------*/
   p = getcwd (x_curr, LEN_RECD);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   /*> rc = yjobs_world__import (a_runas, a_mode);                                    <*/
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   /*---(walk-through)-------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
   rc = yjobs_world__by_cursor (YDLST_HEAD, &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_YJOBS   yLOG_point ("x_world"   , x_world);
      DEBUG_YJOBS   yLOG_info  ("->path"    , x_world->path);
      IF_VERBOSE   yURG_msg (' ', "");
      IF_CONFIRM  yURG_msg_live ();
      yURG_msg     (YURG_BASE, "%4d  %s", ++c, x_world->path);
      IF_CONFIRM  yURG_msg_mute ();
      /*---(return to current)--------------*/
      rc = g_callback (x_world->path);
      DEBUG_YJOBS   yLOG_value   ("callback"  , rc);
      IF_CONFIRM  yURG_msg_live ();
      if (rc >= 0)  yURG_msg     ('>', "%4d  %s", ++c, x_world->path);
      else          yURG_err     ('F', "%4d  %s", ++c, x_world->path);
      IF_CONFIRM  yURG_msg_mute ();
      /*---(next)---------------------------*/
      rc = yjobs_world__by_cursor (YDLST_NEXT, &x_world);
      /*---(done)---------------------------*/
   }
   /*---(return to current)--------------*/
   rc = chdir (x_curr);
   DEBUG_YJOBS   yLOG_value   ("chdir"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_gather       (char a_runas, char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_world     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(walk options)-------------------*/
   DEBUG_YJOBS  yLOG_char    ("a_mode"    , a_mode);
   --rce;  if (a_mode == 0 || strchr (g_gather, a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> x_act = yjobs_args__find (a_arg, &n, r_runas, &x_noise);                       <* 
    *> DEBUG_YJOBS  yLOG_char    ("x_act"     , x_act);                               <* 
    *> if (x_act == '?') {                                                            <* 
    *>    DEBUG_YJOBS  yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/


   /*---(get world file name)------------*/
   /*> rc = yjobs_who_location (a_runas, NULL, NULL, x_world, NULL, NULL);            <* 
    *> DEBUG_YJOBS   yLOG_value   ("location"  , rc);                                 <* 
    *> if (rc < 0) {                                                                  <* 
    *>    DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> if (strlen (x_world) == 0)  rc = yjobs_gather ();                              <* 
    *> else                        rc = yjobs_world  ();                              <*/


   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}
