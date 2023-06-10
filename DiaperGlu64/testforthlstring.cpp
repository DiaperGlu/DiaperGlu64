// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.11.
//
//    DiaperGlu v5.11 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.11 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.11; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 10, 2023              //
// version 5.11               //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_forthdepthlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdepthlstring\n");

#ifdef DGLU_NO_DIAPER
        dg_printzerostring(&BHarrayhead, (unsigned char*)" ... no diaper detected\n");
#endif

#ifndef DGLU_NO_DIAPER

    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthdepthlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdepthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring underflow case - unable to initialize data stack\n");
        return;
    }

    // could check where stack is corrupt, with just under 1 element
    dg_forthdepthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdepthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting lstring stack depth case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthdepthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdepthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    
    dg_forthdepthlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - address not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthstartoffsetlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstartoffsetlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthstartoffsetlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstartoffsetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthstartoffsetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstartoffsetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting lstring start offset case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthstartoffsetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstartoffsetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    
    dg_forthstartoffsetlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - error count not 0 \n");
    } 

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - start offset not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthlengthlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlengthlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlengthlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthlengthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting lstring start offset case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthlengthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlengthlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    
    dg_forthlengthlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - length not what was expected\n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetslstringn ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetslstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetslstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError !=dg_forthgetslstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthgetslstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetslstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting plstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthgetslstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetslstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthgetslstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - error count not 0 \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - length not what was expected\n");
    }

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[stringbufid] );

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != ((UINT64)(pBH->pbuf)) + 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - address not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 i = 0;

    unsigned char sbuf[80];

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgetlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthgetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting plstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

    dg_forthgetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgetlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

    for (i=0; i<80; i++)
    {
        sbuf[i] = 'x';
    }
    
    dg_forthgetlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - error count not 0 \n");
    }

    if (sbuf[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[2] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[3] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[4] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthlstringtos ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 i = 0;

    unsigned char sbuf[80];

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlstringtos\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlstringtos(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlstringtosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthlstringtos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlstringtosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting plstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

    dg_forthlstringtos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlstringtosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_poplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

    for (i=0; i<80; i++)
    {
        sbuf[i] = 'x';
    }
    
    dg_forthlstringtos(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - error count not 0 \n");
    }

    if (sbuf[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[2] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[3] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
    }

    if (sbuf[4] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthstolstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 i = 0;

    unsigned char sbuf[80];

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstolstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthstolstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstolstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthstolstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstolstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting plstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthstolstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthstolstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);

    for (i=0; i<80; i++)
    {
        sbuf[i] = 'x';
    }

    sbuf[0] = 'z';
    sbuf[1] = 'q';
    
    dg_forthstolstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 1 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'q')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgrowlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgrowlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthgrowlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthgrowlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error growing lstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthgrowlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthgrowlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthgrowlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - end offset of 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthpicklstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthpicklstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthpicklstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthpicklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthpicklstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthpicklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring parameters missing case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error getting plstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthpicklstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthpicklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);

    
    dg_forthpicklstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 1 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 10) != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string 2 char 3 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthdroplstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdroplstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthdroplstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdroplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthdroplstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdroplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error dropping lstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthdroplstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdroplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_droplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }   

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthdroplstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string buffer not balanced after calculation,\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthdeletelstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdeletelstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthdeletelstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthdeletelstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error deleting lstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error dropping lstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthdeletelstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdeletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error deleting lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error deleting lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthdeletelstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"zq");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthdeletelstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 1 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 0 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 0 char 1 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 1 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 'q')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 1 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthinsertlstring ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinsertlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthinsertlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthinsertlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error inserting lstring case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error dropping lstring case - unable to initialize data stack\n");
        return;
    }

    //bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    //if (pError != dg_success)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
    //}

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

    dg_forthinsertlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthinsertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error inserting lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error inserting lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // length
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthinsertlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"zq");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // length
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // offset
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthinsertlstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - error count not 0 \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 1 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 2 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 24) != 14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 0 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 0 char 1 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 9) != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnotlstringn ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnotlstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthnotlstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthnotlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthnotlstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthnotlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthnotlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0xc7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x66)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0xf8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthnotlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
 if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x79)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xaa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xdc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x9e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
 if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotlstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthu8reverselstringn ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthu8reverselstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthu8reverselstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthu8reverselstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthu8reverselstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthu8reverselstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthu8reverselstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthu8reverselstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
 if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x23)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
 if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu8reverselstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthuleaddlstringntolstringn ()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 carryout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleaddlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthuleaddlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleaddlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthuleaddlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleaddlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleaddlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (carryout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - carry out not 0\n");
    }      

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0xBE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0xEE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x2A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleaddlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (carryout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - carry out not 0\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x6B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x9A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xAB)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x60)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleaddlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}

