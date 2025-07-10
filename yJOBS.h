#ifndef YJOBS_hguard
#define YJOBS_hguard loaded


#include    <ySTR_solo.h>

typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;



#define     YJOBS_CENTRAL  'C'
#define     YJOBS_LOCAL    'L'
#define     YJOBS_NEITHER  '-'



/*---(standard recturn codes)-------------------*/
#define     RC_ACK          0
#define     RC_POSITIVE     1
#define     RC_OVERRIDE     2
#define     RC_REPAIR       3
#define     RC_WARNING      4
#define     RC_FATAL        5



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
#define     IAM_GREGG        'g'
#define     IAM_OUROBOROS    'o'
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
#define     IAM_UGREGG       'G'
#define     IAM_UOUROBOROS   'O'
/*---(run-as for actions)-----------------------*/
#define     IAM_DEFAULT      '-'
#define     IAM_VERIFY       "eayhkpmEAYHKPM"
#define     IAM_INSTALL      "eayhkpmEAYHKPM"
#define     IAM_CHECK        "eayhkgEAYHKG"
#define     IAM_FILES        "eayhkmEAYHKM"
#define     IAM_DIRS         "pmoPMO"
/*---(run-as/done)------------------------------*/




/*===[[ ACTIONS ]]=============================*/
/*---(placeholder)----------*/
#define     ACT_NONE        '-'

/*---(simple)---------------*/
#define     ACT_VERSION     '1'
#define     ACT_ABOUT       '2'
#define     ACT_HELP        '3'
#define     IF_VERSION      if (yJOBS_ifversion  () == 1)
#define     IF_HELP         if (yJOBS_ifhelp     () == 1)
#define     CASE_ABOUT      '2'
#define     INDEX_VERSION    0
#define     INDEX_ABOUT      1
#define     INDEX_HELP       2

/*---(local verify)---------*/
#define     ACT_VERIFY      'v'
#define     ACT_CVERIFY     'Ñ'
#define     ACT_VVERIFY     'V'
#define     IF_VERIFY       if (yJOBS_ifverify   () == 1)
#define     CASE_VERIFY     'v' : case 'V' : case 'Ñ'
#define     INDEX_VERIFY     4

/*---(local report)---------*/
#define     ACT_LOCALRPT    'l'
#define     ACT_CLOCALRPT   'ò'
#define     ACT_VLOCALRPT   'L'
#define     IF_LOCALRPT     if (yJOBS_iflocalrpt () == 1)
#define     CASE_LOCALRPT   'l' : case 'L' : case 'ò'
#define     INDEX_LOCAL      5

/*---(local register)-------*/
#define     ACT_REGISTER    'b'
#define     ACT_CREGISTER   'é'
#define     ACT_VREGISTER   'B'
#define     IF_REGISTER     if (yJOBS_ifregister () == 1)
#define     CASE_REGISTER   'b' : case 'é' : case 'B'
#define     INDEX_REGISTER   6

/*---(local update)---------*/
#define     ACT_UPDATE      'u'
#define     ACT_CUPDATE     'û'
#define     ACT_VUPDATE     'U'
#define     IF_UPDATE       if (yJOBS_ifupdate   () == 1)
#define     CASE_UPDATE     'u' : case 'U' : case 'û'
#define     INDEX_UPDATE     7

/*---(local install)--------*/
#define     ACT_INSTALL     'i'
#define     ACT_CINSTALL    'ð'
#define     ACT_VINSTALL    'I'
#define     IF_INSTALL      if (yJOBS_ifinstall  () == 1)
#define     CASE_INSTALL    'i' : case 'I' : case 'ð'
#define     INDEX_INSTALL    8

/*---(central stats)--------*/
#define     ACT_STATS       '#'
#define     IF_STATS        if (yJOBS_ifstats   () == 1)
#define     CASE_STATS      '#' 
#define     INDEX_STATS     10

/*---(central list)---------*/
#define     ACT_LIST        '='
#define     IF_LIST         if (yJOBS_iflist    () == 1)
#define     CASE_LIST       '=' 
#define     INDEX_LIST      11

/*---(central reporting)----*/
#define     ACT_REPORT      'm'
#define     ACT_CREPORT     'ó'
#define     ACT_VREPORT     'M'
#define     IF_RERORT       if (yJOBS_ifreport  () == 1)
#define     CASE_REPORT     'm' : case 'M' : case 'ó'
#define     INDEX_REPORT    12

