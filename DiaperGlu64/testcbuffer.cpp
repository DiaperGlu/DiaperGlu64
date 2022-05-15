// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.3.
//
//    DiaperGlu v5.3 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.3 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.3; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// May 15, 2022               //
// version 5.3                //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_newbuffer()
{
    UINT64 tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    
    Bufferhandle* pBH;

    UINT64 i;
    UINT64 n;

    dg_printzerostring(
        &BHarrayhead,
        (unsigned char*)"\n---\ntesting dg_newbuffer\n");
 #ifndef DGLU_NO_DIAPER
    // NULL bufferhandlearrayhead case
    tbuf = dg_newbuffer(
        (Bufferhandle*)badbufferhandle, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! NULL buffer handle array head case - buffer number not max \n");
    }

    if (pError != dg_nullpbharrayheaderror) // invparmpheadnull
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! NULL buffer handle array head case - incorrect error \n");
    }
#endif

    // growby 0 case - assumes no buffer initialized prior to this call
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        0, 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! growby 0 case - buffer number not max \n");
    }

    if (pError != dg_buffergrowby0error) 
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! growby 0 case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! growby 0 case - no buffer should be initialized \n");
    }

    // maxsize < growby case - assumes no buffer initialized prior to this call
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_getpagesize() * 2, 
        dg_getpagesize(), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < growby case - buffer number not max \n");
    }

    if (pError != dg_maxsizeltgrowbyerror) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < growby case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < growby case - no buffer should be initialized \n");
    }

    // bufferhandlearray's maxsize < growby case
    BHarrayhead.growby = dg_getpagesize() * 2;
    BHarrayhead.maxsize = dg_getpagesize();

    tbuf = dg_newbuffer(
        &BHarrayhead,
        1000,
        10000,
        &pError,
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's maxsize < growby case - buffer number not max \n");
    }

    if (pError != dg_BHarraymaxsizeltgrowby) // bharraymaxsizeltbhsize
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's maxsize < growby case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's maxsize < growby case - no buffer allocated \n");
    }
    
    // bufferhandlearray's maxsize < sizeof a bufferhandle case
    BHarrayhead.growby = 10;
    BHarrayhead.maxsize = 12;

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < sizeof bufferhandle case - buffer number not max \n");
    }

    if (pError != dg_BHarraymaxsizeltbhsize) // bharraymaxsizeltbhsize
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < sizeof bufferhandle case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! maxsize < sizeof bufferhandle case - no buffer allocated \n");
    }

    // bufferhandlearray's growby = 0 case
    BHarrayhead.growby = 0;
    BHarrayhead.maxsize = 10000;

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's growby = 0 case - buffer number not max \n");
    }

    if (pError != dg_BHarraygrowby0error) // bharraygrowby0
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's growby = 0 case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! bufferhandlearray's growby = 0 case - no buffer allocated \n");
    }


    // bufferhandlearray's growby < sizeof bufferhandle case
    //   problem gets quietly fixed. It's increased to nearest pagesize larger than bufferhandle
    BHarrayhead.growby = 1;
    BHarrayhead.maxsize = BHarraymaxsize;

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby < sizeof bufferhandle case - no buffer allocated \n");
    }

    if (BHarrayhead.growby != dg_calcnearestpagesize(sizeof(Bufferhandle)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby < sizeof bufferhandle case - growby not = nearest pagesize larger than bufferhandle \n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby < sizeof bufferhandle case - got an error \n");

    }

    ::dg_freeallbuffers(&BHarrayhead);

    // 1st time call no memory for BHarray case
    // BHarray freed from previous test

    dg_initpbharrayhead(&BHarrayhead);
    
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_TRUE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call no memory for BHarray case - buffer number not max \n");
    }

    if (pError != dg_outofmemoryerror) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call no memory for BHarray case - incorrect error \n");
    }

    if (BHarrayhead.pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call no memory for BHarray case - no buffer allocated \n");
    }

    
    // 1st time call case, allocates initial buffer and puts 1st handle in
    if (BHarrayhead.pbuf != badbufferhandle) 
    {
        dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
        BHarrayhead.pbuf = badbufferhandle;
    }

    dg_initpbharrayhead(&BHarrayhead);
    
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(1000), 
        dg_calcnearestpagesize(10000), 
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - no buffer allocated \n");
    }

    if (BHarrayhead.size != BHarraygrowby)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - array size != array growby \n");
    }

    if (tbuf != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - buffer id returned not 0 \n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - error returned not dg_success \n");
    }

    if (BHarrayhead.nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - array's nextfreeindex != max index \n");
    }

    if (BHarrayhead.nextunusedbyte != sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - array's nextunusedbyte incorrect \n");
    }

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - no buffer allocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(1000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(10000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != dg_calcnearestpagesize(1000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1st time call case - buffer has incorrect size \n");
    }

    // BHarray's nextusedbyte corrupt case
    BHarrayhead.nextunusedbyte++;

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(200), 
        dg_calcnearestpagesize(19000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte corrupt case - buffer number not max \n");
    }

    if (pError != dg_BHarraynubcorrupt) // bharraynubcorrupt
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte corrupt case - incorrect error \n");
    }

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte corrupt case - no buffer allocated \n");
    }

    if (BHarrayhead.nextunusedbyte != sizeof (Bufferhandle) + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte corrupt case - array's nextunusedbyte incorrect \n");
    }

    BHarrayhead.nextunusedbyte--;


    // BHarray's nextusedbyte > size case
    BHarrayhead.nextunusedbyte = BHarrayhead.size + sizeof(Bufferhandle);

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(200), 
        dg_calcnearestpagesize(19000), 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte > size case - buffer number not max \n");
    }

    if (pError != dg_BHarraynubgtsize) // bharraynubgtsize
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte > size case - incorrect error \n");
    }

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte > size case - no buffer allocated \n");
    }

    if (BHarrayhead.nextunusedbyte != BHarrayhead.size + sizeof(Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BHarray's nextusedbyte > size case - array's nextunusedbyte incorrect \n");
    }

    BHarrayhead.nextunusedbyte = sizeof(Bufferhandle);


    // 2nd time call case, adds 2nd new handle to the buffer
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(500), 
        dg_calcnearestpagesize(20000), 
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - no buffer allocated \n");
    }

    if (BHarrayhead.size != dg_calcnearestpagesize(BHarraygrowby))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - array size != array growby \n");
    }

    if (tbuf != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - buffer id returned not 1 \n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - error returned not dg_success \n");
    }

    if (BHarrayhead.nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - array's nextfreeindex != max index \n");
    }

    if (BHarrayhead.nextunusedbyte != 2* sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - array's nextunusedbyte incorrect \n");
    }

    i=1;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - no buffer allocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(500))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(20000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != dg_calcnearestpagesize(500))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2nd time call case - buffer has incorrect size \n");
    }

    // 3rd time call case, adds 3rd new handle to the buffer
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(800), 
        dg_calcnearestpagesize(16000), 
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - no buffer allocated \n");
    }

    if (BHarrayhead.size != BHarraygrowby)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - array size != array growby \n");
    }

    if (tbuf != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - buffer id returned not 1 \n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - error returned not dg_success \n");
    }

    if (BHarrayhead.nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - array's nextfreeindex != max index \n");
    }

    if (BHarrayhead.nextunusedbyte != 3* sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - array's nextunusedbyte incorrect \n");
    }

    i=2;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - no buffer allocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(800))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(16000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != dg_calcnearestpagesize(800))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 3rd time call case - buffer has incorrect size \n");
    }

    // no memory for buffer case
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(400), 
        dg_calcnearestpagesize(17000), 
        &pError, 
        FORTH_TRUE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - no buffer allocated \n");
    }

    if (BHarrayhead.size != dg_calcnearestpagesize(BHarraygrowby))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - array size != array growby \n");
    }

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - buffer id returned not max \n");
    }

    if (pError != dg_outofmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - error returned not oombuffer \n");
    }

    if (BHarrayhead.nextfreeindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - array's nextfreeindex != 3 \n");
    }

    if (BHarrayhead.nextunusedbyte != 4* sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - array's nextunusedbyte incorrect \n");
    }

    i=3;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf != badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - buffer allocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(400))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(17000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! no memory for buffer case - buffer has incorrect size \n");
    }

    // not truly free case (there is a free handle from the last test)
    i=3;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->pbuf = BHarrayhead.pbuf;


    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(100), 
        dg_calcnearestpagesize(11000), 
        &pError, 
        FORTH_TRUE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - no buffer allocated \n");
    }

    if (BHarrayhead.size != BHarraygrowby)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - array size != array growby \n");
    }

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - buffer id returned not max \n");
    }

    if (pError != dg_bufferidisnotfree) // nottrulyfree
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - error returned not oombuffer \n");
    }

    if (BHarrayhead.nextfreeindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - array's nextfreeindex != 3 \n");
    }

    if (BHarrayhead.nextunusedbyte != 4* sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - array's nextunusedbyte incorrect \n");
    }

    i=3;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - illegal buffer was unallocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(400)) // left alone 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(17000)) // left alone
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! not truly free case - buffer has incorrect size \n");
    }

    pBH->pbuf = badbufferhandle;


    // there is a free index in the middle somewhere case
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(900), 
        dg_calcnearestpagesize(19000), 
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - no buffer allocated \n");
    }

    if (BHarrayhead.size != dg_calcnearestpagesize(BHarraygrowby))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - array size != array growby \n");
    }

    if (tbuf != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - buffer id returned not 1 \n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - error returned not dg_success \n");
    }

    if (BHarrayhead.nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - array's nextfreeindex != max index \n");
    }

    if (BHarrayhead.nextunusedbyte != 4* sizeof (Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - array's nextunusedbyte incorrect \n");
    }

    i=3;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - no buffer allocated \n");
    }

    if (pBH->growby != dg_calcnearestpagesize(900))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - buffer size incorrect \n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(19000))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - max size incorrect \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - nextfreeindex not set to default \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - nextunusedbyte not initialized to 0 \n");
    }

    if (pBH->size != dg_calcnearestpagesize(900))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! free index case - buffer has incorrect size \n");
    }

    // off the end case, tries to extends BHarray by growby but there is no memory
    BHarrayhead.size = BHarrayhead.nextunusedbyte; // faking buffer is full

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_calcnearestpagesize(400), 
        dg_calcnearestpagesize(14000), 
        &pError, 
        FORTH_TRUE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray no mem case - buffer number not max \n");
    }

    if (pError != dg_outofmemoryerror) // oomextendbharray
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray no mem case - incorrect error got \n");
    }

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray no mem case - no buffer allocated \n");
    }

    if (BHarrayhead.nextunusedbyte != BHarrayhead.size)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray no mem case - array's nextunusedbyte incorrect, got \n");
    }
      // BHarrayhead.size is corrupt after this test!

    // off the end but extending the buffer handle array would exceed maxsize
    BHarrayhead.maxsize = BHarrayhead.size;

    tbuf = dg_newbuffer(
        &BHarrayhead, 
        400, 
        14000, 
        &pError, 
        FORTH_FALSE);

    if (tbuf != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray > maxsize case - buffer number not max \n");
    }

    if (pError != dg_BHarrayfull) // bharrayfull
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray > maxsize case - incorrect error got\n");
    }

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray > maxsize case - no buffer allocated \n");
    }

    if (BHarrayhead.nextunusedbyte != BHarrayhead.size)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray > maxsize case - array's nextunusedbyte incorrect, got \n");
    }

    if (BHarrayhead.size != BHarrayhead.maxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend BHarray > maxsize case - array's size incorrect, got\n");
    }
      // freeing BHarray for further tests. There are 4 buffers in it now

    i=3;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    dg_free(pBH->pbuf, pBH->size, dg_success);

    i=2;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    dg_free(pBH->pbuf, pBH->size, dg_success);

    i=1;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    dg_free(pBH->pbuf, pBH->size, dg_success);

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
    dg_free(pBH->pbuf, pBH->size, dg_success);

    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;

    BHarrayhead.growby = 0;
    BHarrayhead.maxsize = 0;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.size = 0;
    BHarrayhead.id = BHarrayheadid;

    // off the end case, extends bharray by growby
      // making a new buffer
    BHarrayhead.growby = dg_calcnearestpagesize(sizeof(Bufferhandle));
    BHarrayhead.maxsize = 2 * dg_calcnearestpagesize(sizeof(Bufferhandle)); 
    BHarrayhead.nextfreeindex = BHarraymaxindex;

    n = (UINT64)(BHarrayhead.growby / sizeof(Bufferhandle));

    for (i = 0; i < n; i++)
    {
        tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_getpagesize(), 
        dg_getpagesize(), 
        &pError, 
        FORTH_FALSE);
    }

    if (BHarrayhead.pbuf == badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case 1st call - no buffer allocated \n");
    }

    if (pError != dg_success)
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case 1st call - not dg_success \n");
    }

    if (tbuf != n - 1)
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case 1st call - buffer id not n - 1 \n");
    }

    if (BHarrayhead.size != dg_calcnearestpagesize(sizeof(Bufferhandle)))
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case 1st call - size not correct \n");
    }

    // extending bharray call
    tbuf = dg_newbuffer(
        &BHarrayhead, 
        dg_getpagesize(),
        dg_getpagesize(),
        &pError, 
        FORTH_FALSE);

    if (BHarrayhead.pbuf == badbufferhandle)
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case extend call - no buffer allocated \n");
    }

    if (pError != dg_success)
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case extend call - not dg_success \n");
    }

    if (tbuf != n)
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case extend call - buffer id not 2 \n");
    }

    if (BHarrayhead.size != 2 * dg_calcnearestpagesize(sizeof(Bufferhandle)))
    {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! extend bharray case extend call - size not correct \n");
    }

    for (i = 0; i < n+1; i++)
    {
        pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
        dg_free(pBH->pbuf, pBH->size, dg_success);
    }
    
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;

    BHarrayhead.growby = 0;
    BHarrayhead.maxsize = 0;
    BHarrayhead.nextfreeindex = 0;
    BHarrayhead.nextunusedbyte = 0;
    BHarrayhead.size = 0;
    BHarrayhead.id = BHarrayheadid;

    // checking case with growby not a multiple of size of Bufferhandle
    //   with pagesize requirement added in, not so sure we are testing what we want :-)
    BHarrayhead.growby = sizeof(Bufferhandle) + 2;
    BHarrayhead.maxsize = 3 * sizeof (Bufferhandle); // room for 3
    BHarrayhead.nextfreeindex = BHarraymaxindex;

      tbuf = dg_newbuffer(
          &BHarrayhead, 
          100, 
          1000, 
          &pError, 
          FORTH_FALSE);

      if (BHarrayhead.pbuf == badbufferhandle)
      {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby not a multiple of size of Bufferhandle case 1st call - no buffer allocated \n");
      }

      if (pError != dg_success)
      {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby not a multiple of size of Bufferhandle case 1st call - not dg_success \n");
      }

      if (tbuf != 0)
      {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby not a multiple of size of Bufferhandle case 1st call - buffer id not 0 \n");
      }

      if (BHarrayhead.size != ::dg_calcnearestpagesize(sizeof(Bufferhandle) + 2))
      {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! growby not a multiple of size of Bufferhandle case 1st call - size not correct \n");
      }
     
      i=0;
      pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
      dg_free(pBH->pbuf, pBH->size, dg_success);

      dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
      BHarrayhead.pbuf = badbufferhandle;

      BHarrayhead.growby = 0;
      BHarrayhead.maxsize = 0;
      BHarrayhead.nextfreeindex = 0;
      BHarrayhead.nextunusedbyte = 0;
      BHarrayhead.size = 0;
}

