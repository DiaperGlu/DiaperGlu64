// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.7.
//
//    DiaperGlu v5.7 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.7 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.7; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// August 26, 2022            //
// version 5.7                //
// /////////////////////////////



#include "diapergluforth.h"

// c compiling word names
const char dg_compilesegmentname[] = "dg_compilesegment";
const char dg_compile0stringname[] = "dg_compile0string";

// forth standard core wordlist names
const char dg_forthstorename[]               = "!";
const char dg_forthnumbersignname[]          = "#";
const char dg_forthnumbersigngreatername[]   = "#>";
const char dg_forthnumbersignsname[]         = "#S";
const char dg_forthscreatename[]             = "$CREATE";
const char dg_forthtickname[]                = "'";
const char dg_forthparenname[]               = "(";
const char dg_forthstarname[]                = "*";
const char dg_forthstarslashname[]           = "*/";
const char dg_forthstarslashmodname[]        = "*/MOD";
const char dg_forthplusname[]                = "+";
const char dg_forthplusstorename[]           = "+!";

const char dg_checkplusloopdonename[]        = "dg_checkplusloopdone";
const char dg_forthplusloopname[]            = "+LOOP";

const char dg_forthcommaname[]               = ",";
const char dg_forthminusname[]               = "-";
const char dg_forthdotname[]                 = "."; 
const char dg_forthdotquotesname[]           = ".\"";
const char dg_forthslashname[]               = "/";
const char dg_forthslashmodname[]            = "/MOD";
const char dg_forthzerolessname[]            = "0<";
const char dg_forthzeroequalsname[]          = "0=";
const char dg_forthoneplusname[]             = "1+";
const char dg_forthoneminusname[]            = "1-";
const char dg_forthtwostorename[]            = "2!";
const char dg_forthtwostarname[]             = "2*";
const char dg_forthtwoslashname[]            = "2/";
const char dg_forthtwofetchname[]            = "2@";
const char dg_forthtwodropname[]             = "2DROP";
const char dg_forthtwodupname[]              = "2DUP";
const char dg_forthtwoovername[]             = "2OVER";
const char dg_forthtwoswapname[]             = "2SWAP";
const char dg_forthcolonname[]               = ":";
const char dg_forthsemicolonname[]           = ";";
const char dg_forthlessthanname[]            = "<";
const char dg_forthlessthannumbersignname[]  = "<#";
const char dg_forthequalsname[]              = "=";
const char dg_forthgreaterthanname[]         = ">";
const char dg_forthtobodyname[]              = ">BODY";
const char dg_forthtoinname[]                = ">IN";
const char dg_forthtonumbername[]            = ">NUMBER";
const char dg_forthtorname[]                 = ">R";
const char dg_forthquestiondupname[]         = "?DUP";
const char dg_forthfetchname[]               = "@";
const char dg_forthabortname[]               = "ABORT";
const char dg_forthabortquotesname[]         = "ABORT\"";
const char dg_forthabsname[]                 = "ABS";
const char dg_forthacceptname[]              = "ACCEPT";
const char dg_forthalignname[]               = "ALIGN";
const char dg_forthalignedname[]             = "ALIGNED";
const char dg_forthallotname[]               = "ALLOT";
const char dg_forthandname[]                 = "AND";
const char dg_forthbasename[]                = "BASE";
const char dg_forthbeginname[]               = "BEGIN";
const char dg_forthblname[]                  = "BL";
const char dg_forthcstorename[]              = "C!";
const char dg_forthccommaname[]              = "C,";
const char dg_forthcfetchname[]              = "C@";
const char dg_forthcellplusname[]            = "CELL+";
const char dg_forthcellsname[]               = "CELLS";
const char dg_forthcharname[]                = "CHAR";
const char dg_forthcharplusname[]            = "CHAR+";
const char dg_forthcharsname[]               = "CHARS";
const char dg_forthcmovename[]               = "CMOVE";
const char dg_forthcmovetoname[]             = "CMOVE>";
const char dg_forthconstantname[]            = "CONSTANT";
const char dg_forthconstantsname[]           = "CONSTANTS";
const char dg_forthconstantscurlyname[]      = "CONSTANTS<";
const char dg_forthcountname[]               = "COUNT";
const char dg_forthcrname[]                  = "CR";
const char dg_forthcreatename[]              = "CREATE";
const char dg_forthdecimalname[]             = "DECIMAL";
const char dg_forthdepthname[]               = "DEPTH";
const char dg_forthdoname[]                  = "DO";
const char dg_forthdoesname[]                = "DOES>";
const char dg_forthdropname[]                = "DROP";
const char dg_forthdupname[]                 = "DUP";
const char dg_forthelsename[]                = "ELSE";
const char dg_forthemitname[]                = "EMIT";
const char dg_forthenvironmentqueryname[]    = "ENVIRONMENT?";
const char dg_forthevaluatename[]            = "EVALUATE";
const char dg_forthexecutename[]             = "EXECUTE";
const char dg_forthexitname[]                = "EXIT";
const char dg_forthfillname[]                = "FILL";
const char dg_forthfindname[]                = "FIND";
const char dg_forthfmslashmodname[]          = "FM/MOD";
const char dg_forthherename[]                = "HERE";
const char dg_forthholdname[]                = "HOLD";
const char dg_forthiname[]                   = "I";
const char dg_forthifname[]                  = "IF";
const char dg_forthimmediatename[]           = "IMMEDIATE";
const char dg_forthinvertname[]              = "INVERT";
const char dg_forthjname[]                   = "J";
const char dg_forthkeyname[]                 = "KEY";
const char dg_forthleavename[]               = "LEAVE";
const char dg_forthliteralname[]             = "LITERAL";

const char dg_checkloopdonename[]            = "dg_checkloopdone";
const char dg_forthloopname[]                = "LOOP";
const char dg_forthlshiftname[]              = "LSHIFT";
const char dg_forthmstarname[]               = "M*";
const char dg_forthmaxname[]                 = "MAX";
const char dg_forthminname[]                 = "MIN";
const char dg_forthmodname[]                 = "MOD";
const char dg_forthmovename[]                = "MOVE";
const char dg_forthnegatename[]              = "NEGATE";
const char dg_forthorname[]                  = "OR";
const char dg_forthovername[]                = "OVER";
const char dg_forthpostponename[]            = "POSTPONE";
const char dg_forthquitname[]                = "QUIT";
const char dg_forthrfromname[]               = "R>";
const char dg_forthrfetchname[]              = "R@";
const char dg_forthrecursename[]             = "RECURSE";
const char dg_forthrepeatname[]              = "REPEAT";
const char dg_forthrshiftname[]              = "RSHIFT";
const char dg_forthrotname[]                 = "ROT";
const char dg_forthsquotesname[]             = "S\"";
const char dg_forthstodname[]                = "S>D";
const char dg_forthsignname[]                = "SIGN";
const char dg_forthsmslashremname[]          = "SM/REM";
const char dg_forthsourcename[]              = "SOURCE";
const char dg_forthspacename[]               = "SPACE";
const char dg_forthspacesname[]              = "SPACES";
const char dg_forthstatename[]               = "STATE";
const char dg_forthswapname[]                = "SWAP";
const char dg_forththenname[]                = "THEN";
const char dg_forthtypename[]                = "TYPE";
const char dg_forthudotname[]                = "U.";
const char dg_forthulessthanname[]           = "U<";
const char dg_forthumstarname[]              = "UM*";
const char dg_forthumslashmodname[]          = "UM/MOD";
const char dg_forthunloopname[]              = "UNLOOP";
const char dg_forthuntilname[]               = "UNTIL";
const char dg_forthvariablename[]            = "VARIABLE";
const char dg_forthvariablesname[]           = "VARIABLES";
const char dg_forthvariablescurlyname[]      = "VARIABLES<";
const char dg_forthwhilename[]               = "WHILE";
const char dg_forthwordname[]                = "WORD";
const char dg_forthxorname[]                 = "XOR";
const char dg_forthleftbracketname[]         = "[";
const char dg_forthbrackettickname[]         = "[']";
const char dg_forthbracketcharname[]         = "[CHAR]";
const char dg_forthrightbracketname[]        = "]";


// forth standard core extension word names
const char dg_forthnumbertibname[]           = "#TIB";
const char dg_forthdotparenname[]            = ".(";
const char dg_forthdotrname[]                = ".R";
const char dg_forthzeronotequalsname[]       = "0<>";
const char dg_forthzerogreatername[]         = "0>";
const char dg_forthtwotorname[]              = "2>R";
const char dg_forthtworfromname[]            = "2R>";
const char dg_forthtworfetchname[]           = "2R@";
const char dg_forthcolonnonamename[]         = ":NONAME";
const char dg_forthnotequalsname[]           = "<>";
const char dg_forthquerydoname[]             = "?DO";
const char dg_forthagainname[]               = "AGAIN";
const char dg_forthcquotename[]              = "C\"";
// CASE
// COMPILE,
// CONVERT
// ENDCASE
// ENDOF
const char dg_fortherasename[]               = "ERASE";
// EXPECT
const char dg_forthfalsename[]               = "FALSE";
const char dg_forthhexname[]                 = "HEX";
// MARKER
const char dg_forthnipname[]                 = "NIP";
// OF
const char dg_forthpadname[]                 = "PAD";
const char dg_forthparsename[]               = "PARSE";
const char dg_forthlinesparsename[]          = "LINES-PARSE"; 
const char dg_forthparsebuffername[]         = "PARSE-BUFFER";
const char dg_forthparsenamenom[]            = "PARSE-NAME";
const char dg_forthparsenamesname[]          = "PARSE-NAMES";
const char dg_forthlinesparsenamesname[]     = "LINES-PARSE-NAMES";
const char dg_forthparsewordname[]           = "PARSE-WORD";
const char dg_forthparsewordsname[]          = "PARSE-WORDS";
const char dg_forthparselinename[]           = "PARSE-LINE";

const char dg_forthpickname[]                = "PICK";
// QUERY
// REFILL
// RESTORE-INPUT
const char dg_forthrollname[]                = "ROLL";
// SAVE-INPUT
// SOURCE-ID
// SPAN
const char dg_forthsbackslashquotesname[]    = "S\\\"";
const char dg_forthtibname[]                 = "TIB";
const char dg_forthtoname[]                  = "TO";

const char dg_forthtruename[]                = "TRUE";
const char dg_forthtuckname[]                = "TUCK";
// U.R
const char dg_forthugreaterthanname[]        = "U>";
// UNUSED
const char dg_forthvaluename[]               = "VALUE";
// WITHIN
// [COMPILE]
const char dg_forthbackslashname[]           = "\\";


// forth search order word names
const char dg_forthdefinitionsname[]    = "DEFINITIONS";
const char dg_forthforthwordlistname[]  = "FORTH-WORDLIST";
const char dg_forthgetcurrentname[]     = "GET-CURRENT";
const char dg_forthgetordername[]       = "GET-ORDER";
const char dg_forthsearchwordlistname[] = "SEARCH-WORDLIST";
const char dg_forthsetcurrentname[]     = "SET-CURRENT";
const char dg_forthsetordername[]       = "SET-ORDER";
const char dg_forthwordlistname[]       = "WORDLIST";


// forth double number word names
const char dg_forthtwoconstantname[] = "2CONSTANT";
const char dg_forthtwoliteralname[]  = "2LITERAL";
const char dg_forthtworotname[]      = "2ROT";
const char dg_forthtwovariablename[] = "2VARIABLE";
const char dg_forthdlessthanname[]   = "D<";
const char dg_forthdequalsname[]     = "D=";
const char dg_forthdtosname[]        = "D>S";
const char dg_forthdplusname[]       = "D+";
const char dg_forthdminusname[]      = "D-";
const char dg_forthddotname[]        = "D.";
const char dg_forthddotrname[]       = "D.R";
const char dg_forthdzerolessname[]   = "D0<";
const char dg_forthdzeroequalsname[] = "D0=";
const char dg_forthdtwostarname[]    = "D2*";
const char dg_forthdtwoslashname[]   = "D2/";
const char dg_forthdabsname[]        = "DABS";
const char dg_forthdmaxname[]        = "DMAX";
const char dg_forthdminname[]        = "DMIN";
const char dg_forthdnegatename[]     = "DNEGATE";
const char dg_forthdulessthanname[]  = "DU<";
const char dg_forthmstarslashname[]  = "M*/";
const char dg_forthmplusname[]       = "M+";

// forth floating point word names
const char dg_forthminusdenormalname[]   = "-DENORMAL";
const char dg_forthminusinfinityname[]   = "-INFINITY";
const char dg_forthminusnanname[]        = "-NAN";
const char dg_forthtofloatname[]         = ">FLOAT";
const char dg_forthdtofname[]            = "D>F";
const char dg_forthdenormalname[]        = "DENORMAL";
const char dg_forthdfstorename[]         = "DF!";
const char dg_forthdffetchname[]         = "DF@";
const char dg_forthdfalignname[]         = "DFALIGN";
const char dg_forthdfalignedname[]       = "DFALIGNED";
const char dg_forthdfloatplusname[]      = "DFLOAT+";
const char dg_forthdfloatsname[]         = "DFLOATS";
const char dg_forthfliteralname[]        = "FLITERAL";
const char dg_forthfstorename[]          = "F!";
const char dg_forthfstarname[]           = "F*";
const char dg_forthfstarstarname[]       = "F**";
const char dg_forthfplusname[]           = "F+";
const char dg_forthfminusname[]          = "F-";
const char dg_forthfdotname[]            = "F.";
const char dg_forthfslashname[]          = "F/";
const char dg_forthfzerolessthanname[]   = "F0<";
const char dg_forthfzeroequalsname[]     = "F0=";
const char dg_forthflessthanname[]       = "F<";
const char dg_forthffetchname[]          = "F@";
const char dg_forthftodname[]            = "F>D";
const char dg_forthftosname[]            = "F>S";
const char dg_forthfabsname[]            = "FABS";
const char dg_forthfacosname[]           = "FACOS";
const char dg_forthfacoshname[]          = "FACOSH";
const char dg_forthfalignname[]          = "FALIGN";
const char dg_forthfalignedname[]        = "FALIGNED";
const char dg_forthfalogname[]           = "FALOG";
const char dg_forthfasinname[]           = "FASIN";
const char dg_forthfasinhname[]          = "FASINH";
const char dg_forthfatanname[]           = "FATAN";
const char dg_forthfatan2name[]          = "FATAN2";
const char dg_forthfatanhname[]          = "FATANH";
const char dg_forthfconstantname[]       = "FCONSTANT";
const char dg_forthfconstantsname[]      = "FCONSTANTS";
const char dg_forthfconstantscurlyname[] = "FCONSTANTS<";
const char dg_forthfcosname[]            = "FCOS";
const char dg_forthfcoshname[]           = "FCOSH";
const char dg_forthfdepthname[]          = "FDEPTH";
const char dg_forthfdropname[]           = "FDROP";
const char dg_forthfdupname[]            = "FDUP";
const char dg_forthfedotname[]           = "FE.";
const char dg_forthfexpname[]            = "FEXP";
const char dg_forthfexpm1name[]          = "FEXPM1";
const char dg_forthflnname[]             = "FLN";
const char dg_forthflnp1name[]           = "FLNP1";
const char dg_forthflogname[]            = "FLOG";
const char dg_forthfloatsname[]          = "FLOATS";
const char dg_forthfloatplusname[]       = "FLOAT+";
const char dg_forthfloorname[]           = "FLOOR";
const char dg_forthfmaxname[]            = "FMAX";
const char dg_forthfminname[]            = "FMIN";
const char dg_forthfnegatename[]         = "FNEGATE";
const char dg_forthfovername[]           = "FOVER";
const char dg_forthfroundname[]          = "FROUND";
const char dg_forthfrotname[]            = "FROT";
const char dg_forthfsdotname[]           = "FS.";
const char dg_forthfsincosname[]         = "FSINCOS";
const char dg_forthfsinname[]            = "FSIN";
const char dg_forthfsinhname[]           = "FSINH";
const char dg_forthfsqrtname[]           = "FSQRT";
const char dg_forthfswapname[]           = "FSWAP";
const char dg_forthftanname[]            = "FTAN";
const char dg_forthftanhname[]           = "FTANH";
const char dg_forthfvariablename[]       = "FVARIABLE";
const char dg_forthfvariablesname[]      = "FVARIABLES";
const char dg_forthfvariablescurlyname[] = "FVARIABLES<";
const char dg_forthfproximatename[]      = "F~";
const char dg_forthinfinityname[]        = "INFINITY";
const char dg_forthnanname[]             = "NAN";
const char dg_forthpiname[]              = "PI";
const char dg_forthprecisionname[]       = "PRECISION";
const char dg_forthrepresentname[]       = "REPRESENT";
const char dg_forthsetprecisionname[]    = "SET-PRECISION";
const char dg_forthstofname[]            = "S>F";
const char dg_forthsfstorename[]         = "SF!";
const char dg_forthsffetchname[]         = "SF@";
const char dg_forthsfalignname[]         = "SFALIGN";
const char dg_forthsfalignedname[]       = "SFALIGNED";
const char dg_forthsfloatplusname[]      = "SFLOAT+";
const char dg_forthsfloatsname[]         = "SFLOATS";
const char dg_forthlittleename[]         = "e";
const char dg_forthf64commaname[]        = "F64,";

// Forth Locals Word Names
const char dg_forthlocalsbarname[]            = "LOCALS|";
const char dg_forthclearlocalwordlistname[]   = "CLEAR-LOCAL-WORDLIST";
const char dg_forthquerycompileunnestlocalsname[] = "?COMPILE-UNNEST-LOCALS";
const char dg_forthqueryclearlocalsname[]     = "?CLEAR-LOCALS";
const char dg_forthcurlybracename[]           = "{";
const char dg_forthtwovaluename[]             = "2VALUE";
const char dg_forthfvaluename[]               = "FVALUE";

// Forth Programming Tools names
const char dg_forthdotsname[]                 = ".S";
const char dg_forthquestionname[]             = "?";

// Forth String word names
const char dg_forthdashtrailingname[]         = "-TRAILING";
const char dg_forthslashstringname[]          = "/STRING";
const char dg_forthblankname[]                = "BLANK";

// forth error word names
const char dg_forthpushoerrorname[]           = "PUSHOERROR0$";
const char dg_forthtoerrorname[]              = ">ERROR";
const char dg_forthtoerrorshortname[]         = ">E";
const char dg_forthpopoerrorname[]            = "POPOERROR0$";
const char dg_fortherrorfromname[]            = "ERROR>";
const char dg_fortherrorfromshortname[]       = "E>";
const char dg_forthgetoerrorname[]            = "GETOERROR0$";
const char dg_forthgeterrorcountname[]        = "GETERRORCOUNT";
const char dg_forthcheckerrordepthname[]      = "DEPTHERROR";
const char dg_forthdroptoerrorcountname[]     = "DROPTOERRORCOUNT";
const char dg_forthdoterrorsname[]            = ".ERRORS";
const char dg_clearerrorsname[]               = "EMPTY-ERRORS";
const char dg_forthdoterrorsshortname[]       = ".ES";
const char dg_forthshowerrorsname[]           = "SHOW-ERRORS";
const char dg_clearerrorsshortname[]          = "EES";
const char dg_forthcplgetolderrorcountname[]  = "GETOLDERRORCOUNT";


// forth get compile type routine offset bufferid word names
const char dg_forthodoctalwaysexecutename[]   = "OCRALWAYSEXECUTE";
const char dg_forthodoctsubroutinename[]      = "OCREXECUTE";
const char dg_forthodoctpreserveregsname[]    = "OCRPRESERVEREGS";
const char dg_forthodoctsafesubroutinename[]  = "OCRSAFEEXECUTE";
const char dg_forthodocompiletypedpushnname[] = "OCRPUSHN";
const char dg_forthodocompiletypedpushfname[] = "OCRPUSHF";
const char dg_forthodoctdpushdnname[]         = "OCRPUSHDN";
const char dg_forthodocompiletypedpushpname[] = "OCRPUSHBUFADDR";
const char dg_forthodocompiletypevaluename[]  = "OCRVALUE";
const char dg_forthodocompiletypetwovaluename[] = "OCR2VALUE";
const char dg_forthodocompiletypefvaluename[] = "OCRFVALUE";
const char dg_forthodocompiletypeostorename[] = "OCRO!";
const char dg_forthodocompiletypeof64storename[] = "OCROF64!";
const char dg_forthodocompiletypeotwostorename[] = "OCRO2!";
const char dg_forthodocompiletypedpushsname[] = "OCRPUSH$";
const char dg_forthodocompiletypewordsstringquotesname[] = "OCRWORDS$\"";
const char dg_forthodocompiletypewords0stringquotesname[] = "OCRWORDS0$\"";
const char dg_forthodocompiletyperunfileandwaitnoenvquotesname[] = "OCRRUNFILEANDWAITNOENV\"";
const char dg_forthodocompiletypecdeclname[]  = "OCRCALLPROC";
const char dg_forthodocpltypedfpcdeclname[]   = "OCRCALLDFPPROC";
const char dg_forthodoctcdeclretuint128name[] = "OCRCALLPROCRETUINT128";
const char dg_forthodoctcppmembername[]       = "OCRCALLCPPMEMBER";
const char dg_forthodocompiletypecallname[]   = "OCRCALL";
const char dg_forthdocompiletypebrackettoordername[] = "OCR[>ORDER]";  
const char dg_forthdocompiletypebracketwordlistdotname[] = "OCR[WORDLIST.]";
const char dg_forthdocompiletypebracketlibdotname[] = "OCR[LIB.]";