/*---(central check)--------*/
#define     ACT_CHECK       'c'
#define     ACT_CCHECK      'ý'
#define     ACT_VCHECK      'C'
#define     IF_CHECK        if (yJOBS_ifcheck   () == 1)
#define     CASE_CHECK      'c' : case 'C' : case 'ý'
#define     INDEX_CHECK     13

/*---(central security)-----*/
#define     ACT_AUDIT       'a'
#define     ACT_CAUDIT      'è'
#define     ACT_VAUDIT      'A'
#define     IF_AUDIT        if (yJOBS_ifaudit   () == 1)
#define     CASE_AUDIT      'a' : case 'A' : case 'è'
#define     INDEX_AUDIT     14

/*---(central fix)----------*/
#define     ACT_FIX         'f'
#define     ACT_CFIX        'ü'
#define     ACT_VFIX        'F'
#define     IF_FIX          if (yJOBS_iffix     () == 1)
#define     CASE_FIX        'f' : case 'F' : case 'ü'
#define     INDEX_FIX       15

/*---(central use)----------*/
#define     ACT_ONLY        'o'
#define     ACT_CONLY       'ö'
#define     ACT_VONLY       'O'
#define     IF_ONLY         if (yJOBS_ifonly    () == 1)
#define     CASE_ONLY       'o' : case 'O' : case 'ö'
#define     INDEX_ONLY      16

/*---(FUTURE)---------------*/
#define     INDEX_BACKUP    18
#define     INDEX_RESTORE   19
#define     INDEX_PURGE     20

/*---(cloud upload)---------*/
#define     ACT_UPLOAD      'y'
#define     ACT_CUPLOAD     'ï'
#define     ACT_VUPLOAD     'Y'
#define     IF_UPLOAD       if (yJOBS_ifupload  () == 1)
#define     CASE_UPLOAD     'y' : case 'Y' : case 'ï'
#define     INDEX_UPLOAD    22

/*---(cloud download)-------*/
#define     ACT_DOWNLOAD    'z'
#define     ACT_CDOWNLOAD   'í'
#define     ACT_VDOWNLOAD   'Z'
#define     IF_DOWNLOAD     if (yJOBS_ifdownload() == 1)
#define     CASE_DOWNLOAD   'z' : case 'Z' : case 'í'
#define     INDEX_DOWNLOAD  23

/*---(out withdraw)---------*/
#define     ACT_WITHDRAW    'q'
#define     ACT_CWITHDRAW   'þ'
#define     ACT_VWITHDRAW   'Q'
#define     IF_WITHDRAW     if (yJOBS_ifwithdraw() == 1)
#define     CASE_WITHDRAW   'q' : case 'þ' : case 'Q'
#define     INDEX_WITHDRAW  25

/*---(out clear)------------*/
#define     ACT_CLEAR       'x'
#define     ACT_CCLEAR      'õ'
#define     ACT_VCLEAR      'X'
#define     IF_CLEAR        if (yJOBS_ifclear   () == 1)
#define     CASE_CLEAR      'x' : case 'X' : case 'õ'
#define     INDEX_CLEAR     26

/*---(out remove)-----------*/
#define     ACT_REMOVE      'r'
#define     ACT_CREMOVE     'ø'
#define     ACT_VREMOVE     'R'
#define     IF_REMOVE       if (yJOBS_ifremove  () == 1)
#define     CASE_REMOVE     'r' : case 'R' : case 'ø'
#define     INDEX_REMOVE    27

/*---(out pull)-------------*/
#define     ACT_EXTRACT     'e'
#define     ACT_CEXTRACT    'ì'
#define     ACT_VEXTRACT    'E'
#define     IF_EXTRACT      if (yJOBS_ifextract () == 1)
#define     CASE_EXTRACT    'e' : case 'E' : case 'ì'
#define     INDEX_EXTRACT   28

/*---(exec gathre)----------*/
#define     ACT_GATHER      'g'
#define     ACT_CGATHER     'ê'
#define     ACT_VGATHER     'G'
#define     IF_GATHER       if (yJOBS_ifgather  () == 1)
#define     CASE_GATHER     'g' : case 'G' : case 'ê'
#define     INDEX_GATHER    30

