// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.8.
//
//    DiaperGlu v5.8 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.8 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.8; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// March 27, 2023             //
// version 5.8                //
// /////////////////////////////


#include "diapergluforth.h"

const char dg_noerroryet[]                 = " - no error yet";

// const char dg_badmagicerror[]              = " - file or structure's magic number not what was expected error";
const char dg_nullpbharrayheaderror[]      = " - Pointer to buffer handle array head invalid, null or -1 pointer";
const char dg_bharrayheadbadmemerror[]     = " - Buffer handle array head pointer points to memory process is not allowed to access";
const char dg_notbharrayheaderror[]        = " - Pointer does not point to buffer handle array head, id is incorrect";
const char dg_nullpbharrayerror[]          = " - Pointer to buffer handle array invalid, null or -1 pointer";
const char dg_bharraybadmemerror[]         = " - Buffer handle array pointer points to memory process is not allowed to access";

const char dg_BHarraygrowby0error[]        = " - BHarray's grow by is 0. Something is very wrong with script engine.";
const char dg_BHarraymaxsizeltgrowby[]     = " - BHarray's maxsize < growby. Something is very wrong with script engine.";
const char dg_BHarraymaxsizeltbhsize[]     = " - BHarray's maxsize < size of a buffer handle. Did you change the #defines and recompile?";
const char dg_BHarraynubcorrupt[]          = " - BHarray's next unused byte index is corrupt. Something is very wrong.";
const char dg_BHarraynubgtsize[]           = " - BHarray's next unused byte index > BHarray's size. Something is very wrong.";
const char dg_BHarrayfull[]                = " - BHarray is full. Maximum allowed size reached. I can't believe you reached it!";

const char dg_buffernubcorrupt[]           = " - Buffer's next unused byte index corrupt";
const char dg_bufferidnotinbharray[]       = " - Buffer id is too high. There aren't that many buffer handles in the buffer handle array.";
const char dg_bufferidisfree[]             = " - Buffer id is for a free buffer.";
const char dg_bufferidisnotfree[]          = " - Buffer id is for a buffer that is not free.";
const char dg_bufferunderflow[]            = " - Trying to drop more bytes than are in the buffer error";
const char dg_buffergrowbycorrupt[]        = " - Buffer's growby was changed from a multiple of system page size";
const char dg_buffersizecorrupt[]          = " - Buffer's size was changed from a multiple of system page size";
const char dg_buffermaxsizecorrupt[]       = " - Buffer's maximum allowed size was changed from a multiple of system page size";
const char dg_buffermaxsizeltsize[]        = " - Buffer's size is greater than it's maximum allowed size error";
const char dg_bufferoffsetgtlength[]       = " - Buffer's current offset greater than length error";
const char dg_maxsizeltgrowbyerror[]       = " - Buffer's maxsize < growby";
const char dg_bufferidisforerrorstack[]    = " - Buffer id is for error stack which is not allowed.";
const char dg_bufferidisfordglubuffer[]    = " - Buffer id is for a dglu script engine buffer which is not allowed.";

const char dg_buffergrowby0error[]         = " - Buffer's grow by is 0. When a buffer is allocated or increased, units of growby are used.";
const char dg_bufferfullerror[]            = " - growing buffer would exceed maximum allowed size error";

const char dg_nullpointererror[]           = " - null pointer error";
const char dg_offsetpastenderror[]         = " - offset is past end of buffer error";
// const char dg_segmentgoespastenderror[]    = " - offset + length goes past end of buffer error";

const char dg_putbytename[]                = "dg_putbyte";
const char dg_putuint64name[]              = "dg_putuint64";
const char dg_getbytename[]                = "dg_getbyte";
// const char dg_getuint64name[]              = "dg_getuint64";
const char dg_movebytesname[]              = "dg_movebytes";
const char dg_movebytesforwardname[]       = "dg_movebytesforward";
const char dg_movebytesreversename[]       = "dg_movebytesreverse";
// const char dg_comparebytesname[]           = "dg_comparebytes";
// const char dg_scanforbytename[]            = "dg_scanforbyte";
const char dg_scanfornotbytereversename[]  = "dg_scanfornotbytereverse";
const char dg_scanforuint64name[]          = "dg_scanforuint64";
const char dg_searchname[]                 = "dg_search";
const char dg_fillwithbytename[]           = "dg_fillwithbyte";
const char dg_readallbytesname[]           = "dg_readallbytes";
const char dg_getuint16name[]              = "dg_getuint16";
const char dg_getuint32name[]              = "dg_getuint32";
const char dg_putuint16name[]              = "dg_putuint16";
const char dg_putuint32name[]              = "dg_putuint32";
const char dg_hctwostorename[]             = "dg_hctwostore";
const char dg_tentothexname[]              = "dg_tentothex";
const char dg_randomname[]                 = "dg_random";

const char dg_addbytesname[]               = "dg_addbytes";
const char dg_adcbytesname[]               = "dg_adcbytes";
const char dg_sbbbytesname[]               = "dg_sbbbytes";
const char dg_shlbytesname[]               = "dg_shlbytes";
const char dg_rclbytesname[]               = "dg_rclbytes";
const char dg_shrbytesname[]               = "dg_shrbytes";
const char dg_sarbytesname[]               = "dg_sarbytes";
const char dg_rcrbytesname[]               = "dg_rcrbytes";
const char dg_notbytesname[]               = "dg_notbytes";
const char dg_andbytesname[]               = "dg_andbytes";
const char dg_orbytesname[]                = "dg_orbytes";
const char dg_xorbytesname[]               = "dg_xorbytes";
const char dg_nandbytesname[]              = "dg_nandbytes";
const char dg_norbytesname[]               = "dg_norbytes";
const char dg_xnorbytesname[]              = "dg_xnorbytes";
const char dg_reversebytesname[]           = "dg_reversebytes";
const char dg_mulu64tou64sname[]           = "dg_mulu64tou64s";
const char dg_divu64sbyu64name[]           = "dg_divu64sbyu64";


UINT64 dg_getbharrayheadsize()
{
    return(sizeof(Bufferhandle));
}


UINT64 dg_getnearesthighestmultiple (
    UINT64 n,
    UINT64 pagesize)
{
    // hopefully no one will do this, but if they do, gonna use a pagesize of 1 and return n
    if (0 == pagesize)
    {
        return (n);
    }
    
    // if n is 0, calculation would underflow, handling this case here
    if (0 == n)
    {
        return(pagesize);
    }
    
    // if calculation would overflow, round down
    if (n > (UINT64)(0 - pagesize))
    {
        return (pagesize * (UINT64)(n/pagesize));
    }
    
    // normal case, return multiple of pagesize >= n
    return (((UINT64)((n - 1) / pagesize) + 1)* pagesize);
}


UINT64 dg_calcnearestpagesize (UINT64 n)
{
    return (dg_getnearesthighestmultiple (n, dg_getpagesize()));
}



const char* dg_checkbharrayhead (Bufferhandle* pBHarrayhead)
{
    const char* flag = dg_success;
 
 #ifndef DGLU_NO_DIAPER
    
    UINT64 x;
        
    if (pBHarrayhead == (Bufferhandle*)badbufferhandle)
    // 0 may be valid address in Linux
    {
        return (dg_nullpbharrayheaderror);
    }
    
    // seeing if magic id is correct, memory checked in assembler routine
    //  I didn't check id in assembler routine because I don't know what's going
    //  on with the registers on the stack and what's goin on with the local stack 
    //  frame. FreeBSD seems to change the frame differently in different routines
    //  when sigaction is called and local variables aren't where they are 
    //  supposed to be.
    
    flag = dg_getuint64(
        (UINT64*)((unsigned char*)pBHarrayhead + bufferhandleidoffset),
        &x);
    
    if (flag != dg_success)
    {
        return (flag);
    }
    
    if (x != BHarrayheadid)
    {
        return(dg_notbharrayheaderror);
    }
    
#endif
    
    return (flag);

}


const char* dg_checkbharray (Bufferhandle* pBHarrayhead)
{
 #ifndef DGLU_NO_DIAPER
    const char* flag = dg_checkbharrayhead(pBHarrayhead);
    UINT64 x;

    if (flag != dg_success)
    {
        return (flag);
    }

    flag = dg_getuint64(
        (UINT64*)((unsigned char*)pBHarrayhead + bufferhandlepbufoffset),
        &x);
    
    if (x == (UINT64)badbufferhandle)
    {
        return(dg_nullpbharrayerror);
    }
#endif
    return (dg_success);
}


const char* dg_newbuffername = "dg_newbuffer";

UINT64 dg_newbuffer (Bufferhandle* pBHarrayhead,
           UINT64  growby,
           UINT64  maxsize,
           const char** pError,
           UINT64 forceoutofmemory)
{
    Bufferhandle* pBH;
    UINT64 i;
    const char* flag;
    
    UINT64 growby2;
    UINT64 maxsize2;
 #ifndef DGLU_NO_DIAPER
    // see if pError points to valid memory
    flag = dg_putuint64(
        (UINT64*)pError,
        (UINT64)dg_noerroryet);

    if (flag != dg_success)
    {
        return(BHarraymaxindex);
    }

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        *pError = flag;
        return(BHarraymaxindex);
    }
#endif
    // dg_getpagesize does not return errors

    // growby = 0 case
    if (growby == 0)
    {
        *pError = dg_buffergrowby0error;
        return (BHarraymaxindex);
    }

    // maxsize < growby case
    if (maxsize < growby)
    {
        *pError = dg_maxsizeltgrowbyerror;
        return (BHarraymaxindex);
    }

    // force growby to be a multiple of pagesize - Linux requirement
    growby2 = dg_calcnearestpagesize(growby);

    // force maxsize to be a multiple  of pagesize - Linux requirement
    maxsize2 = dg_calcnearestpagesize(maxsize);


    // no memory for buffer handle array yet
    if (pBHarrayhead->pbuf == badbufferhandle) 
    {
        // buffer handle array head's growby = 0 case
        if (pBHarrayhead->growby == 0)
        {
            *pError = dg_BHarraygrowby0error;
            return (BHarraymaxindex);
        }

        // buffer handle array head's maxsize < growby case
        if (pBHarrayhead->maxsize < pBHarrayhead->growby)
        {
            *pError = dg_BHarraymaxsizeltgrowby;
            return (BHarraymaxindex);
        }

        // what if growby or maxsize is too small for one buffer handle?
        if (pBHarrayhead->maxsize < sizeof (Bufferhandle))
        {
            // no room for even one bufferhandle in array
            *pError = dg_BHarraymaxsizeltbhsize;
            return (BHarraymaxindex);
        }

        if (pBHarrayhead->growby < sizeof (Bufferhandle))
        {
            // not gonna give error here, gonna try to fix it
            pBHarrayhead->growby = sizeof (Bufferhandle);
        }

        // force growby to be a multiple of pagesize - Linux requirement
        pBHarrayhead->growby = dg_calcnearestpagesize(pBHarrayhead->growby);

        // force maxsize to be a multiple of pagesize - Linux requirement
        pBHarrayhead->maxsize = dg_calcnearestpagesize(pBHarrayhead->maxsize);


        // initialize new buffer handle array
        if (forceoutofmemory != FORTH_FALSE)
        {
            flag = dg_malloc(&(pBHarrayhead->pbuf), pBHarrayhead->growby, dg_outofmemoryerror);
        }
        else
        {
            flag = dg_malloc(&(pBHarrayhead->pbuf), pBHarrayhead->growby, dg_success);
        }
        
        // not enough memory to make intial bharray case
        if (flag != dg_success)
        {
            *pError = dg_outofmemoryerror;
            // pBHarrayhead->pbuf = badbufferhandle; // dg_malloc does this
            return (BHarraymaxindex);
        }

        pBHarrayhead->nextfreeindex = BHarraymaxindex;   
        pBHarrayhead->nextunusedbyte = 0; 
        pBHarrayhead->size = pBHarrayhead->growby;
        pBHarrayhead->errorcount = 0;
        pBHarrayhead->currentoffset = 0;
    }

    // see if there are any freed indexes, if nextfreeindex points off 
    //  the end, there isn't
    if (pBHarrayhead->nextfreeindex >=
        (pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle)))
    {
        // add a free index at the end

        // Checking to see if nextunusedbyte in BHarray is corrupt
        //  nextunusedbyte should be a multiple of sizeof(Bufferhandle)
        if (pBHarrayhead->nextunusedbyte % sizeof(Bufferhandle) != 0)
        {
            // I could try to fix this here, but that could mask discovery of a serious
            //  error in development. Gonna have it error out.
            *pError = dg_BHarraynubcorrupt;
            return (BHarraymaxindex);
        }

        // Checking to see if nextunusedbyte is off the end of the buffer
        if (pBHarrayhead->nextunusedbyte > pBHarrayhead->size)
        {
            // code screwed up, this should never happen.
            // (it's allowed to be equal to the size, that means the buffer is full)
            *pError = dg_BHarraynubgtsize;
            return (BHarraymaxindex);
        }

        // Is there enough memory in BHarray for another handle?
        if (pBHarrayhead->nextunusedbyte + sizeof(Bufferhandle) > pBHarrayhead->size)
        {
            // NO, need to grow BHarray by growby,
            //  and we can assume growby >= sizeof(Bufferhandle)
            //  and we can assume if we grow by growby it will fit
            //  but we cant assume if we grow by growby we wont exceed the max buffer size
            // but will we exceed maxsize?
            if (pBHarrayhead->size + pBHarrayhead->growby > 
                pBHarrayhead->maxsize)
            {
                // it is possible that if we grew to maxsize the buffer will fit,
                //  but it makes the code more complicated. Gonna keep it simple,
                //  and leave a note suggesting the user makes maxsize a multiple of growby
                //  and makes growby a multiple of the buffer handle size
                *pError = dg_BHarrayfull;
                return (BHarraymaxindex);
            }

            // extending BHarray
            if (forceoutofmemory == FORTH_FALSE)
            {
                flag = dg_realloc(
                    &(pBHarrayhead->pbuf), 
                    pBHarrayhead->size,
                    pBHarrayhead->size + pBHarrayhead->growby, 
                    dg_success);
            }
            else
            {
                flag = dg_realloc(
                    &(pBHarrayhead->pbuf),
                    pBHarrayhead->size,
                    pBHarrayhead->size + pBHarrayhead->growby, 
                    dg_outofmemoryerror);
            }
            
            // not enough memory to extend BHarray?
            if (flag != dg_success)
            {
                *pError = dg_outofmemoryerror;
                return (BHarraymaxindex);
            }
        
            pBHarrayhead->size = pBHarrayhead->size + pBHarrayhead->growby;
        }


        // have memory now, adding freed index at the end

        pBHarrayhead->nextfreeindex = 
            pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle);

        // bumping used memory in buffer
        pBHarrayhead->nextunusedbyte = 
            pBHarrayhead->nextunusedbyte + sizeof(Bufferhandle);
        
        // making next free of the new freed index point to an invalid index
        i = pBHarrayhead->nextfreeindex;
        pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[i] );
        pBH->nextfreeindex = BHarraymaxindex; 

        // initializing rest of new freed index (really only need to do pbuf)
        pBH->growby  = 0;
        pBH->maxsize = 0;
        pBH->nextunusedbyte = 0;
        pBH->pbuf = badbufferhandle;
        pBH->size = 0;
        pBH->currentoffset = 0;
    }

    // we have a freed index
        
    i = pBHarrayhead->nextfreeindex;
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[i] );

    // checking to see if this index has a buffer attached i.e. if it's truly free
    //  if this happens there is something majorly wrong with the code somewhere
    if (pBH->pbuf != badbufferhandle)
    {
        *pError = dg_bufferidisnotfree;
        return (BHarraymaxindex);
    }

    // unlinking freed buffer from free list
    pBHarrayhead->nextfreeindex = pBH->nextfreeindex;

    // initializing the handle
    pBH->nextfreeindex = BHarraymaxindex;
    pBH->nextunusedbyte = 0;
    pBH->maxsize = maxsize2;
    pBH->growby = growby2;
    // pBH->pbuf = (void*)largestunsignedint;
    pBH ->size = 0;
    pBH->currentoffset = 0;

    // allocating memory for new buffer
    if (forceoutofmemory != FORTH_FALSE)
    {
        flag = dg_malloc(
            &pBH->pbuf,
            growby2,
            dg_outofmemoryerror);
    }
    else
    {
        flag = dg_malloc(
            &pBH->pbuf,
            growby2,
            dg_success);
    }
    
    // did we get the memory?
    if (flag != dg_success)
    {
        // put this back into the free list and error out
        pBH->nextfreeindex = pBHarrayhead->nextfreeindex;
        pBHarrayhead->nextfreeindex = i;

        *pError = dg_outofmemoryerror;
        return (BHarraymaxindex);
    }

    pBH->size = growby2;
    
    // woohoo!
    *pError = dg_success;
    return (i);
}