// forth miscellaneous word names
const char dg_forthevaluatebuffername[]       = "EVALUATEBUFFER";
const char dg_forthbyename[]                  = "BYE";
const char dg_forthsynonymname[]              = "SYNONYM";
const char dg_forthocallname[]                = "OCALL";
const char dg_forthqueryendevaluatename[]     = "?END-EVALUATE";
const char dg_forthosquotesname[]             = "OS\"";
const char dg_fortho0quotesname[]             = "O0\"";
const char dg_fortherrorquotesshortname[]     = "E\"";
const char dg_fortherrorquotesname[]          = "ERROR\"";
const char dg_forthtype0stringname[]          = "TYPE0$";
const char dg_forthdotwordnamename[]          = ".NAME";
const char dg_forthshowwordlistname[]         = "SHOW-WORDLIST";
const char dg_forthshowsortedwordlistname[]   = "SHOW-SORTED-WORDLIST";
const char dg_forthshowallwordsname[]         = "SHOW-ALL-WORDS";
const char dg_forthwordsname[]                = "WORDS";
const char dg_forthshowlicensename[]          = "SHOW-LICENSE";
const char dg_forthcrlfname[]                 = "CRLF";
const char dg_forthtoordername[]              = ">SEARCH-ORDER";
const char dg_forthorderfromname[]            = "SEARCH-ORDER>";
const char dg_forthbswapname[]                = "BSWAP";
const char dg_forthodoesname[]                = "ODOES>";
const char dg_forthpagesizename[]             = "PAGESIZE";
const char dg_forthroundupname[]              = "ROUNDUP";
const char dg_forthpackdfname[]               = "PACKDF";
const char dg_forthunpackdfname[]             = "UNPACKDF";
// const char dg_forthdfplusname[]               = "DF+";
// const char dg_forthdfminusname[]              = "DF-";
// const char dg_forthdfstarname[]               = "DF*";
// const char dg_forthdfslashname[]              = "DF/";
const char dg_showframename[]                 = "SHOW-FRAME";
const char dg_forthoherename[]                = "OHERE";
const char dg_forthdglibstringname[]          = "DGLIB$";
const char dg_forthemptywordlistname[]        = "EMPTY-WORDLIST";
const char dg_forthrandomname[]               = "RANDOM";
const char dg_forthn8tocellname[]             = "N8>CELL";
const char dg_forthn16tocellname[]            = "N16>CELL";
const char dg_forthn32tocellname[]            = "N32>CELL";

const char dg_forthcompileu8sname[]           = "COMPILE-U8S";
const char dg_forthcompileu8scurlyname[]      = "COMPILE-U8S<";
const char dg_forthlocalconstantsname[]       = "LOCAL-CONSTANTS";
const char dg_forthbracketlocalconstantsname[] = "[LOCAL-CONSTANTS]";
const char dg_forthlocalconstantscurlyname[]  = "LOCAL-CONSTANTS<";
const char dg_forthbracketlocalconstantscurlyname[]  = "[LOCAL-CONSTANTS]<";
const char dg_forthenumcurlyname[]            = "ENUM<";
const char dg_forthlocalenumcurlyname[]       = "LOCAL-ENUM<";
const char dg_forthbracketlocalenumcurlyname[] = "[LOCAL-ENUM]<";
const char dg_forthtypedenumcurlyname[]       = "TYPED-ENUM<";
const char dg_forthtypedlocalenumcurlyname[]  = "TYPED-LOCAL-ENUM<";
const char dg_forthbenchmarkname[]            = "BENCHMARK";
const char dg_forthnopname[]                  = "NOP";





const char dg_forthcodescommaname[]            = "CODE-S,";
const char dg_forthcodeu8commaname[]           = "CODE-U8,";
const char dg_forthcodeu16commaname[]          = "CODE-U16,";
const char dg_forthcodeu32commaname[]          = "CODE-U32,";
const char dg_forthcodeu64commaname[]          = "CODE-U64,";
const char dg_forthcodeallotname[]             = "CODE-ALLOT";

const char dg_forthdoterrorlinename[]          = ".ERRORLINE";
const char dg_forthdotelname[]                 = ".EL";

// const char dg_forthsftodfname[]                = "SF>DF";
// const char dg_forthdftosfname[]                = "DF>SF";
// const char dg_forthdftodname[]                 = "DF>D";
// const char dg_forthdtodfname[]                 = "D>DF";

const char dg_forthlobitname[]                 = "LOBIT";
const char dg_forthhibitname[]                 = "HIBIT";
const char dg_forthcountbitsname[]             = "COUNTBITS";

const char dg_forthmicrosecondssince1970jan01name[] = "MICROSECONDSSINCE1970JAN01";

const char dg_forthtouleb128name[]             = ">ULEB128";

const char dg_forthhctwostorename[]            = "HC2!";

const char dg_forthdrshiftname[]               = "DRSHIFT";
const char dg_forthdlshiftname[]               = "DLSHIFT";
const char dg_forthdarshiftname[]              = "DARSHIFT";

const char dg_forthbuftodotobufname[]          = "BUF>NEW.OBUF";
const char dg_forthbuftodotofilestringname[]   = "BUF>.OFILE$";
const char dg_forthbuftomachodotobufname[]     = "BUF>NEWMACH-O.OBUF";
const char dg_forthbuftoneweximdotobufname[]   = "BUF>NEWEXPORTIMPORT.OBUF";
const char dg_forthosymbolbuftonewdotobufname[] = "OSYMBOLBUF>NEW.OBUF";
const char dg_forthosymbolbuftonewdotofilestringname[] = "OSYMBOLBUF>NEW.OFILE$";
const char dg_forthtestfindnumbername[]        = "TESTFINDNUMBER";

const char dg_forthfunctblofnname[]            = "FUNCTBL[N]";

const char dg_forthminusrotname[]              = "-ROT";
const char dg_forthsizedconstantscurlyname[]   = "SIZED-CONSTANTS<";


// forth show wordlist names
const char dg_forthforthwordsname[]            = "FORTH-WORDS";
const char dg_fortherrorwordsname[]            = "ERROR-WORDS";
const char dg_forthenvironmentwordsname[]      = "ENVIRONMENT-WORDS";
const char dg_forthbufferwordsname[]           = "BUFFER-WORDS";
const char dg_forthstringwordsname[]           = "$-WORDS";
const char dg_forthlibrarywordsname[]          = "LIB-WORDS";
const char dg_forthuserwordsname[]             = "USER-WORDS";


// forth operating system words
const char dg_forthgethstdinname[]             = "GETHSTDIN";
const char dg_forthgethstdoutname[]            = "GETHSTDOUT";
const char dg_forthgethstderrorname[]          = "GETHSTDERR";
const char dg_forthgetfilelengthname[]         = "GETFILELENGTH";
const char dg_forthreadavailabletobuffername[] = "FILE>BUF";
const char dg_forthreadwaitforntobuffername[]  = "WAITREADN>BUF";
const char dg_forthfixpathstringname[]         = "FIXPATH$";
const char dg_forthopenlibstringname[]         = "OPENLIB$";
const char dg_forthopenlibrarystringname[]     = "OPENLIBRARY$";
const char dg_forthloadlibrarystringname[]     = "LOADLIBRARY$";
// const char* dg_forthloadstdcalllibrarystringname = "LOADSTDCALLLIBRARY$";
const char dg_forthshowopenlibraryname[]       = "SHOWOPENLIBRARY";
const char dg_forthshowlibrarystringname[]     = "SHOWLIBRARY$";
const char dg_forthfindlibrarysymbolname[]     = "FINDLIBRARYSYMBOL";


// forth compiling word names
const char dg_forthcompileentercolonname[]     = "COMPILE-ENTER-:-FRAME";
const char dg_forthcompileentername[]          = "COMPILE-ENTER-FRAME";
const char dg_forthcompileentersubname[]       = "COMPILE-ENTER-SUB-FRAME";
const char dg_forthcompileexitname[]           = "COMPILE-EXIT-FRAME";
const char dg_forthcompilesname[]              = "COMPILE-S";
const char dg_forthsliteralname[]              = "SLITERAL";
const char dg_forthcompilecallcorename[]       = "COMPILE-CALLCORE";
const char dg_forthcompilecallsamebuffername[] = "COMPILE-CALLSAMEBUFFER";
const char dg_forthcompilecallbuffername[]     = "COMPILE-CALLBUFFER";
const char dg_forthcompilesafecallbuffername[] = "COMPILE-SAFECALLBUFFER";
const char dg_forthenterdgluframecommaname[]   = "ENTER-DGLU-FRAME,";
const char dg_forthexitdgluframecommaname[]    = "EXIT-DGLU-FRAME,";
const char dg_forthsafename[]                  = "SAFE";
const char dg_forthiscolonname[]               = "IS-:";
const char dg_forthisotoname[]                 = "IS-O>";
const char dg_forthisobtoname[]                = "IS-OB>";
const char dg_forthisptoname[]                 = "IS-P>";
const char dg_forthiscompilecallname[]         = "IS-COMPILE-CALL";
const char dg_forthiscallprocname[]            = "IS-CALL-PROC";
const char dg_forthiscallprocretuint64name[]   = "IS-CALL-PROC-RET-UINT64";
const char dg_forthstringtonewprocwordname[]   = "$>NEW-PROC-WORD";
const char dg_forthstringtonewobwordname[]     = "$>NEW-OB-WORD";
const char dg_forthcompilebranchname[]         = "COMPILE-BRANCH";
const char dg_forthresolvecompiledbranchname[] = "RESOLVE-BRANCH";

const char dg_forthdopromptname[]              = "DOPROMPT";
const char dg_forthdumpname[]                  = "DUMP";

const char dg_forthqueryerrorifname[]         = "?ERRORIF";

const char dg_forthcreateocname[]             = "CREATEOC";
const char dg_forthcreateovname[]             = "CREATEOV";

const char dg_forthtoonamename[]                = ">ONAME";
const char dg_forthlatestname[]                 = "LATEST";
const char dg_forthbracketlatestname[]          = "[LATEST]";
const char dg_forthbracketcolononamename[]      = "[:ONAME]";
const char dg_forthbracketolatestnamename[]     = "[OLATESTNAME]";
const char dg_forthbracketwordnametoerrorname[] = "[WORDNAME>ERROR]";
const char dg_forthnametoename[]                = "NAME>E";
const char dg_forthnametoerrorname[]            = "NAME>ERROR";

const char dg_forthgetcompileroutinename[]      = "GETOCR"; // should probably call this SET-COMPILE-TYPE
const char dg_forthsetcompileroutinename[]      = "SETOCR"; //  or SET-DATA-FIELD or SET-ODF
const char dg_forthgetodfname[]                 = "GETODF";
const char dg_forthsetodfname[]                 = "SETODF";

const char dg_forthudmslashmodname[]          = "UDM/MOD";

const char dg_forthendoflistname[]             = "ENDOFLIST";
const char dg_forthendofwordlistname[]         = "ENDOFWORDLIST";

const char dg_forthcscanbufname[]              = "CSCANBUF";

const char dg_forthscanbufname[]               = "SCANBUF";
const char dg_forthshowbuffersname[]           = "SHOW-BUFFERS";
const char dg_forthsearchname[]                = "SEARCH";
const char dg_forthcomparename[]               = "COMPARE";


// forth definition word names
const char dg_forthnewdefinitionname[]                  = "NEWDEFINITION";
const char dg_forthnewwordname[]                        = "NEWWORD";
const char dg_forthgetpdefinitionname[]                 = "GETPDEFINITION";
const char dg_forthgetswordheadname[]                   = "GETSWORDHEAD";
const char dg_forthtoheadname[]                         = ">HEAD";
const char dg_forthlinkdefinitionname[]                 = "LINKDEFINITION";
const char dg_forthlinkwordname[]                       = "LINKWORD";
const char dg_forthnewsubroutinedefinitionname[]        = "NEWSUBROUTINEDEFINITION";
const char dg_forthnewvariabledefinitionname[]          = "NEWVARIABLEDEFINITION";
const char dg_forthnewconstantdefinitionname[]          = "NEWCONSTANTDEFINITION";
const char dg_forthgetnewestdefinitioninwordlistname[]  = "GETNEWESTDEFINITIONINWORDLIST";
const char dg_forthgetnextdefinitionname[]              = "GETNEXTDEFINITION";
const char dg_forthfinddefinitioninwordlistname[]       = "FINDDEFINITIONINWORDLIST";
const char dg_forthfinddefinitioninsearchordername[]    = "FINDDEFINITIONINSEARCHORDER";
const char dg_forthputnewestdefinitioncompiletypename[] = "PUTNEWESTDEFINITIONCOMPILETYPE";
const char dg_forthtocurrentname[]                      = ">CURRENT";
const char dg_forthcurrentfromname[]                    = "CURRENT>";
const char dg_forthsearchorderdropname[]                = "SEARCH-ORDER-DROP";
const char dg_forthbracketsearchorderdropname[]         = "[SEARCH-ORDER-DROP]";
const char dg_forthbrackettoorderconstantname[]         = "[>ORDER]CONSTANT";
const char dg_forthwordlistdotname[]                    = "WORDLIST.";
const char dg_forthbracketwordlistdotname[]             = "[WORDLIST.]";
const char dg_forthlibdotname[]                         = "LIB.";
// const char dg_forthbracketlibname[]                     = "[LIB.]";
// const char dg_forthcreatewordlistdotname[]              = "CREATE-WORDLIST.";
const char dg_forthcreatebracketwordlistdotname[]       = "CREATE-[WORDLIST.]";
const char dg_forthcreatebracketlibdotname[]            = "CREATE-[LIB.]";

// dg_forthcreatebracketwordlistdotname

// forth variable names
const char dg_forthpbyeflagname[]                  = "PBYEFLAG";
const char dg_forthpnopromptsflagname[]            = "PNOPROMPTSFLAG";
const char dg_forthpcurrentinputbuffername[]       = "PCURRENTINPUTBUFFER";
const char dg_forthpjumpbuffervariablename[]       = "PJUMPBUFFERVARIABLE";
const char dg_forthpcurrentcompilebuffername[]     = "PCURRENTCOMPILEBUFFER";
const char dg_forthpcurrentcreatewordlistname[]    = "PCURRENTCREATEWORDLIST";
const char dg_forthpcurrentnewvariablebuffername[] = "PCURRENTNEWVARIABLEBUFFER";
const char dg_forthpquitwasinitflagname[]          = "PQUITWASINITFLAG";
const char dg_forthpshowerrorsonexitflagname[]     = "PSHOWERRORSONEXITFLAG";
const char dg_forthpcoloncallssafeflagname[]       = "PCOLONCALLSSAFEFLAG";
const char dg_forthpprecisionname[]                = "PPRECISION";

const char dg_patchdestnamedbufname[]         = "PPATCHDESTNAMEDBUF";
const char dg_patchsrcnamedbufname[]          = "PPATCHSRCNAMEDBUF";
const char dg_patchsrcnamedlibname[]          = "PPATCHSRCNAMEDLIB";
const char dg_patchsrcnamedsymbollistname[]   = "PPATCHSRCNAMEDSYMBOLLIST";
const char dg_patchdestnamedsymbollistname[]  = "PPATCHDESTNAMEDSYMBOLLIST";
const char dg_currentnewsymbolhlistidname[]   = "PCURRENTNEWSYMBOLLISTHLISTID";
const char dg_currentnewsymbolelementidname[] = "PCURRENTNEWSYMBOLLISTELEMENTID";
const char dg_currentglulisthlistidname[]     = "PCURRENTGLULISTHLISTID";
const char dg_currentnewlinkelementidname[]   = "PCURRENTNEWLINKELEMENTID";
const char dg_x86asmaddresssizename[]         = "PX86ASMADDRESSSIZE";
const char dg_prsdepthname[]                  = "PRSDEPTH";
const char dg_pnumberofintparamsname[]        = "PNUMBEROFINTPARAMS";
const char dg_pnumberoffloatparamsname[]      = "PNUMBEROFFLOATPARAMS";



// forth environment word names
const char dg_forthenvironmentwordlistname[] = "ENVIRONMENT-WORDLIST";
const char dg_forthslashcountedstringname[]  = "/COUNTED-STRING";
const char dg_forthslashholdname[]           = "/HOLD";
const char dg_forthslashpadname[]            = "/PAD";
const char dg_forthaddressunitbitsname[]     = "ADDRESS-UNIT-BITS";
const char dg_forthcorename[]                = "CORE";
const char dg_forthcoreextname[]             = "CORE-EXT";
const char dg_forthfloatingname[]            = "FLOATING";
const char dg_forthfloatingextname[]         = "FLOATING-EXT";
const char dg_forthfloatingstackname[]       = "FLOATING-STACK";
const char dg_forthflooredname[]             = "FLOORED";
const char dg_forthmaxcharname[]             = "MAX-CHAR";
const char dg_forthmaxdname[]                = "MAX-D";
const char dg_forthmaxfloatname[]            = "MAX-FLOAT";
const char dg_forthmaxnname[]                = "MAX-N";
const char dg_forthmaxuname[]                = "MAX-U";
const char dg_forthmaxudname[]               = "MAX-UD";
const char dg_forthreturnstackcellsname[]    = "RETURN-STACK-CELLS";
const char dg_forthstackcellsname[]          = "STACK-CELLS";
const char dg_forthsearchordername[]         = "SEARCH-ORDER";
const char dg_forthsearchorderextname[]      = "SEARCH-ORDER-EXT";
const char dg_forthwordlistsname[]           = "WORDLISTS";


// forth buffer word names
const char dg_forthbufferwordlistname[]      = "BUFFER-WORDLIST";

const char dg_forthdepthlstringname[]        = "DEPTHL$";
const char dg_forthstartoffsetlstringname[]  = "STARTOFFSETL$";
const char dg_forthgetstartoffsetlstringnname[] = "GETSTARTOFFSETL$[N]";
const char dg_forthlengthlstringname[]       = "LENGTHL$";
const char dg_forthlengthlstringnname[]      = "LENGTHL$[N]";
const char dg_forthgetplstringname[]         = "GETPL$"; // deprecated
const char dg_forthgetslstringnname[]        = "GETSL$[N]";
const char dg_forthgetlstringname[]          = "GETL$";
const char dg_forthcopylstringntosname[]     = "COPYL$[N]>S";
const char dg_forthlstringsfetchname[]       = "L$S@";   // DROPL$>PASTES
const char dg_forthlstringtosname[]          = "DROPL$>S"; // DROPL$>PASTES
const char dg_forthstolstringname[]          = "S>NEWL$"; // COPYS>NEWL$
const char dg_forthgrowlstringname[]         = "GROWL$";
const char dg_forthshortenlstringname[]      = "SHORTENL$";
const char dg_forthpicklstringname[]         = "PICKL$";
const char dg_forthdroplstringname[]         = "DROPL$";
const char dg_forthdeletelstringname[]       = "DELETEL$";
const char dg_forthdeletelstringnname[]      = "DELETEL$[N]";
const char dg_forthinsertlstringname[]       = "INSERTL$";
const char dg_forthinsertlstringnname[]      = "INSERTL$[N]";
const char dg_forthnewlstringname[]          = "NEWL$";
const char dg_forthcscanlstringname[]        = "CSCANL$";
const char dg_forthcscanlstringnname[]       = "CSCANL$[N]";
const char dg_forthscanlstringname[]         = "SCANL$";
const char dg_forthscanlstringnname[]        = "SCANL$[N]";
const char dg_forthrolllstringname[]         = "ROLLL$";
const char dg_forthminusrolllstringname[]    = "-ROLLL$";
const char dg_forthdeleteinlstringname[]     = "DELETEINL$";
const char dg_forthdeleteinlstringnname[]    = "DELETEINL$[N]";
const char dg_forthinsertinlstringname[]     = "INSERTINL$";
const char dg_forthinsertinlstringnname[]    = "INSERTINL$[N]";
const char dg_forthcatlstringnname[]         = "CATL$[N]";
const char dg_forthcopystolstringnname[]     = "COPYSTOL$[N]";
const char dg_forthcopysfromlstringnname[]   = "COPYSFROML$[N]";
const char dg_forthsetlengthlstringnname[]   = "SETLENGTHL$[N]";
const char dg_forthcopystoreplacelstringnname[] = "COPYS>REPLACEL$[N]";
const char dg_forthcopylstringntoreplacelstringnname[] = "COPYL$[N]>REPLACEL$[N]";
const char dg_forthnewfreeablelstringarrayname[] = "NEWFL$[]";
const char dg_forthfreefreeablelstringarrayname[] = "FREEFL$[]";
const char dg_forthpacklstringname[]         = "PACKL$[]";
const char dg_forthunpacklstringname[]       = "UNPACKL$[]";
const char dg_forthnotlstringnname[]               = "NOTL$[N]";
const char dg_forthu8reverselstringnname[]         = "U8REVERSEL$[N]";
const char dg_forthuleextendlstringntolname[]      = "ULEEXTENDL$[N]TOL";
const char dg_forthuleandlstringntolstringnname[]  = "ULEANDL$[N]>L$[N]";
const char dg_forthuleorlstringntolstringnname[]   = "ULEORL$[N]>L$[N]";
const char dg_forthulexorlstringntolstringnname[]  = "ULEXORL$[N]>L$[N]";
const char dg_forthulenandlstringntolstringnname[] = "ULENANDL$[N]>L$[N]";
const char dg_forthulenorlstringntolstringnname[]  = "ULENORL$[N]>L$[N]";
const char dg_forthulexnorlstringntolstringnname[] = "ULEXNORL$[N]>L$[N]";
const char dg_forthuleaddlstringntolstringnname[]  = "ULEADDL$[N]>L$[N]";
const char dg_forthuleadclstringntolstringnname[]  = "ULEADCL$[N]>L$[N]";
const char dg_forthulesbblstringntolstringnname[]  = "ULESBBL$[N]>L$[N]";
const char dg_forthlelshiftlstringnname[]          = "LELSHIFTL$[N]";
const char dg_forthulershiftlstringnname[]         = "ULERSHIFTL$[N]";
const char dg_forthslershiftlstringnname[]         = "SLERSHIFTL$[N]";
const char dg_forthlelshiftclstringnname[]         = "LELSHIFTCL$[N]";
const char dg_forthlershiftclstringnname[]         = "LERSHIFTCL$[N]";
const char dg_forthu64starlstringnplustolstringnname[] = "U64*L$[N]+>L$[N]";
const char dg_forthtoslashulelstringnname[]        = ">/ULEL$[N]";


