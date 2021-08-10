/*============================----beg-of-source---============================*/
/*===[[ PURPOSE ]]============================================================*

 *   yEXEC is a set of shared functions providing reliable, consisten, and clean
 *   access to program launching and monitoring services.  its purpose is to
 *   take a complex and foundational capability and provide a shared service
 *   that can be tested, maintained, and documented once to avoid migrations.
 *
 *   keeping with the refactoring motto of "DRY: don't repeat yourself", we will
 *   build this code into a single set of shared functions so that we have a
 *   single, unambiguous, authoritative version of the functions.
 *
 *   yEXEC will focus on...
 *      - very solid logging on all functions (noisy and traceable)
 *      - provide execution output on launches
 *      - simple, defensive job launching
 *      - checking for program completion
 *      - finding jobs by name
 *      - daemonizing programs
 *      - normal signal handling
 *
 *   as always, there are many, stable, accepted, existing programs and
 *   utilities built by better programmers that are likely superior in speed,
 *   size, capability, and reliability; BUT, i would not have learned nearly as
 *   much using them, so i follow the adage...
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 *   the underlying idea is to use this build process to learn new programming
 *   capabilities and put additional pressure on me to improve my standards,
 *   maintenance, and coding environment.  just using programs and ideas does
 *   not lead to understanding -- so get messy ;)
 *
 *   any one who wishes to become a good writer [programmer] should endeavour,
 *   before he allows himself to be tempted by the more showy qualities, to be
 *   direct, simple, brief, vigourous, and lucid -- henry watson fowler (1908)
 *
 *   simplicity is prerequisite for reliability and security
 *
 */
/*============================================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YEXEC_hguard
#define YEXEC_hguard loaded





typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;



#define     YJOBS_CENTRAL  'C'
#define     YJOBS_LOCAL    'L'




/*---(run-as)-----------------------------------*/
#define     IAM_EOS          'e'
#define     IAM_ASTRAIOS     'a'
#define     IAM_HYPNOS       'y'
#define     IAM_HERACLES     'h'
#define     IAM_KHRONOS      'k'
/*---(run-as/unit testing)----------------------*/
#define     IAM_UEOS         'E'
#define     IAM_UASTRAIOS    'A'
#define     IAM_UHYPNOS      'Y'
#define     IAM_UHERACLES    'H'
#define     IAM_UKHRONOS     'K'
/*---(run-as/combination)-----------------------*/
#define     IAM_VALID        "eayhkEAYHK"
#define     IAM_UNIT         "EAYHK"
#define     IAM_ETC          "eayEAY"
/*---(run-as/done)------------------------------*/