void testdg_freebuffer()
{
    UINT64 tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH;
    UINT64 i;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freebuffer\n");

    // testing invalid pointer case, basically a crash test
    dg_freebuffer((Bufferhandle*)-1, 0);

    // testing no buffer case, basically a crash test
    dg_freebuffer(&BHarrayhead, 0);

    // testing normal use cases

    BHarrayhead.growby = sizeof(Bufferhandle);
    BHarrayhead.maxsize = 3 * sizeof (Bufferhandle); // room for 3
    BHarrayhead.nextfreeindex = BHarraymaxindex;

    tbuf = dg_newbuffer(&BHarrayhead, 100, 1000, &pError, FORTH_FALSE); // 0
    tbuf = dg_newbuffer(&BHarrayhead, 200, 2000, &pError, FORTH_FALSE); // 1
    tbuf = dg_newbuffer(&BHarrayhead, 300, 3000, &pError, FORTH_FALSE); // 2

    // testing off end case
    dg_freebuffer(&BHarrayhead, 3);

    if (BHarrayhead.nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer bufferid off end case - shouldnt be a free buffer in linked list \n");

    }

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer bufferid off end case - buffer 0 was freed \n");
    }

    i=1;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer bufferid off end case - buffer 1 was freed \n");
    }

    i=2;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer bufferid off end case - buffer 2 was freed \n");
    }

    // testing freeing 1st buffer case
    dg_freebuffer(&BHarrayhead, 1);

    if (BHarrayhead.nextfreeindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 1st buffer case - buffer 1 not in free linked list \n");

    }

    i=1;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf != (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 1st buffer case - buffer 1 was not freed \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 1st buffer case - buffer 1 nextfreeindex not max \n");
    }

    // testing freeing 2nd buffer case
    dg_freebuffer(&BHarrayhead, 0);

    if (BHarrayhead.nextfreeindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 2nd buffer case - buffer 0 not in free linked list \n");

    }

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf != (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 2nd buffer case - buffer 0 was not freed \n");
    }

    if (pBH->nextfreeindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 2nd buffer case - buffer 0 nextfreeindex not 1\n");
    }

    // testing freeing an already free buffer case - nothing should change
    dg_freebuffer(&BHarrayhead, 0);

    if (BHarrayhead.nextfreeindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing free buffer case - buffer 0 not in free linked list \n");

    }

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf != (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing free buffer case - buffer 0 was not freed \n");
    }

    if (pBH->nextfreeindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing free buffer case - buffer 0 nextfreeindex not 1\n");
    }

    // testing freeing 3rd buffer
    dg_freebuffer(&BHarrayhead, 2);

    if (BHarrayhead.nextfreeindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 3rd buffer case - buffer 0 not in free linked list \n");

    }

    i=2;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf != (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 3rd buffer case - buffer 2 was not freed \n");
    }

    if (pBH->nextfreeindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer freeing 3rd buffer case - buffer 2 nextfreeindex not 1\n");
    }

    // testing new buffer again just to make sure free links dont get messed up
    tbuf = dg_newbuffer(&BHarrayhead, 400, 4000, &pError, FORTH_FALSE);

    // buffer 2 should be reallocated now with this buffer

    if (BHarrayhead.nextfreeindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer adding new buffer case - buffer 0 not first in free linked list \n");

    }

    i=2;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->pbuf == (void*)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer adding new buffer case - buffer 2 was not allocated \n");
    }

    if (pBH->nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer adding new buffer case - buffer 2 nextfreeindex not max\n");
    }

    i=0;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->nextfreeindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer adding new buffer case - buffer 0's nextfreeindex not 1 \n");
    }

    i=1;
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    if (pBH->nextfreeindex != BHarraymaxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_freebuffer adding new buffer case - buffer 1's nextfreeindex not max \n");
    }

}

void testdg_growbuffer ()
{
//    unsigned int tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH;
    UINT64 i;
    UINT64 here;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_growbuffer\n");
#ifndef DGLU_NO_DIAPER
    // testing NULL pointer to BHarray case
    here = dg_growbuffer((Bufferhandle*)badbufferhandle, 0, 20, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - null pointer to BHarray case, didn't return maxint \n");
    }

    if (pError != dg_nullpbharrayheaderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - null pointer to BHarray case, incorrect error \n");
    }

    // testing no BHarray buffer case
    here = dg_growbuffer(&BHarrayhead, 0, 20, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - no BHarray buffer case, didn't return maxint \n");
    }

    if (pError != dg_nullpbharrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - no BHarray buffer case, incorrect error \n");
    }

    // testing nub corrupt case
    i = dg_newbuffer(&BHarrayhead, 100, 300, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    BHarrayhead.nextunusedbyte++;

    here = dg_growbuffer(&BHarrayhead, i, 50, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - nub corrupt case, didn't return maxint \n");
    }

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - nub corrupt case, incorrect error \n");
    }

    if (BHarrayhead.nextunusedbyte != (sizeof (Bufferhandle) + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - nub corrupt case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - nub corrupt case, buffer's nub was changed \n");
    }

    BHarrayhead.nextunusedbyte--;

    // testing id not in array case - we have one buffer (i=0) from last test
    here = dg_growbuffer(&BHarrayhead, i+1, 50, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - id not in array case, didn't return maxint \n");
    }

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - id not in array case, incorrect error \n");
    }

    if (BHarrayhead.nextunusedbyte != (i+1) * (sizeof (Bufferhandle)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - id not in array case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - id not in array case, buffer's nub was increased \n");
    }

    if (pBH->size != dg_calcnearestpagesize(100))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - id not in array case, buffer's size was changed \n");
    }

    // testing trying to grow a free buffer case
    dg_freebuffer(&BHarrayhead, i);

    here = dg_growbuffer(&BHarrayhead, i, 50, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - trying to grow a free buffer case, didn't return maxint \n");
    }

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - trying to grow a free buffer case, incorrect error \n");
    }

    if (BHarrayhead.nextunusedbyte != (i+1) * (sizeof (Bufferhandle)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - trying to grow a free buffer case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - trying to grow a free buffer case, buffer's nub was increased \n");
    }
#endif
    // testing grow would exceed maxsize case
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 2*dg_getpagesize(), &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    here = dg_growbuffer(&BHarrayhead, i, 2*dg_getpagesize() + 1, &pError, false);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - exceed maxsize case, didn't return maxint got\n");
    }

    if (pError != dg_bufferfullerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - exceed maxsize case, incorrect error got \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - exceed maxsize case, buffer's nub was increased \n");
    }

    dg_freebuffer(&BHarrayhead, i);

    // testing out of memory cases
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 4*dg_getpagesize(), &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    // length exceeds growby case
    here = dg_growbuffer(&BHarrayhead, i, dg_getpagesize()+1, &pError, true);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, didn't return maxint got\n");
    }

    if (pError != dg_outofmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, incorrect error got\n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, buffer's nub was increased \n");
    }

    // nub + length < size + growby <= maxsize case 
    pBH->nextunusedbyte = dg_getpagesize()/2;
    here = dg_growbuffer(&BHarrayhead, i, (dg_getpagesize()/2) + 1, &pError, true);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, didn't return maxint got\n");
    }

    if (pError != dg_outofmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, incorrect error got\n");
    }

    if (pBH->nextunusedbyte != dg_getpagesize()/2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, buffer's nub was increased \n");
    }

    dg_freebuffer(&BHarrayhead, i);
    // nub + length <= maxsize < size + growby case
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 3*dg_getpagesize(), &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = dg_getpagesize()-2;

    here = dg_growbuffer(&BHarrayhead, i, (2*dg_getpagesize())-1, &pError, true);

    if (here != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, didn't return maxint got\n");
    }

    if (pError != dg_outofmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, incorrect error got\n");
    }

    if (pBH->nextunusedbyte != dg_getpagesize()-2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - out of memory case, buffer's nub was increased \n");
    }

    dg_freebuffer(&BHarrayhead, i);

    // testing dg_success cases

    // no need to extend case
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 4*dg_getpagesize(), &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    here = dg_growbuffer(&BHarrayhead, i, dg_getpagesize(), &pError, false);

    if (here != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend case, didn't return maxint got\n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend case, incorrect error got\n");
    }

    if (pBH->nextunusedbyte != dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend case, buffer's nub was not increased \n");
    }

    // need to extend case, nub + length < size + growby <= maxsize
    here = dg_growbuffer(&BHarrayhead, i, 1, &pError, false);

    if (here != dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, didn't return correct old nub\n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, incorrect error\n");
    }

    if (pBH->nextunusedbyte != dg_getpagesize()+1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, buffer's nub was not increased \n");
    }

    if (pBH->size != 2*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, size incorrect \n");
    }

    // need to extend case, nub + length <= size + growby <= maxsize2
    here = dg_growbuffer(&BHarrayhead, i, dg_getpagesize(), &pError, false);

    if (here != dg_getpagesize()+1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, didn't return correct old nub\n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, incorrect error \n");
    }

    if (pBH->nextunusedbyte != 2*dg_getpagesize()+1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, buffer's nub was not increased \n");
    }

    if (pBH->size != 3*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length < size + growby case, size incorrect \n");
    }

    // need to extend case, nub + length <= maxsize < size + growby
    here = dg_growbuffer(&BHarrayhead, i, dg_getpagesize()+1, &pError, false);

    if (here != 2*dg_getpagesize()+1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length <= maxsize < size + growby case, didn't return maxint\n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length <= maxsize < size + growby case, incorrect error \n");
    }

    if (pBH->nextunusedbyte != 3*dg_getpagesize()+2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length <= maxsize < size + growby case, buffer's nub was not increased \n");
    }

    if (pBH->size != 4*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success extend nub + length <= maxsize < size + growby case, size incorrect \n");
    }

    // no need to extend case, nub + length = maxsize = size + growby
    here = dg_growbuffer(&BHarrayhead, i, dg_getpagesize()-2, &pError, false);

    if (here != 3*dg_getpagesize()+2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend nub + length = maxsize = size + growby case, didn't return maxint\n");
    }

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend nub + length = maxsize = size + growby case, incorrect error \n");
    }

    if (pBH->nextunusedbyte != 4*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend nub + length = maxsize = size + growby case, buffer's nub was not increased \n");
    }

    if (pBH->size != 4*dg_getpagesize())
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_growbuffer - dg_success no extend nub + length = maxsize = size + growby case, size incorrect \n");
    }
}

void testdg_shrinkbuffer ()
{
//    unsigned int tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH;
    UINT64 i;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_shrinkbuffer\n");
#ifndef DGLU_NO_DIAPER
    // testing NULL pointer to BHarray case
    dg_shrinkbuffer((Bufferhandle*)badbufferhandle, 0, 20, &pError);

    if (pError != dg_nullpbharrayheaderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - null pointer to BHarray case, incorrect error \n");
    }

    // testing no BHarray buffer case
    dg_shrinkbuffer(&BHarrayhead, 0, 20, &pError);

    if (pError != dg_nullpbharrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - no BHarray buffer case, incorrect error \n");
    }

    // testing nub corrupt case
    i = dg_newbuffer(&BHarrayhead, 100, 300, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    BHarrayhead.nextunusedbyte++;

    dg_shrinkbuffer(&BHarrayhead, i, 50, &pError);

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - nub corrupt case, incorrect error \n");
    }

    if (BHarrayhead.nextunusedbyte != (sizeof (Bufferhandle) + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - nub corrupt case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - nub corrupt case, buffer's nub was changed \n");
    }

    BHarrayhead.nextunusedbyte--;

    // testing id not in array case - we have one buffer (i=0) from last test
    dg_shrinkbuffer(&BHarrayhead, i+1, 50, &pError);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - id not in array case, incorrect error \n");
    }

    if (BHarrayhead.nextunusedbyte != (i+1) * (sizeof (Bufferhandle)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - id not in array case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - id not in array case, buffer's nub was increased \n");
    }

    if (pBH->size != dg_calcnearestpagesize(100))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - id not in array case, buffer's size was changed \n");
    }

    // testing trying to shrink a free buffer case
    dg_freebuffer(&BHarrayhead, i);

    dg_shrinkbuffer(&BHarrayhead, i, 50, &pError);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - trying to grow a free buffer case, incorrect error \n");    }

    if (BHarrayhead.nextunusedbyte != (i+1) * (sizeof (Bufferhandle)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! srhinkbuffer - trying to grow a free buffer case, BHarrayhead nub was changed \n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - trying to grow a free buffer case, buffer's nub was increased \n");
    }
#endif
    // testing shrink would underflow buffer case
    i = dg_newbuffer(&BHarrayhead, 100, 200, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_shrinkbuffer(&BHarrayhead, i, 1, &pError);

    if (pError != dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - underflow case, incorrect error\n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - underflow case, buffer's nub was changed \n");
    }

    dg_freebuffer(&BHarrayhead, i);

    // testing dg_success case
    i = dg_newbuffer(&BHarrayhead, 100, 200, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = 50;

    dg_shrinkbuffer(&BHarrayhead, i, 1, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - dg_success case, incorrect error\n");
    }

    if (pBH->nextunusedbyte != 49)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - dg_success case, buffer's nub was not changed \n");
    }

    dg_shrinkbuffer(&BHarrayhead, i, 49, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - dg_success case, incorrect error\n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_shrinkbuffer - dg_success case, buffer's nub was not changed \n");
    }

    dg_freebuffer(&BHarrayhead, i);
}


void testdg_getpbuffer()
{
//    UINT64 tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
//    UINT64 i = 0;
    unsigned char* psegment;

    UINT64* plength = NULL;
    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getpbuffer\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    psegment = dg_getpbuffer((Bufferhandle*)badbufferhandle, 0, &plength); // crash test

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer null pBHarrayhead case - NULL buffer pointer not returned\n");
    }

    // changed it so pBHarrayhead is checked before pplength
    //if (plength != (UINT32*)badbufferhandle)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer null pBHarrayhead case - NULL length pointer not returned\n");
    //}

    // no BH array case
    BHarrayhead.errorcount = 0;
    psegment = dg_getpbuffer(&BHarrayhead, 0, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer no BHarray case - NULL buffer pointer not returned\n");
    }

    if (0 == BHarrayhead.errorcount)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer no BHarray case - error count not incremented\n");
    }

    // changed it so bharray is checked before plength
    //if (plength != (UINT64*)badbufferhandle)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer no BHarray case - NULL length pointer not returned\n");
    //}

    // buf id is for error stack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for errorstack case - failed to initialize error stack\n");
    }

    psegment = dg_getpbuffer(&BHarrayhead, 0, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for error stack case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for error stack case - NULL length pointer not returned\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for error stack case - got wrong error on top\n");
    }

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for error stack case - got wrong error on bottom\n");
    }

    dg_clearerrors(&BHarrayhead);

    //buf id isn't in BHarray case
    psegment = dg_getpbuffer(&BHarrayhead, 1, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id isn't in BHarray case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id isn't in BHarray case - NULL length pointer not returned\n");
    }

    pError = dg_geterror(&BHarrayhead,0);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id isn't in BHarray case - got wrong error on bottome\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id isn't in BHarray case - got wrong error on top\n");
    }


    dg_clearerrors(&BHarrayhead);

    //buf id is for a free buffer case
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for free buffer case - unable to allocate memory for buffer\n");
        return;
    }

    dg_freebuffer(&BHarrayhead, bufid);

    psegment = dg_getpbuffer(&BHarrayhead, bufid, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for a free buffer case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for a free buffer case - NULL length pointer not returned\n");
    }

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for a free buffer case - got wrong error on bottom\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer buf id is for a free buffer case - got wrong error on top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // in use bytes > allocated size case
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer in use bytes > allocated size case - unable to allocate memory for buffer\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[bufid]);

    pBH->nextunusedbyte = pBH->size + 1;

    psegment = dg_getpbuffer(&BHarrayhead, bufid, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer in use bytes > allocated size case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer in use bytes > allocated size case - NULL length pointer not returned\n");
    }

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer in use bytes > allocated size case - got wrong error on bottom\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer in use bytes > allocated size case - got wrong error on top\n");
    }

    pBH->nextunusedbyte = 0;

    dg_clearerrors(&BHarrayhead);

    // allocated size > max allowed size case
    pBH->size = pBH->maxsize + 1;

    psegment = dg_getpbuffer(&BHarrayhead, bufid, &plength);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer allocated size > max size case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer allocated size > max size case - NULL length pointer not returned\n");
    }

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_buffermaxsizeltsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer allocated size > max size case - got wrong error on bottom\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer allocated size > max size case - got wrong error on top\n");
    }

    pBH->size = 1000; // this needs to match original size allocation

    dg_clearerrors(&BHarrayhead);

    // NULL pointer to length pointer case
    psegment = dg_getpbuffer(
        &BHarrayhead,
        bufid,
        (UINT64**)badbufferhandle);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer NULL pointer to length pointer case - NULL buffer pointer not returned\n");
    }

    if (plength != (UINT64*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer NULL pointer to length pointer case - NULL length pointer not returned\n");
    }

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_nullpointererror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer NULL pointer to length pointer case - got wrong error on bottom\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffer NULL pointer to length pointer case - got wrong error on top\n");
    }

    dg_clearerrors(&BHarrayhead);