const char dg_forthocfetchname[]             = "OC@";
const char dg_forthgetbufferbytename[]       = "GETBUFFERBYTE";
const char dg_forthofetchname[]              = "O@";
const char dg_forthgetbufferuint64name[]     = "GETBUFFERUINT64";
const char dg_forthostonewstringname[]       = "OS>NEW$";
const char dg_forthocstorename[]             = "OC!";
const char dg_forthputbufferbytename[]       = "PUTBUFFERBYTE";
const char dg_forthostorename[]              = "O!";
const char dg_forthotwostorename[]           = "O2!";
const char dg_forthputbufferuint64name[]     = "PUTBUFFERUINT64";
const char dg_forthctobufname[]              = "C>BUF";
const char dg_forthtobufname[]               = ">BUF";
const char dg_forthstringtobufname[]         = "$>BUF";
const char dg_forthbuftocname[]              = "BUFC>";
const char dg_forthbuftoname[]               = "BUF>";
const char dg_forthbuftostringname[]         = "BUF$>"; // ?
const char dg_forthosstorename[]             = "OS!";
const char dg_forthosfetchname[]             = "OS@";
const char dg_forthstobufname[]              = "S>BUF";
const char dg_forthbuftosname[]              = "BUF>S";
const char dg_forthlengthbufname[]           = "LENGTHBUF";
const char dg_forthgetpbufferhandlearrayheadname[] = "GETPBUFFERHANDLEARRAYHEAD";
const char dg_forthgetsbufferhandlearrayheadname[] = "GETSBUFFERHANDLEARRAYHEAD";
const char dg_forthgetpbufferhandlename[]    = "GETBUFFERHANDLE";
const char dg_forthgetsbufferhandlename[]    = "GETSBUFFERHANDLE";
const char dg_forthgetbuffersizename[]       = "GETBUFFERSIZE";
const char dg_forthgetbufferlengthname[]     = "GETBUFFERLENGTH";
const char dg_forthgetbuffermaxsizename[]    = "GETBUFFERMAXSIZE";
const char dg_forthgetbuffergrowbyname[]     = "GETBUFFERGROWBY";
const char dg_forthgetbuffercurrentoffsetname[] = "GETBUFFERCURRENTOFFSET";
const char dg_forthputbuffercurrentoffsetname[] = "PUTBUFFERCURRENTOFFSET";
const char dg_forthgetpbufferlengthname[]    = "GETPBUFFERLENGTH";
const char dg_forthgetpbuffercurrentoffsetname[] = "GETPBUFFERCURRENTOFFSET";
const char dg_forthgetoarrayelementname[]    = "GETOARRAYELEMENT";
const char dg_forthgetparrayelementname[]    = "GETPARRAYELEMENT";
const char dg_forthinsertinbuffername[]      = "INSERTINBUFFER";
const char dg_forthdeleteinbuffername[]      = "DELETEINBUFFER";
const char dg_forthreplaceinbuffername[]     = "REPLACEINBUFFER";
const char dg_forthinsertsintobuffername[]   = "INSERTSINTOBUFFER";
const char dg_forthgrowbuffername[]          = "GROWBUFFER";
const char dg_forthshrinkbuffername[]        = "SHRINKBUFFER";
const char dg_forthemptybuffername[]         = "EMPTYBUFFER";
const char dg_forthnewbuffername[]           = "NEWBUFFER";
const char dg_forthfreebuffername[]          = "FREEBUFFER";
const char dg_forthgetpbufferoffsetname[]    = "GETPBUFFEROFFSET";
const char dg_forthotopname[]                = "O>P";
const char dg_forthgetpbuffername[]          = "GETPBUFFER";
const char dg_forthgetpbufferpbufferlengthname[] = "GETPBUFFERPBUFFERLENGTH";
const char dg_forthgetsbuffername[]          = "GETSBUFFER";
const char dg_forthgetpbuffersegmentname[]   = "GETPBUFFERSEGMENT";
const char dg_forthgetpnewbuffername[]      =  "GETPNEWBUFFER";

const char dg_forthmaxusedbuffersname[]      = "MAXUSEDBUFFERS";
const char dg_forthinusebuffersname[]        = "INUSEBUFFERS";
const char dg_forthinusebytesname[]          = "INUSEBYTES";
const char dg_forthallocatedbytesname[]      = "ALLOCATEDBYTES";

const char dg_forthcscanname[]              = "CSCAN";
const char dg_forthscanname[]               = "SCAN";

const char dg_forthlinecommentname[]        = "#!";
const char dg_forthslashslashname[]         = "//";

const char dg_forthu16storename[]           = "U16!";
const char dg_forthu32storename[]           = "U32!";
const char dg_forthu64storename[]           = "U64!";
const char dg_forthu128storename[]          = "U128!";

const char dg_forthu16fetchname[]           = "U16@";
const char dg_forthu32fetchname[]           = "U32@";
const char dg_forthu64fetchname[]           = "U64@";
const char dg_forthu128fetchname[]          = "U128@";

// const char dg_forthu16commaname[]           = "U16,";
const char dg_forthu32commaname[]           = "U32,";
const char dg_forthu64commaname[]           = "U64,";
// const char dg_forthu128commaname[]          = "U128,";
const char dg_forthof64storename[]          = "OF64!";
const char dg_forthubufalignname[]          = "UBUFALIGN";

// buffer id names
const char dg_fortherrorstackbufferidname[]          = "ERRORSTACKBUFFERID";
const char dg_forthdatastackbufferidname[]           = "DATASTACKBUFFERID";
const char dg_forthstringstackoffsetbufferidname[]   = "$STACKOFFSETBUFFERID";
const char dg_forthstringstackstringbufferidname[]   = "$STACKSTRINGBUFFERID";
const char dg_forthdataspacebufferidname[]           = "DATASPACEBUFFERID";
const char dg_forthrstackbufferidname[]              = "RSTACKBUFFERID";
const char dg_forthsearchorderstackbufferidname[]    = "SEARCHORDERSTACKBUFFERID";
const char dg_forthterminalinputbufferidname[]       = "TERMINALINPUTBUFFERID";
const char dg_forthholdbufferidname[]                = "HOLDBUFFERID";
const char dg_forthpadbufferidname[]                 = "PADBUFFERID";
const char dg_forthwordlistbufferidname[]            = "WORDLISTBUFFERID";
const char dg_forthdefinitionbufferidname[]          = "DEFINITIONBUFFERID";
const char dg_forthnameoffsetbufferidname[]          = "NAMEOFFSETBUFFERID";
const char dg_forthnamestringbufferidname[]          = "NAMESTRINGBUFFERID";
const char dg_forthwordbufferidname[]                = "WORDBUFFERID";
const char dg_forthleavebufferidname[]               = "LEAVEBUFFERID";
const char dg_forthargsbufferidname[]                = "ARGSBUFFERID";
const char dg_forthcleanupbufferidname[]             = "CLEANUPBUFFERID";
const char dg_forthlibhandlebufferidname[]           = "LIBHANDLEBUFFERID";
const char dg_forthpostbufferidname[]                = "POSTBUFFERID";
const char dg_forthscriptfilenamebufferidname[]      = "SCRIPTFILENAMEBUFFERID";
const char dg_forthlocalpathbufferidname[]           = "LOCALPATHBUFFERID";
const char dg_forthwordnamebufferidname[]            = "WORDNAMEBUFFERID";
const char dg_forthextendablecodespacebufferidname[] = "EXTENDABLECODESPACEBUFFERID";
const char dg_forthextendabledataspacebufferidname[] = "EXTENDABLEDATASPACEBUFFERID";
const char dg_forthcorebufferidname[]                = "COREBUFFERID";
const char dg_forthhlistheaderarraybufferidname[]    = "HLISTHEADERARRAYBUFFERID";
const char dg_linknewbufstackbufferidname[]          = "LINKNEWBUFFERIDSTACKBUFFERID";
const char dg_forthhstackbufferidname[]              = "HSTACKBUFFERID";
const char dg_forthf64stackbufferidname[]            = "F64STACKBUFFERID";


// forth string word names
const char dg_forthstringwordlistname[]              = "$-WORDLIST";

const char dg_forthnumbersignstringname[]            = "#$";
const char dg_forthnumbersigngreaterthanstringname[] = "#>$";
const char dg_forthnumbersignsstringname[]           = "#S$";
const char dg_forthstringquotesname[]                = "$\"";
const char dg_forthstringtoname[]                    = "$>";
const char dg_forthstringtostringname[]              = "$>$";
const char dg_forthturnstringinto0stringname[]       = "$>0$";
const char dg_forthstringtocname[]                   = "$>C";
const char dg_forthstringcstorename[]                = "$C!";
const char dg_forthstringcfetchname[]                = "$C@";
const char dg_forthminuscscanstringname[]            = "-CSCAN$";
const char dg_forthminusrollstringname[]             = "-ROLL$";
const char dg_forthprintstringname[]                 = ".$";
const char dg_forthdotstringsname[]                  = ".$S";
const char dg_forthlessthannumbersignstringname[]    = "<#$";
const char dg_forthequalstringname[]                 = "=$";
const char dg_forthtostringname[]                    = ">$";
const char dg_forthtonewstringname[]                 = ">NEW$";
const char dg_forthqueryincludefilestringname[]      = "?INCLUDEFILE$";
const char dg_forthasciitounicodestringname[]        = "ASCII>UNICODE$";
const char dg_forthctostringname[]                   = "C>$";
const char dg_forthctonewstringname[]                = "C>NEW$";
const char dg_forthcatstringndname[]                 = "CAT$[ND]";
const char dg_forthcatstringname[]                   = "CATENATE$";
const char dg_forthcomparestringname[]               = "COMPARE$";
const char dg_forthcscanstringname[]                 = "CSCAN$";
const char dg_forthdeletestringname[]                = "DELETE$";
const char dg_forthdeleteinstringname[]              = "DELETEIN$";
const char dg_forthdeleteinstringndname[]            = "DELETEIN$[ND]";
const char dg_forthdepthstringname[]                 = "DEPTH$";
const char dg_forthdropstringname[]                  = "DROP$";
const char dg_forthdupstringname[]                   = "DUP$";
const char dg_forthgetenvstringname[]                = "GETENV$";
const char dg_forthgetmethodstringname[]             = "GETMETHOD$";
const char dg_forthgetmidstringname[]                = "GETMID$";
const char dg_forthgetpstringname[]                  = "GETP$";
const char dg_forthgetquerystringname[]              = "GETQUERY$";
const char dg_forthgetsstringndname[]                = "GETS$[ND]";
const char dg_forthgrowstringname[]                  = "GROW$";
const char dg_forthholdstringname[]                  = "HOLD$";
const char dg_forthincludefilestringname[]           = "INCLUDEFILE$";
const char dg_forthinsertinstringname[]              = "INSERTIN$";
const char dg_forthinsertinstringndname[]            = "INSERTIN$[ND]";
const char dg_forthlengthstringname[]                = "LENGTH$";
const char dg_forthloadfilestringname[]              = "LOADFILE$";
const char dg_forthnewstringname[]                   = "NEW$";
const char dg_forthnipstringname[]                   = "NIP$";
const char dg_forthoverstringname[]                  = "OVER$";
const char dg_forthpickstringname[]                  = "PICK$";
const char dg_forthputmidstringname[]                = "PUTMID$";
const char dg_forthrollstringname[]                  = "ROLL$";
const char dg_forthrotstringname[]                   = "ROT$";
const char dg_forthstostringname[]                   = "S>NEW$";
const char dg_forthsavefilestringname[]              = "SAVEFILE$";
const char dg_forthshortenstringname[]               = "SHORTEN$";
const char dg_forthsignstringname[]                  = "SIGN$";
const char dg_forthsplitstringname[]                 = "SPLIT$";
const char dg_forthstripstringname[]                 = "STRIP$";
const char dg_forthstrippathfromfilenamestringname[] = "STRIPPATHFROMFILENAME$";
const char dg_forthvariableflstringname[]            = "VARIABLEFL$";
const char dg_forthswapstringname[]                  = "SWAP$";
const char dg_forthunicodetoasciistringname[]        = "UNICODE>ASCII$";
const char dg_forthurldecodestringname[]             = "URLDECODE$";
const char dg_forthurlencodestringname[]             = "URLENCODE$";
const char dg_forthbackslashstringtostringname[]     = "\\$>$";
const char dg_forthstringtobackslashstringname[]     = "$>\\$";
const char dg_forthfillnewstringname[]               = "FILL-NEW$";
const char dg_forthpzerostrtonewstrname[]            = "P0$>NEW$";
const char dg_forthnglufilestringname[]              = "NGLUFILE$";
const char dg_forthglufilestringname[]               = "GLUFILE$";
const char dg_forthwordsstringquotesname[]           = "WORDS$\"";
const char dg_forthwords0stringquotesname[]          = "WORDS0$\"";
const char dg_forthgetargsfromnstringsname[]         = "GETARGSFROMN$S";
const char dg_forthumulleutostringname[]             = "UMULLEU>$";
const char dg_forthtostarulestringname[]             = ">*ULE$";
const char dg_forthtoslashulestringname[]            = ">/ULE$";
const char dg_forthtofactorialulestringname[]        = ">FACTORIALULE$";
const char dg_forthreversestringname[]               = "REVERSE$";
const char dg_forthnotstringname[]                   = "NOT$";
const char dg_forthuleandstringname[]                = "ULEAND$";
const char dg_forthuleorstringname[]                 = "ULEOR$";
const char dg_forthulexorstringname[]                = "ULEXOR$";
const char dg_forthulenandstringname[]               = "ULENAND$";
const char dg_forthulenorstringname[]                = "ULENOR$";
const char dg_forthulexnorstringname[]               = "ULEXNOR$";
const char dg_forthlelshiftstringname[]              = "LELSHIFT$";
const char dg_forthulershiftstringname[]             = "ULERSHIFT$";
const char dg_forthslershiftstringname[]             = "SLERSHIFT$";
const char dg_forthlelshiftcstringname[]             = "LELSHIFTC$";
const char dg_forthlershiftcstringname[]             = "LERSHIFTC$";
const char dg_forthulestringtonumberstringname[]     = "ULE$>NUMBER$";
const char dg_forthrunfileandwaitnoenvquotesname[]   = "RUNFILEANDWAITNOENV\"";
const char dg_forthrunfileandwaitnoenvstringname[]   = "RUNFILEANDWAITNOENV$";
const char dg_forthsetlengthstringname[]             = "SETLENGTH$";



// forth operating system word names
const char dg_forthwindowswordlistname[]          = "OS-WORDLIST";
const char dg_forthfreelibraryname[]              = "FREELIBRARY";
const char dg_forthcallprocaddressname[]          = "CALLPROC";
const char dg_forthcallcdeclname[]                = "CALLCDECL";
const char dg_forthcallstdcallname[]              = "CALLSTDCALL";
const char dg_forthcallcppmembername[]            = "CALLC++MEMBER";
const char dg_forthcallprocaddressretuint128name[] = "CALLPROCRETUINT128";
const char dg_forthcallcdeclretuint128name[]       = "CALLCDECLRETUINT128";
const char dg_forthcallstdcallretuint128name[]     = "CALLSTDCALLRETUINT128";
const char dg_forthcallcppmemberretuint128name[]   = "CALLC++MEMBERRETUINT128";
const char dg_forthcallcppmemberfunctionname[]    = "CALLWIN32C++MEMBER";
const char dg_forthcalldfpprocname[]              = "CALLDFPPROC";
const char dg_forthregsfromname[]                 = "REGS>";
const char dg_forthtoregsname[]                   = ">REGS";
const char dg_forthshowcapturedregsname[]         = "SHOW-CAPTURED-REGS";
// const char dg_forthtofp0name[]                    = ">FP0";
// const char dg_forthfp0fromname[]                  = "FP0>";
// const char dg_forthfsfromname[]                   = "FS>";
// const char dg_forthf32fromname[]                  = "F32>";
// const char dg_forthf64fromname[]                  = "F64>";

const char dg_forthrunfileandwaitname[]           = "RUNFILEANDWAIT";

// forth user wordlist word names
const char dg_forthuserwordlistname[]             = "USER-WORDLIST";


// forth error word names
const char dg_fortherrorwordlistname[]            = "ERROR-WORDLIST";

const char dg_successname[]                       = "SUCCESS";

const char dg_noerroryetname[]                    = "NOERRORYET";
const char dg_incrementingerrorcountname[]        = "ERRORINCREMENTINGERRORCOUNT";

const char dg_noerrorsname[]                      = "NOERRORS";
const char dg_errorbufnotinbharrayname[]          = "ERRORSTACKBUFFERMISSINGERROR";
const char dg_errorbufisfreename[]                = "ERRORSTACKBUFFERISFREEERROR";
const char dg_errorbufgrowbynesizenemaxsizename[] = "ERRORSTACKBUFFERGROWABLEERROR";
const char dg_errorbufnubcorruptname[]            = "ERRORSTACKBUFFERCORRUPT";
const char dg_errorunderflowname[]                = "ERRORSTACKUNDERFLOWERROR";
const char dg_erroroverflowname[]                 = "ERRORSTACKOVERFLOWERROR";
const char dg_errornotthatmanyerrorsname[]        = "NOTTHATMANYERRORS";

const char dg_errorsbufidis0name[]                = "ERRORSBUFFERIS0ERROR";
const char dg_errorsbufidnotinbharrayname[]       = "ERRORSBUFFERMISSINGERROR";
const char dg_errorsbufidisfreename[]             = "ERRORSBUFFERISFREEERROR";
const char dg_errorsbufidnubcorruptname[]         = "ERRORSBUFFERLENGTHCORRUPTERROR";
const char dg_errorsbufidsizecorruptname[]        = "ERRORSBUFFERSIZECORRUPTERROR";
const char dg_errorsoffsetpastendname[]           = "ERRORGOESPASTENDOFBUFFERERROR";

const char dg_errorinsubroutinename[]             = "SUBROUTINEERROR";
const char dg_osexceptionname[]                   = "OSEXCEPTION";
const char dg_oserrorname[]                       = "OSERROR";
const char dg_badmemoryerrorname[]                = "BADMEMORYERROR";
const char dg_outofmemoryerrorname[]              = "OUTOFMEMORYERROR";
const char dg_nullpbharrayheaderrorname[]         = "NULLPBHARRAYHEADERROR";
const char dg_bharrayheadbadmemerrorname[]        = "BHARRAYHEADBADMEMORYERROR";
const char dg_notbharrayheaderrorname[]           = "NOTBHARRAYHEADERROR";
const char dg_nullpbharrayerrorname[]             = "NULLPBHARRAYERROR";
const char dg_bharraybadmemerrorname[]            = "BHARRAYBADMEMORYERROR";

const char dg_buffernubcorruptname[]              = "BUFFERLENGTHCORRUPTERROR";
const char dg_bufferidnotinbharrayname[]          = "BUFFERNOTEXISTERROR";
const char dg_bufferidisfreename[]                = "BUFFERISFREEERROR";
const char dg_bufferidisnotfreename[]             = "BUFFERISNOTFREEERROR";
const char dg_bufferunderflowname[]               = "BUFFERUNDERFLOWERROR";
const char dg_buffergrowbycorruptname[]           = "BUFFERGROWBYCORRUPTERROR";
const char dg_buffersizecorruptname[]             = "BUFFERSIZECORRUPTERROR";
const char dg_buffermaxsizecorruptname[]          = "BUFFERMAXSIZECORRUPTERROR";
const char dg_buffermaxsizeltsizename[]           = "BUFFERMAXSIZE<SIZEERROR";
const char dg_maxsizeltgrowbyerrorname[]          = "MAXSIZE<GROWBYERROR";
const char dg_bufferidisforerrorstackname[]       = "BUFFERIDISFORERRORSTACKERROR";

const char dg_nullpointererrorname[]              = "NULLPOINTERERROR";
const char dg_offsetpastenderrorname[]            = "OFFSETPASTENDERROR";
const char dg_segmentgoespastenderrorname[]       = "SEGMENTGOESPASTENDERROR";
const char dg_lstringoffsetpastenderrorname[]     = "LSTRINGOFFSETPASTENDERROR";
const char dg_lstringsegmentgoespastenderrorname[] = "LSTRINGSEGMENTGOESPASTENDERROR";

const char dg_buffergrowby0errorname[]            = "GROWBY0ERROR";
const char dg_bufferfullerrorname[]               = "BUFFERFULLERROR";

const char dg_indexnotinarrayerrorname[]          = "INDEXNOTINARRAYERROR";
const char dg_lstringidtoohigherrorname[]         = "L$[]TOOHIGHERROR";
const char dg_lstringsoffsetscorruptname[]        = "L$OFFSETCORRUPTERROR";
const char dg_lstringtopoffsetwasbadname[]        = "L$TOPOFFSETBADERROR";
const char dg_lstringstackdepthcorruptname[]      = "L$DEPTHERROR";
const char dg_toobigfordesterrorname[]            = "TOOBIGFORDESTERROR";

