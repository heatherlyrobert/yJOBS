/*============================----beg-of-source---============================*/
#include   "yJOBS.h"
#include   "yJOBS_priv.h"



/*>    {  0, "HEADER"          , 'h' , "°h-·"    , "header"          , "printing of the title lines"      },                                                            <* 
 *>    {  0, "LOCS"            , 'l' , "°l·"     , "locs"            , "default location lookup"          },                                                            <* 
 *>    {  0, "CWD"             , '¤' , "°¤·"     , "cwd"             , "current working directory"        },                                                            <* 
 *>    {  0, "  "              ,  1  , ""        , ""                , ""                                 },                                                            <*/

/*>                                                                                                                                                                                       <* 
 *>    /+===[[ NAME ]]==========================================================+/                                                                                                        <* 
 *>    { "NMá "     , ' ' ,  0  , "NAME"                             , ""         , ""         , ""                                                                                },     <* 
 *>    /+===[[ REQUEST TYPE ]]==================================================+/                                                                                                        <* 
 *>    { "NCONF"    , '·' , 'c' , "conf"     , "naming²standard²applied"          , "·°-nslc"   , "°) illegal   -) wild      n) normal    s) standard  l) local     c) central"     },    <* 
 *>    { "NDIR"     , '·' , 'd' , "dir"      , "directory²requested"              , "·°£/D"     , "°) null      £) empty     /) pathless  D) passed"                                },    <* 
 *>    { "NFILE"    , '·' , 'f' , "file"     , "file²name²requested"              , "·°£/F-"    , "°) null      £) empty     /) pathed    F) passed    -) skipped"                  },    <* 
 *>    { " "        , ' ' ,  1  , ""         , ""                                 , ""          , ""                                                                                },    <* 
 *>    /+===[[ NAMING ]]========================================================+/                                                                                                        <* 
 *>    { "NFULL"    , '·' , 'n' , "full"     , "name²quality²checking"            , "·°/´¢n"    , "°) null      /) not abs   ´) hidden    ¢) bad char  n) passed"                   },    <* 
 *>    { "NSTYLE"   , '·' , 'b' , "style"    , "naming²style"                     , "·dfb"      , "d) dir       f) file      b) both"                                               },    <* 
 *>    { " "        , ' ' ,  1  , ""         , ""                                 , ""          , ""                                                                                },    <* 
 *>    /+===[[ STANDARDS ]]=====================================================+/                                                                                                        <* 
 *>    { "NDOTS"    , '·' , 'n' , "ndots"    , "file²name²separators"             , "·°<>n"     , "·) skipped   °) none      <) too few   >) too many  n) passed"                   },    <* 
 *>    { "NPREFIX"  , '·' , 'p' , "prefix"   , "required²prefix"                  , "·°up"      , "·) skipped   °) failed    u) user      p) passed"                                },    <* 
 *>    { "NSUFFIX"  , '·' , 's' , "suffix"   , "required²suffix"                  , "·°s"       , "·) skipped   °) failed    s) passed"                                             },    <* 
 *>    { "NDESC"    , '·' , 'd' , "desc"     , "remaining²description"            , "·°d"       , "·) skipped   °) failed    d) passed"                                             },    <* 
 *>    { " "        , ' ' ,  1  , ""         , ""                                 , ""          , ""                                                                                },    <* 
 *>    /+===[[ LOCATION ]]======================================================+/                                                                                                        <* 
 *>    { "NLOC"     , '·' , 'h' , "loc"      , "file²location²type"               , "·°rhes"    , "·) skipped   °) failed    r) root      h) home      e) etc       s) spool"       },    <* 
 *>    { "NUSE"     , '·' , 'H' , "usable"   , "file²location²usable"             , "·°RHES"    , "·) skipped   °) failed    R) root      H) home      E) etc       S) spool"       },    <* 
 *>    { " "        , ' ' ,  1  , ""         , ""                                 , ""          , ""                                                                                },    <* 
 *>    /+===[[ REQUEST ]]=======================================================+/                                                                                                        <* 
 *>    { "NAME"     , '-' , '´' , "ŒŒŒŒŒŒ"   , "[[²name²judgement²]]"             , "-°´"       , "-) unknown   °) failed    ´) passed"                                             },    <* 
 *>    { "   "      , ' ' ,  3  , ""         , ""                                 , ""          , ""                                                                                },    <* 
 *>                                                                                                                                                                                       <*/