void dg_freebuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;

    const char* flag;

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    // assuming nextunusedbyte is a multiple of sizeof Bufferhandle
    //  this could cause problems
    if (bufferid >= (pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle)))
    {
        return;
    }

    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    // see if buffer is already free
    if (pBH->pbuf == badbufferhandle)
    {
        return;
    }

    flag = dg_free(pBH->pbuf, pBH->size, dg_success);
    pBH->pbuf = badbufferhandle;

    pBH->nextfreeindex = pBHarrayhead->nextfreeindex; 
    pBHarrayhead->nextfreeindex = bufferid;

    // if you re-free a buffer that's already in the free list, does it cause
    //  a corrupted free list? That is, a circular list?
}


UINT64 dg_freeallbuffers (Bufferhandle* pBHarrayhead)
{
    Bufferhandle* pBH;
    UINT64 bufferid;
    UINT64 unfreecount = 0;
    UINT64 numberofhandles;
    const char* flag;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return (unfreecount);
    }

    // if nextunusedbyte is corrupt, not catchin it at this time
    //  possible things to check: nub > size or maxsize. size > max,
    //  nub > sizeof(Bufferhandle)

    numberofhandles = pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle);

    for (bufferid = 0; bufferid < numberofhandles; bufferid++)
    {
        pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
        if (pBH->pbuf != badbufferhandle)
        {
            dg_freebuffer(pBHarrayhead, bufferid);
            unfreecount++;
        }
    }

    dg_free(pBHarrayhead->pbuf, pBHarrayhead->size, dg_success);
    pBHarrayhead->pbuf = badbufferhandle;

    return (unfreecount);
}


const char* dg_checkbuffername = "dg_checkbuffer";

const char* dg_checkbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    const char* pError;
#ifndef DGLU_NO_DIAPER   
    pError = dg_checkbharray(pBHarrayhead);

    if (pError != dg_success)
    {
        return(pError);
    }

    // see if bharray length is corrupt
    if (pBHarrayhead->nextunusedbyte % sizeof(Bufferhandle) != 0)
    {
        return (dg_buffernubcorrupt);
    }

    // see if buffer id is off end of bh array
    if (bufferid >= (pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))  )
    {
        return(dg_bufferidnotinbharray);
    }
#endif
    // see if buffer id is for a free buffer
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (badbufferhandle == pBH->pbuf)
    {
        return (dg_bufferidisfree);
    }

    return (dg_success);
}


const char* dg_growbuffername = "dg_growbuffer";

UINT64 dg_growbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 length,
    const char** pError,
    UINT64 forceoutofmemory)
{
    Bufferhandle* pBH;
    UINT64 oldnextunusedbyte;
    UINT64 newgrowsize;
    const char* flag;
    UINT64 pagesize;
#ifndef DGLU_NO_DIAPER
    flag = dg_putuint64(
        (UINT64*)pError,
        (UINT64)dg_noerroryet);

    if (flag != dg_success)
    {
        return(largestunsignedint);
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        *pError = flag;
        return(largestunsignedint);
    }

    if (pBHarrayhead->nextunusedbyte % sizeof(Bufferhandle) != 0)
    {
        *pError = dg_buffernubcorrupt;
        return (largestunsignedint);
    }

    if (bufferid >= (pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle))  )
    {
        *pError = dg_bufferidnotinbharray;
        return(largestunsignedint);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        *pError = dg_bufferidisfree;
        return (largestunsignedint);
    }

    oldnextunusedbyte = pBH->nextunusedbyte;

    // ok, we now know the buffer is actually there. 
    // Now to see if new size fits without growing

    if ((oldnextunusedbyte + length) <= pBH->size)
    {
        // sweet! it fits!
        *pError = dg_success;
        pBH->nextunusedbyte = oldnextunusedbyte + length;
        return (oldnextunusedbyte);
    }

    // ok it doesnt fit without growing. Gonna see if it will fit at all
    pagesize = dg_getpagesize();

    if ((pBH->size % pagesize) != 0)
    {
        // this shouldn't happen unless something other than the buffer routines
        //   modifies growby
        *pError = dg_buffersizecorrupt;
        return (largestunsignedint);
    }

    if ((pBH->growby % pagesize) != 0)
    {
        // this shouldn't happen unless something other than the buffer routines
        //   modifies growby
        *pError = dg_buffergrowbycorrupt;
        return (largestunsignedint);
    }

    if ((oldnextunusedbyte + length) > pBH->maxsize) // being equal to the maxsize is ok
    {
        *pError = dg_bufferfullerror;
        return(largestunsignedint);
    }

    // we now know it will fit, but it needs to grow. 
    // Was trying: If nub + length is > size + growby, grow to size + length, 
        //   otherwise grow by growby
        // But Linux requires memory allocations to be in units of pagesize so..

    if ((oldnextunusedbyte + length) > (pBH->size + pBH->growby))
    {
        newgrowsize = dg_calcnearestpagesize(oldnextunusedbyte + length - 1);
    }
    else
    {
        newgrowsize = pBH->size + pBH->growby;
    }

    // Try to grow by mingrowsize first. 
    // If that doesnt work, just set buffer to maxsize

    if (newgrowsize <= pBH->maxsize)
    {
        if (forceoutofmemory == FORTH_FALSE)
        {    
            flag = dg_realloc(
                &(pBH->pbuf), 
                pBH->size,
                newgrowsize, 
                dg_success);
        }
        else
        {
            flag = dg_realloc(
                &(pBH->pbuf), 
                pBH->size,
                newgrowsize, 
                dg_outofmemoryerror);
        }
        
        if (flag != dg_success)
        {
            *pError = flag;
            return(largestunsignedint);
        }

        pBH->size = newgrowsize;
        pBH->nextunusedbyte = oldnextunusedbyte + length;
    }
    else
    {
        if ((pBH->growby % pagesize) != 0)
        {
            // this shouldn't happen unless something other than the buffer routines
            //   modifies growby
            *pError = dg_buffermaxsizecorrupt;
            return (largestunsignedint);
        }

        if (forceoutofmemory == FORTH_FALSE)
        {
            flag = dg_realloc(
                &(pBH->pbuf), 
                pBH->size,
                pBH->maxsize, 
                dg_success);
        }
        else
        {
            flag = dg_realloc(
                &(pBH->pbuf), 
                pBH->size,
                pBH->maxsize, 
                dg_outofmemoryerror);
        }
        
        if (flag != dg_success)
        {
            *pError = dg_outofmemoryerror;
            return(largestunsignedint);
        }

        pBH->size = pBH->maxsize;
        pBH->nextunusedbyte = oldnextunusedbyte + length;
    }

    *pError = dg_success;

    return (oldnextunusedbyte);
}


const char* dg_shrinkbuffername = "dg_shrinkbuffer";
    
void dg_shrinkbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 length,
    const char** pError)
{
    Bufferhandle* pBH;
    UINT64 oldnextunusedbyte;
    const char* flag;
#ifndef DGLU_NO_DIAPER
    flag = dg_putuint64(
        (UINT64*)pError,
        (UINT64)dg_noerroryet);

    if (flag != dg_success)
    {
        return;
    }

    if (length == 0)
    {
        *pError = dg_success;
        return;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        *pError = flag;
        return;
    }

    if (pBHarrayhead->nextunusedbyte % sizeof(Bufferhandle) != 0)
    {
        *pError = dg_buffernubcorrupt;
        return;
    }

    if (bufferid >= (pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle))  )
    {
        *pError = dg_bufferidnotinbharray;
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        *pError = dg_bufferidisfree;
        return;
    }

    oldnextunusedbyte = pBH->nextunusedbyte;

    // ok, we now know the buffer is actually there. Now to see if there is enough room
    //  for the shrink

    if (length <= oldnextunusedbyte)
    {
        // sweet! it's not too big!
        *pError = dg_success;
        pBH->nextunusedbyte = oldnextunusedbyte - length;
    }
    else
    {
        // we have underflow, so... gonna set used bytes to 0
        *pError = dg_bufferunderflow;
        pBH->nextunusedbyte = 0;
    }

    return;
}


const char* dg_getpbuffername = "dg_getpbuffer";

unsigned char* dg_getpbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64** pplength)
{
    Bufferhandle* pBH;
    const char* perror;

#ifdef DGLU_NO_DIAPER    
    
        pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
        *pplength = &(pBH->nextunusedbyte);
        return ((unsigned char*)pBH->pbuf);

#else

    perror = dg_checkbharray(pBHarrayhead);

    if (perror != dg_success)
    {
        // if dg_checkbharray fails, there is no error stack, so we are just pushing one error
        // to attempt to increment the error count
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    // just checking to see if pointer can be initialized, buffer errors have priority
    if (pplength == (UINT64**)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_nullpointererror);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    perror = dg_putuint64(
        (UINT64*)pplength,
        (UINT64)badbufferhandle);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        //dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }
    
    // using division instead of multiplication to prevent overflow
    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror (pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror (pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror (pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    if (pBH->size > pBH->maxsize)
    {
        dg_pusherror (pBHarrayhead, dg_buffermaxsizeltsize);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((unsigned char*)badbufferhandle);
    }

    *pplength = &(pBH->nextunusedbyte);

    return ((unsigned char*)pBH->pbuf);
    
#endif

}


const char* dg_clearbuffername = "dg_clearbuffer";

void dg_clearbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    unsigned char* pbuffer;
    UINT64* plength;

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &plength);

    if (pbuffer != (unsigned char*)badbufferhandle)
    {
        *plength = 0;
    }
    else
    {
        dg_pusherror(pBHarrayhead, dg_clearbuffername);
    }
}


const char* dg_getpbuffersegmentname = "dg_getpbuffersegment";

unsigned char* dg_getpbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 length)
{
    unsigned char* pbuffer;
    UINT64* plength;

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_getpbuffersegmentname);
        return((unsigned char*)badbufferhandle);
    }

    if (offset + length > *plength)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_getpbuffersegmentname);
        return ((unsigned char*)badbufferhandle);
    }

    return (pbuffer + offset);    
}


const char* dg_getpbufferoffsetname = "dg_getpbufferoffset";

unsigned char* dg_getpbufferoffset  (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    unsigned char* pbufferoffset;
    
    if (bufferid == DG_CORE_BUFFERID)
    {
        return((unsigned char*)offset);
    }

    // could add these...
    // bharrayheadbufferid
    // bharraybufferid
    
    pbufferoffset = dg_getpbuffersegment(pBHarrayhead, bufferid, offset, 0);
    
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"offset = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, offset);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"bufferid = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, bufferid);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"pBHarrayhead + sizeof(Bufferhandle) = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)pBHarrayhead + sizeof(Bufferhandle));
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    return (pbufferoffset);
}


const char* dg_getbuffersegmentname = "dg_getbuffersegment";

void dg_getbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 length,
    unsigned char* pdest)
{
    unsigned char* psegment;
    const char* perror;

    psegment = dg_getpbuffersegment(
        pBHarrayhead,
        bufferid,
        offset,
        length);

    if ((unsigned char*)badbufferhandle == psegment)
    {
        dg_pusherror(
            pBHarrayhead,
            dg_getbuffersegmentname);
        
        return;
    }

    if ((unsigned char*)badbufferhandle == pdest)
    {
        dg_pusherror(
            pBHarrayhead,
            dg_nullpointererror);
        
        dg_pusherror(
            pBHarrayhead,
            dg_getbuffersegmentname);
        
        return;
    }

    perror = dg_movebytes(
        psegment,
        pdest,
        length);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_getbuffersegmentname);
    }    
}


const char* dg_putbuffersegmentname = "dg_putbuffersegment";

void dg_putbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 length,
    unsigned char* psrc)
{
    unsigned char* psegment;
    const char* perror;


    psegment = dg_getpbuffersegment(
        pBHarrayhead,
        bufferid,
        offset,
        length);

    if ((unsigned char*)badbufferhandle == psegment)
    {
        dg_pusherror(pBHarrayhead, dg_putbuffersegmentname);
        return;
    }

    if ((unsigned char*)badbufferhandle == psrc)
    {
        dg_pusherror(pBHarrayhead, dg_nullpointererror);
        dg_pusherror(pBHarrayhead, dg_putbuffersegmentname);
        return;
    }

    perror = dg_movebytes(
        psrc,
        psegment,
        length);

    if (perror != dg_success)
    {

        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_putbuffersegmentname);
    }
    
}


const char* dg_getbufferuint32name = "dg_getbufferuint32";

UINT32 dg_getbufferuint32 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    Bufferhandle* pBH = NULL;
    UINT32* here;
    const char* flag = NULL;
#ifndef DGLU_NO_DIAPER
    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getbufferuint32name);

        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getbufferuint32name);
        return(0);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getbufferuint32name);
        return(0);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getbufferuint32name);
        return(0);
    }

    //buffer is there, time to get the data

    // check index is off end of buffer case
    if (offset + sizeof(UINT32) > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_getbufferuint32name);
        return (0);
    }

    here = (UINT32*)((UINT8*)(pBH->pbuf) + offset);
    return (here[0]);
}


const char* dg_putbufferuint32name =  "dg_putbufferuint32";

void dg_putbufferuint32 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 data)
{
    Bufferhandle* pBH;
    UINT32* here;
    const char* flag;
#ifndef DGLU_NO_DIAPER
    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_putbufferuint32name);
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_putbufferuint32name);
        return;
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_putbufferuint32name);
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_putbufferuint32name);
        return;
    }

    //buffer is there, time to put the data

    // check to see if it fits
    if (offset + sizeof(UINT32) > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_putbufferuint32name);
        return ;
    }

    here = (UINT32*)((char*)pBH->pbuf + offset);
    *here = (UINT32)(data & 0xFFFFFFFF);

    return;
}


const char* dg_pushbufferuint32name = "dg_pushbufferuint32";

void dg_pushbufferuint32 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 data)
{
    const char* pError;
    UINT64 oldnextunusedbyte;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_pushbufferuint32name);
        return;
    }

    // increasing buffer length
    oldnextunusedbyte = dg_growbuffer(
        pBHarrayhead, 
        bufferid, 
        sizeof (UINT32),
        &pError, 
        false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pushbufferuint32name);
        return;
    }

    dg_putbufferuint32(
        pBHarrayhead,
        bufferid,
        oldnextunusedbyte,
        data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbufferuint32name);
    }

    return;
}


const char* dg_popbufferuint32name = "dg_popbufferuint32";

UINT32 dg_popbufferuint32 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    UINT32* here;
    UINT64 offset;
    UINT32 data;
#ifndef DGLU_NO_DIAPER
    const char* flag;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return(0);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return(0);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return(0);
    }

    //buffer is there, time to get the data

    // nub > size case
    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return (0);
    }

    // not enough in buffer to pop case
    if (pBH->nextunusedbyte <  sizeof (UINT32))
    {
        dg_pusherror(pBHarrayhead, dg_bufferunderflow);
        dg_pusherror(pBHarrayhead, dg_popbufferuint32name);
        return (0);
    }

    offset = pBH->nextunusedbyte - sizeof(UINT32);
    here = (UINT32*)((char*)pBH->pbuf + offset);
    data = *here;
    pBH->nextunusedbyte = pBH->nextunusedbyte - sizeof(UINT32);
    return (data);
}