#endif
    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getpbuffersegment()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 bufid = 0;
    unsigned char* psegment;
    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getpbuffersegment\n");

    // error getting pointer to buffer case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment error getting pointer to buffer case - unable to initialize error stack\n");
        return;
    }
#ifndef DGLU_NO_DIAPER
    psegment = dg_getpbuffersegment(&BHarrayhead, 1, 0, 0); // buf 1 not in array yet so this is an error

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment error getting pointer to buffer case - buffer pointer not NULL\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffersegment error getting pointer to buffer case - got wrong error\n");
    }

    dg_clearerrors(&BHarrayhead);
#endif
    // offset + length off end case
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment offset + length off end case - unable to allocate memory for buffer\n");
    }

     // fail case for empty buffer
    psegment = dg_getpbuffersegment(&BHarrayhead, bufid, 0, 1);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment offset + length off end case - buffer pointer not NULL\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffersegment offset + length off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffersegment offset + length off end case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case for empty buffer
    psegment = dg_getpbuffersegment(&BHarrayhead, bufid, 0, 0);

    if (psegment == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment dg_success case for empty buffer - got NULL pointer\n");
    }

    dg_clearerrors(&BHarrayhead);

    // failcase with stuff in buffer
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[bufid]);

    pBH->nextunusedbyte = 10;

    psegment = dg_getpbuffersegment(&BHarrayhead, bufid, 9, 2);

    if (psegment != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment offset + length off end case2 - buffer pointer not NULL\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffersegment offset + length off end case2 - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbuffersegment offset + length off end case2 - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case with not empty buffer
    psegment = dg_getpbuffersegment(&BHarrayhead, bufid, 8, 2);

    if (psegment == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getpbuffersegment dg_success case for not empty buffer - got NULL pointer\n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getbuffersegment()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getbuffersegment\n");

    unsigned char dest[80];

    // testing dest null case
    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    dg_pushbufferuint64(&BHarrayhead, 1, 0x5566778811223344);
    dg_pushbufferuint64(&BHarrayhead, 1, 0x0000000099aabbcc);
#ifndef DGLU_NO_DIAPER
    dg_getbuffersegment(&BHarrayhead, 1, 0, 10, (unsigned char*)badbufferhandle);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment dest null case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_nullpointererror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment dest null case - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // testing invalid buffer segment case (using bufid to big and off end of buffer)
    dg_getbuffersegment(&BHarrayhead, 2, 0, 10, dest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment invalid buffer segment case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment invalid buffer segment case - error incorrect 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
#endif
    // testing dg_success case
    dest[0] = 0;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    dest[4] = 0;
    dest[5] = 0;

    dg_getbuffersegment(
        &BHarrayhead,
        1,
        4,
        4,
        dest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment dg_success case - got error\n");
    }

    if ((dest[0] != 0x88) ||
        (dest[1] != 0x77) ||
        (dest[2] != 0x66) ||
        (dest[3] != 0x55))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment dg_success case - got wrong segment data\n");
        
    }

    if (dest[4] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbuffersegment dg_success case - got too many bytes\n");
    }
    
    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_putbuffersegment()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putbuffersegment\n");

    unsigned char src[80];
    UINT64 data = 0;

    // testing src null case
    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    dg_pushbufferuint64(&BHarrayhead, 1, 0x0);
    dg_pushbufferuint64(&BHarrayhead, 1, 0x0);
#ifndef DGLU_NO_DIAPER
    dg_putbuffersegment(&BHarrayhead, 1, 0, 10, (unsigned char*)badbufferhandle);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment src null case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_nullpointererror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment src null case - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // testing invalid buffer segment case (using bufid to big and off end of buffer)
    dg_putbuffersegment(&BHarrayhead, 2, 0, 10, src);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment invalid buffer segment case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment invalid buffer segment case - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);
#endif
    // testing dg_success case
    src[0] = 0x88;
    src[1] = 0x77;
    src[2] = 0x66;
    src[3] = 0x55;
    src[4] = 0x44;
    src[5] = 0x33;
    src[6] = 0x22;
    src[7] = 0x37;

    dg_putbuffersegment(&BHarrayhead, 1, 4, 4, src);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment dg_success case - got error\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, 1, 4);

    if (data != 0x0000000055667788)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment dg_success case - got wrong segment data, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, 1, 8);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment dg_success case b - got wrong segment data, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, 1, 0);

    if (data != 0x5566778800000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbuffersegment dg_success case c - got wrong segment data, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_pushbufferuint32()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT32 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushbufferuint32\n");
#ifndef DGLU_NO_DIAPER
    // null pBHarrayhead case - crash test
    dg_pushbufferuint32((Bufferhandle*)badbufferhandle, 0, 0);
#endif
    // trying to push to buffer 0
    dg_initerrors(&BHarrayhead, 100, &pError);
    dg_pushbufferuint64(&BHarrayhead, 0, 0);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 push to errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 push to errorstack case - got wrong error 1 below top\n");
    }

    // dg_success case
    i = dg_newbuffer(&BHarrayhead, 8, 15, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_pushbufferuint32(&BHarrayhead, i, 0x58335694);

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0x58335694)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 dg_success case - got an error\n");
    }

    // 2nd push dg_success case
    dg_pushbufferuint32(&BHarrayhead, i, 0x12345678);

    data = dg_getbufferuint32(&BHarrayhead, i, 4);

    if (data != 0x12345678)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 2nd dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 2nd dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 2nd dg_success case - got an error\n");
    }

    // 3rd push dg_success case - need to grow
    dg_pushbufferuint32(&BHarrayhead, i, 0x9abcdef0);

    data = dg_getbufferuint32(&BHarrayhead, i, 8);

    if (data != 0x9abcdef0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 3rd dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 3rd dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 3rd dg_success case - got an error\n");
    }

    // 4th push buffer full case
    pBH->nextunusedbyte = pBH->size;
    dg_pushbufferuint32(&BHarrayhead, i, 0x11223344);

    if (pBH->nextunusedbyte != pBH->size)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - buffer in use bytes changed\n");
    }

    if (dg_geterrorcount(&BHarrayhead) == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - didn't get an error\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - got wrong error 1 below top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferfullerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - got wrong error 2 below top\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint32 buffer full case - error stack not empty\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_getbufferuint32()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT32 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getbufferuint32\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL case
    data = dg_getbufferuint32((Bufferhandle*)badbufferhandle, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 NULL pBHarrayhead case - data != 0\n");
    }
   
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    data = dg_getbufferuint32(&BHarrayhead, 1, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 no BHarray case - data != 0\n");
    }

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 no BH array case - error count not incremented\n");
    }
    
    //  The buffer id is for the errorstack. (use dg_geterror to get errors from the error stack)
    dg_initerrors(&BHarrayhead, 100, &pError);

    data = dg_getbufferuint32(&BHarrayhead, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id for errorstack case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id for errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id for errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id for errorstack case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is off the end of the buffer handle array
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE); 

    data = dg_getbufferuint32(&BHarrayhead, i+1, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id off end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 buffer id off end case - got wrong error 1 below top\n");
    }

    //  The buffer id is for a buffer handle with no buffer attached. (It's free.)
    dg_freebuffer(&BHarrayhead, i);

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 free buffer case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 free buffer case - got wrong error 1 below top\n");
    }
 #endif   
    //  The offset is too close to the end, or off the end of the buffer
    i= dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = 3;

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - got wrong error 1 below top\n");
    }
#endif
    // dg_success case near end of buffer
    pBH->nextunusedbyte = 4;

    ((UINT32*)pBH->pbuf)[0] = 0x12345678;

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0x12345678)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 dg_success near end case - data != 0x1234567899886644\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 dg_success near end case - error count not 0\n");
    }

    // dg_success case near end of buffer 2
    pBH->nextunusedbyte = 12;

    ((UINT32*)pBH->pbuf)[2] = 0xabc4def0;

    data = dg_getbufferuint32(&BHarrayhead, i, 8);

    if (data != 0xabc4def0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 dg_success near end case 2 - data != 0xabc4def077553311\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 dg_success near end case 2 - error count not 0\n");
    }

    // dg_success case middle
    pBH->nextunusedbyte = 16;

    ((UINT32*)pBH->pbuf)[0] = 0x12345678;
    ((UINT32*)pBH->pbuf)[1] = 0xabc4def0;

    // little endian - expect 78563412f0dec4ab in mem
    // pulling out 3412f0de

    data = dg_getbufferuint32(&BHarrayhead, i, 2);

    if (data != 0xdef01234)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case middle - data != 0x6688123456787755\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case middle - error count not 0\n");
    }
    
    // dg_success case alignment off by 1
    pBH->nextunusedbyte = 16;

    ((UINT32*)pBH->pbuf)[0] = 0x12345678;
    ((UINT32*)pBH->pbuf)[1] = 0xabc4def0;

    // little endian - expect 78563412f0dec4ab in mem
    // pulling out 3412f0de

    data = dg_getbufferuint32(&BHarrayhead, i, 1);

    if (data != 0xf0123456)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case alignment off by 1 - data != 0x8812345678775533\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case alignment off by 1 - error count not 0\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_putbufferuint32 ()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT32 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putbufferuint32\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    dg_putbufferuint32(NULL, 0, 0, 0);
      // crash test
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    dg_putbufferuint32(&BHarrayhead, 0, 0, 0);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 no bharray case - error count not incremented\n");
    }

    BHarrayhead.errorcount = 0;
#endif
    //  The buffer id is for the errorstack. (use dg_geterror to get errors from the error stack)
    dg_initerrors(&BHarrayhead, 400, &pError);
