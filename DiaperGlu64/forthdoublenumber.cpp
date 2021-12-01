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


void dg_forthtwoconstant (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( nlo nhi -- )
{
	UINT64 nlo;
    UINT64 nhi;

    unsigned char* pname;
	UINT64 namelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	nhi = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthtwoconstantname);
		return;
	}
    
    nlo = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthtwoconstantname);
		return;
	}

	pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwoconstantname);
        return;
    }

	if (namelength == 0)
	{
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
		dg_pusherror(pBHarrayhead, dg_forthtwoconstantname);
		return;
	}

	dg_createdconstantdef(
        pBHarrayhead,
        nlo,
        nhi,
        pname,
        namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtwoconstantname);
		return;
	}
}


void dg_forthtwoliteral (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthswap(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwoliteralname);
        return;
    }
    
    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwoliteralname);
        return;
    }
    
    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwoliteralname);
        return;
    }
}


void dg_forthtwovariable (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -currentnewvariablebuffer- +2*sizeofunsignedint )
{
	const char* pError;

	UINT64 dsbufid;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_forthcreate(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtwovariablename);
		return;
	}

	dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
		dg_pusherror(pBHarrayhead, dg_forthtwovariablename);
		return;
	}

	dg_growbuffer(
        pBHarrayhead,
        dsbufid,
        2 * sizeof(UINT64),
        &pError,
        FORTH_FALSE);

	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
		dg_pusherror(pBHarrayhead, dg_forthtwovariablename);
		return;
	}
}


void dg_forthdlessthan (Bufferhandle* pBHarrayhead)        
//          ( nd1 nd2 -- flag )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdlessthanname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdlessthanname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_dlessthan(pints);

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthdequals (Bufferhandle* pBHarrayhead)        
//          ( xd1 xd2 -- flag )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;
    
	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthdequalsname);
		return;
	}

	if (*pbuflength < (4 * sizeof(UINT64)))
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthdequalsname);
		return;
	}

	// could check for misaligned data stack

	pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

	// if (pints[0] == pints[1]) doing it this way requires 128 bit alignment
    if ( (pints[0] == pints[2])   && 
         (pints[1]) == (pints[3]) )   
	{
		*((UINT64*)pints) = FORTH_TRUE;
	}
	else
	{
		*((UINT64*)pints) = FORTH_FALSE;
	}

	*pbuflength = *pbuflength - (3 * sizeof(UINT64));
}

void dg_forthdtos (Bufferhandle* pBHarrayhead)        
//          ( nd1 -- n )
{
    
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    INT64 negmax = (INT64)0x8000000000000000; // doing it this way because compiler
                                        // has trouble with -0x8000000000000000
                                        //  (it's doing an unsigned 63 bit conversion)

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdtosname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdtosname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    

    if (((INT64)pints[1]) >= 0)
    {
        if ((((INT64)pints[1]) > 0) ||
            (pints[0] > largestsignedint))
        {
            pints[0] = largestsignedint;
        }
    }
    else
    {
        if ((((INT64)pints[1]) < -1) ||
            (pints[0] < negmax))
        {
            pints[0] = negmax;
        }
    }

    *pbuflength = *pbuflength - (1 * sizeof(UINT64));
    
}

void dg_forthdplus (Bufferhandle* pBHarrayhead)        
//          ( xd1 xd2 -- xd1+xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdplusname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdplusname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));
    
    dg_dplus(pints);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthdminus (Bufferhandle* pBHarrayhead)        
//          ( xd1 xd2 -- xd1-xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdminusname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdminusname);
        return;
    }

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    // could check for misaligned data stack

    dg_dminus(pints);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}

void dg_forthdzeroless (Bufferhandle* pBHarrayhead)        
//          ( nd1 -- flag )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;
    
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdzerolessname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdzerolessname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    if (pints[1] < 0) // really just need to look at the sign bit
    {
        *(pints) = FORTH_TRUE;
    }
    else
    {
        *(pints) = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (1 * sizeof(UINT64));
}

