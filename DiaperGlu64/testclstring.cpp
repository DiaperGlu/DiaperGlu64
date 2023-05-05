// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.10.
//
//    DiaperGlu v5.10 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.10 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.10; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// May 5, 2023                //
// version 5.10               //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_movebytesskipdestination()
{
	unsigned char buf1[27] = "abcdefghijklmnopqrstuvwxyz";
    unsigned char buf2[27] = "                          ";
    
    unsigned char* pbuf1 = buf1;
    unsigned char* pbuf2 = buf2;

    Bufferhandle BHarrayhead;

    const char* perror;

    BHarrayhead.pisapiecb = (void*)-1;
    // test won't work in isapi mode unless this gets set correctly

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_movebytesskipdestination\n");

	// success case no overlap source < destination
    
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2, pbuf2 + 2, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - changed src[0]\n");
    }

    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - changed src[1]\n");
    }

    if (pbuf2[2] != 'a')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - dest[0] incorrect\n");    
    }

    if (pbuf2[3] != 'b')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - after destination changed\n");
    }

    // success case no overlap source > destination
    
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 3, pbuf2 + 1, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - before destination changed\n");
    }

    if (pbuf2[1] != 'd')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - dest[0] incorrect\n");
    }

    if (pbuf2[2] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - dest[1] incorrect\n");    
    }

    if (pbuf2[3] != 'd')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - src[0] changed\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - src[1] changed\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - after source changed\n");
    }
    
    // success case overlap source starts in destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 2, pbuf2 + 1, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - before destination changed\n");
    }
    
    if (pbuf2[1] != 'd')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[3] != 'd')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - alternate src[0] changed\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - alternate src[1] changed\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - after alternate source changed\n");
    }
    
    // success case overlap source starts before destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 1, pbuf2 + 2, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - before source changed\n");
    }
    
    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - src[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[3] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - alternate src[1] incorrect\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - after alternate source incorrect\n");
    }
    
    
    // success case 2 overlap source starts before destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 1, pbuf2 + 3, 5);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - before source changed\n");
    }
    
    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - src[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - src[1] incorrect\n");
    }
    
    if (pbuf2[3] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[4] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[5] != 'i')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[2] incorrect\n");
    }
    
    if (pbuf2[6] != 'j')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[3] incorrect\n");
    }
    
    if (pbuf2[7] != 'k')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[4] incorrect\n");
    }
    
    if (pbuf2[8] != 'i')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[2] incorrect\n");
    }
    
    if (pbuf2[9] != 'j')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[3] incorrect\n");
    }
    
    if (pbuf2[10] != 'k')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[4] incorrect\n");
    }
    
    if (pbuf2[11] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - after alternate src incorrect\n");
    }
}


void testdg_getlstringstartoffset()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n---\ntesting dg_getlstringstartoffset\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE);

    UINT64 data = 0;
#ifndef DGLU_NO_DIAPER
    // error getting length of offset buffer case
    data = dg_getlstringstartoffset(&BHarrayhead, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset error getting length of offset buffer case - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset error getting length of offset buffer case - got error \n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset error getting length of offset buffer case - got error \n");
    }

    dg_clearerrors(&BHarrayhead);


    // test string off end error - no strings on stack case
    data = dg_getlstringstartoffset(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset string off end error - no strings on stack case - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset string off end error - no strings on stack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset get end offset error case - got error wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dont know how to test error getting end offset. error shouldn't happen

    // test getting string off end case (getting last end string offset)
    dg_pushbufferuint64(&BHarrayhead, i, 0x9);

    data = dg_getlstringstartoffset(&BHarrayhead, i, 1);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset off end error case - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset off end error case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset off end error case - got error wrong error 1 below top\n");
    }
#endif

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE);
    
    dg_pushbufferuint64(&BHarrayhead, i, 0x9);
    
    // test normal dg_success case a - one string on stack
    data = dg_getlstringstartoffset(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset dg_success case a - return incorrect\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset dg_success case a - got error \n");
    }

    // test dg_success case with only 2 strings on stack
    dg_pushbufferuint64(&BHarrayhead, i, 0x10);

    data = dg_getlstringstartoffset(&BHarrayhead, i, 1);

    if (data != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset dg_success case b - return incorrect\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringstartoffset dg_success case b - got error \n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getlstringlength()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getlstringlength\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE);

    UINT64 data = 0;

    // test getting beginning of string offset error
    data = dg_getlstringlength(&BHarrayhead, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // test getting start offset error - no strings on stack
    data = dg_getlstringlength(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case b - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case b - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength get start offset error case b - got wrong error 1 from top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // don't know how to test get end offset error


    // test beginning > end error
    dg_pushbufferuint64(&BHarrayhead, i, 0x8); // end of string 0
    dg_pushbufferuint64(&BHarrayhead, i, 0x5); // end of string 1

    data = dg_getlstringlength(&BHarrayhead, i, 1);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength begin > end error case - return not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength begin > end error case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringsoffsetscorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength begin > end error case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // test normal dg_success case
    dg_pushbufferuint64(&BHarrayhead, i, 0x9);

    data = dg_getlstringlength(&BHarrayhead, i, 2);

    if (data != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength dg_success case a - return incorrect\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength dg_success case a - got error \n");
    }

    // test dg_success case with only 1 string on stack
    dg_popbufferuint64(&BHarrayhead, i);
    dg_popbufferuint64(&BHarrayhead, i);

    data = dg_getlstringlength(&BHarrayhead, i, 0);

    if (data != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength dg_success case b - return incorrect\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstringlength dg_success case b - got error \n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getnumberoflstringsonstack()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getnumberoflstringsonstack\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE);

    UINT64 data = 0;
#ifndef DGLU_NO_DIAPER
    // testing dg_getbufferlength error
    data = dg_getnumberoflstringsonstack(&BHarrayhead, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack dg_getbufferlength error case - data not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack dg_getbufferlength error case - got wrong error on top \n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack dg_getbufferlength error case - got wrong error 1 below top \n");
    }

    dg_clearerrors(&BHarrayhead);

    // testing nub corrupt case
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    pBH->nextunusedbyte++;

    data = dg_getnumberoflstringsonstack(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack nub corrupt case - data not 0\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack nub corrupt case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackdepthcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack nub corrupt case - got wrong 1 below top\n");
    }

    pBH->nextunusedbyte--;

    dg_clearerrors(&BHarrayhead);
#endif
    // normal case
    dg_pushbufferuint64(&BHarrayhead, i, 0x11223344);

    data = dg_getnumberoflstringsonstack(&BHarrayhead, i);

    if (data != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack normal case - data not 1\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnumberoflstringsonstack normal case - got error \n");
    }


    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getplstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char* plstring = NULL;
    UINT64 stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getplstring\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    // testing error getting string start offset
    plstring = dg_getplstring(&BHarrayhead, 0, i, 0, &stringlength);

    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting string start offset case - stringlength not 0\n");
    }

    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting string start offset case - plstring not NULL\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting string start offset case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting string start offset case - got wrong error 1 from top\n");
    }

    dg_clearerrors(&BHarrayhead);


    // testing error getting string length
    //  not sure how to test this case, 
    //  it will fail getting start offset every time it fails getting the length
    

    // testing error getting buffer segment
    dg_pushbufferuint64(&BHarrayhead, i-1, 5);
    plstring = dg_getplstring(&BHarrayhead, i-1, 0, 0, &stringlength);

    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting buffer segment case - stringlength not 0\n");
    }

    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting buffer segment case - plstring not NULL\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting buffer segment case case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring error getting buffer segment case case - got wrong error 1 from top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // testing normal case
    dg_pushbuffersegment(&BHarrayhead, i, 8, (unsigned char*)"abcdefg");

    plstring = dg_getplstring(&BHarrayhead, i-1, i, 0, &stringlength);

    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring normal case - stringlength not 5\n");
    }

    if ((plstring[0] != 'a')|| 
        (plstring[1] != 'b')||
        (plstring[2] != 'c')||
        (plstring[3] != 'd')||
        (plstring[4] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring normal case - plstring not set to buffer segment\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring normal case - got error \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    // testing 2 strings on lstring stack
    dg_clearbuffer(&BHarrayhead, i-1);
    dg_clearbuffer(&BHarrayhead, i);
    
    dg_pushbufferuint64(&BHarrayhead, i-1, 5);
    dg_pushbuffersegment(&BHarrayhead, i, 5, (unsigned char*)"hello");
    
    dg_pushbufferuint64(&BHarrayhead, i-1, 11);
    dg_pushbuffersegment(&BHarrayhead, i, 6, (unsigned char*)"world!");
    
    plstring = dg_getplstring(&BHarrayhead, i-1, i, 0, &stringlength);

    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - 1st stringlength not 5\n");
    }

    if ((plstring[0] != 'h')||
        (plstring[1] != 'e')||
        (plstring[2] != 'l')||
        (plstring[3] != 'l')||
        (plstring[4] != 'o'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - 1st string data not right\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - got error on first string\n");
    }
    
    plstring = dg_getplstring(&BHarrayhead, i-1, i, 1, &stringlength);

    if (stringlength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - 2nd stringlength not 5\n");
    }

    if ((plstring[0] != 'w')||
        (plstring[1] != 'o')||
        (plstring[2] != 'r')||
        (plstring[3] != 'l')||
        (plstring[4] != 'd')||
        (plstring[5] != '!'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - 2nd string data not right\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getplstring 2 strings case - got error on second string \n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, i-1);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}



void testdg_getlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char lstring[80];
//    unsigned int stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getlstring\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    // testing error getting string start offset
    lstring[0] = 'a';

    dg_getlstring(&BHarrayhead, 0, i, 0, 80,lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting string start offset case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting string start offset case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting string start offset case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);


    // testing error getting string length
    //  not sure how to test this case, 
    //  it will fail getting start offset every time it fails getting the length

    // testing string too long case
    dg_pushbufferuint64(&BHarrayhead, i-1, 5);
    dg_getlstring(&BHarrayhead, i-1, 0, 0, 4, lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring string too long case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring string too long case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_toobigfordesterror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring string too long case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);
    

    // testing error getting buffer segment
    dg_getlstring(&BHarrayhead, i-1, 0, 0, 80, lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting buffer segment case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting buffer segment case case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring error getting buffer segment case case - got wrong error 1 below top\n");
    }    
    
    dg_clearerrors(&BHarrayhead);

    // testing normal case
    dg_pushbuffersegment(&BHarrayhead, i, 8, (unsigned char*)"bcdefgh");
    lstring[5] = 'a';

    dg_getlstring(&BHarrayhead, i-1, i, 0, 80, lstring);

    if ((lstring[0] != 'b')|| 
        (lstring[1] != 'c')||
        (lstring[2] != 'd')||
        (lstring[3] != 'e')||
        (lstring[4] != 'f'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring normal case - didn't get lstring\n");
    }

    if (lstring[5] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring normal case - extra characters gotten\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlstring normal case - got error \n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, i-1);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_poplstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char lstring[80];
//    unsigned int stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_poplstring\n");
#ifndef DGLU_NO_DIAPER
    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    //  Error getting number of strings on the string stack
    lstring[0] = 'a';

    dg_poplstring(&BHarrayhead, 0, i, 80, lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting number of strings on stack case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_poplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting number of strings on stack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting number of strings on stack case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    //  No strings on string stack
    lstring[0] = 'a';

    dg_poplstring(&BHarrayhead, i-1, i, 80, lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring underflow case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_poplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring underflow case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring underflow case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    //  Error getting the string
    dg_pushbufferuint64(&BHarrayhead, i-1, 0x5);

    lstring[0] = 'a';

    dg_poplstring(&BHarrayhead, i-1, i, 80, lstring);

    if (lstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting string case - lstring changed\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_poplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting string case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring error getting string case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
#endif
    //  Error shrinking the offset buffer (shouldn't get this error)
    //   don't know how to test this case
    //  Error shrinking the string buffer (shouldn't get this error)
    //   don't know how to test this case

    // dg_success case
    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer
    dg_pushbufferuint64(&BHarrayhead, i-1, 0x5);
    
    lstring[0] = 'a';
    lstring[5] = 'a';
    dg_pushbuffersegment(&BHarrayhead, i, 8, (unsigned char*)"bcdefgh");

    dg_poplstring(&BHarrayhead, i-1, i, 80, lstring);

    if ((lstring[0] != 'b')|| 
        (lstring[1] != 'c')||
        (lstring[2] != 'd')||
        (lstring[3] != 'e')||
        (lstring[4] != 'f'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring normal case - didn't get lstring\n");
    }

    if (lstring[5] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring normal case - extra characters gotten\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstring normal case - got error \n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, i-1);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_pushlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char lstring[80];
//    unsigned int stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushlstring\n");

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer
#ifndef DGLU_NO_DIAPER
    // get buffer length error
    dg_pushlstring(&BHarrayhead, i-1, 0, 10, lstring);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error getting bufferlength case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error getting bufferlength case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // push buffer segment to string buffer error
    dg_pushlstring(&BHarrayhead, i-1, i, dg_calcnearestpagesize(100)+1, lstring);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error putting buffer segment case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error putting buffer segment case - got wrong error 1 below top\n");
    }

    if (dg_getbufferlength(&BHarrayhead, i) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error putting buffer segment case - string buffer length changed \n");

    }

    if (dg_getbufferlength(&BHarrayhead, i-1) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error putting buffer segment case - offset buffer length changed \n");

    }

    dg_clearerrors(&BHarrayhead);

    // push offset of end of string + 1 to offset stack error
    dg_pushlstring(&BHarrayhead, 0, i, 10, lstring);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error pushing offset case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error pushing offset case - got wrong error 1 below top\n");
    }

    if (dg_getbufferlength(&BHarrayhead, i) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error pushing offset case - string buffer length changed \n");

    }

    if (dg_getbufferlength(&BHarrayhead, i-1) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring error pushing offset case - offset buffer length changed \n");

    }

    dg_clearerrors(&BHarrayhead);
#endif
    // dg_success case
    lstring[0] = 'a';
    lstring[1] = 'b';
    lstring[2] = 'c';
    lstring[3] = 'd';

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    ((unsigned char*)(pBH->pbuf))[0] = ' ';
    ((unsigned char*)(pBH->pbuf))[1] = ' ';
    ((unsigned char*)(pBH->pbuf))[2] = ' ';
    ((unsigned char*)(pBH->pbuf))[3] = ' ';

    dg_pushlstring(&BHarrayhead, i-1, i, 3, lstring);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, i) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, i-1) != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, i-1, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - end of string +1 offset incorrect\n");
    }

    if ( ( ((unsigned char*)(pBH->pbuf))[0] != 'a') ||
         ( ((unsigned char*)(pBH->pbuf))[1] != 'b') ||
         ( ((unsigned char*)(pBH->pbuf))[2] != 'c') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - string not copied\n");
    }

    if ( ((unsigned char*)(pBH->pbuf))[3] != ' ' ) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstring normal case - extra stuff in string buffer changed\n");
    }

    dg_clearerrors(&BHarrayhead);
         
    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, i-1);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_growlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    
    UINT64 offsetbuffer = 0;
    UINT64 stringbuffer = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_growlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to offset buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_growlstring(&BHarrayhead, 3984, 2934, 5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring error getting pointer to offset buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring error getting pointer to offset buffer case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    

    // underflow case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_growlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1); // lstring stack is empty

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring underflow case - got wrong error on top\n");
    }

     pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring underflow case - got wrong error 1 below\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    

    // error growing buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");

    dg_growlstring(&BHarrayhead, offsetbuffer, 3984, 1); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring error growing buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring error growing buffer case - got wrong error 1 below\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif
    

    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_growlstring(&BHarrayhead, offsetbuffer, stringbuffer, 4); 
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbuffer) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, offsetbuffer) != 2*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - end of string 0 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, sizeof(UINT64)) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - end of string 1 offset incorrect\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbuffer, 1) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - lstring length 1 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_picklstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    
    UINT64 offsetbuffer = 0;
    UINT64 stringbuffer = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_picklstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to offset buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_picklstring(&BHarrayhead, 3984, 2934, 5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring error getting pointer to offset buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring error getting pointer to offset buffer case - got error 1 below top\n");    }

    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);

    // underflow case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_picklstring(&BHarrayhead, offsetbuffer, stringbuffer, 0); // lstring stack is empty

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring underflow case - got error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring underflow case - got error 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // start > end case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_putbufferuint64(&BHarrayhead, offsetbuffer, 0, 5);

    dg_picklstring(&BHarrayhead, offsetbuffer, stringbuffer, 0); // lstring stack is empty

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring start > end case - got error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringsoffsetscorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring start > end case - got error 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // error growing string buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_picklstring(&BHarrayhead, offsetbuffer, 3472, 0); // lstring stack is empty

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring error growing string buffer case - got error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring error growing string buffer case - got error 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // end offset corrupt case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_putbufferuint64(&BHarrayhead, offsetbuffer, 1*sizeof(UINT64), 5);

    dg_picklstring(&BHarrayhead, offsetbuffer, stringbuffer, 0); // lstring stack is empty

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_picklstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring end offset corrupt case - got error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringtopoffsetwasbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_picklstring end offset corrupt case - got error 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // if grow string buffer worked, don't know how to get error getting pointer to string buffer
#endif
    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_picklstring(&BHarrayhead, offsetbuffer, stringbuffer, 1); 
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbuffer) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, offsetbuffer) != 3*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - end of string 0 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 1*sizeof(UINT64)) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - end of string 1 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 2*sizeof(UINT64)) != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - end of string 1 offset incorrect\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbuffer, 2) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - lstring length 1 incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbuffer, 4) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - lstring 2 char 0 incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbuffer, 5) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - lstring 2 char 1 incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbuffer, 6) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case - lstring 2 char 2 incorrect\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // dg_success case 2
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbuffer = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    stringbuffer = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbuffer, stringbuffer, 1, (unsigned char*)"a");

    dg_picklstring(&BHarrayhead, offsetbuffer, stringbuffer, 0); 
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbuffer) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, offsetbuffer) != 3*sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - end of string 0 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 1*sizeof(UINT64)) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - end of string 1 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbuffer, 2*sizeof(UINT64)) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - end of string 1 offset incorrect\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbuffer, 2) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - lstring length 1 incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbuffer, 4) != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_growlstring normal case 2 - lstring 2 char 0 incorrect\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_droplstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;


    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

    UINT64 t1 = 0;
    UINT64 t2 = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_droplstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_droplstring(&BHarrayhead, 3498, 2348);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_droplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting number of lstrings case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting number of lstrings case - got wrong error 1 below\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // no lstrings error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_droplstring(&BHarrayhead, offsetbufferid, stringbufferid);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_droplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring no lstrings error case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring no lstrings error case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);
    
    // error getting lstring length
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");

    t1 = dg_popbufferuint64(&BHarrayhead, offsetbufferid);
    t2 = dg_popbufferuint64(&BHarrayhead, offsetbufferid);

    dg_pushbufferuint64(&BHarrayhead, offsetbufferid, t1);
    dg_pushbufferuint64(&BHarrayhead, offsetbufferid, t2);

    dg_droplstring(&BHarrayhead, offsetbufferid, stringbufferid);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_droplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting lstring length case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting lstring length case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // dont know how to get the error shrinking the offset buffer if the other stuff worked

    // error shrinking string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"there");

    dg_droplstring(&BHarrayhead, offsetbufferid, 39840);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_droplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting lstring length case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_shrinkbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring error getting lstring length case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