#ifndef DGLU_NO_DIAPER
    BHarrayhead.errorcount = 0;
    dg_putbufferuint32(&BHarrayhead, 0, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid for errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid for errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid for errorstack case - got wrong error 1 below top\n");
    }

    //  The buffer id is of the end of the buffer handle array
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    dg_putbufferuint32(&BHarrayhead, i+1, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 bufferid off end case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is for a buffer handle with no buffer attached. (It's free.)
    dg_freebuffer(&BHarrayhead, i);

    dg_putbufferuint32(&BHarrayhead, i, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint32 free buffer case - got wrong error 1 below top\n");
    }
#endif
    //  The offset is to close to the end, or off the end of the buffer
    i= dg_newbuffer(&BHarrayhead, 20, 20, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = 3;

    ((UINT32*)pBH->pbuf)[0] = 0x12345678;

    dg_putbufferuint32(&BHarrayhead, i, 0, 0xffffffff);

    pBH->nextunusedbyte = 4;
    
    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0x12345678)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 offset off end case - data != 0x12345678\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 offset off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint32 offset off end case - got wrong error 1 below top\n");
    }
#endif
    // dg_success case at end
    pBH->nextunusedbyte = 16;

    ((UINT32*)pBH->pbuf)[0] = 0x0;
    ((UINT32*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint32(&BHarrayhead, i, 8, 0x3514268A);
    
    data = dg_getbufferuint32(&BHarrayhead, i, 8);

    if (data != 0x3514268A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at end case - data != 0x3514268A98765432\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at end case - error count not 0\n");
    }

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at end case - error count not 0\n");
    }

    // dg_success at beginning case
    pBH->nextunusedbyte = 16;

    ((UINT32*)pBH->pbuf)[0] = 0x0;
    ((UINT32*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint32(&BHarrayhead, i, 0, 0x3514268A);
    
    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0x3514268A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - error count not 0\n");
    }

    data = dg_getbufferuint32(&BHarrayhead, i, 4);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - error count not 0\n");
    }

    // dg_success at middle case
    pBH->nextunusedbyte = 8;

    ((UINT32*)pBH->pbuf)[0] = 0x0;
    ((UINT32*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint32(&BHarrayhead, i, 2, 0x3514268A);
    
    data = dg_getbufferuint32(&BHarrayhead, i, 2);

    if (data != 0x3514268A)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at beginning case - error count not 0\n");
    }

    // little endian in mem 00 00 8A 26  14 35 00 00

    data = dg_getbufferuint32(&BHarrayhead, i, 0);

    if (data != 0x268A0000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at middle case - data != 0x268A0000\n");
    }

    data = dg_getbufferuint32(&BHarrayhead, i, 4);

    if (data != 0x00003514)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint32 dg_success at middle case - data != 0x00003514\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}

void testdg_pushbufferuint64()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushbufferuint64\n");
#ifndef DGLU_NO_DIAPER
    // null pBHarrayhead case - crash test
    dg_pushbufferuint64((Bufferhandle*)badbufferhandle, 0, 0);
#endif
    // trying to push to buffer 0
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    dg_pushbufferuint64(&BHarrayhead, 0, 0);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 push to errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 push to errorstack case - got wrong error 1 below top\n");
    }
#endif
    // dg_success case
    i = dg_newbuffer(&BHarrayhead, 0x10, 0x1f, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_pushbufferuint64(&BHarrayhead, i, 0x5833569498761234);

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x5833569498761234)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 dg_success case - got an error\n");
    }

    // 2nd push dg_success case
    dg_pushbufferuint64(&BHarrayhead, i, 0x1234567898765432);

    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0x1234567898765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 2nd dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 2nd dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 2nd dg_success case - got an error\n");
    }

    // 3rd push dg_success case - need to grow
    dg_pushbufferuint64(&BHarrayhead, i, 0x9abcdef087563412);

    data = dg_getbufferuint64(&BHarrayhead, i, 16);

    if (data != 0x9abcdef087563412)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 3rd dg_success case - number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 3rd dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 3rd dg_success case - got an error\n");
    }

    // 4th push buffer full case
    pBH->nextunusedbyte = pBH->size;
    dg_pushbufferuint64(&BHarrayhead, i, 0x1122334477553311);

    if (pBH->nextunusedbyte != pBH->size)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - buffer in use bytes changed\n");
    }

    if (dg_geterrorcount(&BHarrayhead) == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - didn't get an error\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - got wrong error 1 below top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferfullerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - got wrong error 2 below top\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferuint64 buffer full case - error stack not empty\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}


void testdg_getbufferuint64()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getbufferuint64\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL case
    data = dg_getbufferuint64((Bufferhandle*)badbufferhandle, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 NULL pBHarrayhead case - data != 0\n");
    }
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    data = dg_getbufferuint64(&BHarrayhead, 1, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 no BHarray case - data != 0\n");
    }

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 no BH array case - error count not incremented\n");
    }
#endif    
    //  The buffer id is for the errorstack. (use dg_geterror to get errors from the error stack)
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    data = dg_getbufferuint64(&BHarrayhead, 0, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id for errorstack case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id for errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id for errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id for errorstack case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is off the end of the buffer handle array
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE); 

    data = dg_getbufferuint64(&BHarrayhead, i+1, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id off end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 buffer id off end case - got wrong error 1 below top\n");
    }

    //  The buffer id is for a buffer handle with no buffer attached. (It's free.)
    dg_freebuffer(&BHarrayhead, i);

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 free buffer case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 free buffer case - got wrong error 1 below top\n");
    }
#endif    
    //  The offset is too close to the end, or off the end of the buffer
    i= dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = 3;

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - got wrong error 1 below top\n");
    }
#endif
    // dg_success case near end of buffer
    pBH->nextunusedbyte = 8;

    ((UINT64*)pBH->pbuf)[0] = 0x1234567899886644;

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x1234567899886644)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success near end case - data != 0x1234567899886644\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success near end case - error count not 0\n");
    }

    // dg_success case near end of buffer 2
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[1] = 0xabc4def077553311;

    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0xabc4def077553311)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success near end case 2 - data != 0xabc4def077553311\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success near end case 2 - error count not 0\n");
    }

    // dg_success case middle
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[0] = 0x1234567877553311;
    ((UINT64*)pBH->pbuf)[1] = 0xabc4def022446688;

    // little endian - expect 78563412f0dec4ab in mem
    // pulling out 3412f0de

    data = dg_getbufferuint64(&BHarrayhead, i, 2); 

    if (data != 0x6688123456787755)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case middle - data != 0x6688123456787755\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case middle - error count not 0\n");
    }
    
    // dg_success case alignment off by 1
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[0] = 0x1234567877553311;
    ((UINT64*)pBH->pbuf)[1] = 0xabc4def022446688;

    // little endian - expect 78563412f0dec4ab in mem
    // pulling out 3412f0de

    data = dg_getbufferuint64(&BHarrayhead, i, 1);

    if (data != 0x8812345678775533)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case alignment off by 1 - data != 0x8812345678775533\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 dg_success case alignment off by 1 - error count not 0\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_putbufferuint64 ()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putbufferuint64\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    dg_putbufferuint64(NULL, 0, 0, 0);
      // crash test
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    dg_putbufferuint64(&BHarrayhead, 0, 0, 0);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 no bharray case - error count not incremented\n");
    }

    BHarrayhead.errorcount = 0;
#endif
    //  The buffer id is for the errorstack. (use dg_geterror to get errors from the error stack)
    dg_initerrors(&BHarrayhead, 400, &pError);
#ifndef DGLU_NO_DIAPER
    BHarrayhead.errorcount = 0;
    dg_putbufferuint64(&BHarrayhead, 0, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid for errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid for errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid for errorstack case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is of the end of the buffer handle array
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    dg_putbufferuint64(&BHarrayhead, i+1, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 bufferid off end case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is for a buffer handle with no buffer attached. (It's free.)
    dg_freebuffer(&BHarrayhead, i);

    dg_putbufferuint64(&BHarrayhead, i, 0, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putbufferuint64 free buffer case - got wrong error 1 below top\n");
    }
#endif    
    //  The offset is to close to the end, or off the end of the buffer
    i= dg_newbuffer(&BHarrayhead, 20, 20, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = 7;

    ((UINT64*)pBH->pbuf)[0] = 0x1234567898765432;

    dg_putbufferuint64(&BHarrayhead, i, 0, 0xffffffffffffffff);

    pBH->nextunusedbyte = 8;
    
    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x1234567898765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 offset off end case - data != 0x12345678\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 offset off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferuint64 offset off end case - got wrong error 1 below top\n");
    }
#endif
    // dg_success case at end
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[0] = 0x0;
    ((UINT64*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint64(&BHarrayhead, i, 8, 0x3514268A98765432);
    
    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0x3514268A98765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at end case - data != 0x3514268A98765432\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at end case - error count not 0\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at end case - data != 0\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at end case - error count not 0\n");
    }

    // dg_success at beginning case
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[0] = 0x0;
    ((UINT64*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint64(&BHarrayhead, i, 0, 0x3514268A44668800);
    
    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x3514268A44668800)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - error count not 0\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - error count not 0\n");
    }

    // dg_success at middle case
    pBH->nextunusedbyte = 16;

    ((UINT64*)pBH->pbuf)[0] = 0x0;
    ((UINT64*)pBH->pbuf)[1] = 0x0;

    dg_putbufferuint64(&BHarrayhead, i, 2, 0x3514268A55779911);
    
    data = dg_getbufferuint64(&BHarrayhead, i, 2);

    if (data != 0x3514268A55779911)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - data != 0x3514268A\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at beginning case - error count not 0\n");
    }

    // little endian in mem 00 00 8A 26  14 35 00 00

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x268A557799110000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at middle case - data != 0x268A0000\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0x0000000000003514)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferuint64 dg_success at middle case - data != 0x00003514\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_pushbuffersegment()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushbuffersegment\n");

    unsigned char src[80];
    UINT64 data = 0;

    // testing error doing put case (src null error)
    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 40, 40, &pError, FORTH_FALSE);

    dg_pushbuffersegment(&BHarrayhead, i, 4, (unsigned char*)badbufferhandle);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment put error case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_putbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment put error case - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // testing grow error case (trying to put a too much in nearest 40 byte max size buffer)
    dg_pushbuffersegment(&BHarrayhead, i, 2*dg_calcnearestpagesize(40), src);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment grow error case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment grow error case - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case
    src[0] = 0x11;
    src[1] = 0x22;
    src[2] = 0x33;
    src[3] = 0x44;
    src[4] = 0x55;
    src[5] = 0x66;
    src[6] = 0x77;
    src[7] = 0x88;
    src[8] = 0x99;

    dg_pushbuffersegment(&BHarrayhead, i, 4, src);
    dg_pushbuffersegment(&BHarrayhead, i, 4, src);
    dg_pushbuffersegment(&BHarrayhead, i, 8, src);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - got error\n");
    }

    // 112233441122334400000000
    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x4433221144332211)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - data a incorrect, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);

    if (data != 0x8877665544332211)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - data b incorrect, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;    
}


void testdg_pickbuffersegment()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 bufid = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pickbuffersegment\n");

    UINT64 data = 0;
#ifndef DGLU_NO_DIAPER
    // testing error growing buffer
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment error growing buffer case - got error initializing error stack buffer\n");
    }

    bufid = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment error growing buffer case - got error making a new buffer\n");
    }

    dg_pickbuffersegment(&BHarrayhead, 3984, 0, 5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pickbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment error growing buffer case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_growbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment error growing buffer case - error incorrect 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

   

    // offset off end error
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case  - got error initializing error stack buffer\n");
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case  - got error making a new buffer\n");
    }

    dg_pickbuffersegment(&BHarrayhead, bufid, 0, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pickbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case - error incorrect 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // offset off end error 2
    // dg_initbuffers(&BHarrayhead);

    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case 2 - got error initializing error stack buffer\n");
    }
    
    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case 2 - got error making a new buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 3908);

    dg_pickbuffersegment(&BHarrayhead, bufid, 6, 3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pickbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case 2 - error incorrect\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment offset off end case 2 - error incorrect\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
#endif
    // if grow worked, not sure how to get an error getting the pointer

    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment dg_success case - got error initializing error stack buffer\n");
    }

    bufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment dg_success case - got error making a new buffer\n");
    }

    dg_pushbufferuint64(&BHarrayhead, bufid, 3908);
    dg_pushbufferuint64(&BHarrayhead, bufid, 789432);

    dg_pickbuffersegment(&BHarrayhead, bufid, 8, 8);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pickbuffersegment dg_success case - got error\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, bufid, 16);

    if (data != 789432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - data a incorrect\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, bufid, 8);

    if (data != 789432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - data b incorrect\n");
    }

    if (dg_getbufferlength(&BHarrayhead, bufid) != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbuffersegment dg_success case - buffer length incorrect\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // would be nice to test where the buffer relocates
}


void testdg_popbuffersegment()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
//    unsigned char* psegment = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushbuffersegment\n");

    unsigned char dest[80];
//    UINT32 data = 0;

    dg_initerrors(&BHarrayhead, 100, &pError);

    i = dg_newbuffer(&BHarrayhead, 80, 80, &pError, FORTH_FALSE);

    dg_pushbufferuint64(&BHarrayhead, 1, 0x1122334455667788);
#ifndef DGLU_NO_DIAPER
    // error getting buffer length case (using bufid off end)
    dg_popbuffersegment(&BHarrayhead, 6, 3, dest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error getting buffer length case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error getting buffer length case - got wrong error 1 below top\n");
    }

    if (dg_getbufferlength(&BHarrayhead, 1) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error getting buffer length case - length was changed \n");
    }

    dg_clearerrors(&BHarrayhead);

    // buffer too small for pop case
    dg_popbuffersegment(&BHarrayhead, 1, 9, dest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment underflow case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment underflow case - got wrong error 1 below\n");
    }

    if (dg_getbufferlength(&BHarrayhead, 1) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment underflow case - length was changed \n");
    }

    dg_clearerrors(&BHarrayhead);

    // error getting buffer segment case (using NULL destination)
    dg_popbuffersegment(&BHarrayhead, 1, 3, (unsigned char*)badbufferhandle);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error while getting buffer segment case - got error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error while getting buffer segment case - got error 1 below top\n");
    }

    if (dg_getbufferlength(&BHarrayhead, 1) != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment error while getting buffer segment case - length was changed \n");
    }

    dg_clearerrors(&BHarrayhead);
