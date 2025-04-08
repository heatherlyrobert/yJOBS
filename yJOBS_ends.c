/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"


/*
 * METIS § dv4·· § maintain audit shuold set all central files owner and perms            § N9Q5G9 §  · §
 *
 */

/*
 *  0         1         2         3         4         5         6         7         8
 *  -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
 *  hl············································································· ··prepare    : header and location lookup
 *      SEáafcd······································································ security   : audit overall security, fixed security
 *               DBásaÔ#óÕ··························································· database   : purge all data, read db, statistics, db reporting, write db
 *                          LOálÖò··················································· local file : audit file secure local, pull file, move to central, read all files, remove central file
 *                                  WOásaeÔ=rÕ······································· world file : audit world security, check entry, load world, report, register/withdrawl, save world
 *                                              CEáamÖr×=x··························· central    : move local to central, audit security of central file, pull one central file, pull all central files, clear one central file, list central files, remove central file
 *                                                          ACágnd··················· actions    : gather, normal/strict, daemon/prickly
 *                                                                  BEásaEUBDR······· backend    : extract file, upload, backup, download, restore
 *                                                                              fy··· wrapup     : footer and yes=pass/°=fail
 */


char    g_acts_score    [LEN_HUND]  = "                                                                        ";

char    g_fullacts      [LEN_DESC]  = "hl aÔÕ lcÖ òmr #=ó WRf BRP UD ×we fF";