#endif

    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"there");

    dg_droplstring(&BHarrayhead, offsetbufferid, stringbufferid);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, offsetbufferid) != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufferid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_droplstring normal case - end of string +1 offset incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_deletelstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;


    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

    UINT64 t1 = 0;
    UINT64 t2 = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_deletelstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_deletelstring(&BHarrayhead, 3498, 2348, 384);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring error getting number of lstrings case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring error getting number of lstrings case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // lstring not on stack error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");

    dg_deletelstring(&BHarrayhead, offsetbufferid, stringbufferid, 2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring - lstring not on stack error case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring - lstring not on stack error case - got wrong error 1 below\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    
    // error getting lstring length
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");

    t1 = dg_popbufferuint64(&BHarrayhead, offsetbufferid);
    t2 = dg_popbufferuint64(&BHarrayhead, offsetbufferid);

    dg_pushbufferuint64(&BHarrayhead, offsetbufferid, t1);
    dg_pushbufferuint64(&BHarrayhead, offsetbufferid, t2);

    dg_deletelstring(&BHarrayhead, offsetbufferid, stringbufferid, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring error getting lstring length case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring error getting lstring length case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // if getting the length worked, I don't know how to get an error getting the start offset

    // error deleting in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"there");

    dg_deletelstring(&BHarrayhead, offsetbufferid, 39840, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deletelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL error deleting in string buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL error deleting in string buffer case - got wrong error 1 below top\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // if get lstring length worked, I don't know how to get an error getting the pointer to the offset buffer

    // if get lstring length worked, I don't know how to get an error shrinking the offset buffer
#endif
    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"there");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"mou");

    dg_deletelstring(&BHarrayhead, offsetbufferid, stringbufferid, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, offsetbufferid) != 2* sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufferid, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - end of string 0 offset incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, offsetbufferid, sizeof(UINT64)) != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - end of string 1 offset incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 0 char 0  incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 0 char 1  incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 2) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 0 char 2  incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'm')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 1 char 0  incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 0 char 1  incorrect\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 5) != 'u')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deletelstring normal case - string 0 char 2  incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_insertlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
	
	unsigned char* pbuf;
	UINT64* pbuflength;

	
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

    UINT64 t1 = 0;
//    unsigned int t2 = 0;

    UINT64 i=0;

    UINT64 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_insertlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    //dg_insertlstring(&BHarrayhead, 3498, 2348, 384, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, 3498, 2348, 384, 5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring error getting number of lstrings case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring error getting number of lstrings case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // lstring not on stack error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"you");

    //dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, 5);


    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring - lstring not on stack error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring - lstring not on stack error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

	// error pushing empty string to top of stack, can't grow offset buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    t1 = ((UINT64)((8 * sizeof(UINT64) - 1) / pagesize) + 1) * pagesize;

    offsetbufferid = dg_newbuffer(&BHarrayhead, t1, t1, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

      // fill offsetbuffer
    for (i=0; i < t1/sizeof(UINT64); i++)
    {
        dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, (unsigned char*)"");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow offset buffer case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" filling up offset buffer\n");
    }

    //dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow offset buffer case - got wrong error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" on top inserting string with full offset buffer\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow offset buffer case - got wrong error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" 1 below top inserting string with full offset buffer\n");
    }

    dg_freeallbuffers(&BHarrayhead);

	// error inserting string in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    t1 = ((UINT32)((100 - 1) / pagesize) + 1) * pagesize;

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, t1, t1, &pError, FORTH_FALSE); // string string buffer

      // fake pushing lstring that fills string buffer
    for (i=0; i < t1; i++)
    {
        dg_pushbufferbyte(&BHarrayhead, stringbufferid, 0x31);
    }

    dg_pushbufferuint64(&BHarrayhead, offsetbufferid, t1);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow string buffer case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" filling up offset buffer\n");
    }

    //dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 1, (unsigned char*)"y");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 1);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow string buffer case - got wrong error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" on top inserting string with full offset buffer\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring can't grow string buffer case - got wrong error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)" 1 below top inserting string with full offset buffer\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif	
	// can you get error from getting offset?

	// success case inserting to empty lstring stack
	// dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to empty stack success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to empty stack success case - not one string on stack \n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to empty stack success case - pushed lstring length wrong \n");
	}

	dg_freeallbuffers(&BHarrayhead);
	
	// success case inserting to end of non empty lstring stack
	// dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3, (unsigned char*)"sir");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack b success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack success case - not two strings on stack \n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack success case - pushed lstring 0 length wrong \n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack success case - pushed lstring 1 length wrong \n");
	}

	pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

	//dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_insertlstring inserting to end of non empty stack case, lstring buffer looks like - ");
	//dg_writestdout(&BHarrayhead, pbuf, *pbuflength);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'h')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'o')
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack  case - string 0 char 4  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 5) != 's')
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack  case - string 1 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[5]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 7) != 'r')
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to end of non empty stack  case - string 1 char 2  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[7]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	dg_freeallbuffers(&BHarrayhead);

	
	// success case inserting to beginning of non empty lstring stack
	// dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3, (unsigned char*)"sir");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 4, (unsigned char*)"many");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 4);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack success case - not two strings on stack \n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack success case - pushed lstring 0 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 0));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack success case - pushed lstring 1 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 2) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack success case - pushed lstring 2 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 2));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

	//dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_insertlstring inserting to beginning of non empty stack case, lstring buffer looks like - ");
	//dg_writestdout(&BHarrayhead, pbuf, *pbuflength);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'm')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'y')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[3]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'h')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to beginning of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	dg_freeallbuffers(&BHarrayhead);

    // success case inserting to middle of non empty lstring stack
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5, (unsigned char*)"hello");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 5);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3, (unsigned char*)"sir");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 3);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	//dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 4, (unsigned char*)"many");
    dg_insertlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 4);


	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack a success case - got error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack success case - not two strings on stack \n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack success case - pushed lstring 0 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 0));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack success case - pushed lstring 1 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 2) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack success case - pushed lstring 2 length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 2));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

	//dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_insertlstring inserting to middle of non empty stack case, lstring buffer looks like - ");
	//dg_writestdout(&BHarrayhead, pbuf, *pbuflength);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'h')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'o')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	//if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 5) != 'm')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

    //if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 8) != 'y')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[8]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

    //if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 9) != 's')
    //{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertlstring inserting to middle of non empty stack  case - string 0 char 0  incorrect got ");
	//	dg_writestdout(&BHarrayhead, &(pbuf[9]), 1);
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_deleteinlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
	
	unsigned char* pbuf;
	UINT64* pbuflength;

	
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_deleteinlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    //dg_insertlstring(&BHarrayhead, 3498, 2348, 384, 5, (unsigned char*)"hello");
    dg_deleteinlstring(&BHarrayhead, 3498, 2348, 384, 5, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring error getting number of lstrings case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring error getting number of lstrings case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // lstring not on stack error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"you");

    dg_deleteinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 2, 5, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - lstring not on stack error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - lstring not on stack error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);


    // segment goes past end of lstring error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Pinky");

    dg_deleteinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 2, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes past end error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringsegmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes past end error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case segment goes to end
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_deleteinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 2, 3);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - lstring 0 length wrong, expected 3 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - lstring 1 length wrong, expected 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - string buffer length wrong, expected 5 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - string buffer character[3] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[3]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - segment goes to end success case - string buffer character[4] wrong, expected i got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // success case one string on l$stack
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");

    dg_deleteinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 0, 1);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - one lstring on stack success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - one lstring on stack success case - lstring 0 length wrong, expected 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - one lstring on stack success case - string buffer length wrong, expected 1 got ");        
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 2));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - one lstring on stack success case - string buffer character[0] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - one lstring on stack success case - string buffer character[1] wrong, expected y got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // success case many strings on l$stack delete below top
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 4, (unsigned char*)"Cats");

    dg_deleteinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 1, 2);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - lstring 0 length wrong, expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - lstring 1 length wrong, expected 5 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 2) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - lstring 2 length wrong, expected 4 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - string buffer length wrong, expected 10 got ");        
        dg_writestdoutuinttodec(&BHarrayhead, dg_getbufferlength(&BHarrayhead, offsetbufferid));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - string buffer character[0] wrong, expected H got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinlstring - many strings on l$stack delete below top success case - string buffer character[1] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_insertinlstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
	
	unsigned char* pbuf;
	UINT64* pbuflength;

	
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_insertinlstring\n");
#ifndef DGLU_NO_DIAPER
    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    //dg_insertlstring(&BHarrayhead, 3498, 2348, 384, 5, (unsigned char*)"hello");
    dg_insertinlstring(&BHarrayhead, 3498, 2348, 384, 5, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring error getting number of lstrings case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring error getting number of lstrings case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // lstring not on stack error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"you");

    dg_insertinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 2, 5, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - lstring not on stack error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - lstring not on stack error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);


    // offset past end of lstring error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Pinky");

    dg_insertinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 6, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - offset past end error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringoffsetpastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - offset past end error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case segment starts at end
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_insertinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 1, 5, 3);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - lstring 0 length wrong, expected 3 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - lstring 1 length wrong, expected 8 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - string buffer length wrong, expected 11 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 6) != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - string buffer character[3] wrong, expected k got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[6]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 7) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - segment starts at end success case - string buffer character[4] wrong, expected y got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[7]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // success case one string on l$stack
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");

    dg_insertinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 0, 1);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - one lstring on stack success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - one lstring on stack success case - lstring 0 length wrong, expected 4 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - one lstring on stack success case - string buffer length wrong, expected 4 got ");        
        dg_writestdoutuinttodec(&BHarrayhead, dg_getbufferlength(&BHarrayhead, offsetbufferid));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - one lstring on stack success case - string buffer character[1] wrong, expected H got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 2) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - one lstring on stack success case - string buffer character[2] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[2]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // success case many strings on l$stack insert below top
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 4, (unsigned char*)"Cats");

    dg_insertinlstring(&BHarrayhead, offsetbufferid, stringbufferid, 0, 1, 2);

    pError = dg_poperror(&BHarrayhead);

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - lstring 0 length wrong, expected 5 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 1) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - lstring 1 length wrong, expected 5 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 2) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - lstring 2 length wrong, expected 4 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 1));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - string buffer length wrong, expected 14 got ");        
        dg_writestdoutuinttodec(&BHarrayhead, dg_getbufferlength(&BHarrayhead, offsetbufferid));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 0) != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - string buffer character[0] wrong, expected H got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[0]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertinlstring - many strings on l$stack delete below top success case - string buffer character[3] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[3]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_catlstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_catlstringn\n");
