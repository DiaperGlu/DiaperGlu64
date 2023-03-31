// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.9.
//
//    DiaperGlu v5.9 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.9 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.9; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// March 31, 2023             //
// version 5.9                //
// /////////////////////////////


#include "diapergluforth.h"

const char* dg_initlstringqueuename =  "dg_initlstringqueue";

void dg_initlstringqueue (
    Bufferhandle *pBHarrayhead,
    UINT64 growby,
    UINT64 maxsize,
    UINT64 switchlength,
    Lstringqueueheader* pLstringqueueheader) //need size too
{
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // making sure switchlength isn't too big to make sure your queues
    //  don't eat up all your memory. This check is also to make sure
    //  the dg_addclipped overflow check works in dg_pushlstringqueuehead
    //  (dg_uaddclipped uses largestunsignedint to indicate arithmetic overflow)
    if (switchlength > dg_maxlstringqueueswitchlength)
    {
        dg_pusherror(pBHarrayhead, dg_queueswitchlengthtoobigerror);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        return;
    }

    // make sure you can write to the lstringqueueheader
    pError = dg_fillwithbyte (
        (unsigned char*)pLstringqueueheader,
        sizeof(Lstringqueueheader),
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        return;
    }
    
    pLstringqueueheader->magic = dg_lstringqueuemagic;
    
    pLstringqueueheader->lstringoffsetbufferida = dg_newbuffer (
        pBHarrayhead,
        growby,
        maxsize,
        &pError,
        FORTH_FALSE);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        return;
    }
    
    pLstringqueueheader->lstringstringbufferida = dg_newbuffer (
        pBHarrayhead,
        growby,
        maxsize,
        &pError,
        FORTH_FALSE);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        
        // making it so that all the buffers are allocated, or none
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringoffsetbufferida);
      
        pLstringqueueheader->lstringoffsetbufferida = (UINT64)dg_badbufferid;
        return;
    }
    
    pLstringqueueheader->lstringoffsetbufferidb = dg_newbuffer (
        pBHarrayhead,
        growby,
        maxsize,
        &pError,
        FORTH_FALSE);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        
        // making it so that all the buffers are allocated, or none
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringoffsetbufferida);
      
        pLstringqueueheader->lstringoffsetbufferida = (UINT64)dg_badbufferid;
        
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringstringbufferida);
      
        pLstringqueueheader->lstringstringbufferida = (UINT64)dg_badbufferid;
        return;
    }
    
    pLstringqueueheader->lstringstringbufferidb = dg_newbuffer (
        pBHarrayhead,
        growby,
        maxsize,
        &pError,
        FORTH_FALSE);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_initlstringqueuename);
        
        // making it so that all the buffers are allocated, or none
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringoffsetbufferida);
      
        pLstringqueueheader->lstringoffsetbufferida = (UINT64)dg_badbufferid;
        
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringstringbufferida);
      
        pLstringqueueheader->lstringstringbufferida = (UINT64)dg_badbufferid;
        
        dg_freebuffer (
            pBHarrayhead,
            pLstringqueueheader->lstringoffsetbufferidb);
      
        pLstringqueueheader->lstringoffsetbufferidb = (UINT64)dg_badbufferid;
        return;
    }
    
    pLstringqueueheader->pusharray = 0;
    pLstringqueueheader->switchlength = switchlength;
    pLstringqueueheader->poparray = 0;
    pLstringqueueheader->popindex = 0;
}

/*
struct Lstringqueueheader
    {
        UINT64 magic;                  // 'lstq'
        UINT64 lstringoffsetbufferida;
        UINT64 lstringstringbufferida;
        UINT64 lstringoffsetbufferidb;
        UINT64 lstringstringbufferidb;      
        UINT64 pusharray;              // current push L$array (0 or 1)
        UINT64 switchlength;
        UINT64 poparray;               // current pop L$array (0 or 1)
        UINT64 popindex;
    };
*/

const char* dg_pushlstringqueueheadname = "dg_pushlstringqueuehead";