const char dg_wordidtoobigerrorname[]             = "WORDIDTOOBIGERROR";
const char dg_wordlistidtoobigerrorname[]         = "WORDLISTIDTOOBIGERROR";
const char dg_wordalreadylinkederrorname[]        = "WORDALREADYLINKEDERROR";
const char dg_newwordoldererrorname[]             = "NEWWORDOLDERERROR";
const char dg_wordnotfoundinsearchordererrorname[] = "WORDNOTFOUNDERROR";

const char dg_BHarraygrowby0errorname[]           = "BHARRAYGROWBY0ERROR";
const char dg_BHarraymaxsizeltgrowbyname[]        = "BHARRAYMAXSIZELTGROWBYERROR";
const char dg_BHarraymaxsizeltbhsizename[]        = "BHARRAYMAXSIZELTSIZEERROR";
const char dg_BHarraynubcorruptname[]             = "BHARRAYNUBCORRUPTERROR";
const char dg_BHarraynubgtsizename[]              = "BHARRAYNUBGTSIZEERROR";
const char dg_BHarrayfullname[]                   = "BHARRAYFULLERROR";

const char dg_initerrorsbuf0inusename[]           = "INITERRORSBUF0INUSEERROR";

const char dg_filenotfounderrorname[]             = "FILENOTFOUNDERROR";
const char dg_pathnotfounderrorname[]             = "PATHNOTFOUNDERROR";
const char dg_accessdeniederrorname[]             = "ACCESSDENIEDERROR";
const char dg_toomanyopenfileserrorname[]         = "TOOMANYOPENFILESERROR";
const char dg_drivenotfounderrorname[]            = "DRIVENOTFOUNDERROR";
const char dg_devicenotfounderrorname[]           = "DEVICENOTFOUNDERROR";
const char dg_devicenotreadyerrorname[]           = "DEVICENOTREADYERROR";
const char dg_filesystemunknownerrorname[]        = "FILESYSTEMUNKNOWNERROR";
const char dg_devicebrokenerrorname[]             = "DEVICEBROKENERROR";
const char dg_fileinuseerrorname[]                = "FILEINUSEERROR";
const char dg_fileislockederrorname[]             = "FILEISLOCKEDERROR";
const char dg_filesystemcorrupterrorname[]        = "FILESYSTEMCORRUPTERROR";
const char dg_filetoobigerrorname[]               = "FILETOOBIGERROR";
const char dg_filetypeunknownerrorname[]          = "FILETYPEUNKNOWNERROR";
const char dg_osdidlessthanavailableerrorname[]   = "OSDIDLESSTHANAVAILABLEERROR";
const char dg_invalidparametererrorname[]         = "INVALIDPARAMETERERROR";

const char dg_writeprotectederrorname[]           = "WRITEPROTECTEDERROR";
const char dg_diskisfullerrorname[]               = "DISKISFULLERROR";

const char dg_crcerrorname[]                      = "CRCERROR";
const char dg_invalidhandleerrorname[]            = "OSINVALIDHANDLEERROR";
const char dg_outsideofbuffererrorname[]          = "OUTSIDEOFBUFFERERROR";

const char dg_datastackmisalignederrorname[]      = "DATASTACKMISALIGNEDERROR";
const char dg_datastackunderflowerrorname[]       = "DATASTACKUNDERFLOWERROR";
const char dg_datastacknoraddrmissingerrorname[]  = "DATASTACKNMISSINGERROR";
const char dg_rstackunderflowerrorname[]          = "RSTACKUNDERFLOWERROR";
const char dg_stringstackunderflowerrorname[]     = "STRINGSTACKUNDERFLOWERROR";
const char dg_lstringstackunderflowerrorname[]    = "LSTRINGSTACKUNDERFLOWERROR";
const char dg_underflowerrorname[]                = "UNDERFLOWERROR";
const char dg_arraymisalignederrorname[]          = "ARRAYMISALIGNEDERROR" ;
const char dg_alreadyfreeerrorname[]              = "ALREADYFREEERROR";
const char dg_wasnottrulyfreeerrorname[]          = "NOTTRULYFREEERROR";

const char dg_emptystringerrorname[]              = "EMPTYSTRINGERROR";
const char dg_stringunderflowerrorname[]          = "STRINGUNDERFLOWERROR";
const char dg_wordlength0errorname[]              = "WORDLENGTH0ERROR";
const char dg_maxwordlengthexceedederrorname[]    = "MAXWORDLENGTHEXCEEDEDERROR";

const char dg_basetoolowerrorname[]               = "BASETOOLOWERROR";
const char dg_basetoohigherrorname[]              = "BASETOOHIGHERROR";
//const char dg_dglubufferinvaliderrorname        = "DGLUBUFFERINVALIDERROR";


// Forth Hierarchical List Names
const char dg_forthnewhlistname[]                = "NEW-HLIST";
const char dg_forthfreehlistname[]               = "FREE-HLIST";
const char dg_forthprunehlistelementname[]       = "PRUNE-ELEMENT";
const char dg_forthfreehlistelementname[]        = "FREE-ELEMENT";
const char dg_forthnewhlistelementname[]         = "NEW-ELEMENT";
const char dg_forthgethlistelementnomname[]      = "GET-ELEMENT-NAME$"; // COPY-ELEMENT-NAME>NEW$
const char dg_forthgethlistelementvaluename[]    = "GET-ELEMENT-VALUE$"; // COPY-ELEMENT-VALUE>NEW$
const char dg_forthgethlistnewestchildname[]     = "GET-ELEMENT-NEWEST-CHILD"; // GET-NEWEST-CHILD
const char dg_forthgethlistoldestchildname[]     = "GET-ELEMENT-OLDEST-CHILD"; // GET-NEWEST-CHILD
const char dg_forthgethlistoldersiblingname[]    = "GET-ELEMENT-OLDER-SIBLING"; // GET-OLDER-SIBLING
const char dg_forthgethlistnewersiblingname[]    = "GET-ELEMENT-NEWER-SIBLING"; // GET-NEWER-SIBLING
const char dg_forthchangehlistparentname[]       = "SET-ELEMENT-PARENT"; // SET-PARENT
const char dg_forthfindclosesthlistchildname[]   = "FIND-CLOSEST-ELEMENT-CHILD-BY-NAME$"; // FIND-CLOSEST-CHILD-BY-NAME$ FIND-CLOSEST-CHILD
const char dg_forthhlisttoxmlstringname[]        = "ELEMENT>DGLUML$";
const char dg_forthgethowmanyhlistkidsname[]     = "GET-ELEMENT-NUMBER-OF-SORTED-CHILDREN";
const char dg_forthgethlistsortedchildnname[]    = "FIND-ELEMENT-CHILD-N"; // FIND-CHILD-N
const char dg_forthfindhlistchildname[]          = "FIND-ELEMENT-CHILD-BY-NAME$"; // FIND-CHILD-BY-NAME$
const char dg_forthhfindstringname[]             = "HFIND$";
const char dg_forthgethlistparentname[]          = "GET-ELEMENT-PARENT"; // GET-PARENT
const char dg_forthsethlistelementvaluename[]    = "SET-ELEMENT-VALUE$";
const char dg_forthpackhlistname[]               = "PACK-HLIST";
const char dg_forthunpackhlistname[]             = "UNPACK-HLIST";
const char dg_forthtoehname[]                    = ">EH";
const char dg_forthehfromname[]                  = "EH>";
const char dg_forthdropehname[]                  = "DROPEH";
const char dg_forthehtopname[]                   = "EH[TOP]";
const char dg_forthehndname[]                    = "EH[ND]";
const char dg_forthdupehname[]                   = "DUPEH";
const char dg_forthehname[]                      = "EH";
const char dg_forthetoehtopname[]                = "E>EH[TOP]";
const char dg_forthehnewelementname[]            = "EH-NEW-ELEMENT";
const char dg_forthehnewelementtoehname[]        = "EH-NEW-ELEMENT>EH";
const char dg_forthnamestrtovaluestrname[]       = "NAME$>VALUE$";
const char dg_forthnamestrtovaluename[]          = "NAME$>VALUE";
const char dg_forthehnamestrtovaluestrname[]     = "EH-NAME$>VALUE$";
const char dg_forthehnamestrtovaluename[]        = "EH-NAME$>VALUE";
const char dg_forthnamewtovaluestrname[]         = "NAMEW>VALUE$";
const char dg_forthnamewtovaluename[]            = "NAMEW>VALUE";
const char dg_forthehnamewtovaluestrname[]       = "EH-NAMEW>VALUE$";
const char dg_forthehnamewtovaluename[]          = "EH-NAMEW>VALUE";
const char dg_forthehoherewtonewelementname[]    = "EH-OHERE-W>NEW-ELEMENT";
const char dg_forthehdotname[]                   = "EH.";
const char dg_forthehbracketnddotname[]          = "EH[ND].";
const char dg_forthehbracket1ddotname[]          = "EH[1D].";
const char dg_forthsymbolenumcurlyname[]         = "SYMBOL-ENUM<";
const char dg_forthosymbolcodeimportscommacurlyname[] = "OSYMBOL-CODE-IMPORTS,<";
const char dg_forthnewflatosymbolbufname[]       = "NEW-FLAT-OSYMBOL-BUF";
const char dg_forthfreeflatosymbolbufname[]      = "FREE-FLAT-OSYMBOL-BUF";
const char dg_forthosymbolimportname[]           = "OSYMBOL-IMPORT";
const char dg_forthimportlinkdatasizename[]      = "IMPORT-LINK-DATA-SIZE";

// Forth Glu List Names
const char dg_forthgluelementname[]              = "GLU-ELEMENT";
const char dg_forthngluelementname[]             = "NGLU-ELEMENT";
const char dg_forthgluname[]                     = "GLU";
const char dg_forthngluname[]                    = "NGLU";
const char dg_forthnewnglulistname[]             = "NEW-NGLULIST";
const char dg_forthnewcurrentnglulistname[]      = "NEW-NGLULIST>EH";
const char dg_forthcreateimportcommaname[]       = "CREATE-IMPORT,";
const char dg_forthcreatecodelinkcommaname[]     = "CREATE-COMPILECALL-CODE-LINK,";
const char dg_forthcreateocodelinkcommaname[]    = "CREATE-O-CODE-LINK,";
const char dg_forthcreateobcodelinkcommaname[]   = "CREATE-OB-CODE-LINK,";
const char dg_forthcreatecdecllinkcommaname[]    = "CREATE-CDECL-CODE-LINK,";
const char dg_forthcreatecolonlinkcommaname[]    = "CREATE-:-CODE-LINK,";
const char dg_forthcreateodatalinkcommaname[]    = "CREATE-O-DATA-LINK,";
const char dg_forthcreateobdatalinkcommaname[]   = "CREATE-OB-DATA-LINK,";
const char dg_forthwtoimportcommaname[]          = "W>IMPORT,";
const char dg_forthwtolinkcommaname[]            = "W>LINK,";
const char dg_forthwtocodelinkcommaname[]        = "W>CODE-LINK,";
const char dg_forthwtodatalinkcommaname[]        = "W>DATA-LINK,";
const char dg_forthsymbolname[]                  = "SYMBOL";
const char dg_forthosymbolname[]                 = "OSYMBOL";
const char dg_forthosymbolentryname[]            = "OSYMBOL-ENTRY";
const char dg_forthstrtoimportcommaname[]        = "$>IMPORT,";
const char dg_forthstrtolinkcommaname[]          = "$>LINK,";
const char dg_forthstrtocodelinkcommaname[]      = "$>CODE-LINK,";
const char dg_forthstrtodatalinkcommaname[]      = "$>DATA-LINK,";

const char dg_wordlisthlistidname[]              = "WORDLIST-HLISTID";
const char dg_stringhlistidname[]                = "$-HLISTID";
const char dg_bufferhlistidname[]                = "BUFFER-HLISTID";
const char dg_symbollistshlistidname[]           = "SYMBOLLIST-HLISTID";
const char dg_libraryhlistidname[]               = "LIBRARY-HLISTID";

// Forth Glu List Names
const char dg_nglufuncbufsname[]            = "NGLU-BUFS";
const char dg_nglufunccallbufname[]         = "NGLU-CALLBUF";
const char dg_nglufunccallbuftodsname[]     = "NGLU-CALLBUF>";
const char dg_nglufunccalloffsetname[]      = "NGLU-CALLDESTOFFSET";
const char dg_nglufunccalloffsetodsname[]   = "NGLU-CALLDESTOFFSET>";
const char dg_nglufunccalllibname[]         = "NGLU-CALLLIB";
const char dg_nglufunccalllibtodsname[]     = "NGLU-CALLLIB>";
const char dg_nglufuncdestbufname[]         = "NGLU-DESTBUF";
const char dg_nglufuncdestsymbolsname[]     = "NGLU-DESTSYMBOLS";
const char dg_nglufuncfilesname[]           = "NGLU-FILES";
const char dg_nglufunchfilesname[]          = "NGLU-HFILES";
const char dg_nglufunchlistherename[]       = "NGLU-HLISTHERE";
const char dg_nglufunclibsname[]            = "NGLU-LIBS";
const char dg_nglufunclinkbufname[]         = "NGLU-LINKBUF";
const char dg_nglufunclinklibname[]         = "NGLU-LINKLIB";
const char dg_nglufunclinknewbufname[]      = "NGLU-LINKNEWBUF";
const char dg_nglufunclinkoffsetname[]      = "NGLU-LINKOFFSET";
const char dg_nglufuncngluname[]            = "NGLU-NGLU";
const char dg_nglufuncsrcbufname[]          = "NGLU-SRCBUF";
const char dg_nglufuncsrclibname[]          = "NGLU-SRCLIB";
const char dg_nglufuncsrcsymbolsname[]      = "NGLU-SRCSYMBOLS";
const char dg_nglufuncsymbolsname[]         = "NGLU-SYMBOLS";
const char dg_nglufuncuint32valuetodsname[] = "NGLU-UINT32VALUE>";
const char dg_nglufuncvaluetossname[]       = "NGLU-VALUE$>NEW$";

const char dg_forthpnewsymbolhlistidname[]   = "PCURRENTNEWSYMBOLHLISTID";
const char dg_forthpnewsymbolelementidname[] = "PCURRENTNEWSYMBOLELEMENTID";

const char dg_forthsymbolsstringtoehname[]   = "SYMBOLLIST$>EH";
const char dg_forthnamedbufstringtoename[]   = "NAMED-BUF$>E";
const char dg_forthnamedbufstrtobufidname[]  = "NAMED-BUF$>BUFID";
const char dg_forthnamedbufstrtopname[]      = "NAMED-BUF$>P";
const char dg_forthhsymbolstrtoname[]        = "HSYMBOL$>";

// const char dg_forthlibdashtotoname[]         = "LIB->";

/*
struct Premadeword {
        const char *pname;
        UINT64 namelength;
        UINT64 compileroutinebuf;
        UINT64 compileroutineoffset;
        UINT64 databuf;
        UINT64 dataoffset;
    };
*/

/*
const unsigned char dg_corenames[] = {
'!',               // 0
'#',               // 1
'#','>',           // 2
'#','S',           // 3
'#','T','I','B',   // 4
'`',               // 5
'(',               // 6
'*',               // 7
'*','/',              // 8
'*','/','M','O','D',  // 9
'+',                  // 10
'+','!'               // 11
'+','L','O','O','P',  // 12
',',                  // 13
'-',                  // 14
'.',                  // 15
'.','"',              // 16
'.','(',              // 17
'/',                  // 18
'/','M','O','D',      // 19
'0','<',              // 20
'0','<','>',          // 21
'0','=',              // 22
'0','>',              // 23
'1','+',              // 24
'1','-',              // 25
'2','!',              // 26
'2','*',              // 27
'2','/',              // 28
'2','@',              // 29
'2','C','O','N','S','T','A','N','T', // 30
'2','D','R','O','P',     // 31
'2','D','U','P',      // 32
'2','O','V','E','R',     // 33
'2','S','W','A','P',     // 34
'2','V','A','R','I','A','B','L','E', // 35
':',         // 36
';',         // 37
'<',         // 38
'<','#',        // 39
'!','=',        // 40
'=',         // 41
'>',         // 42
'>','B','O','D','Y',     // 43
'>','I','N',       // 44
'>','N','U','M','B','E','R',   // 45
'>','R',        // 46
'?','D','U','P',      // 47
'@',         // 48
'A','B','O','R','T',     // 49
'A','B','O','R','T','"',    // 50
'A','B','S',       // 51
'A','C','C','E','P','T',    // 52
'A','G','A','I','N',     // 53
'A','L','I','G','N',     // 54
'A','L','I','G','N','E','D',   // 55
'A','L','L','O','T',     // 56
'A','N','D'     // 57
'B','A','S','E',      // 58
'B','E','G','I','N',     // 59
'B','L',        // 60
'C','!',        // 61
'C',',',        // 62
'C','@',        // 63
'C','E','L','L','S','+',    // 64
'C','E','L','L','S',     // 65
'C','H','A','R',      // 66
'C','H','A','R','+',     // 67
'C','H','A','R','S',     // 68
'C','O','N','S','T','A','N','T',  //69
'C','O','U','N','T',     // 70
'C','R',                 // 71
'C','R','E','A','T','E', // 72
'D','=',                 // 73
'D','E','F','I','N','I','T','I','O','N','S', // 74
'D','E','P','T','H',     // 75
'D','O',                 // 76
'D','O','E','S','>',     // 77
'D','R','O','P',         // 78
'D','O',                 // 79
'E','L','S','E',         // 80
'E','M','I','T',         // 81
'E','N','V','I','R','O','N','M','E','N','T','?',
'E','R','A','S','E',
'E','V','A','L','U','A','T','E',
'E','X','E','C','U','T','E',
'E','X','I','T',
'F','A','L','S','E',
'F','I','L','L',
'F','I','N','D',
'F','M','/','M','O','D',
'G','E','T','-','C','U','R','R','E','N','T',
'G','E','T','-','O','R','D','E','R',
'H','E','R','E',
'H','O','L','D',
'I',
'I','F',
'I','M','M','E','D','I','A','T','E',
'I','N','V','E','R','T',
'J',
'K','E','Y',
'L','E','A','V','E',
'L','I','T','E','R','A','L',
'L','O','C','A','L','S','|',
'L','O','O','P',
'L','S','H','I','F','T',
'M','*',
'M','A','X',
'M','I','N',
'M','O','D',
'M','O','V','E',
'N','E','G','A','T','E',
'N','I','P',
'O','R',
'O','V','E','R',
'P','A','D',
'P','O','S','T',
'Q','U','I','T',
'R','<',
'R','@',
'R','E','C','U','R','S','E',
'R','E','P','E','A','T',
'R','O','L','L',
'R','O','T',
'R','S','H','I','F','T',
'S','"',
'S','>','D',
'S','E','A','R','C','H','-','W','O','R','D','L','I','S','T',
'S','E','T','-','C','U','R','R','E','N','T',
'S','E','T','-','O','R','D','E','R',
'S','I','G','N',
'S','M','/','R','E','M',
'S','O','U','R','C','E',
'S','P','A','C','E',
'S','P','A','C','E','S',
'S','T','A','T','E',
'S','W','A','P',
'T','H','E','N',
'T',I','B',
'T','R','U','E',
'T','U','C','K',
'T','Y','P','E',
'U','.',
'U','<',
'U','M','*',
'U','M','/','M','O','D',
'U','N','L','O','O','P',
'U','N','T','I','L',
'V','A','R','I','A','B','L','E',
'W','H','I','L','E',
'W','O','R','D',
'X','O','R',
'[',
'[','\'',']',
'[','C','H','A','R',']',
']'
};
*/


struct Premadeword presortedcorewords[dg_presortedcorewordlistsize + 2];
struct Premadeword presortedenvironmentwords[dg_presortedenvwordlistsize + 2];
// struct Premadeword presortedstringwords[dg_presortedstringwordlistsize + 2];
// struct Premadeword presortederrorwords[dg_presortederrorwordlistsize + 2];
struct Premadeword presortedbufferwords[dg_prestoredbufferwordlistsize + 2];
// struct Premadeword presortedoswords[dg_presortedoswordlistsize + 2];


