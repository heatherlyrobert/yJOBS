/*============================----beg-of-source---============================*/
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YJOBS_pguard
#define YJOBS_pguard loaded

/*===[[ HEADER ]]=============================================================*/
/*                      ·········1·········2·········3·········4·········5·········6·········7*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_NAME      "yJOBS"
#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "au (process automation)"
#define     P_SUBJECT   "service daemon framework"
#define     P_PURPOSE   "standardize common daemon requests, actions, and feedback"

#define     P_NAMESAKE  "heracles-promachus (leader in battle)"
#define     P_HERITAGE  "greatest human hero of all time, son of zeus, made into a demigod"
#define     P_IMAGERY   "massive, athletic, giant of a man wearing a lion skin and club"
#define     P_REASON    "great olympic leader in the gigantomachy and chthonic wars"

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
#define     P_VERNUM    "1.0e"
#define     P_VERTXT    "added world register/unregister capability from polymnia"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

#define     P_SUMMARY   \
 "yJOBS is a personal shared library created to standardize command line¦ \
 "arguments for service daemons, the flow of execution for the resulting¦ \
 "actions, and the nature and verbosity of feedback.¦"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/



/*===[[ CUSTOM HEADERS ]]=====================================================*/
/*---(always)---------------*/
#include    <yLOG.h>         /* CUSTOM : heatherly process logging            */
#include    <yURG.h>         /* CUSTOM : heatherly debugging framework        */
/*---(optional)-------------*/
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yEXEC.h>        /* CUSTOM : heatherly process control            */
#include    <yREGEX.h>       /* CUSTOM : heatherly regular expressions        */
#include    <ySORT.h>             /* heatherly sorting and searching          */
#include    <yDLST_solo.h>   /* CUSTOM  heatherly regular expressions         */



/*===[[ PUBLIC HEADERS ]]=====================================================*/
/*---(normal)---------------*/
#include    <stdio.h>             /* printf, scanf                               */
#include    <stdlib.h>            /* exit, system, ...                           */
#include    <string.h>            /* strcat, strcpy, strlen, ...                 */
/*---(optional)-------------*/
#include    <math.h>              /* round                                       */
#include    <sys/stat.h>          /* fstat, umask                                */
#include    <dirent.h>



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
   /*---(world file)--------*/
   char      w_name      [LEN_LABEL];
   char      w_full      [LEN_HUND];
   FILE     *w_file;
   int       w_line;
   int       w_count;
};
extern  tLOCAL myJOBS;


#define   MAX_WHO  15
typedef struct cWHO  tWHO;
struct cWHO {
   char        abbr;
   char        unit;
   char        name        [LEN_TERSE];
   char        inst        [LEN_LABEL];
   char        desc        [LEN_DESC];
   char        acts        [LEN_DESC];
   char        local;
   char        central;
   char        cdir        [LEN_DESC];
   char        udir        [LEN_DESC];
   char        lpre        [LEN_LABEL];
   char        cpre        [LEN_LABEL];
   char        lsuf        [LEN_LABEL];
   char        cname       [LEN_LABEL];
   char        hdir        [LEN_DESC];
   char        uhdir       [LEN_DESC];
   char        world       [LEN_LABEL];
   char        db          [LEN_LABEL];
};
extern const tWHO   g_whos [MAX_WHO];


typedef struct cWORLD tWORLD;
struct cWORLD {
   char        path        [LEN_RECD];
   void       *btree;
};
extern int       g_nworld;


extern char   g_runas;
extern char   g_runmode;
extern char   g_runfile    [LEN_PATH];
extern char   g_oneline    [LEN_HUND];
extern char   g_norun;
extern char   s_terse      [LEN_HUND];
extern char   s_fancy      [LEN_RECD];

extern char   g_local      [LEN_DESC];
extern char   g_central    [LEN_DESC];
extern char   g_valid      [LEN_DESC];
extern char   g_unit       [LEN_DESC];
extern char   g_etc        [LEN_DESC];

extern char   g_print      [LEN_RECD];

typedef struct cEXEC tEXEC;
typedef struct cPROC tPROC;
typedef struct cTIE  tTIE;
typedef struct cLIB  tLIB;



extern      char        unit_answer [LEN_RECD];