#endif
    // don't know how to test shrink case... shrink should work

    // dg_success case
    dest[0] = 0x00;
    dest[1] = 0x00;
    dest[2] = 0x00;
    dest[3] = 0x00;
    dest[4] = 0;
    dest[5] = 0;
    dest[6] = 0;
    dest[7] = 0;

    dg_popbuffersegment(&BHarrayhead, 1, 3, dest);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment dg_success case - got error\n");
    }

    if ((dest[0] != 0x33) ||
        (dest[1] != 0x22) ||
        (dest[2] != 0x11))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment dg_success case - got wrong data\n");
    }

    if (dg_getbufferlength(&BHarrayhead, 1) != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_popbuffersegment dg_success case - length incorrect\n");
    }

    dg_clearerrors(&BHarrayhead);    

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getbufferbyte()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 bufid = 0;
    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    unsigned char b = 0;

    const char* perror;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getbufferbyte\n");

    // error getting buffer segment case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting buffer segment case - unable to initialize error stack\n");
        return;
    }

    b = dg_getbufferbyte(&BHarrayhead, 1, 0); // buffer doesn't exist so this is an error

    if (dg_poperror(&BHarrayhead) != dg_getbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting buffer segment case - got wrong error on top\n");
    }

    if (dg_poperror(&BHarrayhead) != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting buffer segment case - got wrong error 1 below top\n");
    }

    if (b != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting buffer segment case - expected return to be 0\n");
    }

    dg_clearerrors(&BHarrayhead);

    // error getting byte from empty buffer case
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting byte from empty buffer case - error initializing buffer\n");
        return;
    }

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[bufid] );

    b = dg_getbufferbyte(&BHarrayhead, bufid, 0);

    perror = dg_poperror(&BHarrayhead);

    if (perror != dg_getbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting byte from empty buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    perror = dg_poperror(&BHarrayhead);

    if (perror != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte error getting byte from empty buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case - only checking 1 because I know get buffer segment works
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte dg_success case - error initializing buffer\n");
        return;
    }

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[bufid] );

    pBH->nextunusedbyte = 1;

    *((unsigned char*)(pBH->pbuf)) = 0x58;

    b = dg_getbufferbyte(&BHarrayhead, bufid, 0);

    if (b != 0x58)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte dg_success case - got wrong byte\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getbufferbyte dg_success case - got an error\n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_putbufferbyte()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 bufid = 0;
    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    unsigned char b = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putbufferbyte\n");

    // error putting buffer segment case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte error putting buffer segment case - unable to initialize error stack\n");
        return;
    }

    dg_putbufferbyte(&BHarrayhead, 1, 0, 0x93); // buffer 1 doesn't exist so this is an error

    if (dg_poperror(&BHarrayhead) != dg_putbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte error putting buffer segment case - got wrong error on top\n");
    }

    if (dg_poperror(&BHarrayhead) != dg_putbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte error putting buffer segment case - got wrong error 1 from top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case - only checking 1 because I know get buffer segment works
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte dg_success case - error initializing buffer\n");
        return;
    }

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[bufid] );

    pBH->nextunusedbyte = 1;

    *((unsigned char*)(pBH->pbuf)) = 0x0;

    dg_putbufferbyte(&BHarrayhead, bufid, 0, 0x98);

    b = *((unsigned char*)(pBH->pbuf));

    if (b != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte dg_success case - put wrong byte\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_putbufferbyte dg_success case - got an error\n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_popbufferbyte()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 bufid = 0;
    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    unsigned char b = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_popbufferbyte\n");

    // error getting buffer segment case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte error getting buffer segment case - unable to initialize error stack\n");
        return;
    }

    b = dg_popbufferbyte(&BHarrayhead, 1); // buffer doesn't exist so this is an error

    if (dg_poperror(&BHarrayhead) != dg_popbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte error getting buffer segment case - got wrong error on top\n");
    }

    if (dg_poperror(&BHarrayhead) != dg_popbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte error getting buffer segment case - got wrong error 1 below top\n");
    }

    if (b != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte error popping buffer segment case - expected return to be 0\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case - only checking 1 because I know get buffer segment works
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte dg_success case - error initializing buffer\n");
        return;
    }

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[bufid] );

    pBH->nextunusedbyte = 1;

    *((unsigned char*)(pBH->pbuf)) = 0x37;

    b = dg_popbufferbyte(&BHarrayhead, bufid);

    if (b != 0x37)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte dg_success case - got wrong byte\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferbyte dg_success case - got an error\n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_pushbufferbyte()
{
    // need to add test for dg_success case where the error count isn't 0
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 bufid = 0;
    Bufferhandle* pBH = NULL;

    const char* pError = NULL;

    unsigned char b = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushbufferbyte\n");

    // error getting buffer segment case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte error pushing buffer segment case - unable to initialize error stack\n");
        return;
    }

    dg_pushbufferbyte(&BHarrayhead, 1, 0x45); // buffer 1 doesn't exist so this is an error

    if (dg_poperror(&BHarrayhead) != dg_pushbufferbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte error putting buffer segment case - got wrong error on top\n");
    }

    if (dg_poperror(&BHarrayhead) != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte error putting buffer segment case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case - only checking 1 because I know get buffer segment works
    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte dg_success case - error initializing buffer\n");
        return;
    }

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[bufid] );

    *((unsigned char*)(pBH->pbuf)) = 0x0;

    dg_pushbufferbyte(&BHarrayhead, bufid, 0xC1);

    b = *((unsigned char*)(pBH->pbuf));

    if (b != 0xC1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte dg_success case - pushed wrong byte\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushbufferbyte dg_success case - got an error\n");
    }

    dg_clearerrors(&BHarrayhead);

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_popbufferuint64()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_popbufferuint64\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    data = dg_popbufferuint64((Bufferhandle*)badbufferhandle, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 null pBHarrayhead case - didn't get 0 return\n");
    }
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;

    data = dg_popbufferuint64(&BHarrayhead, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 no BHarray case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 no BHarray case - error count not incremented\n");
    }

    BHarrayhead.errorcount = 0;
#endif    
    //  The buffer id is for the errorstack.) (use dg_pusherror to put errors on the error stack
#ifndef DGLU_NO_DIAPER
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is for the errorstack case - could not initialize error stack\n");
    }

    data = dg_popbufferuint64(&BHarrayhead, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is for the errorstack case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is for the errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is for the errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is for the errorstack case - got wrong error 1 below top\n");
    }

    dg_freebuffer(&BHarrayhead, 0);
    
    //  The buffer id is off the end of the buffer handle array
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is off the end case - could not initialize error stack\n");
    }

    data = dg_popbufferuint64(&BHarrayhead, 1);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is off the end case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is off the end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is off the end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 buffer id is off the end case - got wrong error 1 below top\n");
    }

    dg_freebuffer(&BHarrayhead, 0);
    
    //  The buffer id is for a buffer handle with no buffer attached.
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - could not initialize error stack\n");
    }

    i = dg_newbuffer(&BHarrayhead, 2 * sizeof(const char*), 4 * sizeof(const char*), &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - could not initialize test buffer\n");
    }

    dg_freebuffer(&BHarrayhead, i);

    data = dg_popbufferuint64(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 free buffer case - got wrong error 1 below top\n");
    }

    dg_freebuffer(&BHarrayhead, 0);

#endif
    // corrupt buffer case, nextunusedbyte > size
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - could not initialize error stack\n");
    }

    x = dg_getpagesize();

    if (dg_getpagesize() < (4 * sizeof(const char*)))
    {
       x = 4 * sizeof(const char*);
    }

    i = dg_newbuffer(&BHarrayhead, x, 2 * x, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - could not initialize new buffer\n");
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = (2*x)+1; 

    data = dg_popbufferuint64(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 corrupt buffer case - got wrong error 1 below top\n");
    }

    pBH->nextunusedbyte = 0;

    dg_freebuffer(&BHarrayhead, 1);

    dg_freebuffer(&BHarrayhead, 0);

    // underflow case
#ifndef DGLU_NO_DIAPER
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - could not initialize error stack\n");
    }

    x = dg_getpagesize();

    if (dg_getpagesize() < (4 * sizeof(const char*)))
    {
        x = 4 * sizeof(const char*);
    }

    i = dg_newbuffer(&BHarrayhead, x, 2 * x, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - could not initialize new buffer\n");
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = 3;
    
    data = dg_popbufferuint64(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 underflow case - got wrong error 1 below top\n");
    }

    pBH->nextunusedbyte = 0;

    dg_freebuffer(&BHarrayhead, 1);

    dg_freebuffer(&BHarrayhead, 0);

#endif
    
    // dg_success case almost empty buffer
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 almost empty buffer case - could not initialize error stack\n");
    }

    x = dg_getpagesize();

    if (dg_getpagesize() < (4 * sizeof(const char*)))
    {
        x = 4 * sizeof(const char*);
    }

    i = dg_newbuffer(&BHarrayhead, x, 2 * x, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 almost empty buffer case - could not initialize new buffer\n");
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_pushbufferuint64(&BHarrayhead, i, 0x1234567898765432);

    data = dg_popbufferuint64(&BHarrayhead, i);

    if (data != 0x1234567898765432)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64almost empty buffer case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 almost empty buffer case - error count not 0\n");
    }

    dg_freebuffer(&BHarrayhead, 1);

    dg_freebuffer(&BHarrayhead, 0);

    // dg_success case full buffer
    dg_initerrors(&BHarrayhead, 32 * 2 * sizeof(const char*), &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 success full buffer case - could not initialize error stack\n");
    }

    x = dg_getpagesize();

    if (dg_getpagesize() < (4 * sizeof(const char*)))
    {
        x = 4 * sizeof(const char*);
    }

    i = dg_newbuffer(&BHarrayhead, x, x, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 success full buffer case - unable to allocate buffer, got error ");
            dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = x - (2 * sizeof(UINT64)); 
    dg_pushbufferuint64(&BHarrayhead, i, 0x8899445511338844);
    dg_pushbufferuint64(&BHarrayhead, i, 0x2233446677439815);

    data = dg_popbufferuint64(&BHarrayhead, i);

    if (data != 0x2233446677439815)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 dg_success case full buffer - didn't get same back\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint64 dg_success case full buffer - error count not 0\n");
    }

    dg_freebuffer(&BHarrayhead, 1);

    dg_freebuffer(&BHarrayhead, 0);

    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_popbufferuint32()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT32 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_popbufferuint32\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    data = dg_popbufferuint32((Bufferhandle*)badbufferhandle, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 null pBHarrayhead case - didn't get 0 return\n");
    }
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;

    data = dg_popbufferuint32(&BHarrayhead, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 no BHarray case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 no BHarray case - error count not incremented\n");
    }

    BHarrayhead.errorcount = 0;
#endif    
    //  The buffer id is for the errorstack.) (use dg_pusherror to put errors on the error stack
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    data = dg_popbufferuint32(&BHarrayhead, 0);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is for the errorstack case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is for the errorstack case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is for the errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is for the errorstack case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is off the end of the buffer handle array
    data = dg_popbufferuint32(&BHarrayhead, 1);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is off the end case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is off the end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is off the end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 buffer id is off the end case - got wrong error 1 below top\n");
    }
    
    //  The buffer id is for a buffer handle with no buffer attached.
    i = dg_newbuffer(&BHarrayhead, 10, 20,&pError, FORTH_FALSE);

    dg_freebuffer(&BHarrayhead, i);

    data = dg_popbufferuint32(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 free buffer case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 free buffer case - got wrong error 1 below top\n");
    }
#endif
    // corrupt buffer case, nextunusedbyte > size
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), 2*dg_getpagesize(),&pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = dg_getpagesize()+1; 

    data = dg_popbufferuint32(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 corrupt buffer case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 corrupt buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 corrupt buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 corrupt buffer case - got wrong error 1 below top\n");
    }

    pBH->nextunusedbyte = 0;

    // underflow case
    pBH->nextunusedbyte = 3;
    
    data = dg_popbufferuint32(&BHarrayhead, i);

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 underflow case - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 underflow case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint32name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 underflow case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 underflow case - got wrong error 1 below top\n");
    }

#endif
    pBH->nextunusedbyte = 0;
    
    // dg_success case almost empty buffer
    dg_pushbufferuint32(&BHarrayhead, i, 0x12345678);

    data = dg_popbufferuint32(&BHarrayhead, i);

    if (data != 0x12345678)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 dg_success case almost empty buffer - didn't get 0 return\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 dg_success case almost empty buffer - error count not 0\n");
    }

    // dg_success case full buffer
    i = dg_newbuffer(&BHarrayhead, dg_getpagesize(), dg_getpagesize(), &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = dg_getpagesize() - 8; // assuming pagesize is multiple of 4 and >= 4
    dg_pushbufferuint32(&BHarrayhead, i, 0x88994455);
    dg_pushbufferuint32(&BHarrayhead, i, 0x22334466);

    data = dg_popbufferuint32(&BHarrayhead, i);

    if (data != 0x22334466)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 dg_success case full buffer - didn't get same back\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_popbufferuint32 dg_success case full buffer - error count not 0\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 1);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_insertinbuffer()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_insertinbuffer\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    dg_insertinbuffer((Bufferhandle*)badbufferhandle, 0, 0, 10); // crash test

    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    dg_insertinbuffer(&BHarrayhead, 0, 0, 10);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer no bharray case - error count not incremented\n");
    }

    BHarrayhead.errorcount = 0;
#endif    
    //  The buffer id is for the errorstack.
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    dg_insertinbuffer(&BHarrayhead, 0, 0, 10);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer no bharray case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer no bharray case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer no bharray case - got wrong error 1 below top\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    //  The buffer id is off the end of the buffer handle array
    dg_insertinbuffer(&BHarrayhead, 1, 0, 10);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer buffer id off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer buffer id off end case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer buffer id off end case - got wrong error 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    //  The buffer id is for a buffer handle with no buffer attached.
    i = dg_newbuffer(&BHarrayhead, 16, 32, &pError, FORTH_FALSE);
    dg_freebuffer(&BHarrayhead, i);

    dg_insertinbuffer(&BHarrayhead, i, 0, 10);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer free buffer case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer free buffer case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer free buffer case - got wrong error 1 below top\n");
    }
    
    //  Offset is after the end of the buffer's in use area (It can be at the end.)
    // pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]); ?
#endif
    i = dg_newbuffer(&BHarrayhead, 16, 32, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    dg_insertinbuffer(&BHarrayhead, i, 17, 10);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer off end case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer off end case - got wrong error on top");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_offsetpastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer off end case - got wrong error 1 below top");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer off end case - buffer length changed\n");
    }
    
    //  Inserting the bytes would cause the buffer to exceed it's maximum allowed size
    dg_insertinbuffer(&BHarrayhead, i, 0, pBH->maxsize + 1);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer exceed maxsize case - error count not incremented\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_insertinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer exceed maxsize case - got wrong error on top");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferfullerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer exceed maxsize case - got wrong error 1 below top");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer exceed maxsize case - buffer length changed\n");
    }
    
    //  There was an error trying to grow the buffer
    //   can't test this case because all grow errors except out of mem are caught
    //   by dg_insertinbuffer.. unless I were to add force out of mem to dg_insertinbuffer
#endif
    // dg_success case at beginning
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    pBH->nextunusedbyte = 0;

    dg_pushbufferuint64(&BHarrayhead, i, 0x9988776600112233);
    dg_pushbufferuint64(&BHarrayhead, i, 0x4455667755337722);

    dg_insertinbuffer(&BHarrayhead, i, 0, 4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at beginning - got error\n");
    }

    // 33221100 33221100 66778899 22773355 77665544
    data = dg_getbufferuint64(&BHarrayhead, i, 0); // data in the insert area should have been left alone

    if (data != 0x0011223300112233)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at beginning - data at 0 changed\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);
    
    if (data != 0x5533772299887766)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at beginning - data at 8 incorrect\n");
    }

    if (pBH->nextunusedbyte != 0x14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at beginning - next unused byte incorrect\n");
    }

    // dg_success case insert at end
    dg_insertinbuffer(&BHarrayhead, i, 0x14, 4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at end - got error\n");
    }

    // 33221100 33221100 66778899 22773355 77665544 77665544
    data = dg_getbufferuint64(&BHarrayhead, i, 0); 

    if (data != 0x0011223300112233)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at end - data at 0 changed\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);
    
    if (data != 0x5533772299887766)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at end - data at 8 changed, expected 0x5533772299887766 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 0x10);
    
    if ((data & 0xffffffff) != 0x44556677)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at end - data at 16 changed, expected 0x4455667744556677 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, data);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");    }

    if (pBH->nextunusedbyte != 0x18)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer dg_success case at end - next unused byte incorrect\n");
    }

    // insert 0 bytes case
    dg_insertinbuffer(&BHarrayhead, i, 4, 0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer insert 0 bytes case - got error\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 0); 

    if (data != 0x0011223300112233)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer insert 0 bytes case - data at 0 changed\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 8);
    
    if (data != 0x5533772299887766)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer insert 0 bytes case - data at 8 changed\n");
    }

    if (pBH->nextunusedbyte != 0x18)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_insertinbuffer insert 0 bytes case - next unused byte incorrect\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_deleteinbuffer()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_deleteinbuffer\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    dg_deleteinbuffer((Bufferhandle*)badbufferhandle, 0, 0, 10); // crash test
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    dg_deleteinbuffer(&BHarrayhead, 0, 0, 10);

    if (BHarrayhead.errorcount == 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer no bharray case - didn't get error\n");
    }

    BHarrayhead.errorcount = 0;