void dg_pushlstringqueuehead (
    Bufferhandle* pBHarrayhead,
    Lstringqueueheader* pLstringqueueheader, // need size too
    unsigned char* pstring,
    UINT64 stringlength)
{
    UINT64 currentpushoffsetbuffer;
    UINT64 currentpushstringbuffer;
    UINT64 numberoflstringsonstack;
    UINT64 currentpushoffsetbufferlength;
    UINT64 currentpushstringbufferlength;
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // push goes into current L$stack and grow is done if needed if:
    //   tail is in other stack or
    //   current L$stack is empty or
    //   length of both buffers of current L$stack after push will be less than
    //     the switch length
    // otherwise push goes onto the other L$stack and if it isn't emtpy, empty it
    //   and the the other L$stack becomes the current L$stack
    
    if (pLstringqueueheader->magic != dg_lstringqueuemagic)
    {
        
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
        return;
    }
    
    if (0 == pLstringqueueheader->pusharray)
    {
        currentpushoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpushstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpushoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpushstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpushoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
        return;
    }
    
    if ( (pLstringqueueheader->pusharray != pLstringqueueheader->poparray) ||
         (0 == numberoflstringsonstack) )
    {
        // push to the end of the current L$array
        dg_pushlstring (
            pBHarrayhead,
            currentpushoffsetbuffer,
            currentpushstringbuffer,
            stringlength,
            pstring);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
            return;
        }      
            
        return;
    }
    
    // get the length of the current buffers
    currentpushoffsetbufferlength = dg_getbufferlength(pBHarrayhead, currentpushoffsetbuffer);
    currentpushstringbufferlength = dg_getbufferlength(pBHarrayhead, currentpushstringbuffer);
    
    // dg_uaddclipped assumes switchlength < (UINT64)largestunsignedint
    if ((dg_uaddclipped(currentpushoffsetbufferlength, stringlength) <= pLstringqueueheader->switchlength) &&
        (dg_uaddclipped(currentpushstringbufferlength, stringlength) <= pLstringqueueheader->switchlength))
    {
        // push to the end of the current L$array
        dg_pushlstring (
            pBHarrayhead,
            currentpushoffsetbuffer,
            currentpushstringbuffer,
            stringlength,
            pstring);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
            return;
        }  
        
        return;
    }
    
    
    // switch current head to the other L$array
    if (0 == pLstringqueueheader->pusharray)
    {
        pLstringqueueheader->pusharray = 1;
        currentpushoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpushstringbuffer = pLstringqueueheader->lstringstringbufferidb;
        
    }
    else
    {
        pLstringqueueheader->pusharray = 0;
        currentpushoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpushstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    
    // empty the other L$array if it isn't empty
    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        currentpushoffsetbuffer,
        &pbufferlength);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
        return;
    }
    
    *pbufferlength = 0; 
    
    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        currentpushstringbuffer,
        &pbufferlength);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
        return;
    }
    
    *pbufferlength = 0;   
    
    // push to the end of the new current L$array
    dg_pushlstring (
        pBHarrayhead,
        currentpushoffsetbuffer,
        currentpushstringbuffer,
        stringlength,
        pstring);
      
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushlstringqueueheadname);
        return;
    }
}


const char* dg_poplstringqueuetailname = "dg_poplstringqueuetail";

unsigned char* dg_poplstringqueuetail (
    Bufferhandle* pBHarrayhead,
    Lstringqueueheader* pLstringqueueheader, // need size too
    UINT64* pstringlength)
{
    UINT64 currentpopoffsetbuffer;
    UINT64 currentpopstringbuffer;
    UINT64 numberoflstringsonstack;
    unsigned char* plstring;
    
    UINT64 magic;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)badbufferhandle);
    }
    
    // make sure pstringlength is valid... put 0 in it
    pError = dg_putuint64 (
        pstringlength,
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    // should we check if the queheader mem is valid?
    pError = dg_getuint64 (
        &(pLstringqueueheader->magic), // paddr,
        &magic); // pn)(pLstringqueueheader->magic
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
        
    if (magic != dg_lstringqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    // if tail is not at end of current tail L$ stack
    //    get addr length of current tail L$ 
    //    increment current tail L$ index
    //    return addr length
    //  
    if (pLstringqueueheader->popindex < numberoflstringsonstack)
    {
        plstring = dg_getplstring(
            pBHarrayhead,
            currentpopoffsetbuffer,
            currentpopstringbuffer,
            pLstringqueueheader->popindex,
            pstringlength);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
            return((unsigned char*)badbufferhandle);
        }
        
        pLstringqueueheader->popindex++;
        
        return(plstring);
    }
    
    // if tail is in same queue as head
    //   return that the queue is empty
    if (pLstringqueueheader->pusharray == pLstringqueueheader->poparray)
    {
        *pstringlength = 0;
        return ((unsigned char*)badbufferhandle);
    }
    
    // move tail to start of same L$ stack as head
    //   get addr length of current tail L$ 
    //   increment current tail L$ index
    //   return addr length
    
    pLstringqueueheader->poparray = pLstringqueueheader->pusharray;
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    pLstringqueueheader->popindex = 0;
    
    // the other L$ stack should not be empty, but just in case...
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    if (0 == numberoflstringsonstack)
    {
        *pstringlength = 0;
        return ((unsigned char*)badbufferhandle);
    }
    
    plstring = dg_getplstring(
        pBHarrayhead,
        currentpopoffsetbuffer,
        currentpopstringbuffer,
        pLstringqueueheader->popindex,
        pstringlength);
      
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_poplstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
        
    pLstringqueueheader->popindex++;
        
    return(plstring);
}