Premadeword* dg_getppresortedcorewords (Bufferhandle* pBHarrayhead)
{
    UINT64 i = 0;

    presortedcorewords[i].pname                 = dg_forthstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstore;

    i++;

    presortedcorewords[i].pname                 = dg_forthnumbersignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnumbersignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnumbersign;

    i++;

    presortedcorewords[i].pname                 = dg_forthnumbersigngreatername;
    presortedcorewords[i].namelength            = sizeof(dg_forthnumbersigngreatername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnumbersigngreater;

    i++;

    presortedcorewords[i].pname                 = dg_forthnumbersignsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnumbersignsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnumbersigns;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthnumbertibname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnumbertibname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnumbertib;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthscreatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthscreatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthscreate;

    i++;      

    presortedcorewords[i].pname                 = dg_forthtickname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtickname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtick;

    i++;

    presortedcorewords[i].pname                 = dg_forthparenname;
    presortedcorewords[i].namelength            = sizeof(dg_forthparenname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthparen;

    i++;

    presortedcorewords[i].pname                 = dg_forthstarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthstarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstar;

    i++;

    presortedcorewords[i].pname                 = dg_forthstarslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthstarslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstarslash;

    i++;

    presortedcorewords[i].pname                 = dg_forthstarslashmodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthstarslashmodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstarslashmod;

    i++;

    presortedcorewords[i].pname                 = dg_forthplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthplus;

    i++;

    presortedcorewords[i].pname                 = dg_forthplusstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthplusstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthplusstore;

    i++;

    presortedcorewords[i].pname                 = dg_forthplusloopname;
    presortedcorewords[i].namelength            = sizeof(dg_forthplusloopname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthplusloop;

    i++;

    presortedcorewords[i].pname                 = dg_forthcommaname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcommaname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcomma;

    i++;

    presortedcorewords[i].pname                 = dg_forthminusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthminusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthminus;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthminusdenormalname;
    presortedcorewords[i].namelength            = sizeof(dg_forthminusdenormalname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64negativedenormal;

    i++;   
 
    presortedcorewords[i].pname                 = dg_forthminusinfinityname;
    presortedcorewords[i].namelength            = sizeof(dg_forthminusinfinityname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64negativeinfinity;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthminusnanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthminusnanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64negativeNaN;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdashtrailingname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdashtrailingname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)dg_forthdashtrailing;

    i++;

    presortedcorewords[i].pname                 = dg_forthdotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdot;

    i++;

    presortedcorewords[i].pname                 = dg_forthdotquotesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdotquotesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdotquotes;

    i++;

    presortedcorewords[i].pname                 = dg_forthdotparenname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdotparenname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdotparen;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdotrname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdotrname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdotr;

    i++;   

    presortedcorewords[i].pname                 = dg_forthslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthslash;

    i++;

    presortedcorewords[i].pname                 = dg_forthslashmodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthslashmodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthslashmod;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthslashstringname;
    presortedcorewords[i].namelength            = sizeof(dg_forthslashstringname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthslashstring;

    i++;   

    presortedcorewords[i].pname                 = dg_forthzerolessname;
    presortedcorewords[i].namelength            = sizeof(dg_forthzerolessname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthzeroless;

    i++;

    presortedcorewords[i].pname                 = dg_forthzeronotequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthzeronotequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthzeronotequals;

    i++;

    presortedcorewords[i].pname                 = dg_forthzeroequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthzeroequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthzeroequals;

    i++;

    presortedcorewords[i].pname                 = dg_forthzerogreatername;
    presortedcorewords[i].namelength            = sizeof(dg_forthzerogreatername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthzerogreater;

    i++;

    presortedcorewords[i].pname                 = dg_forthoneplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthoneplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthoneplus;

    i++;

    presortedcorewords[i].pname                 = dg_forthoneminusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthoneminusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthoneminus;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwostorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwostorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwostore;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwostarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwostarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwostar;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwoslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwoslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwoslash;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthtwotorname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwotorname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwotor;

    i++;      

    presortedcorewords[i].pname                 = dg_forthtwofetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwofetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwofetch;

    i++;
   
    presortedcorewords[i].pname                 = dg_forthtwoconstantname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwoconstantname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwoconstant;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwodropname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnumbersignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwodrop;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwodupname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwodupname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwodup;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthtwoliteralname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwoliteralname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwoliteral;

    i++;   

    presortedcorewords[i].pname                 = dg_forthtwoovername;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwoovername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwoover;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthtworfromname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtworfromname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtworfrom;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthtworfetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtworfetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtworfetch;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthtworotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtworotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtworot;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwoswapname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwoswapname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwoswap;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwovaluename;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwovaluename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwovalue;

    i++;

    presortedcorewords[i].pname                 = dg_forthtwovariablename;
    presortedcorewords[i].namelength            = sizeof(dg_forthtwovariablename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtwovariable;

    i++;

    presortedcorewords[i].pname                 = dg_forthcolonname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcolonname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcolon;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthcolonnonamename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcolonnonamename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcolonnoname;

    i++;   

    presortedcorewords[i].pname                 = dg_forthsemicolonname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsemicolonname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsemicolon;

    i++;

    presortedcorewords[i].pname                 = dg_forthlessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlessthan;

    i++;

    presortedcorewords[i].pname                 = dg_forthlessthannumbersignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlessthannumbersignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlessthannumbersign;

    i++;

    presortedcorewords[i].pname                 = dg_forthnotequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnotequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnotequals;

    i++;

    presortedcorewords[i].pname                 = dg_forthequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthequals;

    i++;

    presortedcorewords[i].pname                 = dg_forthgreaterthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthgreaterthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthgreaterthan;

    i++;

    presortedcorewords[i].pname                 = dg_forthtobodyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtobodyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtobody;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthtofloatname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtofloatname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtofloat;

    i++;

    presortedcorewords[i].pname                 = dg_forthtoinname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtoinname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtoin;

    i++;

    presortedcorewords[i].pname                 = dg_forthtonumbername;
    presortedcorewords[i].namelength            = sizeof(dg_forthtonumbername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtonumber;

    i++;

    presortedcorewords[i].pname                 = dg_forthtorname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtorname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtor;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthquestionname;
    presortedcorewords[i].namelength            = sizeof(dg_forthquestionname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)dg_forthquestion;

    i++;   
 
    presortedcorewords[i].pname                 = dg_forthqueryclearlocalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthqueryclearlocalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)dg_forthqueryclearlocals;

    i++;

    presortedcorewords[i].pname                 = dg_forthquerydoname;
    presortedcorewords[i].namelength            = sizeof(dg_forthquerydoname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthquerydo;

    i++;

    presortedcorewords[i].pname                 = dg_forthquestiondupname;
    presortedcorewords[i].namelength            = sizeof(dg_forthquestiondupname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthquestiondup;

    i++;

    presortedcorewords[i].pname                 = dg_forthfetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)dg_forthfetch;

    i++;

    presortedcorewords[i].pname                 = dg_forthabortname;
    presortedcorewords[i].namelength            = sizeof(dg_forthabortname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthabort;

    i++;

    presortedcorewords[i].pname                 = dg_forthabortquotesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthabortquotesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthabortquotes;

    i++;

    presortedcorewords[i].pname                 = dg_forthabsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthabsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthabs;

    i++;


    presortedcorewords[i].pname                 = dg_forthacceptname;
    presortedcorewords[i].namelength            = sizeof(dg_forthacceptname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthaccept;

    i++;

    presortedcorewords[i].pname                 = dg_forthagainname;
    presortedcorewords[i].namelength            = sizeof(dg_forthagainname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthagain;

    i++;

    presortedcorewords[i].pname                 = dg_forthalignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthalignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthalign;

    i++;

    presortedcorewords[i].pname                 = dg_forthalignedname;
    presortedcorewords[i].namelength            = sizeof(dg_forthalignedname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthaligned;

    i++;

    presortedcorewords[i].pname                 = dg_forthallotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthallotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthallot;

    i++;

    presortedcorewords[i].pname                 = dg_forthandname;
    presortedcorewords[i].namelength            = sizeof(dg_forthandname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthand;

    i++;

    presortedcorewords[i].pname                 = dg_forthbasename;
    presortedcorewords[i].namelength            = sizeof(dg_forthbasename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthbase;

    i++;

    presortedcorewords[i].pname                 = dg_forthbeginname;
    presortedcorewords[i].namelength            = sizeof(dg_forthbeginname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthbegin;

    i++;

    presortedcorewords[i].pname                 = dg_forthblname;
    presortedcorewords[i].namelength            = sizeof(dg_forthblname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthbl;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthblankname;
    presortedcorewords[i].namelength            = sizeof(dg_forthblankname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthblank;

    i++;

    presortedcorewords[i].pname                 = dg_forthcstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcstore;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthcquotename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcquotename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcquote;

    i++;

    presortedcorewords[i].pname                 = dg_forthccommaname;
    presortedcorewords[i].namelength            = sizeof(dg_forthccommaname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthccomma;

    i++;

    presortedcorewords[i].pname                 = dg_forthcfetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcfetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcfetch;

    i++;


    presortedcorewords[i].pname                 = dg_forthcellplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcellplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcellplus;

    i++;

    presortedcorewords[i].pname                 = dg_forthcellsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcellsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcells;

    i++;

    presortedcorewords[i].pname                 = dg_forthcharname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcharname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthchar;

    i++;

    presortedcorewords[i].pname                 = dg_forthcharplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcharplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcharplus;

    i++;

    presortedcorewords[i].pname                 = dg_forthcharsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcharsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthchars;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthcmovename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcmovename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcmove;

    i++;  
    
    presortedcorewords[i].pname                 = dg_forthcmovetoname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcmovetoname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcmoveto;

    i++;  
    
    presortedcorewords[i].pname                 = dg_forthcodename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcodename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcode;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthcomparename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcomparename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcompare;

    i++;   

    presortedcorewords[i].pname                 = dg_forthconstantname;
    presortedcorewords[i].namelength            = sizeof(dg_forthconstantname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthconstant;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthconstantsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthconstantsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthconstants;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthconstantscurlyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthconstantscurlyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthconstantscurly;

    i++;   

    presortedcorewords[i].pname                 = dg_forthcountname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcountname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcount;

    i++;

    presortedcorewords[i].pname                 = dg_forthcrname;
    presortedcorewords[i].namelength            = sizeof(dg_forthcrname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcr;

    i++;

    presortedcorewords[i].pname                 = dg_forthcreatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthcreatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcreate;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdplus;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthdminusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdminusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdminus;

    i++;    
    
    presortedcorewords[i].pname                 = dg_forthddotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthddotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthddot;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthddotrname;
    presortedcorewords[i].namelength            = sizeof(dg_forthddotrname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthddotr;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthdzerolessname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdzerolessname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdzeroless;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdzeroequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdzeroequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdzeroequals;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdtwostarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdtwostarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdtwostar;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdtwoslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdtwoslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdtwoslash;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdlessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdlessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdlessthan;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdequals;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdtofname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdtofname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdtof;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdtosname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdtosname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdtos;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdabsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdabsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdabs;

    i++;

    presortedcorewords[i].pname                 = dg_forthdecimalname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdecimalname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdecimal;

    i++;

    presortedcorewords[i].pname                 = dg_forthdefinitionsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdefinitionsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdefinitions;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdenormalname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdenormalname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64denormal;

    i++;    

    presortedcorewords[i].pname                 = dg_forthdepthname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdepthname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdepth;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdfstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthdfstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfstore;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdffetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdffetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthffetch;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdfalignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdfalignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthalign;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdfalignedname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdfalignedname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthaligned;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdfloatplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdfloatplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcellplus;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdfloatsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdfloatsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcells;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdmaxname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdmaxname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdmax;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdminname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdminname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdmin;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthdnegatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthdnegatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdnegate;

    i++;

    presortedcorewords[i].pname                 = dg_forthdoname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdoname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdo;

    i++;

    presortedcorewords[i].pname                 = dg_forthdoesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdoesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdoes;

    i++;

    presortedcorewords[i].pname                 = dg_forthdropname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdropname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdrop;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthdulessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdulessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdulessthan;

    i++;   

    presortedcorewords[i].pname                 = dg_forthdupname;
    presortedcorewords[i].namelength            = sizeof(dg_forthdupname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdup;

    i++;

    presortedcorewords[i].pname                 = dg_forthelsename;
    presortedcorewords[i].namelength            = sizeof(dg_forthelsename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthelse;

    i++;

    presortedcorewords[i].pname                 = dg_forthemitname;
    presortedcorewords[i].namelength            = sizeof(dg_forthemitname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthemit;

    i++;

    presortedcorewords[i].pname                 = dg_forthendcodename;
    presortedcorewords[i].namelength            = sizeof(dg_forthendcodename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthendcode;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthenterdgluframecommaname;
    presortedcorewords[i].namelength            = sizeof(dg_forthenterdgluframecommaname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_compileinitlocals;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthenvironmentqueryname;
    presortedcorewords[i].namelength            = sizeof(dg_forthenvironmentqueryname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthenvironmentquery;

    i++;

    presortedcorewords[i].pname                 = dg_fortherasename;
    presortedcorewords[i].namelength            = sizeof(dg_fortherasename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_fortherase;

    i++;

    presortedcorewords[i].pname                 = dg_forthevaluatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthevaluatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthevaluate;

    i++;

    presortedcorewords[i].pname                 = dg_forthexecutename;
    presortedcorewords[i].namelength            = sizeof(dg_forthexecutename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthexecute;

    i++;

    presortedcorewords[i].pname                 = dg_forthexitname;
    presortedcorewords[i].namelength            = sizeof(dg_forthexitname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthexit;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthexitdgluframecommaname;
    presortedcorewords[i].namelength            = sizeof(dg_forthexitdgluframecommaname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_compileexitlocals;

    i++;   
 
    presortedcorewords[i].pname                 = dg_forthfstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfstore;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfstarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfstarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfstar;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfstarstarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfstarstarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfstarstar;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfplus;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfminusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfminusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfminus;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfdotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfdotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfdot;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfslash;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfzerolessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfzerolessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfzerolessthan;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfzeroequalsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfzeroequalsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfzeroequals;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthflessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthflessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthflessthan;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthftodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthftodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthftod;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthftosname;
    presortedcorewords[i].namelength            = sizeof(dg_forthftosname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthftos;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthffetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthffetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthffetch;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfabsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfabsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfabs;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfacosname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfacosname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfacos;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfacoshname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfacoshname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfacosh;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfalignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfalignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthalign;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfalignedname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfalignedname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthaligned;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfalogname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfalogname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfalog;

    i++; 

    presortedcorewords[i].pname                 = dg_forthfalsename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfalsename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)FORTH_FALSE;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthfasinname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfasinname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfasin;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfasinhname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfasinhname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfasinh;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthfatanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfatanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfatan;

    i++;   
 
    presortedcorewords[i].pname                 = dg_forthfatan2name;
    presortedcorewords[i].namelength            = sizeof(dg_forthfatan2name);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfatan2;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfatanhname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfatanhname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfatanh;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthfconstantname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfconstantname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfconstant;

    i++;  
    
    presortedcorewords[i].pname                 = dg_forthfconstantsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfconstantsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfconstants;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfconstantscurlyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfconstantscurlyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfconstantscurly;

    i++;  
    
    presortedcorewords[i].pname                 = dg_forthfcosname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfcosname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfcos;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfcoshname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfcoshname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfcosh;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfdepthname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfdepthname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfdepth;

    i++; 
     
    presortedcorewords[i].pname                 = dg_forthfdropname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfdropname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfdrop;

    i++; 
     
    presortedcorewords[i].pname                 = dg_forthfdupname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfdupname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfdup;

    i++; 
     
    presortedcorewords[i].pname                 = dg_forthfedotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfedotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfedot;

    i++;
     
    presortedcorewords[i].pname                 = dg_forthfexpname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfexpname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfexp;

    i++; 
     
    presortedcorewords[i].pname                 = dg_forthfexpm1name;
    presortedcorewords[i].namelength            = sizeof(dg_forthfexpm1name);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfexpm1;

    i++; 

    presortedcorewords[i].pname                 = dg_forthfillname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfillname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfill;

    i++;

    presortedcorewords[i].pname                 = dg_forthfindname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfindname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfind;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthfliteralname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfliteralname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfliteral;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthflnname;
    presortedcorewords[i].namelength            = sizeof(dg_forthflnname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfln;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthflnp1name;
    presortedcorewords[i].namelength            = sizeof(dg_forthflnp1name);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthflnp1;

    i++; 
       
    presortedcorewords[i].pname                 = dg_forthfloatplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfloatplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcellplus;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthfloatsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfloatsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthcells;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthflogname;
    presortedcorewords[i].namelength            = sizeof(dg_forthflogname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthflog;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthfloorname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfloorname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfloor;

    i++; 

    presortedcorewords[i].pname                 = dg_forthfmslashmodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfmslashmodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfmslashmod;

    i++;

    presortedcorewords[i].pname                 = dg_forthfmaxname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfmaxname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfmax;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthfminname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfminname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfmin;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfnegatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfnegatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfnegate;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfovername;
    presortedcorewords[i].namelength            = sizeof(dg_forthfovername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfover;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfrotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfrotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfrot;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthfroundname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfroundname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfround;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfsdotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfsdotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfsdot;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfsinname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfsinname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfsin;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfsincosname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfsincosname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfsincos;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfsinhname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfsinhname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfsinh;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfsqrtname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfsqrtname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfsqrt;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfswapname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfswapname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfswap;

    i++; 
    
    presortedcorewords[i].pname                 = dg_forthftanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthftanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthftan;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthftanhname;
    presortedcorewords[i].namelength            = sizeof(dg_forthftanhname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthftanh;

    i++;

    presortedcorewords[i].pname                 = dg_forthfvaluename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfvaluename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfvalue;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfvariablename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfvariablename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvariable;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfvariablesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfvariablesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvariables;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfvariablescurlyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthfvariablescurlyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvariablescurly;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthfproximatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthfproximatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthfproximate;

    i++; 

    presortedcorewords[i].pname                 = dg_forthgetcurrentname;
    presortedcorewords[i].namelength            = sizeof(dg_forthgetcurrentname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthgetcurrent;

    i++;

    presortedcorewords[i].pname                 = dg_forthgetordername;
    presortedcorewords[i].namelength            = sizeof(dg_forthgetordername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthgetorder;

    i++;

    presortedcorewords[i].pname                 = dg_forthherename;
    presortedcorewords[i].namelength            = sizeof(dg_forthherename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthhere;

    i++;

    presortedcorewords[i].pname                 = dg_forthholdname;
    presortedcorewords[i].namelength            = sizeof(dg_forthholdname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthhold;

    i++;

    presortedcorewords[i].pname                 = dg_forthiname;
    presortedcorewords[i].namelength            = sizeof(dg_forthiname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthi;

    i++;

    presortedcorewords[i].pname                 = dg_forthifname;
    presortedcorewords[i].namelength            = sizeof(dg_forthifname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthif;

    i++;

    presortedcorewords[i].pname                 = dg_forthimmediatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthimmediatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthimmediate;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthinfinityname;
    presortedcorewords[i].namelength            = sizeof(dg_forthinfinityname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64infinity;

    i++;      

    presortedcorewords[i].pname                 = dg_forthinvertname;
    presortedcorewords[i].namelength            = sizeof(dg_forthinvertname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthinvert;

    i++;

    presortedcorewords[i].pname                 = dg_forthjname;
    presortedcorewords[i].namelength            = sizeof(dg_forthjname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthj;

    i++;

    presortedcorewords[i].pname                 = dg_forthkeyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthkeyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthkey;

    i++;

    presortedcorewords[i].pname                 = dg_forthleavename;
    presortedcorewords[i].namelength            = sizeof(dg_forthleavename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthleave;

    i++;

    presortedcorewords[i].pname                 = dg_forthliteralname;
    presortedcorewords[i].namelength            = sizeof(dg_forthliteralname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthliteral;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthlocalconstantsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlocalconstantsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlocalconstants;

    i++;   
 
    presortedcorewords[i].pname                 = dg_forthlocalconstantscurlyname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlocalconstantscurlyname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlocalconstantscurly;

    i++; 

    presortedcorewords[i].pname                 = dg_forthlocalsbarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlocalsbarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlocalsbar;

    i++;

    presortedcorewords[i].pname                 = dg_forthloopname;
    presortedcorewords[i].namelength            = sizeof(dg_forthloopname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthloop;

    i++;

    presortedcorewords[i].pname                 = dg_forthlshiftname;
    presortedcorewords[i].namelength            = sizeof(dg_forthlshiftname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthlshift;

    i++;

    presortedcorewords[i].pname                 = dg_forthmstarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthmstarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmstar;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthmstarslashname;
    presortedcorewords[i].namelength            = sizeof(dg_forthmstarslashname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmstarslash;

    i++; 
 
    presortedcorewords[i].pname                 = dg_forthmplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthmplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmplus;

    i++;  

    presortedcorewords[i].pname                 = dg_forthmaxname;
    presortedcorewords[i].namelength            = sizeof(dg_forthmaxname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmax;

    i++;

    presortedcorewords[i].pname                 = dg_forthminname;
    presortedcorewords[i].namelength            = sizeof(dg_forthminname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmin;

    i++;

    presortedcorewords[i].pname                 = dg_forthmodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthmodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmod;

    i++;

    presortedcorewords[i].pname                 = dg_forthmovename;
    presortedcorewords[i].namelength            = sizeof(dg_forthmovename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthmove;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthnanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64NaN;

    i++;    

    presortedcorewords[i].pname                 = dg_forthnegatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthnegatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnegate;

    i++;

    presortedcorewords[i].pname                 = dg_forthnipname;
    presortedcorewords[i].namelength            = sizeof(dg_forthnipname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthnip;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthocodename;
    presortedcorewords[i].namelength            = sizeof(dg_forthocodename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthocode;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthodocompiletypecallname;
    presortedcorewords[i].namelength            = sizeof(dg_forthodocompiletypecallname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthdocompiletypecall;

    i++;

    
    presortedcorewords[i].pname                 = dg_forthorname;
    presortedcorewords[i].namelength            = sizeof(dg_forthorname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthor;

    i++;


    presortedcorewords[i].pname                 = dg_forthovername;
    presortedcorewords[i].namelength            = sizeof(dg_forthovername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthover;

    i++;

    presortedcorewords[i].pname                 = dg_forthpadname;
    presortedcorewords[i].namelength            = sizeof(dg_forthpadname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthpad;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthpiname;
    presortedcorewords[i].namelength            = sizeof(dg_forthpiname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64pi;

    i++;  

    presortedcorewords[i].pname                 = dg_forthpostponename;
    presortedcorewords[i].namelength            = sizeof(dg_forthpostponename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthpostpone;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthprecisionname;
    presortedcorewords[i].namelength            = sizeof(dg_forthprecisionname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthprecision;

    i++;

    presortedcorewords[i].pname                 = dg_forthquitname;
    presortedcorewords[i].namelength            = sizeof(dg_forthquitname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthquit;

    i++;

    presortedcorewords[i].pname                 = dg_forthrfromname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrfromname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrfrom;

    i++;

    presortedcorewords[i].pname                 = dg_forthrfetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrfetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrfetch;

    i++;

    presortedcorewords[i].pname                 = dg_forthrecursename;
    presortedcorewords[i].namelength            = sizeof(dg_forthrecursename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrecurse;

    i++;

    presortedcorewords[i].pname                 = dg_forthrepeatname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrepeatname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrepeat;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthrepresentname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrepresentname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrepresent;

    i++;   

    presortedcorewords[i].pname                 = dg_forthrollname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrollname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthroll;

    i++;

    presortedcorewords[i].pname                 = dg_forthrotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrot;


    i++;

    presortedcorewords[i].pname                 = dg_forthrshiftname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrshiftname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrshift;

    i++;

    presortedcorewords[i].pname                 = dg_forthsquotesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsquotesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsquotes;

    i++;


    presortedcorewords[i].pname                 = dg_forthstodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthstodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstod;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthstofname;
    presortedcorewords[i].namelength            = sizeof(dg_forthstofname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstof;

    i++;

    presortedcorewords[i].pname                 = dg_forthsearchwordlistname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsearchwordlistname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsearchwordlist;

    i++;

    presortedcorewords[i].pname                 = dg_forthsetcurrentname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsetcurrentname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsetcurrent;

    i++;

    presortedcorewords[i].pname                 = dg_forthsetordername;
    presortedcorewords[i].namelength            = sizeof(dg_forthsetordername);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsetorder;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthsetprecisionname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsetprecisionname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsetprecision;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsfstorename;
    presortedcorewords[i].namelength            = sizeof(dg_forthsfstorename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsfstore;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsffetchname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsffetchname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsffetch;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsfalignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsfalignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsfalign;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsfalignedname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsfalignedname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsfaligned;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsfloatplusname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsfloatplusname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsfloatplus;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthsfloatsname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsfloatsname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsfloats;

    i++;

    presortedcorewords[i].pname                 = dg_forthsignname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsignname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsign;

    i++;

    presortedcorewords[i].pname                 = dg_forthsmslashremname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsmslashremname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsmslashrem;

    i++;

    presortedcorewords[i].pname                 = dg_forthsourcename;
    presortedcorewords[i].namelength            = sizeof(dg_forthsourcename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsource;

    i++;

    presortedcorewords[i].pname                 = dg_forthspacename;
    presortedcorewords[i].namelength            = sizeof(dg_forthspacename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthspace;

    i++;

    presortedcorewords[i].pname                 = dg_forthspacesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthspacesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthspaces;

    i++;

    presortedcorewords[i].pname                 = dg_forthstatename;
    presortedcorewords[i].namelength            = sizeof(dg_forthstatename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthstate;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthswapname;
    presortedcorewords[i].namelength            = sizeof(dg_forthswapname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthswap;

    i++;
 
    presortedcorewords[i].pname                 = dg_forthsynonymname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsynonymname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsynonym;

    i++;

    presortedcorewords[i].pname                 = dg_forthsbackslashquotesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthsbackslashquotesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthsbackslashquotes;

    i++;
    
    presortedcorewords[i].pname                 = dg_forththenname;
    presortedcorewords[i].namelength            = sizeof(dg_forththenname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forththen;

    i++;

    presortedcorewords[i].pname                 = dg_forthtibname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtibname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtib;

    i++;

    presortedcorewords[i].pname                 = dg_forthtoname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtoname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthto;

    i++;

    presortedcorewords[i].pname                 = dg_forthtruename;
    presortedcorewords[i].namelength            = sizeof(dg_forthtruename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypedpushn;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)FORTH_TRUE;

    i++;

    presortedcorewords[i].pname                 = dg_forthtuckname;
    presortedcorewords[i].namelength            = sizeof(dg_forthtuckname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtuck;

    i++;

    presortedcorewords[i].pname                 = dg_forthtypename;
    presortedcorewords[i].namelength            = sizeof(dg_forthtypename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthtype;

    i++;

    presortedcorewords[i].pname                 = dg_forthudotname;
    presortedcorewords[i].namelength            = sizeof(dg_forthudotname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthudot;

    i++;

    presortedcorewords[i].pname                 = dg_forthulessthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthulessthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthulessthan;

    i++;

    presortedcorewords[i].pname                 = dg_forthugreaterthanname;
    presortedcorewords[i].namelength            = sizeof(dg_forthugreaterthanname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthugreaterthan;

    i++;

    presortedcorewords[i].pname                 = dg_forthumstarname;
    presortedcorewords[i].namelength            = sizeof(dg_forthumstarname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthumstar;

    i++;

    presortedcorewords[i].pname                 = dg_forthumslashmodname;
    presortedcorewords[i].namelength            = sizeof(dg_forthumslashmodname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthumslashmod;

    i++;

    presortedcorewords[i].pname                 = dg_forthunloopname;
    presortedcorewords[i].namelength            = sizeof(dg_forthunloopname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthunloop;

    i++;

    presortedcorewords[i].pname                 = dg_forthuntilname;
    presortedcorewords[i].namelength            = sizeof(dg_forthuntilname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthuntil;

    i++;

    presortedcorewords[i].pname                 = dg_forthvaluename;
    presortedcorewords[i].namelength            = sizeof(dg_forthvaluename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvalue;

    i++;

    presortedcorewords[i].pname                 = dg_forthvariablename;
    presortedcorewords[i].namelength            = sizeof(dg_forthvariablename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvariable;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthvariablesname;
    presortedcorewords[i].namelength            = sizeof(dg_forthvariablesname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthvariables;

    i++;

    presortedcorewords[i].pname                 = dg_forthwhilename;
    presortedcorewords[i].namelength            = sizeof(dg_forthwhilename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthwhile;

    i++;

    presortedcorewords[i].pname                 = dg_forthwordname;
    presortedcorewords[i].namelength            = sizeof(dg_forthwordname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthword;

    i++;

    presortedcorewords[i].pname                 = dg_forthwordlistname;
    presortedcorewords[i].namelength            = sizeof(dg_forthwordlistname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthwordlist;

    i++;

    presortedcorewords[i].pname                 = dg_forthxorname;
    presortedcorewords[i].namelength            = sizeof(dg_forthxorname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthxor;

    i++;

    presortedcorewords[i].pname                 = dg_forthleftbracketname;
    presortedcorewords[i].namelength            = sizeof(dg_forthleftbracketname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthleftbracket;

    i++;

    presortedcorewords[i].pname                 = dg_forthbrackettickname;
    presortedcorewords[i].namelength            = sizeof(dg_forthbrackettickname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthbrackettick;

    i++;

    presortedcorewords[i].pname                 = dg_forthbracketcharname;
    presortedcorewords[i].namelength            = sizeof(dg_forthbracketcharname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthbracketchar;

    i++;

    presortedcorewords[i].pname                 = dg_forthrightbracketname;
    presortedcorewords[i].namelength            = sizeof(dg_forthrightbracketname);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_forthrightbracket;

    i++;
    
    presortedcorewords[i].pname                 = (const char*)"dg_umstar";
    presortedcorewords[i].namelength            = 9;
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedcorewords[i].databuf               = DG_CORE_BUFFERID;
    presortedcorewords[i].dataoffset            = (UINT64)&dg_umstar;

    i++;
    
    presortedcorewords[i].pname                 = dg_forthlittleename;
    presortedcorewords[i].namelength            = sizeof(dg_forthlittleename);
    presortedcorewords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedcorewords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedcorewords[i].databuf               = 0;
    presortedcorewords[i].dataoffset            = (UINT64)dg_f64e;

    i++; 
    
    if (i != dg_presortedcorewordlistsize)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize core premade wordlist, number of elements didn't match, expected ");
        dg_writestdoutuinttodec(pBHarrayhead, dg_presortedcorewordlistsize);
        dg_printzerostring(pBHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuinttodec(pBHarrayhead, i);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

        // if i was > then you buffer could have overflowed, this
          // leads to all sorts of strange behavior like changing environ on freebsd
          // and breaking environment variables
        return ((Premadeword*)badbufferhandle);
    }

    return (&(presortedcorewords[0]));
}


Premadeword* dg_getppresortedenvironmentwords ()
{
        UINT64 i = 0;

    presortedenvironmentwords[i].pname                 = dg_forthslashcountedstringname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthslashcountedstringname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)maxwordlength;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthslashholdname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthslashholdname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)dg_maxholdbufferlength;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthslashpadname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthslashpadname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)dg_maxpadbufferlength;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthaddressunitbitsname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthaddressunitbitsname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = dg_addressunitbits;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthcorename;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthcorename);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_TRUE;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthcoreextname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthcoreextname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_FALSE;

    i++;
    
    presortedenvironmentwords[i].pname                 = dg_forthfloatingname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthfloatingname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_TRUE;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthfloatingextname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthfloatingextname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_TRUE;

    i++;
    
    presortedenvironmentwords[i].pname                 = dg_forthfloatingstackname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthfloatingstackname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = maxf64stackbufferlength / sizeof(FLOAT64);

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthflooredname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthflooredname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_FALSE;

    i++;
      
    presortedenvironmentwords[i].pname                 = dg_forthmaxcharname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxcharname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)255;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthmaxdname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxdname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedenvironmentwords[i].databuf               = (UINT64)largestsigneddinthi;
    presortedenvironmentwords[i].dataoffset            = (UINT64)largestsigneddintlo;

    i++;
    
    presortedenvironmentwords[i].pname                 = dg_forthmaxfloatname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxfloatname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushf;
    presortedenvironmentwords[i].databuf               = (UINT64)0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)dg_f64maxfloat;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthmaxnname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxnname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)largestsignedint;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthmaxuname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxuname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)largestunsignedint;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthmaxudname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthmaxudname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedenvironmentwords[i].databuf               = (UINT64)largestunsigneddinthi;
    presortedenvironmentwords[i].dataoffset            = (UINT64)largestunsigneddintlo;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthreturnstackcellsname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthreturnstackcellsname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = maxrstackbufferlength / sizeof(UINT64);

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthsearchordername;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthsearchordername);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_TRUE;

    i++;
      
    presortedenvironmentwords[i].pname                 = dg_forthsearchorderextname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthsearchorderextname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = (UINT64)FORTH_FALSE;

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthstackcellsname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthstackcellsname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = maxdatastackbufferlength / sizeof(UINT64);

    i++;

    presortedenvironmentwords[i].pname                 = dg_forthwordlistsname;
    presortedenvironmentwords[i].namelength            = sizeof(dg_forthwordlistsname);
    presortedenvironmentwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedenvironmentwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedenvironmentwords[i].databuf               = 0;
    presortedenvironmentwords[i].dataoffset            = maxsearchorderbufferlength / sizeof(UINT64);

    i++;
      
    if (i != dg_presortedenvwordlistsize)
    {
        // if i was > then buffer was overflowed, this leads to all sort of
          // strange behavior, like changing environ on freebsd and messing
          // up environment variables
        return ((Premadeword*)badbufferhandle);
    }
    
    return ((Premadeword*)&(presortedenvironmentwords[0]));
}

/*
Premadeword* dg_getppresortedstringwords ()
{
    UINT64 i = 0;

    if (i != dg_presortedstringwordlistsize)
    {
        // if was i > then buffer was overflowed, this leads to all sort of
          // strange behavior, like changing environ on freebsd and messing
          // up environment variables
        return ((Premadeword*)badbufferhandle);
    }    

    return ((Premadeword*)&(presortedstringwords[0]));
}
*/

Premadeword* dg_getppresortedbufferwords (Bufferhandle* pBHarrayhead)
{
    UINT64 i = 0;

    presortedbufferwords[i].pname                 = dg_forthlinecommentname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlinecommentname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinecomment;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnumbersignstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnumbersignstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnumbersignstring;

    i++;
      
    presortedbufferwords[i].pname                 = dg_forthnumbersigngreaterthanstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnumbersigngreaterthanstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtwodrop;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnumbersignsstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnumbersignsstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnumbersignsstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushs;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = 0;

    i++;
    
    presortedbufferwords[i].pname                 = dg_stringhlistidname;
    presortedbufferwords[i].namelength            = sizeof(dg_stringhlistidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_VARIABLESTRINGS_HLISTID;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringtoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthstringto;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringtostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcatstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthturnstringinto0stringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthturnstringinto0stringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthturnstringinto0string;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringtobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringtobuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringtocname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtocname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringtoc;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstrtocodelinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstrtocodelinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstrtocodelinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstrtodatalinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstrtodatalinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstrtodatalinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringtonewobwordname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtonewobwordname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringtonewobword;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringtonewprocwordname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtonewprocwordname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringtonewprocword;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringtobackslashstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringtobackslashstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringtobackslashstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringcstorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringcstorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringcstore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringcfetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringcfetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstringcfetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstringstackoffsetbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringstackoffsetbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_STRINGOFFSETSTACK_BUFFERID;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstringstackstringbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstringstackstringbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_STRINGSTRINGSTACK_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthminuscscanstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthminuscscanstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthminuscscanstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthminusrollstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthminusrollstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthminusrollstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthminusrolllstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthminusrolllstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthminusrolllstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthminusrotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthminusrotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthminusrot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthprintstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthprintstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthprintstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdotstringsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdotstringsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdotstrings;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdotelname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdotelname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdoterrorline;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdoterrorlinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdoterrorlinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdoterrorline;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthdoterrorsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdoterrorsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdoterrors;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdoterrorsshortname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdoterrorsshortname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdoterrors;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdotwordnamename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdotwordnamename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdotwordname;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdotsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdotsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdots;

    i++;

    presortedbufferwords[i].pname                 = dg_forthslashslashname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthslashslashname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinecomment;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlessthannumbersignstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlessthannumbersignstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthequalstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthequalstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcomparestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtostring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtostarulestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtostarulestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtostarulestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtoslashulestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoslashulestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtoslashulestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtoslashulelstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoslashulelstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtoslashulelstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthtobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtocurrentname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtocurrentname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtocurrent;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthtoerrorshortname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoerrorshortname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpushoerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtoehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtoeh;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthtoerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthpushoerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtofactorialulestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtofactorialulestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtofactorialulestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthtoheadname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoheadname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtohead;

    i++;

    presortedbufferwords[i].pname                 = dg_forthtonewstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtonewstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtonewstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthtoordername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtoordername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtoorder;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtouleb128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtouleb128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtouleb128;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthqueryendevaluatename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthqueryendevaluatename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthqueryendevaluate;

    i++;

    presortedbufferwords[i].pname                 = dg_forthqueryerrorifname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthqueryerrorifname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthqueryerrorif;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthqueryincludefilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthqueryincludefilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthqueryincludefilestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_accessdeniederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_accessdeniederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_accessdeniederror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthallocatedbytesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthallocatedbytesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthallocatedbytes;

    i++;

    presortedbufferwords[i].pname                 = dg_alreadyfreeerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_alreadyfreeerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_alreadyfreeerror;

    i++;

    presortedbufferwords[i].pname                 = dg_arraymisalignederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_arraymisalignederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_arraymisalignederror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthasciitounicodestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthasciitounicodestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthasciitounicodestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_badmemoryerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_badmemoryerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_badmemoryerror;

    i++;

    presortedbufferwords[i].pname                 = dg_basetoohigherrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_basetoohigherrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_basetoohigherror;

    i++;

    presortedbufferwords[i].pname                 = dg_basetoolowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_basetoolowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_basetoolowerror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthbenchmarkname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbenchmarkname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbenchmark;

    i++;
    
    presortedbufferwords[i].pname                 = dg_bharraybadmemerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_bharraybadmemerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bharraybadmemerror;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarrayfullname;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarrayfullname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarrayfull;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarraygrowby0errorname;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarraygrowby0errorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarraygrowby0error;

    i++;

    presortedbufferwords[i].pname                 = dg_bharrayheadbadmemerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_bharrayheadbadmemerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bharrayheadbadmemerror;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarraymaxsizeltgrowbyname;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarraymaxsizeltgrowbyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarraymaxsizeltgrowby;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarraymaxsizeltbhsizename;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarraymaxsizeltbhsizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarraymaxsizeltbhsize;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarraynubcorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarraynubcorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarraynubcorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_BHarraynubgtsizename;
    presortedbufferwords[i].namelength            = sizeof(dg_BHarraynubgtsizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_BHarraynubgtsize;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthbswapname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbswapname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbswap;

    i++;

    presortedbufferwords[i].pname                 = dg_forthbuftostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftostring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbufto;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftodotofilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftodotofilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftodotofilestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthbuftodotobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftodotobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftodotobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftoneweximdotobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftoneweximdotobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftomachodotobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftomachodotobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftomachodotobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftomachodotobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftosname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftosname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftos;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbuftocname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbuftocname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbuftoc;

    i++;
    
    presortedbufferwords[i].pname                 = dg_bufferhlistidname;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferhlistidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_NAMEDBUFFERS_HLISTID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_bufferfullerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferfullerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferfullerror;

    i++;

    presortedbufferwords[i].pname                 = dg_buffergrowbycorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_buffergrowbycorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_buffergrowbycorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_bufferidisforerrorstackname;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferidisforerrorstackname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferidisforerrorstack;

    i++;

    presortedbufferwords[i].pname                 = dg_bufferidisfreename;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferidisfreename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferidisfree;

    i++;

    presortedbufferwords[i].pname                 = dg_bufferidisnotfreename;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferidisnotfreename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferidisnotfree;

    i++;

    presortedbufferwords[i].pname                 = dg_buffernubcorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_buffernubcorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_buffernubcorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_buffermaxsizeltsizename;
    presortedbufferwords[i].namelength            = sizeof(dg_buffermaxsizeltsizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_buffermaxsizeltsize;

    i++;

    presortedbufferwords[i].pname                 = dg_bufferidnotinbharrayname;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferidnotinbharrayname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferidnotinbharray;

    i++;

    presortedbufferwords[i].pname                 = dg_buffersizecorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_buffersizecorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_buffersizecorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_bufferunderflowname;
    presortedbufferwords[i].namelength            = sizeof(dg_bufferunderflowname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_bufferunderflow;

    i++;

    presortedbufferwords[i].pname                 = dg_forthbyename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbyename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbye;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthctostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthctostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthctostring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthctobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthctobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthctobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthctonewstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthctonewstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthctonewstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallcppmembername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallcppmembername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddress;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallcppmemberretuint128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallcppmemberretuint128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddressretuint128;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallcdeclname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallcdeclname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddress;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallcdeclretuint128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallcdeclretuint128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddressretuint128;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcalldfpprocname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcalldfpprocname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcalldfpprocaddress;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallprocaddressname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallprocaddressname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddress;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallprocaddressretuint128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallprocaddressretuint128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddressretuint128;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallstdcallname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallstdcallname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddress;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcallstdcallretuint128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcallstdcallretuint128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcallprocaddressretuint128;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcatstringndname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcatstringndname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcatstringnd;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcatstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcatstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthcatstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcatlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcatlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcatlstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodeallotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodeallotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodeallot;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodescommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodescommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodescomma;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodeu16commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodeu16commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodeu16comma;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodeu32commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodeu32commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodeu32comma;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodeu64commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodeu64commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodeu64comma;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcodeu8commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcodeu8commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcodeu8comma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcomparestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcomparestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcomparestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilebranchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilebranchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine; // is this correct?
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilebranch;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilecallbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilecallbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilecallbuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilecallcorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilecallcorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilecallcore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilecallsamebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilecallsamebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilecallsamebuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcompileentercolonname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileentercolonname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_compileinitlocals;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthcompileentername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileentername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_compileinitlocals;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcompileentersubname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileentersubname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_compileentersubroutineframe;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompileexitname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileexitname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_compileexitlocals;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompiles;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcompilesafecallbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompilesafecallbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilesafecallbuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcompileu8sname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileu8sname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompileu8s;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcompileu8scurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcompileu8scurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompileu8scurly;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcopylstringntoreplacelstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcopylstringntoreplacelstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcopylstringntoreplacelstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcopylstringntosname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcopylstringntosname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcopystoreplacelstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcopystoreplacelstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcopystoreplacelstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcopysfromlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcopysfromlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcopysfromlstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcopystolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcopystolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcopystolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcountbitsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcountbitsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcountbits;

    i++;
        
    presortedbufferwords[i].pname                 = dg_crcerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_crcerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_crcerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcreatecolonlinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreatecolonlinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreatecolonlinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcreatecdecllinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreatecdecllinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreatecdecllinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcreatecodelinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreatecodelinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreatecodelinkcomma;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthcreateocodelinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreateocodelinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreateocodelinkcomma;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcreatebracketlibdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreatebracketlibdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreatebracketlibdot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcreatebracketwordlistdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreatebracketwordlistdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreatebracketwordlistdot;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthcreateocname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreateocname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreateoc;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcreateovname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcreateovname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcreateov;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcrlfname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcrlfname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcrlf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcscanname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcscanname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcscan;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcscanstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcscanstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcscanstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcscanbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcscanbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcscanbuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcscanlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcscanlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcscanlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcscanlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcscanlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcscanlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcurrentfromname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcurrentfromname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcurrentfrom;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthdarshiftname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdarshiftname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdarshift;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdataspacebufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdataspacebufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_DATASPACE_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdatastackbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdatastackbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_DATASTACK_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_datastackmisalignederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_datastackmisalignederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_datastackmisalignederror;

    i++;

    presortedbufferwords[i].pname                 = dg_datastacknoraddrmissingerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_datastacknoraddrmissingerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_datastacknoraddrmissingerror;

    i++;

    presortedbufferwords[i].pname                 = dg_datastackunderflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_datastackunderflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_datastackunderflowerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdeletestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeletestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeletestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeleteinstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeleteinstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeleteinstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeleteinstringndname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeleteinstringndname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeleteinstringnd;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdeleteinbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeleteinbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeleteinbuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeleteinlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeleteinlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeleteinlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeleteinlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeleteinlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeleteinlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeletelstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeletelstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeletelstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdeletelstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdeletelstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdeletelstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdepthstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdepthstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdepthstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthcheckerrordepthname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcheckerrordepthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcheckerrordepth;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdepthlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdepthlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdepthlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_devicebrokenerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_devicebrokenerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_devicebrokenerror;

    i++;

    presortedbufferwords[i].pname                 = dg_devicenotfounderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_devicenotfounderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_devicenotfounderror;

    i++;

    presortedbufferwords[i].pname                 = dg_devicenotreadyerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_devicenotreadyerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_devicenotreadyerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdglibstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdglibstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdglibstring;

    i++;
/*    
    presortedbufferwords[i].pname                 = dg_forthdiaperoffname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdiaperoffname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdiaperoff;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdiaperonname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdiaperonname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdiaperon;

    i++;
*/    
    presortedbufferwords[i].pname                 = dg_diskisfullerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_diskisfullerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_diskisfullerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdlshiftname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdlshiftname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdlshift;

    i++;

    presortedbufferwords[i].pname                 = dg_drivenotfounderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_drivenotfounderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_drivenotfounderror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdropstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdropstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdropstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdropehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdropehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdropeh;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdroplstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdroplstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdroplstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlstringtosname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlstringtosname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlstringtos;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdroptoerrorcountname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdroptoerrorcountname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdroptoerrorcount;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdrshiftname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdrshiftname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdrshift;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthdumpname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdumpname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdumphex;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdupstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdupstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdupstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdupehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdupehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdupeh;

    i++;
        
    presortedbufferwords[i].pname                 = dg_fortherrorquotesshortname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortherrorquotesshortname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_fortherrorquotes;

    i++;

    presortedbufferwords[i].pname                 = dg_fortherrorfromshortname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortherrorfromshortname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpopoerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthetoehtopname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthetoehtopname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthetoehtop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_clearerrorsshortname; // EES
    presortedbufferwords[i].namelength            = sizeof(dg_clearerrorsshortname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_clearerrorsanderrorline;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehtop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnamestrtovaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnamestrtovaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnamestrtovalue;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnamestrtovaluestrname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnamestrtovaluestrname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnamestrtovaluestr;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnamewtovaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnamewtovaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnamewtovalue;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnamewtovaluestrname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnamewtovaluestrname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnamewtovaluestr;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnewelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnewelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnewelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehnewelementtoehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehnewelementtoehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnewelementtoeh;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehoherewtonewelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehoherewtonewelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehoherewtonewelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehdot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehfromname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehfromname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehfrom;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehbracket1ddotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehbracket1ddotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehbracket1ddot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehndname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehndname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehnd;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehbracketnddotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehbracketnddotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehbracketnddot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthehtopname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthehtopname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehtop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthhlisttoxmlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhlisttoxmlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthhlisttoxmlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_clearerrorsname; // EMPTY-ERRORS
    presortedbufferwords[i].namelength            = sizeof(dg_clearerrorsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_clearerrorsanderrorline;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthemptywordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthemptywordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthemptywordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthemptybuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthemptybuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthemptybuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_emptystringerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_emptystringerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_emptystringerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthendoflistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthendoflistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_ENDOFWORDLIST;

    i++;

    presortedbufferwords[i].pname                 = dg_forthendofwordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthendofwordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_ENDOFWORDLIST;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthenumcurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_fortherrorquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortherrorquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_fortherrorquotes;

    i++;

    presortedbufferwords[i].pname                 = dg_fortherrorfromname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortherrorfromname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpopoerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_errorsoffsetpastendname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsoffsetpastendname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsoffsetpastend;

    i++;

    presortedbufferwords[i].pname                 = dg_incrementingerrorcountname;
    presortedbufferwords[i].namelength            = sizeof(dg_incrementingerrorcountname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_incrementingerrorcount;

    i++;

    presortedbufferwords[i].pname                 = dg_errorsbufidis0name;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsbufidis0name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsbufidis0;

    i++;

    presortedbufferwords[i].pname                 = dg_errorsbufidisfreename;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsbufidisfreename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsbufidisfree;

    i++;

    presortedbufferwords[i].pname                 = dg_errorsbufidnubcorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsbufidnubcorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsbufidnubcorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_errorsbufidnotinbharrayname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsbufidnotinbharrayname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsbufidnotinbharray;

    i++;

    presortedbufferwords[i].pname                 = dg_errorsbufidsizecorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorsbufidsizecorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorsbufidsizecorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_errorbufnubcorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorbufnubcorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorbufnubcorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_errorbufgrowbynesizenemaxsizename;
    presortedbufferwords[i].namelength            = sizeof(dg_errorbufgrowbynesizenemaxsizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorbufgrowbynesizenemaxsize;

    i++;
    
    presortedbufferwords[i].pname                 = dg_fortherrorstackbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortherrorstackbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_ERRORSTACK_BUFFERID;

    i++;

    presortedbufferwords[i].pname                 = dg_errorbufisfreename;
    presortedbufferwords[i].namelength            = sizeof(dg_errorbufisfreename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorbufisfree;

    i++;

    presortedbufferwords[i].pname                 = dg_errorbufnotinbharrayname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorbufnotinbharrayname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorbufnotinbharray;

    i++;

    presortedbufferwords[i].pname                 = dg_erroroverflowname;
    presortedbufferwords[i].namelength            = sizeof(dg_erroroverflowname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_erroroverflow;

    i++;
    
    presortedbufferwords[i].pname                 = dg_errorunderflowname;
    presortedbufferwords[i].namelength            = sizeof(dg_errorunderflowname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorunderflow;

    i++;

    presortedbufferwords[i].pname                 = dg_forthevaluatebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthevaluatebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthevaluatebuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthf64commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthf64commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthf64comma;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthf64stackbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthf64stackbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_F64STACK_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthreadavailabletobuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthreadavailabletobuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthreadavailabletobuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_fileinuseerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_fileinuseerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_fileinuseerror;

    i++;

    presortedbufferwords[i].pname                 = dg_fileislockederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_fileislockederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_fileislockederror;

    i++;

    presortedbufferwords[i].pname                 = dg_filenotfounderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_filenotfounderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_filenotfounderror;

    i++;

    presortedbufferwords[i].pname                 = dg_filesystemcorrupterrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_filesystemcorrupterrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_filesystemcorrupterror;

    i++;

    presortedbufferwords[i].pname                 = dg_filesystemunknownerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_filesystemunknownerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_filesystemunknownerror;

    i++;

    presortedbufferwords[i].pname                 = dg_filetoobigerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_filetoobigerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_filetoobigerror;

    i++;

    presortedbufferwords[i].pname                 = dg_filetypeunknownerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_filetypeunknownerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_filetypeunknownerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfillnewstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfillnewstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfillnewstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfindclosesthlistchildname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfindclosesthlistchildname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfindclosesthlistchild;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfindhlistchildname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfindhlistchildname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfindhlistchild;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistsortedchildnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistsortedchildnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistsortedchildn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfinddefinitioninsearchordername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfinddefinitioninsearchordername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfinddefinitioninsearchorder;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfinddefinitioninwordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfinddefinitioninwordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfinddefinitioninwordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfindlibrarysymbolname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfindlibrarysymbolname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfindlibrarysymbol;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfixpathstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfixpathstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfixpathstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfreehlistelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreehlistelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreehlistelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthfreeflatosymbolbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreeflatosymbolbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreeflatosymbolbuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfreehlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreehlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreehlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfreebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreebuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthfreefreeablelstringarrayname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreefreeablelstringarrayname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreefreeablelstringarray;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthfreelibraryname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthfreelibraryname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfreelibrary;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgethlistelementnomname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistelementnomname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistelementnom;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistnewersiblingname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistnewersiblingname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistnewersibling;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistnewestchildname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistnewestchildname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistnewestchild;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethowmanyhlistkidsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethowmanyhlistkidsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethowmanyhlistkids;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistoldersiblingname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistoldersiblingname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistoldersibling;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistparentname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistparentname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistparent;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethlistelementvaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethlistelementvaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethlistelementvalue;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthgetargsfromnstringsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetargsfromnstringsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetargsfromnstrings;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbufferbytename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbufferbytename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthocfetch;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbuffercurrentoffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbuffercurrentoffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetbuffercurrentoffset;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbuffergrowbyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbuffergrowbyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetbuffergrowby;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbufferhandlename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbufferhandlename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsbufferhandle;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbufferlengthname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbufferlengthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlengthbuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbuffermaxsizename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbuffermaxsizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetbuffermaxsize;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbuffersizename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbuffersizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetbuffersize;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetbufferuint64name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetbufferuint64name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthofetch;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthgetenvstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetenvstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetenvstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgeterrorcountname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgeterrorcountname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgeterrorcount;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetfilelengthname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetfilelengthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetfilelength;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethstderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethstderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethstderror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethstdinname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethstdinname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethstdin;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgethstdoutname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgethstdoutname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgethstdout;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetmethodstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetmethodstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetmethodstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetmidstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetmidstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetmidstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetnewestdefinitioninwordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetnewestdefinitioninwordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetnewestdefinitioninwordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetnextdefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetnextdefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetnextdefinition;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetoarrayelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetoarrayelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetoarrayelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetcompileroutinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetcompileroutinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetcompileroutine;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetodfname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetodfname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetodf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetoerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetoerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetoerror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcplgetolderrorcountname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcplgetolderrorcountname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompilegetolderrorcount;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetpstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsstringnd;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetparrayelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetparrayelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetparrayelement;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbuffer;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbuffercurrentoffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbuffercurrentoffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbuffercurrentoffset;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbufferhandlearrayheadname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbufferhandlearrayheadname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsbufferhandlearrayhead;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbufferlengthname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbufferlengthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbufferlength;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbufferoffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbufferoffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbufferoffset;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbufferpbufferlengthname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbufferpbufferlengthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbuffer;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetpbuffersegmentname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpbuffersegmentname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
        presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
        presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbuffersegment;

        i++;

    presortedbufferwords[i].pname                 = dg_forthgetplstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetplstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetslstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetpnewbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetpnewbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpnewbuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetquerystringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetquerystringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetquerystring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetsstringndname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetsstringndname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsstringnd;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetsbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetsbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsbuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetsbufferhandlename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetsbufferhandlename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsbufferhandle;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetsbufferhandlearrayheadname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetsbufferhandlearrayheadname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetsbufferhandlearrayhead;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetslstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetslstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetslstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgetstartoffsetlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetstartoffsetlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstartoffsetlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgetswordheadname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgetswordheadname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetswordhead;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgluname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgluname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthglu;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthglufilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthglufilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthglufilestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthgrowstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgrowstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgrowstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgrowbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgrowbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgrowbuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_buffergrowby0errorname;
    presortedbufferwords[i].namelength            = sizeof(dg_buffergrowby0errorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_buffergrowby0error;

    i++;

    presortedbufferwords[i].pname                 = dg_forthgrowlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthgrowlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgrowlstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthhctwostorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhctwostorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthhctwostore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthhexname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhexname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthhex;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthhfindstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhfindstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfindhlistchild;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthhibitname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhibitname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthhibit;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthholdstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthholdstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthholdstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthholdbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthholdbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_HOLD_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthhsymbolstrtoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthhsymbolstrtoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthhsymbolstrto;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthimportlinkdatasizename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthimportlinkdatasizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_IMPORT_LINK_DATA_SIZE;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthincludefilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthincludefilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthincludefilestring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_indexnotinarrayerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_indexnotinarrayerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_indexnotinarrayerror;

    i++;

    presortedbufferwords[i].pname                 = dg_initerrorsbuf0inusename;
    presortedbufferwords[i].namelength            = sizeof(dg_initerrorsbuf0inusename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_initerrorsbuf0inuse;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthinsertinstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertinstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertinstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertinstringndname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertinstringndname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertinstringnd;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertinbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertinbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertinbuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertinlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertinlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertinlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertinlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertinlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertinlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinsertlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertlstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthinsertsintobuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinsertsintobuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinsertsintobuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinusebuffersname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinusebuffersname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinusebuffers;

    i++;

    presortedbufferwords[i].pname                 = dg_forthinusebytesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthinusebytesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthinusebytes;

    i++;
        
    presortedbufferwords[i].pname                 = dg_invalidparametererrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_invalidparametererrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_invalidparametererror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthiscolonname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthiscolonname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthiscolon;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthiscallprocname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthiscallprocname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthiscallproc;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthiscallprocretuint64name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthiscallprocretuint64name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthiscallprocretuint64;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthiscompilecallname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthiscompilecallname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthiscompilecall;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthisotoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthisotoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthisoto;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthisobtoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthisobtoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthisobto;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthisptoname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthisptoname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthispto;

    i++;
    
    presortedbufferwords[i].pname                 = dg_lstringstackdepthcorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringstackdepthcorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringstackdepthcorrupt;

    i++;

    presortedbufferwords[i].pname                 = dg_lstringsoffsetscorruptname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringsoffsetscorruptname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringsoffsetscorrupt;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlstringsfetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlstringsfetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_lstringtopoffsetwasbadname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringtopoffsetwasbadname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringtopoffsetwasbad;

    i++;

    presortedbufferwords[i].pname                 = dg_lstringidtoohigherrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringidtoohigherrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringidtoohigherror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlatestname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlatestname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlatest;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlelshiftstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlelshiftstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlelshiftstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlelshiftcstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlelshiftcstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlelshiftcstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlelshiftclstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlelshiftclstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlelshiftclstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlelshiftlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlelshiftlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlelshiftlstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlengthstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlengthstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlengthstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlengthbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlengthbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlengthbuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlengthlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlengthlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlengthlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlengthlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlengthlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlengthlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlershiftcstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlershiftcstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlershiftcstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlershiftclstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlershiftclstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlershiftclstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlibdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlibdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlibdot;

    i++;
    
    presortedbufferwords[i].pname                 = dg_libraryhlistidname;
    presortedbufferwords[i].namelength            = sizeof(dg_libraryhlistidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_NAMEDSHAREDLIBS_HLISTID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlinesparsename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlinesparsename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinesparse;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlinesparsenamesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlinesparsenamesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinesparsenames;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlinkdefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlinkdefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinkdefinition;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlinkwordname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlinkwordname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinkdefinition;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthloadfilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthloadfilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthloadfilestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlobitname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlobitname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlobit;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthlocalenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlocalenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)& dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlocalenumcurly;

    i++;

    presortedbufferwords[i].pname                 = dg_forthlocalslstringbarname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthlocalslstringbarname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlocalslstringbar;

    i++;
    
    presortedbufferwords[i].pname                 = dg_lstringoffsetpastenderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringoffsetpastenderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringoffsetpastenderror;

    i++;

    presortedbufferwords[i].pname                 = dg_lstringsegmentgoespastenderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringsegmentgoespastenderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringsegmentgoespastenderror;

    i++;

    presortedbufferwords[i].pname                 = dg_lstringstackunderflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_lstringstackunderflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_lstringstackunderflowerror;

    i++;
        
    presortedbufferwords[i].pname                 = dg_maxsizeltgrowbyerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_maxsizeltgrowbyerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_maxsizeltgrowbyerror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthmaxusedbuffersname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthmaxusedbuffersname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthmaxusedbuffers;

    i++;
    
    presortedbufferwords[i].pname                 = dg_maxwordlengthexceedederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_maxwordlengthexceedederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_maxwordlengthexceedederror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthmicrosecondssince1970jan01name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthmicrosecondssince1970jan01name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthmicrosecondssince1970jan01;

    i++;

    presortedbufferwords[i].pname                 = dg_forthn16tocellname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthn16tocellname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthn16tocell;

    i++;

    presortedbufferwords[i].pname                 = dg_forthn32tocellname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthn32tocellname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthn32tocell;

    i++;

    presortedbufferwords[i].pname                 = dg_forthn8tocellname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthn8tocellname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthn8tocell;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamestrtovaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamestrtovaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamestrtovalue;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamestrtovaluestrname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamestrtovaluestrname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamestrtovaluestr;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthnametoename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnametoename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnametoe;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnametoerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnametoerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnametoe;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamedbufstrtobufidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamedbufstrtobufidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamedbufstrtobufid;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamedbufstringtoename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamedbufstringtoename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamedbufstringtoe;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamedbufstrtopname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamedbufstrtopname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamedbufstrtop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamewtovaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamewtovaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamewtovalue;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnamewtovaluestrname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnamewtovaluestrname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnamewtovaluestr;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthnewstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)& dg_forthnewstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthnewhlistelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewhlistelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewhlistelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnewflatosymbolbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewflatosymbolbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewflatosymbolbuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewhlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewhlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewhlist;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnewnglulistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewnglulistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewnglulist;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnewcurrentnglulistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewcurrentnglulistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewcurrentnglulist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewbuffer;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthnewconstantdefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewconstantdefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewconstantdefinition;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewdefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewdefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewdefinition;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewfreeablelstringarrayname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewfreeablelstringarrayname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewfreeablelstringarray;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewsubroutinedefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewsubroutinedefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewsubroutinedefinition;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewvariabledefinitionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewvariabledefinitionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewvariabledefinition;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnewwordname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnewwordname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnewdefinition;

    i++;
    
    presortedbufferwords[i].pname                 = dg_newwordoldererrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_newwordoldererrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_newwordoldererror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthngluname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthngluname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnglu;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncbufsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncbufsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCBUFS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccallbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccallbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLBUF;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccallbuftodsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccallbuftodsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLBUFTODS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccalloffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccalloffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLDESTOFFSET;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccalloffsetodsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccalloffsetodsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLDESTOFFSETTODS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccalllibname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccalllibname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLLIB;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunccalllibtodsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunccalllibtodsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCCALLLIBTODS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncdestbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncdestbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCDESTBUF;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncdestsymbolsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncdestsymbolsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCDESTSYMBOLS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncfilesname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncfilesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCFILES;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunchfilesname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunchfilesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCHFILES;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunchlistherename;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunchlistherename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCHLISTHERE;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunclibsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunclibsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCLIBS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunclinkbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunclinkbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCLINKBUF;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunclinklibname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunclinklibname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCLINKLIB;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunclinknewbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunclinknewbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCLINKNEWBUF;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufunclinkoffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufunclinkoffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCLINKOFFSET;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncngluname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncngluname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
        presortedbufferwords[i].databuf               = 0;
        presortedbufferwords[i].dataoffset            = DG_GLUFUNCNGLU;

        i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncsrcbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncsrcbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
        presortedbufferwords[i].databuf               = 0;
        presortedbufferwords[i].dataoffset            = DG_GLUFUNCSRCBUF;

        i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncsrclibname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncsrclibname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
        presortedbufferwords[i].databuf               = 0;
        presortedbufferwords[i].dataoffset            = DG_GLUFUNCSRCLIB;

        i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncsrcsymbolsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncsrcsymbolsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
        presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
        presortedbufferwords[i].databuf               = 0;
        presortedbufferwords[i].dataoffset            = DG_GLUFUNCSRCSYMBOLS;

        i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncsymbolsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncsymbolsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCSYMBOLS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncuint32valuetodsname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncuint32valuetodsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCUINT64VALUETODS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nglufuncvaluetossname;
    presortedbufferwords[i].namelength            = sizeof(dg_nglufuncvaluetossname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = DG_GLUFUNCVALUETOSTRS;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnglufilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnglufilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnglufilestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnipstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnipstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnipstring;

    i++;

    presortedbufferwords[i].pname                 = dg_noerrorsname;
    presortedbufferwords[i].namelength            = sizeof(dg_noerrorsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_noerrors;

    i++;

    presortedbufferwords[i].pname                 = dg_noerroryetname;
    presortedbufferwords[i].namelength            = sizeof(dg_noerroryetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_noerroryet;

    i++;

    presortedbufferwords[i].pname                 = dg_forthnopname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnopname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_nop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnotstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnotstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthnotstring;

    i++;

    presortedbufferwords[i].pname                 = dg_notbharrayheaderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_notbharrayheaderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_notbharrayheaderror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthnotlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthnotlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_forthnotlstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_errornotthatmanyerrorsname;
    presortedbufferwords[i].namelength            = sizeof(dg_errornotthatmanyerrorsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errornotthatmanyerrors;

    i++;

    presortedbufferwords[i].pname                 = dg_wasnottrulyfreeerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wasnottrulyfreeerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wasnottrulyfreeerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_nullpbharrayerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_nullpbharrayerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_nullpbharrayerror;

    i++;

    presortedbufferwords[i].pname                 = dg_nullpbharrayheaderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_nullpbharrayheaderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_nullpbharrayheaderror;

    i++;

    presortedbufferwords[i].pname                 = dg_nullpointererrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_nullpointererrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_nullpointererror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthostorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthostorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthostore;

    i++;
    
    presortedbufferwords[i].pname                 = dg_fortho0quotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_fortho0quotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_fortho0quotes;

    i++;

    presortedbufferwords[i].pname                 = dg_forthotwostorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthotwostorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthotwostore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthotopname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthotopname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthgetpbufferoffset;

    i++;

    presortedbufferwords[i].pname                 = dg_forthofetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthofetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthofetch;

    i++;

    presortedbufferwords[i].pname                 = dg_forthocstorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthocstorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthocstore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthocfetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthocfetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthocfetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthocallname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthocallname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthocall;
        
    i++;
    
    presortedbufferwords[i].pname                 = dg_forthodoctalwaysexecutename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoctalwaysexecutename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypealwaysexecute;

    i++;

    // presortedbufferwords[i].pname                 = dg_forthodoctcppmembername;
    // presortedbufferwords[i].namelength            = sizeof(dg_forthodoctcppmembername);
    // presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    // presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    // presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    // presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypecppmemberfunction;

    // i++;

    presortedbufferwords[i].pname                 = dg_forthodocpltypedfpcdeclname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocpltypedfpcdeclname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypedfpcdecl;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodocompiletypecdeclname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypecdeclname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypecdecl;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodoctcdeclretuint128name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoctcdeclretuint128name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypecdeclretuint128;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodoctsubroutinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoctsubroutinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypesubroutine;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodocompiletypedpushsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypedpushsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypedpushs;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodocompiletypedpushpname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypedpushpname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypedpushp;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodoctdpushdnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoctdpushdnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypedpushdn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodocompiletypedpushnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypedpushnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypedpushn;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthodocompiletyperunfileandwaitnoenvquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletyperunfileandwaitnoenvquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletyperunfileandwaitnoenvquotes;

    i++;

    presortedbufferwords[i].pname                 = dg_forthodoctsafesubroutinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoctsafesubroutinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypesafesubroutine;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthodocompiletypewordsstringquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypewordsstringquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypewordsstringquotes;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthodocompiletypewords0stringquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodocompiletypewords0stringquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypewords0stringquotes;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthdocompiletypebrackettoordername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdocompiletypebrackettoordername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypebrackettoorder;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdocompiletypebracketlibdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdocompiletypebracketlibdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypebracketlibdot;

    i++;

    presortedbufferwords[i].pname                 = dg_forthdocompiletypebracketwordlistdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthdocompiletypebracketwordlistdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletypebracketwordlistdot;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthodoesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthodoesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthodoes;

    i++;
    
    presortedbufferwords[i].pname                 = dg_offsetpastenderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_offsetpastenderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_offsetpastenderror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthoherename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthoherename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthohere;

    i++;

    presortedbufferwords[i].pname                 = dg_forthopenlibstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthopenlibstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthopenlibstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthopenlibrarystringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthopenlibrarystringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthopenlibrarystring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthosstorename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosstorename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosstore;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthosquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosquotes;

    i++;

    presortedbufferwords[i].pname                 = dg_forthostonewstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthostonewstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthostonewstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthosfetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosfetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosfetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_osdidlessthanavailableerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_osdidlessthanavailableerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_osdidlessthanavailableerror;

    i++;

    presortedbufferwords[i].pname                 = dg_oserrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_oserrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_oserror;

    i++;

    presortedbufferwords[i].pname                 = dg_osexceptionname;
    presortedbufferwords[i].namelength            = sizeof(dg_osexceptionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_osexception;

    i++;

    presortedbufferwords[i].pname                 = dg_invalidhandleerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_invalidhandleerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_invalidhandleerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthosymbolname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosymbolname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthehoherewtonewelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthosymbolcodeimportscommacurlyname; 
    presortedbufferwords[i].namelength            = sizeof(dg_forthosymbolcodeimportscommacurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesafesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosymbolcodeimportscommacurly;

    i++;

    presortedbufferwords[i].pname                 = dg_forthosymbolentryname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosymbolentryname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosymbolentry;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthosymbolimportname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthosymbolimportname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthosymbolimport;

    i++;
    
    presortedbufferwords[i].pname                 = dg_outofmemoryerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_outofmemoryerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_outofmemoryerror;

    i++;

    presortedbufferwords[i].pname                 = dg_outsideofbuffererrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_outsideofbuffererrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_outsideofbuffererror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthoverstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthoverstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthoverstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpzerostrtonewstrname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpzerostrtonewstrname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpzerostrtonewstr;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpackhlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpackhlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpackhlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpackdfname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpackdfname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpackdf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpacklstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpacklstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpacklstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpadbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpadbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_PAD_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpagesizename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpagesizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpagesize;

    i++;

    presortedbufferwords[i].pname                 = dg_forthparsename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparse;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthparsebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparsebuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthparselinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparselinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparseline;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthparsenamenom;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsenamenom);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparseword;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthparsenamesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsenamesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparsewords;

    i++;

    presortedbufferwords[i].pname                 = dg_forthparsewordname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsewordname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparseword;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthparsewordsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthparsewordsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthparsewords;

    i++;
    
    presortedbufferwords[i].pname                 = dg_pathnotfounderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_pathnotfounderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_pathnotfounderror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpbyeflagname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpbyeflagname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)exitmainflag;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpcoloncallssafeflagname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpcoloncallssafeflagname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)coloncallssafeflag;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpcurrentcompilebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpcurrentcompilebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)currentcompilebuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpcurrentcreatewordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpcurrentcreatewordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)currentcompilewordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpcurrentinputbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpcurrentinputbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)currentinterpretbuffer;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpcurrentnewvariablebuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpcurrentnewvariablebuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)currentvariablebuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpickname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpickname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpick;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpickstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpickstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpickstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpicklstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpicklstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpicklstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthpjumpbuffervariablename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpjumpbuffervariablename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)jumpbuffervariable;

    i++;

    presortedbufferwords[i].pname                 = dg_forthpnopromptsflagname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpnopromptsflagname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)promptsoffflag;

    i++;
    
    presortedbufferwords[i].pname                 = dg_pnumberoffloatparamsname;
    presortedbufferwords[i].namelength            = sizeof(dg_pnumberoffloatparamsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_numberofcfparameters;

    i++;
    
    presortedbufferwords[i].pname                 = dg_pnumberofintparamsname;
    presortedbufferwords[i].namelength            = sizeof(dg_pnumberofintparamsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_numberofcparameters;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthpopoerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpopoerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthpopoerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_patchdestnamedbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_patchdestnamedbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_patchdestnamedbuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_patchdestnamedsymbollistname;
    presortedbufferwords[i].namelength            = sizeof(dg_patchdestnamedsymbollistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_patchdestnamedsymbollist;

    i++;
    
    presortedbufferwords[i].pname                 = dg_patchsrcnamedbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_patchsrcnamedbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_patchsrcnamedbuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_patchsrcnamedlibname;
    presortedbufferwords[i].namelength            = sizeof(dg_patchsrcnamedlibname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_patchsrcnamedlib;

    i++;
    
    presortedbufferwords[i].pname                 = dg_patchsrcnamedsymbollistname;
    presortedbufferwords[i].namelength            = sizeof(dg_patchsrcnamedsymbollistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_patchsrcnamedsymbollist;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpprecisionname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpprecisionname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_precision;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpquitwasinitflagname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpquitwasinitflagname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)quitwasinitializedflag;

    i++;
    
    presortedbufferwords[i].pname                 = dg_prsdepthname;
    presortedbufferwords[i].namelength            = sizeof(dg_prsdepthname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_noframereturnstackdepth;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthprunehlistelementname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthprunehlistelementname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthprunehlistelement;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpshowerrorsonexitflagname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpshowerrorsonexitflagname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)showerrorsonexitflag;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthpushoerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthpushoerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64) dg_forthpushoerror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthputbufferbytename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthputbufferbytename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthocstore;

    i++;

    presortedbufferwords[i].pname                 = dg_forthputbuffercurrentoffsetname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthputbuffercurrentoffsetname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthputbuffercurrentoffset;

    i++;

    presortedbufferwords[i].pname                 = dg_forthputbufferuint64name;
    presortedbufferwords[i].namelength            = sizeof(dg_forthputbufferuint64name);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthostore;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthputmidstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthputmidstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthputmidstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthputnewestdefinitioncompiletypename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthputnewestdefinitioncompiletypename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthputnewestdefinitioncompiletype;

    i++;
    
    presortedbufferwords[i].pname                 = dg_x86asmaddresssizename;
    presortedbufferwords[i].namelength            = sizeof(dg_x86asmaddresssizename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushp;
    presortedbufferwords[i].databuf               = DG_DATASPACE_BUFFERID;
    presortedbufferwords[i].dataoffset            = dg_x86asmaddresssize;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrandomname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrandomname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrandom;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthreplaceinbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthreplaceinbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthreplaceinbuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthresolvecompiledbranchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthresolvecompiledbranchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthresolvecompiledbranch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthreversestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthreversestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthreversestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrollstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrollstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrollstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthrolllstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrolllstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrolllstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrotstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrotstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrotstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthroundupname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthroundupname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthroundup;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrstackbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrstackbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_RSTACK_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_rstackunderflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_rstackunderflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_rstackunderflowerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrunfileandwaitname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrunfileandwaitname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrunfileandwait;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthrunfileandwaitnoenvquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrunfileandwaitnoenvquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletyperunfileandwaitnoenvquotes;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdocompiletyperunfileandwaitnoenvquotes;

    i++;

    presortedbufferwords[i].pname                 = dg_forthrunfileandwaitnoenvstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthrunfileandwaitnoenvstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthrunfileandwaitnoenvstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstobufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstobufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstobuf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthstostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstostring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstolstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstolstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstolstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthsafename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsafename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsafe;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsavefilestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsavefilestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsavefilestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthscanname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthscanname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthscan;

    i++;

    presortedbufferwords[i].pname                 = dg_forthscanbufname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthscanbufname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthscanbuf;

    i++;

    presortedbufferwords[i].pname                 = dg_forthscanlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthscanlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthscanlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthscanlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthscanlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthscanlstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthsearchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsearchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsearch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsearchorderdropname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsearchorderdropname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsearchorderdrop;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthorderfromname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthorderfromname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthorderfrom;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsearchorderstackbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsearchorderstackbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_SEARCHORDERSTACK_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_segmentgoespastenderrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_segmentgoespastenderrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_segmentgoespastenderror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthchangehlistparentname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthchangehlistparentname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthchangehlistparent;

    i++;

    presortedbufferwords[i].pname                 = dg_forthsethlistelementvaluename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsethlistelementvaluename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsethlistelementvalue;

    i++;

    presortedbufferwords[i].pname                 = dg_forthsetlengthstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsetlengthstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsetlengthstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthsetlengthlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsetlengthlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsetlengthlstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsetcompileroutinename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsetcompileroutinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsetcompileroutine;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsetodfname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsetodfname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsetodfname;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthshortenstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshortenstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshortenstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthshortenlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshortenlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshortenlstring;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthshowallwordsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshowallwordsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshowallwords;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthshowerrorsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshowerrorsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthdoterrors;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthshowsortedwordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshowsortedwordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshowsortedwordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthshowwordlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshowwordlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshowwordlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthshrinkbuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthshrinkbuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthshrinkbuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsignstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsignstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsignstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsizedconstantscurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsizedconstantscurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsizedconstantscurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthslershiftstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthslershiftstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthslershiftstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthslershiftlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthslershiftlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthslershiftlstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsliteralname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsliteralname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcompiles;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsplitstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsplitstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsplitstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstartoffsetlstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstartoffsetlstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstartoffsetlstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_stringstackunderflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_stringstackunderflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_stringstackunderflowerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_stringunderflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_stringunderflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_stringunderflowerror;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstripstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstripstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstripstring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthstrippathfromfilenamestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthstrippathfromfilenamestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstrippathfromfilenamestring;

    i++;

    presortedbufferwords[i].pname                 = dg_errorinsubroutinename;
    presortedbufferwords[i].namelength            = sizeof(dg_errorinsubroutinename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_errorinsubroutine;

    i++;

    presortedbufferwords[i].pname                 = dg_successname;
    presortedbufferwords[i].namelength            = sizeof(dg_successname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_success;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthswapstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthswapstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthswapstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsymbolname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsymbolname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsymbol;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsymbolenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsymbolenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsymbolenumcurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthsymbolsstringtoehname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthsymbolsstringtoehname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsymbolsstringtoeh;

    i++;
    
    presortedbufferwords[i].pname                 = dg_symbollistshlistidname;
    presortedbufferwords[i].namelength            = sizeof(dg_symbollistshlistidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_NAMEDSYMBOLLISTS_HLISTID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthterminalinputbufferidname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthterminalinputbufferidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_TERMINALINPUT_BUFFERID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtestfindnumbername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtestfindnumbername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtestfindnumber;

    i++;
    
    presortedbufferwords[i].pname                 = dg_toobigfordesterrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_toobigfordesterrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_toobigfordesterror;

    i++;

    presortedbufferwords[i].pname                 = dg_toomanyopenfileserrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_toomanyopenfileserrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_toomanyopenfileserror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtype0stringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtype0stringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtype0string;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtypedenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtypedenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtypedenumcurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthtypedlocalenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthtypedlocalenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtypedlocalenumcurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu128storename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu128storename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtwostore;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu128fetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu128fetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthtwofetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu16storename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu16storename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu16store;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu16fetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu16fetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu16fetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu32storename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu32storename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu32store;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu32commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu32commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu32comma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu32fetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu32fetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu32fetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu64storename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu64storename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthstore;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu64starlstringnplustolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu64starlstringnplustolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu64starlstringnplustolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu64commaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu64commaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu64fetchname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu64fetchname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthfetch;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthu8reverselstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthu8reverselstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthu8reverselstringn;

    i++;

    presortedbufferwords[i].pname                 = dg_forthubufalignname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthubufalignname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthubufalign;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthudmslashmodname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthudmslashmodname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthudmslashmod;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulestringtonumberstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulestringtonumberstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulestringtonumberstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleadclstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleadclstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleadclstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleaddlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleaddlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleaddlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleandstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleandstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleandstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleandlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleandlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleandlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleextendlstringntolname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleextendlstringntolname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleextendlstringntol;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulenandstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulenandstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulenandstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulenandlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulenandlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulenandlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulenorstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulenorstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulenorstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulenorlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulenorlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulenorlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleorstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleorstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleorstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthuleorlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthuleorlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthuleorlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulershiftstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulershiftstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulershiftstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulershiftlstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulershiftlstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulershiftlstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulesbblstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulesbblstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulesbblstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulexnorstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulexnorstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulexnorstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulexnorlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulexnorlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulexnorlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulexorstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulexorstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulexorstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthulexorlstringntolstringnname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthulexorlstringntolstringnname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthulexorlstringntolstringn;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthumulleutostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthumulleutostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthumulleutostring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_underflowerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_underflowerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_underflowerror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthunicodetoasciistringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthunicodetoasciistringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthunicodetoasciistring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthunpackhlistname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthunpackhlistname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthunpackhlist;

    i++;

    presortedbufferwords[i].pname                 = dg_forthunpackdfname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthunpackdfname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthunpackdf;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthunpacklstringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthunpacklstringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthunpacklstring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthurldecodestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthurldecodestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthurldecodestring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthurlencodestringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthurlencodestringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthurlencodestring;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthvariablescurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthvariablescurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthvariablescurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthwtocodelinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwtocodelinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwtocodelinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthwtodatalinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwtodatalinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwtodatalinkcomma;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthwtolinkcommaname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwtolinkcommaname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwtolinkcomma;

    i++;
        
    presortedbufferwords[i].pname                 = dg_forthreadwaitforntobuffername;
    presortedbufferwords[i].namelength            = sizeof(dg_forthreadwaitforntobuffername);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthreadwaitforntobuffer;

    i++;
    
    presortedbufferwords[i].pname                 = dg_wordalreadylinkederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordalreadylinkederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wordalreadylinkederror;

    i++;

    presortedbufferwords[i].pname                 = dg_wordidtoobigerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordidtoobigerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wordidtoobigerror;

    i++;

    presortedbufferwords[i].pname                 = dg_wordlength0errorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordlength0errorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wordlength0error;

    i++;
    
    presortedbufferwords[i].pname                 = dg_wordlisthlistidname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordlisthlistidname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushn;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = (UINT64)DG_WORDLISTS_HLISTID;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthwordlistdotname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwordlistdotname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwordlistdot;

    i++;

    presortedbufferwords[i].pname                 = dg_wordlistidtoobigerrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordlistidtoobigerrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wordlistidtoobigerror;

    i++;

    presortedbufferwords[i].pname                 = dg_wordnotfoundinsearchordererrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_wordnotfoundinsearchordererrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_wordnotfoundinsearchordererror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthwordsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwordsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwords;

    i++;
    
    presortedbufferwords[i].pname                     = dg_forthwordsstringquotesname;
    presortedbufferwords[i].namelength                = sizeof(dg_forthwordsstringquotesname);
    presortedbufferwords[i].compileroutinebuf         = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset      = (UINT64)&dg_forthdocompiletypewordsstringquotes;
    presortedbufferwords[i].databuf                   = 0;  // this is ignored
    presortedbufferwords[i].dataoffset                = 0;  // this is ignored

    i++;
            
    presortedbufferwords[i].pname                 = dg_forthwords0stringquotesname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthwords0stringquotesname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypewords0stringquotes;
    presortedbufferwords[i].databuf               = 0;
    presortedbufferwords[i].dataoffset            = 0;

    i++;

    presortedbufferwords[i].pname                 = dg_writeprotectederrorname;
    presortedbufferwords[i].namelength            = sizeof(dg_writeprotectederrorname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypedpushdn;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)dg_writeprotectederror;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbrackettoorderconstantname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbrackettoorderconstantname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbrackettoorderconstant;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbracketlatestname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbracketlatestname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbracketlatest;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbracketlocalconstantsname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbracketlocalconstantsname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlocalconstants;

    i++;   
 
    presortedbufferwords[i].pname                 = dg_forthbracketlocalconstantscurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbracketlocalconstantscurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlocalconstantscurly;

    i++;
    
    presortedbufferwords[i].pname                 = dg_forthbracketlocalenumcurlyname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbracketlocalenumcurlyname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbracketlocalenumcurly;

    i++; 
    
    presortedbufferwords[i].pname                 = dg_forthbracketsearchorderdropname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbracketsearchorderdropname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthsearchorderdrop;

    i++;
    
    // presortedbufferwords[i].pname                 = dg_forthbracketwordlistdotname;
    // presortedbufferwords[i].namelength            = sizeof(dg_forthbracketwordlistdotname);
    // presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    // presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    // presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    // presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthwordlistdot;

    // i++;

    presortedbufferwords[i].pname                 = dg_forthbackslashname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbackslashname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthlinecomment;

    i++;

    presortedbufferwords[i].pname                 = dg_forthbackslashstringtostringname;
    presortedbufferwords[i].namelength            = sizeof(dg_forthbackslashstringtostringname);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthbackslashstringtostring;

    i++;

    presortedbufferwords[i].pname                 = dg_forthcurlybracename;
    presortedbufferwords[i].namelength            = sizeof(dg_forthcurlybracename);
    presortedbufferwords[i].compileroutinebuf     = DG_CORE_BUFFERID;
    presortedbufferwords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypealwaysexecute;
    presortedbufferwords[i].databuf               = DG_CORE_BUFFERID;
    presortedbufferwords[i].dataoffset            = (UINT64)&dg_forthcurlybrace;

    i++;
    
    if (i != dg_prestoredbufferwordlistsize)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize buffer premade wordlist, number of elements didn't match, expected ");
        dg_writestdoutuinttodec(pBHarrayhead, dg_prestoredbufferwordlistsize);
        dg_printzerostring(pBHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuinttodec(pBHarrayhead, i);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
        
        // if i was > then buffer was overflowed, this leads to all sort of
          // strange behavior, like changing environ on freebsd and messing
          // up environment variables
        return ((Premadeword*)badbufferhandle);
    }  

    return ((Premadeword*)&(presortedbufferwords[0]));
}


// Premadeword* dg_getppresortedoswords ()
// {
//      UINT64 i = 0;

// presortedoswords[i].pname                 = dg_forthtoregsname;
// presortedoswords[i].namelength            = sizeof(dg_forthtoregsname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypepreserveregs;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthtoregs;

// i++;

//  presortedoswords[i].pname                 = dg_forthcallcppmemberfunctionname;
//  presortedoswords[i].namelength            = sizeof(dg_forthcallcppmemberfunctionname);
//  presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
//  presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
//  presortedoswords[i].databuf               = DG_CORE_BUFFERID;
//  presortedoswords[i].dataoffset            = (UINT64)&dg_forthcallcppmemberfunction;

//  i++;

// presortedoswords[i].pname                 = dg_forthloadlibrarystringname;
// presortedoswords[i].namelength            = sizeof(dg_forthloadlibrarystringname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthloadlibrarystring;

// i++;

// presortedoswords[i].pname                 = dg_forthregsfromname;
// presortedoswords[i].namelength            = sizeof(dg_forthregsfromname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypepreserveregs;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthregsfrom;

// i++;


// presortedoswords[i].pname                 = dg_forthshowcapturedregsname;
// presortedoswords[i].namelength            = sizeof(dg_forthshowcapturedregsname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthshowcapturedregs;

// i++;

    

// presortedoswords[i].pname                 = dg_showframename;
// presortedoswords[i].namelength            = sizeof(dg_showframename);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_showframe;

// i++;


// presortedoswords[i].pname                 = dg_forthshowlibrarystringname;
// presortedoswords[i].namelength            = sizeof(dg_forthshowlibrarystringname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthshowlibrarystring;

// i++;

// presortedoswords[i].pname                 = dg_forthshowopenlibraryname;
// presortedoswords[i].namelength            = sizeof(dg_forthshowopenlibraryname);
// presortedoswords[i].compileroutinebuf     = DG_CORE_BUFFERID;
// presortedoswords[i].compileroutineoffset  = (UINT64)&dg_forthdocompiletypesubroutine;
// presortedoswords[i].databuf               = DG_CORE_BUFFERID;
// presortedoswords[i].dataoffset            = (UINT64)&dg_forthshowopenlibrary;

// i++;

    
//    if (i != dg_presortedoswordlistsize)
//    {
        // if i was > then buffer was overflowed, this leads to all sort of
          // strange behavior, like changing environ on freebsd and messing
          // up environment variables
//        return ((Premadeword*)badbufferhandle);
//    }  

//    return ((Premadeword*)&(presortedoswords[0]));
// }

/*
Premadeword* dg_getppresortederrorwords ()
{
    UINT64 i = 0;


    if (i != dg_presortederrorwordlistsize)
    {
        // if i was > then buffer was overflowed, this leads to all sort of
          // strange behavior, like changing environ on freebsd and messing
          // up environment variables
        return ((Premadeword*)badbufferhandle);
    }

    return ((Premadeword*)&(presortederrorwords[0]));
}
*/
