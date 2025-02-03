// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.13.
//
//    DiaperGlu v5.13 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.13 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.13; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 2, 2025           //
// version 5.13               //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"



void testdg_savelocalstackdepth()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 depth;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_savelocalstackdepth\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    
    dg_savelocalstackdepth (&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_savelocalstackdepth success case - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    depth = dg_popbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID);
    
    if (depth != 2*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_savelocalstackdepth success case - got wrong depth, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_restorelocalstackdepth()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 depth;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_restorelocalstackdepth\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID, 1*sizeof(UINT64));
    
    dg_restorelocalstackdepth (&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_restorelocalstackdepth success case - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    depth = dg_getbufferlength(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID);
    
    if (depth != 1*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_restorelocalstackdepth success case - got wrong bufferlength, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // sucess case 2 same length
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID, 2*sizeof(UINT64));
    
    dg_restorelocalstackdepth (&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_restorelocalstackdepth sucess case 2 same length - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    depth = dg_getbufferlength(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID);
    
    if (depth != 2*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_restorelocalstackdepth sucess case 2 same length - got wrong bufferlength, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthlocalsfetch()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlocalsfetch\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 15);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 25);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 30);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID, 2*sizeof(UINT64));
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    dg_forthlocalsfetch(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[0] - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[0] - got wrong value, expected 15, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    dg_forthlocalsfetch(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[1] - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[1] - got wrong value, expected 20, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(&BHarrayhead, 2);
    
    dg_forthlocalsfetch(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[2] - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 25)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success case f[2] - got wrong value, expected 25, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthtolocals()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtolocals\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 15);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 25);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 30);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID, 2*sizeof(UINT64));
    
    dg_pushdatastack(&BHarrayhead, 35);
    
    dg_forthtolocals(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthtolocals success - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID);
    
    if (x != 35)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthlocalsfetch success - got wrong value, expected 35, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdocompiletypelocal()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 x;
    UINT64 databufid;
    UINT64 databufoffset;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdocompiletypelocal\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 5);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 10);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 15);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 25);
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_DATASTACK_BUFFERID, 30);
    
    dg_pushbufferuint64(&BHarrayhead, DG_LOCALS_STACKDEPTH_BUFFERID, 2*sizeof(UINT64));
    
    dg_pushdatastack(&BHarrayhead, 1);
    dg_pushdatastack(&BHarrayhead, 0);
    dg_pushdatastack(&BHarrayhead, (UINT64)dg_statecompile);
    
    // retesting dg_forthlocalsfetch just in case
    dg_pushdatastack(&BHarrayhead, 1);
    
    dg_forthlocalsfetch(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthdocompiletypelocal success - got wrong value doing dg_forthlocalsfetch, expected 20, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to get here
    databufid = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer);

    databufoffset = dg_getbufferlength(&BHarrayhead, databufid);

    dg_compileinitlocals (&BHarrayhead);
    
    dg_forthdocompiletypelocal (&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthdocompiletypelocal success - got error doing dg_forthdocompiletypelocal, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_compileexitlocals (&BHarrayhead);
    
    dg_callbuffer (
        &BHarrayhead,
        databufid,
        databufoffset);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthdocompiletypelocal success - got error doing dg_callbuffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthdocompiletypelocal success - got wrong value, expected 20, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthqueryclearlocals()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 x;
    UINT64 databufid;
    UINT64 databufoffset;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlocalsbar\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists(&BHarrayhead);
    
    // need a current input buffer with local names in it
    // need a current locals wordlist
    // need to be in a colon definition I think... maybe
    // need locals words in wordlist
    // need a localsdepth level to unnest
    // need usinglocals flag to be set
    // call dg_forthqueryclearlocals
    // check that locals wordlist was emptied
    // check that using locals flag was cleared
    // check that localsdepth was unnested
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthlocalsbar()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 x;
    UINT64 databufid;
    UINT64 databufoffset;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    UINT64 mybufferoffset;
    Bufferhandle* pBH;
    UINT64 mywordlist;
    UINT64 mywordid;
    UINT64 usinglocalsflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlocalsbar\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists(&BHarrayhead);
    
    // need a current interpret buffer with local names in it
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success case - error setting current interpret buffer\n");
        return;
    }
    
    // for dg_forthqueryclearlocals
    
    // need a current locals wordlist
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, mywordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - error setting current compile wordlist\n");
        return;
    }
    
    dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 17, (unsigned char*)"testname after | ");
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - error pushing string to current interpret buffer\n");
        return;
    }
    
    dg_forthleftbracket(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - error doing left bracket\n");
        return;
    }
    
    // need to be in a colon definition I think...
    dg_forthcolon(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - error doing colon\n");
        return;
    }
    
    // call dg_forthlocalsbar
    dg_forthlocalsbar(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - error doing LOCALS|\n");
        return;
    }
    
    // check final parse position
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    mybufferoffset = pBH->currentoffset;
    
    if (pBH->currentoffset != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - current interpret buffer's current offset not what was expected. Expected 16, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    // check that names were added to current compile wordlist
    mywordid = dg_finddefinwordlist (
        &BHarrayhead,
        mywordlist,
        (unsigned char*)"after",
        5);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - got error finding new word in locals wordlist\n");
        return;
    }
        
    if (DG_ENDOFWORDLIST == mywordid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - new word not added to locals wordlist\n");
        return;
    }
    
    // check usinglocalsflag and that localsdepth was nested
    usinglocalsflag = dg_getbufferuint32(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - got error getting the locals flag\n");
        return;
    }
    
    if (FORTH_FALSE == usinglocalsflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOCALS| success - using locals flag not set\n");
        return;
    }
    
    // be nice to finish the subroutine, call the code, and very depth and local value
    //  so I need a word that checks the depth.... what if I use dg_evaluatebuffer on a string?
    
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