/*---(exec daemon)----------*/
#define     ACT_DAEMON      'd'
#define     ACT_CDAEMON     'ë'
#define     ACT_VDAEMON     'D'
#define     IF_DAEMON       if (yJOBS_ifdaemon  () == 1)
#define     CASE_DAEMON     'd' : case 'D' : case 'ë'
#define     INDEX_DAEMON    31

/*---(exec prickly daemon)--*/
#define     ACT_PRICKLY     'p'
#define     ACT_CPRICKLY    '÷'
#define     ACT_VPRICKLY    'P'
#define     IF_PRICKLY      if (yJOBS_ifprickly () == 1)
#define     CASE_PRICKLY    'p' : case 'P' : case '÷'
#define     INDEX_PRICKLY   32

/*---(exec normal)----------*/
#define     ACT_NORMAL      'n'
#define     ACT_CNORMAL     'ô'
#define     ACT_VNORMAL     'N'
#define     IF_NORMAL       if (yJOBS_ifnormal  () == 1)
#define     CASE_NORMAL     'n' : case 'N' : case 'ô'
#define     INDEX_NORMAL    33


/*---(exec strict normal)---*/
#define     ACT_STRICT      's'
#define     ACT_CSTRICT     'ù'
#define     ACT_VSTRICT     'S'
#define     IF_STRICT       if (yJOBS_ifstrict  () == 1)
#define     CASE_STRICT     's' : case 'S' : case 'ù'
#define     INDEX_STRICT    34

/*---(exec reload)----------*/
#define     ACT_RELOAD      'h'
#define     ACT_CRELOAD     'î'
#define     ACT_VRELOAD     'H'
#define     IF_RELOAD       if (yJOBS_ifreload  () == 1)
#define     CASE_RELOAD     'h' : case 'H' : case 'î'
#define     INDEX_RELOAD    35

/*---(combination)----------*/
#define     IF_SILENT       if (yJOBS_ifsilent  () == 1)
#define     IF_VERBOSE      if (yJOBS_ifverbose () == 1)
#define     IF_CONFIRM      if (yJOBS_ifconfirm () == 1)

/*---(combination)----------*/
#define     IF_CENTRAL      if (yJOBS_ifcheck () == 1 || yJOBS_ifaudit () == 1 || yJOBS_ifdaemon () == 1 || yJOBS_ifprickly () == 1 || yJOBS_ifnormal () == 1 || yJOBS_ifstrict () == 1)
#define     IF_CCHECK       if (a_act == ACT_CCHECK)
#define     IF_VCHECK       if (a_act == ACT_VCHECK)
#define     IF_CREVIEW      if (a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL || a_act == ACT_CSTRICT)
#define     IF_VREVIEW      if (a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL || a_act == ACT_VSTRICT)
#define     IF_CCENTRAL     if (a_act == ACT_CCHECK  || a_act == ACT_CAUDIT  || a_act == ACT_CDAEMON  || a_act == ACT_CPRICKLY || a_act == ACT_CNORMAL || a_act == ACT_CSTRICT)
#define     IF_VCENTRAL     if (a_act == ACT_VCHECK  || a_act == ACT_VAUDIT  || a_act == ACT_VDAEMON  || a_act == ACT_VPRICKLY || a_act == ACT_VNORMAL || a_act == ACT_VSTRICT)

/*---(unit testing)---------*/
#define     ACT_TESTING     'j'
#define     INDEX_TESTING   37



#define     IF_RUNNING      if (yJOBS_ifrunning () == 1)
#define     IF_DAEMONY      if (yJOBS_ifdaemony () == 1)
#define     IF_NORUN        if (yJOBS_ifnorun   () == 1)
#define     IF_NOEND        if (yJOBS_ifnoend   () == 1)



#define     YJOBS_READ      'Ô'
#define     YJOBS_STATS     's'
#define     YJOBS_GATHER    'g'
#define     YJOBS_AUDIT     'a'
#define     YJOBS_REPORT    ' '
#define     YJOBS_LOCALRPT  '´'
#define     YJOBS_LOCAL     '´'
#define     YJOBS_EXTRACT   'e'
#define     YJOBS_WRITE     'Õ'
#define     YJOBS_PURGE     'P'

#define     YJOBS_PULL      '×'
#define     YJOBS_CLEAR     'x'
#define     YJOBS_LOCRPT    'l'
#define     YJOBS_PUSH      'Ö'
#define     YJOBS_REGISTER  'r'