const static tENV_SCORE s_scores [LEN_FULL] = {
   /*===[[ PREPARE ]]=======================================================*/
   { "HEá "     , ' ' ,  0  , "HEAD"     , ""                                 , ""                                                                                },
   { "RUNAS"    , '·' , 'e' , "runas"    , "host_program calling yjobs"       , "e) eos       k) khronos   p) polymnia   ..."                                     },
   { "ENV"      , '·' , 'u' , "env"      , "run-time environment"             , "·) normal    d) debug     u) unit-test"                                          },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "MODE"     , '·' , 'v' , "mode"     , "yjobs action requested"           , "v) verify    g) gather    d) daemon     ..."                                     },
   { "NOISE"    , '·' , '!' , "noise"    , "verbosity of feedback"            , "-) silent    c) confirm   !) verbose"                                            },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "ONE"      , '·' , 'o' , "onelin"   , "runas oneline desc"               , "°) failed    o) given"                                                           },
   { "CALL"     , '·' , '&' , "callbk"   , "yjobs file provided"              , "°) null      c) given"                                                           },
   { "FILE"     , '·' , 'f' , "file"     , "yjobs file provided"              , "-) n/a       f) required"                                                        },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "RUSER"    , '·' , 'u' , "ruser"    , "run-time user data"               , "°) failed    u) gathered"                                                        },
   { "HEADER"   , '·' , 'h' , "header"   , "printing of the title lines"      , "°) failed    -) skipped   h) header"                                             },
   { "LOCS"     , '·' , 'l' , "locs"     , "default location lookup"          , "°) failed    l) locs"                                                            },
   { "CWD"      , '·' , '¤' , "cwd"      , "current working directory"        , "°) failed    ¤) cwd"                                                             },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ PREPARE ]]=======================================================*/
   { "SEá "     , ' ' ,  0  , "SEC"      , ""                                 , ""                                                                                },
   { "SSECURE"  , '·' , 's' , "secure"   , "general security"                 , ""                                                                                },
   { "SFIX"     , '·' , 'f' , "fix"      , "adding fix to the audit"          , ""                                                                                },
   { "SAUDIT"   , '·' , 'a' , "audit"    , "general audit"                    , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ LOCAL ]]=========================================================*/
   { "LOá "     , ' ' ,  0  , "LOCAL"    , ""                                 , ""                                                                                },
   { "LTYPE"    , '·' , 'd' , "type"     , "type of entry"                    , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "LSECURE"  , '·' , 's' , "secure"   , "security on file/directory"       , ""                                                                                },
   { "LAUDIT"   , '·' , 'a' , "audit"    , "audit local file by pulling"      , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "LPULL"    , '·' , 'Ö' , "pull"     , "pull file in"                     , ""                                                                                },
   { "LREPORT"  , '·' , 'ò' , "report"   , "local report"                     , ""                                                                                },
   { "LMOVE"    , '·' , 'm' , "move"     , "move local to central"            , ""                                                                                },
   { "LREG"     , '·' , 'r' , "regist"   , "register in world"                , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "LWITH"    , '·' , 'w' , "withdr"   , "withdraw from world"              , ""                                                                                },
   { "LREMOVE"  , '·' , 'x' , "remove"   , "remove central file"              , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ CONFIG ]]========================================================*/
   { "CFá "     , ' ' ,  0  , "CONF"     , ""                                 , ""                                                                                },
   { "FSTYLE"   , '·' , 'e' , "style"    , "config location type"             , "e) etc       s) spool"                                                           },
   { "FCOUNT"   , '·' , '1' , "count"    , "count of config files"            , "1) single    *) multiple"                                                        },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "FDSEC"    , '·' , 's' , "secure"   , "configuration dir security"       , ""                                                                                },
   { "FDFIX"    , '·' , 'f' , "dfix"     , "configuration dir fix"            , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "FFSEC"    , '·' , 's' , "secure"   , "configuration files secure"       , ""                                                                                },
   { "FFFIX"    , '·' , 'f' , "fix"      , "configuration files fix"          , ""                                                                                },
   { "FAUDIT"   , '·' , 'a' , "audit"    , "configuration files audit"        , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "FONLY"    , '·' , 'Ö' , "only"     , "pull/load central file"           , ""                                                                                },
   { "FEVERY"   , '·' , 'e' , "every"    , "pull/load all central files"      , ""                                                                                },
   { "FPURGE"   , '·' , 'p' , "purge"    , "do not retain data after pull"    , ""                                                                                },
   { "FLIST"    , '·' , '=' , "list"     , "list central files"               , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ CENTRAL ]]=======================================================*/
   { "CDá "     , ' ' ,  0  , "CEN"      , ""                                 , ""                                                                                },
   { "CSECURE"  , '·' , 's' , "secure"   , "central data dir security"        , ""                                                                                },
   { "CFIX"     , '·' , 'f' , "fix"      , "configuration dir fix"            , ""                                                                                },
   { "CAUDIT"   , '·' , 'a' , "audit"    , "file contents audit"              , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ DATABASE ]]======================================================*/
   { "DBá "     , ' ' ,  0  , "DATABASE" , ""                                 , ""                                                                                },
   { "DSECURE"  , '·' , 's' , "secure"   , "database security"                , "°) non-exist s) secure"                                                          },
   { "DFIX"     , '·' , 'f' , "fix"      , "database fix"                     , "°) couldn't  -) n/a       f) fixed"                                                           },
   { "DAUDIT"   , '·' , 'a' , "audit"    , "database contents audit"          , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "DREAD"    , '·' , 'Ô' , "read"     , "read database"                    , "°) failed    Ô) read"                                                            },
   { "DPURGE"   , '·' , 'p' , "purge"    , "do not retain data after read"    , "°) failed    p) purge"                                                           },
   { "DSTATS"   , '·' , '#' , "stats"    , "database statistics"              , "°) failed    #) passed"                                                          },
   { "DREPORT"  , '·' , 'ó' , "report"   , "database reporting"               , "°) failed    ó) passed"                                                          },
   { "DCLEAR"   , '·' , 'x' , "clear"    , "clear specific data"              , "°) failed    x) clear"                                                           },
   { "DWRITE"   , '·' , 'Õ' , "write"    , "write database"                   , "°) failed    a) audit     Õ) written"                                            },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ WORLD ]]=========================================================*/
   { "WOá "     , ' ' ,  0  , "WORLD"    , ""                                 , ""                                                                                },
   { "WSECURE"  , '·' , 's' , "secure"   , "world file security"              }, /* s) secure, a) audited content, -) skipped    , ""                                                                                */
   { "WFIX"     , '·' , 'f' , "fix"      , "world file fix"                   , ""                                                                                },
   { "WAUDIT"   , '·' , 'a' , "audit"    , "world contents audit"             , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "WENTRY"   , '·' , 'e' , "entry"    , "requested entry check"            }, /* f) file, d) directory, -) skipped , ""                                                                                */
   { "WREAD"    , '·' , 'Ô' , "read"     , "read/import world file"           , ""                                                                                },
   { "WLIST"    , '·' , '=' , "list"     , "reporting on world file"          , ""                                                                                },
   { "WWRITE"   , '·' , 'Õ' , "write"    , "write/export world file"          , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ ACTION ]]========================================================*/
   { "ACá "     , ' ' ,  0  , "ACT"      , ""                                 , ""                                                                                },
   { "GATHER"   , '·' , 'g' , "gather"   , "gather local files"               , ""                                                                                },
   { "NORMAL"   , '·' , 'n' , "normal"   , "normal/strict mode"               , ""                                                                                },
   { "DAEMON"   , '·' , 'd' , "daemon"   , "daemon/prickly mode"              , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ BACKEND ]]=======================================================*/
   { "BEá "     , ' ' ,  0  , "BACKEND"  , ""                                 , ""                                                                                },
   { "BSECURE"  , '·' , 's' , "secure"   , "backend security"                 , ""                                                                                },
   { "BFIX"     , '·' , 'f' , "fix"      , "backend fix"                      , ""                                                                                },
   { "BAUDIT"   , '·' , 'a' , "audit"    , "audit of backend"                 , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "EXTRACT"  , '·' , 'E' , "extrct"   , "extract a central file"           , ""                                                                                },
   { "UPLOAD"   , '·' , 'U' , "upload"   , "upload a central file"            , ""                                                                                },
   { "BACKUP"   , '·' , 'B' , "backup"   , "backup a central file"            , ""                                                                                },
   { "DOWNLOAD" , '·' , 'D' , "dwload"   , "download a central file"          , ""                                                                                },
   { "RESTORE"  , '·' , 'R' , "restor"   , "restore a central file"           , ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""                                                                                },
   /*===[[ JUDGEMENT ]]=====================================================*/
   { "JDá "     , ' ' ,  0  , "³"        , ""                                 , ""                                                                                },
   { "FOOTER"   , '·' , 'f' , "footer"   , "print footer on output"           , ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""                                                                                },
   { "JUDGE"    , ' ' , 'Ï' , "judge"    , "final judgement"                  , ""                                                                                },
   /*===[[ END-OF-LIST ]]===================================================*/
   { "end-list" , '·' , '·' , ""         , "end-of-entries"                   , ""                                                                                },
   /*===[[ DONE ]]==========================================================*/
};


