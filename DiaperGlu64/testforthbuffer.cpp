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

void testdg_forthocfetch ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthocfetch\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthocfetch(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthocfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting byte from buffer case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting byte from buffer case case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthocfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting byte from buffer case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting byte from buffer case case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case - unable to initialize test buffer\n");
    }

    dg_pushbufferbyte(&BHarrayhead, bufid, 0x93);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthocfetch(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 1 - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x93)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushbufferbyte(&BHarrayhead, bufid, 0x93);
    dg_pushbufferbyte(&BHarrayhead, bufid, 0x76);

    dg_forthocfetch(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 2 - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x76)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 2 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthofetch ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthofetch\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthofetch(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthofetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthofetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthofetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting buffer from byte case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch error getting buffer from byte case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthofetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthofetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch error getting buffer from byte case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch error getting buffer from byte case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x934456611223344);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthofetch(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch dg_success case 1 - error count not 0\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x934456611223344)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch dg_success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch dg_success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x93);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x769834944665577);

    dg_forthofetch(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch success case 2 - error count not 0\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x769834944665577)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch success case 2 - got wrong answer, expected 0x769834944665577, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthofetch success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthostonewstring ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    unsigned char* plstring = NULL;
    UINT64 lstringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthostonewstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthostonewstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostonewstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to data stack case - got wrong error on top ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to data stack case - got wrong error 1 below top ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthostonewstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostonewstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring underflow case - got wrong error on top ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring underflow case - got wrong error 1 below top ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting pointer to buffersegment case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to buffersegment case - unable to initialize test buffer\n");
    }
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // buffer segment goes off end

    dg_forthostonewstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostonewstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to buffersegment case - got wrong error on top, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error getting pointer to buffersegment case - got wrong error 1 below top, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing to stringoffset case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error pushing to stringoffset cas - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x31323334);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); 

    dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    dg_forthostonewstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostonewstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error pushing to stringoffset cas - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring error pushing to stringoffset cas - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x3132333435363738);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthostonewstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 1 - error count not 0\n");
    }

    plstring = dg_getplstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 0, &lstringlength);

    if (plstring == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 1 - unable to get pointer to lstring\n");
        return;
    }

    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 1 - length of string pushed not 4\n");
    }

    if (*((UINT64*)(plstring)) != 0x3132333435363738)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 1 - string not pushed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x3132333435373638);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9780987099989796);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthostonewstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2a - error count not 0\n");
    }

    plstring = dg_getplstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 0, &lstringlength);

    if (plstring == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2a - unable to get pointer to lstring\n");
        return;
    }

    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2a - length of string pushed not 4\n");
    }

    if (*((UINT64*)(plstring)) != 0x3132333435373638)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2a - string not pushed\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthostonewstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2b - error count not 0\n");
    }

    plstring = dg_getplstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 1, &lstringlength);

    if (plstring == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2b - unable to get pointer to lstring\n");
        return;
    }

    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2b - length of string pushed not 4\n");
    }

    if (*((UINT64*)(plstring)) != 0x9780987099989796)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2b - string not pushed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostonewstring success case 2b - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

        
}