/*===[[ yJOBS_base ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(utility)--------------*/
char*       yJOBS_version           (void);
/*---(who-table)------------*/
char        yjobs_who_init          (void);
char        yjobs_who_naming        (cchar a_runas, char *a_local, char *a_central, char *a_lpre, char *a_cpre, char *a_lsuf, char *a_cname);
char        yjobs_who_location      (cchar a_runas, char *a_cdir, char *a_hdir, char *a_world, char *a_db);
char        yjobs_who_by_index      (char n, char *a_cdir, char *a_hdir, char *a_world, char *a_db);
char        yjobs_who_action        (cchar a_runas, cchar a_opt);
char        yjobs_who_testing       (cchar a_runas);
/*---(identify)-------------*/
char        yJOBS_runas             (cchar *a_name, char *r_runas);
char*       yjobs_iam               (char a_runas);
char*       yjobs_mode              (char a_mode);
/*---(unittest)-------------*/
char*       yjobs_base__unit        (char *a_question);
/*---(done)-----------------*/



/*===[[ yJOBS_test ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs__unit_rmdir_one   (char *a_dir);
char        yjobs__unit_mkdir_one   (char *a_dir);
char        yjobs__unit_quiet       (void);
char        yjobs__unit_loud        (void);
char        yjobs__unit_end         (void);
char*       yjobs__unit             (char *a_question, int n);


/*===[[ yJOBS_file ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(naming)---------------*/
char        yjobs__name_quality     (uchar *a_name);
char        yjobs__name_local       (cchar a_runas, uchar *a_name, uchar *r_desc);
char        yjobs__name_central     (cchar a_runas, uchar *a_name, uchar *r_desc);
char        yjobs__naming           (cchar a_runas, cchar a_loc, uchar *a_name, uchar *r_desc);
/*---(location)-------------*/
char        yjobs__loc_prepare      (cchar a_runas, cchar a_loc, cchar *a_home, cchar *a_root, uchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_dir);
char        yjobs__loc_local        (cchar *a_home, cchar *a_root, cchar *a_muser, int a_muid, char *r_fuser, char *r_dir);
char        yjobs__loc_central      (cchar a_runas, uchar *a_name, char *r_fuser, char *r_dir);
char        yjobs__location         (cchar a_runas, cchar a_loc, cchar *a_home, cchar *a_root, uchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_dir);
/*---(stats)----------------*/
char        yjobs__stat_exists      (cchar *a_dir, uchar *a_name, tSTAT *r_stat);
char        yjobs__stat_local       (tSTAT *a_stat, int a_muid, int a_uid);
char        yjobs__stat_central     (tSTAT *a_stat, cchar *a_muser, int a_muid, uchar *a_user);
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
char        yjobs_act_directory     (char n, cchar *a_dir, cchar a_fix);
char        yjobs_act_security      (cchar a_runas, cchar a_act, cchar *a_oneline, char a_fix);
char        yjobs_act_fix           (cchar a_runas, cchar a_act, cchar *a_oneline);
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate);





/*===[[ yJOBS_act ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs_act__filter       (cchar *a_name, cchar *a_prefix, int a_muid);
char        yjobs_act__prepare      (cchar a_pre, cchar a_act, cchar *a_oneline, cchar *a_muser, cchar *a_regex, char *a_prefix, char *a_dir, void *a_assimilate);
char        yjobs_act__assim        (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);

char        yjobs_args_info         (char a_mode, char *a_name);
char        yjobs_args__empty       (void);
char        yjobs_args__find        (char *a_runas, char *a_arg, char *n);
char        yjobs_args__single      (char *a_levels, char n, char a_where);
char        yjobs_args__clearmode   (char *a_runas, char *a_runmode, char *a_runfile);
char*       yjobs_args__unit        (char *a_question);


char        yjobs_min_in_msec       (int a_dur, char a_min, int a_floor , int *a_mindur);
char        yjobs_max_in_msec       (int a_dur, char a_max, int a_mindur, int *a_maxdur);



/*===[[ yJOBS_world.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yjobs_world_init        (void);
char        yjobs_world__purge      (void);
/*---(memory)---------------*/
char        yjobs_world__new        (tWORLD **a_new);
char        yjobs_world__free       (tWORLD **a_old);
/*---(existance)------------*/
char        yjobs_world__add        (char *a_path);
char        yjobs_world__remove     (char *a_path);
/*---(cursors)--------------*/
int         yjobs_world__count      (void);
char        yjobs_world__by_path    (uchar *a_path, tWORLD **r_world);
char        yjobs_world__by_index   (int n, tWORLD **r_world);
char        yjobs_world__by_cursor  (char a_dir, tWORLD **r_world);
/*---(register)-------------*/
char        yjobs_world__register   (char *x_path);
/*---(exim)-----------------*/
char        yjobs_world__open       (char *a_opt);
char        yjobs_world__close      (void);
char        yjobs_world__read       (char *a_recd);
char        yjobs_world_import      (void);
char        yjobs_world_export      (void);
/*---(actions)--------------*/
char        yjobs_world_register    (void);
char        yjobs_world_unregister  (void);
/*---(done)-----------------*/


#endif
/*============================----end-of-source---============================*/
