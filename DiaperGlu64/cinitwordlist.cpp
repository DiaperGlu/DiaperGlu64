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

#include "diapergluforth.h"

// //////////////////////////////////////////////////////////////////////
//
// dg_initwordlists
//
// Inputs:
//  Bufferhandle*  pBHarrayhead      pointer to a Bufferhandle structure which is 
//                                    used as the bufferhandle for the array where the other 
//                                    bufferhandles are stored         
//
// Action:
//  Creates the initial word lists and populates them with words.
//
// Failure cases:
//  error in a subroutine - (no error is pushed from this routine)
//   
// //////////////////////////////////////////////////////////////////////

void dg_initwordlists (Bufferhandle* pBHarrayhead)
{
    //unsigned char* pwlhabuf;
    //UINT64* pwlhabuflength;

    UINT64 definition;

    UINT64 forthvocabid;
    UINT64 environmentvocabid;
    UINT64 buffervocabid;
    // UINT64 stringstackvocabid;
    // UINT64 operatingsystemvocabid;
    UINT64 uservocabid;
    // UINT64 errorvocabid;
    UINT64 localsvocabid;
    UINT64 x86vocabid;
    UINT64 colorvocabid;
    
    Premadeword* ppremadewordlist;


    // forth standard words    
    ppremadewordlist = dg_getppresortedcorewords(pBHarrayhead);
    
    if ((Premadeword*)badbufferhandle == ppremadewordlist)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize core premade wordlist, buffer size incorrect\n");
        return;
    }
    
    // freebsd 6.2 doesn't link to the structures when in a dll correctly, so I switched to a function
    forthvocabid = dg_newpresortedwordlist (
        pBHarrayhead,
        ppremadewordlist, // &(mypresortedcorewords[0]),
        dg_presortedcorewordlistsize);


    // forth environment words
    ppremadewordlist = dg_getppresortedenvironmentwords();
    
    if ((Premadeword*)badbufferhandle == ppremadewordlist)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize environment premade wordlist, buffer size incorrect\n");
        return;
    }

    environmentvocabid = dg_newpresortedwordlist (
        pBHarrayhead,
        ppremadewordlist, // &(mypresortedenvironmentwords[0]),
        dg_presortedenvwordlistsize);


    // non forth standard words
    ppremadewordlist = dg_getppresortedbufferwords(pBHarrayhead);
    
    if ((Premadeword*)badbufferhandle == ppremadewordlist)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize buffer premade wordlist, buffer size incorrect\n");
        return;
    }

    buffervocabid = dg_newpresortedwordlist (
        pBHarrayhead,
        ppremadewordlist, // &(mypresortedbufferwords[0]),
        dg_prestoredbufferwordlistsize);


    uservocabid = dg_newwordlist(pBHarrayhead, 0);

    
    localsvocabid = dg_newwordlist(pBHarrayhead, 0);


    colorvocabid = dg_newwordlist(pBHarrayhead, 0);


    // x86 assembler words
    ppremadewordlist = dg_getppresortedx86words();
    
    if ((Premadeword*)badbufferhandle == ppremadewordlist)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Unable to initialize x86 premade wordlist, buffer size incorrect\n");
        return;
    }
    
    x86vocabid = dg_newpresortedwordlist (
        pBHarrayhead,
        ppremadewordlist,
        dg_presortedx86wordlistsize);


    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_corewordlistid, forthvocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_environmentwordlistid, environmentvocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_bufferwordlistid, buffervocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_userwordlistid, uservocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, localsvocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_cpux86vocabid, x86vocabid);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_colorvocabid, colorvocabid);

    dg_initcpux86wordlist(pBHarrayhead);

    // set up initial current compile word list
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, uservocabid);
 
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error intializing wordlists\n");
        return;
    }   


    // set up initial search order
    // dg_pushbufferuint64(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, errorvocabid); // error word list will be searched last

    dg_pushbufferuint64(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, forthvocabid); // core word list will be searched second last

    dg_pushbufferuint64(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, buffervocabid);

    dg_pushbufferuint64(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, uservocabid); // user vocab will be searched first
 
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error setting up search order\n");
        return;
    }  
    

    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthforthwords),
        (unsigned char*)dg_forthforthwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);