const char* dg_getbufferuint64name = "dg_getbufferuint64";

UINT64 dg_getbufferuint64 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    Bufferhandle* pBH = NULL;
    UINT64* here;
#ifndef DGLU_NO_DIAPER
    const char* flag = NULL;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getbufferuint64name);

        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getbufferuint64name);
        return(0);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getbufferuint64name);
        return(0);
    }
#endif

    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getbufferuint64name);
        return(0);
    }

    //buffer is there, time to get the data

    // check index is off end of buffer case
    if (offset + sizeof (UINT64) > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_getbufferuint64name);
        return (0);
    }

    here = (UINT64*)((UINT8*)(pBH->pbuf) + offset);
    return (here[0]);
}


const char* dg_putbufferuint64name =  "dg_putbufferuint64";

void dg_putbufferuint64 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 data)
{
    Bufferhandle* pBH;
    UINT64* here;
#ifndef DGLU_NO_DIAPER
    const char* flag;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_putbufferuint64name);
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_putbufferuint64name);
        return;
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_putbufferuint64name);
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_putbufferuint64name);
        return;
    }

    //buffer is there, time to put the data

    // check to see if it fits
    if (offset + sizeof (UINT64) > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_putbufferuint64name);
        return ;
    }

    here = (UINT64*)((char *)pBH->pbuf + offset);
    *here = data;

    return;
}


const char* dg_pushbufferuint64name = "dg_pushbufferuint64";

void dg_pushbufferuint64 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 data)
{
    const char* pError;
    UINT64 oldnextunusedbyte;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_pushbufferuint64name);
        return;
    }

    // increasing buffer length
    oldnextunusedbyte = dg_growbuffer(
        pBHarrayhead, 
        bufferid, 
        sizeof (UINT64),
        &pError, 
        false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pushbufferuint64name);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        bufferid,
        oldnextunusedbyte,
        data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbufferuint64name);
    }

    return;
}


const char* dg_pushbuffersegmentname = "dg_pushbuffersegment";

void dg_pushbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 length,
    unsigned char* psrc)
{
    UINT64 oldbufferlength;
    UINT64 olderrorcount;
    const char* pError;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    if (DG_ERRORSTACK_BUFFERID == bufferid)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_pushbuffersegmentname);
        return;
    }

    oldbufferlength = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        length,
        &pError,
        false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pushbuffersegmentname);
        return;
    }

    dg_putbuffersegment(
        pBHarrayhead,
        bufferid,
        oldbufferlength,
        length,
        psrc);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbuffersegmentname);
        dg_shrinkbuffer(pBHarrayhead, bufferid, length, &pError); // grow was ok so...
    }

    return;
}


const char* dg_pickbuffersegmentname = "dg_pickbuffersegment";

void dg_pickbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    UINT64 length)
{
    UINT64 oldbufferlength;
    UINT64 olderrorcount;
    const char* pError;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    oldbufferlength = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        length,
        &pError,
        false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pickbuffersegmentname);
        return;
    }

    if (offset + length > oldbufferlength)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_pickbuffersegmentname);
        dg_shrinkbuffer(
            pBHarrayhead,
            bufferid,
            length,
            &pError); // grow was ok so..
        return;
    }

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pbufferlength);

    if ((unsigned char*)badbufferhandle == pbuffer)
    {
        dg_pusherror(pBHarrayhead, dg_pickbuffersegmentname);
        dg_shrinkbuffer(
            pBHarrayhead,
            bufferid,
            length,
            &pError); // grow was ok so..
        return;
    }

    // we know memory is ok so not checking error
    dg_movebytes(
        pbuffer + offset,
        pbuffer + oldbufferlength,
        length);

    return;
}


const char* dg_popbuffersegmentname = "dg_popbuffersegment";

void dg_popbuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 length,
    unsigned char* pdest)
{
    UINT64 bufferlength;
    UINT64 olderrorcount;
    const char* pError;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        bufferid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popbuffersegmentname);
        return;
    }

    if (bufferlength < length)
    {
        dg_pusherror(pBHarrayhead, dg_bufferunderflow);
        dg_pusherror(pBHarrayhead, dg_popbuffersegmentname);
        return;
    }

    dg_getbuffersegment(
        pBHarrayhead,
        bufferid,
        bufferlength - length,
        length,
        pdest);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popbuffersegmentname);
        return;
    }

    dg_shrinkbuffer(
        pBHarrayhead,
        bufferid,
        length,
        &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_popbuffersegmentname);
    }
}


const char* dg_getbufferbytename = "dg_getbufferbyte";

unsigned char dg_getbufferbyte (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    unsigned char data = 0;
    UINT64 olderrorcount = 0;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(data);
    }

    dg_getbuffersegment(
        pBHarrayhead,
        bufferid,
        offset,
        sizeof(unsigned char),
        &data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getbufferbytename);
    }

    return(data);
}


const char* dg_putbufferbytename = "dg_putbufferbyte";

void dg_putbufferbyte (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset,
    unsigned char data)
{
    UINT64 olderrorcount;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    dg_putbuffersegment(
        pBHarrayhead,
        bufferid,
        offset,
        sizeof(unsigned char),
        &data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_putbufferbytename);
    }
}


const char* dg_popbufferbytename = "dg_popbufferbyte";

unsigned char dg_popbufferbyte (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    unsigned char data = 0;
    UINT64 olderrorcount;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(data);
    }

    dg_popbuffersegment(
        pBHarrayhead,
        bufferid,
        sizeof(unsigned char),
        &data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popbufferbytename);
    }

    return (data);
}


const char* dg_pushbufferbytename = "dg_pushbufferbyte";

void dg_pushbufferbyte (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    unsigned char data)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        bufferid,
        sizeof(unsigned char),
        &data);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbufferbytename);
    }
}


const char* dg_popbufferuint64name = "dg_popbufferuint64";

UINT64 dg_popbufferuint64 (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    UINT64* here;
    UINT64 offset;
    UINT64 data;

    const char* flag;
#ifndef DGLU_NO_DIAPER
    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return(0);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return(0);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return(0);
    }

    //buffer is there, time to get the data

    // nub > size case
    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return (0);
    }

    // not enough in buffer to pop case
    if (pBH->nextunusedbyte <  sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_bufferunderflow);
        dg_pusherror(pBHarrayhead, dg_popbufferuint64name);
        return (0);
    }

    offset = pBH->nextunusedbyte - sizeof (UINT64);
    here = (UINT64*)((char *)pBH->pbuf + offset);
    data = *here;
    pBH->nextunusedbyte = pBH->nextunusedbyte - sizeof (UINT64);
    return (data);
}


const char* dg_insertinbuffername = "dg_insertinbuffer";

void dg_insertinbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset, // in bytes
    UINT64 length)
{
    Bufferhandle* pBH;
    const char* pError;
    
    UINT64 oldnextunusedbyte;

    if (0 == length)
    {
        return;
    }
#ifndef DGLU_NO_DIAPER
    pError = dg_checkbharray(pBHarrayhead);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID) // buffer 0 is reserved for the error stack
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    // nub corrupt check?

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    if (offset > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_offsetpastenderror);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    if (pBH->nextunusedbyte + length > pBH->maxsize)
    {
        dg_pusherror(pBHarrayhead, dg_bufferfullerror);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    oldnextunusedbyte = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        length,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_insertinbuffername);
        return;
    }

    if (offset == oldnextunusedbyte)  // no bytes to move, just extending buffer
    {
        // not clearing new area because the next routine is just going to fill it anyways
        return;
    }

    // we have the room and the buffer is there, time to blockmove
    // blockmove is smart enough to move in reverse from end
    dg_movebytes(
        (unsigned char*)pBH->pbuf + offset, 
        (unsigned char*)pBH->pbuf + offset + length, 
        oldnextunusedbyte - offset);

    // not checking return because we know memory is ok
    
    // not clearing new area because the next routine is just going fill it anyways
    return;
}


const char* dg_deleteinbuffername = "dg_deleteinbuffer";

void dg_deleteinbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset, // in bytes
    UINT64 length) // in bytes
{
    Bufferhandle* pBH;
    const char* pError;

    if (length == 0)
    {
        return;
    }
#ifndef DGLU_NO_DIAPER
    pError = dg_checkbharray(pBHarrayhead);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID) // buffer 0 is reserved for the error stack
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }

    // nub corrupt check?

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }

    if (offset + length > pBH->nextunusedbyte)
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }

    if (length == 0)
    {
        return;
    }

    dg_movebytes(
        (unsigned char*)pBH->pbuf + offset + length,
        (unsigned char*)pBH->pbuf + offset,
        pBH->nextunusedbyte - (offset + length));

    // not checking return because we know memory is ok

    dg_shrinkbuffer(pBHarrayhead, bufferid, length, &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_deleteinbuffername);
        return;
    }
}


const char* dg_getbufferlengthname = "dg_getbufferlength";

UINT64 dg_getbufferlength (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    const char* perror;
#ifndef DGLU_NO_DIAPER
    perror = dg_checkbharray(pBHarrayhead);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID) // buffer 0 is reserved for the error stack
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }

    // nub corrupt check?

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }

    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }

    if (pBH->size > pBH->maxsize)
    {
        dg_pusherror(pBHarrayhead, dg_buffermaxsizeltsize);
        dg_pusherror(pBHarrayhead, dg_getbufferlengthname);
        return (0);
    }

    return (pBH->nextunusedbyte);
}


const char* dg_getpbufferhandlename = "dg_getpbufferhandle";

Bufferhandle* dg_getpbufferhandle (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    const char* perror;
#ifndef DGLU_NO_DIAPER
    perror = dg_checkbharray(pBHarrayhead);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getpbufferhandlename);
        return ((Bufferhandle*)badbufferhandle);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror (pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getpbufferhandlename);
        return ((Bufferhandle*)badbufferhandle);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    return(pBH);
}


const char* dg_push0stringtobuffersegmentname  = "dg_push0stringtobuffersegment";

void dg_push0stringtobuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    unsigned char* psrc)
{
    UINT64 length = largestsignedint;

    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    if (psrc == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_nullpointererror);
        dg_pusherror(pBHarrayhead, dg_push0stringtobuffersegmentname);
        return;
    }

    // get length of 0 string
    flag = dg_scanforbyte(psrc, &length,0);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_push0stringtobuffersegmentname);
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        bufferid,
        length,
        psrc);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_push0stringtobuffersegmentname);
        return;
    }
}


void dg_pushdatastack (
       Bufferhandle* pBHarrayhead,
       UINT64 data)
//     ( -- data )
{
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        data);
}

const char* dg_pushbracketobtodatastackname = "dg_pushbracketobtodatastack";

void dg_pushbracketobtodatastack (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_getbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbracketobtodatastackname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID,
        x);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbracketobtodatastackname);
        return;
    }
}


const char* dg_pushu128bracketobtodatastackname = "dg_pushu128bracketobtodatastack";

void dg_pushu128bracketobtodatastack (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_getbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset + sizeof(UINT64));
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushu128bracketobtodatastackname);
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID,
        x);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushu128bracketobtodatastackname);
        return;
    }

    x = dg_getbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushu128bracketobtodatastackname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID,
        x);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushu128bracketobtodatastackname);
        return;
    }
}


void dg_pushf64stack (
       Bufferhandle* pBHarrayhead,
       UINT64 n)  // leaving this as UINT64 to avoid all the casting
//     ( -- data )
{
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n);
}


const char* dg_pushbracketobtof64stackname = "dg_pushbracketobtof64stack";

void dg_pushbracketobtof64stack (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_getbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbracketobtof64stackname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID,
        x);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushbracketobtof64stackname);
        return;
    }
}


void dg_pushsearchorderstack (
       Bufferhandle* pBHarrayhead,
       UINT64 wid)
//     ( -searchorderstack- wid )
{
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        wid);
}


UINT64 dg_popdatastack (Bufferhandle* pBHarrayhead)
//                    ( u -- )
{
    return( dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID) );
}

const char* dg_popdatastacktobracketobname = "dg_popdatastacktobracketob";

void dg_popdatastacktobracketob (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_popbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktobracketobname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset,
        x);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktobracketobname);
    }
}

const char* dg_popdatastacktou128bracketobname = "dg_popdatastacktou128bracketob";

void dg_popdatastacktou128bracketob (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_popbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktou128bracketobname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset,
        x);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktou128bracketobname);
    }

    x = dg_popbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktou128bracketobname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset + sizeof(UINT64),
        x);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popdatastacktou128bracketobname);
    }
}

UINT64 dg_popf64stack (Bufferhandle* pBHarrayhead)
//                    ( f -f64- )
{
    return( dg_popbufferuint64(pBHarrayhead, DG_F64STACK_BUFFERID) );
}

const char* dg_popf64stacktobracketobname = "dg_popf64stacktobracketob";

void dg_popf64stacktobracketob (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    x = dg_popbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popf64stacktobracketobname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead, 
        bufferid,
        offset,
        x);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_popf64stacktobracketobname);
    }
}

UINT64 dg_popsearchorderstack (Bufferhandle* pBHarrayhead)
//                    ( wid -so- )
{
    return( dg_popbufferuint64(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID) );
}

const char* dg_freebuffersetname  = "dg_freebufferset";

void dg_freebufferset (
       Bufferhandle* pBHarrayhead,
       UINT64 buffersetheaderbufferid)
{
    UINT64* pbuffersetheaderbufferlength;
    unsigned char* pbuffersetheaderbuffer;
    
    UINT64 i, bufid, n;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    pbuffersetheaderbuffer = dg_getpbuffer (
      pBHarrayhead,
      buffersetheaderbufferid,
      &pbuffersetheaderbufferlength);
      
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freebuffersetname);
        return;
    }
    
    if (((*pbuffersetheaderbufferlength) % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_freebuffersetname);
        return;
    }
    
    n = (*pbuffersetheaderbufferlength) / sizeof(UINT64);
    
    for (i = 0; i < n; i++)
    {
        bufid = ((UINT64*)pbuffersetheaderbuffer)[i];
        
        dg_freebuffer(pBHarrayhead, bufid);
    }
    
    dg_freebuffer(pBHarrayhead, buffersetheaderbufferid);
}


const char* dg_newbuffersetname  = "dg_newbufferset";

UINT64 dg_newbufferset (
    Bufferhandle* pBHarrayhead,
    UINT64 growby,
    UINT64 maxsize,
    UINT64 numberofbuffers)
{
    UINT64 i, buffersetheaderid, buffersetheadersize, buffersetheadertruesize, n;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return ((UINT64)badbufferhandle);
    }

    // check to see if bufferset header array length calculation will overflow
    if (numberofbuffers >= (largestunsignedint / sizeof(UINT64) ))
    {
        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        dg_pusherror(pBHarrayhead, dg_newbuffersetname);
        return ((UINT64)badbufferhandle);
    }
    
    buffersetheadersize = numberofbuffers * sizeof(UINT64);
    
    buffersetheadertruesize = dg_calcnearestpagesize(buffersetheadersize);
    
    // dg_calcnearestpagesize can return a page size less than the amount asked for if amount is within one pagesize of -1
    //  checking for that case here... although....
    //  (assuming os COULD make a buffer this big, pushing buffer ids to the header buffer will overflow 
    //    the header buffer, so it would be caught that way. But wouldn't you rather know right away instead
    //    of having your computer waste a lot of time trying to allocate all that memory?)
    if (buffersetheadertruesize < buffersetheadersize)
    {
        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        //dg_pusherror(pBHarrayhead, dg_calcnearestpagesizename);
        dg_pusherror(pBHarrayhead, dg_newbuffersetname);
        return ((UINT64)badbufferhandle);
    } 
    
    buffersetheaderid = dg_newbuffer(
        pBHarrayhead,
        buffersetheadertruesize,
        buffersetheadertruesize,
        &pError,
        FORTH_FALSE);
                          
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_newbuffersetname);
        return ((UINT64)badbufferhandle);
    }
    
    // filling the bufferset with new buffers
    for (i = 0; i < numberofbuffers; i++)
    {
       n = dg_newbuffer(
             pBHarrayhead,
             growby,
             maxsize,
             &pError,
             FORTH_FALSE);
             
        if (pError != dg_success)
        {
            // free the buffers already allocated in the bufferset
            dg_freebufferset(pBHarrayhead, buffersetheaderid);
            
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
            dg_pusherror(pBHarrayhead, dg_newbuffersetname);
            return ((UINT64)badbufferhandle);
        }
        
        dg_pushbufferuint64(pBHarrayhead, buffersetheaderid, n);
        
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            // free the buffers already allocated in the bufferset
            dg_freebufferset(pBHarrayhead, buffersetheaderid);
            dg_pusherror(pBHarrayhead, dg_newbuffersetname);
            return ((UINT64)badbufferhandle);
        }
    }
    
    return (buffersetheaderid);
}


