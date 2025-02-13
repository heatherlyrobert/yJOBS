/*============================----beg-of-source---============================*/
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YJOBS_pguard
#define YJOBS_pguard loaded

/*===[[ HEADER ]]=============================================================*/
/*                      ·········1·········2·········3·········4·········5·········6·········7*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "au (process automation)"
#define     P_SUBJECT   "common service daemon framework"
#define     P_PURPOSE   "standardize common daemon requests, actions, and feedback"

#define     P_NAMESAKE  "heracles-promachus (leader in battle)"
#define     P_PRONOUNCE "hay·ruh·klees proh·maa·kuhs"
#define     P_HERITAGE  "greatest human hero of all time, son of zeus, made into a demigod"
#define     P_BRIEFLY   "greece's greatest human hero"
#define     P_IMAGERY   "massive, athletic, giant of a man wearing a lion skin and club"
#define     P_REASON    "great olympic leader in the gigantomachy and chthonic wars"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yJOBS"
#define     P_FULLPATH  "/usr/local/lib64/"
#define     P_SUFFIX    "n/a"
#define     P_CONTENT   "n/a"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "ySTR"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2021-01"

#define     P_VERMAJOR  "1.--, integrate into eos, heracles, and khronos"
#define     P_VERMINOR  "1.2-, improve unit-testing and eos string-testing"
#define     P_VERNUM    "1.2f"
#define     P_VERTXT    "unit testing done with yJOBS__maint_check and updates to function"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

#define     P_SUMMARY   \
 "yJOBS is a personal shared library created to standardize command line¦" \
 "arguments for service daemons, the flow of execution for the resulting¦" \
 "actions, and the nature and verbosity of feedback.¦"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/


/*
 * METIS § mg2·· § add GPL headers (from helios) to all files                             § N9N77I §  · §
 * METIS § dn8·· § catch up all unit testing and pass                                     § N9N77u §  · §
 *
 *
 *
 *
 */


/*===[[ CUSTOM HEADERS ]]=====================================================*/
/*---(always)---------------*/
#include    <yLOG.h>         /* CUSTOM : heatherly process logging            */
#include    <yURG.h>         /* CUSTOM : heatherly debugging framework        */
#include    <yENV.h>
/*---(optional)-------------*/
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yEXEC.h>        /* CUSTOM : heatherly process control            */
#include    <yREGEX.h>       /* CUSTOM : heatherly regular expressions        */
#include    <ySORT.h>             /* heatherly sorting and searching          */
#include    <yDLST_solo.h>   /* CUSTOM  heatherly regular expressions         */
#include    <yCOLOR_solo.h>  /* CUSTOM : heatherly color constants            */



/*===[[ PUBLIC HEADERS ]]=====================================================*/
/*---(normal)---------------*/
#include    <stdio.h>             /* printf, scanf                               */
#include    <stdlib.h>            /* exit, system, ...                           */
#include    <string.h>            /* strcat, strcpy, strlen, ...                 */
#include    <stdarg.h>       /* C_ANSI : va_args                              */
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

#define    MAX_SUMM  50

typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(header)------------*/
   char      m_nsummary;
   char     *m_summary     [MAX_SUMM];
   /*---(environment)-------*/
   char      m_user        [LEN_USER];      /* running user name                */
   int       m_uid;                         /* running user id                  */
   char      m_root        [LEN_DESC];      /* root directory start             */
   char      m_home        [LEN_DESC];      /* home directory start             */
   /*---(overall)-----------*/
   char      m_runas;
   char      m_mode;
   char      m_flag;
   char      m_file        [LEN_PATH];      /* source file name                 */
   char      m_dir         [LEN_PATH];      /* source file dir                  */
   char      m_full        [LEN_PATH];      /* source file qualified name       */
   char      m_oneline     [LEN_HUND];      /* program oneline description      */
   char    (*e_read)       (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);
   char    (*e_exec)       (void);
   char    (*e_callback)   (cchar a_req, cchar *a_full);
   /*---(file base)---------*/
   char      f_loc;                         /* central or local                 */
   char      f_user        [LEN_USER];      /* target file user name            */
   int       f_uid;                         /* target file user id              */
   char      f_desc        [LEN_DESC];      /* target file description          */
   char      f_file        [LEN_DESC];      /* target file target name          */
   char      f_dir         [LEN_PATH];      /* target file target dir           */
   char      f_full        [LEN_PATH];      /* target file targe qualified name */
   /*---(world file)--------*/
   char      w_name        [LEN_LABEL];
   char      w_full        [LEN_PATH];
   FILE     *w_file;
   int       w_line;
   int       w_count;
   /*---(done)--------------*/
};
extern  tLOCAL myJOBS;