/*===[[ BASE USAGE ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yJOBS_version           (void);
char        yJOBS_runas             (char a_name [LEN_TERSE], char *r_runas, ...);
char        yJOBS_noise             (char a_argc, char *a_argv []);
char        yJOBS_argument          (int *b_pos, cchar *a_arg, cchar *a_next, char *r_runas, char *r_mode, char *r_file);
char        yJOBS_driver            (char a_oneline [LEN_HUND], void *f_callback);
char        yJOBS_final             (int a_uid);  /* DEPRICATED */
char        yJOBS_wrap              (void);
char        yJOBS_configured        (char a_runas, char *r_unit, char r_name [LEN_TERSE], char r_desc [LEN_DESC], char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_db [LEN_LABEL], char r_world [LEN_LABEL]);



char        yJOBS_filedata          (char *r_runas, char *r_mode, char *r_floc, char *r_fname, char *r_fuser, int *r_fuid, char *r_fdesc, char *r_fdir, char *r_full);
/*> char        yJOBS_file_audit        (cchar a_path [LEN_HUND], cchar a_file [LEN_HUND]);   <*/


/*===[[ DEBUGGING ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yJOBS_iam               (void);
char*       yJOBS_mode              (void);
/*---(done)-----------------*/
char        yJOBS_mkdirs            (void);
char        yJOBS_rmdirs            (void);



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(local)----------------*/
/*---(central)--------------*/
char        yJOBS_act_check         (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name, void *a_assimilate);
/*> char        yJOBS_act_remove        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name);   <*/
char        yJOBS_act_extract       (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_name);
/*---(security)-------------*/
/*> char        yJOBS_security          (void);                                       <*/
/*> char        yJOBS_fix               (void);                                       <*/
/*---(review)---------------*/
char        yJOBS_act_review        (cchar a_runas, cchar a_act, cchar *a_oneline, cchar *a_muser, int a_muid, cchar *a_regex, void *a_assimilate);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(arguments)------------*/
char        yJOBS_reset             (char *r_runas, char *r_mode, char *r_file);
char        yjobs_args_init         (char *r_runas, char *r_mode, char *r_file);
/*---(runas checkers)-------*/
char        yJOBS_ifvalid           (void);
char        yJOBS_ifunit            (void);
char        yJOBS_ifetc             (void);
/*---(verbosity checkers)---*/
char        yJOBS_ifallmode         (void);
char        yJOBS_ifsilent          (void);
char        yJOBS_ifconfirm         (void);
char        yJOBS_ifverbose         (void);
/*---(support)--------------*/
char        yJOBS_ifhelp            (void);
char        yJOBS_ifversion         (void);
/*---(incomming checkers)---*/
char        yJOBS_ifverify          (void);
char        yJOBS_iflocalrpt        (void);
char        yJOBS_ifregister        (void);
char        yJOBS_ifconfirm         (void);
char        yJOBS_ifinstall         (void);
char        yJOBS_ifupdate          (void);
/*---(central checkers)-----*/
char        yJOBS_ifstats           (void);
char        yJOBS_iflist            (void);
char        yJOBS_ifreport          (void);
char        yJOBS_ifcheck           (void);
char        yJOBS_ifaudit           (void);
char        yJOBS_iffix             (void);
char        yJOBS_ifonly            (void);
/*---(cloud checkers)-------*/
char        yJOBS_ifupload          (void);
char        yJOBS_ifdownload        (void);
/*---(outgoing checkers)----*/
char        yJOBS_ifwithdraw        (void);
char        yJOBS_ifclear           (void);
char        yJOBS_ifremove          (void);
char        yJOBS_ifextract         (void);
/*---(execution checkers)---*/
char        yJOBS_ifgather          (void);
char        yJOBS_ifdaemon          (void);
char        yJOBS_ifprickly         (void);
char        yJOBS_ifnormal          (void);
char        yJOBS_ifstrict          (void);
char        yJOBS_ifreload          (void);
/*---(other checkers)-------*/
char        yJOBS_ifrunning         (void);
char        yJOBS_ifdaemony         (void);
char        yJOBS_ifnorun           (void);
char        yJOBS_ifnoend           (void);
/*---(done)-----------------*/







#endif
/*============================----end-of-source---============================*/