// dg_indexarrayelement... turn index into offset, making sure calculation doesn't overflow
//   element size can not equal 0
//   max index = largestunsignedint / size
//   make sure index not >= max index
//   offset = index * size
//   ok can I come up with a better name? it's basically a multiply which checks for overflow
//   yes I can use dg_umstar and check if the hi UINT64 is 0... so technically I don't really need a separate routine to index an array element
const char* dg_getuint64arrayelementname = "dg_getuint64arrayelement";

UINT64 dg_getuint64arrayelement (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 index)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (0);
    }
    
    // check for array index to buffer byte offset calculation overflow
    if ((index & 0xE000000000000000) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_getuint64arrayelementname);
        return (0);
    }
    
    x = dg_getbufferuint64(pBHarrayhead, bufferid, index << 3);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getuint64arrayelementname);
    }
    
    return (x);
}

const char* dg_putuint64arrayelementname = "dg_putuint64arrayelement";

void dg_putuint64arrayelement (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 index,
    UINT64 x)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    // check for array index to buffer byte offset calculation overflow
    if ((index & 0xE000000000000000) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_putuint64arrayelementname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, bufferid, index << 3, x);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_putuint64arrayelementname);
    }
}


const char* dg_getuint64stackelementname = "dg_getuint64stackelement";

UINT64 dg_getuint64stackelement (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 index) // 0 = top
{
    Bufferhandle* pBH;
    UINT64* here;
    UINT64 offset;
    UINT64 data;

    const char* flag;
#ifndef DGLU_NO_DIAPER
    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return (0);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return(0);
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return(0);
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return(0);
    }

    //buffer is there, time to get the data

    // nub > size case
    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return (0);
    }
    
    // checking to see if index calculation will overflow
    if ((UINT64)largestunsignedint == index)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return(0);
    }
    
    if (((index + 1) & 0xE000000000000000) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return(0);
    }

    // check to see if the indexed element is on the stack
    if (pBH->nextunusedbyte <  (index + 1) * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_getuint64stackelementname);
        return (0);
    }

    offset = pBH->nextunusedbyte - ((index + 1) * sizeof (UINT64));
    here = (UINT64*)((char *)pBH->pbuf + offset);
    data = *here;
    return (data);
}


const char* dg_putuint64stackelementname = "dg_putuint64stackelement";

void dg_putuint64stackelement (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 index, // 0 = top
    UINT64 data)
{
    Bufferhandle* pBH;
    UINT64* here;
    UINT64 offset;

    const char* flag;
#ifndef DGLU_NO_DIAPER
    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }

    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }
#endif
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    if (pBH->pbuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }

    //buffer is there, time to get the data

    // nub > size case
    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }
    
    // checking to see if index calculation will overflow
    if ((UINT64)largestunsignedint == index)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }
    
    if (((index + 1) & 0xE000000000000000) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }

    // check to see if the indexed element is on the stack
    if (pBH->nextunusedbyte <  (index + 1) * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_putuint64stackelementname);
        return;
    }

    offset = pBH->nextunusedbyte - ((index + 1) * sizeof (UINT64));
    here = (UINT64*)((char *)pBH->pbuf + offset);
    *here = data;
    return;
}


const char* dg_stonewbuffername = "dg_stonewbuffer";

UINT64 dg_stonewbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 growby,
    UINT64 maxsize,
    unsigned char* psrc,
    UINT64 srclength)
{
    UINT64 bufferid;
    const char* pError;
    UINT64 growby2;
    Bufferhandle* pBH;
    
    UINT64 initialgrowby;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (BHarraymaxindex);
    }
    
    growby2 = dg_calcnearestpagesize(growby);
    
    // Using srclength as growby so that the initial buffer size will be large enough
    //  to hold the src string. That way a reallocation to grow the buffer won't
    //  be necessary.
    // March 31, 2017 - this is a bug... because sometimes the srclength is 0...
    //    and growby can't be 0... I should only do this if growby2 < srclength
    
    if (growby2 < srclength)
    {
        initialgrowby = srclength;
    }
    else
    {
        initialgrowby = growby2;
    }
    
    bufferid = dg_newbuffer(
        pBHarrayhead,
        initialgrowby,
        maxsize,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_stonewbuffername);
        return (BHarraymaxindex);
    }
    
    // since there was no error, going to skip checks
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    
    pBH->growby = growby2;
    pBH->nextunusedbyte = srclength;
    
    // assuming buffer is long enough since there was no error
    pError = dg_movebytes(
        psrc,
        (unsigned char*)pBH->pbuf,
        srclength);
    
    if (pError != dg_success)
    {
        dg_freebuffer(
            pBHarrayhead,
            bufferid);
        
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_stonewbuffername);
        return BHarraymaxindex;
    }
    
    return (bufferid);
}


const char* dg_getpbufferhandlefastname = "dg_getpbufferhandlefast";

Bufferhandle* dg_getpbufferhandlefast (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    return(&( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] ));
}


const char* dg_makebuffersizeatleastxname = "dg_makebuffersizeatleastx";

void dg_makebuffersizeatleastx (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 x)
{
    Bufferhandle* pBH;
    const char* pError;
    UINT64 oldnextunusedbyte;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        bufferid);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makebuffersizeatleastxname);
        return;
    }
    
    if (pBH->size < x)
    {
        oldnextunusedbyte = dg_growbuffer (
            pBHarrayhead,
            bufferid,
            x,
            &pError,
            FORTH_FALSE);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_makebuffersizeatleastxname);
            return;
        }
        
        pBH->nextunusedbyte = oldnextunusedbyte;
    }
}

const char* dg_getpnewbuffername = "dg_getpnewbuffer";

unsigned char* dg_getpnewbuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferlength)
{
    UINT64 bufferid;
    
    unsigned char* pnewbuffer = (unsigned char*)badbufferhandle;
    UINT64* pbufferlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(pnewbuffer);
    }
    
    bufferid = dg_newbuffer (
        pBHarrayhead,
        bufferlength,
        bufferlength,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_getpnewbuffername);
        return(pnewbuffer);
    }
    
    dg_growbuffer(
        pBHarrayhead,
        bufferid,
        bufferlength,
        &pError,
        FORTH_FALSE);
    
    // can't really get an error here
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_getpnewbuffername);
        return(pnewbuffer);
    }
    
    pnewbuffer = dg_getpbuffer (
      pBHarrayhead,
      bufferid,
      &pbufferlength);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getpnewbuffername);
        return(pnewbuffer);
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LINKNEWBUFFERIDSTACK_BUFFERID,
        bufferid);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getpnewbuffername);
        return(pnewbuffer);
    }
    
    return(pnewbuffer);
}

const char* dg_initbuffers( Bufferhandle* pBHarrayhead )
{
    const char* pError;

    dg_initerrors(
        pBHarrayhead,
        100 * 2 * sizeof(unsigned char*),
        &pError);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_DATASTACK_BUFFERID 1
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, maxdatastackbufferlength, maxdatastackbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_STRINGOFFSETSTACK_BUFFERID 2
    dg_newbuffer(pBHarrayhead, 200, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_STRINGSTRINGSTACK_BUFFERID 3
    dg_newbuffer(pBHarrayhead, 2000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_DATASPACE_BUFFERID 4
    // growby = maxsize to make buffer not move so old forth programs will work
    dg_newbuffer(pBHarrayhead, 1000000, 1000000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    } 

    // #define DG_RSTACK_BUFFERID 5
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, maxrstackbufferlength, maxrstackbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_SEARCHORDERSTACK_BUFFERID 6
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, maxsearchorderbufferlength, maxsearchorderbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_TERMINALINPUT_BUFFERID 7
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_HOLD_BUFFERID 8
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, dg_maxholdbufferlength,  dg_maxholdbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_WORD_BUFFERID 9
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, maxwordbufferlength, maxwordbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_LEAVESTACK_BUFFERID 10
    // growby = maxsize to make buffer size not change to meet Forth standard requirement
    dg_newbuffer(pBHarrayhead, maxleavebufferlength, maxleavebufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_ARGS_BUFFERID 11
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_CLEANUP_BUFFERID 12
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_LIBHANDLE_BUFFERID 13
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_POST_BUFFERID 14
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_SCRIPTFILENAME_BUFFERID 15
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_LOCALPATH_BUFFERID 16
    dg_newbuffer(pBHarrayhead, 1000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_WORDNAME_BUFFERID 17
    dg_newbuffer(pBHarrayhead, 10000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_EXTENDABLECODESPACE_BUFFERID 18
    dg_newbuffer(pBHarrayhead, 10000, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // #define DG_EXTENDABLEDATASPACE_BUFFERID 19
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_CATCHCODE_BUFFERID 20
    // this buffer must not move from it's initial address
    //  this is why growby = maxsize
    dg_newbuffer(pBHarrayhead, 0x1000,  0x1000, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_HLISTHEADERARRAY_BUFFERID 21
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LOCALS_DATASTACK_BUFFERID 22
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LOCALS_STRINGOFFSETSTACK_BUFFERID 23
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LOCALS_STRINGSTRINGSTACK_BUFFERID 24
    dg_newbuffer(pBHarrayhead, 10000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // VARIABLE$ freeable lstring array buffers 25 26 27
    //  27 is the header buffer
    dg_newfreeablelstringarray(pBHarrayhead);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LOCALS_STACKDEPTH_BUFFERID 28
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID 29
    dg_newbuffer(pBHarrayhead, 1000,  largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    // DG_PAD_BUFFERID 30
    dg_newbuffer(pBHarrayhead, dg_maxpadbufferlength,  dg_maxpadbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_SCRIPTNAME_BUFFERID 31
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_QUERYSTRING_BUFFERID 32
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_SERVERNAME_BUFFERID 33
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }

    //#define DG_SERVERSOFTWARE_BUFFERID 34
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_LINKNEWBUFFERIDSTACK_BUFFERID 35
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_EHSTACK_BUFFERID 36
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_F64STACK_BUFFERID 37
    //  since it's a forth buffer and other forth buffers aren't supposed to move
    //  I made this one not move too
    dg_newbuffer(pBHarrayhead, maxf64stackbufferlength, maxf64stackbufferlength, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID 38
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_CURRENTCOMPILEBUFFERSTACK_BUFFERID 39
    //  since it's a forth buffer and other forth buffers aren't supposed to move
    //  I made this one not move too
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_CURRENTVARIABLEBUFFERSTACK_BUFFERID 40
    //  since it's a forth buffer and other forth buffers aren't supposed to move
    //  I made this one not move too
    dg_newbuffer(pBHarrayhead, 0x400, largestsignedint, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    // DG_ERRORLINE_BUFFERID 41  // fixed size buffer since it's handling errors and the data is small
    dg_newbuffer(pBHarrayhead, 0x400, 0x400, &pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        return (pError);
    }
    
    return (dg_success);
}

// according to the standard, dg_stateexecute needs to be NULL
const char* dg_stateexecute = NULL;      // setting the state variable to this puts script interpreter into execute mode
const char dg_statecompile[] = "compile"; // setting the state variable to this puts script interpreter into compile mode


// //////////////////////////////////////////////////////////////////////
//
// dg_initvariables  
//
// Inputs:
//  Bufferhandle* pBHarrayhead    pointer to a Bufferhandle structure which is 
//                                 used as the bufferhandle for the array where the other 
//                                 bufferhandles are stored.
//                                                            
// Action:
//  Initializes the process variables
//
// Failure cases:
//  none - hopefully the data space buffer already exists and was created large enough to hold these
//  
// //////////////////////////////////////////////////////////////////////

const char* dg_initvariablesname = "dg_initvariables";

void dg_initvariables (Bufferhandle* pBHarrayhead)
{
    const char* pError = NULL;

    dg_growbuffer(pBHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        initialsizeofvariablebuffer,
        &pError,
        false);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }

    // dg_forthleftbracket(pBHarrayhead);
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, statevariable, (UINT64)dg_stateexecute);

    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, exitmainflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, promptsoffflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, quitwasinitializedflag, 0);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_variablestringshlistid, DG_ENDOFLIST);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_hlistheaderbuffer, dg_badbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, promptsoffflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompileerrorbufferid, DG_CORE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompileerroroffset, (UINT64)dg_errorinsubroutine);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, 0); // this is a 0 string
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, showerrorsonexitflag, FORTH_TRUE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, coloncallssafeflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_latestnewword, DG_ENDOFWORDLIST);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_colonhaslocalsflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_colonhaslocalstringsflag, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_patchdestnamedbuf, dg_badbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_patchsrcnamedbuf, dg_badbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_patchsrcnamedlib, badlibraryhandle);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_patchsrcnamedsymbollist, DG_ENDOFLIST);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_patchdestnamedsymbollist, DG_ENDOFLIST);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_x86asmaddresssize, sizeof(UINT64)); // size in bytes
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_precision, dg_initialprecision); // number of significant digits
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
    
    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_errorlinenumber, 0); 
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }

    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_localsregsused, 0); 
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }

    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_paramregsused, 0); 
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }

    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_subroutineregspreserved, 0); 
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }

    dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_regspreserveddepth, 0); 
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_initvariablesname);
        return;
    }
}


const char* dg_pushenvtobufname = "dg_pushenvtobuf";

void dg_pushenvtobuf (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    const char* penvname)
{
    UINT64 envvaluelength;
    const char* perror;
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 oldbuflength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        penvname, 
        (unsigned char*)badbufferhandle,
        0,
        &envvaluelength, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_pushenvtobufname);
        return;
    }


    if ((0 == envvaluelength) ||
        ((UINT64)largestunsignedint == envvaluelength))
    {
        return;
    }

    oldbuflength = dg_growbuffer(
        pBHarrayhead, 
        bufferid, 
        envvaluelength + 1, // +1 for null terminator
        &perror, 
        FORTH_FALSE);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pushenvtobufname);
        return;
    }

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pbuflength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushenvtobufname);
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        penvname,
        pbuf + oldbuflength,
        envvaluelength + 1, // + 1 for null terminator
        &envvaluelength,
        dg_success);

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  buflength = ");
    // dg_writestdoutuinttodec(pBHarrayhead, *pbuflength);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  envvaluelength = ");
    // dg_writestdoutuinttodec(pBHarrayhead, envvaluelength);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  pbuf = ");
    // dg_writestdout(pBHarrayhead, pbuf, envvaluelength);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");


    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_pushenvtobufname);
        // dg_pusherror(pBHarrayhead, (const char*)"wassup?");
        return;
    }

    // dropping null terminator
    (*pbuflength)--;
}


const char* dg_getevalstdinfileidname = "dg_getevalstdinfileid";

UINT64 dg_getevalstdinfileid (Bufferhandle* pBHarrayhead)
{
    const char* perror;
    UINT64 fileid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    perror = dg_gethstdin(pBHarrayhead, &fileid, dg_success);
            
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_gethstdinname);
        dg_pusherror(pBHarrayhead, dg_getevalstdinfileidname);
        return (badfilehandle);
    }

    dg_push0stringtobuffersegment(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        (unsigned char*)"stdin");

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalstdinfileidname);
        return (badfilehandle);
    }

    return (fileid);
}