#ifndef DGLU_NO_DIAPER

    // error getting number of lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    //dg_insertlstring(&BHarrayhead, 3498, 2348, 384, 5, (unsigned char*)"hello");
    dg_catlstringn(&BHarrayhead, 3498, 2348, 4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_catlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn error getting number of lstrings case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getnumberoflstringsonstackname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn error getting number of lstrings case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // lstring not on stack error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"you");

    dg_catlstringn(&BHarrayhead, offsetbufferid, stringbufferid, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_catlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - lstring not on stack error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - lstring not on stack error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Brain");

    dg_catlstringn(&BHarrayhead, offsetbufferid, stringbufferid, 0);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid) != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - success case - number of lstrings on stack wrong, expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufferid));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getlstringlength(&BHarrayhead, offsetbufferid, 0) != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - success case - lstring 0 length wrong, expected 8 got ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_getlstringlength(&BHarrayhead, offsetbufferid, 0));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    if (dg_getbufferlength(&BHarrayhead, stringbufferid) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_catlstringn - success case - string buffer length wrong, expected 8 got ");        
        dg_writestdoutuinttodec(&BHarrayhead, dg_getbufferlength(&BHarrayhead, offsetbufferid));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copystolstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

    unsigned char* psrc = (unsigned char*)"abcd";
    unsigned char* pbuf;
    UINT64* pbuflength;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copystolstringn\n");


    // error getting start offset of lstring in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    dg_copystolstringn(&BHarrayhead, 3498, 2348, 4, 3, (unsigned char*)badbufferhandle, 2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copystolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn error getting lstring start offset case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // if you are able to get the start offset, then you should not get an error getting the length

    // segment goes past end error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_copystolstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        2,
        psrc,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copystolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - segment goes past end error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringsegmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - segment goes past end error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif
    // put error doing copy case here

    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_copystolstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        2,
        psrc,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case - string buffer character[1] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 2) != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case - string buffer character[2] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[2]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case - string buffer character[3] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[3]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // success case 2
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_copystolstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        1,
        1,
        psrc,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[3] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 3);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[4] wrong, expected a got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 5) != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[5] wrong, expected b got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[5]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_pushstolstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

    unsigned char* psrc = (unsigned char*)"abcd";
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 x;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushstolstringn\n");


    // error getting start offset of lstring in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    dg_pushstolstringn(&BHarrayhead, 3498, 2348, 4, (unsigned char*)badbufferhandle, 2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushstolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn error getting lstring start offset case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

