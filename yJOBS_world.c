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
   ystrlcpy (myJOBS.w_name  , "", LEN_LABEL);
   ystrlcpy (myJOBS.w_full  , "", LEN_PATH);
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
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   c = yjobs_world__count ();
   DEBUG_YJOBS   yLOG_value   ("count"     , c);
   if (c == 0) {
      yURG_msg ('-', "no current world entries, already clean");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   yURG_msg ('-', "purging existing %d world entries", c);
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
   yURG_msg ('-', "world entries successfully purged, zero remain");
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
yjobs_world__open       (cchar a_runas, cchar *a_opt)
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
      yURG_msg ('-', "world file already open, continuing");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get localtion)------------------*/
   rc = yjobs_who_location (a_runas, NULL, x_hdir, x_world, NULL, NULL);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   --rce;  if (strcmp (x_world, "") == 0) {
      yURG_msg ('-', "no world file specified for this program");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   sprintf (myJOBS.w_name, "%s"  , x_world);
   sprintf (myJOBS.w_full, "%s%s", x_hdir, x_world);
   yURG_msg ('-', "world file identified as å%sæ", myJOBS.w_full);
   DEBUG_YJOBS   yLOG_info    ("w_full"    , myJOBS.w_full);
   /*---(open file)----------------------*/
   myJOBS.w_file = fopen (myJOBS.w_full, a_opt);
   DEBUG_YJOBS   yLOG_point   ("w_file"    , myJOBS.w_file);
   --rce;  if (myJOBS.w_file == NULL) {
      yURG_err ('w', "world file does not exist, but specified");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(note)---------------------------*/
   yURG_msg ('-', "world file successfully openned");
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
   ystrlcpy (myJOBS.w_name, "", LEN_LABEL);
   ystrlcpy (myJOBS.w_full, "", LEN_PATH);
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
      ystrltrim (a_recd, ySTR_BOTH, LEN_RECD);
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
yjobs_world__import     (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      [LEN_PATH]  = "";
   char        x_path      [LEN_PATH]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yjobs_world__open (a_runas, "rt");
   DEBUG_YJOBS   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   yURG_msg ('-', "registry stored at å%sæ", myJOBS.w_full);
   /*---(walk)---------------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      rc = yjobs_world__read (x_curr);
      DEBUG_YJOBS   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_YJOBS   yLOG_note    ("end of file");
         break;
      }
      ystrlcpy (x_path, x_curr, LEN_PATH);
      /*---(save)------------------------*/
      rc = yjobs_world__add (x_path);
      DEBUG_YJOBS   yLOG_value   ("add"       , rc);
      if (rc < 0) {
         yURG_msg ('F', "import failed on %d entry", myJOBS.w_line);
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
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
yjobs_world__export     (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yjobs_world__open (a_runas, "wt");
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

/*> char                                                                              <* 
 *> yjobs_world__justhome   (char *r_file, char *r_path)                              <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    char        x_path      [LEN_PATH]  = "";                                      <* 
 *>    char       *p           = NULL;                                                <* 
 *>    int         l           =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);                                     <* 
 *>    /+---(get the home)-------------------+/                                       <* 
 *>    p = getcwd (x_path, LEN_PATH);                                                 <* 
 *>    DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);                                  <* 
 *>    --rce;  if (p == NULL) {                                                       <* 
 *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    ystrlcat (x_path, "/", LEN_PATH);                                               <* 
 *>    /+---(handle a file)------------------+/                                       <* 
 *>    if (strcmp (myJOBS.m_file, "") != 0)  {                                        <* 
 *>       ystrlcat (x_path, myJOBS.m_file, LEN_PATH);                                  <* 
 *>       if (r_file != NULL)  *r_file = 'y';                                         <* 
 *>    }                                                                              <* 
 *>    l = strlen (x_path);                                                           <* 
 *>    DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);               <* 
 *>    /+---(save-back)----------------------+/                                       <* 
 *>    if (r_path != NULL)  ystrlcpy (r_path, x_path, LEN_PATH);                       <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);                                     <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
yjobs_world__exist      (cchar *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_file      =  '-';
   char        x_path      [LEN_PATH]  = "";
   tSTAT       s;
   /*---(header)-------------------------*/
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
   --rce;  if (l <= 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_path, a_path, LEN_PATH);
   if (x_path [l - 1] != '/') {
      x_file = 'y';
      yURG_msg ('-', "verifying file at %2då%sæ", l, x_path);
   } else {
      x_path [l - 1] = '\0';
      yURG_msg ('-', "verifying dir at  %2då%sæ", l, x_path);
   }
   DEBUG_YJOBS   yLOG_char    ("x_file"    , x_file);
   /*---(check existance)----------------*/
   rc = lstat (x_path, &s);
   DEBUG_YJOBS   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("entry does not exist at this location");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (S_ISLNK (s.st_mode))  {
      DEBUG_YJOBS  yLOG_note    ("can not use a symlink");
      DEBUG_YJOBS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(file specific)------------------*/
   --rce;  if (x_file == 'y') {
      --rce;  if (S_ISDIR (s.st_mode))  {
         DEBUG_YJOBS   yLOG_note    ("can not use a directory");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      --rce;  if (!S_ISREG (s.st_mode))  {
         DEBUG_YJOBS   yLOG_note    ("can not use a specialty file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(directory specific)-------------*/
   --rce;  if (x_file != 'y') {
      --rce;  if (S_ISREG (s.st_mode))  {
         DEBUG_YJOBS   yLOG_note    ("can not use a normal file file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      --rce;  if (!S_ISDIR (s.st_mode))  {
         DEBUG_YJOBS   yLOG_note    ("can not use a specialty file");
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world__home       (cchar a_act, cchar *a_file, char *r_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_path      [LEN_PATH]  = "";
   char       *p           = NULL;
   int         l           =    0;
   tSTAT       s;
   char        x_file      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(get the home)-------------------*/
   p = getcwd (x_path, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcat (x_path, "/", LEN_PATH);
   /*---(handle a file)------------------*/
   if (strcmp (a_file, "") != 0 && a_file [0] != '/')  {
      if (strcmp (a_file, "dir") != 0) ystrlcat (x_path, a_file, LEN_PATH);
   }
   l = strlen (x_path);
   yURG_msg ('-', "current working directory %2då%sæ", l, x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   /*---(verify)-------------------------*/
   rc = yjobs_world__exist (x_path);
   DEBUG_YJOBS   yLOG_value   ("exist"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_path != NULL)  ystrlcpy (r_path, x_path, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_world_audit       (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   int         x_fail      =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "audit the world file...");
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import (a_runas);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   } else {
      yURG_msg ('-', "success, world file imported with no troubles");
   }
   /*---(import)-------------------------*/
   yjobs_world__by_cursor  (YDLST_HEAD, &x_world);
   while (x_world != NULL) {
      rc = yjobs_world__exist (x_world->path);
      DEBUG_YJOBS   yLOG_value   ("exist"     , rc);
      if (rc < 0) {
         yURG_err ('f', "failed to find å%sæ", x_world->path);
         ++x_fail;
      }
      yjobs_world__by_cursor  (YDLST_NEXT, &x_world);
   }
   /*---(troubles)-----------------------*/
   --rce;  if (x_fail > 0) {
      yURG_err ('f', "failed to find (%d) directories in world list", x_fail);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   } else {
      yURG_msg ('-', "success, verified all world entries");
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world_list        (cchar a_runas)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import (a_runas);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   /*---(run list)-----------------------*/
   yjobs_world__by_cursor  (YDLST_HEAD, &x_world);
   while  (x_world != NULL) {
      printf ("%s\n", x_world->path);
      /*> printf ("%2d  %s\n", ++n, x_world->path);                                   <*/
      yjobs_world__by_cursor  (YDLST_NEXT, &x_world);
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_world_register    (cchar a_runas, cchar *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_path      [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "register in world file...");
   g_acts_score  [G_SCORE_WORLD + 1] = G_SCORE_FAIL;
   /*---(check file)---------------------*/
   /*> --rce;  switch (a_runas) {                                                     <* 
    *> case IAM_POLYMNIA  : case IAM_UPOLYMNIA :                                      <* 
    *>    if (strcmp (a_file, "") != 0) {                                             <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return  rce;                                                             <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> case IAM_METIS     : case IAM_UMETIS    :                                      <* 
    *>    if (strcmp (a_file, "") == 0) {                                             <* 
    *>       DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return  rce;                                                             <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> }                                                                              <*/
   /*---(get the home)-------------------*/
   rc = yjobs_world__home (ACT_REGISTER, a_file, x_path);
   DEBUG_YJOBS   yLOG_value   ("home"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   l = strlen (x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import (a_runas);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
   }
   g_acts_score  [G_SCORE_WORLD + 1] = 'Ô';
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (x_path, &x_world);
   if (x_world != NULL) {
      yURG_err ('w', "project already exists in registry, path is same, nothing to do");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add new one)--------------------*/
   g_acts_score  [G_SCORE_WORLD + 3] = G_SCORE_FAIL;
   rc = yjobs_world__add    (x_path);
   --rce;  if (rc < 0) {
      yURG_err ('f', "project could not be added");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "project is new to registry, added");
   g_acts_score  [G_SCORE_WORLD + 3] = 'r';
   /*---(export)-------------------------*/
   g_acts_score  [G_SCORE_WORLD + 5] = G_SCORE_FAIL;
   rc = yjobs_world__export (a_runas);
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
   g_acts_score  [G_SCORE_WORLD + 5] = 'Õ';
   /*---(mute)---------------------------*/
   yURG_msg ('-', "success, current project confirmed in world file");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_world_withdraw    (cchar a_runas, cchar *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_path      [LEN_PATH]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "withdraw project from world file...");
   g_acts_score  [G_SCORE_WORLD + 1] = G_SCORE_FAIL;
   /*---(get the home)-------------------*/
   rc = yjobs_world__home (ACT_WITHDRAW, a_file, x_path);
   DEBUG_YJOBS   yLOG_value   ("home"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   l = strlen (x_path);
   DEBUG_YJOBS   yLOG_complex ("x_path"    , "%2då%sæ", l, x_path);
   /*---(purge)--------------------------*/
   rc = yjobs_world__purge ();
   DEBUG_YJOBS   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = yjobs_world__import (a_runas);
   DEBUG_YJOBS   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_note    ("no existing file");
      return  rce;
   }
   g_acts_score  [G_SCORE_WORLD + 1] = 'Ô';
   /*---(look for existing)--------------*/
   rc = yjobs_world__by_path (x_path, &x_world);
   if (x_world == NULL) {
      yURG_err ('w', "entry does not exist in registry, nothing to do");
      g_acts_score  [G_SCORE_WORLD + 4] = G_SCORE_SKIP;
      g_acts_score  [G_SCORE_WORLD + 5] = G_SCORE_SKIP;
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(remove)-------------------------*/
   g_acts_score  [G_SCORE_WORLD + 4] = G_SCORE_FAIL;
   rc = yjobs_world__remove (x_path);
   --rce;  if (rc < 0) {
      yURG_err ('f', "path could not be withdrawn");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_acts_score  [G_SCORE_WORLD + 4] = 'u';
   /*---(export)-------------------------*/
   g_acts_score  [G_SCORE_WORLD + 5] = G_SCORE_FAIL;
   rc = yjobs_world__export (a_runas);
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
   yURG_msg (' ', "");
   g_acts_score  [G_SCORE_WORLD + 5] = 'Õ';
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

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
   rc = yjobs_act_header (a_runas, a_mode, a_oneline, a_file, NULL, x_world, NULL, x_db, x_cwd, NULL);
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
         yjobs_act_failure (a_mode, "central database did not load properly");
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
   rc = yjobs_world__import (a_runas);
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
         yjobs_act_failure (a_mode, "central database could not save properly");
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
   rc = yjobs_act_footer (a_mode);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yjobs_world             (void) { return yjobs_world_full  (myJOBS.m_runas, myJOBS.m_mode, myJOBS.m_oneline, myJOBS.m_file, myJOBS.e_callback); }

char
yJOBS_world_system       (cchar a_runas, void *a_callback)
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
   rc = yjobs_world__import (a_runas);
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