const char* dg_getslstringqueuetailname = "dg_getslstringqueuetail";

unsigned char* dg_getslstringqueuetail (
    Bufferhandle* pBHarrayhead,
    Lstringqueueheader* pLstringqueueheader,
    UINT64 lstringqueheaderlength,
    UINT64* pstringlength)
{
    UINT64 currentpopoffsetbuffer;
    UINT64 currentpopstringbuffer;
    UINT64 numberoflstringsonstack;
    unsigned char* plstring;
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)badbufferhandle);
    }
    
    if (lstringqueheaderlength < sizeof(Lstringqueueheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    lengthtocheck = lstringqueheaderlength;
    
    if (sizeof(Lstringqueueheader) < lengthtocheck)
    {
        lengthtocheck = sizeof(Lstringqueueheader);
    }
        
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)pLstringqueueheader,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
        
    if (pLstringqueueheader->magic != dg_lstringqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    // make sure pstringlength is valid... put 0 in it
    pError = dg_putuint64 (
        pstringlength,
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    // if tail is not at end of current tail L$ stack
    //    get addr length of current tail L$ 
    //    increment current tail L$ index
    //    return addr length
    //  
    if (pLstringqueueheader->popindex < numberoflstringsonstack)
    {
        plstring = dg_getplstring(
            pBHarrayhead,
            currentpopoffsetbuffer,
            currentpopstringbuffer,
            pLstringqueueheader->popindex,
            pstringlength);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
            return((unsigned char*)badbufferhandle);
        }
        
        // pLstringqueueheader->popindex++;
        
        return(plstring);
    }
    
    // if tail is in same queue as head
    //   return that the queue is empty
    if (pLstringqueueheader->pusharray == pLstringqueueheader->poparray)
    {
        *pstringlength = 0;
        return ((unsigned char*)badbufferhandle);
    }
    
    // move tail to start of same L$ stack as head
    //   get addr length of current tail L$ 
    //   increment current tail L$ index
    //   return addr length
    
    pLstringqueueheader->poparray = pLstringqueueheader->pusharray;
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    pLstringqueueheader->popindex = 0;
    
    // the other L$ stack should not be empty, but just in case...
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    if (0 == numberoflstringsonstack)
    {
        *pstringlength = 0;
        return ((unsigned char*)badbufferhandle);
    }
    
    plstring = dg_getplstring(
        pBHarrayhead,
        currentpopoffsetbuffer,
        currentpopstringbuffer,
        pLstringqueueheader->popindex,
        pstringlength);
      
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
        
    // pLstringqueueheader->popindex++;
        
    return(plstring);
}

const char* dg_droplstringqueuetailname = "dg_droplstringqueuetail";

void dg_droplstringqueuetail (
    Bufferhandle* pBHarrayhead,
    Lstringqueueheader* pLstringqueueheader,
    UINT64 lstringqueheaderlength) 
{
    UINT64 currentpopoffsetbuffer;
    UINT64 currentpopstringbuffer;
    UINT64 numberoflstringsonstack;
    // unsigned char* plstring;
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (lstringqueheaderlength < sizeof(Lstringqueueheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        return;
    }
    
    lengthtocheck = lstringqueheaderlength;
    
    if (sizeof(Lstringqueueheader) < lengthtocheck)
    {
        lengthtocheck = sizeof(Lstringqueueheader);
    }
        
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)pLstringqueueheader,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        return;
    }
        
    if (pLstringqueueheader->magic != dg_lstringqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        return;
    }
    
    // make sure pstringlength is valid... put 0 in it
    // pError = dg_putuint64 (
    //   pstringlength,
    //   0);
        
    // if (pError != dg_success)
    // {
    //    dg_pusherror(pBHarrayhead, pError);
    //    dg_pusherror(pBHarrayhead, dg_putuint64name);
    //    dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
    //    return;
    // }
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        return;
    }
    
    // if tail is not at end of current tail L$ stack
    //    get addr length of current tail L$ 
    //    increment current tail L$ index
    //    return addr length
    //  
    if (pLstringqueueheader->popindex < numberoflstringsonstack)
    {
        // plstring = dg_getplstring(
        //    pBHarrayhead,
        //    currentpopoffsetbuffer,
        //    currentpopstringbuffer,
        //    pLstringqueueheader->popindex,
        //    pstringlength);
      
        // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        // {
        //    dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        //    return;
        // }
        
        pLstringqueueheader->popindex++;
        
        return;
    }
    
    // if tail is in same queue as head
    //   return that the queue is empty
    if (pLstringqueueheader->pusharray == pLstringqueueheader->poparray)
    {
        // *pstringlength = 0;
        return;
    }
    
    // move tail to start of same L$ stack as head
    //   get addr length of current tail L$ 
    //   increment current tail L$ index
    //   return addr length
    
    pLstringqueueheader->poparray = pLstringqueueheader->pusharray;
    
    if (0 == pLstringqueueheader->poparray)
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferida;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferida;
    }
    else
    {
        currentpopoffsetbuffer = pLstringqueueheader->lstringoffsetbufferidb;
        currentpopstringbuffer = pLstringqueueheader->lstringstringbufferidb;
    }
    
    pLstringqueueheader->popindex = 0;
    
    // the other L$ stack should not be empty, but just in case...
    numberoflstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        currentpopoffsetbuffer);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
        return;
    }
    
    if (0 == numberoflstringsonstack)
    {
        // *pstringlength = 0;
        return;
    }
    
    // plstring = dg_getplstring(
    //    pBHarrayhead,
    //    currentpopoffsetbuffer,
    //    currentpopstringbuffer,
    //    pLstringqueueheader->popindex,
    //    pstringlength);
      
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_droplstringqueuetailname);
    //    return((unsigned char*)badbufferhandle);
    // }
        
    pLstringqueueheader->popindex++;
        
    return;
}