/*> static struct {                                                                                                                                                     <* 
 *>    char        s_pos;                                                                                                                                               <* 
 *>    char        s_label     [LEN_TERSE];                                                                                                                             <* 
 *>    char        s_sample;                                                                                                                                            <* 
 *>    uchar       s_valid     [LEN_TERSE];                                                                                                                             <* 
 *>    char        s_print     [LEN_LABEL];                                                                                                                             <* 
 *>    char        s_desc      [LEN_DESC];                                                                                                                              <* 
 *> } s_scores [LEN_HUND] = {                                                                                                                                           <* 
 *>    /+===[[ PREPARE ]]=======================================================+/                                                                                      <* 
 *>    {  0, "HEADER"          , 'h' , "°h-·"    , "header"          , "printing of the title lines"      },                                                            <* 
 *>    {  0, "LOCS"            , 'l' , "°l·"     , "locs"            , "default location lookup"          },                                                            <* 
 *>    {  0, "CWD"             , '¤' , "°¤·"     , "cwd"             , "current working directory"        },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ PREPARE ]]=======================================================+/                                                                                      <* 
 *>    {  0, "SEá"             ,  0  , ""        , "SECURE-"         , ""                                 },                                                            <* 
 *>    {  0, "SAUDIT"          , 'a' , "°a-·"    , "audit"           , "general security audit"           },                                                            <* 
 *>    {  0, "SFIX"            , 'f' , "°fF-·"   , "fix"             , "adding fix to the audit"          },                                                            <* 
 *>    {  0, "SCONF"           , 'c' , "°cF-·"   , "conf"            , "configuration dir security"       },                                                            <* 
 *>    {  0, "SDATA"           , 'd' , "°dF-·"   , "data"            , "central data dir security"        },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ DATABASE ]]======================================================+/                                                                                      <* 
 *>    {  0, "DBá"             ,  0  , ""        , "DATABASE---"       ""                                 },                                                            <* 
 *>    {  0, "DSECURE"         , 's' , "°s--·"   , "secure"          , "database security"                }, /+ s) secure, a) audited content, -) skipped +/            <* 
 *>    {  0, "DAUDIT"          , 'a' , "°a--·"   , "audit"           , "database contents audit"          },                                                            <* 
 *>    {  0, "DREAD"           , 'Ô' , "°Ô-·"    , "read"            , "read database"                    },                                                            <* 
 *>    {  0, "DSTATS"          , '#' , "°#·"     , "stats"           , "database statistics"              },                                                            <* 
 *>    {  0, "DREPORT"         , 'ó' , "°ó·"     , "report"          , "database reporting"               },                                                            <* 
 *>    {  0, "DWRITE"          , 'Õ' , "°Õ-·"    , "write"           , "write database"                   },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ LOCAL ]]=========================================================+/                                                                                      <* 
 *>    {  0, "LOá"             ,  0  , ""        , "LOCAL"           , ""                                 },                                                            <* 
 *>    {  0, "LSECURE"         , 'd' , "°dl·"    , "secure"          , "security on file/directory"       },                                                            <* 
 *>    {  0, "LAUDIT"          , 'Ö' , "°Ö·"     , "audit"           , "audit local file by pulling"      },                                                            <* 
 *>    {  0, "LREPORT"         , 'ò' , "°ò·"     , "report"          , "local report"                     },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ WORLD ]]=========================================================+/                                                                                      <* 
 *>    {  0, "WOá"             ,  0  , ""        , "WORLD--------"   , ""                                 },                                                            <* 
 *>    {  0, "WSECURE"         , 's' , "°s-·"    , "secure"          , "world file security"              }, /+ s) secure, a) audited content, -) skipped    +/         <* 
 *>    {  0, "WAUDIT"          , 'a' , "°a-·"    , "audit"           , "world contents audit"             },                                                            <* 
 *>    {  0, "WENTRY"          , 'e' , "°fd-·"   , "entry"           , "requested entry check"            }, /+ f) file, d) directory, -) skipped +/                    <* 
 *>    {  0, "WREAD"           , 'Ô' , "°Ô-·"    , "read"            , "read/import world file"           },                                                            <* 
 *>    {  0, "WLIST"           , '=' , "°=-·"    , "list"            , "reporting"                        },                                                            <* 
 *>    {  0, "WUPDATE"         , 'r' , "°ruD-·"  , "update"          , "register or withdraw"             }, /+ r) register, u) withdraw, D) duplicate, -) skipped +/   <* 
 *>    {  0, "WWRITE"          , 'Õ' , "°Õ-·"    , "write"           , "write/export world file"          },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ CENTRAL ]]=======================================================+/                                                                                      <* 
 *>    {  0, "CEá"             ,  0  , ""        , "CENTRAL------"   , ""                                 },                                                            <* 
 *>    {  0, "CAUDIT"          , 'a' , "°a-·"    , "audit"           , "file contents audit"              },                                                            <* 
 *>    {  0, "CMOVE"           , 'm' , "°m-·"    , "move"            , "move local to central"            },                                                            <* 
 *>    {  0, "CPULL"           , 'Ö' , "°Ö-·"    , "pull"            , "pull/load central config"         },                                                            <* 
 *>    {  0, "CREAD"           , 'r' , "°rR-·"   , "read"            , "read all central files"           },                                                            <* 
 *>    {  0, "CCLEAR"          , 'x' , "°x-·"    , "clear"           , "clear specific data from db"      },                                                            <* 
 *>    {  0, "CLIST"           , '=' , "°=·"     , "list"            , "list central files"               },                                                            <* 
 *>    {  0, "CREMOVE"         , 'X' , "°X-·"    , "remove"          , "remove central file"              },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ ACTION ]]========================================================+/                                                                                      <* 
 *>    {  0, "ACá"             ,  0  , ""        , "ACTS-"           , ""                                 },                                                            <* 
 *>    {  0, "GATHER"          , 'g' , "°g·"     , "gather"          , "gather local files"               },                                                            <* 
 *>    {  0, "NORMAL"          , 'n' , "°n·"     , "normal"          , "normal/strict mode"               },                                                            <* 
 *>    {  0, "DAEMON"          , 'd' , "°d·"     , "daemon"          , "daemon/prickly mode"              },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ BACKEND ]]=======================================================+/                                                                                      <* 
 *>    {  0, "BEá"             ,  0  , ""        , "BACKEND------"   , ""                                 },                                                            <* 
 *>    {  0, "BSECURE"         , 's' , "°s-·"    , "secure"          , "backend security"                 },                                                            <* 
 *>    {  0, "BAUDIT"          , 'a' , "°a-·"    , "audit"           , "audit of backend"                 },                                                            <* 
 *>    {  0, "EXTRACT"         , 'E' , "°E-·"    , "extrct"          , "extract a central file"           },                                                            <* 
 *>    {  0, "UPLOAD"          , 'U' , "°U-·"    , "upload"          , "upload a central file"            },                                                            <* 
 *>    {  0, "BACKUP"          , 'B' , "°B-·"    , "backup"          , "backup a central file"            },                                                            <* 
 *>    {  0, "DOWNLOAD"        , 'D' , "°D-·"    , "dwload"          , "download a central file"          },                                                            <* 
 *>    {  0, "RESTORE"         , 'R' , "°R-·"    , "restor"          , "restore a central file"           },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <* 
 *>    /+===[[ JUDGEMENT ]]=====================================================+/                                                                                      <* 
 *>    {  0, "FOOTER"          , 'f' , "°f-·"    , "footer"          , "print footer on output"           },                                                            <* 
 *>    {  0, "JUDGE"           , 'y' , "°y!·"    , "judge"           , "final judgement"                  },                                                            <* 
 *>    /+===[[ END-OF-LIST ]]===================================================+/                                                                                      <* 
 *>    { -1, "end-of-list"     , '·' , ""        , ""                , "end-of-entries"                   },                                                            <* 
 *>    /+===[[ DONE ]]==========================================================+/                                                                                      <* 
 *> };                                                                                                                                                                  <*/



