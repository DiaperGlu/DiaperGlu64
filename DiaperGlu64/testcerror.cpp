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
// #include <stdio.h>

void testdg_initerrors()
{
//    UINT64 tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH;
    UINT64 i;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n---\ntesting dg_initerrors\n");

    // buffer reserved for errorstack (0) already allocated case

    i = dg_newbuffer(&BHarrayhead, 100, 200, &pError, FORTH_FALSE);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[i]);

    dg_initerrors(&BHarrayhead, 8, &pError);

    if (pError != dg_initerrorsbuf0inuse)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors - buffer0 already in use case, got wrong error\n");
    }

    if (BHarrayhead.nextfreeindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors - buffer0 already in use case, buffer allocated not freed\n");
    }

    if (BHarrayhead.nextunusedbyte != 2* sizeof(Bufferhandle))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors - there seems to be extra stuff in the buffer handle array\n");
    }

    dg_freebuffer(&BHarrayhead, i);

    //  size < minimum size dg_success case
    BHarrayhead.errorcount = 2398;
    dg_initerrors(&BHarrayhead, 0, &pError);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[0]);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors size < minimum size dg_success case - didn't get dg_success\n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(errorstackminimumsize))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors size < minimum size dg_success case - maxsize not forced to minimum size\n");
    }

    if (pBH->growby != dg_calcnearestpagesize(errorstackminimumsize))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors size < minimum size dg_success case - growby not forced to minumum size\n");
    }
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initerrors size < minimum size dg_success case - errorcoutn not 0\n");
    }

    dg_freebuffer(&BHarrayhead, 0);

    // normal case with freed buffer 0
    BHarrayhead.errorcount =2834;
    dg_initerrors(&BHarrayhead, errorstackminimumsize + 8, &pError);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[0]);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors normal case with freed buffer 0 case - didn't get dg_success\n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize((errorstackminimumsize + 8)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors normal case with freed buffer 0 case - maxsize not forced to minimum size\n");
    }

    if (pBH->growby != dg_calcnearestpagesize((errorstackminimumsize + 8)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors normal case with freed buffer 0 case - growby not forced to minumum size\n");
    } 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL normal case with freed buffer 0 case - errorcoutn not 0\n");
    }

    dg_freebuffer(&BHarrayhead, 0);

    // normal case with no BHarray buffer allocated
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
    BHarrayhead.size = 0;
    BHarrayhead.errorcount =98989;
    BHarrayhead.nextfreeindex = BHarraymaxindex;

    dg_initerrors(&BHarrayhead, dg_calcnearestpagesize(errorstackminimumsize + 10*8), &pError);
    pBH = &(((Bufferhandle*)(BHarrayhead.pbuf))[0]);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors no BHarray buffer allocated case - didn't get dg_success\n");
    }

    if (pBH->maxsize != dg_calcnearestpagesize(errorstackminimumsize + 10*8))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors no BHarray buffer allocated case - maxsize not forced to minimum size\n");
    }

    if (pBH->growby != dg_calcnearestpagesize(errorstackminimumsize + 10*8))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_initerrors no BHarray buffer allocated case - growby not forced to minumum size\n");
    }
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initerrors no BHarray buffer allocated case - errorcoutn not 0\n");
    }

    dg_freebuffer(&BHarrayhead, 0);
}