void testdg_forthuleadclstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 carryinout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleadclstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthuleadclstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleadclstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthuleadclstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleadclstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleadclstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (carryinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - carry out not 0\n");
    }      

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0xBE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0xEE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x2A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleadclstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (carryinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - carry out not 0\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x6C)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x9A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xAB)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x60)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulesbblstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
    UINT64 borrowinout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulesbblstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulesbblstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulesbblstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulesbblstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulesbblstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // borrowinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulesbblstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    borrowinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (borrowinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - carry out not 0\n");
    }      

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x4e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xbc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x1b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // borrowinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulesbblstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    borrowinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - got error popping the data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (borrowinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - carry out not 0\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleadclstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0xA0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x9B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulesbblstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthuleandlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleandlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthuleandlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleandlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthuleandlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleandlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleandlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleandlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x84)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x44)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthuleorlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleorlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthuleorlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthuleorlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthuleorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xbe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xdd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x27)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthuleorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0xe7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulexorlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulexorlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulexorlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulexorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulexorlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulexorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulexorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xbe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xcc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulexorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x63)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x9e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulenandlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulenandlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulenandlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulenandlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulenandlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulenandlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulenandlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xee)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xfc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulenandlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x7b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xbb)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x9e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulenorlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulenorlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulenorlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulenorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulenorlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulenorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulenorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x41)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x22)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xd8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x9e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulenorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x18)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xaa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x54)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulexnorlstringntolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulexnorlstringntolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulexnorlstringntolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulexnorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulexnorlstringntolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulexnorlstringntolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulexnorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x38)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x99)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x41)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x33)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 2 char 1 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xdb)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 2 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x9e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - string 2 char 3 not what was expected\n");
    }         

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\xE5\x44\x88\xFF");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthulexnorlstringntolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x9c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xee)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x54)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x61)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorlstringntolstringn success case 2 - data stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthlelshiftlstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 carryout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlelshiftlstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlelshiftlstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlelshiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthlelshiftlstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlelshiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlelshiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - carry out not what was expected\n");
    }  

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x70)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\xe1");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlelshiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 1 - carry out not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x0c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x46)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xc2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthulershiftlstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 carryout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulershiftlstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthulershiftlstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulershiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthulershiftlstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthulershiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthulershiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - carry out not what was expected\n");
    }  

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x9c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0xcc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x87\x55\x23\xe1");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthulershiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - carry out not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0xc3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xaa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x91)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x70)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftlstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthslershiftlstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 carryout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthslershiftlstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthslershiftlstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthslershiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthslershiftlstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthslershiftlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthslershiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - carry out not what was expected\n");
    }  

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x9c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0xcc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftlstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x87\x55\x23\xe1");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthslershiftlstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 1 - carry out not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0xc3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xaa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x91)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xf0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftlstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthlelshiftclstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 carryinout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlelshiftclstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlelshiftclstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlelshiftclstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthlelshiftclstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlelshiftclstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlelshiftclstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - carry out not what was expected\n");
    }  

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x70)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\xe1");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlelshiftclstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 1 - carry out not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x0d)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x46)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xc2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftclstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthlershiftclstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 carryinout = 0;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlershiftclstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthlershiftclstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlershiftclstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthlershiftclstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthlershiftclstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x86\x55\x23\x61");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlershiftclstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - carry out not what was expected\n");
    }  

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x9c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0xcc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string 2 char 0 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - string 2 char 1 not what was expected\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"\x38\x99\x07");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"\x87\x55\x23\xe1");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"\xE5\x44");   

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // carryinout
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    
    dg_forthlershiftclstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    carryinout = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - got error popping the datastack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 
    
    if (carryinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 1 - carry out not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - end offset of 2 not what was expected\n");
    }   
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 0 char 2 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0xc3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0xaa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 1 char 1 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x91)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 1 char 2 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0xF0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 1 char 3 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0xe5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - string 2 char 0 not what was expected\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftclstringn success case 2 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthu64starlstringnplustolstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthu64starlstringnplustolstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthu64starlstringnplustolstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthu64starlstringnplustolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthu64starlstringnplustolstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthu64starlstringnplustolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 8, (unsigned char*)"\x03\x00\x00\x00\x00\x00\x00\x00");
    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 8, (unsigned char*)"\x00\x00\x00\x00\x00\x00\x00\x00");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // u
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthu64starlstringnplustolstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - end offset of 0 not what was expected\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - end offset of 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 4 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 5 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 6 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 1 char 7 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 2 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 9) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - string 2 char 1 not what was expected\n");
    }               

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthu64starlstringnplustolstringn success case 1 - data  stack not balanced after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);   
}


