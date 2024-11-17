/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



char
yjobs__share_prepare    (char a_area, char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, char r_cdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_error     [LEN_HUND]  = "";
   /*---(default)------------------------*/
   strcpy (g_acts_score, g_acts_empty);
   if (r_cdir  != NULL)  strcpy (r_cdir , "");
   if (r_world != NULL)  strcpy (r_world, "");
   if (r_db    != NULL)  strcpy (r_db   , "");
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS   yLOG_info    ("g_valid"   , g_valid);
   if (a_runas == 0 || strchr (g_valid, a_runas)  == NULL) {
      sprintf (x_error, "runas (%c) not recognized or valid", ychrvisible (a_runas));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_info    ("g_allmode" , g_allmode);
   if (a_mode  == 0 || strchr (g_allmode, a_mode) == NULL) {
      sprintf (x_error, "mode (%c) not recognized or valid", ychrvisible (a_mode));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yjobs_ends_failure (a_mode, "descriptive \"oneline\" string is NULL or empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      yjobs_ends_failure (a_mode, "local file/directory is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      yjobs_ends_failure (a_mode, "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(help find bad calls)------------*/
   rc = 0;
   DEBUG_YJOBS  yLOG_char    ("a_area"    , a_area);
   --rce;  switch (a_area) {
   case 'h'  : if (strchr (G_HLP, a_mode) == NULL)  rc = -1;      break;
   case 'i'  : if (strchr (G_INC, a_mode) == NULL)  rc = -1;      break;
   case 'm'  : if (strchr (G_CEN, a_mode) == NULL)  rc = -1;      break;
   case 'o'  : if (strchr (G_OUT, a_mode) == NULL)  rc = -1;      break;
   case 'e'  : if (strchr (G_EPI, a_mode) == NULL)  rc = -1;      break;
   case 'g'  : if (strchr (G_GAT, a_mode) == NULL)  rc = -1;      break;
   default   :
      yjobs_ends_failure (a_mode, "area provided does not match any area [himoeg]");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_value   ("match"     , rc);
   --rce;  if (rc < 0) {
      sprintf (x_error, "requested mode (%c) does not match area (%c)", ychrvisible (a_mode), ychrvisible (a_area));
      yjobs_ends_failure (a_mode, x_error);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(show header)--------------------*/
   rc = yjobs_ends_header (a_runas, a_mode, a_oneline, a_file, r_cdir, NULL, r_world, r_db, NULL, r_full);
   DEBUG_YJOBS   yLOG_value   ("header"    , rc);
   if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}


