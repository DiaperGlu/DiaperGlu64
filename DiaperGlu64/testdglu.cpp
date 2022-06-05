// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.4.
//
//    DiaperGlu v5.4 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.4 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.4; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 5, 2022               //
// version 5.4                //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"
// #include <stdio.h>

void dg_forthselftest ()
{
	// test C error routines
	// printf("... entering self test\n");
    
	testdg_initerrors();
	testdg_pusherror();
	testdg_geterror();
	testdg_poperror();
	testdg_geterrorcount();
	testdg_checkerrorsonstack();
	testdg_clearerrors();
    testdg_replaceerrors();
    
	// test C buffer routines
	testdg_newbuffer();     // these three originally were at the top
	testdg_growbuffer();
	testdg_shrinkbuffer();
    
	testdg_getpbuffersegment();
	testdg_getpbuffer();
    
    
	testdg_getbuffersegment();
    testdg_putbuffersegment();
	testdg_pushbuffersegment();
    
	testdg_popbuffersegment();
	testdg_pickbuffersegment();

	testdg_getbufferbyte();
	testdg_putbufferbyte();
	testdg_popbufferbyte();
	testdg_pushbufferbyte();
    
    testdg_getbufferuint32();
    testdg_putbufferuint32();
    testdg_pushbufferuint32();
    testdg_popbufferuint32();
    
	testdg_getbufferuint64();
	testdg_putbufferuint64();
	testdg_pushbufferuint64();
	testdg_popbufferuint64();

	testdg_insertinbuffer();
	testdg_deleteinbuffer();

	testdg_getbufferlength();

	testdg_push0stringtobuffersegment();
	testdg_getpbufferhandle();

    testdg_checkbuffer();

    testdg_freebufferset();
    testdg_newbufferset();
    
    testdg_getuint64arrayelement();
    testdg_putuint64arrayelement();
    
    testdg_getuint64stackelement();
    testdg_putuint64stackelement();
    
    testdg_stonewbuffer();
    
    testdg_getpnewbuffer();
    testdg_pushhctwotobuffer();
    
    testdg_parseword();
    testdg_parse();
    testdg_parsemultiline();
    testdg_parsewords();
    testdg_noparseentirecurrentline();
    testdg_parseline();
    testdg_noparselineatoffset();
    testdg_replacebuffersegment();
    testdg_tocurrent();
    testdg_currentfrom();

	//need dg_clearbuffer
	//need dg_getpbufferoffset
	//need dg_getpbufferhandle

	// test C lstring words
	testdg_getlstringstartoffset();
	testdg_getlstringlength();
	testdg_getnumberoflstringsonstack();
    testdg_getplstring();
	testdg_getlstring();
	testdg_poplstring();
	testdg_pushlstring();
	testdg_growlstring();
	testdg_picklstring();
	testdg_droplstring();
	testdg_deletelstring();
	testdg_insertlstring();
    testdg_deleteinlstring();
    testdg_insertinlstring();
    testdg_catlstringn();
    testdg_copystolstringn();
    testdg_pushstolstringn();
    testdg_copysfromlstringn();
    testdg_setlengthlstringn();
	testdg_replacelstringn();
    testdg_copylstringntoreplacelstringn();
    testdg_copytoinsertlstrntom();
    testdg_makesurelstringnexists();
    testdg_newfreeablelstringarray();
    testdg_freefreeablelstringarray();
    testdg_newfreeablelstring();
    testdg_freefreeablelstring();
    testdg_isfreeablelstringfree();
    testdg_getsflstrheader();
    testdg_copyflstrheadertos();
    testdg_insertsintoflstrn();
    testdg_copysfromflstrn();
    testdg_copytoinsertflstrntom();
    testdg_deleteinflstringn();
    testdg_getlengthflstringn();
    testdg_newfreeablelstringonend();
    testdg_comparestolstringn();
    testdg_deleteuint64inlstringn();
    testdg_insertwithcfillinlstringn();
    testdg_packlstring();
    testdg_unpacklstring();
    testdg_stonewstring();
    testdg_stonew0string();
    testdg_dropnlstrings();
    testdg_uleextendlstringntol();
    testdg_uleaddlstringntolstringn();
    testdg_uleadclstringntolstringn();
    testdg_ulesbblstringntolstringn();
    testdg_uleandlstringntolstringn();
    testdg_uleorlstringntolstringn();
    testdg_ulexorlstringntolstringn();
    testdg_ulenandlstringntolstringn();
    testdg_ulenorlstringntolstringn();
    testdg_ulexnorlstringntolstringn();
    testdg_notlstringn();
    testdg_reverselstringn();
    testdg_lelshiftlstringn();
    testdg_ulershiftlstringn();
    testdg_slershiftlstringn();
    testdg_lelshiftclstringn();
    testdg_lershiftclstringn();
    testdg_mulu64bylstringnaddtolstringn();
    testdg_divlstringnbyu64();
    
    // test C lstring queue stuff
    testdg_initlstringqueue();
    testdg_pushlstringqueuehead();
    testdg_poplstringqueuetail();
    testdg_getslstringqueuetail();
    testdg_dropslstringqueuetail();
    testdg_newfreesharedlstringqueue();
 
 // test C hierarchical list routines
    testdg_gethlistheaderarrayheader();
    testdg_querycreatehlistheaderarray();
    
    testdg_gethlistheader();
    testdg_newhlist();
    testdg_freehlist();
    testdg_linklasthlistchildelement();
    testdg_unlinkhlistchildelement();
    testdg_newhlistelement();
    testdg_freehlistelement();
    
    testdg_gethlistlastchildofparent();
    testdg_gethlistnextsibling();
    testdg_gethlistprevioussibling();
    testdg_getshlistelementnom();
    testdg_getshlistelementvalue();

    testdg_dobinaryinsertsortstep();
    testdg_findsortedhlistchild();
    
    
    testdg_newunsortedhlistelement();
    testdg_gethlistelementparent();
    testdg_sethlistelementvalue();
    testdg_getshlistelementnamene();
    testdg_sortcomparehlistnom();
    testdg_getidofsortedhlistchildn();
    testdg_addnsamechartostring();
    testdg_changehlistelementparent();
    testdg_prunehlistelement();
    testdg_hlisttodglumlstring();
    testdg_callhlistchildren();
    testdg_callhlistchildrenbyn();
    testdg_packhlist();
    testdg_namestringtovaluestring();

	// C number conversion


	// test C wordlist words
	testdg_newwordlist();
	testdg_newword();
	testdg_getpdefinition();
	testdg_linkdefinition();
	testdg_createsubthreaddef();
	testdg_createvariabledef();
	testdg_createconstantdef();
	testdg_getlatestdefinition();
	testdg_getnextdefinition();
	testdg_executedefinition();
	testdg_finddefinwordlist();
	testdg_findefinsearchorder();
	//need change latest compile routine
    testdg_newpresortedwordlist();
    testdg_copyandrenamewordid();
    testdg_findcopyandrenameword();
    testdg_createbrackettoorderconstantdef();

	// test C evaluate
	testdg_evaluatebuffer();
    testdg_hibit();   
    
    // test c compiling routines
    testdg_bumpdisplacementsizeifneeded();
	testdg_compilemovregtoreg();
	testdg_compilenegatereg();
	testdg_compileaddregtoreg();
	testdg_compilesubn8fromrsp();
	testdg_compileaddn8torsp();
	testdg_compilepushntoret();
	testdg_compilepopregfromret();
	testdg_compilepushregtoret();
	testdg_compilecalloffset();
	testdg_compilejmpoffset();
	testdg_compilecalladdress();
	testdg_callbuffer();
    testdg_callprocaddress();
    testdg_callprocaddressretuint128();
    testdg_calldfpprocaddress();
	testcompiledemptysubroutine();
	testcompiledstackalign();
	testcompileinitlocalreturnpBHarrayhead();
	testcompileinitlocalreturnframepBHarrayhead();
	testcompilecallforthroutineincore();
	testcompilecallforthroutineincoreatvariousaligments();
//	testcompilecallsubroutineswithvariousnumberofparameters();
	testcompilecalloffsetinsamebuffer();
	testdg_compilepushtodatastack();
    testdg_compilepushntodatastack();
    

    testdg_initjumpbuffer();
	testdg_compilesafecall();
/*	testdg_forthcompilegetolderrorcount();
    
	testdg_packmodrslashm();
	testdg_packsib();
*/
	testdg_forthsquotes();
	testdg_forthosquotes();
	testdg_fortho0quotes();
    testdg_packtwobytevex();
    testdg_packthreebytevex();
    testdg_compilevex();
    testdg_compileaddnlocalstocallsubsframe();
    
/*
    // test C sorted list routines
    //testdg_findaftermatchinsortedarray();
    //testdg_addkeytosortedarray();
    //testdg_removekeyfromsortedarray();
   // testdg_findsortedkeyinlstring();
    //testdg_addsortedkeyinlstring();
    //testdg_removesortedkeyinlstring();
    //testdg_findsinsortedlstrings();
*/
    

    // test linker words
    testdg_patchaddressusingdlsym();
    testdg_patchaddressusinghlist();
    testdg_patchpnewbuffer();
    testdg_loadsharedliblist();
    testdg_glu();
    testdg_nglu();
    testdg_getnamedsymbollisthideid ();
    testdg_hsymbolnametovalue ();
    testdg_namedbufnametoeid ();
    testdg_namedbufnametobufid ();
    testdg_namedbufnametoaddr ();

	// test Forth Core Words
	testdg_checkloopdone ();
	testdg_checkplusloopdone();
	
	testdg_forthstore();
	testdg_forthnumbersign();
	testdg_forthnumbersigngreater();
	testdg_forthnumbersigns();
	testdg_forthtick();
	testdg_forthparen();
	testdg_forthstar();
	testdg_forthstarslash();
	testdg_forthstarslashmod();
	testdg_forthplus();
	testdg_forthplusstore();
    
	testdg_forthplusloop();
	testdg_forthcomma();
	testdg_forthminus();
	testdg_forthdot();
	// dotquotes not tested here
	testdg_forthslash();
	testdg_forthslashmod();
	testdg_forthzeroless();
	testdg_forthzeroequals();
	testdg_forthoneplus();
	testdg_forthoneminus();
	testdg_forthtwostore();
	testdg_forthtwostar();
	testdg_forthtwoslash();
	testdg_forthtwofetch();
	testdg_forthtwodrop();
	testdg_forthtwodup();
	testdg_forthtwoover();
	testdg_forthtwoswap();
	testdg_forthcolon();
	testdg_forthsemicolon();
	testdg_forthlessthan();
	testdg_forthlessthannumbersign();
	testdg_forthequals();
	testdg_forthgreaterthan();
	testdg_forthtobody();
	testdg_forthtoin();
	testdg_forthtonumber();
	testdg_forthtor();
	testdg_forthquestiondup();
	testdg_forthfetch();
	// ABORT not tested here
	// ABORT" not tested here
	testdg_forthabs();
	testdg_forthaccept();
	testdg_forthalign();
	testdg_forthaligned();
	testdg_forthallot();
	testdg_forthand();	
	testdg_forthbase();
	testdg_forthbegin();
	testdg_forthbl();
	testdg_forthcstore();
	testdg_forthccomma();
	testdg_forthcfetch();
	testdg_forthcellplus();
	testdg_forthcells();
	testdg_forthchar();
	testdg_forthcharplus();
	testdg_forthchars();   
	testdg_forthconstant();
	testdg_forthcount();
	testdg_forthcr();
	testdg_forthcreate();
	testdg_forthdecimal();
	testdg_forthdepth();
	testdg_forthdo();
	testdg_forthdoes();
	testdg_forthdrop();
	testdg_forthdup();
	testdg_forthelse();
	testdg_forthemit();
//    testdg_forthenvironmentquery();
	// ENVIRONMENT? not tested here
	testdg_forthevaluate();
	testdg_forthexecute();
	testdg_forthexit();
	testdg_forthfill();
	testdg_forthfind();
	testdg_forthfmslashmod();
	testdg_forthhere();
	testdg_forthhold();
	testdg_forthi();
	testdg_forthif();
    testdg_forthimmediate();
	testdg_forthinvert();
	testdg_forthj();
	// KEY not tested here
    testdg_forthleave();
	testdg_forthliteral();
    testdg_forthloop();
	testdg_forthlshift();
	testdg_forthmstar();
    testdg_forthmax();
    testdg_forthmin();
    testdg_forthmod();
	testdg_forthmove();
	testdg_forthnegate();
	testdg_forthor();
	testdg_forthover();
	testdg_forthpostpone();
	// QUIT not tested here
	testdg_forthrfrom();
	testdg_forthrfetch();
    testdg_forthrecurse();
	testdg_forthrepeat();
	testdg_forthrot();
	testdg_forthrshift();
	// S" not tested here
	testdg_forthstod();
	testdg_forthsign();
	testdg_forthsmslashrem();
	testdg_forthsource();
	testdg_forthspace();
	testdg_forthspaces();
	testdg_forthstate();
	testdg_forthswap();
	testdg_forththen();
	testdg_forthtype();
	testdg_forthudot();
	testdg_forthulessthan();
    testdg_forthumstar();
	testdg_forthumslashmod();
	testdg_forthunloop();
	testdg_forthuntil();
	testdg_forthvariable();
	// WHILE not tested here
	testdg_forthword();
	testdg_forthxor();
	testdg_forthleftbracket();
	// ['] not tested here
	// [CHAR] not tested here
	testdg_forthrightbracket();

	// test Forth Core Extension Words
    testdg_forthzeronotequals();
    testdg_forthzerogreater();	
    testdg_forthnotequals();
    testdg_fortherase();
	testdg_forthhex();
    testdg_forthnip();
	testdg_forthpick();
    testdg_forthroll();
    
    testdg_forthugreaterthan();
    testdg_forthminusrot ();
    
    // not sure what category
    testdg_forthudmslashmod();
    
    // forth programming tool words
    testdg_forthsynonym ();
    
    // forth string words
    testdg_forthdashtrailing ();
    testdg_forthcompiles();
    testdg_forthcmove();
    testdg_forthcmoveto();
    testdg_forthslashstring ();
    testdg_forthblank ();
    testdg_forthcompare ();
    testdg_forthsearch();
    
    // forth locals
    testdg_savelocalstackdepth();
    testdg_restorelocalstackdepth();
    testdg_forthlocalsfetch();
    testdg_forthtolocals();
    testdg_forthdocompiletypelocal();
    testdg_forthlocalsbar();

	//dg_initwordlists
	//dg_forthbye
	//push0$tobuffersegment

	// test Forth buffer words
	testdg_forthocfetch();
	testdg_forthofetch();
	testdg_forthostonewstring();
	testdg_forthocstore();
	testdg_forthostore();
	// testputbufferstring2(); // not implemented yet 
	testdg_forthctobuf();
	testdg_forthtobuf();
	testdg_forthstringtobuf();
	testdg_forthbuftoc();
	testdg_forthbufto();
	testdg_forthbuftostring();
	testdg_forthosstore();
	testdg_forthosfetch();
	testdg_forthstobuf();
	testdg_forthbuftos();
	testdg_forthlengthbuf();
	testdg_forthgetsbufferhandlearrayhead();
	testdg_forthgetsbufferhandle();
	testdg_forthgetoarrayelement();
	testdg_forthgetparrayelement();
	testdg_forthgetbuffersize();
	testdg_forthgetbuffermaxsize();
	testdg_forthgetbuffergrowby();
	testdg_forthgetbuffercurrentoffset();
	testdg_forthputbuffercurrentoffset();
	testdg_forthgetpbufferlength();
	testdg_forthgetpbuffercurrentoffset();
	testdg_forthinsertinbuffer();
	testdg_forthdeleteinbuffer();
    testdg_forthreplaceinbuffer();
    testdg_forthinsertsintobuffer ();   
	testdg_forthgrowbuffer();
	testdg_forthshrinkbuffer();
	testdg_forthemptybuffer();
	testdg_forthnewbuffer();
	testdg_forthfreebuffer();
	testdg_forthgetpbufferoffset();
	testdg_forthgetpbuffer();
    testdg_forthgetsbuffer();
	testdg_forthgetpbuffersegment();
    testdg_forthmaxusedbuffers();
    testdg_forthinusebuffers();
    testdg_forthinusebytes();
	testdg_forthparse();
    testdg_forthparsebuffer();   
	testdg_forthparseword();
    testdg_forthparsewords(); 
    testdg_forthparseline();
    testdg_forthtocurrent();
    testdg_forthcurrentfrom();
    testdg_forthbrackettoorderconstant();


	// test Forth lstring stuff
	testdg_forthdepthlstring();
	testdg_forthstartoffsetlstring();
	testdg_forthlengthlstring();
	testdg_forthgetslstringn();
	testdg_forthgetlstring();
	testdg_forthlstringtos();
	testdg_forthstolstring();
	testdg_forthgrowlstring();
	testdg_forthpicklstring();
	testdg_forthdroplstring();
	testdg_forthdeletelstring();
    testdg_forthinsertlstring();
    testdg_forthnotlstringn();
    testdg_forthu8reverselstringn();
    testdg_forthuleaddlstringntolstringn();
    testdg_forthuleadclstringntolstringn();
    testdg_forthulesbblstringntolstringn();
    testdg_forthuleandlstringntolstringn();
    testdg_forthuleorlstringntolstringn();
    testdg_forthulexorlstringntolstringn();
    testdg_forthulenandlstringntolstringn();
    testdg_forthulenorlstringntolstringn();
    testdg_forthulexnorlstringntolstringn();
    testdg_forthlelshiftlstringn();
    testdg_forthulershiftlstringn();
    testdg_forthslershiftlstringn();
    testdg_forthlelshiftclstringn();
    testdg_forthlershiftclstringn();
    testdg_forthu64starlstringnplustolstringn();
    testdg_forthtoslashulelstringn();
    
    // testing Forth string stack stuff
	testdg_forthcomparestring();
	testdg_forthgetmidstring();
	testdg_forthcatstring();
	testdg_forthlengthstring();
	testdg_forthshortenstring();
	testdg_forthpickstring();
	testdg_forthdropstring();
	testdg_forthdeletestring();
	testdg_forthswapstring();
	testdg_forthnipstring();
	testdg_forthrotstring();
	testdg_forthdepthstring();
	testdg_forthnewstring();
	testdg_forthchartostring();
	testdg_forthtonewstring();
	testdg_forthturnstringinto0string();
	testdg_forthinsertinstring();
	testdg_forthdeleteinstring();
	testdg_forthstringcfetch();
	testdg_forthstringcstore();
	testdg_forthstringtoc();
	testdg_forthstringto();
	testdg_forthctostring();
	testdg_forthtostring();
	testdg_forthstringquotes();
	testdg_forthholdstring();
	testdg_forthnumbersignstring();
	testdg_forthnumbersignsstring();
	testdg_forthsignstring();
	testdg_forthsplitstring();
	testdg_forthputmidstring();
    testdg_forthgetsstringnd();
//	testdg_forthfreelibrary();
    testdg_forthwordsstringquotes();
    testdg_forthwords0stringquotes();
    testdg_forthgetargsfromnstrings();
    testdg_forthnotstring();
    testdg_forthreversestring();
    testdg_forthlelshiftstring();
    testdg_forthulershiftstring();
    testdg_forthslershiftstring();
    testdg_forthlelshiftcstring();
    testdg_forthlershiftcstring();
    testdg_forthuleandstring();
    testdg_forthuleorstring();
    testdg_forthulexorstring();
    testdg_forthulenandstring();
    testdg_forthulenorstring();
    testdg_forthulexnorstring();
	
    // test Forth search order words
    testdg_forthgetcurrent();
    testdg_forthsetcurrent();
    testdg_forthsetorder();
//    testdg_forthgetorder();
    testdg_forthwordlist();
    testdg_forthdefinitions();
//    testdg_forthsearchwordlist();

    // test Forth hierarchical list
    testdg_forthnewhlist();
    testdg_forthfreehlist();
    testdg_forthnewhlistelement();
    testdg_forthehdot();
    testdg_forthehbracketnddot();
    testdg_forthehbracket1ddot();
    
    // test Forth floating point
    testdg_timeslog2();
    testdg_f64tobase10();
    testdg_unpackdf();
    testdg_f64tof64rootf642expf6410exp();
    testdg_fixedpointu128todecimalstring();
    testdg_represent();
    testdg_f64twotothex();
    testdg_forthdtof();
    testdg_forthstof();
    testdg_forthfstore();
    testdg_forthffetch();
    testdg_forthfstar();
    testdg_forthfplus();
    testdg_forthfminus();
    testdg_forthfslash();
    testdg_forthfzerolessthan();
    testdg_forthfzeroequals();
    testdg_forthflessthan();
    testdg_forthftod();
    testdg_forthftos();
    testdg_forthfdepth();
    testdg_forthfdrop();
    testdg_forthfdup();
    testdg_forthfliteral();
    testdg_forthfloor();
    testdg_forthfmin();
    testdg_forthfmax();
    testdg_forthfnegate();
    testdg_forthfround();
    testdg_forthfover();
    testdg_forthfrot();
    testdg_forthfswap();
    testdg_forthrepresent();
    testdg_forthfstarstar();
    testdg_forthfabs();
    testdg_forthfacos();
    testdg_forthfacosh();
    testdg_forthfalog();
    testdg_forthfasin();
    testdg_forthfasinh();
    testdg_forthfatan();
    testdg_forthfatan2();
    testdg_forthfatanh();
    testdg_forthfcos();
    testdg_forthfcosh();
    testdg_forthfexp();
    testdg_forthfexpm1();
    testdg_forthfln();
    testdg_forthflnp1();
    testdg_forthflog();
    testdg_forthfsin();
    testdg_forthfsincos();
    testdg_forthfsinh();
    testdg_forthfsqrt();
    testdg_forthftan();
    testdg_forthftanh();
    testdg_forthfproximate();
    testdg_forthprecision();
    testdg_sfstore();
    testdg_sffetch();
    testdg_sfalign();
    testdg_sfaligned();
    testdg_sfloatplus();
    testdg_sfloats();
    
    testdg_forthtwotor();
    testdg_forthtwoliteral();
    testdg_forthtworfrom();
    testdg_forthtworfetch();
    testdg_forthtworot();
    testdg_forthdplus();
    testdg_forthdminus();
    testdg_forthddot();
    testdg_forthddotr();
    testdg_forthdzeroless();
    testdg_forthdzeroequals();
    testdg_forthdtwostar();
    testdg_forthdtwoslash();
    testdg_forthdlessthan();
    testdg_forthdequals();
    testdg_forthdtos();
    testdg_forthdabs();
    testdg_forthdmax();
    testdg_forthdmin();
    testdg_forthdnegate();
    testdg_forthdulessthan();
    testdg_forthmstarplus();
    testdg_forthmplus();

#ifdef DGLU_OS_WIN64
	// win64 specific
	testdg_pushsymboltowin64coffsymboltable();
	testdg_pushsectionlengthtowin64coffsymboltable();
	testdg_pushexportsymbolstowin64coffbuffers();
	testdg_pushimportsymbolstowin64coffbuffers();
	testdg_forthfindlibrarysymbol();
	testdg_forthcallprocaddress();
	testdg_forthcallprocaddressretuint128();
	testdg_forthcalldfpprocaddress();
	testdg_forthopenlibrarystring();
#endif

/*
    // test cpux86 functions
    testdg_pulloneaddressingmode();
    testdg_formatsib ();
    testdg_formatmodrslashm ();
    testdg_compilepsf ();
    testdg_gettargettype ();
    testdg_compilentoa ();
    testdg_compilentom ();
    testdg_compilentor ();
    testdg_compilertom ();
    testdg_compiletwotargets ();
    
    testdg_getsenvnamevalue ();
    */
    
    testdg_determineparameterregister();
    
}