/*====================------------------------------------====================*/
/*===----                           scoring                            ----===*/
/*====================------------------------------------====================*/
static void      o___SCORE_________o (void) {;};

char
yjobs_ends_init         (void)
{
   char          rce       =  -10;
   char          rc        =    0;
   rc = yENV_score_init  (s_scores);
   --rce;  if (rc < 0)  return rce;
   rc = yENV_score_clear ();
   --rce;  if (rc < 0)  return rce;
   return 0;
}


/*====================------------------------------------====================*/
/*===----                          topmost                             ----===*/
/*====================------------------------------------====================*/
static void      o___HEADER________o (void) {;};

char
yjobs_ends__titles      (char a_runas, char a_mode, char a_oneline [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yENV_score_mark ("HEADER"   , G_SCORE_FAIL);
   yENV_score_mark ("NOISE"    , G_SCORE_SKIP);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      yjobs_ends_failure (a_mode, "", "called with NULL mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      yjobs_ends_failure (a_mode, "", "called with an invalid mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_verbose" , g_verbose);
   if (strchr (g_verbose , a_mode) == NULL) {
      yENV_score_mark ("HEADER"   , G_SCORE_SKIP);
      if (strchr (g_confirm , a_mode) != NULL) yENV_score_mark ("NOISE"    , 'c');
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   yENV_score_mark ("NOISE"    , '!');
   /*---(pre-header)---------------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yjobs_ends_failure (a_mode, "", "called with NULL/empty oneline");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   yURG_msg (':', "%s", a_oneline);
   /*---(actual header)------------------*/
   --rce;  switch (a_mode) {     /*---(incomming 5)-----------------*/
   case CASE_VERIFY   :  yURG_msg (':', "  option --vverify   : check details, but not register, update, or install");    break;
   case CASE_LOCALRPT :  yURG_msg (':', "  option --vlocal    : verify and perform a specific report on local data");     break;
   case CASE_REGISTER :  yURG_msg (':', "  option --vregister : verify and add to world, but not update or install");     break;
   case CASE_UPDATE   :  yURG_msg (':', "  option --vupdate   : verify and update global, but not register");             break;
   case CASE_INSTALL  :  yURG_msg (':', "  option --vinstall  : complete intake of verification, update, and registration"); break;
                         /*---(maintain 6)------------------*/
   case CASE_STATS    :  break;  /* no verbose option */
   case CASE_LIST     :  break;  /* no verbose option */
   case CASE_REPORT   :  yURG_msg (':', "  option --vreport   : search, process, or report from central information");    break;
   case CASE_CHECK    :  yURG_msg (':', "  option --vcheck    : verify details of centrally installed file");             break;
   case CASE_AUDIT    :  yURG_msg (':', "  option --vaudit    : check central setup, files, and security");               break;
   case CASE_FIX      :  yURG_msg (':', "  option --vfix      : check and repair central setup, files, and security");    break;
   case CASE_ONLY     :  yURG_msg (':', "  option --vonly     : execute with single central file");                       break;
                         /*---(epic 3)----------------------*/
                         /*---(elsewhere 2)-----------------*/
                         /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW :  yURG_msg (':', "  option --vwithdraw : remove from world, but not contents/file from central");  break;
   case CASE_CLEAR    :  yURG_msg (':', "  option --vclear    : remove contents/file from central, but not world");       break;
   case CASE_REMOVE   :  yURG_msg (':', "  option --vremove   : remove both from central contents and world");            break;
   case CASE_EXTRACT  :  yURG_msg (':', "  option --vextract  : make a local copy of a central file/entry");              break;
                         /*---(execution 6)-----------------*/
   case CASE_GATHER   :  yURG_msg (':', "  option --vgather   : verify and update all entries from world file");          break;
   case CASE_DAEMON   :  yURG_msg (':', "  option --vdaemon   : verbosely launch in background daemon mode");             break;
   case CASE_PRICKLY  :  yURG_msg (':', "  option --vprickly  : verbosely launch in prickly daemon mode");                break;
   case CASE_NORMAL   :  yURG_msg (':', "  option --vnormal   : verbosely launch in normal/non-daemon mode");             break;
   case CASE_STRICT   :  yURG_msg (':', "  option --vstrict   : verbosely launch in strict normal/non-daemon mode");      break;

   default            :
                         yjobs_ends_failure (a_mode, "", "called with an unrecognized mode");
                         DEBUG_YJOBS   yLOG_note    ("mode is illegal or not-recognized");
                         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
                         return rce;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(update score)-------------------*/
   yENV_score_mark ("HEADER"   , 'h');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yjobs_ends__locations   (char a_runas, char a_mode, char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cdir      [LEN_DESC]  = "";
   char        x_conf      [LEN_LABEL] = "";
   char        x_hdir      [LEN_DESC]  = "";
   char        x_world     [LEN_LABEL] = "";
   char        x_db        [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yENV_score_mark ("LOCS"     , G_SCORE_FAIL);
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , ""     , LEN_DESC);
   if (r_conf  != NULL)  ystrlcpy (r_conf , ""     , LEN_LABEL);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , ""     , LEN_DESC);
   if (r_world != NULL)  ystrlcpy (r_world, ""     , LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , ""     , LEN_LABEL);
   /*---(get location data)--------------*/
   rc = yJOBS_configured   (a_runas, NULL, NULL, NULL, x_cdir, x_conf, x_hdir, x_db, x_world);
   DEBUG_YJOBS   yLOG_value   ("location"  , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "can not retrieve location information for runas");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cdir"    , x_cdir);
   DEBUG_YJOBS   yLOG_info    ("x_conf"    , x_conf);
   DEBUG_YJOBS   yLOG_info    ("x_hdir"    , x_hdir);
   DEBUG_YJOBS   yLOG_info    ("x_world"   , x_world);
   DEBUG_YJOBS   yLOG_info    ("x_db"      , x_db);
   /*---(save-back)----------------------*/
   if (r_cdir  != NULL)  ystrlcpy (r_cdir , x_cdir , LEN_DESC);
   if (r_conf  != NULL)  ystrlcpy (r_conf , x_conf , LEN_LABEL);
   if (r_hdir  != NULL)  ystrlcpy (r_hdir , x_hdir , LEN_DESC);
   if (r_world != NULL)  ystrlcpy (r_world, x_world, LEN_LABEL);
   if (r_db    != NULL)  ystrlcpy (r_db   , x_db   , LEN_LABEL);
   /*---(update score)-------------------*/
   yENV_score_mark ("LOCS"     , 'l');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends__cwd         (char a_runas, char a_mode, char a_file [LEN_PATH], char a_cdir [LEN_PATH], char r_cwd [LEN_PATH], char r_dir [LEN_PATH], char r_file [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        rce         =  -10;
   char        x_cwd       [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   char        x_full      [LEN_PATH]  = "";
   char       *p           = NULL;
   char        l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(score)--------------------------*/
   yENV_score_mark ("CWD"      , G_SCORE_FAIL);
   /*---(default)------------------------*/
   if (r_cwd   != NULL)  ystrlcpy (r_cwd  , ""     , LEN_PATH);
   if (r_dir   != NULL)  ystrlcpy (r_dir  , ""     , LEN_PATH);
   if (r_file  != NULL)  ystrlcpy (r_file , ""     , LEN_PATH);
   if (r_full  != NULL)  ystrlcpy (r_full , ""     , LEN_PATH);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("a_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      yjobs_ends_failure (a_mode, "", "called with NULL mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      yjobs_ends_failure (a_mode, "", "called with an invalid mode");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      yjobs_ends_failure (a_mode, "", "called with a NULL file name");
      DEBUG_YJOBS   yLOG_note    ("a_file is null (FATAL)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_file [0] == '\0') {
      DEBUG_YJOBS   yLOG_note    ("a_file is empty (warning)");
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   DEBUG_YJOBS  yLOG_point   ("a_cdir"    , a_cdir);
   /*---(get current working dir)--------*/
   p = getcwd (x_cwd, LEN_PATH);
   DEBUG_YJOBS   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      yjobs_ends_failure (a_mode, "", "system call getcwd failed");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_cwd"     , x_cwd);
   /*---(test split)---------------------*/
   rc = yENV_name_split (a_file, NULL, x_dir, x_file);
   DEBUG_YJOBS   yLOG_value   ("split"     , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "file name could not be split");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_dir"     , x_dir);
   DEBUG_YJOBS   yLOG_info    ("x_file"    , x_file);
   /*---(directory)----------------------*/
   if (strcmp (x_dir, "") == 0) {
      switch (a_mode) {
      case CASE_VERIFY   : case CASE_LOCALRPT : case CASE_REGISTER :
      case CASE_UPDATE   : case CASE_INSTALL  : case CASE_WITHDRAW :
         ystrlcpy (x_dir, x_cwd, LEN_PATH);
         break;
      case CASE_CHECK    : case CASE_ONLY     : case CASE_REMOVE   :
      case CASE_EXTRACT  :
      default :
         ystrlcpy (x_dir, a_cdir, LEN_PATH);
         break;
      }
      l = strlen (x_dir);
      if (x_dir [l - 1] != '/')  ystrlcat (x_dir, "/", LEN_PATH);
   }
   DEBUG_YJOBS   yLOG_info    ("x_dir"     , x_dir);
   DEBUG_YJOBS   yLOG_info    ("x_file"    , x_file);
   /*---(full)---------------------------*/
   rc = yENV_name_full (x_dir, x_file, NULL, x_full);
   DEBUG_YJOBS   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0) {
      yjobs_ends_failure (a_mode, "", "file name could not be joined");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YJOBS   yLOG_info    ("x_full"    , x_full);
   /*---(save-back)----------------------*/
   if (r_cwd   != NULL)   ystrlcpy (r_cwd  , x_cwd  , LEN_PATH);
   if (r_dir   != NULL)   ystrlcpy (r_dir  , x_dir  , LEN_PATH);
   if (r_file  != NULL)   ystrlcpy (r_file , x_file , LEN_PATH);
   if (r_full  != NULL)   ystrlcpy (r_full , x_full , LEN_PATH);
   /*---(score)--------------------------*/
   yENV_score_mark ("CWD"      , '¤');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yjobs_ends_prepare      (char a_runas, char a_mode, char a_oneline [LEN_HUND], char a_file [LEN_PATH], void *f_callback, int *r_ruid, char r_ruser [LEN_USER], char r_cdir [LEN_DESC], char r_conf [LEN_LABEL], char r_hdir [LEN_DESC], char r_world [LEN_LABEL], char r_db [LEN_LABEL], char r_cwd [LEN_PATH], char r_dir [LEN_PATH], char r_file [LEN_PATH], char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_error     [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ruid  != NULL)  *r_ruid  = -1;
   if (r_ruser != NULL)  strcpy (r_ruser, "");
   if (r_cdir  != NULL)  strcpy (r_cdir , "");
   if (r_conf  != NULL)  strcpy (r_conf , "");
   if (r_hdir  != NULL)  strcpy (r_hdir , "");
   if (r_world != NULL)  strcpy (r_world, "");
   if (r_db    != NULL)  strcpy (r_db   , "");
   if (r_cwd   != NULL)  strcpy (r_cwd  , "");
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   if (r_file  != NULL)  strcpy (r_file , "");
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense - runas)----------------*/
   DEBUG_YJOBS   yLOG_char    ("a_runas"   , a_runas);
   DEBUG_YJOBS   yLOG_info    ("g_valid"   , g_valid);
   --rce;  if (a_runas == 0 || strchr (g_valid, a_runas)  == NULL) {
      yENV_score_mark ("RUNAS"    , G_SCORE_FAIL);
      yENV_score_mark ("ENV"      , '·');
      sprintf (x_error, "runas (%c) not recognized or valid", ychrvisible (a_runas));
      yjobs_ends_failure (a_mode, "", x_error);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense - mode)-----------------*/
   DEBUG_YJOBS   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YJOBS   yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (a_mode  == 0 || strchr (g_allmode, a_mode) == NULL) {
      yENV_score_mark ("MODE"     , G_SCORE_FAIL);
      yENV_score_mark ("NOISE"    , '·');
      sprintf (x_error, "mode (%c) not recognized or valid", ychrvisible (a_mode));
      yjobs_ends_failure (a_mode, "", x_error);
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense - oneline)--------------*/
   DEBUG_YJOBS  yLOG_point   ("a_oneline" , a_oneline);
   --rce;  if (a_oneline == NULL || a_oneline [0] == '\0') {
      yENV_score_mark ("ONE"      , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "", "descriptive \"oneline\" string is NULL or empty");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_oneline" , a_oneline);
   /*---(defense - callback)-------------*/
   DEBUG_YJOBS  yLOG_point   ("f_callback", f_callback);
   --rce;  if (f_callback == NULL) {
      yENV_score_mark ("CALL"     , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "", "host program callback function is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense - file)-----------------*/
   DEBUG_YJOBS  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file    == NULL) {
      yENV_score_mark ("FILE"     , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "", "local file/directory is NULL");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_file"    , a_file);
   /*---(security)-----------------------*/
   rc = yEXEC_whoami          (NULL, NULL, r_ruid, NULL, NULL, r_ruser, 'n', NULL, NULL, NULL);
   DEBUG_YJOBS  yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yENV_score_mark ("RUSER"    , G_SCORE_FAIL);
      yjobs_ends_failure (a_mode, "", "could not identify current user (yEXEC_whoami)");
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yENV_score_mark ("RUSER"    , 'u');
   /*---(titles)-------------------------*/
   rc = yjobs_ends__titles (a_runas, a_mode, a_oneline);
   DEBUG_YJOBS   yLOG_value   ("titles"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get central files)--------------*/
   rc = yjobs_ends__locations (a_runas, a_mode, r_cdir, r_conf, r_hdir, r_world, r_db);
   DEBUG_YJOBS   yLOG_value   ("locations" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get current working dir)--------*/
   rc = yjobs_ends__cwd       (a_runas, a_mode, a_file, r_cdir, r_cwd, r_dir, r_file, r_full);
   DEBUG_YJOBS   yLOG_value   ("cwd"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                          footer                              ----===*/
/*====================------------------------------------====================*/
static void      o___FOOTER________o (void) {;};

char
yjobs_ends__footer      (char a_func [LEN_TITLE], char a_mode, char a_prefix [LEN_TERSE], char a_color [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_suffix    [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (a_func);
   /*---(default)------------------------*/
   yENV_score_mark ("FOOTER"   , G_SCORE_FAIL);
   yENV_score_mark ("JUDGE"    , G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_prefix"  , a_prefix);
   /*---(pre-score)----------------------*/
   yENV_score_mark ("JUDGE"    , 'Ï');
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      yENV_score_mark ("FOOTER"   , G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (a_func);
      return 0;
   }
   /*---(prepare)------------------------*/
   if (strcmp (a_prefix, "APPROVED") == 0)  strcpy (x_suffix, "; USES over-rides");
   if (strcmp (a_prefix, "REPAIRED") == 0)  strcpy (x_suffix, "; MUST investigate");
   if (strcmp (a_prefix, "WARNING")  == 0)  strcpy (x_suffix, "; BUT, issues outstanding");
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(write actual header)------------*/
   switch (a_mode) {    /*---(incomming 5)-----------------*/
   case CASE_VERIFY   : yURG_msg (':', "%s%s, read and verified local, but no register, update, or install requested%s%s" , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_LOCALRPT : yURG_msg (':', "%s%s, verified and specific report completed on local data%s%s"                   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_REGISTER : yURG_msg (':', "%s%s, verified and registered local, but no update or install requested%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_UPDATE   : yURG_msg (':', "%s%s, verified and updated, but registration not requested%s%s"                   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_INSTALL  : yURG_msg (':', "%s%s, full install of verification, update, and registration%s%s"                 , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(central 6)-------------------*/
   case CASE_CHECK    : yURG_msg (':', "%s%s, centrally installed file is runable, all lines checked%s%s"                 , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_AUDIT    : yURG_msg (':', "%s%s, environment and all central files passed relevent checks%s%s"               , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_FIX      : yURG_msg (':', "%s%s, environment and all central files passed relevent checks%s%s"               , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_ONLY     : yURG_msg (':', "%s%s, central execution on single file confirmed%s%s"                             , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(epic 3)----------------------*/
                        /*---(elsewhere 2)-----------------*/
                        /*---(outgoing 4)------------------*/
   case CASE_WITHDRAW : yURG_msg (':', "%s%s, registered local withdrawn from world, but clear/remove not requested%s%s"  , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_CLEAR    : yURG_msg (':', "%s%s, installed file/dir cleared from database, but withdraw not requested%s%s"   , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_REMOVE   : yURG_msg (':', "%s%s, installed file/dir cleared from database and withdrawn from world%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   case CASE_EXTRACT  : yURG_msg (':', "%s%s, installed file/dir contents extracted to local file%s%s"                    , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
                        /*---(execution 6)-----------------*/
   case CASE_GATHER   : yURG_msg (':', "%s%s, world registry entries have been gathered/updated in the database%s%s"      , a_color, a_prefix, x_suffix, BOLD_OFF);  break;
   }
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   yENV_score_mark ("FOOTER"   , 'f');
   if (strcmp (a_prefix, "WARNING") == 0)  rc = 1;
   DEBUG_YJOBS  yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (a_func);
   return rc;
}

char yjobs_ends_success      (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "SUCCESS" , BOLD_GRN); }
char yjobs_ends_approved     (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "APPROVED", BOLD_BLU); }
char yjobs_ends_repaired     (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "REPAIRED", BOLD_CYN); }
char yjobs_ends_warning      (char a_mode) { return yjobs_ends__footer (__FUNCTION__, a_mode, "WARNING" , BOLD_YEL); }

char
yjobs_ends_failure      (char a_mode, char a_message [LEN_HUND], char a_final [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YJOBS  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   yENV_score_mark ("FOOTER"   , G_SCORE_FAIL);
   yENV_score_mark ("JUDGE"    , G_SCORE_FAIL);
   /*---(defense)------------------------*/
   DEBUG_YJOBS  yLOG_value   ("m_mode"    , a_mode);
   --rce;  if (a_mode    == 0) {
      a_mode = ACT_CVERIFY;
   }
   DEBUG_YJOBS  yLOG_char    ("m_mode"    , a_mode);
   DEBUG_YJOBS  yLOG_info    ("g_allmode" , g_allmode);
   --rce;  if (strchr (g_allmode , a_mode) == NULL) {
      a_mode = ACT_CVERIFY;
   }
   DEBUG_YJOBS  yLOG_point   ("a_message" , a_message);
   --rce;  if (a_message == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_message" , a_message);
   DEBUG_YJOBS  yLOG_point   ("a_final"   , a_final);
   --rce;  if (a_final == NULL) {
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YJOBS  yLOG_info    ("a_final"   , a_final);
   /*---(quick-out)----------------------*/
   DEBUG_YJOBS  yLOG_info    ("g_silent"  , g_silent);
   if (strchr (g_silent  , a_mode) != NULL) {
      yENV_score_mark ("FOOTER"   , G_SCORE_SKIP);
      DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(message)------------------------*/
   if (strcmp (a_message, "") != 0)    yURG_err ('f', a_message);
   /*---(prepare)------------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_live ();
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (' ', "");
   /*---(actual footer)------------------*/
   if (strchr (g_verbose , a_mode)  != NULL)  yURG_msg (':', "%sFAILED, %s, the reasons are shown above%s"      , BOLD_ERR, a_final, BOLD_OFF);
   else                                       yURG_msg (':', "%sFAILED, %s, run verbosely to identify reasons%s", BOLD_ERR, a_final, BOLD_OFF);
   /*---(clean-up)-----------------------*/
   if (strchr (g_confirm , a_mode)  != NULL)  yURG_msg_mute ();
   /*---(score)--------------------------*/
   yENV_score_mark ("FOOTER"   , 'f');
   /*---(complete)-----------------------*/
   DEBUG_YJOBS   yLOG_exit    (__FUNCTION__);
   return 0;
}