void testdg_forthtoslashulelstringn()
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

    UINT64 offsetbufid = 0;
    UINT64 stringbufid = 0;
 
    UINT64 remainder = 99;   

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtoslashulelstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthtoslashulelstringn(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtoslashulelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthtoslashulelstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtoslashulelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

    // success case 1 no remainder
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 8, (unsigned char*)"\x0f\x00\x00\x00\x00\x00\x00\x00");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // u
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthtoslashulelstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    remainder = dg_popdatastack(&BHarrayhead);   
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - error count not 0 from popping data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (remainder != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - got wrong remainder\n");
    }   
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - end offset of 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 4 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 5 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 6 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 1 no remainder - string 1 char 7 not what was expected\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
 
    // success case 2 remainder
    dg_initbuffers(&BHarrayhead);

    offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - unable to initialize test buffer\n");
        return;
    }

    stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - unable to initialize test buffer\n");
        return;
    }

    dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 8, (unsigned char*)"\x11\x00\x00\x00\x00\x00\x00\x00");

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // u
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);   
    
    dg_forthtoslashulelstringn(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    remainder = dg_popdatastack(&BHarrayhead);   
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - error count not 0 from popping data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    if (remainder != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - got wrong remainder\n");
    }   
 
    if (dg_getbufferlength(&BHarrayhead, stringbufid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string buffer not balanced after calculation\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - lstring stack not balanced after calculation\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - end offset of 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 0 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 1) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 1 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 2 not what was expected\n");
    }         

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 3 not what was expected\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 4 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 5 not what was expected\n");
    } 
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 6) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 6 not what was expected\n");
    }
 
    if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtoslashulelstringn success case 2 remainder - string 1 char 7 not what was expected\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);      
}


/*
void testdg_forthcscanlstring ()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcscanlstring\n");

    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - unable to initialize error stack\n");
        return;
    }

    dg_forthcscanlstring(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcscanlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    // underflow case
    dg_initbuffers(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring underflow case - unable to initialize data stack\n");
        return;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

    // could check where stack is corrupt, with just under 1 element
    dg_forthcscanlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcscanlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    
    // error cscanning lstring case

}
*/

// dg_forthscanlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing scan case
//  success case

// dg_forthshortenlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing shorten case
//  success case

// dg_forthnewlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing new case
//  success case

// dg_forthrolllstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing roll case
//  success case

// dg_forthminusrolllstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing minusroll case
//  success case

// dg_forthdeleteinlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing deletein case
//  success case

// dg_forthinsertinlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing insertin case
//  success case

// dg_forthcatlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_catlstringn case
//  success case

// dg_forthcopystolstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copystolstringn case
//  success case

// dg_forthcopysfromlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copysfromlstringn case
//  success case

// dg_forthsetlengthlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_setlengthlstringn case
//  success case

// dg_forthcopystoreplacelstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copystoreplacelstringn case
//  success case

// dg_forthcopylstringntoreplacelstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copylstringntoreplacelstringn case
//  success case