/*
struct SharedQueueHandleBufferStructs {
        UINT64 magic; // 'sqhb'
        struct Bufferhandle sharedQueueBHarrayhead;
        struct Lstringqueueheader lsQueueHeader;
        UINT64 mutexhandle;
        unsigned char mutexmem[DG_MUTEX_MEM_SIZE]; // mac os x needs this
    };
     
#define dg_sharedqueuemagic (0x62687473)
*/

const char* dg_newsharedlstringqueuename = "dg_newsharedlstringqueue";

UINT64 dg_newsharedlstringqueue(
    Bufferhandle* pBHarrayhead,
    UINT64 growby,       // of the shared queue buffers
    UINT64 maxsize,      // of the shared queue buffers
    UINT64 switchlength) //need size too
{
    UINT64 SharedQueueHandleSize;
    UINT64 SharedQueueHandleBufferID;
    
    SharedQueueHandleBufferStructs* psharedqueuebuffer;
    UINT64* psharedqueuebufferlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((UINT64)dg_badbufferid);
    }
    
    // this should be one page on Windows and Mac OS X
    SharedQueueHandleSize = dg_calcnearestpagesize(sizeof(SharedQueueHandleBufferStructs)); 
    
    SharedQueueHandleBufferID = dg_newbuffer (
        pBHarrayhead,
        SharedQueueHandleSize,
        SharedQueueHandleSize,
        &pError,
        FORTH_FALSE);
  
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    dg_growbuffer (
        pBHarrayhead,
        SharedQueueHandleBufferID,
        sizeof(SharedQueueHandleBufferStructs), // length,  // in bytes
        &pError,
        FORTH_FALSE); // forceoutofmemory);
  
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    psharedqueuebuffer = (SharedQueueHandleBufferStructs*)dg_getpbuffer (
        pBHarrayhead,
        SharedQueueHandleBufferID,
        &psharedqueuebufferlength);
  
    // this shouldn't happen
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer(pBHarrayhead, SharedQueueHandleBufferID);
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    psharedqueuebuffer->magic = dg_sharedqueuemagic;
    
    dg_initpbharrayhead(&(psharedqueuebuffer->sharedQueueBHarrayhead));
    
    dg_initerrors (
        &(psharedqueuebuffer->sharedQueueBHarrayhead),
        dg_getpagesize(),
        &pError);
        
    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, SharedQueueHandleBufferID);
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    dg_initlstringqueue (
        &(psharedqueuebuffer->sharedQueueBHarrayhead),
        growby,
        maxsize,
        switchlength,
        &(psharedqueuebuffer->lsQueueHeader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freeallbuffers(&(psharedqueuebuffer->sharedQueueBHarrayhead));
        dg_freebuffer(pBHarrayhead, SharedQueueHandleBufferID);
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    pError = dg_newmutex(  
        &(psharedqueuebuffer->mutexHolder),
        dg_success);
        
    if (pError != dg_success)
    {
        dg_freeallbuffers(&(psharedqueuebuffer->sharedQueueBHarrayhead));
        dg_freebuffer(pBHarrayhead, SharedQueueHandleBufferID);
        dg_pusherror(pBHarrayhead, dg_newsharedlstringqueuename);
        return((UINT64)dg_badbufferid);
    }
    
    return(SharedQueueHandleBufferID);
}


const char* dg_freesharedlstringqueuename = "dg_freesharedlstringqueue";

void dg_freesharedlstringqueue(
    Bufferhandle* pBHarrayhead,
    UINT64 SharedQueueHandleBufferID)
{
    SharedQueueHandleBufferStructs* psharedqueuebuffer;
    UINT64* psharedqueuebufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psharedqueuebuffer = (SharedQueueHandleBufferStructs*)dg_getpbuffer (
        pBHarrayhead,
        SharedQueueHandleBufferID,
        &psharedqueuebufferlength);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freesharedlstringqueuename);
        return;
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_freesharedlstringqueuename);
        return;
    }
    
    dg_freeallbuffers(&(psharedqueuebuffer->sharedQueueBHarrayhead));
    dg_freebuffer(pBHarrayhead, SharedQueueHandleBufferID);
}

