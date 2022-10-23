/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


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
   strlcpy (myJOBS.w_name  , "", LEN_LABEL);
   strlcpy (myJOBS.w_full  , "", LEN_HUND);
   myJOBS.w_file   = NULL;
   myJOBS.w_count  = 0;
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
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
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
      yURG_msg ('f', "could not prepare/clear registry, %d entries remain", yjobs_world__count ());
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "current registry prepared for import");
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
   /*---(update counter)-----------------*/
   ++myJOBS.w_count;
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
   /*---(update counter)-----------------*/
   --myJOBS.w_count;
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
   strlcpy (x_new->path, a_path, LEN_HUND);
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



/*====================------------------------------------====================*/
/*===----                           searching                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yjobs_world__count        (void)                            { return ySORT_count     (B_WORLD); }
char yjobs_world__by_path      (uchar *a_path, tWORLD **r_world) { return ySORT_by_name   (B_WORLD, a_path, r_world); }
char yjobs_world__by_index     (int n, tWORLD **r_world)         { return ySORT_by_index  (B_WORLD, n, r_world); }
char yjobs_world__by_cursor    (char a_dir, tWORLD **r_world)    { return ySORT_by_cursor (B_WORLD, a_dir, r_world); }



/*====================------------------------------------====================*/
/*===----                        export and import                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXIM____________o () { return; }

char
yjobs_world__open       (char *a_opt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("w_file"    , myJOBS.w_file);
   --rce;  if (myJOBS.w_file != NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get localtion)------------------*/
   rc = yjobs_who_location (g_runas, NULL, x_hdir, x_world, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   --rce;  if (strcmp (x_world, "") == 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   sprintf (myJOBS.w_name, "%s%s", x_hdir);
   sprintf (myJOBS.w_full, "%s%s", x_hdir, x_world);
   DEBUG_YJOBS   yLOG_info    ("w_full"    , myJOBS.w_full);
   /*---(open file)----------------------*/
   myJOBS.w_file = fopen (myJOBS.w_full, a_opt);
   DEBUG_YJOBS   yLOG_point   ("w_file"    , myJOBS.w_file);
   --rce;  if (myJOBS.w_file == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(note)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("openned successfully");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__close      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("w_file"    , myJOBS.w_file);
   --rce;  if (myJOBS.w_file == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open flow)----------------------*/
   rc = fclose (myJOBS.w_file);
   DEBUG_YJOBS   yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   strlcpy (myJOBS.w_name, "", LEN_LABEL);
   strlcpy (myJOBS.w_full, "", LEN_HUND);
   myJOBS.w_file = NULL;
   /*---(note)---------------------------*/
   DEBUG_YJOBS   yLOG_note    ("closed successfully");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__read       (char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   /*---(begin)----------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_point   ("w_file"    , myJOBS.w_file);
   --rce;  if (myJOBS.w_file == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find a record)------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      fgets (a_recd, LEN_RECD, myJOBS.w_file);
      DEBUG_YJOBS   yLOG_value   ("length"    , strlen (a_recd));
      if (feof (myJOBS.w_file)) {
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++myJOBS.w_line;
      /*---(filter)----------------------*/
      if (a_recd [0] == '\0')  continue;
      if (a_recd [0] == '#')   continue;
      if (a_recd [0] == ' ')   continue;
      /*---(clean-up)--------------------*/
      strltrim (a_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (a_recd);
      if (x_len <  5)          continue;
      if (a_recd [x_len - 1] == '\n')  a_recd [--x_len] = '\0';
      DEBUG_YJOBS   yLOG_info    ("a_recd"    , a_recd);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
yjobs_world__import     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      [LEN_RECD]  = "";
   char        x_path      [LEN_RECD]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yjobs_world__open ("rt");
   DEBUG_YJOBS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      rc = yjobs_world__read (x_curr);
      DEBUG_YJOBS   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_YJOBS   yLOG_note    ("end of file");
         break;
      }
      strlcpy (x_path, x_curr, LEN_HUND);
      /*---(save)------------------------*/
      yjobs_world__add (x_path);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = yjobs_world__close ();
   DEBUG_YJOBS   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(note)---------------------------*/
   yURG_msg ('-', "imported %d entries from world registry", yjobs_world__count ());
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__export     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yjobs_world__open ("wt");
   DEBUG_YJOBS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_YJOBS   yLOG_value   ("count"     , yjobs_world__count ());
   rc = yjobs_world__by_cursor (YDLST_HEAD, &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_YJOBS   yLOG_info  ("->path"    , x_world->path);
      fprintf (myJOBS.w_file, "%s\n", x_world->path);
      rc = yjobs_world__by_cursor (YDLST_NEXT, &x_world);
   }
   /*---(close)--------------------------*/
   rc = yjobs_world__close ();
   DEBUG_YJOBS   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   yURG_msg ('-', "exported %d entries to world registry", yjobs_world__count ());
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      major actions                           ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char
yjobs_world__home       (char a_act, char *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_path      [LEN_HUND]  = "";
   char       *p           = NULL;
   int         l           =    0;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(get the home)-------------------*/
   p = getcwd (x_path, LEN_HUND);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcat (x_path, "/", LEN_HUND);
   if (strcmp (g_runfile, "") == 0)  {
      l = strlen (x_path);
      DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
      if (a_path != NULL)  strlcpy (a_path, x_path, LEN_HUND);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle a file)------------------*/
   strlcat (x_path, g_runfile, LEN_HUND);
   l = strlen (x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   /*> if (a_act != ACT_REGISTER) {                                                   <* 
    *>    if (a_path != NULL)  strlcpy (a_path, x_path, LEN_HUND);                    <* 
    *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                  <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(check existance)----------------*/
   rc = lstat (x_path, &s);
   DEBUG_YEXEC   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YEXEC   yLOG_note    ("file does not exist at this location");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISLNK (s.st_mode))  {
      DEBUG_YEXEC  yLOG_note    ("can not use a symlink");
      DEBUG_YEXEC  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISDIR (s.st_mode))  {
      DEBUG_YEXEC   yLOG_note    ("can not use a directory");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISREG (s.st_mode))  {
      DEBUG_YEXEC   yLOG_note    ("can not use a specialty file");
      DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (a_path != NULL)  strlcpy (a_path, x_path, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_world_register    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_path      [LEN_HUND]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "register project in world file...");
   /*---(get the home)-------------------*/
   rc = yjobs_world__home (ACT_REGISTER, x_path);
   DEBUG_YJOBS   yLOG_value   ("home"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   l = strlen (x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   yURG_msg ('-', "current working directory %2då%sæ", l, x_path);
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import ();
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (x_path, &x_world);
   if (x_world != NULL) {
      yURG_err ('w', "project already exists in registry, path is same, nothing to do");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add new one)--------------------*/
   rc = yjobs_world__add    (x_path);
   --rce;  if (rc < 0) {
      yURG_err ('f', "project could not be added");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "project is new to registry, added");
   /*---(export)-------------------------*/
   rc = yjobs_world__export ();
   DEBUG_YJOBS   yLOG_value   ("export"    , rc);
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
   /*---(mute)---------------------------*/
   yURG_msg ('-', "success, current project confirmed in world file");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_world_unregister  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_path      [LEN_HUND]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "withdraw project from world file...");
   /*---(get the home)-------------------*/
   rc = yjobs_world__home (ACT_WITHDRAW, x_path);
   DEBUG_YJOBS   yLOG_value   ("home"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   l = strlen (x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   yURG_msg ('-', "current working directory %2då%sæ", l, x_path);
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import ();
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
      return  rce;
   }
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (x_path, &x_world);
   if (x_world == NULL) {
      yURG_err ('w', "entry does not exist in registry, nothing to do");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(remove)-------------------------*/
   rc = yjobs_world__remove (x_path);
   --rce;  if (rc < 0) {
      yURG_err ('f', "path could not be withdrawn");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(export)-------------------------*/
   rc = yjobs_world__export ();
   DEBUG_YJOBS   yLOG_value   ("export"    , rc);
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
   /*---(mute)---------------------------*/
   yURG_msg ('-', "success, current project withdrawn from world file");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yJOBS_world_system       (void *a_callback)
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
   rc = yjobs_world__import ();
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