const char* dg_getevalfilenamefileidname = "dg_getevalfilenamefileid";

UINT64 dg_getevalfilenamefileid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuf,
    UINT64* pbuflength)
{
    UINT64 fileid;
    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    if (0 == *pbuflength)
    {
        return (badfilehandle);
    }

    // this is probably unnecessary
    dg_clearbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalfilenamefileidname);
        return (badfilehandle);
    }

    dg_pushbuffersegment(
        pBHarrayhead, 
        DG_SCRIPTFILENAME_BUFFERID,
        *pbuflength,
        pbuf);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalfilenamefileidname);
        return (badfilehandle);
    }

    // append null terminator
    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalfilenamefileidname);
        return (badfilehandle);
    }

    pbuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pbuflength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalfilenamefileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pbuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getevalfilenamefileidname);
        return (badfilehandle);
    }

    return (fileid);
}


const char* dg_getevalargsfileidname = "dg_getevalargsfileid";

UINT64 dg_getevalargsfileid (Bufferhandle* pBHarrayhead)
{
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 fileid;
    // const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    pbuf = dg_getpbuffer(pBHarrayhead, DG_ARGS_BUFFERID, &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    fileid = dg_getevalfilenamefileid (
        pBHarrayhead,
        pbuf,
        pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    return (fileid);


    /*
    if (0 == *pbuflength)
    {
        return (badfilehandle);
    }

    dg_pushbuffersegment(
        pBHarrayhead, 
        DG_SCRIPTFILENAME_BUFFERID,
        *pbuflength,
        pbuf);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    // append null terminator
    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    pbuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pbuflength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pbuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getevalargsfileidname);
        return (badfilehandle);
    }

    return (fileid);
    */
}

// if there is no script file specified try to run noscript.dglu
UINT64 dg_getnoscriptfileid (Bufferhandle* pBHarrayhead)
{
    UINT64 fileid;
    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)"noscript.dglu",
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_droptoerrorcount(pBHarrayhead, olderrorcount);
        return (badfilehandle);
    }

    return (fileid);
}


const char* dg_getiisquerystringfileidname = "dg_getiisquerystringfileid";

UINT64 dg_getiisquerystringfileid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    unsigned char* pscriptfilenamebuf;
    UINT64* pscriptfilenamebuflength;

    UINT64 i, n;
    UINT64 fileid;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    if (0 == namelength)
    {
        return (badfilehandle);
    }

    dg_clearbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    dg_pushenvtobuf(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, "PATH_TRANSLATED");

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    // strip trailing null terminator
    n = *pscriptfilenamebuflength;

    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &n, 0);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    if (n < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = n;
    }

    // if path translated was not empty and there is no trailing \, add one
    if (*pscriptfilenamebuflength > 0)
    {
        if ((pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '\\') || 
            (pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '/'))
        {
            dg_pushbufferbyte(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, DG_PATH_SLASH_SYMBOL);
        }
    }

    // if first character of file name is / or \ then we want to skip it
    if (('/' == pname[0]) || ('\\' == pname[0]))
    {
        dg_pushbuffersegment(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, namelength - 1, pname + 1);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
            return (badfilehandle);
        }
    }
    else
    {
        dg_pushbuffersegment(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, namelength, pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
            return (badfilehandle);
        }
    }

    // append null terminator
    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    // replace slashes 
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    for (i = 0; i < *pscriptfilenamebuflength; i++)
    {
        // if DG_PATH_SLASH_SYMBOL is already / then we really don't need to do this...
        if (('/' == pscriptfilenamebuf[i]) || ('\\' == pscriptfilenamebuf[i]))
        {
            pscriptfilenamebuf[i] = DG_PATH_SLASH_SYMBOL;
        }
    }

    // get pointer again in case buffer moved
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pscriptfilenamebuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getiisquerystringfileidname);
    }

    return (fileid);
}


const char* dg_getapachequerystrfileidname = "dg_getapachequerystrfileid";

UINT64 dg_getapachequerystrfileid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    unsigned char* pscriptfilenamebuf;
    UINT64* pscriptfilenamebuflength;

    UINT64 i, n;
    UINT64 fileid;
    
    UINT64 continueflag;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    if (0 == namelength)
    {
        return (badfilehandle);
    }

    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
        return (badfilehandle);
    }

    // strip trailing null terminator
    n = *pscriptfilenamebuflength;

    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &n, 0);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
        return (badfilehandle);
    }

    if (n < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = n;
    }

    // drop everything after last slash or backslash    
    continueflag = FORTH_TRUE;
    
    while (continueflag != FORTH_FALSE)
    {
        if ((pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '\\') ||
            (pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '/'))
        {
            continueflag = FORTH_FALSE;
        }
        else
        {
            (*pscriptfilenamebuflength)--;
        }
    }

    /*
    // if path translated was not empty and there is no trailing \, add one
    if (*pscriptfilenamebuflength > 0)
    {
        if ((pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '\\') || 
            (pscriptfilenamebuf[*pscriptfilenamebuflength - 1] != '/'))
        {
            dg_pushbufferbyte(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, DG_PATH_SLASH_SYMBOL);
        }
    }
    */

    // if first character of file name is / or \ then we want to skip it
    if (('/' == pname[0]) || ('\\' == pname[0]))
    {
        dg_pushbuffersegment(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, namelength - 1, pname + 1);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
            return (badfilehandle);
        }
    }
    else
    {
        dg_pushbuffersegment(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, namelength, pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
            return (badfilehandle);
        }
    }

    // append null terminator
    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
        return (badfilehandle);
    }

    // replace slashes 
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
        return (badfilehandle);
    }

    for (i = 0; i < *pscriptfilenamebuflength; i++)
    {
        // if DG_PATH_SLASH_SYMBOL is already / then we really don't need to do this...
        if (('/' == pscriptfilenamebuf[i]) || ('\\' == pscriptfilenamebuf[i]))
        {
            pscriptfilenamebuf[i] = DG_PATH_SLASH_SYMBOL;
        }
    }

    // get pointer again in case buffer moved
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pscriptfilenamebuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getapachequerystrfileidname);
    }

    return (fileid);
}


const char* dg_getquerystringfileidname = "dg_getquerystringfileid";

UINT64 dg_getquerystringfileid(Bufferhandle* pBHarrayhead)
{
    unsigned char* pscriptfilenamebuf;
    UINT64* pscriptfilenamebuflength;
    UINT64 QUERY_STRINGlength;
    const char* perror;
    UINT64 fileid;
    UINT64 PATH_TRANSLATEDlength;
    UINT64 i;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    dg_clearbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    dg_pushenvtobuf(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, "PATH_TRANSLATED");

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    // strip trailing null terminator
    PATH_TRANSLATEDlength = *pscriptfilenamebuflength;

    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &PATH_TRANSLATEDlength, 0);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    if (PATH_TRANSLATEDlength < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = PATH_TRANSLATEDlength;
    }

    // if path translated was not empty and there is no trailing /, add one
    if (*pscriptfilenamebuflength > 0)
    {
        if (pscriptfilenamebuf[PATH_TRANSLATEDlength - 1] != '/')
        {
            dg_pushbufferbyte(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, DG_PATH_SLASH_SYMBOL);
            PATH_TRANSLATEDlength++;
        }
    }

    dg_pushenvtobuf(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, "QUERY_STRING");

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    // strip trailing null terminator - (could start scan at start of QUERY_STRING)
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    QUERY_STRINGlength = *pscriptfilenamebuflength;

    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &QUERY_STRINGlength, 0);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    if (QUERY_STRINGlength < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = QUERY_STRINGlength;
    }

    // strip everything after first & or ; (could start scan at start of QUERY_STRING)
    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &QUERY_STRINGlength, (UINT64)'&');

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    if (QUERY_STRINGlength < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = QUERY_STRINGlength;
    }

    perror = dg_scanforbyte((void*)pscriptfilenamebuf, &QUERY_STRINGlength, (UINT64)';');

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    if (QUERY_STRINGlength < *pscriptfilenamebuflength)
    {
        *pscriptfilenamebuflength = QUERY_STRINGlength;
    }

    // if there is an =, remove it and everything before it in QUERY_STRING part
    QUERY_STRINGlength = *pscriptfilenamebuflength - PATH_TRANSLATEDlength;

    perror = dg_scanforbyte(
        (void*)(pscriptfilenamebuf + PATH_TRANSLATEDlength), 
        &QUERY_STRINGlength, 
        (UINT64)'=');

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    if (QUERY_STRINGlength < (*pscriptfilenamebuflength - PATH_TRANSLATEDlength))
    {
        perror = dg_movebytes(
            pscriptfilenamebuf + PATH_TRANSLATEDlength + QUERY_STRINGlength + 1, 
            pscriptfilenamebuf + PATH_TRANSLATEDlength, 
            (*pscriptfilenamebuflength - PATH_TRANSLATEDlength) - (QUERY_STRINGlength + 1)); 

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_movebytesname);
            dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
            return (badfilehandle);
        }

        *pscriptfilenamebuflength = *pscriptfilenamebuflength - (QUERY_STRINGlength + 1);
    }

    // if there is a leading / remove it
    if ((PATH_TRANSLATEDlength) < *pscriptfilenamebuflength)
    {
       if ('/' == pscriptfilenamebuf[PATH_TRANSLATEDlength])
       {
            perror = dg_movebytes(
                pscriptfilenamebuf + PATH_TRANSLATEDlength + 1, 
                pscriptfilenamebuf + PATH_TRANSLATEDlength, 
                (*pscriptfilenamebuflength - PATH_TRANSLATEDlength) - 1); 

            if (perror != dg_success)
            {
                dg_pusherror(pBHarrayhead, perror);
                dg_pusherror(pBHarrayhead, dg_movebytesname);
                dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
                return (badfilehandle);
            }

            *pscriptfilenamebuflength = *pscriptfilenamebuflength - 1;
        }
    }

    // append null terminator
    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    // replace slashes just in case
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    for (i = 0; i < *pscriptfilenamebuflength; i++)
    {
        // if DG_PATH_SLASH_SYMBOL is already / then we really don't need to do this...
        if ('/' == pscriptfilenamebuf[i])
        {
            pscriptfilenamebuf[i] = DG_PATH_SLASH_SYMBOL;
        }
    }

    // DG_SCRIPTFILENAME_BUFFERID buffer is currently locked down, but just in case someone
      // in future changes this, getting pointer again
    pscriptfilenamebuf = dg_getpbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID, &pscriptfilenamebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pscriptfilenamebuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getquerystringfileidname);
    }

    return (fileid);
}

////////////////////////////////////////////////
// errors with badfilehandle - there was a script file name but it did not load
// no errors with badfilehandle - no script file in cgi mode
// errors with filehandle - shouldn't happen
// no errors with filehandle - woohoo
const char* dg_getevaluatefileidname = "dg_getevaluatefileid";

UINT64 dg_getevaluatefileid(Bufferhandle* pBHarrayhead)
{
    UINT64 fileid;

    unsigned char* pSERVER_NAMEbuf;
    UINT64* pSERVER_NAMEbuflength;

    unsigned char* pargsbuf;
    UINT64* pargsbuflength;

    unsigned char* pSCRIPT_NAMEbuf;
    UINT64* pSCRIPT_NAMEbuflength;

    unsigned char* pQUERY_STRINGbuf;
    UINT64* pQUERY_STRINGbuflength;

    unsigned char* pSERVER_SOFTWAREbuf;
    UINT64* pSERVER_SOFTWAREbuflength;

    UINT64 matchflag;

    UINT64 firstvaluestartoffset;
    UINT64 firstvaluelength;

    UINT64 SERVER_NAMEisemptyflag;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    dg_clearbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }


    // check SERVER_NAME exists
    SERVER_NAMEisemptyflag = FORTH_FALSE;

    pSERVER_NAMEbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SERVERNAME_BUFFERID,
        &pSERVER_NAMEbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pSERVER_NAMEbuflength)
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (0 == pSERVER_NAMEbuf[0])
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    // check SERVER_SOFTWARE exists
    pSERVER_SOFTWAREbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SERVERSOFTWARE_BUFFERID,
        &pSERVER_SOFTWAREbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pSERVER_SOFTWAREbuflength)
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (0 == pSERVER_SOFTWAREbuf[0])
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (FORTH_FALSE != SERVER_NAMEisemptyflag)
    {
        // Not a cgi or isapi script
        fileid = dg_getevalargsfileid(pBHarrayhead);

        // if you return an error here with a bad file handle
        // dg_doinputstuff will think you are in cgi/isapi mode
        //  with no script file so...        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);

            // got error, try to open stdin
            // fileid = dg_getevalstdinfileid(pBHarrayhead);

            // if (pBHarrayhead->errorcount != olderrorcount)
            // {
            //    dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            //    return (dg_stdinbadfilehandle);
            //}

            return (fileid);
        }

        // no error with a file handle means a script file was specified in args
        if (fileid != badfilehandle)
        {
            // is running from args
            return (fileid);
        }

        // no error with a bad file handle means running from stdin
        fileid = dg_getevalstdinfileid(pBHarrayhead);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (dg_stdinbadfilehandle);
        }

        return (fileid);
    }

    // doing CGI or ISAPI mode 

    //  what are environment variables in each mode?
      // PATH_INFO         supposed to have stuff after scriptname/ and bafore ?
      //                     but if you do diaperglu.exe/scriptname.dglu you get
      //                     diaperglu.exe/scriptname.dglu (or diaperglu.exe\scriptname.dglu)
      //                     fortunately Diaperglu does not support using 
      //                     diaperglu.exe/scriptname
      //                     Apache does not seem to support PATH_INFO for CGI
      // PATH_TRANSLATED   supposed to be PATH_INFO converted to full path or something
      //                      but there are issues... if server is standards compliant then
      //                      this is not necessarily the full path to the script file
      //                      Apache does not seem to support PATH_TRANSLATED for CGI
      // SCRIPT_FILENAME   supposed to be full path to script file but older versions
      //                      of IIS do not support this parameter
      // QUERY_STRING      stuff after ? in URL which for Diaperglu is 
      //                      supposed to be a script file name. 
      //                      Using first value as script file name in diaperglu?parameters mode
      //                      changed Juse 23, 2013 for Version 3.1
      // SERVER_NAME       is name of server (localhost for test)
      //                      if SERVER_NAME does not exist then Diaperglu is not in ISAPI or CGI mode
      // SERVER_SOFTWARE   is name of http server. Either none, Apache..., or Micro...

    pSCRIPT_NAMEbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTNAME_BUFFERID,
        &pSCRIPT_NAMEbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    pargsbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_ARGS_BUFFERID,
        &pargsbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    // check to see if stuff after last / or \ in args matches stuff after
      // last / or \ in SCRIPT_NAME
    matchflag = dg_checkformatchafterslash(
        pSCRIPT_NAMEbuf,
        *pSCRIPT_NAMEbuflength,
        pargsbuf,
        *pargsbuflength);

    if (FORTH_FALSE != matchflag)
    {
        // they match! this means a script file was directly specified
          // and that the args buffer holds the file name

        fileid = dg_getevalargsfileid(pBHarrayhead);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (badfilehandle);
        }

        return (fileid);
    }

    // if there is anything at all in QUERY_STRING,
    //   then Diaperglu is gonna assume the first parameter's value is the script file
    //   under IIS, Diaperglu will have to append the file name to PATH_TRANSLATED
    //     (PATH_TRANSLATED is already in the args buffer in this case)

    pQUERY_STRINGbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_QUERYSTRING_BUFFERID,
        &pQUERY_STRINGbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pQUERY_STRINGbuflength)
    {
        // Diaperglu was invoked directly with no arguments
        // so there is no script file specified
        // return badfilehandle with no errors
        return (badfilehandle);
    }

    if (0 == pQUERY_STRINGbuf[0])
    {
        // Diaperglu was invoked directly with no arguments
        // so there is no script file specified
        // return badfilehandle with no errors
        return (badfilehandle);
    }

    // at this point assume the query string's first parameter's value holds
    // the script file name
    // under iis, append the script file name to the args buffer which holds PATH_TRANSLATED
    perror = dg_getsvalue(
        pQUERY_STRINGbuf,
        *pQUERY_STRINGbuflength,
        &firstvaluestartoffset,
        &firstvaluelength);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getsvaluename);
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == firstvaluelength)
    {
        // no script file specified case so return badfilehandle with no errors
        return (badfilehandle);
    }

    // IIS 7.0 SERVER_SOFTWARE starts with M
    // Apache 2.0 SERVER_SOFTWARE starts with A
    if ('M' != pSERVER_SOFTWAREbuf[0])
    {
        // assuming Apache so need to append QUERY_STRING filename to
        //  SCRIPT_FILENAME 
        // fileid = dg_getevalfilenamefileid (
        //     pBHarrayhead,
        //     pQUERY_STRINGbuf + firstvaluestartoffset,
        //     &firstvaluelength);

        fileid = dg_getapachequerystrfileid(
            pBHarrayhead,
            pQUERY_STRINGbuf + firstvaluestartoffset,
            firstvaluelength);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (badfilehandle);
        }

        return (fileid);
    }

    // assuming IIS so need to append QUERY_STRING filename to path_translated
    //  path translated already in args buffer
    fileid = dg_getiisquerystringfileid(
        pBHarrayhead,
        pQUERY_STRINGbuf + firstvaluestartoffset,
        firstvaluelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    return (fileid);
}