/*===[[ ACTIONS ]]=============================*/
/*---(placeholder)----------*/
#define     ACT_NONE        '-'
/*---(simple)---------------*/
#define     ACT_VERSION     '1'
#define     ACT_HELP        '2'
#define     IF_VERSION      if (yJOBS_ifversion () == 1)
#define     IF_HELP         if (yJOBS_ifhelp    () == 1)
/*---(local)----------------*/
#define     ACT_VERIFY      'v'
#define     ACT_VVERIFY     'V'
#define     ACT_CVERIFY     'ÿ'
#define     IF_VERIFY       if (yJOBS_ifverify  () == 1)
#define     CASE_VERIFY     'v' : case 'V' : case 'ÿ'
/*---(incomming)------------*/
#define     ACT_INSTALL     'i'
#define     ACT_VINSTALL    'I'
#define     ACT_CINSTALL    'ð'
#define     IF_INSTALL      if (yJOBS_ifinstall () == 1)
#define     CASE_INSTALL    'i' : case 'I' : case 'ð'
/*---(central/inventory)----*/
#define     ACT_COUNT       'l'
#define     ACT_LIST        'L'
#define     IF_LIST         if (yJOBS_iflist    () == 1)
#define     CASE_LIST       'l' : case 'L'
/*---(central/installed)----*/
#define     ACT_CHECK       'c'
#define     ACT_VCHECK      'C'
#define     ACT_CCHECK      'ý'
#define     IF_CHECK        if (yJOBS_ifcheck   () == 1)
#define     CASE_CHECK      'c' : case 'C' : case 'ý'
/*---(central/security)-----*/
#define     ACT_AUDIT       'a'
#define     ACT_VAUDIT      'A'
#define     ACT_CAUDIT      'è'
#define     IF_AUDIT        if (yJOBS_ifaudit   () == 1)
#define     CASE_AUDIT      'a' : case 'A' : case 'è'
/*---(central/fix)----------*/
#define     ACT_FIX         'f'
#define     ACT_VFIX        'F'
#define     ACT_CFIX        'ü'
#define     IF_FIX          if (yJOBS_iffix     () == 1)
#define     CASE_FIX        'f' : case 'F' : case 'ü'
/*---(outgoing)-------------*/
#define     ACT_REMOVE      'r'
#define     ACT_VREMOVE     'R'
#define     ACT_CREMOVE     'ø'
#define     IF_REMOVE       if (yJOBS_ifremove  () == 1)
#define     CASE_REMOVE     'r' : case 'R' : case 'ø'
/*---(pull)-----------------*/
#define     ACT_EXTRACT     'e'
#define     ACT_VEXTRACT    'E'
#define     ACT_CEXTRACT    'ì'
#define     IF_EXTRACT      if (yJOBS_ifextract () == 1)
#define     CASE_EXTRACT    'e' : case 'E' : case 'ì'
/*---(daemon)---------------*/
#define     ACT_RELOAD      'H'
#define     ACT_DAEMON      'd'
#define     ACT_VDAEMON     'D'
#define     ACT_CDAEMON     'ë'
#define     IF_DAEMON       if (yJOBS_ifdaemon  () == 1)
#define     CASE_DAEMON     'd' : case 'D' : case 'ë'
/*---(prickly daemon)-------*/
#define     ACT_PRICKLY     'p'
#define     ACT_VPRICKLY    'P'
#define     ACT_CPRICKLY    '÷'
#define     IF_PRICKLY      if (yJOBS_ifprickly () == 1)
#define     CASE_PRICKLY    'p' : case 'P' : case '÷'
/*---(normal)---------------*/
#define     ACT_NORMAL      'n'
#define     ACT_VNORMAL     'N'
#define     ACT_CNORMAL     'ô'
#define     IF_NORMAL       if (yJOBS_ifnormal  () == 1)
#define     CASE_NORMAL     'n' : case 'N' : case 'ô'
/*---(combination)----------*/
#define     IF_SILENT       if (yJOBS_ifsilent  () == 1)
#define     IF_VERBOSE      if (yJOBS_ifverbose () == 1)
#define     IF_CONFIRM      if (yJOBS_ifconfirm () == 1)
/*---(combination)----------*/
#define     IF_CCHECK       if (a_act == ACT_CCHECK)
#define     IF_VCHECK       if (a_act == ACT_VCHECK)
#define     IF_CREVIEW      if (a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL)
#define     IF_VREVIEW      if (a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL)
#define     IF_CCENTRAL     if (a_act == ACT_CCHECK  || a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON  || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL)
#define     IF_VCENTRAL     if (a_act == ACT_VCHECK  || a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON  || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL)
/*---(unit testing)---------*/
#define     IF_NORUN        if (yJOBS_ifnorun   () == 1)






/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yJOBS_version           (void);
char        yJOBS_iam               (char a_iam , char *a_print);
char        yJOBS_mode              (char a_mode, char *a_print);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(local)----------------*/
char        yJOBS_acceptable_full   (cchar a_runas, cchar *a_home, cchar *a_root, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
char        yJOBS_local_dir         (cchar a_runas, char *a_root, char *a_home);
char        yJOBS_acceptable        (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
/*---(central)--------------*/
char        yJOBS_central_full      (cchar a_runas, cchar *a_central, cchar *a_name, cchar *a_muser, int a_muid, char *r_fuser, int *r_fuid, char *r_fdesc);
char        yJOBS_central_dir       (cchar a_runas, cchar *a_name, char *a_dir, char *a_user, char *a_file);
char        yJOBS_central           (cchar a_runas, cchar *a_name, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_dir);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(local)----------------*/
char        yJOBS_act_verify        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
char        yJOBS_act_install       (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
/*---(central)--------------*/
char        yJOBS_act_check         (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
char        yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name);
char        yJOBS_act_extract       (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name);
/*---(security)-------------*/
char        yJOBS_act_security      (cchar a_runas, cchar a_act, cchar *a_oneline);
char        yJOBS_act_fix           (cchar a_runas, cchar a_act, cchar *a_oneline);
/*---(review)---------------*/
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate);
/*---(done)-----------------*/


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(arguments)------------*/
char        yJOBS_args_handle       (char *a_runas, char *a_runmode, char *a_runfile, int *i, char *a_arg, char *a_next);
char        yJOBS_final             (int a_uid);
/*---(checkers)-------------*/
char        yJOBS_ifsilent          (void);
char        yJOBS_ifverbose         (void);
char        yJOBS_ifconfirm         (void);
char        yJOBS_ifverify          (void);
char        yJOBS_ifinstall         (void);
char        yJOBS_iflist            (void);
char        yJOBS_ifcheck           (void);
char        yJOBS_ifremove          (void);
char        yJOBS_ifextract         (void);
char        yJOBS_ifaudit           (void);
char        yJOBS_iffix             (void);
char        yJOBS_ifdaemon          (void);
char        yJOBS_ifprickly         (void);
char        yJOBS_ifnormal          (void);
char        yJOBS_ifnorun           (void);
/*---(done)-----------------*/







#endif
/*============================----end-of-source---============================*/