void testdg_pusherror ()
{
//    UINT64 tbuf = 555;
    const char* pError;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH;
    UINT64 i;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pusherror\n");

    //  buffer 0 is full
#ifndef DGLU_NO_DIAPER
    // pBHarrayhead = NULL case, crash test
    dg_pusherror(NULL, dg_bufferunderflow);


    //  BHarray buffer not allocated case
    BHarrayhead.errorcount = 0;
    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror BHarray buffer not allocated case - errorcount not incrememnted\n");
    }

    //  buffer 0 is not in array (BH nub < 1 * sizeof bufferhandle)
    BHarrayhead.errorcount = 0;
    i = dg_newbuffer(&BHarrayhead, 100, 100, &pError, FORTH_FALSE);
    BHarrayhead.nextunusedbyte = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror buffer 0 is not in array case - errorcount not incrememnted a\n");
    }

    BHarrayhead.nextunusedbyte = sizeof (Bufferhandle) - 1;
    BHarrayhead.errorcount = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror buffer 0 is not in array case - errorcount not incrememnted b\n");
    }

    BHarrayhead.nextunusedbyte = sizeof (Bufferhandle);

    //  buffer 0 is free
    dg_freebuffer(&BHarrayhead, i);
    BHarrayhead.errorcount = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror buffer 0 is free case - errorcount not incrememnted \n");
    }

    //  buffer 0 growby != buffer 0 size != buffer 0 maxsize (something else used buffer 0)
    dg_initerrors(&BHarrayhead, 8 * sizeof(const char), &pError);

    pBH = (Bufferhandle *)BHarrayhead.pbuf;
    pBH->growby--;

    BHarrayhead.errorcount = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror growby != size != maxsize case - errorcount not incrememnted a\n");
    }

    pBH->growby++;
    pBH->size--;
    BHarrayhead.errorcount = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror growby != size != maxsize case - errorcount not incrememnted b\n");
    }

    pBH->size++;
    pBH->maxsize++;
    BHarrayhead.errorcount = 0;

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror growby != size != maxsize case - errorcount not incrememnted c\n");

    }

    pBH->maxsize--;

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror growby != size != maxsize case - nextunusedbyte != 0\n");
    }

    // normal case 1 
    dg_freebuffer(&BHarrayhead, 0);
#endif
    dg_initerrors(&BHarrayhead, 8 * sizeof(const char*), &pError);

    pBH = (Bufferhandle *)BHarrayhead.pbuf; // error stack is locked down

    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 1 - errorcount != 1\n");
    }

    if (pBH->nextunusedbyte != 2 * sizeof (const char*))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 1  - nextunusedbyte not bumped\n");
    }

    if (((UINT64*)(pBH->pbuf))[0] != (UINT64)dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 1  - error not on stack\n");
    }

    if (((UINT64*)(pBH->pbuf))[1] != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 1  - DG_CORE_BUFFERID not on stack\n");
    }

    // normal case 2
    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 2 - errorcount != 2\n");
    }

    if (pBH->nextunusedbyte != 4 * sizeof (const char*))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 2  - nextunusedbyte not bumped\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[2] != (UINT64)dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 2  - error not on stack\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[3] != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 2  - DG_CORE_BUFFERID not on stack\n");
    }

    // normal case 3
    dg_pusherror(&BHarrayhead, dg_bufferunderflow);

    if (BHarrayhead.errorcount != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 3 - errorcount != 3\n");
    }

    if (pBH->nextunusedbyte != 6 * sizeof (const char*))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 3  - nextunusedbyte not bumped\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[4] != (UINT64)dg_bufferunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 3  - error not on stack\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[5] != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 3  - DG_CORE_BUFFERID not on stack\n");
    }

    // normal case 4
    dg_pusherror(&BHarrayhead, dg_buffernubcorrupt);

    if (BHarrayhead.errorcount != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 4 - errorcount != 4\n");
    }

    if (pBH->nextunusedbyte != 8 * sizeof (const char*))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 4  - nextunusedbyte not bumped\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[6] != (UINT64)dg_buffernubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 4  - error not on stack\n");
    }

    if ( ((UINT64*)(pBH->pbuf))[7] != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror normal case 4  - DG_CORE_BUFFERID not on stack\n");
    }

    // errorstack full case
    pBH->nextunusedbyte = pBH->size; 
      // assuming pagesize is a multiple of 8
    dg_pusherror(&BHarrayhead, dg_bufferidnotinbharray);

    if (BHarrayhead.errorcount != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror errorstack full case - errorcount != 5\n");
    }

    if (pBH->nextunusedbyte != pBH->size)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_pusherror errorstack full case  - nextunusedbyte was changed\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_geterror ()
{
//    UINT64 tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;
//    UINT64 i = 0;
    UINT64 tnub = 0;

    UINT64* plength = NULL;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_geterror\n");

    const char** pestack = NULL;
#ifndef DGLU_NO_DIAPER
    // null pBHarrayhead case
    pError = dg_geterror((Bufferhandle*)badbufferhandle, 0);

    if (pError != dg_nullpbharrayheaderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror null pBHarrayhead case - got wrong error\n");
    }
#endif
    // no errors case
    BHarrayhead.errorcount = 0;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError!= dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror no errors case - got an error\n");
    }