#endif

    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_pushstolstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        psrc,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 1) != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - string buffer character[1] wrong, expected e got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 2) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - string buffer character[2] wrong, expected y got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[2]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - string buffer character[3] wrong, expected a got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[3]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - string buffer character[3] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getlstringlength (
		&BHarrayhead,
		offsetbufferid,
		0);
  
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - got an error getting string length, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }    
    
    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case - string length wrong, expected 4, got ");
     	dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }  

    dg_freeallbuffers(&BHarrayhead);

    // success case 2
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_pushstolstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        1,
        psrc,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case 2 - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 3) != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case 2 - string buffer character[3] wrong, expected P got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[1]), 3);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 4) != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[4] wrong, expected a got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[4]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 5) != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[5] wrong, expected n got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[5]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 6) != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[6] wrong, expected k got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[6]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 7) != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[7] wrong, expected y got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[7]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 8) != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[8] wrong, expected a got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[8]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_getbufferbyte(&BHarrayhead, stringbufferid, 9) != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copystolstringn - success case 2 - string buffer character[a] wrong, expected b got ");
     	dg_writestdout(&BHarrayhead, &(pbuf[9]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getlstringlength (
		&BHarrayhead,
		offsetbufferid,
		1);
  
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case 2 - got an error getting string length, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }    
    
    if (x != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushstolstringn - success case 2 - string length wrong, expected 7, got ");
     	dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }  

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copysfromlstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    unsigned int offsetbufferid = 0;
    unsigned int stringbufferid = 0;

//    unsigned int t1 = 0;
//    unsigned int t2 = 0;

//    UINT32 i=0;

    unsigned char pdest[5];
    unsigned char* pbuf;
    UINT64* pbuflength;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copysfromlstringn\n");

#ifndef DGLU_NO_DIAPER
    // error getting start offset of lstring in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_copysfromlstringn(
        &BHarrayhead, 
        3498, 
        2348, 
        4, 
        3, 
        2,
        (unsigned char*)badbufferhandle);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copysfromlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn error getting lstring start offset case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // if you are able to get the start offset, then you should not get an error getting the length

    // segment goes past end error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_copysfromlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        2,
        2,
        pdest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copysfromlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - segment goes past end error case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringsegmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - segment goes past end error case - got wrong error 1 below ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // error doing copy lstring 0 not exist case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_copysfromlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        offsetbufferid, 
        0, 
        0, 
        2,
        pdest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copysfromlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn error doing copy lstring 0 not exist case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn error doing copy lstring 0 not exist case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    pdest[0] = 'a';

    dg_copysfromlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        2,
        1,
        pdest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - success case - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pdest[0] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - success case - destination string character[1] wrong, expected y got ");
     	dg_writestdout(&BHarrayhead, &(pdest[0]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // success case 2
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    pdest[0] = 'a';
    pdest[1] = 'b';

    dg_copysfromlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        1,
        1,
        2,
        pdest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - success case 2 - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pbuflength);

    if (pdest[0] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - success case 2 - destination string character[0] wrong, expected i got ");
     	dg_writestdout(&BHarrayhead, &(pdest[0]), 3);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pdest[1] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromlstringn - success case 2 - destination string character[1] wrong, expected n got ");
     	dg_writestdout(&BHarrayhead, &(pdest[1]), 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_setlengthlstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;

    UINT64* poffsetbuf = NULL;
    UINT64* poffsetbuflength = NULL;

    unsigned char* pstringbuf = NULL;
    UINT64* pstringbuflength = NULL;
		
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_setlengthlstringn\n");
#ifndef DGLU_NO_DIAPER

    // error getting start offset of lstring in string buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_setlengthlstringn(
        &BHarrayhead, 
        3498, 
        2348, 
        4, 
        3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_setlengthlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn error getting lstring start offset case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringstartoffsetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // if you are able to get the start offset, then you should not get an error getting the length

    // error shrinking lstring - should not be able to get an error doing this I think
    //   what if pointer to string buffer is wrong? or string buffer id is wrong?
    
    // error growing lstring - can get an out of memory error

    // success case - shrinking lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_setlengthlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        2);

    //buffer should not have moved since dg_newbuffer, but it is better to get pointers after dg_setlengthstringn
    poffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, offsetbufferid, &poffsetbuflength);
    pstringbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pstringbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (poffsetbuf[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - length of lstring 0 incorrect\n");
    }

    if (poffsetbuf[1] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - length of lstring 1 incorrect\n");
    }
    
    if (pstringbuf[0] != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 0 character 0 incorrect, got ");
        dg_writestdoutraw(&BHarrayhead, pstringbuf + 0, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pstringbuf[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 0 character 1 incorrect\n");
    }

    if (pstringbuf[2] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 2 character 0 incorrect\n");
    }

    if (pstringbuf[3] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 2 character 1 incorrect\n");
    }

    if (pstringbuf[4] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 2 character 2 incorrect\n");
    }

    if (pstringbuf[5] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 2 character 3 incorrect\n");
    }

    if (pstringbuf[6] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case shrinking lstring - lstring 2 character 4 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case - growing lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");

    dg_setlengthlstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid, 
        0,
        6);

    //buffer may have moved since dg_newbuffer
    poffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, offsetbufferid, &poffsetbuflength);
    pstringbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pstringbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (poffsetbuf[0] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - length of lstring 0 incorrect\n");
    }

    if (poffsetbuf[1] != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - length of lstring 1 incorrect\n");
    }
    
    if (pstringbuf[0] != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 0 incorrect, got ");
        dg_writestdoutraw(&BHarrayhead, pstringbuf + 0, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pstringbuf[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 1 incorrect\n");
    }

    if (pstringbuf[2] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 2 incorrect\n");
    }

    if (pstringbuf[3] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 3 incorrect\n");
    }

    if (pstringbuf[4] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 4 incorrect\n");
    }

    if (pstringbuf[5] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 0 character 5 incorrect\n");
    }

    if (pstringbuf[6] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 1 character 0 incorrect\n");
    }

    if (pstringbuf[7] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 1 character 1 incorrect\n");
    }

    if (pstringbuf[8] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 1 character 2 incorrect\n");
    }

    if (pstringbuf[9] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 1 character 3 incorrect\n");
    }

    if (pstringbuf[10] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_setlengthlstringn - success case growing lstring - lstring 1 character 4 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_replacelstringn()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    UINT64 offsetbufferid = 0;
    UINT64 stringbufferid = 0;

    UINT64* poffsetbuf = NULL;
    UINT64* poffsetbuflength = NULL;

    unsigned char* pstringbuf = NULL;
    UINT64* pstringbuflength = NULL;

//    UINT32 pagesize = dg_getpagesize();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_replacelstringn\n");


    // success case - growing lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 8, (unsigned char*)"thinking");

    dg_replacelstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid,
        0,
        (unsigned char*)"AreYou",
        6);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    //buffer may have moved since dg_newbuffer
    poffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, offsetbufferid, &poffsetbuflength);
    pstringbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pstringbuflength);

    if (poffsetbuf[0] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 0 incorrect\n");
    }

    if (poffsetbuf[1] != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 1 incorrect\n");
    }

    if (poffsetbuf[2] != 19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 1 incorrect\n");
    }
    
    if (pstringbuf[0] != 'A')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 0 incorrect, got ");
        dg_writestdoutraw(&BHarrayhead, pstringbuf + 0, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pstringbuf[1] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 1 incorrect\n");
    }

    if (pstringbuf[2] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 2 incorrect\n");
    }

    if (pstringbuf[3] != 'Y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 3 incorrect\n");
    }

    if (pstringbuf[4] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 4 incorrect\n");
    }

    if (pstringbuf[5] != 'u')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 5 incorrect\n");
    }

    if (pstringbuf[6] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 0 incorrect\n");
    }

    if (pstringbuf[7] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 1 incorrect\n");
    }

    if (pstringbuf[8] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 2 incorrect\n");
    }

    if (pstringbuf[9] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 3 incorrect\n");
    }

    if (pstringbuf[10] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 4 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // success case - shrinking lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    offsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    stringbufferid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, offsetbufferid, stringbufferid, 5, (unsigned char*)"Brain");

    dg_replacelstringn(
        &BHarrayhead, 
        offsetbufferid, 
        stringbufferid,
        1,
        (unsigned char*)"IThinkSo",
        8);

    //buffer may have moved since dg_newbuffer
    poffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, offsetbufferid, &poffsetbuflength);
    pstringbuf = dg_getpbuffer(&BHarrayhead, stringbufferid, &pstringbuflength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (poffsetbuf[0] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 0 incorrect\n");
    }

    if (poffsetbuf[1] != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 1 incorrect\n");
    }

    if (poffsetbuf[2] != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - length of lstring 1 incorrect\n");
    }
    
    if (pstringbuf[0] != 'H')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 0 incorrect, got ");
        dg_writestdoutraw(&BHarrayhead, pstringbuf + 0, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pstringbuf[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 1 incorrect\n");
    }

    if (pstringbuf[2] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 0 character 2 incorrect\n");
    }

    if (pstringbuf[3] != 'I')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 0 incorrect\n");
    }

    if (pstringbuf[4] != 'T')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 1 incorrect\n");
    }

    if (pstringbuf[5] != 'h')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 2 incorrect\n");
    }

    if (pstringbuf[6] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 3 incorrect\n");
    }

    if (pstringbuf[7] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 4 incorrect\n");
    }

    if (pstringbuf[8] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 5 incorrect\n");
    }

    if (pstringbuf[9] != 'S')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 6 incorrect\n");
    }

    if (pstringbuf[10] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 1 character 7 incorrect\n");
    }

    if (pstringbuf[11] != 'B')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 2 character 0 incorrect\n");
    }

    if (pstringbuf[12] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 2 character 1 incorrect\n");
    }

    if (pstringbuf[13] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 2 character 2 incorrect\n");
    }

    if (pstringbuf[14] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 2 character 3 incorrect\n");
    }

    if (pstringbuf[15] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_replacelstringn - success case growing lstring - lstring 2 character 4 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copylstringntoreplacelstringn()
{
//    UINT32 tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
		
    UINT64 srcoffsetbufferid = 0;
    UINT64 srcstringbufferid = 0;

    UINT64 destoffsetbufferid = 0;
    UINT64 deststringbufferid = 0;

    UINT64* pdestoffsetbuf = NULL;
    UINT64* pdestoffsetbuflength = NULL;

    unsigned char* pdeststringbuf = NULL;
    UINT64* pdeststringbuflength = NULL;

    UINT64* psrcoffsetbuf = NULL;
    UINT64* psrcoffsetbuflength = NULL;

    unsigned char* psrcstringbuf = NULL;
    UINT64* psrcstringbuflength = NULL;

    UINT64 testbuflength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copylstringntoreplacelstringn\n");
#ifndef DGLU_NO_DIAPER
    // error getting source lstring length case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_copylstringntoreplacelstringn(
        &BHarrayhead, 
        3498, 
        2348, 
        4, 
        3234,
        3241,
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copylstringntoreplacelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error getting lstring start offset case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // error setting destination lstring length case
    //  (can get this if destination offset buffer messed up, or out of memory for string buffer grow)
    //  (lower level functions are tested so only need to check if error from them is handled correctly)
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // string string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_copylstringntoreplacelstringn(
        &BHarrayhead, 
        srcoffsetbufferid, 
        srcstringbufferid, 
        0, 
        3234,
        3241,
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copylstringntoreplacelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error setting destination lstring length case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_setlengthlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error setting destination lstring length case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // error getting pointer to source lstring case
    //  (if source offset buffer is ok but string buffer is messed up you can get this)
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    destoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    deststringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 4, (unsigned char*)"What");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 3, (unsigned char*)"are");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 2, (unsigned char*)"we");

    dg_freebuffer(&BHarrayhead, srcstringbufferid);

    dg_copylstringntoreplacelstringn(
        &BHarrayhead, 
        srcoffsetbufferid, 
        srcstringbufferid, 
        0, 
        destoffsetbufferid,
        deststringbufferid,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copylstringntoreplacelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error getting pointer to source lstring case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error getting pointer to source lstring case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    // error copying to destination lstring case
    //  (if destination offset buffer is ok, but string buffer is not you can get this)
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    destoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    deststringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 4, (unsigned char*)"What");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 3, (unsigned char*)"are");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 2, (unsigned char*)"we");

    dg_freebuffer(&BHarrayhead, deststringbufferid);

    dg_copylstringntoreplacelstringn(
        &BHarrayhead, 
        srcoffsetbufferid, 
        srcstringbufferid, 
        0, 
        destoffsetbufferid,
        deststringbufferid,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copylstringntoreplacelstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error copying to destination lstring case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copystolstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn error copying to destination lstring case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case - worst case - source and destination lstring are in same buffer with relocating grow
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    // making sure string buffer is at least 64 bytes
    testbuflength = dg_calcnearestpagesize(64);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // string offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, testbuflength, 2*testbuflength, &pError, FORTH_FALSE); // string string buffer

    // push lstrings that are = to page size, then have a copy that makes it go over
    dg_pushlstring(
        &BHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        0,
        (unsigned char*)"");

    dg_growlstring(
        &BHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        testbuflength-8);

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinko");

    dg_copylstringntoreplacelstringn(
        &BHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        2,
        srcoffsetbufferid,
        srcstringbufferid,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    //buffer may have moved since dg_newbuffer
    psrcoffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, srcoffsetbufferid, &psrcoffsetbuflength);
    psrcstringbuf = dg_getpbuffer(&BHarrayhead, srcstringbufferid, &psrcstringbuflength);

    if (psrcoffsetbuf[0] != testbuflength - 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 0 length incorrect\n");
    }

    if (psrcoffsetbuf[1] != testbuflength - 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 length incorrect\n");
    }

    if (psrcoffsetbuf[2] != testbuflength + 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 length incorrect\n");
    }

    if (psrcstringbuf[testbuflength-8] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 character 0 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-7] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 character 1 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-6] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 character 2 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-5] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 character 3 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-4] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 1 character 4 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-3] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 character 0 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-2] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 character 1 incorrect\n");
    }

    if (psrcstringbuf[testbuflength-1] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 character 2 incorrect\n");
    }

    if (psrcstringbuf[testbuflength] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 character 3 incorrect\n");
    }

    if (psrcstringbuf[testbuflength+1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - lstring 2 character 4 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);


    // success case - separate source and destination buffers
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    destoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    deststringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 4, (unsigned char*)"What");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 3, (unsigned char*)"are");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 2, (unsigned char*)"we");

    dg_copylstringntoreplacelstringn(
        &BHarrayhead, 
        srcoffsetbufferid, 
        srcstringbufferid, 
        1, 
        destoffsetbufferid,
        deststringbufferid,
        0);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case worst case source and destination same buffer with grow - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    //buffer may have moved since dg_newbuffer
    pdestoffsetbuf = (UINT64*)dg_getpbuffer(&BHarrayhead, destoffsetbufferid, &pdestoffsetbuflength);
    pdeststringbuf = dg_getpbuffer(&BHarrayhead, deststringbufferid, &pdeststringbuflength);

    if (pdestoffsetbuf[0] != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 length incorrect\n");
    }

    if (pdestoffsetbuf[1] != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 1 length incorrect\n");
    }

    if (pdestoffsetbuf[2] != 10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 2 length incorrect\n");
    }

    if (pdeststringbuf[0] != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 character 0 incorrect\n");
    }

    if (pdeststringbuf[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 character 1 incorrect\n");
    }

    if (pdeststringbuf[2] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 character 2 incorrect\n");
    }

    if (pdeststringbuf[3] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 character 3incorrect\n");
    }

    if (pdeststringbuf[4] != 'y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 0 character 4 incorrect\n");
    }

    if (pdeststringbuf[5] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 1 character 0 incorrect\n");
    }

    if (pdeststringbuf[6] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 1 character 1 incorrect\n");
    }

    if (pdeststringbuf[7] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 1 character 2 incorrect\n");
    }

    if (pdeststringbuf[8] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 2 character 0 incorrect\n");
    }

    if (pdeststringbuf[9] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copylstringntoreplacelstringn - success case - separate source and destination buffers - lstring 2 character 1 incorrect\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copytoinsertlstrntom()
{
    Bufferhandle BHarrayhead;
    
    UINT64 srcoffsetbufferid;
    UINT64 srcstringbufferid;
    
    UINT64 destoffsetbufferid;
    UINT64 deststringbufferid;
    
    unsigned char* pdestm;

    UINT64 destlengthm;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copytoinsertlstrntom\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to source case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_copytoinsertlstrntom (
        &BHarrayhead,
        (UINT32)dg_badbufferid,
        (UINT32)dg_badbufferid,
        0,
        0,
        (UINT32)dg_badbufferid,
        (UINT32)dg_badbufferid,
        0,
        0,
        0);
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_copytoinsertlstrntomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom error getting pointer to source case - got wrong error on top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom error getting lstring start offset case - got wrong error 1 below top ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
 #endif   
    // success case copy to insertin in different lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    destoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    deststringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 4, (unsigned char*)"What");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 3, (unsigned char*)"are");
    dg_pushlstring(&BHarrayhead, destoffsetbufferid, deststringbufferid, 2, (unsigned char*)"we");
    
    dg_copytoinsertlstrntom (
        &BHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        1,
        2,
        destoffsetbufferid,
        deststringbufferid,
        0,
        3,
        2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring, got errors doing dg_copytoinsertlstrntom - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pdestm = dg_getplstring(
        &BHarrayhead,
        destoffsetbufferid,
		deststringbufferid,
		0,
        &destlengthm);
        
    if (destlengthm != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring, destination lstring length is not as expected. Expected 6 got ");
        dg_writestdoutuinttodec(&BHarrayhead, destlengthm);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdestm[2] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring,  dest[2] incorrect, expected a \n");
    }
    
    if (pdestm[3] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring,  dest[3] incorrect, expected n \n");
    }
    
    if (pdestm[4] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring,  dest[4] incorrect, expected k \n");
    }
    
    if (pdestm[5] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in different lstring,  dest[5] incorrect, expected t \n");
    }
    
    // success case copy to insertin in same lstring
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);

    srcoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    srcstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, srcoffsetbufferid, srcstringbufferid, 5, (unsigned char*)"Brain");

    dg_copytoinsertlstrntom (
        &BHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        1,
        1,
        srcoffsetbufferid,
        srcstringbufferid,
        1,
        2,
        2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring, got errors doing dg_copytoinsertlstrntom - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pdestm = dg_getplstring(
        &BHarrayhead,
        srcoffsetbufferid,
		srcstringbufferid,
		1,
        &destlengthm);
        
    if (destlengthm != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring, destination lstring length is not as expected. Expected 6 got ");
        dg_writestdoutuinttodec(&BHarrayhead, destlengthm);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdestm[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring,  dest[1] incorrect, expected i \n");
    }
    
    if (pdestm[2] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring,  dest[2] incorrect, expected i \n");
    }
    
    if (pdestm[3] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring,  dest[3] incorrect, expected n \n");
    }
    
    if (pdestm[4] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertlstrntom - success case copy to insertin in same lstring,  dest[4] incorrect, expected n \n");
    }
}


void testdg_makesurelstringnexists ()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    
    UINT64 depth;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_makesurelstringnexists\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to offset buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_makesurelstringnexists (
        &BHarrayhead,
        (UINT32)dg_badbufferid,
        (UINT32)dg_badbufferid,
        0);
        
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_makesurelstringnexistsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists error getting pointer to source case - got wrong error on top expected dg_makesurelstringnexistsname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists error getting pointer to source case - got wrong error 1 below top expected dg_getpbuffername, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif    
    // 2 from 0 success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 0 success case, error making test buffers\n");
    }
    
    dg_makesurelstringnexists (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 0 success case, got error making sure lstringn exists\n");
    }
    
    depth = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        lstringoffsetbufferid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 0 success case, error getting lstring depth, got\n");
        // dg_forthdoterrors(&BHarrayhead);
    }

    if (depth != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 0 success case, depth not correct, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // 2 from 2 success case
    dg_makesurelstringnexists (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 2 success case, got error making sure lstringn exists\n");
    }
    
    depth = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        lstringoffsetbufferid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 2 success case, error getting lstring depth, got\n");
        // dg_forthdoterrors(&BHarrayhead);
    }

    if (depth != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 2 from 2 success case, depth not correct, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // 3 from 2 success case
    dg_makesurelstringnexists (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        3);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 3 from 2 success case, got error making sure lstringn exists\n");
    }
    
    depth = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        lstringoffsetbufferid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 3 from 2 success case, error getting lstring depth, got\n");
        // dg_forthdoterrors(&BHarrayhead);
    }

    if (depth != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesurelstringnexists - 3 from 2 success case, depth not correct, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, depth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_newfreeablelstringarray()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 flstrbufid;
    unsigned char* pbuf;
    UINT64* pbuflength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newfreeablelstringarray\n");

    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, expected no error - got an error ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // free index buffer length should be size of free index buffer header
    if (*pbuflength != sizeof(Freeablelstringarrayheader))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, length of free index buffer incorrect.\n");
    }
    
    // checking magic id
    if ( (((Freeablelstringarrayheader*)(pbuf))->magic) != dg_freeablelstringheadermagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, free index buffer magic incorrect.\n");
    }
    
    // checking offset buffer id for valid buffer
    pError = dg_checkbuffer( &BHarrayhead, (((Freeablelstringarrayheader*)(pbuf))->lstringoffsetbufferid) );
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, got error checking lstring offset buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // checking offset buffer id for valid buffer
    pError = dg_checkbuffer( &BHarrayhead, (((Freeablelstringarrayheader*)(pbuf))->lstringstringbufferid) );
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, got error checking lstring string buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // checking first free index to make sure it is the 'end of list' marker
    if ( (((Freeablelstringarrayheader*)(pbuf))->firstfreeid) != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringarray - success case, free index buffer first free index incorrect.\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_freefreeablelstringarray ()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 flstrbufid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    Freeablelstringarrayheader* pheader;
    UINT64 lstringoffsetbufid;
    UINT64 lstringstringbufid;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freefreeablelstringarray\n");

    // success case
    dg_initbuffers(&BHarrayhead);
    // dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
    
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, got error making new freeable lstring array - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    
    dg_freefreeablelstringarray(&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, expected no error freeing new lstring array, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer(&BHarrayhead, flstrbufid);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, expected lstring string free index buffer to be free, got message ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer(&BHarrayhead, lstringoffsetbufid);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, expected lstring offset buffer to be free, got message ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     pError = dg_checkbuffer(&BHarrayhead, lstringstringbufid);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freefreeablelstringarray - success case, expected lstring string buffer to be free, got message ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_newfreeablelstring()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 flstrbufid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    Freeablelstringarrayheader* pheader;
    UINT64 lstringoffsetbufid;
    UINT64 lstringstringbufid;
    UINT64 myfirstfreeid;
    
    UINT64 flstrid;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newfreeablelstring\n");

    // making freeable lstring array for test
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - success case, got error making new freeable lstring array - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // empty array success case
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, got error making new freeable lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (flstrid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, returned lstring index incorrect\n ");
    }
    
    // none were free, so first free should still point to end of list
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, first free id was changed from end of list\n ");
    }
    
    if (*((UINT64*)(pbuf + sizeof(Freeablelstringarrayheader))) != (UINT64)dg_freeablelstringisnotfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, lstring is not marked as not free\n ");
    }
    
    if (*pbuflength != (sizeof(Freeablelstringarrayheader) + sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - empty array success case, lstring free index buffer length is not as expected\n ");
    }
    
    // non empty array none free success case
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, got error making new freeable lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (flstrid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, returned lstring index incorrect\n ");
    }
    
    // none were free, so first free should still point to end of list
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, first free id was changed from end of list\n ");
    }
    
    if (*((UINT64*)(pbuf + sizeof(Freeablelstringarrayheader) + sizeof(UINT64))) != (UINT64)dg_freeablelstringisnotfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, lstring is not marked as not free\n ");
    }
    
    if (*pbuflength != (sizeof(Freeablelstringarrayheader) + (2*sizeof(UINT64))))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - non empty array none free success case, lstring free index buffer length is not as expected\n ");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_freefreeablelstring()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 flstrbufid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    Freeablelstringarrayheader* pheader;
    UINT64 lstringoffsetbufid;
    UINT64 lstringstringbufid;
    UINT64 myfirstfreeid;
    
    UINT64 flstrid;
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freefreeablelstring\n");

    // freeing end of list success case
    
     // making freeable lstring array for test
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - setup, got error making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing end of list success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, flstrid);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing end of list success case, got errors freeing new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing end of list success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing end of list success case, first free id was changed from end of list\n ");
    }
    
    if ((*pbuflength) != sizeof(Freeablelstringarrayheader))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing end of list success case, lstring free index buffer length is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, sizeof(Freeablelstringarrayheader));
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, (*pbuflength));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // freeing index not at end of list success case
    
     // making freeable lstring array for test
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - setup, got error making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    dg_freefreeablelstring(&BHarrayhead, flstrbufid, 1); // freeing lstring 1 of 0, 1, 2
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, got errors freeing new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, first free id was not changed from end of list\n ");
    }
    
    if ((*pbuflength) != (sizeof(Freeablelstringarrayheader) + 3 * sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, lstring free index buffer length is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, sizeof(Freeablelstringarrayheader) + (3 * sizeof(UINT64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, (*pbuflength));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(&BHarrayhead, flstrbufid, (sizeof(Freeablelstringarrayheader) + (1 * sizeof(UINT64))));
    
    if (x != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case, index 1's next free pointer is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)dg_freeablelstringlastfreeid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     // now freeing index 0
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, 0); // freeing lstring 0 of 0, free, 2
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, got errors freeing new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, first free id was not changed from 1\n ");
    }
    
    if ((*pbuflength) != (sizeof(Freeablelstringarrayheader) + 3 * sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, lstring free index buffer length is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, sizeof(Freeablelstringarrayheader) + (3 * sizeof(UINT64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, (*pbuflength));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(&BHarrayhead, flstrbufid, (sizeof(Freeablelstringarrayheader) + (1 * sizeof(UINT64))));
    
    if (x != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, index 1's next free pointer is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)dg_freeablelstringlastfreeid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(&BHarrayhead, flstrbufid, (sizeof(Freeablelstringarrayheader) + (0 * sizeof(UINT64))));
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing index not at end of list success case 2, index 1's next free pointer is not as expected. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // freeing an already free index fail case
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, 0); // trying to free lstring 0 of free, free, 2
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freefreeablelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing an already free index fail case, got wrong error on top expected dg_freefreeablelstringname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_alreadyfreeerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing an already free index fail case, got wrong error 1 below top expected dg_alreadyfreeerror, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // freeing an index off end fail case
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, 3); // trying to free lstring 3 of free, free, 2
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freefreeablelstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing an index off end fail case, got wrong error on top expected dg_freefreeablelstringname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_lstringidtoohigherror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstring - freeing an index off end fail case, got wrong error 1 below top expected dg_lstringidtoohigherror, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_isfreeablelstringfree()
{
    Bufferhandle BHarrayhead;
    
    UINT64 flstrbufid;
    UINT64 flstrid;
    UINT64 isfreeflag;
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_isfreeablelstringfree\n");

#ifndef DGLU_NO_DIAPER    
    // index off end case - should return is free and no error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - index off end case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - index off end case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - index off end case, got errors checking free status of freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (isfreeflag != FORTH_TRUE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - index off end case, freeable lstring was free\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case not free
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case not free, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case not free, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        flstrid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case not free, got errors checking free status of freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (isfreeflag != FORTH_FALSE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case not free, freeable lstring was not free\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success case free
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case free, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case free, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, flstrid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case free, got errors freeing freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        flstrid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case free, got errors checking free status of freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (isfreeflag == FORTH_FALSE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case free, freeable lstring was free\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success case multiple freeable lstrings
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors making new freeable lstring 0 - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors making new freeable lstring 1 - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstrid = dg_newfreeablelstring (&BHarrayhead, flstrbufid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors making new freeable lstring 2 - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_freefreeablelstring(&BHarrayhead, flstrbufid, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors freeing freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, got errors checking free status of freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (isfreeflag != FORTH_FALSE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, freeable lstring 0 was free\n");
    }
    
    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        1);
    
    if (isfreeflag == FORTH_FALSE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, freeable lstring 1 was not free\n");
    }
    
    isfreeflag = dg_isfreeablelstringfree(
        &BHarrayhead,
        flstrbufid,
        2);
    
    if (isfreeflag != FORTH_FALSE) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_isfreeablelstringfree - success case multiple freeable lstrings, freeable lstring 2 was free\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getsflstrheader()
{
    Bufferhandle BHarrayhead;
    
    Freeablelstringarrayheader* pflstrah;
    UINT64 myflstrheaderlength;
    UINT64 freeindexbuffer = (UINT64)dg_badbufferid;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getsflstrheader\n");

#ifndef DGLU_NO_DIAPER    
    // bad pflstrheaderlength case
    //dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        (UINT64*)badbufferhandle);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getsflstrheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - bad pflstrheaderlength case, got wrong error on top expected dg_getsflstrheadername, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - bad pflstrheaderlength case, got wrong error 1 below top expected dg_putuint32name, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmemoryerror) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - bad pflstrheaderlength case, got wrong error 2 below top expected dg_badmemoryerror, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
    

    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = (UINT64)dg_badbufferid;
    
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrheaderlength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getsflstrheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - bad free index buffer case, got wrong error on top expected dg_getsflstrheadername, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - bad free index buffer case, got wrong error on top expected dg_getpbuffersegmentname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
#endif    
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - success case , got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrheaderlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - success case , got errors getting s of freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    if (pflstrah->magic != dg_freeablelstringheadermagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - success case , freeable lstring array header magic not correct\n");
    }
    
    if (myflstrheaderlength != sizeof(Freeablelstringarrayheader))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getsflstrheader - success case , got wrong freeable lstring array header length, got - ");
        dg_writestdoutuinttodec(&BHarrayhead, myflstrheaderlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
            
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copyflstrheadertos()
{
    Bufferhandle BHarrayhead;
    
    Freeablelstringarrayheader* pflstrah;
    UINT64 myflstrheaderlength;
    UINT64 freeindexbuffer = (UINT64)dg_badbufferid;
    Freeablelstringarrayheader myflstrah;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copyflstrheadertos\n");

#ifndef DGLU_NO_DIAPER    
    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = (UINT64)dg_badbufferid;
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrah,
        sizeof(Freeablelstringarrayheader));
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - bad free index buffer case, got wrong error on top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif    

    // bad magic case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - bad magic case , got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrheaderlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - bad magic case , got errors getting s of freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    pflstrah->magic = 0;
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrah,
        sizeof(Freeablelstringarrayheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - bad magic case, got wrong error on top expected dg_getsflstrheadername, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - bad magic case, got wrong error 1 below top expected dg_badmagicerror, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - success case , got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - success case , got errors copyig header of freeable lstring array to s - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    if (myflstrah.magic != dg_freeablelstringheadermagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copyflstrheadertos - success case , freeable lstring array header magic not correct\n");
    }
            
    dg_freeallbuffers(&BHarrayhead);
}
        

void testdg_insertsintoflstrn()
{
    Bufferhandle BHarrayhead;
    
    Freeablelstringarrayheader* pflstrah;
    UINT64 myflstrheaderlength;
    
    UINT64 freeindexbuffer = (UINT32)dg_badbufferid;
    UINT64 flstringid = 0;
    
    UINT64 x;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_insertsintoflstrn\n");

#ifndef DGLU_NO_DIAPER    
    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = (UINT64)dg_badbufferid;
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        0, // flstringid
        0, // offset
        (unsigned char*)"potatoes",
        8); // length
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_insertsintoflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - bad free index buffer case, got wrong error on top expected dg_insertsintoflstrnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - bad free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif
    
    // bad magic case already tested in dg_copyflstrheadertos
    
    // error inserting in lstring n (freeablelstring n doesn't exist)
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case free, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case free, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        1, // flstringid
        0, // offset
        (unsigned char*)"potatoes",
        8); // length
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_insertsintoflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - error inserting in lstring n case, got wrong error on top expected dg_insertsintoflstrnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_insertinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - error inserting in lstring n case, got wrong error on top expected dg_insertinlstringname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case free, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case free, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        flstringid,
        0, // offset
        (unsigned char*)"potatoes",
        8); // length
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors inserting s in a freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    // check length
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrheaderlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors getting pointer to header of freeable lstring array to s - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    x = dg_getlstringlength (
        &BHarrayhead,
        pflstrah->lstringoffsetbufferid,
        0);
        
    if (x != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got wrong freeable lstring length expected 8, got - ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    // check value
    plstring = dg_getplstring(
        &BHarrayhead,
        pflstrah->lstringoffsetbufferid,
        pflstrah->lstringstringbufferid,
        0, // stringid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors getting pointer to lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (plstring[0] != 'p')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got wrong character at lstring[0]\n");
    }
    
    if (plstring[7] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got wrong character at lstring[7]\n");
    }
    
    // insert another string at a non zero offset
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        flstringid,
        4, // offset
        (unsigned char*)"moo",
        3); // length
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors inserting second s in a freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    // check length
    pflstrah = dg_getsflstrheader(
        &BHarrayhead,
        freeindexbuffer,
        &myflstrheaderlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors getting second pointer to header of freeable lstring array to s - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    x = dg_getlstringlength (
        &BHarrayhead,
        pflstrah->lstringoffsetbufferid,
        0);
        
    if (x != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got wrong freeable lstring length second time expected 11, got - ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    // check value
    plstring = dg_getplstring(
        &BHarrayhead,
        pflstrah->lstringoffsetbufferid,
        pflstrah->lstringstringbufferid,
        0, // stringid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , got errors getting pointer to lstring second time - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (plstring[4] != 'm')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , second time - got wrong character at lstring[4]\n");
    }
    
    if (plstring[6] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , second time got wrong character at lstring[6]\n");
    }
    
    if (plstring[7] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , second time got wrong character at lstring[7]\n");
    }
    
    if (plstring[10] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertsintoflstrn - success case , second time got wrong character at lstring[10]\n");
    }
            
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_copysfromflstrn()
{
    Bufferhandle BHarrayhead;
    
    UINT64 freeindexbuffer = (UINT64)dg_badbufferid;
    UINT64 flstringid = 0;
    
    unsigned char pdest[30];
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copysfromflstrn\n");

#ifndef DGLU_NO_DIAPER    
    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = (UINT64)dg_badbufferid;
    flstringid = 0;
    
    dg_copysfromflstrn(
        &BHarrayhead,
        (UINT64)freeindexbuffer,
        flstringid, // flstringid,
        0, // offset,
        1, // length,
        (unsigned char*)pdest); // pdest);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - bad free index buffer case, got wrong error on top expected dg_copysfromflstrnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - bad free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // error doing copy case - using bad index
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - error doing copy case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringid = 0;
    
    dg_copysfromflstrn(
        &BHarrayhead,
        (UINT64)freeindexbuffer,
        flstringid, // flstringid,
        2, // offset,
        3, // length,
        (unsigned char*)pdest); // pdest);
 
                               
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - error doing copy case, got wrong error on top expected dg_copysfromflstrnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - error doing copy case, got wrong error 1 below top expected dg_copysfromlstringnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_freeallbuffers(&BHarrayhead);
#endif    
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffer = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case free, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case free, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_movebytes(
        (unsigned char*)"abcdefghij",
        (unsigned char*)pdest,
        10);
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        flstringid,
        0, // offset
        (unsigned char*)"moose",
        5); // length

    
    dg_copysfromflstrn(
        &BHarrayhead,
        (UINT64)freeindexbuffer,
        flstringid, // flstringid,
        2, // offset,
        3, // length,
        (unsigned char*)pdest); // pdest);
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case , got errors copying s from a freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (pdest[0] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case , got wrong character at dest[0]\n");
    }
    
    if (pdest[1] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case , got wrong character at dest[1]\n");
    }
    
    if (pdest[2] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case , got wrong character at dest[2]\n");
    }
    
    if (pdest[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case , got wrong character at dest[3]\n");
    }
    
    // success 2 trying with non zero flstring index
    flstringid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_movebytes(
        (unsigned char*)"abcdefghij",
        (unsigned char*)pdest,
        10);
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffer,
        flstringid,
        0, // offset
        (unsigned char*)"potatoes",
        8); // length
        
    
    dg_copysfromflstrn(
        &BHarrayhead,
        (UINT64)freeindexbuffer,
        flstringid, // flstringid,
        4, // offset,
        3, // length,
        (unsigned char*)pdest); // pdest);
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got errors copying s from a freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    if (pdest[0] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got wrong character at dest[0]\n");
    }
    
    if (pdest[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got wrong character at dest[1]\n");
    }
    
    if (pdest[2] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got wrong character at dest[2]\n");
    }
    
    if (pdest[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copysfromflstrn - success case 2, got wrong character at dest[3]\n");
    }
}
    

void testdg_copytoinsertflstrntom()
{
    Bufferhandle BHarrayhead;
    
    UINT64 freeindexbuffern = (UINT64)dg_badbufferid;
    UINT64 freeindexbufferm = (UINT64)dg_badbufferid;
    UINT64 flstringnid = 0;
    UINT64 flstringmid = 0;
    
    unsigned char pdest[30];
    
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copytoinsertflstrntom\n");

#ifndef DGLU_NO_DIAPER    
    // bad source free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbufferm = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad source free index buffer case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringmid = dg_newfreeablelstring (&BHarrayhead, freeindexbufferm);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad source free index buffer case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    freeindexbuffern = (UINT64)dg_badbufferid;
    flstringnid = 0;
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbufferm,
        flstringmid,
        0, // offset
        (unsigned char*)"moose",
        5); // length
    
    dg_copytoinsertflstrntom(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offsetn,
        freeindexbufferm,
        flstringmid,
        0, // offsetm,
        2); // length);   
         
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copytoinsertflstrntomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad source free index buffer case, got wrong error on top expected dg_copytoinsertflstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad source free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // bad destination free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad destination free index buffer case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad destination free index buffer case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    freeindexbufferm = (UINT64)dg_badbufferid;
    flstringmid = 0;
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset
        (unsigned char*)"moose",
        5); // length
        
    dg_copytoinsertflstrntom(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offsetn,
        freeindexbufferm,
        flstringmid,
        0, // offsetm,
        2); // length);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copytoinsertflstrntomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad destination free index buffer case, got wrong error on top expected dg_copytoinsertflstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - bad destination free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    
    // error doing copy to insert case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbufferm = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringmid = dg_newfreeablelstring (&BHarrayhead, freeindexbufferm);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbufferm,
        flstringmid,
        0, // offset
        (unsigned char*)"elephant",
        8); // length
        
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset
        (unsigned char*)"moose",
        5); // length

        
    dg_copytoinsertflstrntom(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid + 1,
        0, // offsetn,
        freeindexbufferm,
        flstringmid,
        0, // offsetm,
        2); // length);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copytoinsertflstrntomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got wrong error on top expected dg_copytoinsertflstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copytoinsertlstrntomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - error doing copy to insert case, got wrong error 1 below top expected dg_copytoinsertlstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);
#endif

    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbufferm = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringmid = dg_newfreeablelstring (&BHarrayhead, freeindexbufferm);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbufferm,
        flstringmid,
        0, // offset
        (unsigned char*)"elephant",
        8); // length
        
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset
        (unsigned char*)"moose",
        5); // length

        
    dg_copytoinsertflstrntom(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        2, // offsetn,
        freeindexbufferm,
        flstringmid,
        1, // offsetm,
        3); // length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got errors copying to insert in freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    // add test to check destination string
    dg_copysfromflstrn(
        &BHarrayhead,
        freeindexbufferm,
        flstringmid, // flstringid,
        0, // offset,
        5, // length,
        (unsigned char*)pdest); // pdest);
        
    if (pdest[0] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got wrong character at dest[0]\n");
    }
    
    if (pdest[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got wrong character at dest[1]\n");
    }
    
    if (pdest[2] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got wrong character at dest[2]\n");
    }
    
    if (pdest[3] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got wrong character at dest[3]\n");
    }
    
    if (pdest[4] != 'l')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_copytoinsertflstrntom - success case, got wrong character at dest[4]\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_deleteinflstringn()
{
    Bufferhandle BHarrayhead;
    
    UINT64 freeindexbuffern = (UINT64)dg_badbufferid;
    
    UINT64 flstringnid = 0;
    
    const char* pError;
    
    unsigned char pdest[30];

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_deleteinflstringn\n");

#ifndef DGLU_NO_DIAPER    
    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = (UINT64)dg_badbufferid;
    flstringnid = 0;
    
    dg_deleteinflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset,
        2); // length);
         
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_deleteinflstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad free index buffer case, got wrong error on top expected dg_copytoinsertflstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // bad flstring index case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad flstring index case, got errors making new freeable lstring array - got\n");
		/// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad flstring index case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_deleteinflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid + 1,
        0, // offset,
        2); // length);
         
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_deleteinflstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad free index buffer case, got wrong error on top expected dg_copytoinsertflstrntomname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_deleteinlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - bad free index buffer case, got wrong error 1 below top expected dg_deleteinlstringname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset
        (unsigned char*)"morsel",
        6); // length
    
    dg_deleteinflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        1, // UINT32 offset,
        3); // UINT32 length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got errors deleting in freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }

    // add test to check destination string
    dg_copysfromflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid, // flstringid,
        0, // offset,
        3, // length,
        (unsigned char*)pdest); // pdest);
        
    if (pdest[0] != 'm')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got wrong character at dest[0]\n");
    }
    
    if (pdest[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got wrong character at dest[1]\n");
    }
    
    if (pdest[2] != 'l')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinflstringn - success case, got wrong character at dest[2]\n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getlengthflstringn()
{
    Bufferhandle BHarrayhead;
    
    UINT64 freeindexbuffern = (UINT64)dg_badbufferid;
    
    UINT64 flstringnid = 0;
    
    UINT64 length = 0;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getlengthflstringn\n");

#ifndef DGLU_NO_DIAPER    
    // bad free index buffer case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad free index buffer case, got wrong error initializing error stack, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    freeindexbuffern = (UINT64)dg_badbufferid;
    flstringnid = 0;
    
    length = dg_getlengthflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid);
         
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getlengthflstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad free index buffer case, got wrong error on top expected dg_getlengthflstringnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad free index buffer case, got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // bad flstring index case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad flstring index case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad flstring index case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    length = dg_getlengthflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid+1);
                 
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getlengthflstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad flstring index case, got wrong error on top expected dg_getlengthflstringnname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getlstringlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - bad flstring index case, got wrong error 1 below top expected dg_getlstringlengthname, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
#endif
    
    // success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    freeindexbuffern = dg_newfreeablelstringarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) !=0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got errors making new freeable lstring array - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    flstringnid = dg_newfreeablelstring (&BHarrayhead, freeindexbuffern);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got errors making new freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_insertsintoflstrn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid,
        0, // offset
        (unsigned char*)"morsel",
        6); // length
    
    length = dg_getlengthflstringn(
        &BHarrayhead,
        freeindexbuffern,
        flstringnid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got errors getting length of freeable lstring - got\n");
		// dg_forthdoterrors(&BHarrayhead);
    }
        
    if (length != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthflstringn - success case, got wrong length, expected 6\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_newfreeablelstringonend()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 flstrbufid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    Freeablelstringarrayheader* pheader;
    UINT64 lstringoffsetbufid;
    UINT64 lstringstringbufid;
    UINT64 myfirstfreeid;
    
    UINT64 flstrid;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    INT64 compareflag;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newfreeablelstringonend\n");


    // making freeable lstring array for test
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    flstrbufid = dg_newfreeablelstringarray(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - success case, got error making new freeable lstring array - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // empty array success case
    flstrid = dg_newfreeablelstringonend (
        &BHarrayhead,
        flstrbufid,
        (unsigned char*)"lentils",
        7);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, got error making new freeable lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (flstrid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, returned lstring index incorrect\n ");
    }
    
    // none were free, so first free should still point to end of list
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, first free id was changed from end of list\n ");
    }
    
    if (*((UINT64*)(pbuf + sizeof(Freeablelstringarrayheader))) != (UINT64)dg_freeablelstringisnotfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, lstring is not marked as not free\n ");
    }
    
    if (*pbuflength != (sizeof(Freeablelstringarrayheader) + sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - empty array success case, lstring free index buffer length is not as expected\n ");
    }
    
    // non empty array none free success case
    flstrid = flstrid = dg_newfreeablelstringonend (
        &BHarrayhead,
        flstrbufid,
        (unsigned char*)"pizza",
        5);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, got error making new freeable lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (flstrid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, returned lstring index incorrect\n ");
    }
    
    // none were free, so first free should still point to end of list
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != (UINT64)dg_freeablelstringlastfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, first free id was changed from end of list\n ");
    }
    
    if (*((UINT64*)(pbuf + sizeof(Freeablelstringarrayheader) + sizeof(UINT64))) != (UINT64)dg_freeablelstringisnotfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, lstring is not marked as not free\n ");
    }
    
    if (*pbuflength != (sizeof(Freeablelstringarrayheader) + (2*sizeof(UINT64))))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - non empty array none free success case, lstring free index buffer length is not as expected\n ");
    }
    
    // one free case
    dg_freefreeablelstring(
        &BHarrayhead,
        flstrbufid,
        0);
        
    flstrid = flstrid = dg_newfreeablelstringonend (
        &BHarrayhead,
        flstrbufid,
        (unsigned char*)"jig",
        3);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, got error making new freeable lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (flstrid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, returned lstring index incorrect\n ");
    }
    
    //  one was free, so first free should still point to it
    pbuf = dg_getpbuffer(&BHarrayhead, flstrbufid, &pbuflength);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, got error getting pointer to free index buffer, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pheader = (Freeablelstringarrayheader*)pbuf;
    lstringoffsetbufid = pheader->lstringoffsetbufferid;
    lstringstringbufid = pheader->lstringstringbufferid;
    myfirstfreeid = pheader->firstfreeid;
    
    if (myfirstfreeid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, first free id was not 0 as expected\n ");
    }
    
    if (*((UINT64*)(pbuf + sizeof(Freeablelstringarrayheader) + 2*sizeof(UINT64))) != (UINT64)dg_freeablelstringisnotfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, lstring is not marked as not free\n ");
    }
    
    if (*pbuflength != (sizeof(Freeablelstringarrayheader) + (3*sizeof(UINT64))))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, lstring free index buffer length is not as expected\n ");
    } 
    
    plstring = dg_getplstring(
        &BHarrayhead,
        lstringoffsetbufid,
        lstringstringbufid,
        2,
        &lstringlength);
        
    pError = dg_comparebytes((unsigned char*)"jig", 3, plstring, lstringlength, &compareflag);
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newfreeablelstringonend - one free case success case, lstring pushed is not correct\n ");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_comparestolstringn()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
        
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 n;
    
    INT64 compareflag;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_comparestolstringn\n");

    // success match case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Brain");

    plstring = (unsigned char*)"Pinky";
    lstringlength = 5;
    n = 1;
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success match case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    compareflag = dg_comparestolstringn (
        &BHarrayhead,
        plstring,
        lstringlength,
        lstringoffsetbufferid, 
        lstringstringbufferid,
        n);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success match case, got error comparing s to lstring n - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success match case, got wrong compare flag, expected 0 for equals - got ");
		dg_writestdoutuinttodec(&BHarrayhead, (UINT32)compareflag);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
    
    // success less than case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Brain");

    plstring = (unsigned char*)"Brai";
    lstringlength = 4;
    n = 2;
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success less than case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    compareflag = dg_comparestolstringn (
        &BHarrayhead,
        plstring,
        lstringlength,
        lstringoffsetbufferid, 
        lstringstringbufferid,
        n);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success less than case, got error comparing s to lstring n - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success less than case, got wrong compare flag, expected -1 for less than - got ");
		dg_writestdoutuinttodec(&BHarrayhead, (UINT32)compareflag);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
    
    // success greater than case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Brain");

    plstring = (unsigned char*)"Heys";
    lstringlength = 4;
    n = 0;
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success greater than case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    compareflag = dg_comparestolstringn (
        &BHarrayhead,
        plstring,
        lstringlength,
        lstringoffsetbufferid, 
        lstringstringbufferid,
        n);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success greater than case, got error comparing s to lstring n - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_comparestolstringn - success greater than case, got wrong compare flag, expected 1 for greater than - got ");
		dg_writestdoutuinttodec(&BHarrayhead, (UINT32)compareflag);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_deleteuint64inlstringn()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
        
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 value;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_deleteuint64inlstringn\n");

    // success found case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 0, (unsigned char*)"");
    
    value = 0x1122334451617181;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0x5566778852627282;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0x99AABBCC93837263;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0x5566778852627282;
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success found case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_deleteuint64inlstringn (
        &BHarrayhead, 
        lstringoffsetbufferid,
        lstringstringbufferid,
        2,
        value);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success found case, got error deleting uint32 in lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getplstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        2,
        &lstringlength);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success found case, got error getting pointer to lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    value = ((UINT64*)plstring)[0];
    
    if (value != 0x1122334451617181)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success found case, got wrong value, expected 0x1122334451617181 - got ");
		dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)value);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    value = ((UINT64*)plstring)[1];
    
    if (value != 0x99AABBCC93837263)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success found case, got wrong value, expected 0x99AABBCC93837263 - got ");
		dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)value);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
                
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success not found case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 0, (unsigned char*)"");
    
    value = 0x1122334451617181;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0x5566778852627282;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0x99AABBCC93837263;
    
    dg_stotoplstring (
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        sizeof(UINT64),
        (unsigned char*)&value);
        
    value = 0xDDEEFF21;
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_deleteuint64inlstringn (
        &BHarrayhead, 
        lstringoffsetbufferid,
        lstringstringbufferid,
        2,
        value);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got error deleting uint32 in lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getplstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        2,
        &lstringlength);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got error getting pointer to lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    value = ((UINT64*)plstring)[0];
    
    if (value != 0x1122334451617181)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got wrong value, expected 0x1122334451617181 - got ");
		dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)value);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    value = ((UINT64*)plstring)[1];
    
    if (value != 0x5566778852627282)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got wrong value, expected 0x5566778852627282 - got ");
		dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)value);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    value = ((UINT64*)plstring)[2];
    
    if (value != 0x99AABBCC93837263)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteuint64inlstringn - success not found case, got wrong value, expected 0x99AABBCC93837263 - got ");
		dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)value);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
                
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_insertwithcfillinlstringn()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    UINT64 lstringindex;
    UINT64 lstringoffset;
        
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 n;
    unsigned char cvalue;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_insertwithcfillinlstringn\n");

    // success found case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    lstringoffsetbufferid = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE); // lstring offset buffer
    lstringstringbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE); // lstring string buffer

    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 3, (unsigned char*)"Hey");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 5, (unsigned char*)"Pinky");
    dg_pushlstring(&BHarrayhead, lstringoffsetbufferid, lstringstringbufferid, 6, (unsigned char*)"Brains");
        
    pError = dg_poperror(&BHarrayhead);
    
    cvalue = 'x';
    n = 3,
    lstringindex = 1;
    lstringoffset = 2;
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got error making lstring arrays - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertwithcfillinlstringn (
        &BHarrayhead, 
        lstringoffsetbufferid, 
        lstringstringbufferid,
        lstringindex, // lstringindex,
        lstringoffset, // offset,
        n, // length,
        cvalue);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got error inserting and filling in lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getplstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        &lstringlength);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got error getting pointer to lstring - got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[0];
    
    if (cvalue != 'P')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[0], expected 'P' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[1];
    
    if (cvalue != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[1], expected 'i' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[2];
    
    if (cvalue != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[2], expected 'x' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[3];
    
    if (cvalue != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[3], expected 'x' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[4];
    
    if (cvalue != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[4], expected 'x' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    cvalue = plstring[5];
    
    if (cvalue != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_insertwithcfillinlstringn - success found case, got wrong value at lstring[5], expected 'n' - got ");
		dg_writestdoutraw(&BHarrayhead, (unsigned char*)&cvalue, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
                                    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_packlstring()
{
    Bufferhandle BHarrayhead;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    INT64 compareflag;
    
    UINT64 x;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_packlstring\n");
    
    // success empty lstring stack case
    
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    // dg_initvariables(&BHarrayhead);
    
    lstringoffsetbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error making new lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringstringbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error making new lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_packlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error packing the lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        lstringstringbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error getting pointer to lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes(
        (unsigned char*)dg_packedlstringmagicstring,
        dg_packedlstringmagicstringlength,
        pbuffer,
        dg_packedlstringmagicstringlength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error getting comparing magic string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - one free case success case, lstring pushed is not correct\n ");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringstringbufferid,
        dg_packedlstringmagicstringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error getting buffer length from string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != *pbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got wrong length at end of string buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringoffsetbufferid,
        0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got an error getting buffer length from offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != *pbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success empty lstring stack case - got wrong length at end of offset buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 3 lstrings on stack case
    
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    // dg_initvariables(&BHarrayhead);
    
    lstringoffsetbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error making new lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringstringbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error making new lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        3,
        (unsigned char*)"abc");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pushing 1st lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        5,
        (unsigned char*)"defgh");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pushing 2nd lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        1,
        (unsigned char*)"i");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pushing 2nd lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_packlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error packing lstring stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        lstringstringbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pointer to lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes(
        (unsigned char*)dg_packedlstringmagicstring,
        dg_packedlstringmagicstringlength,
        pbuffer + 9,
        dg_packedlstringmagicstringlength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting comparing magic string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - one free case success case, lstring pushed is not correct\n ");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringstringbufferid,
        (3 * sizeof(UINT64)) + 9 + dg_packedlstringmagicstringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting buffer length from string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != *pbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong length at end of string buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringoffsetbufferid,
        3 * sizeof(UINT64));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting buffer length from offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != *pbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong length at end of offset buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_packedlstringmagicstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringstringbufferid,
        (0 * sizeof(UINT64)) + 9 + dg_packedlstringmagicstringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting 1st end offset from offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong 1st end offset in offset buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringstringbufferid,
        (1 * sizeof(UINT64)) + 9 + dg_packedlstringmagicstringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting 2nd end offset from offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong 2nd end offset in offset buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 8);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        lstringstringbufferid,
        (2 * sizeof(UINT64)) + 9 + dg_packedlstringmagicstringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting 3rd end offset from offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong 3rd end offset in offset buffer wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 9);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // this should return the lstring array to it's pre packed state
    dg_droplstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error doing droplstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        lstringstringbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pointer to lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*pbufferlength != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong string buffer length after droplstring got ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 9);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        lstringoffsetbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got an error getting pointer to lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*pbufferlength != (3 * sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packlstring success 3 lstrings on stack case - got wrong offset buffer length after droplstring got ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, (3 * sizeof(UINT64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_unpacklstring()
{
    Bufferhandle BHarrayhead;
    
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    UINT64 lstringoffsetbufferid2;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    unsigned char* pbuffer2;
    UINT64* pbuffer2length;
    
    INT64 compareflag;
    
    UINT64 x;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_unpacklstring\n");
    
    // success empty lstring stack case
    
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    // dg_initvariables(&BHarrayhead);
    
    lstringoffsetbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - got an error making new lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringstringbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - got an error making new lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_packlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - got an error packing the lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringoffsetbufferid2 = dg_unpacklstring(
        &BHarrayhead,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - got an error unpacking the lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        // dg_forthdoterrors(&BHarrayhead);
    }
    
    x = dg_getbufferlength(&BHarrayhead, lstringstringbufferid);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - string buffer length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead,x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 0);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, lstringoffsetbufferid2);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL undg_packlstring success empty lstring stack case - offset buffer length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead,x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 0);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // dg_unpacklstring 3 strings on lstring stack success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    // dg_initvariables(&BHarrayhead);
    
    lstringoffsetbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error making new lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringstringbufferid = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error making new lstring string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        3,
        (unsigned char*)"abc");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error getting pushing 1st lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        5,
        (unsigned char*)"defgh");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error getting pushing 2nd lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        1,
        (unsigned char*)"i");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error getting pushing 2nd lstring onto stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_packlstring(
        &BHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error packing the lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    lstringoffsetbufferid2 = dg_unpacklstring(
        &BHarrayhead,
        lstringstringbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error unpacking the lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        // dg_forthdoterrors(&BHarrayhead);
    }
    
    // the two offset buffers should now be identical
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        lstringoffsetbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error getting pointer to lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffer2 = dg_getpbuffer (
        &BHarrayhead,
        lstringoffsetbufferid2,
        &pbuffer2length);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error getting pointer to lstring offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*pbufferlength != *pbuffer2length + sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - length's aren't of by 1 UINT32. offset buffer 1 length is ");
        dg_writestdoutuinttodec(&BHarrayhead,*pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" , offset buffer 2's length is ");
        dg_writestdoutuinttodec(&BHarrayhead, *pbuffer2length);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes(
        pbuffer,
        *pbufferlength - sizeof(UINT64), // have to drop length at end of buffer
        pbuffer2,
        *pbuffer2length,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - got an error comparing the offset buffers, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring 3 strings on lstring stack success case - offset buffers are not the same\n ");

    }
    
    x = dg_getbufferlength(&BHarrayhead, lstringstringbufferid);
    
    if (x != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unpacklstring success empty lstring stack case - string buffer length wrong got ");
        dg_writestdoutuinttodec(&BHarrayhead,x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 9);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

void testdg_stonewstring()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char lstring[80];
//    unsigned int stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_stonewstring\n");

    dg_initbuffers(&BHarrayhead);
    // dg_initerrors(&BHarrayhead, 100, &pError);


    // dg_success case
    lstring[0] = 'a';
    lstring[1] = 'b';
    lstring[2] = 'c';
    lstring[3] = 'd';
        
    dg_stonewstring (
        &BHarrayhead,
        lstring,
        3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewstring normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewstring normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewstring normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0) != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewstring normal case - end of string +1 offset incorrect\n");
    }
    
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_STRINGSTRINGSTACK_BUFFERID]);

    if ( ( ((unsigned char*)(pBH->pbuf))[0] != 'a') ||
         ( ((unsigned char*)(pBH->pbuf))[1] != 'b') ||
         ( ((unsigned char*)(pBH->pbuf))[2] != 'c') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewstring normal case - string not copied\n");
    }
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_stonew0string()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    unsigned char lstring[80];
//    unsigned int stringlength = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_stonew0string\n");

    dg_initbuffers(&BHarrayhead);
    // dg_initerrors(&BHarrayhead, 100, &pError);


    // dg_success case
    lstring[0] = 'a';
    lstring[1] = 'b';
    lstring[2] = 'c';
    lstring[3] = 'd';
        
    dg_stonew0string (
        &BHarrayhead,
        lstring,
        3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonew0string normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonew0string normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonew0string normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonew0string normal case - end of string +1 offset incorrect\n");
    }
    
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_STRINGSTRINGSTACK_BUFFERID]);

    if ( ( ((unsigned char*)(pBH->pbuf))[0] != 'a') ||
         ( ((unsigned char*)(pBH->pbuf))[1] != 'b') ||
         ( ((unsigned char*)(pBH->pbuf))[2] != 'c') ||
         ( ((unsigned char*)(pBH->pbuf))[3] != 0) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonew0string normal case - string not copied\n");
    }
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_dropnlstrings()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_dropnlstrings\n");

    dg_initbuffers(&BHarrayhead);


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"oh",
        2);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error pushing 2nd string to stack\n");
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"why",
        3);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error pushing third string to stack\n");
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"puppy",
        5);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error pushing fourth string to stack\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - offset buffer length incorrect\n");
    }

    if (dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0) != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - end of string +1 offset incorrect\n");
    }

    dg_clearerrors(&BHarrayhead);
    
    // underflow case
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_dropnlstringsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings underflow case - got wrong error on top \n");
    }
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_lstringstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings underflow case - got wrong error 1 below top \n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // exactly enough strings case
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings exactly enough to drop case - got error \n");
    }
    
    if (dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings exactly enough to drop case - string buffer length incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings exactly enough to drop case - offset buffer length incorrect\n");
    }
    
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_uleextendlstringntol()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_uleextendlstringntol\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case growing from 4 to 6
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleextendlstringntol (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        6); //  newlength)
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - got error unsigned extending string\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - got error getting pointer to lstring\n");
    }
    
    if (plstring[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - character before extension got changed\n");
    }
    
    if (lstringlength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - length wrong after extension\n");
    }
    
    if (plstring[4] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - 1st extended byte not 0\n");
    }
    
    if (plstring[5] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case 4 to 6 - 2nd extended byte not 0\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropnlstrings normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case not growing
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal case not growing - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleextendlstringntol (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        3); //  newlength)
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal not growing - got error unsigned extending string\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal not growing - got error getting pointer to lstring\n");
    }
    
    if (plstring[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal not growing - character before extension got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleextendlstringntol normal not growing - length wrong after extension\n");
    }
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_uleaddlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_uleaddlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case no carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleaddlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - got error doing dg_uaddlelstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 1st character of 1st string got changed\n");
    }
    
    if (plstring[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 3rd character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - length of 2nds string wrong\n");
    }
    
    if (carryout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case no carry - carryout not 0\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal with carry case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case with carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xfc\xfc\xfb",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x03\x05",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleaddlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - got error doing dg_uaddlelstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 1st character of 1st string got changed\n");
    }
    
    if (plstring[3] != 0xfb)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 3rd character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - length of 2nds string wrong\n");
    }
    
    if (carryout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal case with carry - carryout not 1\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleaddlstringntolstringn normal with carry case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_uleadclstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_uleadclstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case no carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 0;
    
    dg_uleadclstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 1st character of 1st string got changed\n");
    }
    
    if (plstring[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 3rd character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - length of 2nds string wrong\n");
    }
    
    if (carryinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case no carry - carryout not 0\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal with carry case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case with carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xfc\xfc\xfb",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x03\x05",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 1;
    
    dg_uleadclstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 1st character of 1st string got changed\n");
    }
    
    if (plstring[3] != 0xfb)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 3rd character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - length of 2nds string wrong\n");
    }
    
    if (carryinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal case with carry - carryout not 1\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleadclstringntolstringn normal with carry case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulesbblstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 borrowinout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulesbblstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case no borrow
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"abcd",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x01\x02\x01",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    borrowinout = 0;
    
    dg_ulesbblstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &borrowinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - got error doing dg_usbblelstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 1st character of 2nd string got changed\n");
    }
    
    if (plstring[3] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 4th character of 2nd string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 1st character of 1st string incorrect\n");
    }
    
    if (plstring[1] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 2nd character of 1st string incorrect\n");
    }
    
    if (plstring[2] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 3rd character of 1st string incorrect\n");
    }
    
    if (plstring[3] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - 4th character of 1st string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - length of 2nds string wrong\n");
    }
    
    if (borrowinout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case no borrow - borrowinout not 0\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal with borrow case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case with carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xfc\xfc\xfb",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x03\x05",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    borrowinout = 1;
    
    dg_ulesbblstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &borrowinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - got error doing dg_ulesbblstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 1st character of 1st string got changed\n");
    }
    
    if (plstring[3] != 0xfb)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 3rd character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 2nd character of 1st string incorrect, got %x");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
    }
    
    if (plstring[1] != 0x05)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 2nd character of 2nd string incorrect, got %x ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[2] != 0x06)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 3rd character of 2nd string incorrect, got %x ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[3] != 0x09)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - 4th character of 2nd string incorrect, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[3]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - length of 1st string wrong\n");
    }
    
    if (borrowinout != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal case with borrow - borrowinout not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulesbblstringntolstringn normal with carry borrow - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
         
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}