const char* dg_pushsharedlstringqueuename = "dg_pushsharedlstringqueue";

void dg_pushsharedlstringqueue(
    Bufferhandle* pBHarrayhead,
    SharedQueueHandleBufferStructs* psharedqueuebuffer, // has to be the pointer
    UINT64 sharedquebufferlength,                       // making them pass the length too
    unsigned char* pstring,
    UINT64 stringlength)
{
    UINT64 magic;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // checking memory at psharedqueuebuffer... just checking magic's memory for now
    pError = dg_getuint64 (
        &psharedqueuebuffer->magic,
        &magic);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
        return;
    }
    
    if (magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
        return;
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
        return;
    }
    
    // lock mutex
    pError = dg_lockmutex(
        &(psharedqueuebuffer->mutexHolder), 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_lockmutexname);
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
    }
        
    // push string
    dg_pushlstringqueuehead (
        pBHarrayhead,
        &(psharedqueuebuffer->lsQueueHeader), 
        pstring,
        stringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
        return;
    }
    
    // free mutex
    pError = dg_freemutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_pushsharedlstringqueuename);
    }
}


const char* dg_lockpopsharedlstringqueuetailname = "dg_lockpopsharedlstringqueuetail";

unsigned char* dg_lockpopsharedlstringqueuetail (
    Bufferhandle* pBHarrayhead,
    SharedQueueHandleBufferStructs* psharedqueuebuffer, 
    UINT64 sharedquebufferlength,
    UINT64* pstringlength)
{
    unsigned char* pstring;
    UINT64 lengthtocheck = sizeof(UINT64);
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)largestunsignedint);
    }
    
    // check memory at pstringlength
    pError = dg_putuint64(
        pstringlength,
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // checking memory at psharedqueuebuffer... just checking magic's memory for now
    pError = dg_readallbytes (
        (unsigned char*)psharedqueuebuffer,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // lock mutex
    pError = dg_lockmutex(
        &(psharedqueuebuffer->mutexHolder), 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_lockmutexname);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
        
    pstring = dg_poplstringqueuetail (
        pBHarrayhead,
        &(psharedqueuebuffer->lsQueueHeader), // need size too
        pstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // unlock mutex
    pError = dg_unlockmutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_lockpopsharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    return (pstring);
}


const char* dg_getssharedlstringqueuetailname = "dg_getssharedlstringqueuetail";

unsigned char* dg_getssharedlstringqueuetail (
    Bufferhandle* pBHarrayhead,
    SharedQueueHandleBufferStructs* psharedqueuebuffer, 
    UINT64 sharedquebufferlength,
    UINT64* pstringlength)
{
    unsigned char* pstring;
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)largestunsignedint);
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    lengthtocheck = sharedquebufferlength;
    
    if (sizeof(SharedQueueHandleBufferStructs) < lengthtocheck)
    {
        lengthtocheck = sizeof(SharedQueueHandleBufferStructs);
    }
    
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)psharedqueuebuffer,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_getslstringqueuetailname);
        return((unsigned char*)badbufferhandle);
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // check memory at pstringlength
    pError = dg_putuint64(
        pstringlength,
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // lock mutex
    pError = dg_lockmutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_lockmutexname);
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
        
    pstring = dg_getslstringqueuetail (
        pBHarrayhead,
        &(psharedqueuebuffer->lsQueueHeader),
        sizeof(Lstringqueueheader), 
        pstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    // free mutex
    pError = dg_freemutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_getssharedlstringqueuetailname);
        return((unsigned char*)largestunsignedint);
    }
    
    return (pstring);
}