#define   MAX_WHO  15
typedef struct cWHO  tWHO;
struct cWHO {
   char        w_abbr;
   char        w_unit;
   char        name        [LEN_TERSE];
   char        inst        [LEN_LABEL];
   char        desc        [LEN_DESC];
   char        w_acts      [LEN_DESC];
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
   char        update;
   char        db          [LEN_LABEL];
};
extern const tWHO   g_whos [MAX_WHO];


typedef struct cWORLD tWORLD;
struct cWORLD {
   char        path        [LEN_RECD];
   void       *btree;
};
extern int       g_nworld;


extern char   g_norun;
extern char   s_terse      [LEN_HUND];
extern char   s_fancy      [LEN_RECD];

extern char   g_local      [LEN_DESC];
extern char   g_central    [LEN_DESC];
extern char   g_valid      [LEN_DESC];
extern char   g_unit       [LEN_DESC];
extern char   g_etc        [LEN_DESC];

extern char   g_allmode    [LEN_HUND];
extern char   g_silent     [LEN_DESC];
extern char   g_confirm    [LEN_DESC];
extern char   g_verbose    [LEN_DESC];

/*---(help)-----------------*/
extern char   G_HLP         [LEN_DESC];
/*---(incomming)------------*/
extern char   G_INC         [LEN_DESC];
extern char   g_verify      [LEN_SHORT];
extern char   g_localrpt    [LEN_SHORT];
extern char   g_register    [LEN_SHORT];
extern char   g_install     [LEN_SHORT];
extern char   g_update      [LEN_SHORT];
/*---(central)--------------*/
extern char   G_CEN         [LEN_DESC];
extern char   g_stats       [LEN_SHORT];
extern char   g_list        [LEN_SHORT];
extern char   g_report      [LEN_SHORT];
extern char   g_check       [LEN_SHORT];
extern char   g_audit       [LEN_SHORT];
extern char   g_fix         [LEN_SHORT];
extern char   g_only        [LEN_SHORT];
/*---(outgoing)-------------*/
extern char   G_OUT         [LEN_DESC];
extern char   g_withdraw    [LEN_SHORT];
extern char   g_clear       [LEN_SHORT];
extern char   g_remove      [LEN_SHORT];
extern char   g_extract     [LEN_SHORT];
/*---(transfer)-------------*/
extern char   G_EPI         [LEN_DESC];
extern char   g_upload      [LEN_SHORT];
extern char   g_download    [LEN_SHORT];
/*---(execution)------------*/
extern char   G_GAT         [LEN_DESC];
extern char   g_gather      [LEN_SHORT];
extern char   g_running     [LEN_LABEL];
extern char   g_daemony     [LEN_LABEL];
extern char   g_daemon      [LEN_SHORT];
extern char   g_prickly     [LEN_SHORT];
extern char   g_normal      [LEN_SHORT];
extern char   g_strict      [LEN_SHORT];
extern char   g_reload      [LEN_SHORT];
/*---(actions)--------------*/
extern char   g_act_rdb     [LEN_HUND];    /* read central database       */
extern char   g_act_upd     [LEN_HUND];    /* pull data from local file   */
extern char   g_act_ins     [LEN_HUND];    /* move local file to central  */
extern char   g_act_reg     [LEN_HUND];    /* register in world file      */

extern char   g_act_sec     [LEN_HUND];    /* audit directory security    */
extern char   g_act_aud     [LEN_HUND];    /* audit file security         */
extern char   g_act_pul     [LEN_HUND];    /* read-in central files       */
extern char   g_act_rpt     [LEN_HUND];    /* central reporting           */
extern char   g_act_run     [LEN_HUND];    /* run mode                    */
extern char   g_act_chk     [LEN_HUND];    /* check a single central file */
extern char   g_act_kep     [LEN_HUND];    /* retain file pull data       */

