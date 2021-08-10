/*============================----beg-of-source---============================*/
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YEXEC_pguard
#define YEXEC_pguard loaded

/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_NAME      "yJOBS"
#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "au (process automation)"
#define     P_SUBJECT   "process control"
#define     P_PURPOSE   "shared job control environment"

#define     P_NAMESAKE  "heracles-promachus (leader in battle)"
#define     P_HERITAGE  "demi-god, the son of zeus and a mortal woman"
#define     P_IMAGERY   "powerful giant of a man wearing a lion skin and club"
#define     P_REASON    "great leader in the gigantomachy and chthonic wars"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "ySTR"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2021-01"

#define     P_VERMAJOR  "1.--, integrate into eos, heracles, and khronos"
#define     P_VERMINOR  "1.0-, break away from yEXEC"
#define     P_VERNUM    "1.0a"
#define     P_VERTXT    "initial pull of functionality from yEXEC"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/




#include    <yLOG.h>         /* CUSTOM : heatherly process logging            */
#include    <yURG.h>         /* CUSTOM : heatherly debugging framework        */
#include    <yEXEC.h>        /* CUSTOM : heatherly process control            */
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yCOLOR_solo.h>  /* CUSTOM : heatherly color constants            */
#include    <yDLST_solo.h>   /* CUSTOM : heatherly list constants             */
#include    <yREGEX.h>       /* CUSTOM : heatherly regular expressions        */

/*===[[ PUBLIC HEADERS ]]=====================================================*/
/*---(big standards)------------*/
#include    <stdio.h>             /* printf, scanf                               */
#include    <stdlib.h>            /* exit, system, ...                           */
#include    <sys/unistd.h>        /* fork, execl, getpid, getuid                 */
#include    <string.h>            /* strcat, strcpy, strlen, ...                 */
#include    <math.h>              /* round                                       */
#include    <sys/stat.h>          /* fstat, umask                                */
#include    <dirent.h>

/*---(users)--------------------*/
#include <unistd.h>                 /* stat(),crpyt()                      */



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef struct stat      tSTAT;
typedef struct dirent    tDIRENT;


#define     SIMPLE         /**/
#define     CHECK          /**/

#define          SUCCESS          0
#define          NOT_READY       -1
#define          FAILED          -2
#define          SKIPPING        -3

typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char      status;
   char      full  [LEN_RECD];
   /*---(parsing)-----------*/
   char      recd  [LEN_RECD];
};
extern  tLOCAL its;



extern char   g_runas;
extern char   g_runmode;
extern char   g_runfile     [LEN_PATH];
extern char   g_norun;
extern char   s_terse     [LEN_HUND];
extern char   s_fancy     [LEN_RECD];

typedef struct cEXEC tEXEC;
typedef struct cPROC tPROC;
typedef struct cTIE  tTIE;
typedef struct cLIB  tLIB;



extern      char        unit_answer [LEN_RECD];




/*===[[ yJOBS_base ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(utility)--------------*/
char*       yJOBS_version           (void);
/*---(identify)-------------*/
char        yJOBS_iam               (char a_iam , char *a_print);
char        yJOBS_mode              (char a_mode, char *a_print);
/*---(unittest)-------------*/
char*       yjobs_base__unit        (char *a_question);
char        yjobs__unit_quiet       (void);
char        yjobs__unit_loud        (void);
char        yjobs__unit_end         (void);
/*---(done)-----------------*/




/*===[[ yJOBS_file ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(shared)---------------*/
char        yjobs__naming           (uchar *a_name);
char        yjobs__location         (cchar a_pre, cchar a_loc, cchar *a_home, cchar *a_root, uchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_dir);
char        yjobs__stats            (cchar a_loc, cchar *a_dir, uchar *a_name, cchar *a_muser, int a_muid, uchar *a_user, int a_uid);
/*---(local)----------------*/
char        yJOBS_acceptable_full   (cchar a_runas, cchar *a_home, cchar *a_root, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
char        yJOBS_local_dir         (cchar a_runas, char *a_root, char *a_home);
char        yJOBS_acceptable        (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
/*---(central)--------------*/
char        yJOBS_central_full      (cchar a_runas, cchar *a_central, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc);
char        yJOBS_central_dir       (cchar a_runas, cchar *a_name, char *a_dir, char *a_user, char *a_file);
char        yJOBS_central           (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
/*---(unittest)-------------*/
char*       yjobs_file__unit        (char *a_question);
/*---(done)-----------------*/




/*===[[ yJOBS_act ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yJOBS_act_verify        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
char        yJOBS_act_install       (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
char        yJOBS_act_check         (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
char        yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name);
char        yJOBS_act_security      (cchar a_runas, cchar a_act, cchar *a_oneline);
char        yJOBS_act_fix           (cchar a_runas, cchar a_act, cchar *a_oneline);
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate);





/*===[[ yJOBS_act ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs_act__checkdir     (cchar *a_dir, int a_perms);
char        yjobs_act__filter       (cchar *a_name, cchar *a_prefix, int a_muid);
char        yjobs_act__prepare      (cchar a_pre, cchar a_act, cchar *a_oneline, cchar *a_muser, cchar *a_regex, char *a_prefix, char *a_dir, void *a_assimilate);
char        yjobs_act__assim        (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);
char        yjobs_act__mkdir        (void);
char        yjobs_act__rmdir        (void);

char        yjobs_args__empty       (void);
char        yjobyjobss__init        (char a_runas, char a_runmode, char *a_runfile);
char        yjobs_args__single      (char *a_levels, char n);
char        yjobs_args__clearmode   (char *a_runas, char *a_runmode, char *a_runfile);
char*       yjobs_args__unit        (char *a_question);

char*       yjobs_base__unit        (char *a_question);
char        yjobs__unit_quiet       (void);
char        yjobs__unit_loud        (void);
char        yjobs__unit_end         (void);

char        yjobs_min_in_msec       (int a_dur, char a_min, int a_floor , int *a_mindur);
char        yjobs_max_in_msec       (int a_dur, char a_max, int a_mindur, int *a_maxdur);




#endif
/*============================----end-of-source---============================*/