/*
    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_fortherrorwords),
        (unsigned char*)dg_fortherrorwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);
*/

    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthenvironmentwords),
        (unsigned char*)dg_forthenvironmentwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthbufferwords),
        (unsigned char*)dg_forthbufferwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthstringwords),
        (unsigned char*)dg_forthstringwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthlibrarywords),
        (unsigned char*)dg_forthlibrarywordsname);


    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthuserwords),
        (unsigned char*)dg_forthuserwordsname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);

    

    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)(forthvocabid),
        (unsigned char*)dg_forthforthwordlistname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);

    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error adding words names\n");
        return;
    }
    
/*
    definition = dg_new0stringcorenameword(
        pBHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)&dg_forthdocompiletypedpushn,
        0,
        errorvocabid,
        (unsigned char*)dg_fortherrorwordlistname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);
 */   
    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)&dg_forthdocompiletypedpushn,
        0,
        environmentvocabid,
        (unsigned char*)dg_forthenvironmentwordlistname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);

    definition = dg_new0stringnamecoreword(
      pBHarrayhead, 
      (UINT64)(&dg_forthdocompiletypedpushn),
      (UINT64)(buffervocabid), 
      (unsigned char*)dg_forthbufferwordlistname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition); 
    
    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthfunctblofn),
        (unsigned char*)dg_forthfunctblofnname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);

    
    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypeftcolon), // call/compile function table
        1,                         // function table function 1
        (unsigned char*)"FTDUP");  // it's DUP except called through a function table
                                   //  this experiment in calling Diaperglu functions from
                                   //  precompiled files has been superceded by the linker

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);



    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_LINKNEWBUFFERIDSTACK_BUFFERID,
        (unsigned char*)dg_linknewbufstackbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);
    

    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_WORD_BUFFERID,
        (unsigned char*)dg_forthwordbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_LEAVESTACK_BUFFERID,
        (unsigned char*)dg_forthleavebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_ARGS_BUFFERID,
        (unsigned char*)dg_forthargsbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_CLEANUP_BUFFERID,
        (unsigned char*)dg_forthcleanupbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_LIBHANDLE_BUFFERID,
        (unsigned char*)dg_forthlibhandlebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_POST_BUFFERID,
        (unsigned char*)dg_forthpostbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)DG_SCRIPTFILENAME_BUFFERID,
        (unsigned char*)dg_forthscriptfilenamebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)DG_LOCALPATH_BUFFERID,
        (unsigned char*)dg_forthlocalpathbufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_WORDNAME_BUFFERID,
        (unsigned char*)dg_forthwordnamebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)DG_EXTENDABLECODESPACE_BUFFERID,
        (unsigned char*)dg_forthextendablecodespacebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)DG_EXTENDABLEDATASPACE_BUFFERID,
        (unsigned char*)dg_forthextendabledataspacebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);


    definition = dg_new0stringcorenameword(
        pBHarrayhead, 
        DG_CORE_BUFFERID,
        (UINT64)(&dg_forthdocompiletypedpushn),
        0,
        DG_CORE_BUFFERID,
        (unsigned char*)dg_forthcorebufferidname);

    dg_linkdefinition(pBHarrayhead, buffervocabid, definition);
    


    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error adding buffer and wordlist names\n");
        return;
    }

    ////////////////////////////
    // Set up user wordlist   //
    ////////////////////////////


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypedpushn),
        (UINT64)(uservocabid),
        (unsigned char*)dg_forthuserwordlistname);

    dg_linkdefinition(pBHarrayhead, forthvocabid, definition);


    /////////////////////


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthshowlicense),
        (unsigned char*)dg_forthshowlicensename);

    dg_linkdefinition(pBHarrayhead, uservocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthforthwords),
        (unsigned char*)dg_forthforthwordsname);

    dg_linkdefinition(pBHarrayhead, uservocabid, definition);


    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error initializing user wordlist\n");
        return;
    }


    /////////////////////////////
    // Set up color wordlist   //
    /////////////////////////////


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthci),
        (unsigned char*)dg_forthciname);

    dg_linkdefinition(pBHarrayhead, colorvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthcleftbracket),
        (unsigned char*)dg_forthcleftbracketname);

    dg_linkdefinition(pBHarrayhead, colorvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthcrightbracket),
        (unsigned char*)dg_forthcrightbracketname);

    dg_linkdefinition(pBHarrayhead, colorvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthcp),
        (unsigned char*)dg_forthcpname);

    dg_linkdefinition(pBHarrayhead, colorvocabid, definition);


    definition = dg_new0stringnamecoreword(
        pBHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthcleftparen),
        (unsigned char*)dg_forthcleftparenname);

    dg_linkdefinition(pBHarrayhead, colorvocabid, definition);


    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"got error initializing color wordlist\n");
        return;
    }

}