const char* dg_dropsharedlstringqueuetailname = "dg_dropsharedlstringqueuetail";

void dg_dropsharedlstringqueuetail (
    Bufferhandle* pBHarrayhead,
    SharedQueueHandleBufferStructs* psharedqueuebuffer, 
    UINT64 sharedquebufferlength)
{
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_dropsharedlstringqueuetailname);
        return;
    }
    
    lengthtocheck = sharedquebufferlength;
    
    if (sizeof(SharedQueueHandleBufferStructs) < lengthtocheck)
    {
        lengthtocheck = sizeof(SharedQueueHandleBufferStructs);
    }
    
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)psharedqueuebuffer,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_dropsharedlstringqueuetailname);
        return;
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_dropsharedlstringqueuetailname);
        return;
    }
    
    dg_droplstringqueuetail(
        pBHarrayhead,
        &(psharedqueuebuffer->lsQueueHeader),
        sizeof(Lstringqueueheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dropsharedlstringqueuetailname);
        return;
    }
    
    // free mutex
    pError = dg_freemutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_dropsharedlstringqueuetailname);
        return;
    }
}


const char* dg_locksharedlstringqueuename = "dg_locksharedlstringqueue";

void dg_locksharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, 
        UINT64 sharedquebufferlength)
{
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_locksharedlstringqueuename);
        return;
    }
    
    lengthtocheck = sharedquebufferlength;
    
    if (sizeof(SharedQueueHandleBufferStructs) < lengthtocheck)
    {
        lengthtocheck = sizeof(SharedQueueHandleBufferStructs);
    }
    
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)psharedqueuebuffer,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_locksharedlstringqueuename);
        return;
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_locksharedlstringqueuename);
        return;
    }
    
    // unlock mutex
    pError = dg_lockmutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_locksharedlstringqueuename);
        return;
    }
}


const char* dg_unlocksharedlstringqueuename = "dg_unlocksharedlstringqueue";

void dg_unlocksharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, 
        UINT64 sharedquebufferlength)
{
    UINT64 lengthtocheck;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (sharedquebufferlength < sizeof(SharedQueueHandleBufferStructs))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_unlocksharedlstringqueuename);
        return;
    }
    
    lengthtocheck = sharedquebufferlength;
    
    if (sizeof(SharedQueueHandleBufferStructs) < lengthtocheck)
    {
        lengthtocheck = sizeof(SharedQueueHandleBufferStructs);
    }
    
    // should we check if the queheader mem is valid?
    //  probably make nodiaperglu flag remove this check...
    pError = dg_readallbytes (
        (unsigned char*)psharedqueuebuffer,
        lengthtocheck);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_readallbytesname);
        dg_pusherror(pBHarrayhead, dg_unlocksharedlstringqueuename);
        return;
    }
    
    if (psharedqueuebuffer->magic != dg_sharedqueuemagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_unlocksharedlstringqueuename);
        return;
    }
    
    // unlock mutex
    pError = dg_unlockmutex(
        &(psharedqueuebuffer->mutexHolder), // mutexhandle 
        dg_success); // forceerrorflag
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freemutexname);
        dg_pusherror(pBHarrayhead, dg_unlocksharedlstringqueuename);
        return;
    }
}