#endif    
    //  The buffer id is for the errorstack. 
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    dg_deleteinbuffer(&BHarrayhead, 0, 0, 10);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer id for error stack case - didn't get error\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer id for error stack case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer id for error stack case - error incorrect 1 below top\n");
    }
    
    //  The buffer id is off the end of the buffer handle array
    dg_deleteinbuffer(&BHarrayhead, 1, 0, 10);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer id off end case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer id off end case - error incorrect 1 below top\n");
    }
   
    //  The buffer id is for a buffer handle with no buffer attached.
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    dg_freebuffer(&BHarrayhead, i);

    dg_deleteinbuffer(&BHarrayhead, i, 0, 5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer free buffer case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer free buffer case - error incorrect 1 below top\n");
    }
#endif    
    //  Offset + length is after the end of the buffer's in use area (It can be at the end.)
    i = dg_newbuffer(&BHarrayhead, 20, 40, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = 10;

    dg_deleteinbuffer(&BHarrayhead, i, 0, 11);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case a - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case a - error incorrect 1 below top\n");
    }

    dg_deleteinbuffer(&BHarrayhead, i, 10, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case b - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case b - error incorrect 1 below top\n");
    }

    dg_deleteinbuffer(&BHarrayhead, i, 9, 2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_deleteinbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case c - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_segmentgoespastenderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer off end case c - error incorrect 1 below top\n");
    }

    dg_clearerrors(&BHarrayhead);

    // length 0 case
    dg_deleteinbuffer(&BHarrayhead, i, 11, 0);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer length 0 case c - got error \n");
    }
#endif
    // dg_success case - delete at beginning
    pBH->nextunusedbyte = 0;

    dg_pushbufferuint64(&BHarrayhead, i, 0x4455667700112233);
    dg_pushbufferuint64(&BHarrayhead, i, 0x665544cc8899aabb);

    // 33221100 77665544 bbaa9988 cc445566
    dg_deleteinbuffer(&BHarrayhead, i, 0, 4);

    if (pBH->nextunusedbyte != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_deleteinbuffer dg_success case delete at beginning - next unused byte incorrect\n");
    }

    // 77665544 bbaa9988 cc445566
    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x8899aabb44556677)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_deleteinbuffer dg_success case delete at beginning - data at 0 wrong\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer dg_success case delete at beginning - got error \n");
    }

    // dg_success case - delete at end

    dg_deleteinbuffer(&BHarrayhead, i, 8, 4);

    if (pBH->nextunusedbyte != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_deleteinbuffer dg_success case delete at end - next unused byte incorrect\n");
    }

    data = dg_getbufferuint64(&BHarrayhead, i, 0);

    if (data != 0x8899aabb44556677)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_deleteinbuffer dg_success case delete at end - data at 0 wrong\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_deleteinbuffer dg_success case delete at end - got error \n");
    }

    pBH->nextunusedbyte= 8; // checking to make sure stuff off end didn't get changed

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getbufferlength()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 data = 0;
    UINT64 tempsize = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getbufferlength\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    data = dg_getbufferlength(NULL, 0); // crash test
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    data = dg_getbufferlength(&BHarrayhead, 0);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength no bharray case - didn't get error\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength no bharray case - return not 0\n");
    }

    BHarrayhead.errorcount = 0;
#endif    
    //  The buffer id is for the errorstack. 
    dg_initerrors(&BHarrayhead, 100, &pError);
#ifndef DGLU_NO_DIAPER
    data = dg_getbufferlength(&BHarrayhead, 0);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id for error stack case - didn't get error\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id for error stack case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id for error stack case - error incorrect 1 below top\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id for error stack case - return not 0\n");
    }
    
    //  The buffer id is off the end of the buffer handle array
    data = dg_getbufferlength(&BHarrayhead, 2);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id off end case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id off end case - error incorrect 1 below top\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength id off end case - return not 0\n");
    }
    
    //  The buffer id is for a buffer handle with no buffer attached.
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    dg_freebuffer(&BHarrayhead, i);

    dg_getbufferlength(&BHarrayhead, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength free buffer case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength free buffer case - error incorrect 1 below top\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength free buffer case - return not 0\n");
    }

    // didn't check nub of bharray corrupt case
#endif
    // nub of buffer corrupt case
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);
#ifndef DGLU_NO_DIAPER
    pBH->nextunusedbyte = pBH->size + 1; // forcing nub to be > size

    data = dg_getbufferlength(&BHarrayhead, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength nub corrupt case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength nub corrupt case - error incorrect 1 below top\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength nub corrupt case - return not 0\n");
    }

    pBH->nextunusedbyte = 0;
#endif
    // size > maxsize case
    tempsize = pBH->size;
#ifndef DGLU_NO_DIAPER
    pBH->size = pBH->maxsize + 1;

    data = dg_getbufferlength(&BHarrayhead, 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbufferlengthname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength size corrupt case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_buffermaxsizeltsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength size corrupt case - error incorrect 1 below top\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength size corrupt case - return not 0\n");
    }

    pBH->size = tempsize;
#endif
    // dg_success case
    dg_pushbufferuint64(&BHarrayhead, 1, 0x1122334455667788);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushbufferuint64 dg_success case - got error \n");
    }

    data = dg_getbufferlength(&BHarrayhead, 1);

    if (data != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getbufferlength dg_success case - got wrong buffer size\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_getpbufferhandle()
{
//    unsigned int tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i;
    UINT64 data = 0;
//    unsigned int tempsize = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getpbufferhandle\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is NULL
    pBH = dg_getpbufferhandle(NULL, 0); // crash test
    
    //  There is no memory allocated for the buffer handle array
    BHarrayhead.errorcount = 0;
    pBH = dg_getpbufferhandle(&BHarrayhead, 0);

    if (BHarrayhead.errorcount == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle no bharray case - didn't get error\n");
    }

    if (data != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle no bharray case - return not 0\n");
    }

    BHarrayhead.errorcount = 0;

    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);
    
    //  The buffer id is off the end of the buffer handle array
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle id off end case - got error initializing error stack buffer\n");
    }
    
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle id off end case - got error making a new buffer\n");
    }

    pBH = dg_getpbufferhandle(&BHarrayhead, 3984); // over by 1 case checked in another test for same calculation

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbufferhandlename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle id off end case - error incorrect on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle id off end case - error incorrect 1 below top\n");
    }

    if (pBH != (Bufferhandle*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle id off end case - return not NULL\n");
    }
    
    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);
#endif
    
    // dg_success case 0
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got error initializing error stack buffer\n");
    }

    pBH = dg_getpbufferhandle(&BHarrayhead, 0);

    if (pBH != (Bufferhandle*)(BHarrayhead.pbuf) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got wrong bufferhandle\n");

    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got error \n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    // dg_success case 1
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got error initializing error stack buffer\n");
    }
    
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got error making a new buffer\n");
    }

    pBH = dg_getpbufferhandle(&BHarrayhead, 1);

    if (pBH != ((Bufferhandle*)(BHarrayhead.pbuf) + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got wrong bufferhandle\n");

    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpbufferhandle dg_success case - got error \n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_push0stringtobuffersegment()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;

    UINT64 bufid = 0, i;


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_push0stringtobuffersegment\n");

#ifndef DGLU_NO_DIAPER
    //  The pointer to the 0 string is NULL
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment The pointer to the 0 string is NULL - got error initializing error stack buffer\n");
    }
    
    i = dg_newbuffer(&BHarrayhead, 10, 20, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment The pointer to the 0 string is NULL - got error making a new buffer\n");
    }
    

    dg_push0stringtobuffersegment(&BHarrayhead, 0, (unsigned char*)badbufferhandle); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_push0stringtobuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment The pointer to the 0 string is NULL - didn't get expected error on top\n");
        
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_nullpointererror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment The pointer to the 0 string is NULL - didn't get expected error 1 below top\n");
        
    }

    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);

    
    //  bad memory case 
    //  - this check does not work on FreeBSD, dg_scanforbyte from -3 does not throw a signal
    /*
    dg_initbuffers(&BHarrayhead);

    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    dg_push0stringtobuffersegment(&BHarrayhead, bufid, (unsigned char*)-3); // hopefully -3 is a bad memory address

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_push0stringtobuffersegmentbadmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment bad memory case - didn't get expected error got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
    }

    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);
    */


    // error pushing buffer segment case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment error pushing buffer segment case - got error initializing error stack buffer\n");
    }

    dg_push0stringtobuffersegment(&BHarrayhead, 
        DG_ERRORSTACK_BUFFERID,                        // not allowed to push to error stack
        (unsigned char*)dg_badmemoryerror); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_push0stringtobuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment error pushing buffer segment case - didn't get expected error on top\n");
        
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment error pushing buffer segment case - didn't get expected error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment error pushing buffer segment case - didn't get expected error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
#endif

    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment dg_success case - got error initializing error stack buffer\n");
    }

    bufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment dg_success case - couldn't initialize buffer\n");
    }

    dg_push0stringtobuffersegment(&BHarrayhead, 
        bufid,
        (unsigned char*)dg_badmemoryerror); 


    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_push0stringtobuffersegment dg_success case - got an error\n");
        
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_checkbuffer()
{
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 bufid1, bufid2;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_checkbuffer\n");
#ifndef DGLU_NO_DIAPER
    //  The pointer to the buffer handle array head is badbufferhandle
    pError = dg_checkbuffer(&BHarrayhead, (UINT64)badbufferhandle); // crash test
    
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer bad bharray handle case - didn't get error\n");
    }

    
    //  The buffer id is off the end of the bufferhandle array
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer id off end case - got error initializing error stack buffer\n");
    }

    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer id off end case - couldn't initialize buffer\n");
    }

    pError = dg_checkbuffer(&BHarrayhead, 12345); 

    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer id off end case - error on top not dg_bufferidnotinbharray, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
#endif    
    // dg_success case 0
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer dg_success case 0 - got error initializing error stack buffer\n");
    }

    pError = dg_checkbuffer(&BHarrayhead, 0);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer dg_success case 0 - got error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    // dg_success case 1
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer dg_success case 1 - got error initializing error stack buffer\n");
    }

    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer dg_success case 1 - couldn't initialize buffer\n");
    }

    pError = dg_checkbuffer(&BHarrayhead, 0);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer dg_success case 1 - got error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
#ifndef DGLU_NO_DIAPER    
    // checking a buffer that was freed at the end of the bufferhandle array
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer off end case - got error initializing error stack buffer\n");
    }

    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer off end case - couldn't initialize buffer\n");
    }
    
    dg_freebuffer(&BHarrayhead, bufid1);

    pError = dg_checkbuffer(&BHarrayhead, bufid1);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer off end case - got wrong error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // checking a buffer that was freed in middle of BHarray case
    // dg_initbuffers(&BHarrayhead);
    
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer in middle case - got error initializing error stack buffer\n");
    }

    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer in middle case - couldn't initialize buffer\n");
    }
    
    bufid2 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer in middle case - couldn't initialize buffer 2\n");
    }
    
    dg_freebuffer(&BHarrayhead, bufid1);

    pError = dg_checkbuffer(&BHarrayhead, bufid1);

    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_checkbuffer free buffer in middle case - got wrong error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    #endif
}


void testdg_freebufferset()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = (const char*)badbufferhandle;

    UINT64 bufid1 = (UINT64)badbufferhandle;
    UINT64 bufid2 = (UINT64)badbufferhandle;
    UINT64 bufid3 = (UINT64)badbufferhandle;
    
    UINT64 buffersetheaderbufferid = (UINT64)badbufferhandle;


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freebufferset\n");

#ifndef DGLU_NO_DIAPER
    //  Error getting pointer to buffersetheader buffer and it's length
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset bad buffersetheader bufferid case - got error initializing error stack buffer\n");
    }

    dg_freebufferset(&BHarrayhead, (UINT64)badbufferhandle);
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_freebuffersetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset bad buffersetheader bufferid case - got wrong error on top of error stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);


    // Buffersetheader array of buffer ids length in bytes is not a multiple of the size of a buffer id
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset misaligned case - got error initializing error stack buffer\n");
    }
    
    buffersetheaderbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset misaligned case - couldn't initialize buffersetheader buffer\n");
    }

    dg_pushbufferbyte(&BHarrayhead, buffersetheaderbufferid, 5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset misaligned case - got error setting up test while pushing byte to buffersetheader buffer\n");
    }
    
    dg_freebufferset(&BHarrayhead, buffersetheaderbufferid);
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_freebuffersetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset  misaligned case - got wrong error on top of error stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_arraymisalignederror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset  misaligned case - got wrong error one below top of error stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    
    
    // dg_success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - got error initializing error stack buffer\n");
    }
    
    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - couldn't initialize buffer1\n");
    }
    
    bufid2 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - couldn't initialize buffer2\n");
    }
    
    bufid3 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - couldn't initialize buffer2\n");
    }
    
    buffersetheaderbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - couldn't initialize buffersetheader buffer\n");
    }
    
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - error after pushing bufferid of buffer 1 to buffersetheader buffer\n");
    }
    
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - error after pushing bufferid of buffer 2 to buffersetheader buffer\n");
    }
    
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - error after pushing bufferid of buffer 3 to buffersetheader buffer\n");
    }
    
    dg_freebufferset(&BHarrayhead, buffersetheaderbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - got an error freeing the bufferset\n");
        
    }
    
    // checking the buffers to make sure they are really free
    pError = dg_checkbuffer(&BHarrayhead, bufid1);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - 1st test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer1 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid2);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - 2nd test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer2 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid2);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid3);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - 3rd test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer3 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, buffersetheaderbufferid);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case - header buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer3 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    
    
    // dg_success case with badbufferhandle in bufferset
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - got error initializing error stack buffer\n");
    }
    
    bufid1 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - couldn't initialize buffer1\n");
    }
    
    bufid2 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - couldn't initialize buffer2\n");
    }
    
    bufid3 = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - couldn't initialize buffer2\n");
    }
    
    buffersetheaderbufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - couldn't initialize buffersetheader buffer\n");
    }
    
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid1);
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid2);
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, (UINT64)badbufferhandle);
    dg_pushbufferuint64(&BHarrayhead, buffersetheaderbufferid, bufid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - couldn't push test case buffer ids to buffersetheader buffer\n");
    }
    
    dg_freebufferset(&BHarrayhead, buffersetheaderbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - got an error freeing the bufferset\n");
        
    }
    
    // checking the buffers to make sure they are really free
    pError = dg_checkbuffer (&BHarrayhead, bufid1);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - 1st test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer1 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid2);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - 2nd test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer2 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid2);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid3);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - 3rd test buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer3 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, buffersetheaderbufferid);
    
    if (pError != dg_bufferidisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case with badbufferhandle in bufferset - header buffer in bufferset was not freed. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer3 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif

    // need to check to make sure this routine is accessing beyond end of buffer (put 4 in and drop 1)
    
}