void testdg_uleandlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_uleandlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleandlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - got error doing dg_uandlelstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleandlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_uleorlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_uleorlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_uleorlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_uleorlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulexorlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulexorlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulexorlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexorlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulenandlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulenandlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulenandlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - got error doing dg_uandlelstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0xfe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 0xfd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenandlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulenorlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulenorlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulenorlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0xfe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0xfd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0xf8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 0xf8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulenorlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulexnorlstringntolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulexnorlstringntolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x02\x01\x03",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulexnorlstringntolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 0xfe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0xfd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0xf9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[3] != 0xfa)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulexnorlstringntolstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_notlstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_notlstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_notlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - 1st byte of 1st string got changed\n");
    }
    
    if (plstring[1] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - 2nd byte of 1st string got changed\n");
    }
    
    if (plstring[2] != 0xf8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - 3rd byte of 1st string got changed\n");
    }
    
    if (plstring[3] != 0xf9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - 4th character of 1st string got changed\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_notlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0xf6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0x8f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0xc8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0xdd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - 4th character of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_notlstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_reverselstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_reverselstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_reverselstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0x06)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0x07)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x80)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_reverselstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 0x22)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0x37)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x70)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0x09)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - 4th character of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_reverselstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_lelshiftlstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_lelshiftlstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_lelshiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - carry out not 0\n");
    }
    
    if (plstring[0] != 0x02)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x0c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x82",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_lelshiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case - carry out not 1\n");
    }
    
    if (plstring[0] != 0x12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0xe0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x6e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0x04)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - 4th byte of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftlstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_ulershiftlstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ulershiftlstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulershiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - carry out not 0\n");
    }
    
    if (plstring[0] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0xc0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x83",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_ulershiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case - carry out not 1\n");
    }
    
    if (plstring[0] != 0x04)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0xb8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x9b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0x41)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - 4th byte of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_ulershiftlstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_slershiftlstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_slershiftlstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_slershiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - carry out not 0\n");
    }
    
    if (plstring[0] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0xc0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x83",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_slershiftlstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (carryout != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case - carry out not 1\n");
    }
    
    if (plstring[0] != 0x04)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0xb8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x9b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0xc1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - 4th byte of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_slershiftlstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_lelshiftclstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_lelshiftclstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 0;
    
    dg_lelshiftclstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (carryinout != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - carry out not 0\n");
    }
    
    if (plstring[0] != 0x02)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x0c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x82",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 1;
    
    dg_lelshiftclstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (carryinout != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case - carry out not 1\n");
    }
    
    if (plstring[0] != 0x13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0xe0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x6e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0x04)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - 4th byte of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lelshiftclstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_lershiftclstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_lershiftclstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x80\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x22",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 0;
    
    dg_lershiftclstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - got error getting pointer to 1st lstring\n");
    }
    
    if (carryinout != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - carry out not 0\n");
    }
    
    if (plstring[0] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - 1st byte of 1st string not correct\n");
    }
    
    if (plstring[1] != 0xc0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - 2nd byte of 1st string not correct\n");
    }
    
    if (plstring[2] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - 3rd byte of 1st string not correct\n");
    }
    
    if (plstring[3] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - 4th character of 1st string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case 2
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x07\x06",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x09\x70\x37\x83",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    carryinout = 1;
    
    dg_lershiftclstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &carryinout);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - got error doing dg_uleorlstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - got error getting pointer to 1st lstring\n");
    }
    
    if (carryinout != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case - carry out not 1\n");
    }
    
    if (plstring[0] != 0x04)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - 1st byte of 2nd string not correct\n");
    }
    
    if (plstring[1] != 0xb8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - 2nd byte of 2nd string not correct\n");
    }
    
    if (plstring[2] != 0x9b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - 3rd byte of 2nd string not correct\n");
    }
    
    if (plstring[3] != 0xc1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - 4th byte of 2nd string not correct\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_lershiftclstringn normal case 2 - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_mulu64bylstringnaddtolstringn()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_mulu64bylstringnaddtolstringn\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // dg_success case no carry
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
        16);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal no carry case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case no carry need to align source
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00",
        4);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
        16);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align source - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal no carry case need to align source - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case no carry need to align destination
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x00",
        1);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - 4th character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case no carry need to align destination - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal no carry case need to align destination - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    // dg_success case carry when u64destlength = u64srclength + 1
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff",
        16);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 16th character of 2nd string incorrect\n");
    }
    
    if (plstring[16] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[17] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[23] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - last character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal carry when u64destlength = u64srclength + 1 case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case carry when u64destlength > u64srclength + 1
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00",
        24);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 16th character of 2nd string incorrect\n");
    }
    
    if (plstring[16] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[17] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[23] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - last character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal carry when u64destlength > u64srclength + 1 case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case carry when u64destlength > u64srclength + 1 b
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 b - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00",
        24);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 16th character of 2nd string incorrect\n");
    }
    
    if (plstring[16] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[17] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 18th character of 2nd string incorrect\n");
    }
    
    if (plstring[18] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - 19th character of 2nd string incorrect\n");
    }
    
    if (plstring[23] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - last character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // dg_success case carry when u64destlength > u64srclength + 1 c
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x01\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength = u64srclength + 1 c - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff",
        24);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error pushing 2nd string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_mulu64bylstringnaddtolstringn (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        3); // u);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - got error doing dg_uleadclstringntolstringn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 1st character of 1st string got changed\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - last character of 1st string got changed\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - length wrong\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - got error getting pointer to 2nd lstring\n");
    }
    
    if (plstring[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 1st character of 2nd string incorrect\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 2nd character of 2nd string incorrect\n");
    }
    
    if (plstring[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 3rd character of 2nd string incorrect\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 16th character of 2nd string incorrect\n");
    }
    
    if (plstring[16] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 17th character of 2nd string incorrect\n");
    }
    
    if (plstring[17] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 18th character of 2nd string incorrect\n");
    }
    
    if (plstring[18] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 19th character of 2nd string incorrect\n");
    }
    
    if (plstring[23] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 24th character of 2nd string incorrect\n");
    }
    
    if (plstring[24] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 25th character of 2nd string incorrect\n");
    }
    
    if (plstring[25] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - 26th character of 2nd string incorrect\n");
    }
    
    if (plstring[31] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - last character of 2nd string incorrect\n");
    }
    
    if (lstringlength != 32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 c - length of 2nds string wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mulu64bylstringnaddtolstringn normal case carry when u64destlength > u64srclength + 1 b - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
        
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_divlstringnbyu64()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 remainder;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_divlstringnbyu64\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // success case one uint64 already aligned
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x0f\x00\x00\x00\x00\x00\x00\x00",
        8);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_divlstringnbyu64 (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,  // stringida
        3,  // u
        &remainder);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - got error doing dg_divlstringnbyu64, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - 1st character of 1st string wrong\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - 2nd character of 1st string wrong\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - last character of 1st string wrong\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 already aligned - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    
    // success case one uint64 not aligned
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x0f\x00\x00\x00\x00\x00\x00\x00",
        1);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_divlstringnbyu64 (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,  // stringida
        3,  // u
        &remainder);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - got error doing dg_divlstringnbyu64, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - 1st character of 1st string wrong\n");
    }
    
    if (plstring[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - 2nd character of 1st string wrong\n");
    }
    
    if (plstring[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - last character of 1st string wrong\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case one uint64 not aligned - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
    
    // success case two uint64s already aligned
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x06\x00\x00\x00\x00\x00\x00\x00\xfb\xff\xff\xff\xff\xff\xff\xff",
        16);
        
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - got error pushing 1st string to stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_divlstringnbyu64 (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,  // stringida
        (UINT64)-2,  // u
        &remainder);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - got error doing dg_divlstringnbyu64, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
		&lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - got error getting pointer to 1st lstring\n");
    }
    
    if (plstring[0] != (unsigned char)-3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - 1st character of 1st string got changed, expected -3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[0]);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[1] != (unsigned char)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - 2nd character of 1st string got changed, expected -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[1]);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[7] != (unsigned char)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - 8th character of 1st string wrong, expected -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[7]);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[15] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - last character of 1st string wrong, expected 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[15]);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_divlstringnbyu64 success case two uint64s already aligned - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
        
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_fescdecodelstring()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_fescdecodelstring\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\\z\\a\\b\\t\\l\\v\\f\\r\\e\\q\\\\\\m\\0\\n\\'\\?abc\\x98\\wz\\",
        43);

    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - got error pushing encoded string to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }

    dg_fescdecodelstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);
      
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - got error doing dg_fescencodelstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        &lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - got error getting pointer to 1st lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    if (plstring[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 1st character of 1st string wrong\n");
    }

    if (plstring[1] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 2nd character of 1st string wrong\n");
    }

    if (plstring[2] != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 3rd character of 1st string wrong\n");
    }

    if (plstring[3] != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 4th character of 1st string wrong\n");
    }

    if (plstring[4] != 0x0a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 5th character of 1st string wrong\n");
    }

    if (plstring[5] != 0x0b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 6th character of 1st string wrong\n");
    }

    if (plstring[6] != 0x0c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 7th character of 1st string wrong\n");
    }

    if (plstring[7] != 0x0d)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 8th character of 1st string wrong\n");
    }

    if (plstring[8] != 0x1b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 9th character of 1st string wrong\n");
    }

    if (plstring[9] != 0x22)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 10th character of 1st string wrong\n");
    }

    if (plstring[10] != 0x5c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 11th character of 1st string wrong\n");
    }

    if (plstring[11] != 0x0d)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 12th character of 1st string wrong\n");
    }

    if (plstring[12] != 0x0a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 13th character of 1st string wrong\n");
    }

    if (plstring[13] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 14th character of 1st string wrong\n");
    }

    if (plstring[14] != 0x0a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 15th character of 1st string wrong\n");
    }

    if (plstring[15] != 0x27)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 16th character of 1st string wrong\n");
    }

    if (plstring[16] != 0x3f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 17th character of 1st string wrong\n");
    }

    if (plstring[17] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 18th character of 1st string wrong\n");
    }

    if (plstring[18] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 19th character of 1st string wrong\n");
    }

    if (plstring[19] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 20th character of 1st string wrong\n");
    }

    if (plstring[20] != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 21th character of 1st string wrong\n");
    }

    if (plstring[21] != '-')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 22th character of 1st string wrong\n");
    }

    if (plstring[22] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 23th character of 1st string wrong\n");
    }

    if (plstring[23] != '-')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 24th character of 1st string wrong\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - length wrong\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
        
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_fescencodelstring()
{
    const char* pError = NULL;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_fescencodelstring\n");

    dg_initbuffers(&BHarrayhead); // gonna use the string stack for testing


    // success case
    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"\x07\x07\x08\x09\x08\x0b\x0c\x0d\x1b\x22\x5c\x61\x01\x62\x7F\xFF\x00\x0a",
        18);

    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstringsuccess case - got error pushing encoded string to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }

    dg_fescencodelstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);
      
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - got error doing dg_fescencodelstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        &lstringlength);
  
    pError = dg_poperror(&BHarrayhead);
        
    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - got error getting pointer to 1st lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    if (plstring[0] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 1st character of 1st string wrong\n");
    }

    if (plstring[1] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 2nd character of 1st string wrong\n");
    }

    if (plstring[2] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 3rd character of 1st string wrong, expected \\, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (plstring[3] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 4th character of 1st string wrong\n");
    }

    if (plstring[4] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 5th character of 1st string wrong\n");
    }

    if (plstring[5] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 6th character of 1st string wrong\n");
    }

    if (plstring[6] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 7th character of 1st string wrong\n");
    }

    if (plstring[7] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 8th character of 1st string wrong\n");
    }

    if (plstring[8] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 9th character of 1st string wrong\n");
    }

    if (plstring[9] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 10th character of 1st string wrong\n");
    }

    if (plstring[10] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 11th character of 1st string wrong\n");
    }

    if (plstring[11] != 'v')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 12th character of 1st string wrong\n");
    }

    if (plstring[12] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 13th character of 1st string wrong\n");
    }

    if (plstring[13] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 14th character of 1st string wrong\n");
    }

    if (plstring[14] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 15th character of 1st string wrong\n");
    }

    if (plstring[15] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 16th character of 1st string wrong\n");
    }

    if (plstring[16] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 17th character of 1st string wrong\n");
    }

    if (plstring[17] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 18th character of 1st string wrong\n");
    }

    if (plstring[18] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 19th character of 1st string wrong\n");
    }

    if (plstring[19] != '"')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 20th character of 1st string wrong\n");
    }

    if (plstring[20] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 21th character of 1st string wrong\n");
    }

    if (plstring[21] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 22th character of 1st string wrong\n");
    }

    if (plstring[22] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 23th character of 1st string wrong\n");
    }

    if (plstring[23] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 24th character of 1st string wrong\n");
    }

    if (plstring[24] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 25th character of 1st string wrong\n");
    }

    if (plstring[25] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 26th character of 1st string wrong\n");
    }

    if (plstring[26] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 27th character of 1st string wrong\n");
    }

    if (plstring[27] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 28th character of 1st string wrong\n");
    }

    if (plstring[28] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 29th character of 1st string wrong\n");
    }

    if (plstring[29] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 30th character of 1st string wrong\n");
    }

    if (plstring[30] != '7')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 31th character of 1st string wrong\n");
    }

    if (plstring[31] != 'F')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 32rd character of 1st string wrong, expected \\, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[31]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (plstring[32] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 33th character of 1st string wrong\n");
    }

    if (plstring[33] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 34th character of 1st string wrong\n");
    }

    if (plstring[34] != 'F')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 35th character of 1st string wrong\n");
    }

    if (plstring[35] != 'F')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 36rd character of 1st string wrong, expected \\, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[35]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (plstring[36] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 37rd character of 1st string wrong, expected \\, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[36]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (plstring[37] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 38th character of 1st string wrong\n");
    }

    if (plstring[38] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 39th character of 1st string wrong\n");
    }

    if (plstring[39] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 40th character of 1st string wrong\n");
    }

    if (plstring[40] != '\\')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 41rd character of 1st string wrong, expected \\, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[40]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (plstring[41] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 42th character of 1st string wrong\n");
    }

    if (plstring[42] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescdecodelstring success case - 43th character of 1st string wrong\n");
    }

    if (plstring[43] != 'A')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - 44rd character of 1st string wrong, expected 0x0A, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, plstring[43]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (lstringlength != 44)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - got wrong length\n");
    }
    
    dg_dropnlstrings(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_fescencodelstring success case - got error clearing string stack \n");
    }

    dg_clearerrors(&BHarrayhead);
        
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}
