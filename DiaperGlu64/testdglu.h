// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2025 James Patrick Norris
//
//    This file is part of DiaperGlu v5.14.
//
//    DiaperGlu v5.14 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.14 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.14; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 20, 2025          //
// version 5.14               //
// /////////////////////////////

#if !defined(_INC_testdglu)
#define _INC_testdglu

#ifdef  __cplusplus
extern "C" {
#endif

// /////////////////
//  Windows stuff //
// /////////////////
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

void dg_forthselftest ();

// c system access routines
void testdg_malloc ();
void testdg_realloc ();
void testdg_putbyte ();
void testdg_getbyte ();
void testdg_putuint32 ();
void testdg_getuint32 ();

// c processor support routines
void testdg_scanforbyte ();
void testdg_scanforuint32 ();
void testdg_movebytes ();
void testdg_comparebytes ();
void testdg_search ();
void testdg_movebytesskipdestination();
	
// compiling and processor dependent routines
void testdg_compilemovbracketrplussrplusd32tor();
void testdg_compileotor();
void testdg_bumpdisplacementsizeifneeded();
void testdg_compilemovregtoreg();
void testdg_compilecompareir64ir64();
void testdg_compilecompareiretu64();
void testdg_compilecomparenreg();
void testdg_compilecomparenbracketrbpplusn();
void testdg_compilemovfregtofreg();
void testdg_compilenegatereg();
void testdg_compileaddregtoreg();
void testdg_compilesubn8fromrsp();
void testdg_compilesubnfromrsp();
void testdg_compileaddn8torsp();
void testdg_compileaddntorsp();
void testdg_compileaddntorsp();
void testdg_compilepushntoret();
void testdg_compilepopregfromret();
void testdg_compilepushregtoret();
void testdg_compilecalloffset();
void testdg_compilejmpoffset();
void testdg_compilecalladdress();
void testdg_callbuffer();
// void testdg_callbufferinstatecompile();
void testdg_callprocaddress();
void testdg_callprocaddressretuint128();
void testdg_calldfpprocaddress();
void testcompiledemptysubroutine();
void testcompiledstackalign();
void testcompileinitlocalreturnpBHarrayhead();
void testcompileinitlocalreturnframepBHarrayhead();
void testcompilecallforthroutineincore();
void testcompilecallforthroutineincoreatvariousaligments();
void testcompilecallsubroutineswithvariousnumberofparameters();
void testcompilecalloffsetinsamebuffer();
void testdg_compiledgframecallbuffer();
void testdg_compilepushtodatastack();
void testdg_compilepushntodatastack();

void testdg_initjumpbuffer();
void testdg_compilesafecallcore();
void testdg_compilesafecallsamebuffer();
void testdg_compilesafecallbuffer();
void testdg_forthcompilesafecallbuffer();
void testdg_compilesafecallforth();
void testdg_forthcompilegetolderrorcount();
void testdg_packmodrslashm();
void testdg_packsib ();
void testdg_compilerfromr ();
void testdg_compilerfrommatrplusscaletimesrplusn ();
void testdg_compilerfrommatrplusn ();
void testdg_forthsquotes();
void testdg_forthosquotes();
void testdg_fortho0quotes();
void testdg_packtwobytevex();
void testdg_packthreebytevex();
void testdg_compilevex();
void testdg_compileaddnlocalstocallsubsframe();
void testdg_compileobtoptodatastack();
void testdg_compilemovbracketrsptoreg();
void testdg_compilemovbracketrbpd8toreg();
void testdg_compilemovbracketrbpd8tofreg();
void testdg_compilemovbracketrspd8toreg();
void testdg_compilemovbracketrbpd32toreg();
void testdg_compilemovbracketrbpd32tofreg();
void testdg_compilemovbracketrspd32toreg();
void testdg_compilemovbracketrbpdtoreg();
void testdg_compilemovbracketrspdtoreg();
void testdg_compilemovregtobracketrbpd8();
void testdg_compilemovfregtobracketrbpd8();
void testdg_compilemovfregtobracketrbpd32();
void testdg_compilemovregtobracketrsp();
void testdg_compilemovregtobracketrspd8();
void testdg_compilemovregtobracketrbpd32();
void testdg_compilemovregtobracketrspd32();
void testdg_compilemovregtobracketrbpd();
void testdg_compilemovregtobracketrspd();

void testdg_compilepreservelocalsregstoret();
void testdg_compilepreservenoframeregs();
void testdg_compilepreservecallsubsregs();

void testdg_compileunpreservelocalsregsfromret();
void testdg_compileunpreservelocalsregsfromframe();
void testdg_compileunpreservenoframeregs();
void testdg_compileunpreservecallsubsframeregs();

void testdg_compilebracketrbpdtodatastack();
void testdg_compiledatastacktobracketrbpd();
void testdg_compilecallcoreoneuparam();
void testdg_compilecallcoretwouparams();
// void testdg_compilebracketobtoptodatastack();
void testdg_compileopreg64tobracketrsp();

void testdg_getcallsubsframepreservedregoffset();


// c buffer routines
void testdg_newbuffer ();
void testdg_freebuffer ();
void testdg_growbuffer ();
void testdg_shrinkbuffer ();

// c error routines
void testdg_initerrors ();
void testdg_pusherror ();
void testanyerrors ();
void testdg_poperror ();
void testdg_geterror ();
void testdg_geterrorcount ();
void testdg_checkerrorsonstack ();
void testdg_clearerrors ();
void testdg_replaceerrors ();

// c buffer routines
void testdg_getpbuffersegment();
void testdg_getpbuffer();

void testdg_insertinbuffer();
void testdg_deleteinbuffer();

void testdg_getbuffersegment();
void testdg_putbuffersegment();
void testdg_pushbuffersegment();
void testdg_popbuffersegment();
void testdg_pickbuffersegment();

void testdg_getbufferbyte();
void testdg_putbufferbyte();
void testdg_popbufferbyte();
void testdg_pushbufferbyte();

void testdg_getbufferuint32();
void testdg_putbufferuint32();
void testdg_pushbufferuint32();
void testdg_popbufferuint32();

void testdg_getbufferuint64();
void testdg_putbufferuint64();
void testdg_pushbufferuint64();
void testdg_popbufferuint64();

void testdg_getbufferlength();

void testdg_push0stringtobuffersegment();
void testdg_getpbufferhandle();

void testdg_checkbuffer();

void testdg_freebufferset();
void testdg_newbufferset();

void testdg_getuint64arrayelement();
void testdg_putuint64arrayelement();

void testdg_getuint64stackelement();
void testdg_putuint64stackelement();

void testdg_stonewbuffer();
void testdg_getpnewbuffer();
void testdg_pushhctwotobuffer();

void testdg_parseword();
void testdg_parse();
void testdg_parsemultiline();
void testdg_parsewords();
void testdg_noparseentirecurrentline();
void testdg_parseline();
void testdg_noparselineatoffset();
void testdg_replacebuffersegment();
void testdg_tocurrent();
void testdg_currentfrom();
void testdg_createbrackettoorderconstantdef();

void testdg_pushbracketobtodatastack();
void testdg_pushu128bracketobtodatastack();
void testdg_pushbracketobtof64stack();
void testdg_popdatastacktobracketob();
void testdg_popf64stacktobracketob();
void testdg_popdatastacktou128bracketob();
void testdg_ubufferalign();

void testdg_forthdocompiletypealwaysexecute();
void testdg_forthdocompiletypesubroutine();
void testdg_forthdocompiletypedpushn();
void testdg_forthdocompiletypedpushdn();
void testdg_forthdocompiletypedpushp();
void testdg_forthdocompiletypedpushs();
void testdg_forthdocompiletypewordsstringquotes();
void testdg_forthdocompiletypewords0stringquotes();
void testdg_forthdocompiletypecdecl();
void testdg_forthdocompiletypecdeclretuint128();
void testdg_forthdocompiletypeftcolon();
void testdg_forthdocompiletypebracketwordlistdot();
void testdg_forthdocompiletypevalue();
void testdg_forthdocompiletypefvalue();
void testdg_forthdocompiletypetwovalue();
void testdg_forthscommatoos();
void testdg_forths0commatoob();

// c lstring routines
void testdg_getlstringstartoffset();
void testdg_getlstringlength();
void testdg_getnumberoflstringsonstack();
void testdg_getplstring();
void testdg_getlstring();
void testdg_poplstring();
void testdg_pushlstring();
void testdg_growlstring();
void testdg_picklstring();
void testdg_droplstring();
void testdg_deletelstring();
void testdg_insertlstring();
void testdg_deleteinlstring();
void testdg_insertinlstring();
void testdg_catlstringn();
void testdg_copystolstringn();
void testdg_pushstolstringn();
void testdg_copysfromlstringn();
void testdg_setlengthlstringn();
void testdg_replacelstringn();
void testdg_copylstringntoreplacelstringn();
void testdg_copytoinsertlstrntom();
void testdg_makesurelstringnexists();
void testdg_newfreeablelstringarray();
void testdg_freefreeablelstringarray();
void testdg_newfreeablelstring();
void testdg_freefreeablelstring();
void testdg_isfreeablelstringfree();
void testdg_getsflstrheader();
void testdg_copyflstrheadertos();
void testdg_insertsintoflstrn();
void testdg_copysfromflstrn();
void testdg_copytoinsertflstrntom();
void testdg_deleteinflstringn();
void testdg_getlengthflstringn();
void testdg_newfreeablelstringonend();
void testdg_comparestolstringn();
void testdg_deleteuint64inlstringn();
void testdg_insertwithcfillinlstringn();
void testdg_packlstring();
void testdg_unpacklstring();
void testdg_stonewstring();
void testdg_stonew0string();
void testdg_dropnlstrings();
void testdg_uleextendlstringntol();
void testdg_uleaddlstringntolstringn();
void testdg_uleadclstringntolstringn();
void testdg_ulesbblstringntolstringn();
void testdg_uleandlstringntolstringn();
void testdg_uleorlstringntolstringn();
void testdg_ulexorlstringntolstringn();
void testdg_ulenandlstringntolstringn();
void testdg_ulenorlstringntolstringn();
void testdg_ulexnorlstringntolstringn();
void testdg_notlstringn();
void testdg_reverselstringn();
void testdg_lelshiftlstringn();
void testdg_ulershiftlstringn();
void testdg_slershiftlstringn();
void testdg_lelshiftclstringn();
void testdg_lershiftclstringn();
void testdg_mulu64bylstringnaddtolstringn();
void testdg_divlstringnbyu64();
void testdg_fescdecodelstring();
void testdg_fescencodelstring();

void testdg_initlstringqueue();
void testdg_pushlstringqueuehead();
void testdg_poplstringqueuetail();
void testdg_getslstringqueuetail();
void testdg_dropslstringqueuetail();

void testdg_newfreesharedlstringqueue();

void testnewvocabularyword();
void testgetword();

void testdg_chartodigit();
void testdg_pchartonumber();
void testdg_hexdectonumber();

void testdg_newwordlist();
void testdg_newword();
void testdg_getpdefinition();
void testdg_linkdefinition();
void testdg_createsubthreaddef();
void testdg_createvariabledef();
void testdg_createconstantdef();
void testdg_getlatestdefinition();
void testdg_getnextdefinition();
void testdg_interpretdefinition();
void testdg_finddefinwordlist();
void testdg_findefinsearchorder();
void testdg_newpresortedwordlist();
void testdg_copyandrenamewordid();
void testdg_findcopyandrenameword();

void testdg_safecompiledefinition();

void testdg_evaluatebuffer();
void testdg_hibit();

void testdg_checkloopdone();
void testdg_checkplusloopdone();

// C sorted list test routines
//extern const char* dg_forthtestcompareroutinename;
//void dg_forthtestcompareroutine (Bufferhandle* pBHarrayhead);

//void testdg_findaftermatchinsortedarray();
//void testdg_addkeytosortedarray();
//void testdg_removekeyfromsortedarray();
//void testdg_findsortedkeyinlstring();
//void testdg_addsortedkeyinlstring();
void testdg_removesortedkeyinlstring();
//void testdg_getshlistelementvalue();
//void testdg_findsinsortedlstrings();

// C Hierarchical list routines
void testdg_gethlistheaderarrayheader();
void testdg_querycreatehlistheaderarray();

void testdg_gethlistheader();
void testdg_newhlist();
void testdg_freehlist();
void testdg_linklasthlistchildelement();
void testdg_unlinkhlistchildelement();
void testdg_newhlistelement();
void testdg_freehlistelement();

void testdg_gethlistlastchildofparent();
void testdg_gethlistnextsibling();
void testdg_gethlistprevioussibling();
void testdg_getshlistelementnom();
void testdg_getshlistelementvalue();

void testdg_findsortedhlistchild();
void testdg_dobinaryinsertsortstep();

void testdg_newunsortedhlistelement();
void testdg_gethlistelementparent();
void testdg_sethlistelementvalue();
void testdg_getshlistelementnamene();
void testdg_sortcomparehlistnom();
void testdg_getidofsortedhlistchildn();
void testdg_addnsamechartostring();
void testdg_changehlistelementparent();
void testdg_prunehlistelement();
void testdg_hlisttodglumlstring();
void testdg_callhlistchildrenbyn();
void testdg_callhlistchildren();

void testdg_checkfornamedbuffer();
void testdg_patchaddressusingdlsym();
void testdg_patchaddressusinghlist();
void testdg_patchpnewbuffer();
void testdg_loadsharedliblist();
void testdg_glu();
void testdg_nglu();
void testdg_getnamedsymbollisthideid ();
void testdg_hsymbolnametovalue ();
void testdg_namedbufnametoeid ();
void testdg_namedbufnametobufid ();
void testdg_namedbufnametoaddr ();

void testdg_packhlist();
void testdg_namestringtovaluestring();
void testdg_namestringtovaluestringflag();

void testdg_ubitsmask();

// Forth core routines
void testdg_forthstore();
void testdg_forthnumbersign();
void testdg_forthnumbersigngreater();
void testdg_forthnumbersigns();
void testdg_forthtick();
void testdg_forthparen();
void testdg_forthstar();
void testdg_forthstarslash();
void testdg_forthstarslashmod();
void testdg_forthplus();
void testdg_forthplusstore();
void testdg_forthplusloop();
void testdg_forthcomma();
void testdg_forthtwostore();
void testdg_forthtonumber();
void testdg_forthtor();
void testdg_forthquestiondup();
void testdg_forthfetch();
void testdg_forthaccept();
void testdg_forthallot();
void testdg_forthalign();

void testdg_forthminus();

void testdg_forthdot();

void testdg_forthlessthan();

void testdg_forthequals();

void testdg_forthtwofetch();
void testdg_forthtwodrop();
void testdg_forthtwodup();
void testdg_forthtwoover();
void testdg_forthtwoswap();
void testdg_forthlessthannumbersign();
void testdg_forthtobody();
void testdg_forthtoin();

void testdg_forthbase();  // I coulda made this compile type variable
void testdg_forthbl();

void testdg_forthcstore();
void testdg_forthccomma();
void testdg_forthcfetch();
void testdg_forthcase();
void testdg_forthcellplus();
void testdg_forthcells();
void testdg_forthchar();
void testdg_forthcharplus();
void testdg_forthcmove ();
void testdg_forthcmoveto ();
void testdg_forthconstant();
void testdg_forthcount();

void testdg_forthcr();
void testdg_forthcreate();
void testdg_forthdepth();
void testdg_forthdo();
void testdg_forthdoes();

void testdg_forthdrop();
void testdg_forthdup();

void testdg_forthemit();
void testdg_forthenvironmentquery();
void testdg_forthevaluate();
void testdg_forthexecute();
void testdg_forthexit();
void testdg_forthfill();
void testdg_forthfind();
void testdg_forthfmslashmod();
void testdg_forthhere();
void testdg_forthhold();
void testdg_forthimmediate();
void testdg_forthleave();
void testdg_forthliteral();
void testdg_forthloop();
void testdg_forthmove();
void testdg_forthover();
void testdg_forthpostpone();
void testdg_forthrecurse();
void testdg_forthrfrom();
void testdg_forthrfetch();
void testdg_forthrot();
void testdg_forthsign();

void testdg_forthsource();
void testdg_forthspace();
void testdg_forthspaces();
void testdg_forthtype();
void testdg_forthudot();

void testdg_forthumstar();
void testdg_forthumslashmod();

void testdg_forthstate(); // I coulda made this compile type variable
void testdg_forthunloop();

void testdg_forthgreaterthan();
void testdg_forthand();
void testdg_forthlshift();
void testdg_forthmstar();
void testdg_forthmax();
void testdg_forthmin();
void testdg_forthmod();
void testdg_forthor();
void testdg_forthrshift();
void testdg_forthsmslashrem();
void testdg_forthstod();
void testdg_forthulessthan();
void testdg_forthumstar();
void testdg_forthvariable();
void testdg_forthword();
void testdg_forthxor();

void testdg_forthzeroless();
void testdg_forthzeroequals();
void testdg_forthoneplus();
void testdg_forthoneminus();
void testdg_forthtwostar();
void testdg_forthtwoslash();
void testdg_forthabs();
void testdg_forthaligned();
void testdg_forthdg_forthcharplus();
void testdg_forthchars();
void testdg_forthinvert();
void testdg_forthi();
void testdg_forthj();
void testdg_forthmod();
void testdg_forthnegate();

void testdg_forthslash();
void testdg_forthslashmod();

void testdg_forthleftbracket();
void testdg_forthrightbracket();

void testdg_forthcolon();
void testdg_forthsemicolon();

void testdg_forthbegin();
void testdg_forthelse();
void testdg_forthif();
void testdg_forthrepeat();
void testdg_forthswap();
void testdg_forththen();
void testdg_forthuntil();
//void testdg_forthwhile(); IF is tested and SWAP is tested so... I'm going to skip this one

void testdg_forthzeronotequals();
void testdg_forthzerogreater();
void testdg_forthnotequals();
void testdg_forthcompilecomma();
void testdg_forthdecimal();
void testdg_fortherase();
void testdg_forthhex();
void testdg_forthnip();
void testdg_forthpick();
void testdg_forthroll();
void testdg_forthugreaterthan();
void testdg_forthwithin();
void testdg_forthminusrot ();

// forth string words
void testdg_forthdashtrailing ();
void testdg_forthcompiles();
void testdg_forthslashstring ();
void testdg_forthblank ();
void testdg_forthcompare ();
void testdg_forthsearch();

// forth programming tools words
void testdg_forthsynonym ();

// forth locals words
void testdg_savelocalstackdepth();
void testdg_restorelocalstackdepth();
void testdg_forthlocalsfetch();
void testdg_forthtolocals();
void testdg_forthdocompiletypelocal();
void testdg_forthlocalsbar();

//void testdg_forthcontrolflow();

// dg_forth buffer words
void testdg_forthocfetch();
void testdg_forthofetch();
void testdg_forthostonewstring();

void testdg_forthocstore();
void testdg_forthostore();

void testdg_forthctobuf();
void testdg_forthtobuf();
void testdg_forthstringtobuf();

void testdg_forthbuftoc();
void testdg_forthbufto();
void testdg_forthbuftostring();

void testdg_forthosstore();
void testdg_forthosfetch();
void testdg_forthstobuf();
void testdg_forthbuftos();

void testdg_forthlengthbuf();

void testdg_forthgetsbufferhandlearrayhead();
void testdg_forthgetsbufferhandle();
void testdg_forthgetoarrayelement();
void testdg_forthgetparrayelement();

void testdg_forthgetbuffersize();
void testdg_forthgetbuffermaxsize();
void testdg_forthgetbuffergrowby();
void testdg_forthgetbuffercurrentoffset();
void testdg_forthputbuffercurrentoffset();
void testdg_forthgetpbufferlength();
void testdg_forthgetpbuffercurrentoffset();

void testdg_forthinsertinbuffer();
void testdg_forthdeleteinbuffer();
void testdg_forthreplaceinbuffer();
void testdg_forthinsertsintobuffer ();
void testdg_forthgrowbuffer();
void testdg_forthshrinkbuffer();
void testdg_forthemptybuffer();
void testdg_forthnewbuffer();
void testdg_forthfreebuffer();
void testdg_forthgetpbufferoffset();
void testdg_forthgetpbuffer();
void testdg_forthgetsbuffer();
void testdg_forthgetpbuffersegment();
void testdg_forthparse();
void testdg_forthparsebuffer();
void testdg_forthparseword();
void testdg_forthparsewords();
void testdg_forthparseline();
void testdg_forthmaxusedbuffers();
void testdg_forthinusebuffers();
void testdg_forthinusebytes();
void testdg_forthtocurrent();
void testdg_forthcurrentfrom();
void testdg_forthbrackettoorderconstant();
void testdg_forthbitset();
void testdg_forthbitclr();
void testdg_forthbitnot();
void testdg_forthumax();
void testdg_forthumin();
void testdg_forthulessthanequals();
void testdg_forthugreaterthanequals();

// dg_forth lstring words
void testdg_forthdepthlstring();
void testdg_forthstartoffsetlstring();
void testdg_forthlengthlstring();
void testdg_forthgetslstringn();
void testdg_forthgetlstring();
void testdg_forthlstringtos();
void testdg_forthstolstring();
void testdg_forthgrowlstring();
void testdg_forthpicklstring();
void testdg_forthdroplstring();
void testdg_forthdeletelstring();
void testdg_forthinsertlstring();
void testdg_forthnotlstringn();
void testdg_forthu8reverselstringn();
void testdg_forthuleaddlstringntolstringn();
void testdg_forthuleadclstringntolstringn();
void testdg_forthulesbblstringntolstringn();
void testdg_forthuleandlstringntolstringn();
void testdg_forthuleorlstringntolstringn();
void testdg_forthulexorlstringntolstringn();
void testdg_forthulenandlstringntolstringn();
void testdg_forthulenorlstringntolstringn();
void testdg_forthulexnorlstringntolstringn();
void testdg_forthlelshiftlstringn();
void testdg_forthulershiftlstringn();
void testdg_forthslershiftlstringn();
void testdg_forthlelshiftclstringn();
void testdg_forthlershiftclstringn();
void testdg_forthu64starlstringnplustolstringn();
void testdg_forthtoslashulelstringn();

void testdg_forthudmslashmod();

// dg_forth string stack words
void testdg_forthcomparestring();
void testdg_forthgetmidstring();
void testdg_forthcatstring();
void testdg_forthlengthstring();
void testdg_forthshortenstring();
void testdg_forthpickstring();
void testdg_forthdropstring();
void testdg_forthdeletestring();
void testdg_forthswapstring();
void testdg_forthnipstring();
void testdg_forthrotstring();
void testdg_forthdepthstring();
void testdg_forthnewstring();
void testdg_forthchartostring();
void testdg_forthtonewstring();
void testdg_forthturnstringinto0string();
void testdg_forthinsertinstring();
void testdg_forthdeleteinstring();
void testdg_forthstringcfetch();
void testdg_forthstringcstore();
void testdg_forthstringtoc();
void testdg_forthstringto();
void testdg_forthctostring();
void testdg_forthtostring();
void testdg_forthstringquotes();
void testdg_forthholdstring();
void testdg_forthnumbersignstring();
void testdg_forthnumbersignsstring();
void testdg_forthsignstring();
void testdg_forthsplitstring();
void testdg_forthputmidstring();
void testdg_forthgetsstringnd();
void testdg_forthfreelibrary();
void testdg_forthwordsstringquotes();
void testdg_forthwords0stringquotes();
void testdg_forthgetargsfromnstrings();
void testdg_forthnotstring();
void testdg_forthreversestring();
void testdg_forthlelshiftstring();
void testdg_forthulershiftstring();
void testdg_forthslershiftstring();
void testdg_forthlelshiftcstring();
void testdg_forthlershiftcstring();
void testdg_forthuleandstring();
void testdg_forthuleorstring();
void testdg_forthulexorstring();
void testdg_forthulenandstring();
void testdg_forthulenorstring();
void testdg_forthulexnorstring();
void testdg_forthgetpoststring();
void testdg_forthqueryzerostringtostring();
void testdg_forthformstringtovaluestringnamestringu();

void testdg_forthgetcurrent();
void testdg_forthsetcurrent();
void testdg_forthsetorder();
void testdg_forthgetorder();
void testdg_forthwordlist();
void testdg_forthdefinitions();
void testdg_forthsearchwordlist();

void testdg_forthnewhlist();
void testdg_forthfreehlist();
void testdg_forthnewhlistelement();
void testdg_forthehdot();
void testdg_forthehbracketnddot();
void testdg_forthehbracket1ddot();
void testdg_forthehnewelements();
void testdg_forthquerynamestrtovaluestr();
void testdg_forthehquerynamestrtovaluestr();
    
void testdg_pulloneaddressingmode();
void testdg_formatsib();
void testdg_formatmodrslashm();
void testdg_compilepsf();
void testdg_gettargettype ();
void testdg_compilentoa ();
void testdg_compilentom ();
void testdg_compilentor ();
void testdg_compilertom ();
void testdg_compiletwotargets ();
void testdg_determineparameterregister();
    
void testdg_getsenvnamevalue ();
void testdg_timeslog2 ();
void testdg_f64tobase10 ();
void testdg_unpackdf ();
void testdg_f64tof64rootf642expf6410exp ();
void testdg_fixedpointu128todecimalstring ();
void testdg_represent ();
void testdg_f64twotothex();
void testdg_forthdtof();
void testdg_forthstof();
void testdg_forthfstore();
void testdg_forthfstar();
void testdg_forthffetch();
void testdg_forthfplus();
void testdg_forthfminus();
void testdg_forthfslash();
void testdg_forthfzerolessthan();
void testdg_forthfzeroequals();
void testdg_forthflessthan();
void testdg_forthftod();
void testdg_forthftos();
void testdg_forthfdepth();
void testdg_forthfdrop();
void testdg_forthfdup();
void testdg_forthfliteral();
void testdg_forthfloor();
void testdg_forthfmin();
void testdg_forthfmax();
void testdg_forthfnegate();
void testdg_forthfround();
void testdg_forthfover();
void testdg_forthfrot();
void testdg_forthfswap();
void testdg_forthrepresent();
void testdg_forthfstarstar();
void testdg_forthfabs();
void testdg_forthfacos();
void testdg_forthfacosh();
void testdg_forthfalog();
void testdg_forthfasin();
void testdg_forthfasinh();
void testdg_forthfatan();
void testdg_forthfatan2();
void testdg_forthfatanh();
void testdg_forthfcos();
void testdg_forthfcosh();
void testdg_forthfexp();
void testdg_forthfexpm1();
void testdg_forthfln();
void testdg_forthflnp1();
void testdg_forthflog();
void testdg_forthfsin();
void testdg_forthfsincos();
void testdg_forthfsinh();
void testdg_forthfsqrt();
void testdg_forthftan();
void testdg_forthftanh();
void testdg_forthfproximate();
void testdg_forthprecision();
void testdg_sfstore();
void testdg_sffetch();
void testdg_sfalign();
void testdg_sfaligned();
void testdg_sfloatplus();
void testdg_sfloats();
void testdg_forthtwotor();
void testdg_forthtwoliteral();
void testdg_forthtworfrom();
void testdg_forthtworfetch();

void testdg_forthtworot();
// ddvoid testdg_forthdstar();
void testdg_forthdplus();
void testdg_forthdminus();
void testdg_forthdequals();
void testdg_forthdzeroless();
void testdg_forthdzeroequals();
void testdg_forthdlessthan();
void testdg_forthdtwostar();
void testdg_forthdtwoslash();
void testdg_forthdtos();
void testdg_forthdabs();
void testdg_forthdmax();
void testdg_forthdmin();
void testdg_forthdnegate();
void testdg_forthdulessthan();
void testdg_forthmstarplus();
void testdg_forthmplus();
void testdg_forthddot();
void testdg_forthddotr();

void testdg_pushsymboltowin64coffsymboltable();
void testdg_pushsectionlengthtowin64coffsymboltable();
void testdg_pushexportsymbolstowin64coffbuffers();
void testdg_pushimportsymbolstowin64coffbuffers();
void testdg_forthfindlibrarysymbol();
void testdg_forthcallprocaddress();
void testdg_forthcallprocaddressretuint128();
void testdg_forthcalldfpprocaddress();
void testdg_forthopenlibrarystring();

void testdg_regtolocalsregindex();
void testdg_localsregindextoreg();
void testdg_paramregsindextolocalsregindex();
void testdg_marklocalsregasused();
void testdg_forthallrmaskunuse();
void testdg_usenextunusedlocalsintreg();
void testdg_usenextunusedlocalsfloatreg();
void testdg_forthregscurly();


#ifdef  __cplusplus
}
#endif


#endif  /* _INC_testdglu */