void testdg_newbufferset()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;

    UINT64 bufid1 = (UINT64)badbufferhandle;
    UINT64 bufid2 = (UINT64)badbufferhandle;
    UINT64 bufid3 = (UINT64)badbufferhandle;
    
    UINT64 buffersetheaderbufferid = (UINT64)badbufferhandle;
    
    UINT64 bufferlength = 0;


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newbufferset\n");


    //  Success case 5 buffers
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success case 3 buffers case - got error initializing error stack buffer\n");
    }

    buffersetheaderbufferid = dg_newbufferset(&BHarrayhead, 1000, 5000, 3);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset success 3 buffers case - got an error making the new bufferset, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    bufferlength = dg_getbufferlength(&BHarrayhead, buffersetheaderbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset success 3 buffers case - got an error getting the buffer header's length, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (bufferlength != 3 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset dg_success 3 buffers case - buffer header length incorrect expected 12 bytes. Got ");
        dg_writestdoutuinttodec(&BHarrayhead, bufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufid3 = dg_popbufferuint64(&BHarrayhead, buffersetheaderbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset success 3 buffers case - got an error popping buffer 3's id, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    bufid2 = dg_popbufferuint64(&BHarrayhead, buffersetheaderbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset success 3 buffers case - got an error popping buffer 2's id, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    bufid1 = dg_popbufferuint64(&BHarrayhead, buffersetheaderbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
       pError = dg_poperror(&BHarrayhead);
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset success 3 buffers case - got an error popping buffer 1's id, got ");
       dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
       dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
       dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid3);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset dg_success 3 buffers case - buffer 3 not in use. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer3 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_checkbuffer (&BHarrayhead, bufid2);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset dg_success 3 buffers case - buffer 2 not in use. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer2 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid2);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    pError = dg_checkbuffer (&BHarrayhead, bufid1);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset dg_success 3 buffers case - buffer 1 not in use. Got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", buffer1 id was ");
        dg_writestdoutuinttodec(&BHarrayhead, bufid1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // test number of buffers would overflow indexing calculation
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freebufferset number of buffers overflows indexing calculation case - got error initializing error stack buffer\n");
    }

    buffersetheaderbufferid = dg_newbufferset(&BHarrayhead, 1000, 5000, 0x2000000000000000);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_newbuffersetname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset number of buffers overflows indexing calculation case - Got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_invalidparametererror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newbufferset number of buffers overflows indexing calculation case - Got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    // test dg_calcnearestpagesize calculation rounds down
    //   might not be able to do this test unless I know what pagesize is
}


void testdg_getuint64arrayelement()
{
    Bufferhandle BHarrayhead;
    
    UINT64 arraybufid, x;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getuint64arrayelement\n");


    //  Success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error initializing error stack buffer\n");
    }
    
    arraybufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x1191817161514131);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error pushing 1st number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x2292827262524232);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error pushing 2nd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x3393837363534331);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error pushing 3rd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error getting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x1191817161514131)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got wrong element, expected 0x11918171, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error getting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x2292827262524232)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got wrong element, expected 0x22928272, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got error getting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x3393837363534331)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement success case - got wrong element, expected 0x33938373, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    // index off end or array case
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 3);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getuint64arrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement index off end case - got wrong error on top. Expected dg_getuint32arrayelementname, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement index off end case - got wrong error 1 below top. Expected dg_getbufferuint64name, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // index to offset calculation would overflow
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 0x2000000000000000);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getuint64arrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelement index calculation overflow case - got wrong error on top. Expected dg_getuint32arrayelementname, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64arrayelementƒ index calculation overflow case - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_putuint64arrayelement()
{
    Bufferhandle BHarrayhead;
    
    UINT64 arraybufid, x;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putuint64arrayelement\n");


    //  Success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error initializing error stack buffer\n");
    }
    
    arraybufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x1191817161514131);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error pushing 1st number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x2292827262524232);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error pushing 2nd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x3393837363534331);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error pushing 3rd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_putuint64arrayelement(&BHarrayhead, arraybufid, 0, 0x5141312161718191);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error putting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_putuint64arrayelement(&BHarrayhead, arraybufid, 1, 0x5242322282736758);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error putting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
     dg_putuint64arrayelement(&BHarrayhead, arraybufid, 2, 0x5343332391817161);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error putting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error getting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5141312161718191)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got wrong element, expected 0x51413121, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error getting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5242322282736758)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got wrong element, expected 0x52423222, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got error getting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5343332391817161)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement success case - got wrong element, expected 0x53433323, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    // index off end or array case
    dg_putuint64arrayelement(&BHarrayhead, arraybufid, 3, 0);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64arrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement index off end case - got wrong error on top. Expected dg_putuint32arrayelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement index off end case - got wrong error 1 below top. Expected dg_putbufferuint64name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // index to offset calculation would overflow
    dg_putuint64arrayelement(&BHarrayhead, arraybufid, 0x2000000000000000, 0);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64arrayelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement index calculation overflow case - got wrong error on top. Expected dg_putuint32arrayelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64arrayelement index calculation overflow case - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getuint64stackelement()
{
    Bufferhandle BHarrayhead;
    
    UINT64 arraybufid, x;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getuint64stackelement\n");


    //  Success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error initializing error stack buffer\n");
    }
    
    arraybufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x1191817161514131);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error pushing 1st number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x229282728292a2b2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error pushing 2nd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x3393837363534332);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error pushing 3rd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error getting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x3393837363534332)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got wrong element, expected 0x33938373, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error getting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x229282728292a2b2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got wrong element, expected 0x22928272, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, 2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got error getting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x1191817161514131)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement success case - got wrong element, expected 0x11918171, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    // index off end or array case
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, 3);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index off end case - got wrong error on top. Expected dg_getuint32stackelementname, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index off end case - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // index to offset calculation would overflow
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, 0x2000000000000000);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index calculation overflow case - got wrong error on top. Expected dg_getuint32stackelementname, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index calculation overflow case - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // index to offset calculation would overflow case 2
    x = dg_getuint64stackelement(&BHarrayhead, arraybufid, (UINT32)-1);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index calculation overflow case 2 - got wrong error on top. Expected dg_getuint32stackelementname, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuint64stackelement index calculation overflow case 2 - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_putuint64stackelement()
{
    Bufferhandle BHarrayhead;
    
    UINT64 arraybufid, x;
    
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);


    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_putuint64stackelement\n");


    //  Success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error initializing error stack buffer\n");
    }
    
    arraybufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x11918171);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error pushing 1st number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x22928272);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error pushing 2nd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_pushbufferuint64(&BHarrayhead, arraybufid, 0x33938373);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error pushing 3rd number onto array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_putuint64stackelement(&BHarrayhead, arraybufid, 0, 0x5141312161718191);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error putting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_putuint64arrayelement(&BHarrayhead, arraybufid, 1, 0x5242322262728292);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error putting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
     dg_putuint64stackelement(&BHarrayhead, arraybufid, 2, 0x5343332363738393);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error putting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error getting element 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5343332363738393)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got wrong element, expected 0x53433323, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error getting element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5242322262728292)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got wrong element, expected 0x52423222, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_getuint64arrayelement(&BHarrayhead, arraybufid, 2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got error getting element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0x5141312161718191)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement success case - got wrong element, expected 0x51413121, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    // index off end or array case
    dg_putuint64stackelement(&BHarrayhead, arraybufid, 3, 0);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index off end case - got wrong error on top. Expected dg_putuint32stackelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index off end case - got wrong error 1 below top. Expected dg_putbufferuint64name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    // index to offset calculation would overflow
    dg_putuint64stackelement(&BHarrayhead, arraybufid, 0x2000000000000000, 0);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index calculation overflow case - got wrong error on top. Expected dg_putuint32stackelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index calculation overflow case - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    // index to offset calculation would overflow case 2
    dg_putuint64stackelement(&BHarrayhead, arraybufid, (UINT64)-1, 0);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_putuint64stackelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index calculation overflow case 2 - got wrong error on top. Expected dg_putuint32stackelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_indexnotinarrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_putuint64stackelement index calculation overflow case 2 - got wrong error 1 below top. Expected dg_indexnotinarrayerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_stonewbuffer()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    Bufferhandle* psrcBH;
    unsigned char* psrcbuf;
    UINT64 srcbufid;
    UINT64 srcbuflength;
    
    Bufferhandle* pnewBH;
    unsigned char* pnewbuf;
    UINT64 newbufid;


    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_stonewbuffer\n");

    
    //  Simple success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Simple success case - got error initializing error stack buffer\n");
    }
    
    srcbuflength = 1;
    
    srcbufid = dg_newbuffer(
        &BHarrayhead, 
        srcbuflength,
        (UINT64)-1,
        &pError, 
        FORTH_FALSE);
    
    psrcBH = dg_getpbufferhandlefast(&BHarrayhead, srcbufid);
    psrcbuf = (unsigned char*)psrcBH->pbuf;
    
    psrcbuf[0] = 'J';
    
    newbufid = dg_stonewbuffer(&BHarrayhead, dg_getpagesize(), (UINT64)-1, psrcbuf, srcbuflength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Simple success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pnewBH = dg_getpbufferhandlefast(&BHarrayhead, newbufid);
    pnewbuf = (unsigned char*)pnewBH->pbuf;
    
    if (pnewbuf[0] != 'J')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Simple success case - first character not copied.\n");
    }
    
    if (pnewBH->nextunusedbyte != srcbuflength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Simple success case - length not correct.\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //  Larger than one page size success case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Larger than one page size success case - got error initializing error stack buffer\n");
    }
    
    srcbuflength = (3 * dg_getpagesize()) + 1;
    
    srcbufid = dg_newbuffer(
        &BHarrayhead, 
        srcbuflength,
        (UINT64)-1,
        &pError, 
        FORTH_FALSE);
    
    psrcBH = dg_getpbufferhandlefast(&BHarrayhead, srcbufid);
    psrcbuf = (unsigned char*)psrcBH->pbuf;
    
    psrcbuf[0] = 'a';
    psrcbuf[srcbuflength - 1] = 'z';
    
    newbufid = dg_stonewbuffer(&BHarrayhead, dg_getpagesize(), (UINT64)-1, psrcbuf, srcbuflength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Larger than one page size success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pnewBH = dg_getpbufferhandlefast(&BHarrayhead, newbufid);
    pnewbuf = (unsigned char*)pnewBH->pbuf;
    
    if (pnewbuf[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Larger than one page size success case - first character not copied.\n");
    }
    
    if (pnewbuf[pnewBH->nextunusedbyte -1] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Larger than one page size success case - last character not copied.\n");
    }
    
    if (pnewBH->nextunusedbyte != srcbuflength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Larger than one page size success case - length not correct.\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    
    
    
    //  Maxsize too small error case
    // dg_initbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Maxsize too small error case - got error initializing error stack buffer\n");
    }
    
    srcbuflength = (3 * dg_getpagesize()) + 1;
    
    srcbufid = dg_newbuffer(
        &BHarrayhead, 
        srcbuflength,
        (UINT64)-1,
        &pError, 
        FORTH_FALSE);
    
    psrcBH = dg_getpbufferhandlefast(&BHarrayhead, srcbufid);
    psrcbuf = (unsigned char*)psrcBH->pbuf;
    
    psrcbuf[0] = 'a';
    psrcbuf[srcbuflength - 1] = 'z';
    
    newbufid = dg_stonewbuffer(&BHarrayhead, dg_getpagesize(), srcbuflength-1, psrcbuf, srcbuflength);

    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_stonewbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_stonewbuffer Maxsize too small error case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getpnewbuffer ()
{
    Bufferhandle BHarrayhead;
    
    UINT64 bufferid;
    UINT64 bufferlength;
    const char* pError;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getpnewbuffer\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_getpnewbuffer(
        &BHarrayhead,
        0x2017);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpnewbuffer success case - got an error doing dg_getpnewbuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    bufferid = dg_popbufferuint64(&BHarrayhead, DG_LINKNEWBUFFERIDSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpnewbuffer success case - got an error getting buffer id, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    bufferlength = dg_getbufferlength(&BHarrayhead, bufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpnewbuffer success case - got an error getting buffer length, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    if (bufferlength != 0x2017)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getpnewbuffer success case - got wrong buffer length, expected 0x2017, got ");
        dg_writestdoutuinttodec(&BHarrayhead, bufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_pushhctwotobuffer()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
    UINT64 i = 0;
    UINT64 pud[2];
    unsigned char c;

    pud[0] = 0;
    pud[1] = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushhctwotobuffer\n");
#ifndef DGLU_NO_DIAPER
    // null pBHarrayhead case - crash test
    dg_pushhctwotobuffer((Bufferhandle*)badbufferhandle, 0, (UINT64*)pud);
#endif
    // trying to push to buffer 0
    dg_initerrors(&BHarrayhead, 100, &pError);
    dg_pushhctwotobuffer(&BHarrayhead, 0, (UINT64*)pud);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushhctwotobuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer push to errorstack case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_bufferidisforerrorstack)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer push to errorstack case - got wrong error 1 below top, got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    // dg_success case
    i = dg_newbuffer(&BHarrayhead, 0x10, 0x1f, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_touleb128(0x85, pud);

    dg_pushhctwotobuffer(&BHarrayhead, i, pud);

    c = dg_getbufferbyte(&BHarrayhead, i, 0);

    if (c != 0x85)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer dg_success case - 1st byte of number not pushed onto buffer\n");
    }

    c = dg_getbufferbyte(&BHarrayhead, i, 1);

    if (c != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer dg_success case - 2nd byte of number not pushed onto buffer\n");
    }

    if (pBH->nextunusedbyte != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer dg_success case - buffer not extended\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pushhctwotobuffer dg_success case - got an error, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, i);
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_parsewords()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    unsigned char* pstring;
    UINT64 stringlength;
    UINT64 foundendflag;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_parsewords\n");
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
        if (dg_geterrorcount(&BHarrayhead) != 0)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to set the current input buffer, got:\n ");
            pError = dg_poperror(&BHarrayhead);
            dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }


    // dg_success case
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)"um   did this work?\"more");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'u') ||
        (pstring[1] != 'm') ||
        (foundendflag != FORTH_FALSE) ||
        stringlength != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong first word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to parse second word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'd') ||
        (pstring[1] != 'i') ||
        (pstring[2] != 'd') ||
        (foundendflag != FORTH_FALSE) ||
        stringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong second word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to parse third word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 't') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 's') ||
        (foundendflag != FORTH_FALSE) ||
        stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong third word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to parse fourth word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'w') ||
        (pstring[1] != 'o') ||
        (pstring[2] != 'r') ||
        (pstring[3] != 'k') ||
        (pstring[4] != '?') ||
        (foundendflag != FORTH_TRUE) ||
        stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong fourth word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case - got an error trying to parse off end word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((pstring[0] != 'm') ||
        (pstring[1] != 'o') ||
        (pstring[2] != 'r') ||
        (pstring[3] != 'e') ||
        (foundendflag != FORTH_TRUE) ||
        stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong fifth word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parsewords(
        &BHarrayhead,
        &stringlength,
        '"', // enddelimiter,
        &foundendflag,
        FORTH_FALSE);
        
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong length trying to parse word off end.\n ");
        return;
    }
    
    if (foundendflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsewords dg_success case -  got wrong found end flag trying to parse word off end.\n ");
        return;
    }

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}