#ifndef DGLU_NO_DIAPER
    // no BHarray case
    BHarrayhead.errorcount = 1;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_nullpbharrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror no BHarray case - got wrong error\n");
    }
#endif
    // no error stack case - buffer index off end of array
    BHarrayhead.errorcount = 1;

    dg_initerrors(&BHarrayhead, 1000, &pError);
    BHarrayhead.errorcount = 1;

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror no error stack case - unable to initialize error stack for test\n");
        return;
    }

    tnub = BHarrayhead.nextunusedbyte;
    BHarrayhead.nextunusedbyte = 0;

    

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorbufnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror error stack id off end of array case - got wrong error\n");
    }

    BHarrayhead.nextunusedbyte = tnub;

    // error stack is free case
    dg_freebuffer(&BHarrayhead, 0);
    BHarrayhead.errorcount = 1;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorbufisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror error stack buffer is free case - got wrong error\n");
    }

    // growby != size, why are we checking this?
    dg_initerrors(&BHarrayhead, 1000, &pError);
    BHarrayhead.errorcount = 1;

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror growby != size case - error initializing error stack\n");
    }

    pBH = (Bufferhandle*)(BHarrayhead.pbuf);
    
    pBH->size--;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorbufgrowbynesizenemaxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror growby != size case - got wrong error\n");
    }

    pBH->size++;

    // growby != maxsize case
    pBH->maxsize--;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorbufgrowbynesizenemaxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror growby != maxsize case - got wrong error\n");
    }

    pBH->maxsize++;

    // nub corrupt case
    pBH->nextunusedbyte++;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorbufnubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror nub corrupt case - got wrong error\n");
    }

    pBH->nextunusedbyte--;

    // no errors in buffer yet error count != 0 case
    BHarrayhead.errorcount = 1;

    pBH->nextunusedbyte = 0;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_errorunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror underflow case - got wrong error\n");
    }

    // error not in array case
    pBH->nextunusedbyte = 2*sizeof(const char *); // sizing for 1 error

    pError = dg_geterror(&BHarrayhead, 1); // this is 2nd error

    if (pError != dg_errornotthatmanyerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror not that many errors case - got wrong error\n");
    }

    // dg_success case
    pBH->nextunusedbyte = 4 * sizeof(const char *); // sizing for 2 errors

    BHarrayhead.errorcount = 2;

    pestack = (const char**)(pBH->pbuf);
    pestack[0] = dg_success;
    pestack[1] = (const char*)DG_CORE_BUFFERID;
    pestack[2] = dg_incrementingerrorcount;
    pestack[3] = (const char*)DG_CORE_BUFFERID;

    pError = dg_geterror(&BHarrayhead, 0);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror dg_success case - got wrong error\n");
    }

    pError = dg_geterror(&BHarrayhead, 1);

    if (pError != dg_incrementingerrorcount)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror dg_success case - got wrong error\n");
    }

    // dg_success case 2, error is in another buffer
    // dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

    // dg_pushbuffersegment(&BHarrayhead, 1, 5, (unsigned char*)"abcd\0");
    // dg_pushbuffersegment(&BHarrayhead, 1, 10, (unsigned char*)"myerror\n");

   // pestack[0] = (const char*)5;
   // pestack[1] = (const char*)1;

    // pError = dg_geterror(&BHarrayhead, 0);

    // if (pError != (const char*)(dg_getpbuffer(&BHarrayhead, 1, &plength) + 5))
    // {
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterror dg_success case 2 - got wrong error\n");
    // }

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_poperror ()
{
//    UINT64 tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
//    UINT64 i = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_poperror\n");

    // testing null pBHarrayhead case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  null pBHarrayhead case\n");
#ifndef DGLU_NO_DIAPER
    pError = dg_poperror((Bufferhandle*)badbufferhandle);

    if (pError != dg_nullpbharrayheaderror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror null pBHarrayhead case - got wrong error\n");
    }
#endif
    // error count = 0 case with no BHarray  allocated
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  error count = 0 case with no BHarray  allocated\n");
    
    pError = dg_poperror (&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror error count = 0 case with no BHarray  allocated - got wrong error\n");
    }

    // error count != 0 with no BHarray allocated case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  error count != 0 with no BHarray allocated case\n");
#ifndef DGLU_NO_DIAPER
    BHarrayhead.errorcount = 1;

    pError = dg_poperror (&BHarrayhead);

    if (pError != dg_nullpbharrayerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror error count != 0 with no BHarray allocated case - got wrong error\n");
    }
#endif
    // took this out because dg_checkbharray does not decrement error count
    //if (BHarrayhead.errorcount != 0)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror error count != 0 with no BHarray allocated case - error count not decremented\n");
    //}

    // no buffer 0 case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  no buffer 0 case\n");

    dg_newbuffer(&BHarrayhead, 100, 400, &pError, FORTH_FALSE);

    BHarrayhead.nextunusedbyte = 0; // faking no buffer 0;

    BHarrayhead.errorcount = 1;

    pError = dg_poperror (&BHarrayhead);

    if (pError != dg_errorbufnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror no buf 0 case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror no buf 0 case - error count not decremented\n");
    }

    BHarrayhead.nextunusedbyte = sizeof (Bufferhandle);

    // buf 0 is free case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  buf 0 is free case\n");

    dg_freebuffer(&BHarrayhead, 0);

    BHarrayhead.errorcount = 1;

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorbufisfree)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror buf 0 is free case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror buf 0 is free case - error count not decremented\n");
    }

    // growby != size case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"  growby != size case\n");

    dg_initerrors(&BHarrayhead, 8 * sizeof(const char*), &pError);

    pBH = (Bufferhandle*)BHarrayhead.pbuf;

    pBH->growby--;

    BHarrayhead.errorcount = 1;

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorbufgrowbynesizenemaxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror growby != size case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror growby != size case - error count not decremented\n");
    }
    
    // size != maxsize case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   size != maxsize case\n");

    pBH->growby++;
    pBH->maxsize++;

    BHarrayhead.errorcount = 1;

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorbufgrowbynesizenemaxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror size != maxsize case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror size != maxsize case - error count not decremented\n");
    }

    pBH->maxsize--;

    // nub corrupt case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   nub corrupt case\n");

    pBH->nextunusedbyte++;
    BHarrayhead.errorcount = 1;

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorbufnubcorrupt)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror nub corrupt case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror nub corrupt case - error count not decremented\n");
    }

    pBH->nextunusedbyte--;

    // normal case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   normal case\n");

    dg_freeallbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 32, &pError);

    dg_pusherror(&BHarrayhead, dg_getbuffererrorname);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getbuffererrorname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror normal case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror normalcase - error count not decremented\n");
    }

    // underflow case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   underflow case\n");
    dg_freeallbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 32, &pError);
    pBH = (Bufferhandle*)BHarrayhead.pbuf;

    BHarrayhead.errorcount = 1;

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorunderflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror normal case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror normal case - error count not decremented\n");
    }

    // full stack case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   full stack case\n");

    dg_freeallbuffers(&BHarrayhead);
    dg_initerrors(&BHarrayhead, 4 * 2 * sizeof(const char*), &pError); // some operating systems use page size...
    pBH = (Bufferhandle*)BHarrayhead.pbuf;

    dg_pusherror(&BHarrayhead, dg_getbuffererrorname);
    dg_pusherror(&BHarrayhead, dg_errorbufnotinbharray);
    dg_pusherror(&BHarrayhead, dg_errorbufisfree);
    dg_pusherror(&BHarrayhead, dg_errorbufgrowbynesizenemaxsize);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_errorbufgrowbynesizenemaxsize)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror full stack case - got wrong error\n");
    }

    if (BHarrayhead.errorcount != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror full stack case - error count not decremented\n");
    }

    // overflow case
    // added this because buffer allocation is now pagesize aligned
    //  assuming pagesize is a multiple of 8
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   overflow case\n");

    pBH->nextunusedbyte = pBH->size;

    BHarrayhead.errorcount = pBH->size/(2*sizeof(unsigned char*));

    dg_pusherror(&BHarrayhead, dg_noerrors);

    if (BHarrayhead.errorcount != (pBH->size/(2*sizeof(unsigned char*)) + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror overflow case - second push should make 5\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_erroroverflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror overflow case case - got wrong error, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (BHarrayhead.errorcount != pBH->size/(2*sizeof(unsigned char*)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror overflow case case - error count not decremented\n");
    }

    // testing multiple overflows case
    //dg_printzerostring(&BHarrayhead, (unsigned char*)"   multiple overflows case\n");

    dg_pusherror(&BHarrayhead, dg_noerrors);
    dg_pusherror(&BHarrayhead, dg_noerrors);

    if (BHarrayhead.errorcount != (pBH->size/(2*sizeof(unsigned char*)) + 2))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror multiple overflows case - should be 2 over full after pushes\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_erroroverflow)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror multiple overflows case case - got wrong error, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (BHarrayhead.errorcount != pBH->size/(2*sizeof(unsigned char*)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_poperror multiple overflows case case - error count not dropped to full\n");
    }

    // cleanup
    dg_freebuffer(&BHarrayhead, 0);
    dg_free(BHarrayhead.pbuf, BHarrayhead.size, dg_success);
    BHarrayhead.pbuf = badbufferhandle;
}


void testdg_geterrorcount ()
{
//    UINT64 tbuf = 555;
//    const char* pError = (const char*)badbufferhandle;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

//    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;
    UINT64 i = 0;
//    UINT64 tnub = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_geterrorcount\n");
#ifndef DGLU_NO_DIAPER
    // pBHarrayhead NULL case
    i = dg_geterrorcount((Bufferhandle*)badbufferhandle);

    if (i != (UINT64)baderrorcount)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterrorcount null pBHarrayhead case - got wrong error count \n");
    }
#endif
    // dg_success case
    BHarrayhead.errorcount = 5;

    i = dg_geterrorcount(&BHarrayhead);

    if (i != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_geterrorcount dg_success case - got wrong error count \n");
    }
}


void testdg_checkerrorsonstack ()
{
//    UINT64 tbuf = 555;
    const char* pError = (const char*)badbufferhandle;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;
    UINT64 i = 0;
//    UINT64 tnub = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_checkerrorsonstack\n");
#ifndef DGLU_NO_DIAPER
    // pBHarrayhead NULL case
    i = dg_checkerrorsonstack((Bufferhandle*)badbufferhandle); // this test also sees if it crashes

    if (i != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack NULL pBHarrayhead case - got wrong error count\n");
    }

    // no BHarray case
    BHarrayhead.errorcount = 5;

    i = dg_checkerrorsonstack(&BHarrayhead);

    if (i!= 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack no BHarray case - got wrong error count \n");
    }
#endif
    // no error stack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack no errorstack case - error initializing errorstack \n");
        return;
    }

    dg_freebuffer(&BHarrayhead, 0);
    BHarrayhead.errorcount = 5;

    i = dg_checkerrorsonstack(&BHarrayhead);

    if (i != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack no error stack case - got wrong error count\n");
    }
    
    // dg_success case
    dg_initerrors(&BHarrayhead, 1000, &pError);
    BHarrayhead.errorcount = 5;

    pBH = (Bufferhandle*)BHarrayhead.pbuf;
    pBH->nextunusedbyte = 4 * sizeof (const char*); // 2 errors

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack dg_success case - error initializing error stack\n");
        return;
    }

    i = dg_checkerrorsonstack(&BHarrayhead);

    if (i != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_checkerrorsonstack dg_success case - got wrong error count\n");
    }

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_clearerrors ()
{
//    UINT64 tbuf = 555;
    const char* pError = NULL;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    Bufferhandle* pBH = NULL;
//    UINT64 i = 0;
//    UINT64 tnub = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_clearerrors\n");
#ifndef DGLU_NO_DIAPER
    // BHarrayhead = NULL case crash test
    dg_clearerrors((Bufferhandle*)badbufferhandle);

    // no BHarray case
    BHarrayhead.errorcount = 4;

    dg_clearerrors(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors no BHarray case - error count not cleared\n");
    }
#endif
    // errorstack id off end case
    dg_initerrors(&BHarrayhead, 1000, &pError);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors errorstack id off end case - couldn't initialize error stack\n");
        return;
    }

    BHarrayhead.errorcount = 6;

    BHarrayhead.nextunusedbyte--; 

    pBH = (Bufferhandle*)(BHarrayhead.pbuf);
    pBH->nextunusedbyte = 4;

    dg_clearerrors(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors errorstack id off end case - error count not cleared \n");
    }

    if (pBH->nextunusedbyte != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors errorstack id off end case - error stack's next unused byte changed\n");
    }

    BHarrayhead.nextunusedbyte++;

    // success case
    BHarrayhead.errorcount = 6;
    pBH->nextunusedbyte = 8;

    dg_clearerrors(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors success case - error count not cleared\n");
    }

    if (pBH->nextunusedbyte != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_clearerrors success case - error stack size not set to 0\n");
    }

    // cleanup
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_replaceerrors ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 erroroffset;
    UINT64 errorbufferid;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_replaceerrors\n");
    
    // success case changing middle of 3
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_errorinsubroutine);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_osexception);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_oserror);
        
    dg_replaceerrors(
        &BHarrayhead, 
        DG_CORE_BUFFERID, // olderrorbufferid,
        (UINT64)dg_osexception,
        DG_CORE_BUFFERID,
        (UINT64)dg_badmemoryerror);
        
    dg_getbuffererror (
        &BHarrayhead, 
        0, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error bufferid[0] \n");
    }
    
    if (erroroffset != (UINT64)dg_errorinsubroutine)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error offset[0] \n");
    }
    
    dg_getbuffererror (
        &BHarrayhead, 
        1, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error bufferid[1] \n");
    }
    
    if (erroroffset != (UINT64)dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error offset[1] \n");
    }


    dg_getbuffererror (
        &BHarrayhead, 
        2, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error bufferid[2] \n");
    }
    
    if (erroroffset != (UINT64)dg_oserror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing middle of 3 - got wrong error offset[2] \n");
    }
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case changing last of 3
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_errorinsubroutine);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_osexception);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_oserror);
        
    dg_replaceerrors(
        &BHarrayhead, 
        DG_CORE_BUFFERID, // olderrorbufferid,
        (UINT64)dg_oserror,
        DG_CORE_BUFFERID,
        (UINT64)dg_badmemoryerror);
        
    dg_getbuffererror (
        &BHarrayhead, 
        0, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error bufferid[0] \n");
    }
    
    if (erroroffset != (UINT64)dg_errorinsubroutine)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error offset[0] \n");
    }
    
    dg_getbuffererror (
        &BHarrayhead, 
        1, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error bufferid[1] \n");
    }
    
    if (erroroffset != (UINT64)dg_osexception)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error offset[1], got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)erroroffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_getbuffererror (
        &BHarrayhead, 
        2, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error bufferid[2] \n");
    }
    
    if (erroroffset != (UINT64)dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing last of 3 - got wrong error offset[2] \n");
    }

    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case changing first of 3
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_errorinsubroutine);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_osexception);
        
    dg_pushbuffererror (
        &BHarrayhead,
        DG_CORE_BUFFERID,
        (UINT64)dg_oserror);
        
    dg_replaceerrors(
        &BHarrayhead, 
        DG_CORE_BUFFERID, // olderrorbufferid,
        (UINT64)dg_errorinsubroutine,
        DG_CORE_BUFFERID,
        (UINT64)dg_badmemoryerror);
        
    dg_getbuffererror (
        &BHarrayhead, 
        0, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error bufferid[0] \n");
    }
    
    if (erroroffset != (UINT64)dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error offset[0] \n");
    }
    
    dg_getbuffererror (
        &BHarrayhead, 
        1, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error bufferid[1] \n");
    }
    
    if (erroroffset != (UINT64)dg_osexception)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error offset[1], got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)erroroffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_getbuffererror (
        &BHarrayhead, 
        2, // errorindex, 
        &erroroffset, // UINT32* poffset, 
        &errorbufferid); // UINT32* pbufferid // ,
        
    if (errorbufferid != DG_CORE_BUFFERID)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error bufferid[2] \n");
    }
    
    if (erroroffset != (UINT64)dg_oserror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_replaceerrors success case changing first of 3 - got wrong error offset[2] \n");
    }

    dg_freeallbuffers(&BHarrayhead);
}