extern char   g_act_wit     [LEN_HUND];    /* withdraw from world file    */
extern char   g_act_clr     [LEN_HUND];    /* clear out of database       */
extern char   g_act_rem     [LEN_HUND];    /* remove from central (files) */
extern char   g_act_wdb     [LEN_HUND];    /* write central db            */
/*---(done)-----------------*/

extern char   g_print       [LEN_RECD];

typedef struct cEXEC tEXEC;
typedef struct cPROC tPROC;
typedef struct cTIE  tTIE;
typedef struct cLIB  tLIB;



extern char    g_acts_empty    [LEN_HUND];
extern char    g_acts_score    [LEN_HUND];
extern char    g_fullacts      [LEN_DESC];



#define     G_SCORE_FAIL      '°'
#define     G_SCORE_SKIP      '-'



#define     G_SCORE_PREPARE    0
#define     G_SCORE_SECURE     7
#define     G_SCORE_DATABASE  14
#define     G_SCORE_LOCAL     24
#define     G_SCORE_WORLD     32
#define     G_SCORE_CENTRAL   43
#define     G_SCORE_ACTION    55
#define     G_SCORE_BACKEND   63
#define     G_SCORE_JUDGE     70



#define     YJOBS_RC_READ      1
#define     YJOBS_RC_STATS     6
#define     YJOBS_RC_WRITE     3
#define     YJOBS_RC_PULL      2
#define     YJOBS_RC_CLEAR     7
#define     YJOBS_RC_LOCALRPT  5
#define     YJOBS_RC_REPORT    8
#define     YJOBS_RC_EXTRACT   9
#define     YJOBS_RC_PURGE    10
#define     YJOBS_RC_REGISTER 11



extern      char    unit_answer     [LEN_RECD];




/*===[[ yJOBS_base ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(utility)--------------*/
char*       yJOBS_version           (void);
/*---(who-table)------------*/
char        yjobs_who_init          (void);
char        yjobs_who_naming        (cchar a_runas, char *a_local, char *a_central, char a_lpre [LEN_LABEL], char a_cpre [LEN_LABEL], char a_lsuf [LEN_LABEL], char a_cname [LEN_LABEL]);
char        yjobs__who_base         (cchar a_runas, char *r_unit, char r_name [LEN_TERSE], char r_desc [LEN_DESC], char r_cdir [LEN_DESC], char r_cname [LEN_LABEL], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char *r_update, char r_db [LEN_LABEL]);
char        yjobs_who_location      (cchar a_runas, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char *r_update, char r_db [LEN_LABEL]);
char        yjobs_who_by_index      (char n, char *a_cdir, char *a_hdir, char *a_world, char *a_db);
char        yjobs_who_action        (cchar a_runas, cchar a_opt);
char        yjobs_who_testing       (cchar a_runas);
/*---(identify)-------------*/
char        yjobs_runas             (cchar *a_name, char *r_runas);
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
char        yjobs__name_quality     (cchar *a_name);
char        yjobs__name_local       (cchar a_runas, cchar *a_name, uchar *r_desc);
char        yjobs__name_central     (cchar a_runas, cchar *a_name, uchar *r_desc);
char        yjobs__naming           (cchar a_runas, cchar a_loc, cchar *a_name, uchar *r_desc);
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
char        yjobs_local_full        (cchar a_runas, cchar *a_home, cchar *a_root, cchar *a_file, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
char        yjobs__local_dirs       (cchar a_runas, char *r_root, char *r_home);
char        yjobs_local_old         (cchar a_runas, cchar *a_file, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
char        yjobs_local             (char *r_fuser, int *r_fuid, char *r_fdesc, char *r_fdir);
/*---(central)--------------*/
char        yjobs_central_full      (cchar a_runas, cchar *a_central, cchar *a_file, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc);
char        yjobs_central_dirs      (cchar a_runas, cchar a_mode, cchar *a_file, cchar *a_user, char *r_dir, char *r_new);
char        yjobs_central_old       (cchar a_runas, cchar a_mode, cchar *a_file, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
char        yjobs_central           (void);
/*---(unittest)-------------*/
char*       yjobs_file__unit        (char *a_question);
/*---(done)-----------------*/




/*===[[ yJOBS_act ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*> char        yjobs_incomming_full    (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_HUND], void *f_callback);   <*/
/*> char        yjobs_incomming         (void);                                       <*/
char        yjobs_maintain_full     (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_HUND], void *f_callback);
char        yjobs_maintain          (void);
char        yjobs_outgoing_full     (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_HUND], void *f_callback);
char        yjobs_outgoing          (void);
char        yjobs_running__pull     (cchar a_runas, cchar a_mode, cchar *a_cdir, void *f_callback);
char        yjobs_running_full      (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_HUND], void *f_callback);
char        yjobs_running           (void);
char        yjobs_gather_full       (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar a_file [LEN_HUND], void *f_callback);
char        yjobs_gather            (void);