void testdg_forthocstore ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthocstore\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthocstore(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);


    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthocstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error putting byte to buffer case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error putting byte to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthocstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthocstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error putting byte to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error putting byte to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 1 - unable to initialize test buffer\n");
    }

    dg_growbuffer(&BHarrayhead, bufid, 1, &pError, false);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthocstore(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 1 - error count not 0");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 0) != 0x29)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 1 - wrong number stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case - unable to initialize test buffer\n");
    }

    dg_growbuffer(&BHarrayhead, bufid, 2, &pError, false);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x83);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthocstore(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 2 - error count not 0");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 1) != 0x83)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 2 - wrong number stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthostore ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthostore\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocstore error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthostore(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);


    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthostore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error putting dword to buffer case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore error putting byte to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthostore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthostorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore error putting byte to buffer cas1 - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore error putting byte to buffer cas1 - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 1 - unable to initialize test buffer\n");
    }

    dg_growbuffer(&BHarrayhead, bufid, 8, &pError, false);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x292398439383736);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthostore(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 1 - error count not 0");
    }

    if (dg_getbufferuint64(&BHarrayhead, bufid, 0) != 0x292398439383736)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 1 - wrong number stored \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case - unable to initialize test buffer\n");
    }

    dg_growbuffer(&BHarrayhead, bufid, 12, &pError, false);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8323981187868584);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthostore(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 2 - error count not 0");
    }

    if (dg_getbufferuint64(&BHarrayhead, bufid, 4) != 0x8323981187868584)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 2 - wrong number stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthostore success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthctobuf ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthctobuf\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthctobuf(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthctobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthctobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthctobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing byte to buffer case
    dg_initbuffers(&BHarrayhead);

    bufid = 999;

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthctobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthctobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf error pushing byte to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf error pushing byte to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthctobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 1 - error count not 0");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 0) != 0x29)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 1 - wrong number stored \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x83);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthctobuf(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x92);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthctobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 2 - error count not 0");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 1) != 0x92)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 2 - wrong number stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctobuf success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthtobuf ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtobuf\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthtobuf(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing dword to buffer case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x29);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 999);

    dg_forthtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf error pushing dword to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf error pushing dword to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x2923984156585755);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthtobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 1 - error count not 0\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, bufid, 0) != 0x2923984156585755)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 1 - wrong number stored \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 1 - didn't get expected length\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8323989918171615);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthtobuf(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x2304932119897959);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthtobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 2 - error count not 0\n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 2 - didn't get expected length\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, bufid, 8) != 0x2304932119897959)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 2 - wrong number stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtobuf success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthstringtobuf ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringtobuf\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthstringtobuf(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthstringtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting string stack depth case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting string stack depth case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    dg_forthstringtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting string stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting string stack depth case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // string stack underflow case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf string stack underflow case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthstringtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_stringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting pointer to string case
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to string case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"hello");

    dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

    dg_forthstringtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error getting pointer to string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing to buffer case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29387);

    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"hello");
    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"everyone");
    
    dg_forthstringtobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstringtobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error pushing to stringoffset cas - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf error pushing to stringoffset cas - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // if dg_getplstring worked, I don't know how to get an error dropping the lstring

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case - unable to initialize test buffer\n");
    }

    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"hello");
    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"everyone");

    dg_pushbufferbyte(&BHarrayhead, bufid, 0x41);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthstringtobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - error count not 0\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - string stack depth not 1 after test\n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - buffer length not what was expected after test\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 0) != 0x41)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - buffer corrupted\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 1) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - start of string not copied\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 2) != 'v')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - 2nd letter of string not copied\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, bufid, 8) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - 7th letter of string not copied\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtobuf success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthbuftoc ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthbuftoc\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthocfetch error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthbuftoc(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftocname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthbuftoc(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftocname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error popping byte from buffer
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc error popping byte from buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthbuftoc(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftocname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc error popping byte from buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc error popping byte from buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferbyte(&BHarrayhead, bufid, 0x93);
    dg_pushbufferbyte(&BHarrayhead, bufid, 0x87);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthbuftoc(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc success case 1 - error count not 0\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x87)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftoc success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthbufto ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthbufto\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthbufto(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthbufto(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error popping dword from buffer
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error popping dword from buffer case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthbufto(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error popping dword from buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto error popping dword from buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x932398);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x8723475390088776);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthbufto(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case 1 - error count not 0\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x8723475390088776)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthbuftostring ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    unsigned char* plstring = 0;
    UINT64 lstringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthbuftostring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthbuftostring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftostringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthbuftostring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftostringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting buffer length
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error popping dword from buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3249);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthbuftostring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftostringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error getting buffer length case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error getting buffer length case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

/*
    // error buffer underflow
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error buffer underflow case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

    dg_pushbufferuint64(&BHarrayhead, bufid, 23984);

    dg_forthbuftostring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftostringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error buffer underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error buffer underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
*/
    // if get buffer length worked, dont know how you get an error getting a pointer to the segment

    // error pushing lstring
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error pushing lstring case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_pushbufferuint64(&BHarrayhead, bufid, 23984);

    dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

    dg_forthbuftostring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftostringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error pushing lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring error pushing lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // if get buffer length worked, don't know how to get an error shrinking buffer
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x932398);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x8723470987654321);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthbuftostring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - error count not 0");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - data  stack not empty after calculation\n");
    }

    plstring = dg_getplstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 0, &lstringlength);

    // if ( *((UINT64*)(plstring)) != 0x932398 )
    // {
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - lstring not have correct data a\n");
    // }

    if ( *((UINT64*)(plstring)) != 0x8723470987654321 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - lstring not have correct data b\n");
    }

    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 1 - lstring length not correct\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x932398);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x8723475198764321);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"hello");

    dg_forthbuftostring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - error count not 0");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - data  stack not empty after calculation\n");
    }

    plstring = dg_getplstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 1, &lstringlength);

    // if ( *((UINT64*)(plstring)) != 0x932398 )
    // {
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - lstring not have correct data a\n");
    // }

    if ( *((UINT64*)(plstring)) != 0x8723475198764321 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - lstring not have correct data b\n");
    }

    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftostring success case 2 - lstring length not correct\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

}