/*
////////////////////////////////////////////////
// errors with badfilehandle - there was a script file name but it did not load
// no errors with badfilehandle - no script file in cgi mode
// errors with filehandle - shouldn't happen
// no errors with filehandle - woohoo
const char* dg_getevaluatefileidname = "dg_getevaluatefileid";

UINT64 dg_getevaluatefileid (Bufferhandle* pBHarrayhead)
{
    UINT64 fileid;

    unsigned char* pSERVER_NAMEbuf;
    UINT64* pSERVER_NAMEbuflength;

    unsigned char* pargsbuf;
    UINT64* pargsbuflength;

    unsigned char* pSCRIPT_NAMEbuf;
    UINT64* pSCRIPT_NAMEbuflength;

    unsigned char* pQUERY_STRINGbuf;
    UINT64* pQUERY_STRINGbuflength;

    unsigned char* pSERVER_SOFTWAREbuf;
    UINT64* pSERVER_SOFTWAREbuflength;

    unsigned char* pPATH_INFObuf;
    UINT64* pPATH_INFObuflength;

    unsigned char* pPATH_TRANSLATEDbuf;
    UINT64* pPATH_TRANSLATEDbuflength;

    UINT64 matchflag;

    UINT64 firstvaluestartoffset;
    UINT64 firstvaluelength;

    UINT64 SERVER_NAMEisemptyflag;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    dg_clearbuffer(pBHarrayhead, DG_SCRIPTFILENAME_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }


    // check SERVER_NAME exists
    SERVER_NAMEisemptyflag = FORTH_FALSE;
    
    pSERVER_NAMEbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SERVERNAME_BUFFERID,
        &pSERVER_NAMEbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pSERVER_NAMEbuflength) 
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (0 == pSERVER_NAMEbuf[0])
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    // check SERVER_SOFTWARE exists
    pSERVER_SOFTWAREbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SERVERSOFTWARE_BUFFERID,
        &pSERVER_SOFTWAREbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pSERVER_SOFTWAREbuflength) 
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (0 == pSERVER_SOFTWAREbuf[0])
    {
        SERVER_NAMEisemptyflag = FORTH_TRUE;
    }

    if (FORTH_FALSE != SERVER_NAMEisemptyflag) 
    {
        // Not a cgi or isapi script
        fileid = dg_getevalargsfileid(pBHarrayhead);

        // if you return an error here with a bad file handle
        // dg_doinputstuff will think you are in cgi/isapi mode
        //  with no script file so...        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);

            // got error, try to open stdin
            // fileid = dg_getevalstdinfileid(pBHarrayhead);

            // if (pBHarrayhead->errorcount != olderrorcount)
            // {
            //    dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            //    return (dg_stdinbadfilehandle);
            //}
            
            return (fileid);
        }

        // no error with a file handle means a script file was specified in args
        if (fileid != badfilehandle)
        {
            // is running from args
            return (fileid);
        }
        
        // no error with a bad file handle means running from stdin
        fileid = dg_getevalstdinfileid(pBHarrayhead);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (dg_stdinbadfilehandle);
        }
            
        return (fileid);      
    }

    // doing CGI or ISAPI mode 

    //  what are environment variables in each mode?
      // PATH_INFO         supposed to have stuff after scriptname/ and bafore ?
      //                     but if you do diaperglu.exe/scriptname.dglu you get
      //                     diaperglu.exe/scriptname.dglu (or diaperglu.exe\scriptname.dglu)
      //                     fortunately Diaperglu does not support using 
      //                     diaperglu.exe/scriptname
      //                     Apache does not seem to support PATH_INFO for CGI
      // PATH_TRANSLATED   supposed to be PATH_INFO converted to full path or something
      //                      but there are issues... if server is standards compliant then
      //                      this is not necessarily the full path to the script file
      //                      Apache does not seem to support PATH_TRANSLATED for CGI
      // SCRIPT_FILENAME   supposed to be full path to script file but older versions
      //                      of IIS do not support this parameter
      // QUERY_STRING      stuff after ? in URL which for Diaperglu is 
      //                      supposed to be a script file name. 
      //                      Using first value as script file name in diaperglu?parameters mode
      //                      changed Juse 23, 2013 for Version 3.1
      // SERVER_NAME       is name of server (localhost for test)
      //                      if SERVER_NAME does not exist then Diaperglu is not in ISAPI or CGI mode
      // SERVER_SOFTWARE   is name of http server. Either none, Apache..., or Micro...
    
    pSCRIPT_NAMEbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTNAME_BUFFERID,
        &pSCRIPT_NAMEbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    pargsbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_ARGS_BUFFERID,
        &pargsbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    // check to see if stuff after last / or \ in args matches stuff after
      // last / or \ in SCRIPT_NAME
    matchflag = dg_checkformatchafterslash(
        pSCRIPT_NAMEbuf,
        *pSCRIPT_NAMEbuflength,
        pargsbuf,
        *pargsbuflength);

    if (FORTH_FALSE != matchflag)
    {
        // they match! this means a script file was directly specified
          // and that the args buffer holds the file name

        fileid = dg_getevalargsfileid(pBHarrayhead);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (badfilehandle);
        }

        return (fileid);
    }

    // if there is anythign in PATH_INFO then PATH_TRANSLATED holds the path/filename
    pPATH_INFObuf = dg_getpbuffer(
        pBHarrayhead,
        DG_PATHINFO_BUFFERID,
        &pPATH_INFObuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    
    // if (0 != *pPATH_INFObuflength)
    // {
    //    if (pPATH_INFObuf[0] != 0)
    //    {
    //        pPATH_TRANSLATEDbuf = dg_getpbuffer(
    //            pBHarrayhead,
    //            DG_PATHTRANSLATED_BUFFERID,
    //            &pPATH_TRANSLATEDbuflength);

    //        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
     //       {
     //           // this should not happen :-)
     //           dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
     //           return (badfilehandle);
     //       }

     //       fileid = dg_getevalfilenamefileid(
     //           pBHarrayhead,
     //           pPATH_TRANSLATEDbuf,
     //            pPATH_TRANSLATEDbuflength);

     //       if (pBHarrayhead->errorcount != olderrorcount)
     //       {
     //           dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
     //           return (badfilehandle);
     //       }

     //       return(fileid);
     //   }
     // }
    

    // if there is anything at all in QUERY_STRING,
    //   then Diaperglu is gonna assume the first parameter's value is the script file
    //   under IIS, Diaperglu will have to append the file name to PATH_TRANSLATED
    //     (PATH_TRANSLATED is already in the args buffer in this case)

    pQUERY_STRINGbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_QUERYSTRING_BUFFERID,
        &pQUERY_STRINGbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // this should not happen :-)
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == *pQUERY_STRINGbuflength)
    {
        // Diaperglu was invoked directly with no arguments
        // so there is no script file specified
        // return badfilehandle with no errors
        return (badfilehandle);
    }

    if (0 == pQUERY_STRINGbuf[0])
    {
        // Diaperglu was invoked directly with no arguments
        // so there is no script file specified
        // return badfilehandle with no errors
        return (badfilehandle);
    }

    // at this point assume the query string's first parameter's value holds
    // the script file name
    // under iis, append the script file name to the args buffer which holds PATH_TRANSLATED
    perror = dg_getsvalue(
        pQUERY_STRINGbuf,
        *pQUERY_STRINGbuflength,
        &firstvaluestartoffset,
        &firstvaluelength);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getsvaluename);
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    if (0 == firstvaluelength)
    {
        // no script file specified case so return badfilehandle with no errors
        return (badfilehandle);
    }

    // IIS 7.0 SERVER_SOFTWARE starts with M
    // Apache 2.0 SERVER_SOFTWARE starts with A
    if ('M' != pSERVER_SOFTWAREbuf[0])
    {
        // assuming Apache so need to append QUERY_STRING filename to
        //  SCRIPT_FILENAME 
        // fileid = dg_getevalfilenamefileid (
        //     pBHarrayhead,
        //     pQUERY_STRINGbuf + firstvaluestartoffset,
        //     &firstvaluelength);

        fileid = dg_getapachequerystrfileid (
            pBHarrayhead,
            pQUERY_STRINGbuf + firstvaluestartoffset,
            firstvaluelength);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
            return (badfilehandle);
        }

        return (fileid);
    }

    // assuming IIS so need to append QUERY_STRING filename to path_translated
    //  path translated already in args buffer
    fileid = dg_getiisquerystringfileid (
        pBHarrayhead,
        pQUERY_STRINGbuf + firstvaluestartoffset,
        firstvaluelength);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getevaluatefileidname);
        return (badfilehandle);
    }

    return (fileid);   
}
*/

const char* dg_readstdinavailabletobuffername = "dg_readstdinavailabletobuffer";

void dg_readstdinavailabletobuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    UINT64 hstdin;
    UINT64 filelength;
    const char* pError;
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 numread;
    
    UINT64 olderrorcount = olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    ::dg_clearbuffer(pBHarrayhead, bufferid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
    }

    pError = ::dg_gethstdin(
        pBHarrayhead,
        &hstdin, 
        dg_success);
        
    if (pError == dg_oserror)
    {
        // this means you are running under some versions of IIS and stdin is not being used
        return;
    }

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_gethstdinname);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    pError = ::dg_getfilelength(
        pBHarrayhead,
        hstdin, 
        &filelength, 
        dg_success);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getfilelengthname);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    if (filelength > largestsignedint)
    {
        dg_pusherror(pBHarrayhead, dg_outofmemoryerror);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    ::dg_growbuffer(pBHarrayhead, bufferid, filelength, &pError, FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    pbuf = ::dg_getpbuffer(pBHarrayhead, bufferid, &pbuflength);

    if (olderrorcount != pBHarrayhead->errorcount)
    {
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    pError = ::dg_readfile(
        pBHarrayhead,
        hstdin, 
        pbuf, 
        filelength, 
        10, 
        &numread, 
        dg_success);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readfilename);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }

    if (numread != filelength)
    {
        dg_pusherror(pBHarrayhead, dg_osdidlessthanavailableerror);
        dg_pusherror(pBHarrayhead, dg_readstdinavailabletobuffername);
        return;
    }
}


const char* dg_querygetpostname = "dg_querygetpost";

void dg_querygetpost (
    Bufferhandle* pBHarrayhead, 
    UINT64 firsttimethrough)
{
    UINT64 envvaluelength;
    const char* perror;
    INT64 compareflag;
    unsigned char mybuf[5];
    UINT64 i;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"SERVER_NAME", 
        (unsigned char*)badbufferhandle, 
        0, 
        &envvaluelength, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_querygetpostname);
        return;
    }

    if ((0 == envvaluelength) ||
        ((UINT64)largestunsignedint == envvaluelength))
    {
        // not a cgi script 
        return;
    }

    if (firsttimethrough != FORTH_TRUE)
    {
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"REQUEST_METHOD", 
        (unsigned char*)badbufferhandle, 
        0, 
        &envvaluelength, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_querygetpostname);
        return;
    }

    if (4 != envvaluelength) // length of 'POST' 
    {
        // not length of 'POST'
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"REQUEST_METHOD", 
        mybuf, 
        envvaluelength + 1, // + 1 for null terminator, which is 5
        &envvaluelength, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_querygetpostname);
        return;
    }

    // need to convert to upper
    //  might not need this... but just in case
    for (i=0; i<4; i++)
    {
        if ( (mybuf[i] >= 'a') && (mybuf[i] <= 'z'))
        {
            mybuf[i] = mybuf[i] - ('a' - 'A');
        }
    }

    perror = dg_comparebytes(
        (unsigned char*)(&(mybuf[0])),
        4,
        (unsigned char*)"POST",
        4,
        &compareflag);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_querygetpostname);
        return;
    }

    if (0 != compareflag)
    {
        // it is not POST
        return;
    }

    // it is POST
    dg_readstdinavailabletobuffer(
                pBHarrayhead,
                DG_POST_BUFFERID);
   
    if (olderrorcount != pBHarrayhead->errorcount)
    {
        dg_pusherror(pBHarrayhead, dg_querygetpostname);
    }
}


const char* dg_closeevalfileidname = "dg_closeevalfileid";

void dg_closeevalfileid (
    Bufferhandle* pBHarrayhead, 
    UINT64 fileid)
{
    UINT64 stdinfileid;
    const char* perror;

    perror = dg_gethstdin(pBHarrayhead, &stdinfileid, dg_success);

    if ((perror != dg_success) && (perror != dg_oserror))
    {
        // ignoring dg_oserror getting hstdin
        // some versions IIS does not initialize a stdin if it isn't needed
        //  os returns an invalid file handle, and dg_gethstdin returns dg_oserror
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_gethstdinname);
        dg_pusherror(pBHarrayhead, dg_closeevalfileidname);
        return;
    }

    if (fileid == stdinfileid)
    {
        return;
    }

    perror = dg_closefile(fileid, dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_closefilename);
        dg_pusherror(pBHarrayhead, dg_closeevalfileidname);
    }
}


// this tries to add another line to the terminal input buffer from the input source
const char* dg_getonemorestdinlinename = "dg_getonemorestdinline";

void dg_getonemorestdinline(Bufferhandle* pBHarrayhead)
{
    unsigned char c = ' ';
    UINT64 numread;
    const char* perror;
    UINT64 length;
    UINT64 fileid;
    UINT64 bufferid = DG_TERMINALINPUT_BUFFERID;
    const char* pError;
   
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pError = dg_gethstdin(
        pBHarrayhead,
        &fileid,
        dg_success);

    // get all characters from input until cr, lf, or connection closed
    while(c != 10)
    {
        perror = dg_readfile(
            pBHarrayhead,
            fileid,
            &c,
            1,
            0,
            &numread,
            dg_success); // pforceerror);

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_readfilename);
            dg_pusherror(pBHarrayhead, dg_getonemorestdinlinename);
            return;
        }

        if (numread < 1)
        {
            // connection was closed
            // this is not an error
            //c = 10;
            return;
        }

        // ignoring crs. Windows uses CRLF
        //if (c == 13)
        //{
        //    c = 10;
        //}

        // convert delete to bs
        if (c == 127)
        {
            c = 8;
        }

        if (10 == c) // end of buffer is a delimiter so we don't need to push the end of line character
                     //  but going to do it anyways
        {
            dg_pushbufferbyte(pBHarrayhead, bufferid, c);
            // check for push error

            if (pBHarrayhead->errorcount != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_getonemorestdinlinename);
                return;
            }

            // need to check if there is more stuff in terminal input buffer...
            //  if there is... need to stay in loop...
            //  so... getfilelength(cib)  // don't really like windows implementation of this...
                                          //  since it's throwing away a couple of events...
        }
        else
        {
            if (c != 8)
            {
                // throw away non text characters - would like to support unicode someday
                if ((c >= 0x20)
                    && (c <= 126))
                {
                    dg_pushbufferbyte(pBHarrayhead, bufferid, c);
                    // check for push error

                    if (pBHarrayhead->errorcount != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_getonemorestdinlinename);
                        return;
                    }
                }
            }
            else 
            {
                length = dg_getbufferlength(pBHarrayhead, bufferid);

                if (pBHarrayhead->errorcount != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_getonemorestdinlinename);
                    return;
                }

                // handle backspace
                if (length > 0)
                {
                    dg_popbufferbyte(pBHarrayhead, bufferid);

                    // this should never happen
                    if (pBHarrayhead->errorcount != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_getonemorestdinlinename);
                        return;
                    }
                }
            }
        }
    }

    return;
}