void testdg_parseword()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    unsigned char* pstring;
    UINT64 stringlength;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_parseword\n");
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
        if (dg_geterrorcount(&BHarrayhead) != 0)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to set the current input buffer, got:\n ");
            pError = dg_poperror(&BHarrayhead);
            dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }


    // dg_success case
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)"  um did this work?");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseword(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'u') ||
        (pstring[1] != 'm') ||
        stringlength != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case -  got wrong first word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parseword(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to parse second word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'd') ||
        (pstring[1] != 'i') ||
        (pstring[2] != 'd') ||
        stringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case -  got wrong second word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parseword(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to parse third word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 't') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 's') ||
        stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case -  got wrong third word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parseword(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to parse fourth word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'w') ||
        (pstring[1] != 'o') ||
        (pstring[2] != 'r') ||
        (pstring[3] != 'k') ||
        (pstring[4] != '?') ||
        stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case -  got wrong fourth word. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pstring = dg_parseword(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case - got an error trying to parse off end word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseword dg_success case -  got wrong length trying to parse word off end.\n ");
        return;
    }

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_parse()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    unsigned char* pstring;
    UINT64 stringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_parse\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
        if (dg_geterrorcount(&BHarrayhead) != 0)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse success case - got an error trying to set the current input buffer, got:\n ");
            pError = dg_poperror(&BHarrayhead);
            dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \"");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parse(
        &BHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse success case - expected 7 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no end character case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse no end character success case - got an error trying to set the current input buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pickle");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse no end character success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parse(
        &BHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse no end character success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k') ||
        (pstring[5] != 'l') ||
        (pstring[6] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse no end character success case - expected ' pickle' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse no end character success case - expected 6 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminator case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse line terminator success case - got an error trying to set the current input buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse line terminator success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parse(
        &BHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse line terminator success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse line terminator success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parse line terminator success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_parsemultiline()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    unsigned char* pstring;
    UINT64 stringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_parsemultiline\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
        if (dg_geterrorcount(&BHarrayhead) != 0)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - got an error trying to set the current input buffer, got:\n ");
            pError = dg_poperror(&BHarrayhead);
            dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \"");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parsemultiline(
        &BHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline success case - expected 9 got wrong current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no end character case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - got an error trying to set the current input buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pickle");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parsemultiline(
        &BHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k') ||
        (pstring[5] != 'l') ||
        (pstring[6] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - expected ' pickle' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - expected 7 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline no end character success case - expected 7 got wrong current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminator case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - got an error trying to set the current input buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)more");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parsemultiline(
        &BHarrayhead,
        &stringlength,
        ')');
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k') ||
        (pstring[5] != '\n') ||
        (pstring[6] != 'l') ||
        (pstring[7] != 'e') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parsemultiline line terminator success case - expected 9 got wrong current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_tocurrent()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_tocurrent\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); 
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        0x98);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error trying to set the current compile wordlist, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_tocurrent(
        &BHarrayhead,
        0x105);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error doing dg_tocurrent, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting current new word wordlist, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x105)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 0x105 got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting length of new word stack buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected sizeof(UINT64) got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting top of current new word wordlist stack, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 0x98 got wrong top of current new word wordlist stack. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_tocurrent(
        &BHarrayhead,
        0x32);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error doing dg_tocurrent 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting current new word wordlist, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 0x32 got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting length of new word stack buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != (2 * sizeof(UINT64)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 2*sizeof(UINT64) got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting 2nd of current new word wordlist stack 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 0x98 got wrong 2nd of current new word wordlist stack 2nd time. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID,
        sizeof(UINT64));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - got an error getting top of current new word wordlist stack 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x105)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_tocurrent success case - expected 0x105 got wrong top of current new word wordlist stack 2nd time. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
        
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}


void testdg_currentfrom()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_currentfrom\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); 
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        0x98);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error trying to set the current compile wordlist, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_tocurrent(
        &BHarrayhead,
        0x105);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error doing dg_tocurrent, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_currentfrom(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error doing dg_currentfrom, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x105)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected 0x105 got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error getting length of new word stack buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected 0 got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error getting current new word wordlist, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected 0x98 got wrong current new word wordlist. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_currentfrom(&BHarrayhead);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error doing dg_currentfrom 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x98)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected 0x98 got wrong current new word wordlist 2nd time. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error getting length of new word stack buffer 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected 0 got wrong current new word wordlist 2nd time. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - got an error getting current new word wordlist 2nd time, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFWORDLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_currentfrom success case - expected DG_ENDOFWORDLIST got wrong current new word wordlist 2nd time. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
}

void testdg_noparseentirecurrentline()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    unsigned char* pstring;
    UINT64 stringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_noparseentirecurrentline\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline success case - expected 7 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no end character case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pickle");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline no end character success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline no end character success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k') ||
        (pstring[5] != 'l') ||
        (pstring[6] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline no end character success case - expected ' pickle' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline no end character success case - expected 6 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminator case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // line terminator start in middle case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator start in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = pBH->currentoffset + 2;
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator start in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator start in middle success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminator start in middle success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // two line terminators start in middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline two line terminators start in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = pBH->currentoffset + 5;
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline two line terminators start in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline two line terminators start in middle success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline two line terminators start in middle success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // multiple line terminators start in middle of line terminators success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple line terminators start in middle of line terminators success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 8;
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple line terminators start in middle of line terminators success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple line terminators start in middle of line terminators success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple line terminators start in middle of line terminators success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 
    
    
    // line terminators at end success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminators at end success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 9;
    
    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminators at end success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminators at end success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline line terminators at end success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 


    // multiple lines error in middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 12;

    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != 's') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle success case - expected 'shoe' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle b success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle b success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 11;

    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle b success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != 's') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle b success case - expected 'shoe' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle b success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle c success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle c success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 9;

    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle c success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != 's') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle c success case - expected 'shoe' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error in middle c success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error before middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error before middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 8;

    pstring = dg_noparseentirecurrentline(
        &BHarrayhead,
        &stringlength,
        DG_TERMINALINPUT_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error before middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error before middle success case - expected 'shoe' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparseentirecurrentline multiple lines error before middle success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
}


void testdg_parseline()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    unsigned char* pstring;
    UINT64 stringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_parseline\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cr success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \r hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline cr success case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // crlf success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \r\nhoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline crlf success case - expected 10 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // lfcr success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n\rhoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'o') ||
        (pstring[4] != ' ') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - expected 'boo :) ' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - expected 8 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline lfcr success case - expected 10 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no end character case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pickle");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline no end character success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline no end character success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline no end character success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k') ||
        (pstring[5] != 'l') ||
        (pstring[6] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline no end character success case - expected ' pickle' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline no end character success case - expected 7 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - expected 7 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminator case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'p') ||
        (pstring[2] != 'i') ||
        (pstring[3] != 'c') ||
        (pstring[4] != 'k'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - expected ' pick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator success case - expected 6 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // line terminator start in middle case (not supposed to do this...)
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = pBH->currentoffset + 2;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'i') ||
        (pstring[1] != 'c') ||
        (pstring[2] != 'k') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - expected 'ick' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - expected 3 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminator start in middle success case - expected 6 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // two line terminators start in middle success case (not supposed to do this)
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = pBH->currentoffset + 5;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != 'c') ||
        (pstring[1] != 'k') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - expected 'ck' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (stringlength != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - expected 2 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline two line terminators start in middle success case - expected 8 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // multiple line terminators start in middle of line terminators success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple line terminators start in middle of line terminators success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple line terminators start in middle of line terminators success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 8;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple line terminators start in middle of line terminators success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple line terminators start in middle of line terminators success case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple line terminators start in middle of line terminators success case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 
    
    
    // line terminators at end success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 9;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success b case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success b case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success b case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 8;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success b case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success b case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success b case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success c case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success c case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success c case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 7;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success c case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success c case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success b case - expected c got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success d case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\r\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success d case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success d case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    pBH->currentoffset = 7;
    
    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success d case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline line terminators at end success d case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline success d case - expected 9 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 


    // multiple lines error in middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 13;

    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != 't') ||
        (pstring[1] != 'o') ||
        (pstring[2] != 'm') ||
        (pstring[3] != 'a') ||
        (pstring[4] != 't') ||
        (pstring[5] != 'o') )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - expected 'tomato' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - expected 5 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle success case - expected 19 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle b success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parselines multiple lines error in middle b success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle b success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 12;

    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parselines multiple lines error in middle b success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parselines multiple lines error in middle b success case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle b success case - expected 13 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle c success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 8;

    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if ((pstring[0] != 's') ||
        (pstring[1] != 'h') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - expected 'shoe' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - expected 4 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error in middle c success case - expected 13 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error before middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parselines multiple lines error before middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_putbufferuint64 (
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error before middle success case - got an error trying to set current interpret buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID]);
    pBH->currentoffset = 7;

    pstring = dg_parseline(
        &BHarrayhead,
        &stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error before middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (stringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error before middle success case - expected 0 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_TERMINALINPUT_BUFFERID] );
    
    if (pBH->currentoffset != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_parseline multiple lines error before middle success case - expected 8 got wrong end current offset. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
}


void testdg_noparselineatoffset()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    UINT64 linenumber;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_noparselineatoffset\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cr success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \r hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset cr success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset cr success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset cr success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // crlf success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \r\nhoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset crlf success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset crlf success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset crlf success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // lfcr success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n\rhoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset lfcr success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset lfcr success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset lfcr success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no end character case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pickle");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset no end character success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset no end character success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset no end character success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminator case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // line terminator end in middle case 
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end in middle success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // line terminator end at end case 
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end at end success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        5);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end at end success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminator end at end success case - expected 0 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // two line terminators end in middle success case 
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset two line terminators end in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        5);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset two line terminators end in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset two line terminators end in middle success case - expected 1 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
    
    // multiple line terminators end in middle of line terminators success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\nle)");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple line terminators end in middle of line terminators success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        8);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple line terminators end in middle of line terminators success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple line terminators end in middle of line terminators success case - expected 2 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 
    
    
    // line terminators at end success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        9);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success case - expected 2 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success b case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success b case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        8);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success b case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success b case - expected 2 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success c case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\n\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success c case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        7);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success c case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success c case - expected 1 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // line terminators at end success d case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed
        
    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\r\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success d case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        6);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success d case - got an error trying to parse at end, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset line terminators at end success d case - expected 1 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1; 


    // multiple lines error in middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        13);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle success case - expected 3 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle b success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle b success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        12);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle b success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle b success case - expected 2 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error in middle c success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle c success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        8);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle c success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error in middle c success case - expected 2 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }

    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;


    // multiple lines error before middle success case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead); // probably not needed

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" \n pick\nshoe\ntomato");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error before middle success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    linenumber = dg_noparselineatoffset(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        7);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error before middle success case - got an error trying to parse first word, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (linenumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_noparselineatoffset multiple lines error before middle success case - expected 1 got wrong line number. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, linenumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);

    // cleanup
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = (void*)-1;
    
}


void testdg_replacebuffersegment()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    Bufferhandle* pBH;
    
    unsigned char* pstring;
    UINT64* pstringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_replacebuffersegment\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_replacebuffersegment (
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        3, // destoffset,
        2, // destlength,
        (unsigned char*)"xz", // psrc,
        2); //  srclength)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success case - got an error trying to do replace, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_getpbuffer(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        &pstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success case - got an error trying to get pointer to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'x') ||
        (pstring[4] != 'z') ||
        (pstring[5] != ':') ||
        (pstring[6] != ')') ||
        (pstring[7] != ' '))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success case - expected ' boxz:) ...' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (*pstringlength != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success case - expected 13 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success need to grow case
    dg_initbuffers(&BHarrayhead);

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to grow case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_replacebuffersegment (
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        3, // destoffset,
        2, // destlength,
        (unsigned char*)"xzwt", // psrc,
        4); //  srclength)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to grow case - got an error trying to do replace, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_getpbuffer(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        &pstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to grow case - got an error trying to get pointer to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'x') ||
        (pstring[4] != 'z') ||
        (pstring[5] != 'w') ||
        (pstring[6] != 't') ||
        (pstring[7] != ':'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to grow case - expected ' boxzwt:) ...' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (*pstringlength != 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to grow case - expected 15 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success need to shrink case
    dg_initbuffers(&BHarrayhead);

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)" boo :) \n hoo");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to shrink case - got an error trying to push test string to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_replacebuffersegment (
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        3, // destoffset,
        2, // destlength,
        (unsigned char*)"x", // psrc,
        1); //  srclength)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to shrink case - got an error trying to do replace, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pstring = dg_getpbuffer(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        &pstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to shrink case - got an error trying to get pointer to buffer, got:\n ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
        
    if ((pstring[0] != ' ') ||
        (pstring[1] != 'b') ||
        (pstring[2] != 'o') ||
        (pstring[3] != 'x') ||
        (pstring[4] != ':') ||
        (pstring[5] != ')') ||
        (pstring[6] != ' ') ||
        (pstring[7] != '\n'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to shrink case - expected ' box:) ...' got wrong string. Got '");
        dg_writestdoutraw(
            &BHarrayhead,
            pstring,
            *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    if (*pstringlength != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_replacebuffersegment success need to shrink case - expected 15 got wrong string length. Got '");
        dg_writestdoutuinttodec(&BHarrayhead, *pstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    dg_freeallbuffers(&BHarrayhead);
}
