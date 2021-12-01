// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2021 James Patrick Norris
//
//    This file is part of DiaperGlu v5.0.
//
//    DiaperGlu v5.0 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.0 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.0; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// January 9, 2021            //
// version 5.0                //
// /////////////////////////////


#include "diapergluforth.h"

void dg_forthdashtrailing (Bufferhandle* pBHarrayhead)
//     ( caddr1 u1 -- caddr2 u2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofspaces;
    
    const char* pError;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdashtrailingname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdashtrailingname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    numberofspaces = pints[1];
    
    pError = dg_scanfornotbytereverse(
        (void*)(pints[0]),
        &numberofspaces,
        (UINT64)' ');
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanfornotbytereversename);
        dg_pusherror(pBHarrayhead, dg_forthdashtrailingname);
        return;
    }
    
    if (numberofspaces == (UINT64)-1)  // this means all were spaces
    {
        pints[1] = 0;
    }
    else
    {
        pints[1] -= numberofspaces;
    }
    
    
}

void dg_forthslashstring (Bufferhandle* pBHarrayhead)
//     ( caddr1 u1 n1 -- caddr2 u2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    INT64 n;
    UINT64 u;

    unsigned char* caddrout;
    
    const char* pError;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthslashstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthslashstringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    
    n = (INT64)(pints[2]);
    
    if (n > 0)
    {
        if (n > pints[1])
        {
            n = (INT64)(pints[1]);
        }
        
        u = (UINT64)n;
        
        pints[0] += u;        
        pints[1] -= u;
    }
    else
    {
        n = 0 - n;
        u = (UINT64)n;
        
        pints[0] -= u;
        pints[1] += u;
    }
    
    *pbuflength -= sizeof(UINT64);
}

void dg_forthsearch (Bufferhandle* pBHarrayhead)
//     ( caddr1 u1 caddr2 u2 -- caddr3 u3 flag )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

    unsigned char* caddrout;
    
    const char* pError;

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthsearchname);
		return;
	}

	if (*pbuflength < (4 * sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthsearchname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    // would it be better to just pass a pointer to the data stack?
    pError = dg_search(
        (unsigned char*)(pints[0]), 
        pints[1], 
        (unsigned char*)(pints[2]), 
        pints[3], 
        (unsigned char**)(&caddrout));
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_searchname);
        dg_pusherror(pBHarrayhead, dg_forthsearchname);
        return;
    }
         
	if (caddrout != NULL)
	{
		pints[1] = pints[1]  - (UINT64)(caddrout - pints[0]);
		pints[0] = (UINT64)caddrout;
		pints[2] = FORTH_TRUE;
	}
	else
	{
		pints[2] = FORTH_FALSE;
	}


	*pbuflength -= sizeof(UINT64);
}


void dg_forthcompiles (Bufferhandle* pBHarrayhead)
//            ( addr u -- )
//            ( compiles copy of string at addr u and code that does: ( -- addr' u ) 
{
	UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;
	
	UINT64* pints = NULL;
	
	UINT64 sqstrlen = 0;
	unsigned char* pstring = NULL;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
	
	
	// get source addr and length from data stack
	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);
	
	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}
	
	if (*pbuflength < (2 * sizeof(UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}
	
	// could check for misaligned data stack here
	
	pints = (UINT64*)(pdatastack + *pbuflength - 2* sizeof(UINT64));
	
	sqstrlen = pints[1];
	pstring = (unsigned char*)pints[0];
	
	*pbuflength -= (2 * sizeof(UINT64));
	
    // compile string and code to push addr and length of copy to data stack
	
	// getting the address of the string by using a call calculates the address at run time and allows for the case
	//  where the buffer containing the string moves. You just need to use the pointer to the string before the buffer moves again.
	dg_compilecalloffset (pBHarrayhead, sqstrlen);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}	
	
	dg_compilesegment (
        pBHarrayhead,
        (const char*)pstring,
        sqstrlen);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}	
	
	// address of string is now on return stack	
	dg_compilepushdatastack(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}
	
	dg_compilepushntoret(
        pBHarrayhead,
        sqstrlen);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}
	
	dg_compilepushdatastack(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcompilesname);
		return;
	}
}


void dg_forthblank (Bufferhandle* pBHarrayhead)
//            ( addr u -- ) 
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;
    
    const char* perror;
    
    UINT64* pints = NULL;
    
    UINT64 sqstrlen = 0;
    unsigned char* pstring = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    
    // get source addr and length from data stack
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);
    
    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthblankname);
        return;
    }
    
    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthblankname);
        return;
    }
    
    // could check for misaligned data stack here
    
    pints = (UINT64*)(pdatastack + *pbuflength - (2* sizeof(UINT64)));
    
    sqstrlen = pints[1];
    pstring = (unsigned char*)pints[0];
    
    *pbuflength -= (2 * sizeof(UINT64));
    
    perror = dg_fillwithbyte (
            pstring,
            sqstrlen,
            ' ');
            
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_forthblankname);
        return;
    }
}

void dg_forthcompare (Bufferhandle* pBHarrayhead)
//     ( caddr1 u1 caddr2 u2 -- cflag )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    INT64 flag;
    
    const char* pError;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcomparename);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcomparename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));
    
    pError = dg_comparebytes (
        (unsigned char*)(pints[0]), 
        pints[1], 
        (unsigned char*)(pints[2]), 
        pints[3], 
        &flag);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_forthcomparename);
        return;
    }
         
    pints[0] = flag;


    *pbuflength -= (3 * sizeof(UINT64));
}