/*---(obsolete)-------------*/
char        yJOBS_act_check         (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar *a_name, void *a_assimilate);
char        yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar *a_name);
char        yjobs_act__fixdir       (cchar a_dir [LEN_PATH], char a_issue, int a_perms, tSTAT *r_stat);
char        yjobs_act_fix           (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND]);
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar a_oneline [LEN_HUND], cchar a_muser [LEN_USER], int a_muid, cchar *a_regex, void *a_assimilate);



/*===[[ yJOBS_ends ]]=========================================================*/
/*·type···· ´···function··········· ´···arguments·····························*/
/*---(scoring)--------------*/
char        yjobs_ends_clear        (void);
char        yjobs_ends_score        (char a_section, char a_offset, uchar a_result);
/*---(header)---------------*/
char        yjobs__ends_titles      (char a_mode, char a_oneline [LEN_HUND]);
char        yjobs__ends_locations   (char a_runas, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL]);
char        yjobs__ends_cwd         (char a_mode, char a_file [LEN_TERSE], char a_cdir [LEN_PATH], char r_cwd [LEN_PATH], char r_full [LEN_PATH]);
char        yjobs_ends_header       (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_TERSE], char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_cwd [LEN_PATH], char r_full [LEN_PATH]);
/*---(footer)---------------*/
char        yjobs_ends_success      (char a_mode);
char        yjobs_ends_approved     (char a_mode);
char        yjobs_ends_repaired     (char a_mode);
char        yjobs_ends_warning      (char a_mode);
/*---(failure)--------------*/
char        yjobs_ends_failure      (char a_mode, char a_hint [LEN_HUND]);
/*---(end)------------------*/



/*===[[ yJOBS_act ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs_act__filter       (cchar *a_name, cchar *a_prefix, int a_muid);
char        yjobs_act__prepare      (cchar a_pre, cchar a_act, cchar a_oneline [LEN_HUND], cchar a_muser [LEN_USER], cchar *a_regex, char *a_prefix, char *a_dir, void *a_assimilate);
char        yjobs_act__assim        (cchar a_runas, cchar a_loc, cchar *a_name, char *r_user, char *r_desc);

char        yjobs_args_info         (char a_mode, char *a_name);
char        yjobs_args__empty       (void);
char        yjobs_args_offset       (char a_mode);
char        yjobs_args__find        (char *a_arg, char *n, char *r_runas, char *r_noise);
char        yjobs_args__single      (char *a_levels, char a_cat, char n, char a_run, char a_where);
char        yjobs_args__clearmode   (char *a_runas, char *a_runmode, char *a_runfile);
char        yjobs_final_full        (int a_uid);
char        yjobs_final             (void);
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
char        yjobs_world__open       (cchar a_runas, cchar *a_opt);
char        yjobs_world__close      (void);
char        yjobs_world__read       (char *a_recd);
char        yjobs_world__import     (cchar a_runas);
char        yjobs_world__export     (cchar a_runas);
/*---(actions)--------------*/
char        yjobs_world__exist      (cchar *a_path);
char        yjobs_world__home       (cchar a_act, cchar *a_file, char *r_path);
char        yjobs_world_audit       (cchar a_runas);
char        yjobs_world_list        (cchar a_runas);
char        yjobs_world_register    (cchar a_runas, cchar *a_file);
char        yjobs_world_withdraw    (cchar a_runas, cchar *a_file);
/*---(done)-----------------*/

