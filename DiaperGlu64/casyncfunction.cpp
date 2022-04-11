// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.2.
//
//    DiaperGlu v5.2 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.2 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.2; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// April 10, 2022             //
// version 5.2                //
// /////////////////////////////


#include "diapergluforth.h"

// parent holds go mutex
// child holds I got the message mutex
//  ...
// parent sets up the function to call
// parent waits for (grabs) the stop mutex
// parent releases the go mutex
// parent waits for child to release I got the go mutex which means
//  child now holds the go mutex
// parent releases the I got the go mutex
// parent does other stuff
//  ...
// child may or may not be done, may or may not have released the go mutex
//  and may or may not be waiting on the stop mutex
// 
// parent waits for the go mutex
// parent releases the stop mutex
// parent waits for the child to release the I got the stop mutex which means
//  the child now holds the stop mutex
// parent releases the I got the stop mutex
//  ... and things are back were they started


// child waits for go mutex
// child gets the I got the stop mutex back
// child releases I got the go mutex
// child calls the async function(s)
// child releases the go mutex

// child waits for stop mutex
// child gets the I got the go mutex back
// child releases the I got the stop mutex
// child releases the stop mutex

// I think this covers all the timing cases....

// to initialize...
//  parent creates 3 mutexes
//  parent grabs the go mutex
//  parent starts the child thread
//  parent can't use the child until it has the I got the go mutex...
//   so the first time the parent uses the child... it has to busy wait
//   I'll use a child is initialized flag to indicate the child did this...
//   (If you don't... the parent may release the go mutex and get the I got the 
//    go mutex before the child ever got it... causing a deadlock...)

// need to maintain a list of async function children...
//  so when parent wants to call a function, it has a pool ready to go..
//  and let the user set a maximum limit...
//  so like a freeable lstring array... except instead of a list of free
//  lstrings, it's a linked list of what's available... mostly available
//  instead of mostly in use... 


// need the child function

const char* dg_asfcgrabigotgomutexstate = "error grabbing I got go mutex";
const char* dg_asfcgrabigotstopmutexstate = "error grabbing I got stop mutex";
const char* dg_asfcgrabgomutexstate = "error grabbing go mutex";
const char* dg_asfcgrabstopmutexstate = "error grabbing go mutex";

const char* dg_asfcreleaseigotgomutexstate = "error releasing I got go mutex";
const char* dg_asfcreleaseigotstopmutexstate = "error releasing I got stop mutex";
const char* dg_asfcreleasegomutexstate = "error releasing go mutex";
const char* dg_asfcreleasestopmutexstate = "error releasing go mutex";