void dg_forthdzeroequals (Bufferhandle* pBHarrayhead)        
//          ( nd1 -- flag )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdzeroequalsname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdzeroequalsname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    if ((pints[0] == 0) &&(pints[1] == 0))
    {
        *(pints) = FORTH_TRUE;
    }
    else
    {
        *(pints) = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (1 * sizeof(UINT64));
}

void dg_forthdtwostar (Bufferhandle* pBHarrayhead)        
//          ( xd1 -- xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdtwostarname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdtwostarname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    dg_shld(pints, 1);
}


void dg_forthdtwoslash (Bufferhandle* pBHarrayhead)        
//          ( xd1 -- xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdtwoslashname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdtwoslashname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_ashrd((INT64*)pints, 1);
}

void dg_forthdabs (Bufferhandle* pBHarrayhead)        
//          ( xd1 -- xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdabsname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdabsname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_dabs(pints);
}

void dg_forthdmin (Bufferhandle* pBHarrayhead)        
//          ( nd1 nd2 -- nd1|nd2 )
{
    
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdminname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdminname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));
    
    dg_dmin(pints);
    
    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthdmax (Bufferhandle* pBHarrayhead)        
//          ( nd1 nd2 -- nd1|nd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdmaxname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdmaxname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_dmax(pints);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}

void dg_forthdnegate (Bufferhandle* pBHarrayhead)        
//          ( xd1 -- xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdnegatename);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdnegatename);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    dg_dnegate(pints);
}


void dg_forthdulessthan (Bufferhandle* pBHarrayhead)        
//          ( nd1 nd2 -- flag )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdulessthanname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdulessthanname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    // doing it this way to avoid 128 bit alignment check problem
    
    dg_dulessthan(pints);

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthddot (Bufferhandle* pBHarrayhead)
//     ( nd -- )
{
    UINT64 olderrorcount = 0;

    olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthlessthannumbersign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthdup(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }
    
    dg_forthtor(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthdabs(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthnumbersigns(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthrfrom(pBHarrayhead); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthsign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthnumbersigngreater(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthtype(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthspace(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }
}

void dg_forthmplus (Bufferhandle* pBHarrayhead)        
//          ( xd1 n -- xd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthmplusname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthmplusname);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    
    dg_mplus(pints);
    
    *pbuflength = *pbuflength - (1 * sizeof(UINT64));
}


void dg_forthddotr (Bufferhandle* pBHarrayhead)
//     ( nd1 n2 -- )
{
    INT64 n2, i;
    INT64 stringlength;
    unsigned char c = ' '; // could use a string of spaces to make this faster
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n2 = (INT64)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthlessthannumbersign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthdup(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }
    
    dg_forthtor(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotname);
        return;
    }

    dg_forthdabs(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthnumbersigns(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthrfrom(pBHarrayhead); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthsign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }

    dg_forthnumbersigngreater(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }
    
    // need top number from data stack....
    stringlength = (INT64)dg_getuint64stackelement (
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0);
        
    if (n2 > stringlength)
    {
        for (i = 0; i < (n2 - stringlength); i++)
        {
            dg_writestdout(
                pBHarrayhead,
                &c,
                1);
        }
    }
    
    dg_forthtype(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthddotrname);
        return;
    }
}

void dg_forthtworot (Bufferhandle* pBHarrayhead)           
//       ( nd1 nd2 nd3 -- nd2 nd3 nd1 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 datalo = 0;
    UINT64 datahi = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtworotname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtworotname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    // doing it this way to avoid 128 bit alignment check problem
    datalo = pints[0];
    datahi = pints[1];
    pints[0] = pints[2];
    pints[1] = pints[3];
    pints[2] = pints[4];
    pints[3] = pints[5];
    pints[4] = datalo;
    pints[5] = datahi;
}

void dg_forthmstarslash (Bufferhandle* pBHarrayhead)        
//          ( nd1 n1 n2 -- nd2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthmstarslashname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthmstarslashname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));
    
    dg_mstarslash(pints, pints[2], pints[3]);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}