// this blocking waits for one line from the terminal
const char* dg_getanotherlinename = "dg_getanotherline";

UINT64 dg_getanotherline(
    Bufferhandle* pBHarrayhead,
    UINT64 fileid,
    UINT64 bufferid, 
    const char* pforceerror)
{
    unsigned char c = ' ';
    UINT64 numread;
    const char* perror;
    UINT64 length;
   
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_clearbuffer(pBHarrayhead, bufferid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getlinename);
        return (FORTH_TRUE);
    }

    // get all characters from input until cr, lf, or connection closed
    while(c != 10)
    {
        perror = dg_readfile(
            pBHarrayhead,
            fileid,
            &c,
            1,
            0,
            &numread,
            pforceerror);

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_readfilename);
            dg_pusherror(pBHarrayhead, dg_getanotherlinename);
            return (FORTH_TRUE);
        }

        if (numread < 1)
        {
            // connection was closed
            // this is not an error
            //c = 10;
            return (FORTH_TRUE);
        }

        // ignoring crs. Windows uses CRLF
        //if (c == 13)
        //{
        //    c = 10;
        //}

        // convert delete to bs
        if (c == 127)
        {
            c = 8;
        }

        if (10 == c) // end of buffer is a delimiter so we don't need to push the end of line character
                     //  but going to do it anyways
        {
            dg_pushbufferbyte(pBHarrayhead, bufferid, c);
            // check for push error

            if (pBHarrayhead->errorcount != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_getanotherlinename);
                return (FORTH_FALSE);
            }

            // need to check if there is more stuff in terminal input buffer...
            //  if there is... need to stay in loop...
            //  so... getfilelength(cib)  // don't really like windows implementation of this...
                                          //  since it's throwing away a couple of events...
        }
        else
        {
            if (c != 8)
            {
                // throw away non text characters - would like to support unicode someday
                if ((c >= 0x20)
                    && (c <= 126))
                {
                    dg_pushbufferbyte(pBHarrayhead, bufferid, c);
                    // check for push error

                    if (pBHarrayhead->errorcount != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_getanotherlinename);
                        return (FORTH_FALSE);
                    }
                }
            }
            else 
            {
                length = dg_getbufferlength(pBHarrayhead, bufferid);

                if (pBHarrayhead->errorcount != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_getanotherlinename);
                    return (FORTH_FALSE);
                }

                // handle backspace
                if (length > 0)
                {
                    dg_popbufferbyte(pBHarrayhead, bufferid);

                    // this should never happen
                    if (pBHarrayhead->errorcount != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_getanotherlinename);
                        return (FORTH_FALSE);
                    }
                }
            }
        }
    }

    return (FORTH_FALSE);
}


// this clears the current input buffer then 
//  blocking waits for one line from the terminal
const char* dg_getlinename = "dg_getline";

UINT64 dg_getline(
    Bufferhandle* pBHarrayhead,
    UINT64 fileid,
    UINT64 bufferid, 
    const char* pforceerror)
{  
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_clearbuffer(pBHarrayhead, bufferid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getlinename);
        return (FORTH_TRUE);
    }

    return(dg_getanotherline(
        pBHarrayhead,
        fileid,
        bufferid, 
        pforceerror));
}


void dg_compilesegment (
    Bufferhandle* pBHarrayhead, 
    const char* psrc, 
    UINT64 length)
{
    UINT64 currentcompilebufferid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    currentcompilebufferid = dg_getbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_compilesegmentname);
        return;
    }

    dg_pushbuffersegment(pBHarrayhead, currentcompilebufferid, length, (unsigned char*)psrc);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_compilesegmentname);
        return;
    }
}

const char* dg_argstoargsbuffername = "dg_argstoargsbuffer";

void dg_argstoargsbuffer (Bufferhandle* pBHarrayhead, int argc, char* argv[])
{
    INT64 i;
    UINT64 valuelength;
    unsigned char* pargs;
    UINT64* pargslength;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_clearbuffer(pBHarrayhead, DG_ARGS_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
        return;
    }

    
    if (argc < 2)
    {
        // try to get PATH_TRANSLATED
        flag = dg_getenvironmentvariable(
            pBHarrayhead,
            (const char*)"PATH_TRANSLATED",
            (unsigned char*)badbufferhandle,
            0,
            &valuelength,
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            return;
        }

        if ((0 == valuelength) ||
            ((UINT64)largestunsignedint == valuelength))
        {
            return;
        }

        dg_growbuffer(
            pBHarrayhead,
            DG_ARGS_BUFFERID,
            valuelength + 1, // +1 for null terminator
            &flag,
            FORTH_FALSE);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            return;
        }

        pargs = dg_getpbuffer(
            pBHarrayhead,
            DG_ARGS_BUFFERID,
            &pargslength);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            return;
        }

        flag = dg_getenvironmentvariable(
            pBHarrayhead,
            (const char*)"PATH_TRANSLATED",
            pargs,
            (*pargslength) + 1,
            &valuelength,
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
            dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            return;
        }

        // need to drop null terminator, dg_getenvironmentvariable appends a null
        dg_shrinkbuffer(
            pBHarrayhead,
            DG_ARGS_BUFFERID,
            1,
            &flag);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
            dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            return;
        }

        return;
    }

    

    // really just want the first argument
    if (argc < 2)
    {
         return;
    }

    i = 1;
    //for (i = 1; i < argc; i++)
    //{
        // Linux does not handle a space after the end of a filename gracefully
        //if (i != 1)
        //{

            //dg_push0stringtobuffersegment(
            //    pBHarrayhead, 
            //    DG_ARGS_BUFFERID, 
            //    (unsigned char*)" ");

            //if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            //{
            //    dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
            //    return;
            //}
        //}

                dg_push0stringtobuffersegment(
                    pBHarrayhead, 
                    DG_ARGS_BUFFERID, 
                    (unsigned char*)argv[i]);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
                    dg_pusherror(pBHarrayhead, dg_argstoargsbuffername);
                    return;
        }
    //}
}


const char dg_parseoffdelimitername[] = "dg_parseoffdelimiter";

unsigned char* dg_parseoffdelimiter(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char delimiter)
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;

    UINT64 beginoffset = 0;
    UINT64 endoffset = 0;

    UINT64 cibid = 0;
    const char* perror;

    unsigned char c = 0;


    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return((unsigned char*)badbufferhandle);
    }
    
    perror = dg_putuint64(pwordlength, 0);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_parseoffdelimitername);
        return((unsigned char*)badbufferhandle);
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parseoffdelimitername);
        return((unsigned char*)badbufferhandle);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parseoffdelimitername);
        return((unsigned char*)badbufferhandle);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;
    
    beginoffset = *pcibcurrentoffset;
    endoffset = beginoffset;

    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + (*pcibcurrentoffset));

        if (c != delimiter)
        {
            break;
        }

        (*pcibcurrentoffset)++;
        endoffset = *pcibcurrentoffset;
    }
    
    *pwordlength = endoffset - beginoffset;
    
    return (pcib + beginoffset);
}


const char dg_parsename[] = "dg_parse";

unsigned char* dg_parse(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char endchar)
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;

    UINT64 beginoffset = 0;
    UINT64 endoffset = 0;

    UINT64 cibid = 0;
    const char* perror;

    unsigned char c = 0;


    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return((unsigned char*)badbufferhandle);
    }
    
    perror = dg_putuint64(pwordlength, 0);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_parsename);
        return((unsigned char*)badbufferhandle);
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsename);
        return((unsigned char*)badbufferhandle);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsename);
        return((unsigned char*)badbufferhandle);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;
    
    beginoffset = *pcibcurrentoffset;
    endoffset = beginoffset;

    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + (*pcibcurrentoffset));

        if ((c == endchar) || (dg_islineterminator(c)))
        {
            (*pcibcurrentoffset)++; // to get off end delimeter - forth standard for parsing
            break;
        }

        (*pcibcurrentoffset)++;
        endoffset = *pcibcurrentoffset;
    }
    
    *pwordlength = endoffset - beginoffset;
    
    return (pcib + beginoffset);
}


const char dg_parsemultilinename[] = "dg_parsemultiline";

unsigned char* dg_parsemultiline(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char endchar)
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;

    UINT64 beginoffset = 0;
    UINT64 endoffset = 0;

    UINT64 cibid = 0;
  
    const char* perror;

    unsigned char c = 0;

    UINT64 fileid;

    UINT64 oldbufferlength;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return((unsigned char*)badbufferhandle);
    }
    
    perror = dg_putuint64(pwordlength, 0);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_parsemultilinename);
        return((unsigned char*)badbufferhandle);
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsemultilinename);
        return((unsigned char*)badbufferhandle);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsemultilinename);
        return((unsigned char*)badbufferhandle);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;
    
    beginoffset = *pcibcurrentoffset;
    endoffset = beginoffset;

    // begin
    //   if (at end and parsing from terminal_input_bufferid) then 
    //    wait for more from stdin (if stdin is closed you get nothing)
    //    if terminal input buffer can grow, may need to get the pointers again...
    // while (not at end of buffer or did not parse terminator)
    //   parse one character 
    // repeat

    while(true)
    {
        if ((*pcibcurrentoffset >= *pciblength) &&
            (DG_TERMINALINPUT_BUFFERID == cibid))
        {
            // need to print out what endchar you are waiting for
            dg_printzerostring(pBHarrayhead, (unsigned char*)"\nParsing characters over multiple lines until ");
            c = endchar;

            perror = dg_gethstdout(
                pBHarrayhead,
                &fileid,
                dg_success);

            if (perror != dg_success)
            {
                dg_pusherror(pBHarrayhead, perror);
                dg_pusherror(pBHarrayhead, dg_gethstdinname);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            perror = dg_writefile(
                pBHarrayhead,
                fileid,
                (unsigned char*)&c,
                1, // length,
                dg_success);

            if (perror != dg_success)
            {
                dg_pusherror(pBHarrayhead, perror);
                dg_pusherror(pBHarrayhead, dg_writefilename);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }
            
            dg_forthdoprompt(pBHarrayhead);

            // pushes another line onto end of cib
            dg_getonemorestdinline(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            // it will probably never happen, but just in case the buffer moved
            //  need to get the pointer to the buffer again
            pcib = dg_getpbuffer(
                pBHarrayhead,
                cibid,
                &pciblength);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            // because dg_getpbuffer worked, I know the buf header for pcib is there
            // pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] ); // shouldn't change....
            pcibcurrentoffset = &pBH->currentoffset;

        }

        if (*pcibcurrentoffset >= *pciblength)
        {
            break;
        }

        c = *(pcib + (*pcibcurrentoffset));

        if (endchar == c)
        {
            (*pcibcurrentoffset)++; // to get off end delimeter - forth standard for parsing
            break;
        }

        (*pcibcurrentoffset)++;
        endoffset = *pcibcurrentoffset;
                 
    }

    //    while(*pcibcurrentoffset < *pciblength)
    //    {
    //        c = *(pcib + (*pcibcurrentoffset));

    //        if (c == endchar)
    //        {
    //            (*pcibcurrentoffset)++; // to get off end delimeter - forth standard for parsing
    //            break;
    //        }

    //        (*pcibcurrentoffset)++;
    //        endoffset = *pcibcurrentoffset;
    //    }

  
    *pwordlength = endoffset - beginoffset;
    
    return (pcib + beginoffset);
}


const char dg_parsewordname[] = "dg_parseword";

unsigned char* dg_parseword(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength)
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;
    UINT64 ciboldoffset = 0;

    UINT64 cibid = 0;

    unsigned char c = 0;

    UINT64 namelength = 0;

    Bufferhandle* pBH = NULL;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)dg_badbufferid);
    }
    
    pError = dg_putuint64(pwordlength, 0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_parsewordname);
        return((unsigned char*)dg_badbufferid);
    }
    
    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsewordname);
        return((unsigned char*)dg_badbufferid);;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsewordname);
        return((unsigned char*)dg_badbufferid);;
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;

    //getting off the delimiters
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if (dg_isdelimiter(c) == FORTH_FALSE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

    ciboldoffset = *pcibcurrentoffset;

    //getting to the next delimiter after the word
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if (dg_isdelimiter(c) == FORTH_TRUE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

    namelength = *pcibcurrentoffset - ciboldoffset;
    
    if (*pcibcurrentoffset < *pciblength) // to skip trailing deliminter... forth standard requirement
    {
        (*pcibcurrentoffset)++;
    }  

    /* checked in calling routine so I'm taking this out 4/14/2020 J.N. */
    /*
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_parsewordname);
        return((unsigned char*)dg_badbufferid);
    }
    */
    
    *pwordlength = namelength;
    
    return (pcib + ciboldoffset);
}


const char dg_parsewordsname[] = "dg_parsewords";

unsigned char* dg_parsewords(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char enddelimiter,
    UINT64* pfoundendflag,
    UINT64 lineterminatorsareendflag) // single line only if true
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;
    UINT64 ciboldoffset = 0;

    UINT64 cibid = 0;

    unsigned char c = 0;

    UINT64 namelength = 0;

    Bufferhandle* pBH = NULL;
    
    const char* pError;
    UINT64 fileid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)dg_badbufferid);
    }
    
    pError = dg_putuint64(pwordlength, 0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_parsewordsname);
        return((unsigned char*)dg_badbufferid);
    }
    
    pError = dg_putuint64(pfoundendflag, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_parsewordsname);
        return((unsigned char*)dg_badbufferid);
    }
    
    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsewordsname);
        return((unsigned char*)dg_badbufferid);;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parsewordsname);
        return((unsigned char*)dg_badbufferid);;
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;

    // begin
    //   if (at end and parsing from terminal_input_bufferid and multiline) then 
    //    wait for more from stdin (if stdin is closed you get nothing)
    //    if terminal input buffer can grow, may need to get the pointers again...
    // while (not at end of buffer or did not parse terminator or will parse non delimiter)
    //   parse one character 
    // repeat

    while (true)
    {
        if ((*pcibcurrentoffset >= *pciblength) &&
            (DG_TERMINALINPUT_BUFFERID == cibid) &&
            (FORTH_FALSE == lineterminatorsareendflag))
        {
            // hopefully don't need anything that is already in the buffer...
            //  this reduces the chances of the need for a grow...    
            *pciblength = 0;
            *pcibcurrentoffset = 0;

            // need to print out what endchar you are waiting for
            dg_printzerostring(pBHarrayhead, (unsigned char*)"\nParsing word names over multiple lines until ");
            c = enddelimiter;

            pError = dg_gethstdout(
                pBHarrayhead,
                &fileid,
                dg_success);

            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_gethstdinname);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            pError = dg_writefile(
                pBHarrayhead,
                fileid,
                (unsigned char*)&c,
                1, // length,
                dg_success);

            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_writefilename);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }
            
            dg_forthdoprompt(pBHarrayhead);

            // pushes another line onto end of cib
            dg_getonemorestdinline(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            // it will probably never happen, but just in case the buffer moved
            //  need to get the pointer to the buffer again
            pcib = dg_getpbuffer(
                pBHarrayhead,
                cibid,
                &pciblength);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
                dg_pusherror(pBHarrayhead, dg_parsemultilinename);
                return((unsigned char*)badbufferhandle);
            }

            // because dg_getpbuffer worked, I know the buf header for pcib is there
            // pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] ); // shouldn't change....
            pcibcurrentoffset = &pBH->currentoffset;
        }

        if (*pcibcurrentoffset >= *pciblength)
        {
            break;
        }

        c = *(pcib + *pcibcurrentoffset);
        
        if  ( (enddelimiter == c) || 
              ( dg_islineterminator(c) && (lineterminatorsareendflag != FORTH_FALSE) ) )
        {
            *pfoundendflag = FORTH_TRUE;
            (*pcibcurrentoffset)++; // moving past end delimiter
            return (pcib + *pcibcurrentoffset - 1);
        }
        
        if (dg_isdelimiter(c) == FORTH_FALSE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

/*
    //getting off the delimiters
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if  ( (enddelimiter == c) || 
              ( dg_islineterminator(c) && (lineterminatorsareendflag != FORTH_FALSE) ) )
        {
            *pfoundendflag = FORTH_TRUE;
            (*pcibcurrentoffset)++; // moving past end delimiter
            return (pcib + *pcibcurrentoffset - 1);
        }
        
        if (dg_isdelimiter(c) == FORTH_FALSE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }
*/
    ciboldoffset = *pcibcurrentoffset;

    //getting to the next delimiter after the word
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if ( (enddelimiter == c) || 
             ( dg_islineterminator(c) && (lineterminatorsareendflag != FORTH_FALSE) ) )
        {
            *pfoundendflag = FORTH_TRUE;
            break;
        }
        
        if (dg_isdelimiter(c) != FORTH_FALSE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

    namelength = *pcibcurrentoffset - ciboldoffset;
    
    if (*pcibcurrentoffset < *pciblength) // to skip trailing deliminter... forth standard requirement
    {
        (*pcibcurrentoffset)++;
    } 
    else
    {
        // got to end of buffer, going to treat this as you got the terminator
        *pfoundendflag = FORTH_TRUE;
    } 

    /* checked in calling routine so I'm taking this out 4/14/2020 J.N. */
    /*
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_parsewordname);
        return((unsigned char*)dg_badbufferid);
    }
    */
    
    *pwordlength = namelength;
    
    return (pcib + ciboldoffset);
}


const char* dg_savelocalstackdepthname = "dg_savelocalstackdepth";

void dg_savelocalstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 localbufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get depth of local stack
    localbufferlength = dg_getbufferlength(
        pBHarrayhead, 
        DG_LOCALS_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
        return;
    }
    
    if ((localbufferlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederrorname);
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
    }
    
    // save it to the depth stack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID,
        localbufferlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
        return;
    }
        
    return;
}