const tSCORE_TABLE g_scores [LEN_FULL] = {
   /*===[[ PREPARE ]]=======================================================*/
   { "HEá "     , ' ' ,  0  , "HEAD"     , ""                                 , ""               ,  ""                                                                                },
   { "RUNAS"    , '·' , 'e' , "runas"    , "host_program calling yjobs"       , ""               ,  "e) eos       k) khronos   p) polymnia   ..."                                     },
   { "ENV"      , '·' , 'u' , "env"      , "run-time environment"             , "nbu"            ,  "·) normal    d) debug     u) unit-test"                                          },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "MODE"     , '·' , 'v' , "mode"     , "yjobs action requested"           , ""               ,  "v) verify    g) gather    d) daemon     ..."                                     },
   { "NOISE"    , '·' , '!' , "noise"    , "verbosity of feedback"            , ""               ,  "-) silent    c) confirm   !) verbose"                                            },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "ONE"      , '·' , 'o' , "onelin"   , "runas oneline desc"               , ""               ,  "°) failed    o) given"                                                           },
   { "CALL"     , '·' , '&' , "callbk"   , "yjobs file provided"              , ""               ,  "°) null      c) given"                                                           },
   { "FILE"     , '·' , 'f' , "file"     , "yjobs file provided"              , ""               ,  "-) n/a       f) required"                                                        },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "RUSER"    , '·' , 'u' , "ruser"    , "run-time user data"               , ""               ,  "°) failed    u) gathered"                                                        },
   { "HEADER"   , '·' , 'h' , "header"   , "printing of the title lines"      , ""               ,  "°) failed    -) skipped   h) header"                                             },
   { "LOCS"     , '·' , 'l' , "locs"     , "default location lookup"          , ""               ,  "°) failed    l) locs"                                                            },
   { "CWD"      , '·' , '¤' , "cwd"      , "current working directory"        , ""               ,  "°) failed    ¤) cwd"                                                             },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ PREPARE ]]=======================================================*/
   { "SEá "     , ' ' ,  0  , "SEC"      , ""                                 , ""               ,  ""                                                                                },
   { "SSECURE"  , '·' , 's' , "secure"   , "general security"                 , ""               ,  ""                                                                                },
   { "SFIX"     , '·' , 'f' , "fix"      , "adding fix to the audit"          , ""               ,  ""                                                                                },
   { "SAUDIT"   , '·' , 'a' , "audit"    , "general audit"                    , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ LOCAL ]]=========================================================*/
   { "LOá "     , ' ' ,  0  , "LOCAL"    , ""                                 , ""               ,  ""                                                                                },
   { "LTYPE"    , '·' , 'd' , "type"     , "type of entry"                    , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "LSECURE"  , '·' , 's' , "secure"   , "security on file/directory"       , ""               ,  ""                                                                                },
   { "LAUDIT"   , '·' , 'a' , "audit"    , "audit local file by pulling"      , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "LPULL"    , '·' , 'Ö' , "pull"     , "pull file in"                     , ""               ,  ""                                                                                },
   { "LREPORT"  , '·' , 'ò' , "report"   , "local report"                     , ""               ,  ""                                                                                },
   { "LMOVE"    , '·' , 'm' , "move"     , "move local to central"            , ""               ,  ""                                                                                },
   { "LREG"     , '·' , 'r' , "regist"   , "register in world"                , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "LWITH"    , '·' , 'w' , "withdr"   , "withdraw from world"              , ""               ,  ""                                                                                },
   { "LREMOVE"  , '·' , 'x' , "remove"   , "remove central file"              , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ CONFIG ]]========================================================*/
   { "CDá "     , ' ' ,  0  , "CDIR"     , ""                                 , ""               ,  ""                                                                                },
   { "FSTYLE"   , '·' , 'e' , "style"    , "config location type"             , ""               ,  "e) etc       s) spool"                                                           },
   { "FCOUNT"   , '·' , '1' , "count"    , "count of config files"            , ""               ,  "1) single    *) multiple"                                                        },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "FDSEC"    , '·' , 's' , "secure"   , "configuration dir security"       , ""               ,  ""                                                                                },
   { "FDFIX"    , '·' , 'f' , "dfix"     , "configuration dir fix"            , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ CONFIG FILE ]]===================================================*/
   { "CFá "     , ' ' ,  0  , "CONF"     , ""                                 , ""               ,  ""                                                                                },
   { "FFSEC"    , '·' , 's' , "secure"   , "configuration files secure"       , ""               ,  ""                                                                                },
   { "FFFIX"    , '·' , 'f' , "fix"      , "configuration files fix"          , ""               ,  ""                                                                                },
   { "FAUDIT"   , '·' , 'a' , "audit"    , "configuration files audit"        , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "FONLY"    , '·' , 'Ö' , "only"     , "pull/load central file"           , ""               ,  ""                                                                                },
   { "FEVERY"   , '·' , 'e' , "every"    , "pull/load all central files"      , ""               ,  ""                                                                                },
   { "FPURGE"   , '·' , 'p' , "purge"    , "do not retain data after pull"    , ""               ,  ""                                                                                },
   { "FLIST"    , '·' , '=' , "list"     , "list central files"               , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ CENTRAL ]]=======================================================*/
   { "HDá "     , ' ' ,  0  , "HDIR"     , ""                                 , ""               ,  ""                                                                                },
   { "CSECURE"  , '·' , 's' , "secure"   , "central data dir security"        , ""               ,  ""                                                                                },
   { "CFIX"     , '·' , 'f' , "fix"      , "configuration dir fix"            , ""               ,  ""                                                                                },
   { "CAUDIT"   , '·' , 'a' , "audit"    , "file contents audit"              , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ DATABASE ]]======================================================*/
   { "DBá "     , ' ' ,  0  , "DATABASE" , ""                                 , ""               ,  ""                                                                                },
   { "DSECURE"  , '·' , 's' , "secure"   , "database security"                , ""               ,  "°) non-exist s) secure"                                                          },
   { "DFIX"     , '·' , 'f' , "fix"      , "database fix"                     , ""               ,  "°) couldn't  -) n/a       f) fixed"                                                           },
   { "DAUDIT"   , '·' , 'a' , "audit"    , "database contents audit"          , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "DREAD"    , '·' , 'Ô' , "read"     , "read database"                    , ""               ,  "°) failed    Ô) read"                                                            },
   { "DPURGE"   , '·' , 'p' , "purge"    , "do not retain data after read"    , ""               ,  "°) failed    p) purge"                                                           },
   { "DSTATS"   , '·' , '#' , "stats"    , "database statistics"              , ""               ,  "°) failed    #) passed"                                                          },
   { "DREPORT"  , '·' , 'ó' , "report"   , "database reporting"               , ""               ,  "°) failed    ó) passed"                                                          },
   { "DCLEAR"   , '·' , 'x' , "clear"    , "clear specific data"              , ""               ,  "°) failed    x) clear"                                                           },
   { "DWRITE"   , '·' , 'Õ' , "write"    , "write database"                   , ""               ,  "°) failed    a) audit     Õ) written"                                            },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ WORLD ]]=========================================================*/
   { "WOá "     , ' ' ,  0  , "WORLD"    , ""                                 , ""               ,  ""                                                                                },
   { "WSECURE"  , '·' , 's' , "secure"   , "world file security"              , ""               ,  "" }, /* s) secure, a) audited content, -) skipped    , ""                                                                                */
   { "WFIX"     , '·' , 'f' , "fix"      , "world file fix"                   , ""               ,  ""                                                                                },
   { "WAUDIT"   , '·' , 'a' , "audit"    , "world contents audit"             , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "WENTRY"   , '·' , 'e' , "entry"    , "requested entry check"            , ""               ,  "" }, /* f) file, d) directory, -) skipped , ""                                                                                */
   { "WREAD"    , '·' , 'Ô' , "read"     , "read/import world file"           , ""               ,  ""                                                                                },
   { "WLIST"    , '·' , '=' , "list"     , "reporting on world file"          , ""               ,  ""                                                                                },
   { "WWRITE"   , '·' , 'Õ' , "write"    , "write/export world file"          , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ ACTION ]]========================================================*/
   { "ACá "     , ' ' ,  0  , "ACT"      , ""                                 , ""               ,  ""                                                                                },
   { "GATHER"   , '·' , 'g' , "gather"   , "gather local files"               , ""               ,  ""                                                                                },
   { "NORMAL"   , '·' , 'n' , "normal"   , "normal/strict mode"               , ""               ,  ""                                                                                },
   { "DAEMON"   , '·' , 'd' , "daemon"   , "daemon/prickly mode"              , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ BACKEND ]]=======================================================*/
   { "BEá "     , ' ' ,  0  , "BACKEND"  , ""                                 , ""               ,  ""                                                                                },
   { "BSECURE"  , '·' , 's' , "secure"   , "backend security"                 , ""               ,  ""                                                                                },
   { "BFIX"     , '·' , 'f' , "fix"      , "backend fix"                      , ""               ,  ""                                                                                },
   { "BAUDIT"   , '·' , 'a' , "audit"    , "audit of backend"                 , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "EXTRACT"  , '·' , 'E' , "extrct"   , "extract a central file"           , ""               ,  ""                                                                                },
   { "UPLOAD"   , '·' , 'U' , "upload"   , "upload a central file"            , ""               ,  ""                                                                                },
   { "BACKUP"   , '·' , 'B' , "backup"   , "backup a central file"            , ""               ,  ""                                                                                },
   { "DOWNLOAD" , '·' , 'D' , "dwload"   , "download a central file"          , ""               ,  ""                                                                                },
   { "RESTORE"  , '·' , 'R' , "restor"   , "restore a central file"           , ""               ,  ""                                                                                },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ""               ,  ""                                                                                },
   /*===[[ JUDGEMENT ]]=====================================================*/
   { "JDá "     , ' ' ,  0  , "³"        , ""                                 , ""               ,  ""                                                                                },
   { "FOOTER"   , '·' , 'f' , "footer"   , "print footer on output"           , ""               ,  ""                                                                                },
   { " "        , ' ' ,  1  , ""         , ""                                 , ""               ,  ""                                                                                },
   { "JUDGE"    , ' ' , 'Ï' , "judge"    , "final judgement"                  , ""               ,  ""                                                                                },
   /*===[[ END-OF-LIST ]]===================================================*/
   { "end-list" , '·' , '·' , ""         , "end-of-entries"                   , ""               ,  ""                                                                                },
   /*===[[ DONE ]]==========================================================*/
};

char
yjobs_yscore_init       (void)
{
   char          rce       =  -10;
   char          rc        =    0;
   rc = ySCORE_init  (g_scores, '-', &(myJOBS.m_yscore));
   --rce;  if (rc < 0)  return rce;
   return 0;
}

char
yjobs_yscore_wrap       (void)
{
   char          rce       =  -10;
   char          rc        =    0;
   rc = ySCORE_wrap  (&(myJOBS.m_yscore));
   --rce;  if (rc < 0)  return rce;
   return 0;
}

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