char        yjobs_prog_about        (void);

char        yjobs_callback          (cchar a_req, cchar *a_data);




/*===[[ yJOBS_share.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs_share_prepare     (char a_func [LEN_TITLE], char a_area, char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, char r_cdir [LEN_DESC], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_full [LEN_PATH]);
char        yjobs_share_readdb      (char a_func [LEN_TITLE], char a_area, char a_mode, char a_db [LEN_LABEL], void *f_callback);
char        yjobs_share_writedb     (char a_func [LEN_TITLE], char a_area, char a_mode, char a_db [LEN_LABEL], void *f_callback);
char        yjobs__share_filter     (char a_name [LEN_HUND], char a_prefix [LEN_TERSE], int a_muid);
char        yjobs__share_single     (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback);
char        yjobs__share_multiple   (char a_runas, char a_mode, char a_config [LEN_DESC], char a_cname [LEN_LABEL], char a_user [LEN_USER], int a_uid, void *f_callback);
char        yjobs_share_review      (char a_func [LEN_TITLE], char a_area, char a_runas, char a_mode, void *f_callback, char a_fail);


/*===[[ yJOBS_in.c ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(partial)--------------*/
char        yjobs__in_dir           (char a_runas, char a_mode, char a_file [LEN_PATH], char r_fuser [LEN_USER], char r_fdir [LEN_PATH], char r_full [LEN_PATH]);
char        yjobs__in_verify        (char a_runas, char a_mode, char a_file [LEN_PATH], char r_fuser [LEN_USER], char r_fdir [LEN_PATH], char r_full [LEN_PATH]);
char        yjobs__in_pull          (char a_mode, void *f_callback, char a_full [LEN_PATH]);
char        yjobs__in_report        (char a_mode, void *f_callback, char a_full [LEN_PATH]);
char        yjobs__in_intake        (char a_runas, char a_mode, char a_file [LEN_PATH], char a_db [LEN_LABEL], char a_fuser [LEN_USER]);
char        yjobs__in_register      (char a_runas, char a_mode, char a_file [LEN_PATH], char a_world [LEN_LABEL], void *f_testcall);
/*---(main)-----------------*/
char        yjobs_in_full           (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback);
char        yjobs_in                (void);
/*---(done)-----------------*/



/*===[[ yJOBS_maint.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(partial)--------------*/
char        yjobs__maint_secure     (char a_runas, char a_mode, char a_oneline [LEN_HUND]);
char        yjobs_maint_security    (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_fix);
char        yjobs__maint_config     (char a_runas, char a_mode, char a_cdir [LEN_DESC], void *f_callback, char c_hardfail);
char        yjobs__maint_check      (char a_runas, char a_mode, char a_cdir [LEN_DESC], char a_file [LEN_LABEL], void *f_callback, char c_hardfail);
char        yjobs__maint_central    (char a_runas, char a_mode, char a_hdir [LEN_DESC], char a_world [LEN_LABEL], char a_database [LEN_LABEL], void *f_callback, char c_hardfail);
char        yjobs__maint_stats      (char a_mode, void *f_callback);
char        yjobs__maint_report     (char a_mode, char a_file [LEN_PATH], void *f_callback);
/*---(main)-----------------*/
char        yjobs_maint_full        (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback);
char        yjobs_maint             (void);
/*---(done)-----------------*/



/*===[[ yJOBS_dir.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yjobs__dir_fix          (char a_dir [LEN_PATH], char a_issue, int a_perms, tSTAT *r_stat);
char        yjobs__dir_check        (char a_level, char a_dir [LEN_PATH], int a_perms, char a_fix);
char        yjobs_dir_single        (char a_level, char a_dir [LEN_PATH], char a_fix);
char        yjobs_dir_review        (char a_runas, char a_act, char a_oneline [LEN_HUND], char a_fix);
char        yjobs_dir_list          (char a_path [LEN_PATH], char r_list [LEN_MASS]);


/*---(done)-----------------*/
char        yjobs_world_full        (cchar a_runas, cchar a_mode, cchar a_oneline [LEN_HUND], cchar *a_file, void *f_callback);
char        yjobs_world             (void);



#endif
/*============================----end-of-source---============================*/