const char* dg_restorelocalstackdepthname = "dg_restorelocalstackdepth";

void dg_restorelocalstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 oldlocalbufferlength;
    
    unsigned char* plocalstack;
    UINT64* plocalsstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldlocalbufferlength = dg_popbufferuint64(
        pBHarrayhead, 
        DG_LOCALS_STACKDEPTH_BUFFERID);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    plocalstack = dg_getpbuffer(
        pBHarrayhead, 
        DG_LOCALS_DATASTACK_BUFFERID, 
        &plocalsstacklength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    if ((oldlocalbufferlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederrorname);
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
    }
    
    if (*plocalsstacklength < oldlocalbufferlength)
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    *plocalsstacklength = oldlocalbufferlength;
}


const char* dg_savelocallsstackdepthname = "dg_savelocallsstackdepth";

void dg_savelocallsstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 locallstringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get depth of locals lstring stack
    locallstringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocallsstackdepthname);
        return;
    }
    
    // save it to the depth stack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID,
        locallstringstackdepth);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocallsstackdepthname);
        return;
    }
        
    return;
}

const char* dg_restorelocallsstackdepthname = "dg_restorelocallsstackdepth";

void dg_restorelocallsstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 oldlocalslstringdepth;
    
    UINT64 currentlocalslstringdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldlocalslstringdepth = dg_popbufferuint64(
        pBHarrayhead, 
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
        return;
    }
    
    // doing this the slow way for now
    currentlocalslstringdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
        return;
    }
    
    while (currentlocalslstringdepth > oldlocalslstringdepth)
    {
        dg_droplstring (
            pBHarrayhead,
            DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
            DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
            return;
        }
            
        currentlocalslstringdepth--;
    }

}

const char* dg_tocurrentname = "dg_tocurrent";

void dg_tocurrent (
    Bufferhandle* pBHarrayhead,
    UINT64 newcurrentwordlist)
{
    UINT64 oldcurrentwordlist;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldcurrentwordlist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID,
        oldcurrentwordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        newcurrentwordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentname);
        return;
    }
}

const char* dg_currentfromname = "dg_currentfrom";

UINT64 dg_currentfrom (Bufferhandle* pBHarrayhead)
{
    UINT64 oldcurrentwordlist;
    UINT64 newcurrentwordlist;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(DG_ENDOFWORDLIST);
    }
    
    oldcurrentwordlist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_currentfromname);
        return(DG_ENDOFWORDLIST);
    }
    
    if (0 == dg_getbufferlength(
        pBHarrayhead,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID))
    {
        newcurrentwordlist = DG_ENDOFWORDLIST;
    }
    else
    {
        newcurrentwordlist = dg_popbufferuint64(
            pBHarrayhead,
            DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_currentfromname);
            return(DG_ENDOFWORDLIST);
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        newcurrentwordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_currentfromname);
        return(DG_ENDOFWORDLIST);
    }
    
    return(oldcurrentwordlist);
}

const char* dg_tocurrentcompilebufferstackname = "dg_tocurrentcompilebufferstack";

void dg_tocurrentcompilebufferstack (Bufferhandle* pBHarrayhead)
{
    UINT64 current;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    current = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentcompilebufferstackname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_CURRENTCOMPILEBUFFERSTACK_BUFFERID,
        current);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentcompilebufferstackname);
        return;
    }
}

const char* dg_fromcurrentcompilebufferstackname = "dg_fromcurrentcompilebufferstack";

void dg_fromcurrentcompilebufferstack (Bufferhandle* pBHarrayhead)
{
    UINT64 current;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    current = dg_popbufferuint64(
        pBHarrayhead,
        DG_CURRENTCOMPILEBUFFERSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fromcurrentcompilebufferstackname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer,
        current);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fromcurrentcompilebufferstackname);
        return;
    }
}

const char* dg_tocurrentvariablebufferstackname = "dg_tocurrentvariablebufferstack";

void dg_tocurrentvariablebufferstack (Bufferhandle* pBHarrayhead)
{
    UINT64 current;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    current = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentvariablebufferstackname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_CURRENTVARIABLEBUFFERSTACK_BUFFERID,
        current);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_tocurrentvariablebufferstackname);
        return;
    }
}

const char* dg_fromcurrentvariablebufferstackname = "dg_fromcurrentvariablebufferstack";

void dg_fromcurrentvariablebufferstack (Bufferhandle* pBHarrayhead)
{
    UINT64 current;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    current = dg_popbufferuint64(
        pBHarrayhead,
        DG_CURRENTVARIABLEBUFFERSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fromcurrentvariablebufferstackname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer,
        current);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fromcurrentvariablebufferstackname);
        return;
    }
}

/*
const char* dg_getbuffercurrentoffsetname = "dg_getbuffercurrentoffset";

UINT64 dg_getbuffercurrentoffset (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    Bufferhandle* pBH;
    const char* perror;

#ifdef DGLU_NO_DIAPER    
    
        pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );;
        return (pBH->currentoffset);

#else

    perror = dg_checkbharray(pBHarrayhead);

    if (perror != dg_success)
    {
        // if dg_checkbharray fails, there is no error stack, so we are just pushing one error
        // to attempt to increment the error count
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getbuffercurrentoffsetname);
        return ((UINT64)largestunsignedint);
    }

    // just checking to see if pointer can be initialized, buffer errors have priority
    if (pplength == (UINT64**)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_nullpointererror);
        dg_pusherror(pBHarrayhead, dg_getbuffercurrentoffsetname);
        return ((UINT64)largestunsignedint);
    }

    if (bufferid == DG_ERRORSTACK_BUFFERID)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_getbuffercurrentoffsetname);
        return ((UINT64)largestunsignedint);
    }
    
    // using division instead of multiplication to prevent overflow
    if (bufferid >= pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle))
    {
        dg_pusherror (pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_getbuffercurrentoffsetname);
        return ((UINT64)largestunsignedint);
    }

    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    if (pBH->pbuf == badbufferhandle)
    {
        dg_pusherror (pBHarrayhead, dg_bufferidisfree);
        dg_pusherror(pBHarrayhead, dg_getbuffercurrentoffsetname);
        return ((UINT64)largestunsignedint);
    }

    if (pBH->nextunusedbyte > pBH->size)
    {
        dg_pusherror (pBHarrayhead, dg_buffernubcorrupt);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((UINT64)largestunsignedint);
    }

    if (pBH->size > pBH->maxsize)
    {
        dg_pusherror (pBHarrayhead, dg_buffermaxsizeltsize);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((UINT64)largestunsignedint);
    }
    
    if (pBH->currentoffset > pBH->nextunusedbyte)
    {
        dg_pusherror (pBHarrayhead, dg_bufferoffsetgtlength);
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        return ((UINT64)largestunsignedint);
    }

    return (pBH->currentoffset);
    
#endif

}
*/

const char dg_noparseentercurrentlinename[] = "dg_noparseentirecurrentline";

unsigned char* dg_noparseentirecurrentline(
    Bufferhandle* pBHarrayhead,
    UINT64* plinelength,
    UINT64 bufferid)
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;

    UINT64 beginoffset = 0;
    UINT64 endoffset = 0;

    const char* perror;

    unsigned char c = 0;


    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return((unsigned char*)badbufferhandle);
    }
    
    perror = dg_putuint64(plinelength, 0);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_noparseentercurrentlinename);
        return((unsigned char*)badbufferhandle);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_noparseentercurrentlinename);
        return((unsigned char*)badbufferhandle);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );
    pcibcurrentoffset = &pBH->currentoffset;
    
    beginoffset = *pcibcurrentoffset;

    // need to parse backwards off line terminators
    //  (including if character before start character was a line terminator)
    while (beginoffset > 0)
    {
        if (beginoffset <= *pciblength)
        {
            c = *(pcib + (beginoffset - 1));

            if (!dg_islineterminator(c))
            {
                break;
            }
        }

        beginoffset--;
    }

    endoffset = beginoffset;

    // get endoffset at the end of the file or on a line terminator
    while (endoffset < *pciblength)
    {
        c = *(pcib + endoffset);

        if (dg_islineterminator(c))
        {
            // end offset will be on a line terminator or at the end of the buffer
            //  so the parsed area will not include a line terminator
            break;
        }

        endoffset++;
    }

    // at this point you are not on a line terminator
    //  or... you are at the beginning of the buffer and it's all line terminators
    //  or the buffer is empty

    while (beginoffset > 0)
    {
        beginoffset--;

        c = *(pcib + beginoffset);

        if (dg_islineterminator(c))
        {
            // not including line terminator
            beginoffset++;
            break;
        }
    }
    
    *plinelength = endoffset - beginoffset;
    
    return (pcib + beginoffset);
}


const char dg_replacebuffersegmentname[] = "dg_replacebuffersegment";

void dg_replacebuffersegment (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 destoffset,
    UINT64 destlength,
    unsigned char* psrc,
    UINT64 srclength)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    // need to insert or delete difference in lengths from end of segment
    if (srclength != destlength)
    {
        if (srclength < destlength)
        {
            // need to delete
            dg_deleteinbuffer (
                pBHarrayhead,
                bufferid,
                destoffset + srclength, 
                destlength - srclength);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_replacebuffersegmentname);
                return;
            }
        }
        else
        {
            // need to insert
            dg_insertinbuffer (
                pBHarrayhead,
                bufferid,
                destoffset + destlength, // in bytes
                srclength - destlength);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
            dg_pusherror(pBHarrayhead, dg_replacebuffersegmentname);
                return;
            }
        }
    }
    
    // need to do putbuffersegment....
    dg_putbuffersegment(
        pBHarrayhead,
        bufferid,
        destoffset,
        srclength,
        psrc);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_replacebuffersegmentname);
    }
}


const char dg_parselinename[] = "dg_parseline";

unsigned char* dg_parseline(
    Bufferhandle* pBHarrayhead,
    UINT64* plinelength) 
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;
    UINT64 ciboldoffset = 0;

    UINT64 cibid = 0;

    unsigned char c = 0;

    Bufferhandle* pBH = NULL;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)dg_badbufferid);
    }
    
    pError = dg_putuint64(plinelength, 0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_parselinename);
        return((unsigned char*)dg_badbufferid);
    }
    
    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parselinename);
        return((unsigned char*)dg_badbufferid);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_parselinename);
        return((unsigned char*)dg_badbufferid);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;

    // assumes at the start of a line
    ciboldoffset = *pcibcurrentoffset;

    //getting to the next terminator after the line
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if (dg_islineterminator(c) != FORTH_FALSE)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }
    
    *plinelength = *pcibcurrentoffset - ciboldoffset;
    
    // parsing exactly one eol
    if(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        // consuming the one line terminator
        (*pcibcurrentoffset)++;
        
        // handling the crlf case because crlf pair is one terminator
        if ('\r' == c) // cr
        {
            if(*pcibcurrentoffset < *pciblength)
            {
                c = *(pcib + *pcibcurrentoffset);
                
                if ('\n' == c) // lf
                {
                    (*pcibcurrentoffset)++;
                }
            }
        }
    }
    
    return (pcib + ciboldoffset);
}


const char dg_noparselineatoffsetname[] = "dg_parselineatoffset";

UINT64 dg_noparselineatoffset(
    Bufferhandle* pBHarrayhead,
    UINT64 cibid,
    UINT64 offset) 
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64 currentoffset = 0;
    UINT64 ciboldoffset = 0;
    
    UINT64 linenumber = 0;

    unsigned char c = 0;

    Bufferhandle* pBH = NULL;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(linenumber);
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_noparselineatoffsetname);
        return(linenumber);
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );

    // assumes at the start of a line
    
    
    while (currentoffset < *pciblength)
    {
    
        // parse one line
        ciboldoffset = currentoffset;
        
        //getting to the next terminator after the line
        while(currentoffset < *pciblength)
        {
            c = *(pcib + currentoffset);
        
            if (dg_islineterminator(c) != FORTH_FALSE)
            {
                break;
            }

            currentoffset++;
        }
    
        // parsing exactly one eol
        if(currentoffset < *pciblength)
        {
            c = *(pcib + currentoffset);
        
            // consuming the one line terminator
            currentoffset++;
        
            // handling the crlf case because crlf pair is one terminator
            if ('\r' == c) // cr
            {
                if(currentoffset < *pciblength)
                {
                    c = *(pcib + currentoffset);
                
                    if ('\n' == c) // lf
                    {
                        (currentoffset)++;
                    }
                }
            }
        }
        
        // if you haven't found end, increment line number and keep going
        if ((currentoffset <= offset) && (currentoffset < *pciblength))
        {
            linenumber++;
        }
        else
        {
            break;
        }
    }
    
    return (linenumber);
}


const char dg_ubufferalignname[] = "dg_ubufferalign";

UINT64 dg_ubufferalign(
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 u) 
{
    UINT64 bufferlength, x;
    const char* pError;
  
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(largestunsignedint);
    }

    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        bufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ubufferalignname);
        return(largestunsignedint);
    }

    x = bufferlength % u;

    if (x > 0)
    {
        dg_growbuffer (
            pBHarrayhead,
            bufferid,
            u - x,
            &pError,
            FORTH_FALSE);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_ubufferalignname);
            return(largestunsignedint);
        }

        return(bufferlength + (u-x));
    }

    return(bufferlength);
}


