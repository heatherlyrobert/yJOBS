/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"

/*
 * METIS § ga4·· § modify world to call gather directly if no world file                  § N9N747 §  · §
 *
 *
 *
 *
 *
 */

#define     B_WORLD     'w'
char   g_print       [LEN_RECD]  = "";



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yjobs_world_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_WORLD, "world");
   DEBUG_YJOBS   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(global defaults)----------------*/
   /*> ystrlcpy (myJOBS.w_name  , "", LEN_LABEL);                                     <*/
   /*> ystrlcpy (myJOBS.w_full  , "", LEN_PATH);                                      <*/
   /*> myJOBS.w_file   = NULL;                                                        <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
yjobs_world__new        (tWORLD **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tWORLD     *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YJOBS   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_spoint  (*a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_new = NULL;
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tWORLD *) malloc (sizeof (tWORLD));
      if (x_tries > 3)   break;
   }
   DEBUG_YJOBS   yLOG_sint    (x_tries);
   DEBUG_YJOBS   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   x_new->path [0]    = '\0';
   x_new->btree       = NULL;
   /*---(save return)--------------------*/
   *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yjobs_world__free       (tWORLD **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YJOBS   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_YJOBS   yLOG_snote   ("never set");
      DEBUG_YJOBS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and return)---------------*/
   free (*a_old);
   *a_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       add and remove                         ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
