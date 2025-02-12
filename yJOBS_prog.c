/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"

/*
 *    read
 *    gather  (for non-world programs)
 *    walk
 *    report
 *    extract
 *    write
 *
 *    pull    (auto-clear also)
 *    clear
 *    local   (file only report)
 *    push
 *
 *
 */

/*> #define     YJOBS_READ      'Ô'                                                   <*/
/*> #define     YJOBS_GATHER    'g'                                                   <*/
/*> #define     YJOBS_WALK      'a'                                                   <*/
/*> #define     YJOBS_REPORT    'm'                                                   <*/
/*> #define     YJOBS_EXTRACT   'x'                                                   <*/
/*> #define     YJOBS_WRITE     'Õ'                                                   <*/

/*> #define     YJOBS_PULL      '×'                                                   <*/
/*> #define     YJOBS_CLEAR     'c'                                                   <*/
/*> #define     YJOBS_LOCAL     'l'                                                   <*/



char
yjobs_prog__prepare     (cchar *a_oneline, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_complex ("runas"     , "%c  å%sæ", myJOBS.m_runas, g_valid);
   --rce;  if (yJOBS_ifvalid () == 0) {
      DEBUG_YJOBS   yLOG_note    ("runas not recognized");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_YJOBS   yLOG_complex ("mode"      , "%c  å%sæ", myJOBS.m_mode, g_allmode);
   --rce;  if (yJOBS_ifallmode () == 0) {
      DEBUG_YJOBS   yLOG_note    ("mode not recognized");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(save args)----------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_oneline" , a_oneline);
   if (a_oneline  == NULL)    ystrlcpy (myJOBS.m_oneline , "oneline program description not provided", LEN_HUND);
   else                       ystrlcpy (myJOBS.m_oneline , a_oneline, LEN_HUND);
   DEBUG_YJOBS   yLOG_point   ("f_callback", f_callback);
   if (f_callback != NULL)    myJOBS.e_callback   = f_callback;
   else                       myJOBS.e_callback   = NULL;
   /*---(finalize verbosity)-------------*/
   rc = yjobs_final ();
   DEBUG_YJOBS   yLOG_value   ("final"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yJOBS_driver            (cchar *a_oneline, void *f_callback)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   char        x_done      =  '-';
   char       *p           = NULL;
   char        x_world     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YJOBS   yLOG_complex ("runas"     , "%c  å%sæ", myJOBS.m_runas, g_valid);
   --rce;  if (yJOBS_ifvalid () == 0) {
      DEBUG_YJOBS   yLOG_note    ("runas not recognized");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_YJOBS   yLOG_complex ("mode"      , "%c  å%sæ", myJOBS.m_mode, g_allmode);
   --rce;  if (yJOBS_ifallmode () == 0) {
      DEBUG_YJOBS   yLOG_note    ("mode not recognized");
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(save args)----------------------*/
   DEBUG_YJOBS   yLOG_point   ("a_oneline" , a_oneline);
   if (a_oneline  == NULL)    ystrlcpy (myJOBS.m_oneline , "oneline program description not provided", LEN_HUND);
   else                       ystrlcpy (myJOBS.m_oneline , a_oneline, LEN_HUND);
   DEBUG_YJOBS   yLOG_point   ("f_callback", f_callback);
   if (f_callback != NULL)    myJOBS.e_callback   = f_callback;
   else                       myJOBS.e_callback   = NULL;
   /*---(finalize verbosity)-------------*/
   rc = yjobs_final ();
   DEBUG_YJOBS   yLOG_value   ("final"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(overall 3)----------------------*/
   --rce;  if (x_done != 'y') {
      DEBUG_YJOBS   yLOG_note    ("checking overall (123)");
      switch (myJOBS.m_mode) {
      case CASE_ABOUT      :
         DEBUG_YJOBS   yLOG_note    ("call about option (zero callback)");
         rc = yjobs_prog_about ();
         x_done = 'y';
         break;
      default              :
         DEBUG_YJOBS   yLOG_note    ("not found in overall switch");
         break;
      }
   }
   /*---(incomming 5)--------------------*/
   --rce;  if (x_done != 'y') {
      DEBUG_YJOBS   yLOG_note    ("checking incomming (vlbui)");
      switch (myJOBS.m_mode) {
      case CASE_VERIFY     :
      case CASE_LOCALRPT   :
      case CASE_REGISTER   :
      case CASE_UPDATE     :
      case CASE_INSTALL    :
         /*> rc = yjobs_incomming ();                                                 <*/
         rc = yjobs_in ();
         x_done = 'y';
         break;
      default              :
         DEBUG_YJOBS   yLOG_note    ("not found in incomming switch");
         break;
      }
   }
   /*---(central 6)----------------------*/
   --rce;  if (x_done != 'y') {
      DEBUG_YJOBS   yLOG_note    ("checking maintain (#=mcaf)");
      switch (myJOBS.m_mode) {
      case CASE_STATS      :
      case CASE_LIST       :
      case CASE_REPORT     :
      case CASE_CHECK      :
      case CASE_AUDIT      :
      case CASE_FIX        :
         /*> rc = yjobs_maintain  ();                                                 <*/
         rc = yjobs_maint     ();
         x_done = 'y';
         break;
      case CASE_ONLY       :
         rc = yjobs_maint     ();
         /*> rc = yjobs_maintain  ();                                                 <*/
         x_done = 'y';
         break;
      default              :
         DEBUG_YJOBS   yLOG_note    ("not found in maintain switch");
         break;
      }
   }
   /*---(outgoing 4)---------------------*/
   --rce;  if (x_done != 'y') {
      DEBUG_YJOBS   yLOG_note    ("checking outgoing (wxre)");
      switch (myJOBS.m_mode) {
      case CASE_WITHDRAW   :
      case CASE_CLEAR      :
      case CASE_REMOVE     :
      case CASE_EXTRACT    :
         rc = yjobs_outgoing  ();
         x_done = 'y';
         break;
      default              :
         DEBUG_YJOBS   yLOG_note    ("not found in outgoing switch");
         break;
      }
   }
   /*---(other)--------------------------*/
   --rce;  if (x_done != 'y') {
      DEBUG_YJOBS   yLOG_note    ("checking running (gdpsn)");
      switch (myJOBS.m_mode) {
      case CASE_GATHER     :
         /*---(get central files)--------------*/
         rc = yjobs_who_location (myJOBS.m_runas, NULL, NULL, x_world, NULL, NULL);
         DEBUG_YJOBS   yLOG_value   ("location"  , rc);
         if (rc < 0) {
            DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (strlen (x_world) == 0)  rc = yjobs_gather ();
         else                        rc = yjobs_world  ();
         break;
      case CASE_DAEMON     :
      case CASE_PRICKLY    :
      case CASE_NORMAL     :
      case CASE_STRICT     :
         rc = yjobs_running   ();
         x_done = 'y';
         break;
      default              :
         DEBUG_YJOBS   yLOG_note    ("not found in running switch");
         break;
      }
   }
   /*---(complete)-----------------------*/
   /*> --rce;  if (x_done != 'y') {                                                   <* 
    *>    DEBUG_YJOBS   yLOG_note    ("checking for special ONLY");                   <* 
    *>    switch (myJOBS.m_mode) {                                                    <* 
    *>    case CASE_ONLY       :                                                      <* 
    *>       switch (myJOBS.m_mode) {                                                 <* 
    *>       case  'o' :  myJOBS.m_mode = 'n';  break;                                <* 
    *>       case  'ö' :  myJOBS.m_mode = 'ô';  break;                                <* 
    *>       case  'O' :  myJOBS.m_mode = 'N';  break;                                <* 
    *>       }                                                                        <* 
    *>       DEBUG_YJOBS   yLOG_note    ("ONLY changes into normal");                 <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yjobs_prog_about_para   (cchar *a_para)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar      *p           = NULL;
   uchar      *q           =  "¦";
   uchar       t           [LEN_RECD]  = "";
   uchar       s           [LEN_RECD]  = "";
   int         c           =    0;
   printf ("\n");
   ystrlcpy (t, a_para, LEN_RECD);
   p = strtok (t, q);
   while (p != NULL) {
      if (c == 0) {
         sprintf (s, "%s %s", p, YSTR_EDOTS);
         printf ("%-80.80s\n", s);
      } else {
         printf ("   %s\n", p);
      }
      ++c;
      p = strtok (NULL, q);
   }
   return 0;
}

char
yjobs_prog_about        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         c           = myJOBS.m_nsummary;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   printf ("%s --about (autobiography of a program)\n", myJOBS.m_summary [ 12]);
   /*---(standard headers)---------------*/
   yjobs_prog_about_para ("twenty-seven (27) standard headers¦");
   printf ("\n");
   printf ("   basename  : %s\n", myJOBS.m_summary [ 12]);
   printf ("\n");
   printf ("   focus     : %s\n", myJOBS.m_summary [++n]);
   printf ("   niche     : %s\n", myJOBS.m_summary [++n]);
   printf ("   subject   : %s\n", myJOBS.m_summary [++n]);
   printf ("   purpose   : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   namesake  : %s\n", myJOBS.m_summary [++n]);
   printf ("   pronounce : %s\n", myJOBS.m_summary [++n]);
   printf ("   heritage  : %s\n", myJOBS.m_summary [++n]);
   printf ("   briefly   : %s\n", myJOBS.m_summary [++n]);
   printf ("   imagery   : %s\n", myJOBS.m_summary [++n]);
   printf ("   reason    : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   oneline   : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   homedir   : %s\n", myJOBS.m_summary [++n]); ++n;
   printf ("   fullpath  : %s\n", myJOBS.m_summary [++n]);
   printf ("   suffix    : %s\n", myJOBS.m_summary [++n]);
   printf ("   content   : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   system    : %s\n", myJOBS.m_summary [++n]);
   printf ("   language  : %s\n", myJOBS.m_summary [++n]);
   printf ("   complier  : %s\n", myJOBS.m_summary [++n]);
   printf ("   codesize  : %s\n", myJOBS.m_summary [++n]);
   printf ("   depends   : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   author    : %s\n", myJOBS.m_summary [++n]);
   printf ("   created   : %s\n", myJOBS.m_summary [++n]);
   printf ("\n");
   printf ("   vermajor  : %s\n", myJOBS.m_summary [++n]);
   printf ("   verminor  : %s\n", myJOBS.m_summary [++n]);
   printf ("   ver num   : %s\n", myJOBS.m_summary [++n]);
   printf ("   ver txt   : %s\n", myJOBS.m_summary [++n]);
   /*---(paragraphs)---------------------*/
   while (strcmp (myJOBS.m_summary [++n], "") != 0) {
      yjobs_prog_about_para (myJOBS.m_summary [n]);
   }
   yjobs_prog_about_para ("done¦");
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}