void testdg_forthosstore ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthosstore\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthosstore(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthosstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting buffer segment
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error popping dword from buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

    dg_forthosstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosstorename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error popping dword from buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore error popping dword from buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbufto success case - unable to initialize test buffer\n");
    }

    testint = 0;

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x2398483);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9ABCDEF012345678);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

    dg_forthosstore(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore success case 1 - error count not 0\n");
    }

    if (testint != 0x9ABCDEF012345678)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosstore success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthosfetch()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthosfetch\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthosfetch(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthosfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error putting buffer segment
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_forthosfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthosfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch success case - unable to initialize test buffer\n");
    }

    testint = 0x8877334455667788;

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x2398483);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9ABCDEF0);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthosfetch(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch success case 1 - error count not 0 \n");
    }

    testint = dg_getbufferuint64(&BHarrayhead, bufid, 16);

    if (testint != 0x8877334455667788)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthstobuf()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstobuf\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthstobuf(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthstobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error putting buffer segment
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);

    dg_forthstobuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstobufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf error putting buffer segment case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf error putting buffer segment case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf success case - unable to initialize test buffer\n");
    }

    testint = 0x8877334481828384;

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x2398483);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9ABCDEF011223344);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_forthstobuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf success case 1 - error count not 0 \n");
    }

    testint = dg_getbufferuint64(&BHarrayhead, bufid, 24);

    if (testint != 0x8877334481828384)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstobuf success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthbuftos()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthbuftos\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthbuftos(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39498);

    // could check where stack is corrupt, with just under 2 elements

    dg_forthbuftos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error putting buffer segment
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4); 
    
    dg_forthbuftos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthbuftosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos error putting buffer segment case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos error putting buffer segment case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos dg_success case - unable to initialize test buffer\n");
    }

    testint = 0x8877334411446688;

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x2398483);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9ABCDEF013579642);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    
    dg_forthbuftos(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos success case 1 - error count not 0 \n");
    }

    if (testint != 0x9ABCDEF013579642)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbuftos success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthlengthbuf ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlengthbuf\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlengthbuf(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthbufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthlengthbuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthbufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting bufferlength
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthosfetch error putting buffer segment case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984); 

    dg_forthlengthbuf(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthbufname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf error getting bufferlength case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf error getting bufferlength case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf success case - unable to initialize test buffer\n");
        return;
    }

    testint = 0x88773344;

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x2398483);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9ABCDEF0);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthlengthbuf(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf success case 1 - buffer bufid not balanced after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthbuf success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthgetsbufferhandlearrayhead ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetsbufferhandlearrayhead\n");
#ifndef DGLU_NO_DIAPER
    // error pushing to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead error pushing to datastack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetsbufferhandlearrayhead(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbufferhandlearrayheadname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead error pushing to datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead error pushing to datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);
    
    dg_forthgetsbufferhandlearrayhead(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != sizeof(Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead success case 1 - got wrong answer \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)&BHarrayhead)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandlearrayhead success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthgetsbufferhandle ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetsbufferhandle\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetsbufferhandle(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetsbufferhandle(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error getting pointer to the buffer handle
    dg_initbuffers(&BHarrayhead);

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferhandle error putting buffer segment case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984); 

    dg_forthgetsbufferhandle(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error getting pointer to the buffer handle case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error getting pointer to the buffer handle case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing to the data stack
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error pushing to the data stack - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
    
    pBH->size = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;

    dg_forthgetsbufferhandle(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if ( pError != dg_forthgetsbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error pushing to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if ( pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle error pushing to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthgetsbufferhandle(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != sizeof(Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle success case 1 - got wrong answer \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != (UINT64)pBH)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbufferhandle success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthgetoarrayelement ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetoarrayelement\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetoarrayelement(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetoarrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetoarrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetoarrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid + 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetoarrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetoarrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error offset off end
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error offset off end case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 234923);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthgetoarrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetoarrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error offset off end case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement error offset off end case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 234923);
    dg_pushbufferuint64(&BHarrayhead, bufid, 9823415509876532);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    
    dg_forthgetoarrayelement(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetoarrayelement success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetparrayelement ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;
    UINT64* plength = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetparrayelement\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetparrayelement(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetparrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 23984);

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetparrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetparrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid + 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetparrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetparrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error offset off end
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error offset off end case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 234923);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_forthgetparrayelement(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetparrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error offset off end case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement error offset off end case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    
    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 234923);
    dg_pushbufferuint64(&BHarrayhead, bufid, 982341);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    
    dg_forthgetparrayelement(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)(dg_getpbuffer(&BHarrayhead, bufid, &plength) + 8))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetparrayelement success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetbuffersize ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetbuffersize\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetbuffersize(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffersizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetbuffersize(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffersizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetbuffersize(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffersizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 2*dg_getpagesize(), &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthgetbuffersize(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != dg_getpagesize() )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetbuffermaxsize ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetbuffermaxsize\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetbuffermaxsize(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffermaxsizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetbuffermaxsize(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffermaxsizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetbuffermaxsize(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffermaxsizename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 2*dg_getpagesize(), &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthgetbuffermaxsize(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2*dg_getpagesize() )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffermaxsize success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetbuffergrowby ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetbuffergrowby\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetbuffergrowby(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffergrowbyname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetbuffergrowby(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffergrowbyname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetbuffergrowby(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffergrowbyname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 2*dg_getpagesize(), &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthgetbuffergrowby(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != dg_getpagesize() )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetbuffercurrentoffset ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;
    
    Bufferhandle* pBH = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetbuffercurrentoffset\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffergrowby error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetbuffercurrentoffset(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset success case - unable to initialize test buffer\n");
        return;
    }
    
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234);
    
    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );
    pBH->currentoffset = 5;

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthgetbuffercurrentoffset(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 5 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffercurrentoffset success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthputbuffercurrentoffset ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthputbuffercurrentoffset\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthputbuffercurrentoffset(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthputbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2938);

    // could check where stack is corrupt, with just under 1 elements

    dg_forthputbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthputbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to buffer handle case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthputbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthputbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to buffer handle case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset error getting pointer to buffer handle case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23984);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthputbuffercurrentoffset(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 1 - error count not 0 \n");
    }

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (pBH->currentoffset != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 1 - current offset not stored\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23984);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid); 
    
    dg_forthputbuffercurrentoffset(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 2 - error count not 0 \n");
    }

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (pBH->currentoffset != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 2 - current offset not set to buffer length\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputbuffercurrentoffset success case 2 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetpbufferlength ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetpbufferlength\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetpbufferlength(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetpbufferlength(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetpbufferlength(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, bufid, 2398);
    
    dg_forthgetpbufferlength(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );
    
    if (testint != (UINT64)&(pBH->nextunusedbyte) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength success case 1 - got wrong answer \n");
    }

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength success case 1 - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferlength success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetpbuffercurrentoffset ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetpbuffercurrentoffset\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetpbuffercurrentoffset(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 elements

    dg_forthgetpbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer handle case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 3 elements

    dg_forthgetpbuffercurrentoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffercurrentoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, bufid, 2398);
    
    dg_forthgetpbuffercurrentoffset(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );
    
    if (testint != (UINT64)&(pBH->currentoffset) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset success case 1 - got wrong answer \n");
    }

    if (pBH->currentoffset != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset success case 1 - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffercurrentoffset success case 1 - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthinsertinbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinsertinbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthinsertinbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 3 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthinsertinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error inserting in buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error inserting in buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_forthinsertinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error inserting in buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer error inserting in buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef088776655);
    
    dg_forthinsertinbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, bufid);
    
    if (testint != 0x9abcdef088776655)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case 1 - got wrong answer \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, bufid);

    if (testint != 0x1234567898765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthdeleteinbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdeleteinbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthdeleteinbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 3 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthdeleteinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error deleting in buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error deleting in buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_forthdeleteinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error deleting in buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer error deleting in buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef088776655);
    
    dg_forthdeleteinbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, bufid);
    
    if (testint != 0x9abcdef088776655)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer success case 1 - got wrong answer \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthreplaceinbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthreplaceinbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthreplaceinbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthreplaceinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 3 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthreplaceinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthreplaceinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error replacing in buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error inserting in buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"test string");
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_forthreplaceinbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthreplaceinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error inserting in buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_replacebuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer error inserting in buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"eb"); // 0x65 0x62
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef088776655);
    
    dg_forthreplaceinbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - error count not 0 \n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        bufid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - got error getting pointer to buffer \n");
    }
    else
    {
        if (pbuffer[0] != 0x32)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[0] incorrect \n");
        }
        
        if (pbuffer[1] != 0x54)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[1] incorrect \n");
        }
        
        if (pbuffer[2] != 0x76)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[2] incorrect \n");
        }
        
        if (pbuffer[3] != 0x98)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[3] incorrect \n");
        }
        
        if (pbuffer[4] != 0x65)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[4] incorrect \n");
        }
        
        if (pbuffer[5] != 0x62)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[5] incorrect \n");
        }
        
        if (pbuffer[6] != 0x12)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[6] incorrect \n");
        }
        
        if (pbuffer[7] != 0x55)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - pbuffer[7] incorrect \n");
        }
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreplaceinbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthinsertsintobuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinsertsintobuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthinsertsintobuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertsintobuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 3 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthinsertsintobuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertsintobuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error inserting s into buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error inserting s into buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"test string");
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    

    dg_forthinsertsintobuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertsintobuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error inserting in buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_replacebuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer error inserting in buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"eb"); // 0x65 0x62
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef088776655);
    
    dg_forthinsertsintobuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - error count not 0 \n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        bufid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - got error getting pointer to buffer \n");
    }
    else
    {
        if (pbuffer[0] != 0x32)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[0] incorrect \n");
        }
        
        if (pbuffer[1] != 0x54)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[1] incorrect \n");
        }
        
        if (pbuffer[2] != 0x76)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[2] incorrect \n");
        }
        
        if (pbuffer[3] != 0x98)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[3] incorrect \n");
        }
        
        if (pbuffer[4] != 0x65)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[4] incorrect \n");
        }
        
        if (pbuffer[5] != 0x62)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[5] incorrect \n");
        }
        
        if (pbuffer[6] != 0x78)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[6] incorrect \n");
        }
        
        if (pbuffer[7] != 0x56)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - pbuffer[7] incorrect \n");
        }
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 18)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertsintobuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgrowbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgrowbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgrowbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthgrowbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error growing buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error growing buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    dg_forthgrowbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error growing buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer error growing buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef011223344);
    
    dg_forthgrowbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthshrinkbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthshrinkbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthshrinkbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthshrinkbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthshrinkbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthshrinkbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error shrinking buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error shrinking buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    dg_forthshrinkbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthshrinkbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error shrinking buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_shrinkbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error shrinking buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x1234567898765432);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef011223344);
    
    dg_forthshrinkbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, bufid);

    if (testint != 0x1234567898765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer success case 1 - expected data in buffer to not change\n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthemptybuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthemptybuffer\n");
#ifndef DGLU_NO_DIAPER
    // error popping datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthemptybuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthemptybuffername)
    {
                dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer error getting pointer to data stack case - expected name error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    //if (pError != dg_forthemptybufferpopdatastackerror)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer error getting pointer to data stack case - got wrong error \n");
    //}
    
    // need to get true error from bottom

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // error clearing buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer error clearing buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    dg_forthemptybuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthemptybuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshrinkbuffer error clearing buffer case- expected name error on top \n");
    }

    // need to test for true error on bottome

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    dg_pushbufferuint64(&BHarrayhead, bufid, 0x12345678);
    dg_pushbufferuint64(&BHarrayhead, bufid, 0x9abcdef0);
    
    dg_forthemptybuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer success case 1 - buffer not balanced after calculation\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemptybuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthnewbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnewbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthnewbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthnewbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthnewbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthnewbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error making new buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error making new buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    dg_forthnewbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthnewbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error making new buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_newbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer error making new buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_getpagesize());
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2*dg_getpagesize());
    
    dg_forthnewbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - error count not 0 \n");
    }

    bufid = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (pBH->growby != dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - growby not what was expected\n");
    }

    if (pBH->maxsize != 2*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - maxsize not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthfreebuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthfreebuffer\n");
#ifndef DGLU_NO_DIAPER
    // error popping datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthfreebuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthfreebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer error getting popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer error getting popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // tried to free dglu script engine buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer tried to free a dglu script engine buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_lastdiaperglubufferid);

    dg_forthfreebuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthfreebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer tried to free a dglu buffer case- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfordglubuffer)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer tried to free a dglu buffer case- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer success case - unable to initialize test buffer\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthfreebuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer success case 1 - error count not 0 \n");
    }

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (pBH->pbuf != (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer success case 1 - buffer not freed\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthfreebuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetpbufferoffset ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetpbufferoffset\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetpbufferoffset(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 92834);

    dg_forthgetpbufferoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer offset case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error making new buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

    dg_forthgetpbufferoffset(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbufferoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error getting pointer to buffer offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbufferoffset error getting pointer to buffer offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23947);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthgetpbufferoffset(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - pointer not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetpbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetpbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetpbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 element
    dg_forthgetpbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

    dg_forthgetpbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 34098);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;


    dg_forthgetpbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23947);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthgetpbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != (UINT64)&(pBH->nextunusedbyte) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - plength not what was expected\n");
    }

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - length not what was expected\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != ((UINT64)(pBH->pbuf)) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - pointer not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetsbuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetsbuffer\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetsbuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 element
    dg_forthgetsbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

    dg_forthgetsbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 34098);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;


    dg_forthgetsbuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetsbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer error getting pointer to buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    


    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23947);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    
    dg_forthgetsbuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != 8 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer success case 1 - returned length not what was expected\n");
    }

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer success case 1 - buffer length not what was expected\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)(pBH->pbuf))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsbuffer success case 1 - buffer pointer not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffer success case 1 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetpbuffersegment ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetpbuffersegment\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetpbuffersegment(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

    // could check where stack is corrupt, with just under 1 element
    dg_forthgetpbuffersegment(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetbuffersize error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

    dg_forthgetpbuffersegment(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment error getting pointer to buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment success case 1 - unable to initialize test buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 23947);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, bufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    
    dg_forthgetpbuffersegment(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 1 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetpbuffersegment success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthmaxusedbuffers ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;

    const char* pError = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthmaxusedbuffers\n");

    // success case 1
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - unable to initialize error stack\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - unable to make data stack\n");
        return;
    }
    
    dg_forthmaxusedbuffers (&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - got wrong number of max used buffers 1st time\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - unable to make buffer\n");
        return;
    }
    
    dg_forthmaxusedbuffers (&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - got wrong number of max used buffers 2nd time\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - unable to make buffer\n");
        return;
    }
    
    dg_forthmaxusedbuffers (&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - got wrong number of max used buffers 3rd time\n");
        return;
    }
    
    dg_freebuffer(&BHarrayhead, 2);
    
    dg_forthmaxusedbuffers (&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthmaxusedbuffers success case - got wrong number of max used buffers after free\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthinusebuffers ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;

    const char* pError = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinusebuffers\n");

    // success case 1
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - unable to initialize error stack\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - unable to make data stack\n");
        return;
    }
    
    dg_forthinusebuffers(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - got wrong number of in use buffers 1st time\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - unable to buffer\n");
        return;
    }
    
    dg_forthinusebuffers(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - got wrong number of in use buffers 2nd time\n");
        return;
    }
    
    dg_freebuffer(&BHarrayhead, 2);
    
    dg_forthinusebuffers(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebuffers success case - got wrong number of max used buffers after free\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthinusebytes ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;

    const char* pError = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinusebytes\n");

    // success case 1
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - unable to initialize error stack\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - unable to make data stack\n");
        return;
    }
    
    dg_forthinusebytes(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - got wrong number of in use bytes 1st time\n");
        return;
    }
    
    dg_newbuffer(&BHarrayhead, 0x1000, 0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - unable to buffer\n");
        return;
    }
    
    dg_forthinusebytes(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - got wrong number of in use bytes 2nd time\n");
        return;
    }
    
    dg_growbuffer (
        &BHarrayhead,
        2,
        201,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - unable to grow buffer\n");
        return;
    }
    
    dg_forthinusebytes(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 201)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinusebytes success case - got wrong number of bytes after grow\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // should check case where stuff pushed into buffer isn't a multiple of element size
}

// need test dg_forthlinecomment

void testdg_forthparse ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthparse\n");
#ifndef DGLU_NO_DIAPER
    // error popping end character case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error popping end character case - unable to initialize error stack\n");
        return;
    }

    dg_forthparse(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error popping end character case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error popping end character case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error popping end character case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // error getting current input buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting current input buffer case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    // could check where stack is corrupt, with just under 1 element
    dg_forthparse(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to current input buffer case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 23984);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    dg_forthparse(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;

    dg_forthparse(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 13, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');
    
    dg_forthparse(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 9 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 1 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if ( testint != ((UINT64)(pBH->pbuf)) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 13, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparse(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 6 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 3
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 16, (unsigned char*)"hi there - you\num");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparse(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 11 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - length not what was expected 11, got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 3 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // dg_success case 4
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 13, (unsigned char*)"hi there - you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparse(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 10 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - length not what was expected 11, got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse success case 4 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthparsebuffer ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthparsebuffer\n");
#ifndef DGLU_NO_DIAPER
    // error popping end character case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error popping end character case - unable to initialize error stack\n");
        return;
    }

    dg_forthparsebuffer(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error popping end character case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error popping end character case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error popping end character case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // error getting current input buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting current input buffer case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    // could check where stack is corrupt, with just under 1 element
    dg_forthparsebuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsemultilinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to current input buffer case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 23984);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting pointer to current input buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    dg_forthparsebuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsemultilinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;

    dg_forthparsebuffer(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 13, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');
    
    dg_forthparsebuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 9 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 1 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if ( testint != ((UINT64)(pBH->pbuf)) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 13, (unsigned char*)"hi there ) you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsebuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 6 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // dg_success case 3
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 17, (unsigned char*)"hi there - you\num");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsebuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 14 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - length not what was expected, expected 14 got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // dg_success case 4
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there - you");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, ')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsebuffer(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 4 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 11 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 4 - length not what was expected 11, expected got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 4 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsebuffer success case 4 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthparseword ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthparseword\n");
#ifndef DGLU_NO_DIAPER
    
    // error getting current input buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 element
    dg_forthparseword(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to current input buffer case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 23984);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error getting pointer to current input buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - unable to initialize test buffer\n");
    //}

    dg_forthparseword(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // no name error
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword no name error - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword no name error - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    //dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");


    dg_forthparseword(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword no name error - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_nowordfounderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword no name error - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");


    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;

    dg_forthparseword(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparsewordname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi there ) you");
    
    dg_forthparseword(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 1 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 1 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi there ) you");

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparseword(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 5 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 3
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hiathereb-cyou");

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparseword(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 11 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - length not what was expected, got \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case 3 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}

void testdg_forthparsewords ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthparsewords\n");

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseword success case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi there)you");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)')');
    
    dg_forthparsewords(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 1 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 1 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 1 - address not what was expected\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != FORTH_FALSE )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 1 - flag not what was expected \n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi there)you");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsewords(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 5 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - length not what was expected, expected 5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - address not what was expected\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != FORTH_TRUE )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - flag not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 3
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hiathereb-cyou");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsewords(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 11 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - length not what was expected, got \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - address not what was expected\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != FORTH_TRUE )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - flag not what was expected, got \n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 3 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 4
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 4, (unsigned char*)" hi ");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)')');

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparsewords(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - length not what was expected, got \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - address not what was expected\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != FORTH_TRUE )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - flag not what was expected, got \n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparsewords success case 4 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthparseline ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    BHarrayhead.maxsize = BHarraymaxsize;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.pbuf = (void*)-1;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount = 0;
    BHarrayhead.id = BHarrayheadid;

    Bufferhandle* pBH = NULL;

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthparseline\n");
#ifndef DGLU_NO_DIAPER
    
    // error getting current input buffer case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 element
    dg_forthparseline(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparselinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parselinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    // error getting pointer to current input buffer case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 23984);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error getting pointer to current input buffer case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error getting pointer to current input buffer case - unable to initialize test buffer\n");
    //}

    dg_forthparseline(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparselinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_parselinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // empty line case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline empty line case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline empty line case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    //dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");


    dg_forthparseline(&BHarrayhead);

    if (0 != dg_geterrorcount(&BHarrayhead))
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline empty line case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    


    // error pushing to data stack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error pushing to data stack case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)"hi there ) you");


    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );

    pBH->size = pBH->nextunusedbyte;
    pBH->growby = pBH->nextunusedbyte;
    pBH->maxsize = pBH->nextunusedbyte;

    dg_forthparseline(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthparselinename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi\nthere ) you");
    
    dg_forthparseline(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 1 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hi there )\nyou");

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparseline(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 8 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - length not what was expected \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    // success case 3
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - unable to initialize data stack\n");
        return;
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 14, (unsigned char*)" hiathereb-cyou");

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    pBH->currentoffset = 3;
    
    dg_forthparseword(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 11 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - length not what was expected, got \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[bufid] );

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparseline success case 3 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_forthtocurrent ()
{
    Bufferhandle BHarrayhead;
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtocurrent\n");

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case - unable to initialize buffers and variables\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 0x123);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case - got error pushing 1st test number to data stack\n");
        return;
    }
    
    dg_forthtocurrent(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case 1 - error count not 0 after doing 1st >CURRENT\n");
    }
    
    dg_pushdatastack(&BHarrayhead, 0x567);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case - got error pushing 2nd test number to data stack\n");
        return;
    }
    
    dg_forthtocurrent(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case 1 - error count not 0 after doing 2nd >CURRENT\n");
    }

    x = dg_popbufferuint64(&BHarrayhead, DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);

    if (x != 0x123)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case 1 - length not what was expected \n");
    }

    x = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (x != 0x567 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtocurrent success case 1 - current new word wordlist not what was expected\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthcurrentfrom ()
{
    Bufferhandle BHarrayhead;
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcurrentfrom\n");

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case - unable to initialize buffers and variables\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 0x123);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case - got error pushing 1st test number to data stack\n");
        return;
    }
    
    dg_forthtocurrent(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - error count not 0 after doing 1st >CURRENT\n");
    }
    
    dg_pushdatastack(&BHarrayhead, 0x567);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case - got error pushing 2nd test number to data stack\n");
        return;
    }
    
    dg_forthtocurrent(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - error count not 0 after doing 2nd >CURRENT\n");
    }
    
    dg_forthcurrentfrom(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - error doing 1st current from\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x567)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - 1st current from value wrong \n");
    }

    dg_forthcurrentfrom(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - error doing 2nd current from\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x123)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcurrentfrom success case 1 - 2nd current from value wrong \n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthbrackettoorderconstant ()
{
    Bufferhandle BHarrayhead;
    UINT64 x;
    UINT64 bufid;
    UINT64 wordid;
    UINT64 wordlistid;
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthbrackettoorderconstant\n");

    // success case 1
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead); // needed to make new wordlists

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - unable to initialize buffers and variables\n");
        return;
    }
    
    wordlistid = dg_newwordlist (
        &BHarrayhead,
        0); // hlist 0 is parent for wordlists
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error making a new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        wordlistid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error setting current new word wordlist\n");
        return;
    }
    
    bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthparse error pushing to data stack case - unable to initialize test buffer\n");
    }

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, bufid);

    dg_pushbuffersegment(&BHarrayhead, bufid, 3, (unsigned char*)"moo ");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error setting up current interpret buffer\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 0x125);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error pushing number to datastack\n");
        return;
    }
    
    dg_forthbrackettoorderconstant(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error doing dg_forthbrackettoorderconstant\n");
        return;
    }
    
    wordid = dg_getlatestdefinition (
        &BHarrayhead,
        wordlistid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant success case - error getting latest definition\n");
        return;
    }
    
    dg_executedefinition (
        &BHarrayhead,
        wordid);   
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant dg_success case - got an error executing the new definition\n" );
	}
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant dg_success case - got an error popping top value from search order stack\n" );
	}
 
    if (x != 0x125)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthbrackettoorderconstant dg_success case - got wrong 1st wordlist from dg_currentfrom, expected 0x125, got " );
        dg_writestdoutuint64tohex(
            &BHarrayhead,
            x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n" );
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