yjobs_world__add        (char *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tWORLD     *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_path"    , a_path);
   l = strlen (a_path);
   DEBUG_YJOBS   yLOG_value   ("l"         , l);
   --rce;  if (l <= 3) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for duplicate)------------*/
   rc = yjobs_world__by_path (a_path, &x_new);
   DEBUG_YJOBS   yLOG_point   ("by_name"   , x_new);
   --rce;  if (x_new != NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create function)----------------*/
   rc = yjobs_world__new (&x_new);
   DEBUG_YJOBS   yLOG_point   ("x_new"     , x_new);
   --rce;  if (rc < 0 || x_new == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   ystrlcpy (x_new->path, a_path, LEN_PATH);
   /*---(into btree)---------------------*/
   rc = ySORT_hook (B_WORLD, x_new, x_new->path, &x_new->btree);
   DEBUG_YJOBS   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare functions)--------------*/
   DEBUG_YJOBS   yLOG_note    ("prepare btree");
   rc = ySORT_prepare  (B_WORLD);
   DEBUG_YJOBS   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__remove     (char *a_path)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_path"    , a_path);
   /*---(find)---------------------------*/
   rc = yjobs_world__by_path (a_path, &x_old);
   DEBUG_YJOBS   yLOG_value   ("by_path"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = ySORT_unhook (&(x_old->btree));
   DEBUG_YJOBS   yLOG_value   ("un-btree"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   rc = yjobs_world__free (&x_old);
   DEBUG_YJOBS   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare functions)--------------*/
   DEBUG_YJOBS   yLOG_note    ("prepare btree");
   rc = ySORT_prepare  (B_WORLD);
   DEBUG_YJOBS   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   c = yjobs_world__count ();
   DEBUG_YJOBS   yLOG_value   ("count"     , c);
   if (c == 0) {
      yURG_msg ('-', "clearing registry, no entries exist, nothing to do");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   rc = yjobs_world__by_cursor (YDLST_HEAD, &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_YJOBS   yLOG_point ("x_world"   , x_world);
      DEBUG_YJOBS   yLOG_info  ("->path"    , x_world->path);
      rc = yjobs_world__remove (x_world->path);
      rc = yjobs_world__by_cursor (YDLST_HEAD, &x_world);
   }
   /*---(check)--------------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
   --rce;  if (yjobs_world__count () > 0) {
      yURG_msg ('f', "clearing registry failed, %d entries remain", yjobs_world__count ());
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "clearing registry, %d entries purged from memory", c);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           searching                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yjobs_world__count        (void)                            { return ySORT_count     (B_WORLD); }
char yjobs_world__by_path      (uchar *a_path, tWORLD **r_world) { return ySORT_by_name   (B_WORLD, a_path, r_world); }
char yjobs_world__by_index     (int n, tWORLD **r_world)         { return ySORT_by_index  (B_WORLD, n, r_world); }
char yjobs_world__by_cursor    (char a_dir, tWORLD **r_world)    { return ySORT_by_cursor (B_WORLD, a_dir, r_world); }



/*====================------------------------------------====================*/
/*===----                       export/import                          ----===*/
/*====================------------------------------------====================*/
static void  o___EXIM____________o () { return; }

char
yjobs_world__read       (FILE *f, int *b_line, char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   /*---(begin)----------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_recd != NULL)  strlcpy (r_recd, "", LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("w_file"    , f);
   --rce;  if (f == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_point   ("r_recd"    , r_recd);
   --rce;  if (r_recd == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find a record)------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      fgets (r_recd, LEN_RECD, f);
      if (feof (f)) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return RC_ACK;
      }
      if (b_line != NULL) {
         ++(*b_line);
         DEBUG_YJOBS   yLOG_value   ("b_line"    , b_line);
      }
      DEBUG_YJOBS   yLOG_info    ("r_recd"    , r_recd);
      /*---(filter)----------------------*/
      if (r_recd [0] == '\0')  continue;
      if (r_recd [0] == '#')   continue;
      if (r_recd [0] == ' ')   continue;
      /*---(clean-up)--------------------*/
      ystrltrim (r_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (r_recd);
      DEBUG_YJOBS   yLOG_value   ("x_len"     , x_len);
      if (x_len <  5)          continue;
      if (r_recd [x_len - 1] == '\n')  r_recd [--x_len] = '\0';
      DEBUG_YJOBS   yLOG_info    ("final"     , r_recd);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_world__import     (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         x_line      =    0;
   char        x_curr      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WREAD  ] = G_SCORE_FAIL;
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   rc = yENV_open_full ("world file", a_hdir, a_world, 'r', NULL, NULL, NULL, &f);
   DEBUG_YJOBS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      rc = yjobs_world__read (f, &x_line, x_curr);
      DEBUG_YJOBS   yLOG_value   ("read"      , rc);
      if (rc <  0) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
      if (rc == RC_ACK) {
         DEBUG_YJOBS   yLOG_note    ("end of file");
         break;
      }
      /*---(save)------------------------*/
      rc = yjobs_world__add (x_curr);
      DEBUG_YJOBS   yLOG_value   ("add"       , rc);
      if (rc < 0) {
         yURG_msg ('F', "import failed on %d entry", x_line);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
      /*---(done)------------------------*/
   }
   /*---(note)---------------------------*/
   yURG_msg ('-', "imported %d entries from world registry (%d lines in file)", yjobs_world__count (), x_line);
   /*---(close)--------------------------*/
   rc = yENV_close_full ("world file", &f, '-');
   DEBUG_YJOBS   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WREAD  ] = 'Ô';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_world__export     (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   tWORLD     *x_world     = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WWRITE ] = G_SCORE_FAIL;
   /*---(open)---------------------------*/
   rc = yENV_open_full ("world file", a_hdir, a_world, 'w', NULL, NULL, NULL, &f);
   DEBUG_YJOBS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(title)--------------------------*/
   fprintf (f, "## world registry file\n\n");
   /*---(walk-through)-------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
   rc = yjobs_world__by_cursor (YDLST_HEAD, &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_YJOBS   yLOG_info  ("->path"    , x_world->path);
      fprintf (f, "%s\n", x_world->path);
      rc = yjobs_world__by_cursor (YDLST_NEXT, &x_world);
   }
   /*---(footer)-------------------------*/
   fprintf (f, "\n## end-of-file with %d records\n", yjobs_world__count ());
   /*---(note)---------------------------*/
   yURG_msg ('-', "exported %d entries to world registry (%d lines in file)", yjobs_world__count (), yjobs_world__count () + 4);
   /*---(close)--------------------------*/
   rc = yENV_close_full ("world file", &f, '-');
   DEBUG_YJOBS   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WWRITE ] = 'Õ';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                    foreach actions                           ----===*/
/*====================------------------------------------====================*/
static void  o___FOREACH_________o () { return; }

char
yjobs_world__foreach    (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   tWORLD     *x_world     = NULL;
   char        x_type      =  '-';
   char        x_entry     [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   int         n           =    0;
   int         x_bads      =    0;
   int         x_fails     =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(score)--------------------------*/
   g_acts_score  [G_SCORE_WAUDIT ] = G_SCORE_FAIL;
   /*---(mute)---------------------------*/
   switch (a_mode) {
   case CASE_LIST :   yURG_all_mute ();   break;
   }
   /*---(audit world file)---------------*/
   yURG_msg ('>', "audit existance and security of world file...");
   /*---(audit world file)---------------*/
   rc = yENV_audit_reg ('-', 'n', a_hdir, a_world, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "world file is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   yURG_msg ('-', "success, world file exists and security is appropriate");
   /*---(import)-------------------------*/
   yURG_msg ('>', "import the world file...");
   rc = yjobs_world__import (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   yURG_msg ('-', "success, world file imported");
   /*---(muting)-------------------------*/
   switch (a_mode) {
   case CASE_LIST :   yURG_all_live ();   break;
   }
   /*---(run list)-----------------------*/
   yjobs_world__by_cursor  (YDLST_HEAD, &x_world);
   while  (x_world != NULL) {
      ++n;
      switch (a_mode) {
      case CASE_LIST  :
         yURG_msg (' ', "%s", x_world->path);
         break;
      case CASE_AUDIT :
         strlcpy (x_entry, x_world->path, LEN_PATH);
         l = strlen (x_entry);
         yURG_msg ('>', "%d) verify world entry...", n);
         x_type = yENV_exists (x_entry);
         DEBUG_YJOBS   yLOG_complex ("exists"    , "%d/%c", x_type, x_type);
         if (x_type == YENV_DIR) {
            if (x_entry [l - 1] != '/') {
               strlcat (x_entry, '/', LEN_PATH);
               ++l;
            }
         } else if (x_type != YENV_REG && x_type != YENV_HARD) {
            if (x_entry [l - 1] == '/')  x_type = YENV_DIR;
            else                         x_type = YENV_REG;
         }
         /*---(parse)--------------------------*/
         rc = yENV_name_split (x_entry, NULL, x_dir, x_file);
         if (rc > rc_final)  rc_final = rc;
         DEBUG_YJOBS   yLOG_value   ("split"     , rc);
         --rce;  if (rc < 0) {
            rc_final = RC_FAILED;
            ++x_fails;
            break;
         }
         /*---(audit entry)--------------------*/
         rc = yENV_audit (x_type, '-', 'n', x_dir, x_file, "-", "-", "-", -1, -1, '-', "");
         if (rc > rc_final)  rc_final = rc;
         DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
         --rce;  if (rc < 0) {
            rc_final = RC_FAILED;
            ++x_fails;
            break;
         }
         yURG_msg ('-', "success, entry exists and is appropriate");
         break;
      }
      yjobs_world__by_cursor  (YDLST_NEXT, &x_world);
   }
   /*---(mute)---------------------------*/
   switch (a_mode) {
   case CASE_LIST :   yURG_all_mute ();   break;
   }
   /*---(score)--------------------------*/
   if (rc_final == RC_POSITIVE)   g_acts_score  [G_SCORE_WAUDIT ] = 'a';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char yjobs_world_list        (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL]) { return yjobs_world__foreach (a_runas, a_mode, a_hdir, a_world); }
char yjobs_world_audit       (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL]) { return yjobs_world__foreach (a_runas, a_mode, a_hdir, a_world); }



/*====================------------------------------------====================*/
/*===----                    main drivers                              ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }

char
yjobs_world__prepare    (char a_runas, char a_mode, char a_entry [LEN_PATH], char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_entry     [LEN_PATH]  = "";
   int         l           =    0;
   char        x_type      =  '-';
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(audit world file)---------------*/
   yURG_msg ('>', "audit existance and security of world file...");
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WAUDIT ] = G_SCORE_FAIL;
   /*---(audit world file)---------------*/
   rc = yENV_audit_reg ('-', 'n', a_hdir, a_world, "root", "root", "f_tight");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "world file is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WAUDIT ] = 's';
   yURG_msg ('-', "success, world file exists and security is appropriate");
   /*---(prepare for action)-------------*/
   yURG_msg ('>', "confirm and audit requested entry...");
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WENTRY ] = G_SCORE_FAIL;
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_entry"   , a_entry);
   --rce;  if (a_entry == NULL) {
      yURG_err ('f', "entry requested is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YJOBS   yLOG_info    ("a_entry"   , a_entry);
   --rce;  if (a_entry [0] == '\0') {
      yURG_err ('f', "entry requested is empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (x_entry, a_entry, LEN_PATH);
   l = strlen (x_entry);
   /*---(ckeck for entry)----------------*/
   x_type = yENV_exists (x_entry);
   DEBUG_YJOBS   yLOG_complex ("exists"    , "%d/%c", x_type, x_type);
   if (x_type == YENV_DIR) {
      if (x_entry [l - 1] != '/') {
         strlcat (x_entry, '/', LEN_PATH);
         ++l;
      }
   } else if (x_type != YENV_REG && x_type != YENV_HARD) {
      if (x_entry [l - 1] == '/')  x_type = YENV_DIR;
      else                         x_type = YENV_REG;
   }
   /*---(parse)--------------------------*/
   rc = yENV_name_split (x_entry, NULL, x_dir, x_file);
   DEBUG_YJOBS   yLOG_value   ("split"     , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "entry name could not be split");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(audit entry)--------------------*/
   rc = yENV_audit (x_type, '-', 'n', x_dir, x_file, "-", "-", "-", -1, -1, '-', "");
   DEBUG_YJOBS   yLOG_value   ("audit"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "entry is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(mark)---------------------------*/
   if (x_type == YENV_DIR)   g_acts_score  [G_SCORE_WENTRY ] = 'd';
   else                      g_acts_score  [G_SCORE_WENTRY ] = 'f';
   yURG_msg ('-', "success, entry exists and is appropriate");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_world_register    (char a_runas, char a_mode, char a_entry [LEN_PATH], char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_entry     [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(audit world file)---------------*/
   rc = yjobs_world__prepare (a_runas, a_mode, a_entry, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "entry is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for action)-------------*/
   yURG_msg ('>', "register entry in world file...");
   /*---(import)-------------------------*/
   rc = yjobs_world__import     (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (a_entry, &x_world);
   if (x_world != NULL) {
      yURG_err ('w', "entry already exists in registry, nothing to do");
      g_acts_score  [G_SCORE_WUPDATE] = 'D';
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WUPDATE] = G_SCORE_FAIL;
   /*---(add new one)--------------------*/
   rc = yjobs_world__add    (a_entry);
   --rce;  if (rc < 0) {
      yURG_err ('f', "entry could not be added");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WUPDATE] = 'r';
   yURG_msg ('-', "entry is NEW to registry, and added successfully");
   /*---(export)-------------------------*/
   rc = yjobs_world__export     (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("export"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(final)--------------------------*/
   yURG_msg ('-', "success, updated world file");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yjobs_world_withdraw    (char a_runas, char a_mode, char a_entry [LEN_PATH], char a_hdir [LEN_DESC], char a_world [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_entry     [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(audit world file)---------------*/
   rc = yjobs_world__prepare (a_runas, a_mode, a_entry, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "entry is not secure/appropriate");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for action)-------------*/
   yURG_msg ('>', "withdraw entry from world file...");
   /*---(import)-------------------------*/
   rc = yjobs_world__import (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
      return  rce;
   }
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (a_entry, &x_world);
   if (x_world == NULL) {
      yURG_err ('w', "entry does not exist in registry, nothing to do");
      g_acts_score  [G_SCORE_WUPDATE] = 'D';
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WUPDATE] = G_SCORE_FAIL;
   /*---(remove)-------------------------*/
   rc = yjobs_world__remove (a_entry);
   --rce;  if (rc < 0) {
      yURG_err ('f', "path could not be withdrawn");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(mark)---------------------------*/
   g_acts_score  [G_SCORE_WUPDATE] = 'u';
   yURG_msg ('-', "entry EXISTED in registry, and removed successfully");
   /*---(export)-------------------------*/
   rc = yjobs_world__export (a_runas, a_mode, a_hdir, a_world);
   DEBUG_YJOBS   yLOG_value   ("export"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(final)--------------------------*/
   yURG_msg ('-', "success, updated world file");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

