/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YJOBS_hguard
#define YJOBS_hguard loaded



typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;



#define     YJOBS_CENTRAL  'C'
#define     YJOBS_LOCAL    'L'
#define     YJOBS_NEITHER  '-'




/*---(run-as)-----------------------------------*/
#define     IAM_EOS          'e'
#define     IAM_ASTRAIOS     'a'
#define     IAM_HYPNOS       'y'
#define     IAM_HERACLES     'h'
#define     IAM_KHRONOS      'k'
#define     IAM_POLYMNIA     'p'
#define     IAM_METIS        'm'
#define     IAM_HELIOS       'l'
#define     IAM_HERMES       'r'
#define     IAM_THEMIS       't'
/*---(run-as/unit testing)----------------------*/
#define     IAM_UEOS         'E'
#define     IAM_UASTRAIOS    'A'
#define     IAM_UHYPNOS      'Y'
#define     IAM_UHERACLES    'H'
#define     IAM_UKHRONOS     'K'
#define     IAM_UPOLYMNIA    'P'
#define     IAM_UMETIS       'M'
#define     IAM_UHELIOS      'L'
#define     IAM_UHERMES      'R'
#define     IAM_UTHEMIS      'T'
/*---(run-as for actions)-----------------------*/
#define     IAM_DEFAULT      '-'
#define     IAM_VERIFY       "eayhkpmEAYHKPM"
#define     IAM_INSTALL      "eayhkpmEAYHKPM"
#define     IAM_CHECK        "eayhkEAYHK"
/*---(run-as/done)------------------------------*/



/*===[[ ACTIONS ]]=============================*/
/*---(placeholder)----------*/
#define     ACT_NONE        '-'
/*---(simple)---------------*/
#define     ACT_VERSION     '1'
#define     ACT_HELP        '2'
#define     ACT_STATS       '3'
#define     IF_VERSION      if (yJOBS_ifversion () == 1)
#define     IF_HELP         if (yJOBS_ifhelp    () == 1)
#define     IF_STATS        if (yJOBS_ifstats   () == 1)
/*---(local)----------------*/
#define     ACT_VERIFY      'v'
#define     ACT_VVERIFY     'V'
#define     ACT_CVERIFY     'Ñ'
#define     IF_VERIFY       if (yJOBS_ifverify  () == 1)
#define     CASE_VERIFY     'v' : case 'V' : case 'Ñ'
/*---(local)----------------*/
#define     ACT_REGISTER    'b'
#define     ACT_VREGISTER   'B'
#define     ACT_CREGISTER   'é'
#define     IF_REGISTER     if (yJOBS_ifregister() == 1)
#define     CASE_REGISTER   'b' : case 'é' : case 'B'
/*---(incomming)------------*/
#define     ACT_INSTALL     'i'
#define     ACT_VINSTALL    'I'
#define     ACT_CINSTALL    'ð'
#define     IF_INSTALL      if (yJOBS_ifinstall () == 1)
#define     CASE_INSTALL    'i' : case 'I' : case 'ð'
/*---(incomming)------------*/
#define     ACT_UPDATE      'u'
#define     ACT_VUPDATE     'U'
#define     ACT_CUPDATE     'û'
#define     IF_UPDATE       if (yJOBS_ifupdate  () == 1)
#define     CASE_UPDATE     'u' : case 'U' : case 'û'
/*---(central/inventory)----*/
#define     ACT_COUNT       'l'
#define     ACT_LIST        'L'
#define     IF_LIST         if (yJOBS_iflist    () == 1)
#define     CASE_LIST       'l' : case 'L'
/*---(central/inventory)----*/
#define     ACT_REPORT      'ò'
#define     CASE_REPORT     'ò' 
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
#define     ACT_WITHDRAW    'q'
#define     ACT_VWITHDRAW   'Q'
#define     ACT_CWITHDRAW   'þ'
#define     IF_WITHDRAW     if (yJOBS_ifwithdraw() == 1)
#define     CASE_WITHDRAW   'q' : case 'þ' : case 'Q'
/*---(outgoing)-------------*/
#define     ACT_CLEAR       'x'
#define     ACT_VCLEAR      'X'
#define     ACT_CCLEAR      'õ'
#define     IF_CLEAR        if (yJOBS_ifclear   () == 1)
#define     CASE_CLEAR      'x' : case 'X' : case 'õ'
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
/*---(upload)---------------*/
#define     ACT_UPLOAD      'y'
#define     ACT_VUPLOAD     'Y'
#define     ACT_CUPLOAD     'ï'
#define     IF_UPLOAD       if (yJOBS_ifupload  () == 1)
#define     CASE_UPLOAD     'y' : case 'Y' : case 'ï'
/*---(download)-------------*/
#define     ACT_DOWNLOAD    'z'
#define     ACT_VDOWNLOAD   'Z'
#define     ACT_CDOWNLOAD   'í'
#define     IF_DOWNLOAD     if (yJOBS_ifdownload() == 1)
#define     CASE_DOWNLOAD   'z' : case 'Z' : case 'í'
/*---(gather)---------------*/
#define     ACT_GATHER      'g'
#define     ACT_VGATHER     'G'
#define     ACT_CGATHER     'ê'
#define     IF_GATHER       if (yJOBS_ifgather  () == 1)
#define     CASE_GATHER     'g' : case 'G' : case 'ê'
/*---(daemon)---------------*/
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
/*---(normal)---------------*/
#define     ACT_STRICT      's'
#define     ACT_VSTRICT     'S'
#define     ACT_CSTRICT     'ù'
#define     IF_STRICT       if (yJOBS_ifstrict  () == 1)
#define     CASE_STRICT     's' : case 'S' : case 'ù'
/*---(reload)---------------*/
#define     ACT_RELOAD      'h'
#define     ACT_VRELOAD     'H'
#define     ACT_CRELOAD     'î'
#define     IF_RELOAD       if (yJOBS_ifreload  () == 1)
#define     CASE_RELOAD     'h' : case 'H' : case 'î'
/*---(combination)----------*/
#define     IF_SILENT       if (yJOBS_ifsilent  () == 1)
#define     IF_VERBOSE      if (yJOBS_ifverbose () == 1)
#define     IF_CONFIRM      if (yJOBS_ifconfirm () == 1)
/*---(combination)----------*/
#define     IF_CENTRAL      if (yJOBS_ifcheck () == 1 || yJOBS_ifaudit () == 1 || yJOBS_ifdaemon () == 1 || yJOBS_ifprickly () == 1 || yJOBS_ifnormal () == 1 || yJOBS_ifstrict () == 1)
#define     IF_CCHECK       if (a_act == ACT_CCHECK)
#define     IF_VCHECK       if (a_act == ACT_VCHECK)
#define     IF_CREVIEW      if (a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL)
#define     IF_VREVIEW      if (a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL)
#define     IF_CCENTRAL     if (a_act == ACT_CCHECK  || a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON  || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL)
#define     IF_VCENTRAL     if (a_act == ACT_VCHECK  || a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON  || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL)
/*---(unit testing)---------*/
#define     ACT_TESTING     'j'
#define     IF_NORUN        if (yJOBS_ifnorun   () == 1)
#define     IF_NOEND        if (yJOBS_ifnoend   () == 1)