void dg_childasyncfunctioncallerthread(DG_AsyncFunctionCallerHeader *pasfch)
{
    const char* pError;
    UINT64 doneflag = FORTH_FALSE;
    
    // init the BHarrayhead
    dg_initpbharrayhead(&(pasfch.childBHarrayhead));
    
    // init errors
    dg_initerrors (
        &(pasfch.childBHarrayhead),
        dg_getpagesize(),            // UINT64 size,
        &pError);
        
    if (pError != dg_success)
    {
        return;
    }
    
    // child now has an error stack
    
    // child grabs the I got the go mutex
    pError = dg_lockmutex(
        pasfch->childgotgomutexHolder, // UINT64 mutexHolder, 
        dg_success);                        // const char* forceerrorflag)
        
    if (pError != dg_success)
    {
        dg_pusherror(
            &(pasfch.childBHarrayhead), 
            pError);
        dg_pusherror(
            &(pasfch.childBHarrayhead), 
            dg_lockmutexname);
        dg_pusherror(
            &(pasfch.childBHarrayhead), 
            dg_asfcgrabigotgomutexstate);
        return; // having the thread exit...
    }
    
    while(FORTH_FALSE == doneflag)
    {
        // child waits for the go mutex
        pError = dg_lockmutex(
            pasfch->childgomutexHolder,  
            dg_success);                // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_lockmutexname;
            pasfch->childlasterrorstate = dg_asfcgrabgomutexstate;
        
            return; // having the thread exit...
        }
        
        // child waits for the I got the stop mutex
        pError = dg_lockmutex(
            pasfch->childgotstopmutexHolder, 
            dg_success);                     // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_lockmutexname;
            pasfch->childlasterrorstate = dg_asfcgrabigotstopmutexstate;
        
            return; // having the thread exit...
        }
        
        // child releases the I got the go mutex
        pError = dg_unlockmutex(
            pasfch->childgotgomutexHolder, 
            dg_success);                   // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_unlockmutexname;
            pasfch->childlasterrorstate = dg_asfcreleaseigotgomutexstate;
        
            return; // having the thread exit...
        }
        
        // call the function
        pasfch->pfunction(&(pasfch->childpBHarrayhead));
        
        // child releases the go the go mutex
        pError = dg_unlockmutex(
            pasfch->childgomutexHolder, 
            dg_success);                // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_unlockmutexname;
            pasfch->childlasterrorstate = dg_asfcreleasegomutexstate;
        
            return; // having the thread exit...
        }
        
        // ////////
        
        // child waits for the stop mutex
        pError = dg_lockmutex(
            pasfch->childstopmutexHolder, 
            dg_success);                  // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_lockmutexname;
            pasfch->childlasterrorstate = dg_asfcgrabstopmutexstate;
        
            return; // having the thread exit...
        }
        
        // child waits for the I got the go mutex
        pError = dg_lockmutex(
            pasfch->childgotgomutexHolder, 
            dg_success);                     // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_lockmutexname;
            pasfch->childlasterrorstate = dg_asfcgrabigotgomutexstate;
        
            return; // having the thread exit...
        }
        
        // child releases the I got the stop mutex
        pError = dg_unlockmutex(
            pasfch->childgotstopmutexHolder, 
            dg_success);                     // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_unlockmutexname;
            pasfch->childlasterrorstate = dg_asfcreleaseigotstopmutexstate;
        
            return; // having the thread exit...
        }
        
        // child releases the stop the go mutex
        pError = dg_unlockmutex(
            pasfch->childstopmutexHolder, 
            dg_success);                // const char* forceerrorflag)
        
        if (pError != dg_success)
        {
            if (pasfch->childerrorcount < largestunsignedint)
            {
                pasfch->childerrorcount++;
            }
        
            pasfch->childlasterror = pError;
            pasfch->childlasterrorroutine = dg_unlockmutexname;
            pasfch->childlasterrorstate = dg_asfcreleasestopmutexstate;
        
            return; // having the thread exit...
        }
    }
}
    

const char* dg_intasyncfucntioncallerheadername =  "dg_intasyncfucntioncallerheader";

void dg_intasyncfucntioncallerheader (
    Bufferhandle *pBHarrayhead,
	DG_AsyncFunctionCallerHeader *pasfch) //need size too
{
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // make sure you can write to the DG_AsyncFunctionCallerHeader
    pError = dg_fillwithbyte (
        (unsigned char*)pasfch,
        sizeof(DG_AsyncFunctionCallerHeader),
        0);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_intasyncfucntioncallerheadername);
        return;
    }
    
    pLstringqueueheader->magic = dg_afchmagic;
    
    pError = dg_newmutex(
        &(pasfch->childgomutexmem), // unsigned char* pmutexmem,  
        &(pasfch->childgomutexHolder), 
        dg_success); // const char* forceerrorflag)
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newmutexname);
        dg_pusherror(pBHarrayhead, dg_intasyncfucntioncallerheadername);
        return;
    }
    
    pError = dg_newmutex(
        &(pasfch->childstopmutexmem), // unsigned char* pmutexmem,  
        &(pasfch->childstopmutexHolder), 
        dg_success); // const char* forceerrorflag)
        
    if (pError != dg_success)
    {
        // ignoring error from free
        dg_freemutex(
            pasfch->childgomutexHolder, 
            dg_success);
    
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newmutexname);
        dg_pusherror(pBHarrayhead, dg_intasyncfucntioncallerheadername);
        return;
    }
    
    pError = dg_newmutex(
        &(pasfch->childgotmessagemutexmem), // unsigned char* pmutexmem,  
        &(pasfch->childgotmessagemutexHolder), 
        dg_success); // const char* forceerrorflag)
        
    if (pError != dg_success)
    {
        // ignoring error from free
        dg_freemutex(
            pasfch->childgomutexHolder, 
            dg_success);
            
        dg_freemutex(
            pasfch->childstopmutexHolder, 
            dg_success);
    
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newmutexname);
        dg_pusherror(pBHarrayhead, dg_intasyncfucntioncallerheadername);
        return;
    }
    
    
}