/*===[[ BASE USAGE ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yJOBS_version           (void);
char        yJOBS_runas             (cchar *a_name, char *r_runas);
char        yJOBS_argument          (int *i, cchar *a_arg, cchar *a_next, char *r_runas, char *r_mode, char *r_file);
char        yJOBS_driver            (char *a_oneline, char *a_user, int a_uid, void *a_assimilate, void *a_runner);
char        yJOBS_wrap              (void);



/*===[[ DEBUGGING ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yJOBS_iam               (void);
char*       yJOBS_mode              (void);
/*---(done)-----------------*/
char        yJOBS_mkdirs            (void);
char        yJOBS_rmdirs            (void);



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
char        yJOBS_security          (cchar *a_oneline);
char        yJOBS_fix               (cchar *a_oneline);
/*---(review)---------------*/
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(arguments)------------*/
char        yJOBS_args_init         (char a_runas, char a_runmode, char *a_runfile);
char        yJOBS_final             (int a_uid);
/*---(checkers)-------------*/
char        yJOBS_ifvalid           (void);
char        yJOBS_ifunit            (void);
char        yJOBS_ifetc             (void);
char        yJOBS_ifsilent          (void);
char        yJOBS_ifverbose         (void);
char        yJOBS_ifregister        (void);
char        yJOBS_ifconfirm         (void);
char        yJOBS_ifverify          (void);
char        yJOBS_ifinstall         (void);
char        yJOBS_iflist            (void);
char        yJOBS_ifcheck           (void);
char        yJOBS_ifclear           (void);
char        yJOBS_ifremove          (void);
char        yJOBS_ifextract         (void);
char        yJOBS_ifaudit           (void);
char        yJOBS_iffix             (void);
char        yJOBS_ifwithdraw        (void);
char        yJOBS_ifupload          (void);
char        yJOBS_ifdownload        (void);
char        yJOBS_ifgather          (void);
char        yJOBS_ifdaemon          (void);
char        yJOBS_ifprickly         (void);
char        yJOBS_ifnormal          (void);
char        yJOBS_ifstrict          (void);
char        yJOBS_ifreload          (void);
char        yJOBS_ifnorun           (void);
char        yJOBS_ifnoend           (void);
/*---(done)-----------------*/







#endif
/*============================----end-of-source---============================*/
