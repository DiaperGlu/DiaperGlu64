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


void dg_forthcomparestring ( Bufferhandle* pBHarrayhead )
//     ( $1 $2 -$- $1 $2 )
//     ( -- flag )
{
	UINT64 string1length = 0;
	UINT64 string2length = 0;
	UINT64 string2id = 0;
	unsigned char* pstring1 = NULL;
	unsigned char* pstring2 = NULL;
	UINT64 minlength = 0;
	INT64 flag = 0;

	const char* perror;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	string2id = dg_getnumberoflstringsonstack(pBHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		return;
	}

	if (string2id < 2)
	{
		// not enough strings to do compare, will push error and push not equal
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		return;
	}

	pstring1 = dg_getplstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		string2id - 2,
		&string1length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		return;
	}

	pstring2 = dg_getplstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		string2id - 1,
		&string2length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		return;
	}

	if (string1length > string2length)
	{
		minlength = string2length;
	}
	else
	{
		minlength = string1length;
	}

	perror = dg_comparebytes(
		pstring1,
		string1length,
		pstring2,
		string2length,
		&flag);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_comparebytesname);
		dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		//return;
	}
	
	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, flag);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcomparestringname);
		return;
	}
}


void dg_forthgetmidstring ( Bufferhandle* pBHarrayhead )
//             ( $1 -$- $1 $2 )
//             ( offset length -- )
{
	UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;

	UINT64* pints = NULL;

	UINT64 string1length = 0;
	UINT64 string1startoffset = 0;

	UINT64 offset = 0;
	UINT64 length = 0;

	UINT64 string2id = 0;

	UINT64 i = 0;

	const char* pError;

	unsigned char* psb = NULL;
	UINT64* psblength = NULL;


	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	if (*pbuflength < (2 * sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

	offset = pints[0];
	length = pints[1];

	// it would be faster to just get the pointer to the offset buffer

	string2id = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	if (string2id < 1)
	{
		// not enough strings to do compare, will push error and push not equal
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	// ok we need to get the start offset of the last string
	//  and the length of the last string
	string1startoffset = dg_getlstringstartoffset(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        string2id - 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	string1length = dg_getlstringlength(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        string2id - 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}


	// then we check parameters to see if they are ok
	//  doing it in steps to avoid chance of addition overflow
	if (length > string1length)
	{
		dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	if (offset > string1length - length)
	{
		dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}
	
	// then we do a dg_pushlstring by hand because the string buffer might move
	// since the source string is in the same buffer and the buffer might move when we grow it, dg_pushlstring won't work
	// grow string buffer
	dg_growbuffer(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID,
        length,
        &pError,
        false);

	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	// push new end offset
	dg_pushbufferuint64(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        string1startoffset + string1length + length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	// get pointer string stack's string buffer AFTER the grow
	psb = dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID,
        &psblength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetmidstringname);
		return;
	}

	// blockmove
	for (i = 0; i < length; i++)
	{
		psb[string1startoffset + string1length + i] = psb[string1startoffset + offset + i];
	}


	*pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthcatstring ( Bufferhandle* pBHarrayhead )
//                  ( $1 $2 -$- $1+$2 )
{
	UINT64* poffsetlength = NULL;
	unsigned char* poffsetstack = NULL;

	UINT64* pints = NULL;

	poffsetstack = dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetlength);

	if (poffsetstack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcatstringname);
		return;
	}

	if (*poffsetlength < (2 * sizeof(UINT64)))
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthcatstringname);
		return;
	}

	// could check for misaligned offset stack here

	pints = (UINT64*)(poffsetstack + *poffsetlength - (2 * sizeof(UINT64)));
	
	pints[0] = pints[1];

	*poffsetlength -= sizeof(UINT64);
}


void dg_forthlengthstring ( Bufferhandle* pBHarrayhead )
//                ( $1 -$- $1 )
//                ( -- length )
{
	UINT64 length;

	UINT64 numberofstringsonstack;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numberofstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthlengthstringname);
		return;
	}

	if (numberofstringsonstack < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthlengthstringname);
		return;
	}

	length = dg_getlstringlength(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        numberofstringsonstack - 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthlengthstringname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthlengthstringname);
		return;
	}
}


void dg_forthshortenstring ( Bufferhandle* pBHarrayhead )
//                 ( $1 -$- $1' )
//                 ( n -- )            
{
	UINT64* poffsetlength = NULL;
	UINT64* poffsetstack = NULL;

	UINT64 n = 0;
	UINT64 depth = 0;
	UINT64 slength = 0;

	UINT64 startoffset = 0;

	const char* pError = NULL;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthshortenstringname);
		return;
	}

	poffsetstack = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetlength);

	if (poffsetstack == (UINT64*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthshortenstringname);
		return;
	}

	depth = *poffsetlength / sizeof (UINT64);

	if (depth < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthshortenstringname);
		return;
	}

	// could check for misaligned offset stack here

	if (depth >= 2)
	{
		startoffset = poffsetstack[depth-2];
	}

	if (poffsetstack[depth-1] < startoffset)
	{
        dg_pusherror(pBHarrayhead, dg_lstringstackdepthcorrupt);
		dg_pusherror(pBHarrayhead, dg_forthshortenstringname);
		return;
	}

	slength = poffsetstack[depth-1] - startoffset;

	if (n > slength)
	{
		n = slength;
	}

	poffsetstack[depth-1] -= n;

	dg_shrinkbuffer(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID,
        n,
        &pError);

	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
		dg_pusherror(pBHarrayhead, dg_forthshortenstringname);
	}
}


void dg_forthpickstring (Bufferhandle* pBHarrayhead)
//              ( $x .. $3 $2 $1 $0 -$- $x ... $3 $2 $1 $0 $[nidx] )
//              ( idx -- )
{
	UINT64 x;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	x = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthpickstringname);
		return;
	}

	dg_picklstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        x);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthpickstringname);
		return;
	}
}


void dg_forthdupstring ( Bufferhandle* pBHarrayhead )
//             ( $1 -$- $1 $1 )
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthdupstringname);
		return;
	}

	dg_forthpickstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdupstringname);
		return;
	}
}


void dg_forthoverstring (Bufferhandle* pBHarrayhead)
//              ( $1 $0 -$- $1 $0 $1 )
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthoverstringname);
		return;
	}

	dg_forthpickstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthoverstringname);
		return;
	}
}


void dg_forthdropstring (Bufferhandle* pBHarrayhead)
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_droplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdropstringname);
		return;
	}
}


void dg_forthdeletestring (Bufferhandle* pBHarrayhead)
//                ( ... $n+1 $n $n-1... $1 $0 -$- $n+1 $n-1 ... $1 $0 )
//                ( n -- )
{
	UINT64 stringid;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	stringid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthdeletestringname);
		return;
	}

	dg_deletelstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		stringid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeletestringname);
		return;
	}
}


void dg_forthswapstring (Bufferhandle* pBHarrayhead)
//              ( $1 $0 -$- $0 $1 )
{
	UINT64 numstrings;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthswapstringname);
		return;
	}

	if (numstrings < 2)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthswapstringname);
		return;
	}

	dg_forthoverstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthswapstringname);
		return;
	}

	numstrings++;

	dg_deletelstring(pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numstrings - 3);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthswapstringname);
		return;
	}
}


void dg_forthnipstring (Bufferhandle* pBHarrayhead)
//              ( $1 $0 -$- $0 )
{
	UINT64 numstrings;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnipstringname);
		return;
	}

	if (numstrings < 2)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthnipstringname);
		return;
	}

	dg_deletelstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numstrings - 2);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnipstringname);
		return;
	}
}


void dg_forthrotstring (Bufferhandle* pBHarrayhead)
//             ( $2 $1 $0 -$- $0 $1 $2 )
{
	UINT64 numstrings;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrotstringname);
		return;
	}

	if (numstrings < 3)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthrotstringname);
		return;
	}

	dg_picklstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrotstringname);
		return;
	}

	numstrings++;

	dg_deletelstring(pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numstrings - 4);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrotstringname);
		return;
	}
}


void dg_forthdepthstring (Bufferhandle* pBHarrayhead)
//     ( -- n )
//     ( $1 $2 $3 ... $n -$- $1 $2 $3 ... $n )
{
	UINT64 depth;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	depth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdepthstringname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        depth);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthdepthstringname);
		return;
	}
}


void dg_forthnewstring (Bufferhandle* pBHarrayhead)
//             ( -$- empty$ )
{
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushlstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		0,
		(unsigned char*)"");

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnewstringname);
		return;
	}
}


void dg_forthctonewstring (Bufferhandle* pBHarrayhead)      // ( -$- $1 )      ( char -- )
{
	unsigned char c = ' ';

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	c = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthctonewstringname);
		return;
	}

	dg_pushlstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		1,
		&c);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthctonewstringname);
		return;
	}
}


void dg_forthtonewstring (Bufferhandle* pBHarrayhead)      
//     ( -$- $u )      
//     ( u -- )
{
	UINT64 u;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	u = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthtonewstringname);
		return;
	}

	dg_pushlstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		sizeof(UINT64),
		(unsigned char*)(&u));

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtonewstringname);
		return;
	}
}


void dg_forthturnstringinto0string (Bufferhandle* pBHarrayhead)
//                         ( $1 -$- 0$1 )
{
	unsigned char terminator = '\0';

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushlstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		1,
		&terminator);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthturnstringinto0stringname);
		return;
	}

	dg_forthcatstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthturnstringinto0stringname);
		return;
	}
}


void dg_forthinsertinstring (Bufferhandle* pBHarrayhead)
//                  ( offset length -- )
//                  ( $1 -$- $' )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

	UINT64 offset;
	UINT64 length;
	UINT64 startoffset;

	UINT64 newstringbufferlength;

	UINT64 numstrings;


	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	if (*pbuflength < (2 * sizeof(UINT64)) )
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

	length = pints[1];
	offset = pints[0];

	numstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_getnumberoflstringsonstackname);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}
	
	if (numstrings < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

    /*
    // could do this instead
    dg_insertinlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        numstrings-1,
        offset,
        length);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}
    */

	// do dg_insertinbuffer on stringbuffer - need to calculate buffer offset from offset passed in
	startoffset = dg_getlstringstartoffset(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        numstrings - 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	dg_insertinbuffer(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID,
        startoffset + offset,
        length);
	// offset > oldlength error checked by dg_insertinbuffer

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	// then get the new string buffer buffer length and update the end of string offset for the top string
	newstringbufferlength = dg_getbufferlength(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	dg_putbufferuint64(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		(numstrings - 1) * sizeof(UINT64), 
		newstringbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringname);
		return;
	}

	*pbuflength -= 2 * sizeof(UINT64);
}


void dg_forthdeleteinstring (Bufferhandle* pBHarrayhead)
//                  ( offset length -- )
//                  ( $1 -$- $1' )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

	UINT64 offset;
	UINT64 length;

	UINT64 numstrings;
	UINT64 i;

	unsigned char* plstring;
	UINT64 lstringlength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	if (*pbuflength < (2 * sizeof(UINT64)) )
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

	offset = pints[0];
	length = pints[1];
	

	numstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	if (numstrings < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

    /*
    // could do this instead
    dg_deleteinlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        numstrings-1,
        offset,
        length);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}
    */

	plstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numstrings - 1,
		&lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	if (length > lstringlength) // checking length here to avoid addition overflow
	{
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	if (offset > lstringlength - length) 
	{
		dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}

	if (length == 0) // nothing to do :-)
	{
		return;
	}

	// blockmove
	for (i = offset; i < lstringlength - length; i++)
	{
		plstring[i] = plstring[i + length];
	}

	// shrink
	pints[0] = length;

	*pbuflength -= sizeof(UINT64);

	dg_forthshortenstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringname);
		return;
	}
}


void dg_forthstringcfetch (Bufferhandle* pBHarrayhead) 
//                     ( $1 -$- $1 )   
//                     ( position -- char )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

	UINT64 string1length;

	UINT64 string2id;

	unsigned char* pstring1;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	if (*pbuflength < sizeof(UINT64))
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

	string2id = dg_getnumberoflstringsonstack(pBHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	if (string2id < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	pstring1 = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		string2id - 1,
		&string1length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	if ( pints[0] >= string1length )
	{
        dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror);
		dg_pusherror(pBHarrayhead, dg_forthstringcfetchname);
		return;
	}

	pints[0] = (UINT64)pstring1[(pints[0])];
}


void dg_forthstringcstore (Bufferhandle* pBHarrayhead)   
//                   ( $1 -$- $1' )  
//                   ( char position -- )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

	UINT64 string1length;

	UINT64 string2id;

	unsigned char* pstring1;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	if (*pbuflength < (2 * sizeof(UINT64)))
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

	string2id = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	if (string2id < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	pstring1 = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		string2id - 1,
		&string1length);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	if (pints[1] >= string1length)
	{
        dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror);
		dg_pusherror(pBHarrayhead, dg_forthstringcstorename);
		return;
	}

	pstring1[(pints[1])] = pints[0];

	*pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthstringtoc (Bufferhandle* pBHarrayhead)
//                     ( $1 -$- $1' )
//                     ( -- char )
{
	UINT64* poffsetlength;
	UINT64* poffsetstack;

	UINT64 c;
	UINT64 depth;
	UINT64 slength;

	UINT64 startoffset = 0; // setting to 0 needed here

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	poffsetstack = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetlength);

	if (poffsetstack == (UINT64*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}

	depth = *poffsetlength / sizeof (UINT64);

	if (depth < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}

	// could check for misaligned offset stack here

	if (depth >= 2)
	{
		startoffset = poffsetstack[depth-2];
	}

	if (poffsetstack[depth-1] < startoffset)
	{
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorruptname);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}

	slength = poffsetstack[depth-1] - startoffset;

	if (slength < 1)
	{
		// change this to dg_stringemptyerror
        dg_pusherror(pBHarrayhead, dg_lstringemptyerror);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}

	c = (UINT64)dg_popbufferbyte(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}

	poffsetstack[depth-1] -= 1;

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        c);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtocname);
		return;
	}
}


void dg_forthstringto (Bufferhandle* pBHarrayhead)
//     ( $1 -$- $1' )
//     ( -- u )
{
	UINT64* poffsetlength;
	UINT64* poffsetstack;

	UINT64 u;
	UINT64 depth;
	UINT64 slength;

	UINT64 startoffset = 0; // setting to 0 needed here

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	poffsetstack = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetlength);

	if (poffsetstack == (UINT64*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}

	depth = *poffsetlength / sizeof (UINT64);

	if (depth < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}

	// could check for misaligned offset stack here

	if (depth >= 2)
	{
		startoffset = poffsetstack[depth-2];
	}

	if (poffsetstack[depth-1] < startoffset)
	{
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorruptname);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}

	slength = poffsetstack[depth-1] - startoffset;

	if (slength < sizeof(UINT64))
	{
        dg_pusherror(pBHarrayhead, dg_stringunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}

	u = dg_popbufferuint64(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}

	poffsetstack[depth-1] -= sizeof(UINT64);

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        u);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstringtoname);
		return;
	}
}


void dg_forthctostring (Bufferhandle* pBHarrayhead)
//                    ( $1 -$- $1' )
//                    ( char -$- )
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_forthctonewstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthctostringname);
		return;
	}

	dg_forthcatstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthctostringname);
		return;
	}
}


void dg_forthtostring (Bufferhandle* pBHarrayhead)
//                    ( $1 -$- $1' )
//                    ( char -$- )
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_forthtonewstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtostringname);
		return;
	}

	dg_forthcatstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtostringname);
		return;
	}
}


void dg_forthstringquotes (Bufferhandle* pBHarrayhead )
//          ( "<space>stuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
//          ( -$- "stuff" )
{
	
    unsigned char* psqstr;
	UINT64 sqstrlen;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	psqstr = dg_parse(
        pBHarrayhead,
        &sqstrlen,
        '"');
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringquotesname);
        return;
    }

	dg_pushlstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
		sqstrlen,
		psqstr);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstringquotesname);
		return;
	}
}


void dg_forthholdstring (Bufferhandle* pBHarrayhead) // ( $1 -$- $1' ) ( char -- )
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthholdstringname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthholdstringname);
		return;
	}

	dg_forthinsertinstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthholdstringname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0);

	// can't really get this one
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthholdstringname);
		return;
	}

	dg_forthstringcstore(pBHarrayhead);

	// can't really get this one
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthholdstringname);
		return;
	}
}


void dg_forthnumbersignstring (Bufferhandle* pBHarrayhead)   // ( $1 -$- $1' ) ( ud -- ud' )
{
	UINT64 remainder;

	UINT64 base;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthbasename);
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	if (base < 2)
	{
        dg_pusherror(pBHarrayhead, dg_basetoolowerror);
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        base);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	dg_forthudmslashmod(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	remainder = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	// converting remainder to an ascii character
	if (remainder < 10)
	{
		remainder = remainder + 0x30;
	}
	else
	{
		remainder = remainder + 0x37;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        remainder);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
		return;
	}

	dg_forthholdstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnumbersignstringname);
	}
}


void dg_forthnumbersignsstring (Bufferhandle* pBHarrayhead)
//                            ( $1 -$- $1' ) 
//                            ( ud -- 0 0)
{
	unsigned char* pdatastack;
	UINT64* pdatastacklength;

	UINT64 flag = FORTH_TRUE; // init to FORTH_TRUE needed here

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	while(flag == FORTH_TRUE)
	{
		dg_forthnumbersignstring(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthnumbersignsstringname);
			return;
		}

		// Data stack is of fixed size by default and can't move, so we don't need to get a pointer to the data stack
        //   buffer every time. However we still need to keep track of the length... Could speed this up by not getting
        //   pointer every time.
		pdatastack = dg_getpbuffer(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            &pdatastacklength);

		if (pdatastack == (unsigned char*)badbufferhandle)
		{
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
			dg_pusherror(pBHarrayhead, dg_forthnumbersignsstringname);
			return;
		}

		if (*pdatastacklength < sizeof(UINT64))
		{
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
			dg_pusherror(pBHarrayhead, dg_forthnumbersignsstringname);
			return;
		}

		if ( (*((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) |
			 *((UINT64*)(pdatastack + *pdatastacklength - (2 * (sizeof(UINT64))))) )
			== 0 )
		{
			flag = FORTH_FALSE;
		}
	}	
}


void dg_forthsignstring (Bufferhandle* pBHarrayhead)    // ( $1 -$- $1' ) ( n -- )
{
	INT64 n;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	n = (INT64)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthsignstringname);
		return;
	}

	if (n < 0)
	{
		dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)'-');

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
			dg_pusherror(pBHarrayhead, dg_forthsignstringname);
			return;
		}

		dg_forthholdstring(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthsignstringname);
			return;
		}
	}
}


void dg_forthsplitstring (Bufferhandle* pBHarrayhead)
//               ( $1 -$- $2 $3 )
//               ( n -- )
{	
	UINT64 n;

	UINT64* poffsets;
	UINT64* poffsetslength;

	UINT64 depth;
	UINT64 startoffset = 0; // initialization needed
	UINT64 endoffset;
	UINT64 slength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
		return;
	}

	poffsets = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetslength);

	if (poffsets == (UINT64*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
		return;
	}

	depth = *poffsetslength / sizeof (UINT64);

	if (depth < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
		return;
	}

	// could check for misaligned offset stack here

	if (depth >= 2)
	{
		startoffset = poffsets[depth-2];
	}

	if (poffsets[depth-1] < startoffset)
	{
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
		dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
		return;
	}

	endoffset = poffsets[depth-1];

	slength = endoffset - startoffset;

	if (n > slength)
	{
        // not sure why I did this... but it is convenient
		n = slength;
        //dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror);
		//dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
		//return;
	}

	//poffsets[depth-1] = endoffset - n;
	poffsets[depth-1] = startoffset + n;

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        endoffset);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		poffsets = (UINT64*)dg_getpbuffer(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            &poffsetslength);
		
		if (poffsets != NULL)
		{
			poffsets[depth-1] = endoffset; // restoring old end offset
		}

        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthsplitstringname);
	}
}

 
void dg_forthputmidstring (Bufferhandle* pBHarrayhead)
//     ( destinationoffset -- )
//     ( destination$ source$ -$- destination$' )
{
	UINT64 n;

	UINT64* poffsets;
	UINT64* poffsetslength;

	UINT64 depth;
	UINT64 startoffset = 0; // initialization needed
	UINT64 endoffset1;
	UINT64 endoffset2;
	UINT64 slength1;
	UINT64 slength2;

	unsigned char* pstringbuf;
	UINT64* pstringbuflength;

	UINT64 i;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


	// popn
	n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}


	// get pointer to offset buffer
	poffsets = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        &poffsetslength);

	if (poffsets == (UINT64*)badbufferhandle)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackoffsetbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}


	// check for ssunderflow
	depth = *poffsetslength / sizeof (UINT64);

	if (depth < 2)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// get offsets
	if (depth > 2)
	{
		startoffset = poffsets[depth - 3];
	}

	endoffset1 = poffsets[depth - 2];
	endoffset2 = poffsets[depth - 1];

	// check for corrupt
	if (startoffset > endoffset1)
	{
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	if (endoffset1 > endoffset2)
	{
		dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt); // could have separate error or the number 2
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// get lengths
	slength1 = endoffset1 - startoffset;
	slength2 = endoffset2 - endoffset1;
	
	// check n with lengths
	if (n > slength1)
	{
        dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror); // could have separate error or the number 2
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// in steps to avoid addition overflow
	if (slength2 > slength1 - n)
	{
		dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror);
        dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// get pointer to string buffer
	pstringbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_STRINGSTRINGSTACK_BUFFERID,
        &pstringbuflength);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthstringstackstringbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// check length of string buf
	if (*pstringbuflength != endoffset2)
	{
        dg_pusherror(pBHarrayhead, dg_lstringtopoffsetwasbad);
		dg_pusherror(pBHarrayhead, dg_forthputmidstringname);
		return;
	}

	// blockmove
	for (i=0; i < slength2; i++)
	{
		pstringbuf[startoffset + n + i] = pstringbuf[endoffset1 + i];
	}

	// drop last string
	*poffsetslength -= sizeof(UINT64);
	*pstringbuflength -= slength2;
}


void dg_forthstostring (Bufferhandle* pBHarrayhead)
//     ( addr length -- )
//     ( -- $1 )

{
	unsigned char* address;
	UINT64 length;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthstostringname);
		return;
	}

	if (*plength < (2 * sizeof (UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthstostringname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64)));

	address = (unsigned char*)pints[0];
	length = pints[1];

	dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        length,
        address);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstostringname);
		return;
	}

	(*plength) -= (2*sizeof(UINT64));
}


void dg_forthgetsstringnd (Bufferhandle* pBHarrayhead)
//               ( $n $n-1 ... $1 $0 -$- $n $n-1 ... $1 $0 )
//               ( n -- pstringn dg_forthlengthstringn )
{
	UINT64 n;

	UINT64 depth = 0;

	unsigned char* pstring = NULL;
	UINT64 stringlength = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}

	depth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}

	if (n >= depth)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}

	pstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		depth - (n+1), 
		&stringlength);

	if (pstring == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);

	// can't really get this error
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthgetsstringndname);
		return;
	}
}


void dg_forthprintstring(Bufferhandle* pBHarrayhead)
//              ( $1 -$- )
{
	UINT64 numberofstrings;

	unsigned char* plstring;
	UINT64 lstringlength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numberofstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthprintstringname);
		return;
	}

	if (numberofstrings < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthprintstringname);
		return;
	}

	plstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		numberofstrings - 1, 
		&lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthprintstringname);
		return;
	}

	dg_writestdout(
        pBHarrayhead,
        plstring,
        lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthprintstringname);
		return;
	}

	dg_forthdropstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthprintstringname);
		return;
	}
}


void dg_forthloadfilestring (Bufferhandle* pBHarrayhead)
//              ( filename$ -$- )
//              ( -- bufferid )
{
	const char* pError = NULL;
	UINT64 fileid;
	UINT64 filelength = 0;
	UINT64 bufid = 0;
	unsigned char* pbufsegment = NULL;

	const char* flag = dg_success;
	UINT64 numberofstringsonstack;
	unsigned char* pnamelstring;
	UINT64 namelength;
    UINT64 numread;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// shouldn't this go after depth check?
	dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	numberofstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	if (numberofstringsonstack < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	// isapi doesn't support relative pathing
	// if this is running in isapi mode and filename does not include full path,
	// the path of the script file from extension control block variable 
	//  PATH_TRANSLATED needs to be added

	dg_forthfixpathstring(pBHarrayhead);

	pnamelstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numberofstringsonstack - 1,
		&namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	flag = dg_openfileforread(
        (const char*)pnamelstring,
        &fileid,
        dg_success);

    dg_forthdropstring(pBHarrayhead);

	if (flag != dg_success)
	{
		dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	flag = dg_getfilelength(
        pBHarrayhead,
        fileid, 
        &filelength, 
        dg_success);

	if (flag != dg_success)
	{
		::dg_closefile(fileid, dg_success);
		dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getfilelengthname);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	if (filelength >= largestsignedint) 
	{
		dg_closefile(
            fileid,
            dg_success);
        
        dg_pusherror(pBHarrayhead, dg_filetoobigerror);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	bufid = dg_newbuffer(
        pBHarrayhead,
		filelength + 1, 
		largestsignedint,
		&pError,
		FORTH_FALSE);

	if (pError != dg_success)
	{
		dg_closefile(
            fileid,
            dg_success);
        
        dg_pusherror(pBHarrayhead, pError);
        //dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	dg_growbuffer(
        pBHarrayhead,
        bufid,
        filelength,
        &pError,
        false);

	if (pError != dg_success)
	{
		dg_closefile(
            fileid,
            dg_success);
        
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	pbufsegment = dg_getpbuffersegment(
        pBHarrayhead,
		bufid,
		0,
		filelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_closefile(
            fileid,
            dg_success);
        
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	flag = dg_readfile(
        pBHarrayhead,
        fileid, 
        pbufsegment, 
        filelength, 
        0, 
        &numread, 
        dg_success);

	if (flag != dg_success)
	{
		dg_closefile(
            fileid,
            dg_success);
        
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_readfilename);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

    if (numread != filelength)
    {
        dg_closefile(
            fileid,
            dg_success);
        
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
        dg_pusherror(pBHarrayhead, dg_osdidlessthanavailableerror);
        dg_pusherror(pBHarrayhead, dg_readfilename);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
    }

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_closefile(
            fileid,
            dg_success);
        
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}

	flag = dg_closefile(
        fileid,
        dg_success);

	if (flag != dg_success)
	{
		dg_freebuffer(
            pBHarrayhead,
            bufid);
        
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_closefilename);
		dg_pusherror(pBHarrayhead, dg_forthloadfilestringname);
		return;
	}
}


void dg_forthsavefilestring (Bufferhandle* pBHarrayhead)
//              ( filename$ -$- )
//              ( bufferid -- )
{
	UINT64 fileid;

	UINT64 bufid = 0;

	unsigned char* pbuf = NULL;
	UINT64* pbuflength = NULL;

	const char* flag = NULL;

	UINT64 numberofstringsonstack;
	unsigned char* pnamelstring;
	UINT64 namelength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	bufid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}


	pbuf = dg_getpbuffer(
        pBHarrayhead,
        bufid,
        &pbuflength);

	if (pbuf == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	numberofstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	if (numberofstringsonstack < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	dg_forthfixpathstring(pBHarrayhead);

	pnamelstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numberofstringsonstack - 1,
		&namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	flag = dg_openfileforwritenew(
        (const char*)pnamelstring,
        &fileid,
        dg_success);


	if (flag != dg_success)
	{
		dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_openfileforwritenewname);
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}

	dg_forthdropstring(pBHarrayhead);

	if (flag != dg_success)
	{
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		return;
	}


	flag = dg_writefile(
        pBHarrayhead,
        fileid, 
        pbuf, 
        *pbuflength, 
        dg_success);

	if (flag != dg_success)
	{
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_writefilename);
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
		// not returning here so file will still be closed
	}

	flag = dg_closefile(
        fileid,
        dg_success);

	if (flag != dg_success)
	{
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_closefilename);
		dg_pusherror(pBHarrayhead, dg_forthsavefilestringname);
	}
}


void dg_forthincludefilestring (Bufferhandle* pBHarrayhead)
//     ( filename$ -$- )
{
	UINT64 bufferid = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_forthloadfilestring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthincludefilestringname); // buffer should not have been allocated
		return;
	}

	bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
	// moving bufferid to the return stack in case evaluate buffer corrupts the data stack

	// if dg_forthloadfilestring worked, shouldn't be able to get this error
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthincludefilestringname); // buffer should not have been allocated
		return;
	}

	dg_evaluatebuffer(
        pBHarrayhead,
        bufferid);
	// not checking errors here on purpose

	dg_freebuffer(
        pBHarrayhead,
        bufferid);
	// free buffer doesn't return errors
}


void dg_forthqueryincludefilestring (Bufferhandle* pBHarrayhead)
//                      ( filename$ -$- )
//                      ( flag -- )
{
	UINT64 flag = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	flag = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthqueryincludefilestringname);
		return;
	}

	if (flag != FORTH_FALSE)
	{
		dg_forthincludefilestring(pBHarrayhead);

		// not checking errors here on purpose
		return;

	}
	else
	{
		dg_forthdropstring(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthqueryincludefilestringname);
			return;
		}
	}
}


void dg_forthfreelibrary (Bufferhandle* pBHarrayhead)
//     ( libraryhandle -- )
{
	UINT64 hlibrary;

	const char* errflag;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	hlibrary = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthfreelibraryname);
		return;
	}

	errflag = dg_freelibrary(
        hlibrary,
        dg_success);

	if (errflag != dg_success)
	{
		dg_pusherror(pBHarrayhead, dg_forthfreelibraryname);
	}
}


void dg_forthgetenvstring (Bufferhandle* pBHarrayhead)
//                        ( variablename$ -$- variablevalue$ )
{
	UINT64 depth = 0;

	unsigned char* pnamestring = NULL;
	UINT64 namestringlength = 0;
	unsigned char* pvaluestring = NULL;
	UINT64 valuestringlength = 0;
	const char* flag;
    UINT64 valuestringlength2;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	depth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

	if (0 >= depth)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

    ::dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

	pnamestring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		depth - 1, 
		&namestringlength);

	if (pnamestring == (unsigned char*)badbufferhandle) 
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

	flag = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)pnamestring, 
        (unsigned char*)badbufferhandle, 
        0, 
        &valuestringlength, 
        dg_success);

	if (flag != dg_success)
	{
		dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
        return;
	}

	dg_forthnewstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

	if ((valuestringlength != 0) &&
        (valuestringlength != (UINT64)largestunsignedint))
	{
		dg_growlstring(
            pBHarrayhead, 
            DG_STRINGOFFSETSTACK_BUFFERID, 
            DG_STRINGSTRINGSTACK_BUFFERID, 
            valuestringlength + 1); // + 1 for null terminator

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
			return;
		}

		// pointer name string could have moved from grow so getting it again
         // since it is on same lstring stack as value string
		pnamestring = dg_getplstring(
            pBHarrayhead, 
			DG_STRINGOFFSETSTACK_BUFFERID, 
			DG_STRINGSTRINGSTACK_BUFFERID, 
			depth - 1, 
			&namestringlength);

		if (pnamestring == (unsigned char*)badbufferhandle) 
		{
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
			return;
		}

		pvaluestring = dg_getplstring(
            pBHarrayhead,
			DG_STRINGOFFSETSTACK_BUFFERID, 
			DG_STRINGSTRINGSTACK_BUFFERID, 
			depth, 
			&valuestringlength);

		if (pvaluestring == (unsigned char*)badbufferhandle)
		{
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
			return;
		}

		flag = dg_getenvironmentvariable(
            pBHarrayhead,
            (const char*)pnamestring, 
            pvaluestring, 
            valuestringlength + 1, // + 1 for null terminator 
            &valuestringlength2, 
            dg_success);

		if (flag != dg_success)
		{
			dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
            return;
		}

		// dg_getenvironmentvariable returns a null terminated string, need to drop null
          // this is for compatibility with a win32 requirement
		dg_forthstringtoc(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
			return;
		}

		dg_forthdrop(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
			return;
		}
	}

	dg_forthswapstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}

	dg_forthdropstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgetenvstringname);
		return;
	}
}

void dg_forthgetmethodstring (Bufferhandle* pBHarrayhead)
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        14,
        (unsigned char*)"REQUEST_METHOD");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthgetmethodstringname);
	    return;
	}

    dg_forthgetenvstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthgetmethodstringname);
	    return;
	}
}

void dg_forthgetquerystring (Bufferhandle* pBHarrayhead)
//                          ( -$- query$ )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        12,
        (unsigned char*)"QUERY_STRING");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthgetquerystringname);
	    return;
	}

    dg_forthgetenvstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthgetquerystringname);
	    return;
	}
}

void dg_forthcscanstring (Bufferhandle* pBHarrayhead)
//                    ( index value -- index' )
{
	UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;

	UINT64* pints = NULL;

	UINT64 offset;
	unsigned char* caddr1 = NULL;

	UINT64 u1 = 0;
	UINT64 value = 0;
	UINT64 stringstackdepth;

	const char* flag;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}

	if (*pbuflength < (2 * sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}

	// could check for misaligned data stack here

	pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

	offset = (UINT64)(pints[0]);
	value =  (UINT64)(pints[1]);

	// need to get depth of string stack first
	stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		// not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}

	caddr1 = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&u1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
	}

	if (offset < u1)
	{
		u1 = u1 - offset;
		caddr1 = caddr1 + offset;

		flag = ::dg_scanforbyte(
            (void*)caddr1,
            &u1,
            value);

		if (flag != dg_success)
		{
			dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_scanforbytename);
			dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		}

		if (u1 != (UINT64)largestunsignedint)
		{
			u1 = u1 + offset;
		}
	}
	else
	{
		u1 = (UINT64)largestunsignedint;
	}

	pints[0] = (UINT64)u1;

	*pbuflength -= sizeof(UINT64);
}


void dg_forthminuscscanstring (Bufferhandle* pBHarrayhead)
//        ( index value -- index' )
//        ( a$ -$- a$ )
{
	UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;
	
	UINT64* pints = NULL;
	
	UINT64 offset;
	unsigned char* caddr1 = NULL;
	
	UINT64 u1 = 0;
	UINT64 value = 0;
	UINT64 stringstackdepth;
	UINT64 doneflag;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
	
	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);
	
	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}
	
	if (*pbuflength < (2 * sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}
	
	// could check for misaligned data stack here
	
	pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
	
	offset = (UINT64)(pints[0]);
	value =  (UINT64)(pints[1]);
	
	// need to get depth of string stack first
	stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}
	
	if (stringstackdepth < 1)
	{
		// not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
		return;
	}
	
	caddr1 = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&u1);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcscanstringname);
	}
	
	if (u1 != 0)
	{
		if (offset > (u1 - 1))
		{
			offset = u1 - 1;
		}
		
		doneflag = FORTH_FALSE;
		
		while (FORTH_FALSE == doneflag)
		{
			if (value == caddr1[offset])
			{
				doneflag = FORTH_TRUE;
			}
			else
			{
				if (0 == offset)
				{
					// value was not found
					doneflag = FORTH_TRUE;
					offset = (UINT64)largestunsignedint;
				}
				else
				{
					offset--;
				}
			}
		}
	}
	else
	{
		// empty string case
		offset = (UINT64)largestunsignedint;
	}
	
	pints[0] = offset;
	
	*pbuflength -= sizeof(UINT64);
}


void dg_forthasciitounicodestring (Bufferhandle* pBHarrayhead)
//                                ( -- )
//                                ( ascii$ -$- unicode$ )
{
	UINT64 numberofstrings = 0;

	unsigned char* plstring = NULL;
	UINT64 lstringlength = 0;

	UINT64 i = 0;
	INT64 c = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numberofstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthasciitounicodestringname);
		return;
	}

	if (numberofstrings < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthasciitounicodestringname);
		return;
	}

	lstringlength = dg_getlstringlength(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		numberofstrings - 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthasciitounicodestringname);
		return;
	}

	if (lstringlength == 0)
	{
		return;
	}

	dg_growlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthasciitounicodestringname);
		return;
	}

	plstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		numberofstrings - 1, 
		&lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthasciitounicodestringname);
		return;
	}

	//shuffle time
	for (i = lstringlength/2; i > 0; i--)
	{
		c = plstring[i-1];
		plstring[2*(i-1)] = c;
		plstring[2*(i-1)+1] = 0;
	}
}


void dg_forthunicodetoasciistring (Bufferhandle* pBHarrayhead)
//                                ( -- )
//                                ( unicode$ -$- ascii$ )
{
	UINT64 numberofstrings = 0;

	unsigned char* plstring = NULL;
	UINT64 lstringlength = 0;

	UINT64 i = 0;
	INT64 c = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numberofstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthunicodetoasciistringname);
		return;
	}

	if (numberofstrings < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthunicodetoasciistringname);
		return;
	}

	plstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		numberofstrings - 1, 
		&lstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthunicodetoasciistringname);
		return;
	}

	// what if lstringlength is odd? that means last character is not unicode
	//  should throw away last character
	if ((lstringlength % 2) == 1)
	{
		// need error checking here
		dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            1);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{	
		    dg_pusherror(pBHarrayhead, dg_forthunicodetoasciistringname);
		    return;
		}

		dg_forthshortenstring(pBHarrayhead); 
		// shortening the string doesn't change the pointer so
		//  we don't need to get the pointer to the string again
		lstringlength--;
	}

	if (lstringlength == 0)
	{
		return;
	}

	//shuffle time
	for (i = 0; i<lstringlength; i=i+2)
	{
		c = plstring[i];
		if (plstring[i+1] != 0)
		{
			c = '_';
		}
		plstring[i/2] = c;
	}

	// need error checking here - shouldn't be able to get error here
	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        lstringlength/2);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{	
	    dg_pusherror(pBHarrayhead, dg_forthunicodetoasciistringname);
	    return;
	}

	dg_forthshortenstring(pBHarrayhead);
}


void dg_forthgrowstring (Bufferhandle* pBHarrayhead)
//                ( n -- )
//                ( $1 -$- l$' )
{
	UINT64* pbuflength;
	unsigned char* pdatastack;

	UINT64* pints;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthgrowstringname);
		return;
	}

	if (*pbuflength < sizeof(UINT64))
	{
		dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthgrowstringname);
		return;
	}

	// could check for misaligned data stack pointer here

	pints = (UINT64*)(pdatastack + *pbuflength - 1*sizeof(UINT64));

	dg_growlstring(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
		pints[0]);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthgrowstringname);
		return;
	}

	*pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthrollstring (Bufferhandle* pBHarrayhead)
//     ( nd -- )
//     ( $bottom ... $nd+1 $nd $nd-1 ... $1 $0 -$- $bottom ... $nd+1 $nd-1 ... $1 $0 $nd )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrollstringname);
		return;
	}

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrollstringname);
		return;
	}

    dg_forthrolllstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrollstringname);
		return;
	}
}


void dg_forthminusrollstring (Bufferhandle* pBHarrayhead)
//     ( nd -- )
//     ( $depth-1{bottom} ... $nd+1 l$nd $nd-1 ... $1 $0{top} -l$- 
//                 $depth-1{bottom} ... $nd+1 $0 $nd $nd-1 ... $1 )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthminusrollstringname);
		return;
	}

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthminusrollstringname);
		return;
	}

    dg_forthminusrolllstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthminusrollstringname);
		return;
	}
}


void dg_forthdeleteinstringnd (Bufferhandle* pBHarrayhead)
//     ( offset length nd -- )
//     ( $bottom ... $nd+1 $nd $nd-1 ... $1 $0 -$- $bottom ... $nd+1 $nd' $nd-1 ... $1 $0 )
{
    UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;

	UINT64* pints = NULL;

    UINT64 stringstackdepth; 

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringndname);
		return;
	}

	if (*pbuflength < (3 * sizeof(UINT64)) )
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringndname);
		return;
	}

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeleteinstringndname);
		return;
    }

	// could check for misaligned data stack pointer here

	pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    if (stringstackdepth <= pints[2])
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthdeleteinstringndname);
		return;
    }

    dg_deleteinlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - (pints[2] + 1),
        pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeleteinstringndname);
		return;
    }


    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthinsertinstringnd (Bufferhandle* pBHarrayhead)
//     ( offset length nd -- )
//     ( $bottom ... $nd+1 $nd $nd-1 ... $1 $0 -$- $bottom ... $nd+1 $nd' $nd-1 ... $1 $0 )
{
    UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;

	UINT64* pints = NULL;

    UINT64 stringstackdepth; 

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringndname);
		return;
	}

	if (*pbuflength < (3 * sizeof(UINT64)))
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringndname);
		return;
	}

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertinstringndname);
		return;
    }

	// could check for misaligned data stack pointer here

	pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    if (stringstackdepth <= pints[2])
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthinsertinstringndname);
		return;
    }

    dg_insertinlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - (pints[2] + 1),
        pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertinstringndname);
		return;
    }


    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthcatstringnd (Bufferhandle* pBHarrayhead)
//     ( offset length nd -- )
//     ( $bottom ... $nd+1 $nd $nd-1 ... $1 $0 -$- $bottom ... $nd+1 $nd+nd-1 ... $1 $0 )
{
    UINT64* pbuflength = NULL;
	unsigned char* pdatastack = NULL;

	UINT64* pints = NULL;

    UINT64 stringstackdepth; 

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

	if (pdatastack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthcatstringndname);
		return;
	}

	if (*pbuflength < sizeof(UINT64))
	{
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthcatstringndname);
		return;
	}

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcatstringndname);
		return;
    }

	// could check for misaligned data stack pointer here

	pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    if (stringstackdepth <= pints[0] + 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthcatstringndname);
		return;
    }

    dg_catlstringn(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - (pints[0] + 1));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcatstringndname);
		return;
    }


    *pbuflength = *pbuflength - sizeof(UINT64);
}


/*
const char* dg_forthhexdecstringtonumbername = "HEXDEC$>NUMBER";

void dg_forthhexdecstringtonumber (Bufferhandle* pBHarrayhead)
    ( number$ -$- )
    ( -- n conversionokflag )
{
    UINT64 stringstackdepth;
    unsigned char* pstring;

	UINT64 stringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    if (stringstackdepth < 1)
	{
		// not enough strings to do compare, will push error and push not equal
		//dg_pusherror(pBHarrayhead, dg_forthurldecodestringssunderflowerror);
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, FORTH_FALSE);
		return;
	}

    pstring = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&stringlength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhexdecstringtonumbername);
        return;
    }

    // if length of $ < 2 it is decimal
    // if $ starts with 0x or 0X it is hex
    // can use c conversion routine here


}
*/


void dg_forthurlencodestring (Bufferhandle* pBHarrayhead)
// ( -- )
// ( decodedurl$ -$- url$ )
// alpha numeric left alone
// characters from this set left alone: minus underscore period tilde
// all other characters replaced with %xx where xx is the hex ascii code for the character
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_urlencodelstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthurlencodestringname);
        return;
    }
}

void dg_forthurldecodestring (Bufferhandle* pBHarrayhead)
//                           ( -- )
//                           ( url$ -$- decodedurl$ )
// + changed to space, %xx changed to character for xx hex ascii code
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_urldecodelstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthurldecodestringname);
	}
}

/*
const char* dg_forthformdecodestringname = "FORMDECODE$";

void dg_forthformdecodestring (Bufferhandle* pBHarrayhead)
//     ( form$ -$- name0$ value0$ name1$ value1$ ... namen$ valuen$ )
//     ( -- n )

{
    UINT64 ssdepth;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    UINT64 numberofpairs;
    UINT64 slength;
    unsigned char* pstring;
    UINT64 stringlength;

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    ssdepth = ::dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
        return;
    }

    if (0 == ssdepth)
    {
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
        return;
    }

    numberofpairs = 0;

    slength = dg_getlstringlength(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        ssdepth - 1);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
        dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
        return;
    }

    while (slength > 0)
    {
        numberofpairs++;

        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACKBUFFERID, 0);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            // obviously can't push to datastack so not trying again
            //dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
            dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
            return;
        }

        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACKBUFFERID, '&');

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            // obviously can't push to datastack so not trying again
            //dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
            dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
            return;
        }

        dg_forthcscanstring(pBHarrayhead);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
            dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
            return;
        }






    }

    // done :-)
    dg_forthdropstring(pBHarrayhead);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, numberofpairs);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthformdecodestringname);
    }

    return;

	// number of pairs = 0
	// begin
	// if there is empty$ on stack, drop it, push number of pairs and stop
	// 
	// scan$ for &
	// if no &,
	//   scan$ for =
	//   if no =
	//     ( name$ garaunteed to not be empty )
	//     push empty value$
	//     push number of pairs
	//     stop
	//   else
	//     split$ at =, drop =
	//     if name$ is empty, drop value $...
	//   then
}

*/

/*
: FORMDECODE$ ( form$ -$- value0$ name0$ value1$ name1$ ... valuen$ namen$ ) ( -- n )
    
    DEPTH$ 1 U< IF
      ( underflow error )
      0 EXIT
    THEN

    0 ( number of pairs so far )

    BEGIN

      LENGTH$ 0= 0= 

    WHILE

      1+ ( incrementing pair count )

      0 [CHAR] & CSCAN$ 
      DUP -1 = IF
  
        ( no & found case, this is last name value pair )
        DROP NEW$ SWAP$

      ELSE

        ( & found, splitting string after & )
        1+ SPLIT$ SWAP$ 

        ( dropping & from end of name=value$ pair )
        $>C DROP

      THEN

      ( now have name=value$ on top )

      0 [CHAR] = CSCAN$
      DUP -1 = IF

        ( no = case, treat entire string as a name$ )
        DROP NEW$ SWAP$

      ELSE

        ( = found, splitting string after = )
        1+ SPLIT$ 

        URLDECODE$

        ?0$>$ ( server sends 0 strings sometimes )

        SWAP$ 

        ( dropping = from end of name$ )
        $>C DROP

        URLDECODE$

        ?0$>$ ( server sends 0 strings sometimes )

      THEN

      ( bringing rest of form$ back to top )
      ROT$

      ?ERRORIF 
        DROP$ EXIT
      THEN

    REPEAT

    DROP$
;

: LOADNAMEVALUEPAIRDEFINITIONS ( n -- ) ( value0$ name0$ value1$ name1$ ... valuen$ namen$ )

    DEPTH 1 U< IF 
      EXIT 
    THEN

    DUP 0= IF
      DROP EXIT
    THEN

    0 DO

      LENGTH$ 0= IF
        DROP$ DROP$
      ELSE

        ( add a definition for name$ that pushes value$ to $ stack )

        ( make sure no delimiters in name$ here )

        ( add name$ to current new definition wordlist as a call subroutine type )
        0 GETP$ NEWSUBROUTINEDEFINITION DROP$
        GET-CURRENT LINKDEFINITION
 
        ( compile push copy of value$ to string stack )

        0 GETP$ COMPILE-S DROP$ ( compile push addr length of copy of value$ to data stack )

        STATE @ ( save current state )

        ['] S>NEW$ ( get execute token of S>NEW$ )
 
        ] ( force compile mode )

        EXECUTE ( compile call S>NEW$ )

        STATE ! ( restore state )

        ( compile return from subroutine )
        POSTPONE EXIT

        ?ERRORIF
          EXIT
        THEN

      THEN

    LOOP
;

*/


void dg_forthstripstring (Bufferhandle* pBHarrayhead)
{
	UINT64 stringstackdepth;

    unsigned char* pstring = NULL;
	UINT64 stringlength = 0;

    UINT64 firstnondelimiter = 0;
	UINT64 lastnondelimiter; // really 1 after last non delimiter

    UINT64 i;

    const char* flag;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // need to get depth of string stack first
	stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstripstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		// not enough strings to do compare, will push error and push not equal
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstripstringname);
		return;
	}

	pstring = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&stringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstripstringname);
        return;
	}

	if (stringlength == 0)
	{
		return;
	}

    lastnondelimiter = stringlength;

    // find first non delimiter in string
    i=0;

    while (i < stringlength)
    {
        if (FORTH_FALSE == (dg_isdelimiter(pstring[i])))
        {
            break;
        }

        i++;
    }

    firstnondelimiter = i;

    // find 1 after last non delimiter in string
    i = stringlength;

    if (firstnondelimiter < stringlength)
    {
        while (i > firstnondelimiter)
        {
            if (FORTH_FALSE == (dg_isdelimiter(pstring[i-1])))
            {
                break;
            }

            i--;
        }
    }

    lastnondelimiter = i;

    if (lastnondelimiter > firstnondelimiter)
    {
        // move segment to beginning
        if (firstnondelimiter != 0)
        {
            // need to blockmove
            flag = dg_movebytes(
                pstring + firstnondelimiter, 
                pstring, 
                lastnondelimiter - firstnondelimiter);

            if (flag != dg_success)
            {
                dg_pusherror(pBHarrayhead, flag);
                dg_pusherror(pBHarrayhead, dg_forthstripstringname);
                return;
            }
        }
    }

    // drop extra stuff from string
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        firstnondelimiter + (stringlength - lastnondelimiter));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstripstringname);
        return;
	}

    dg_forthshortenstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstripstringname);
        return;
	}
}


void dg_forthdotstrings (Bufferhandle* pBHarrayhead)
{
	UINT64 numberoflstrings = 0;
	UINT64 i = 0;
//	UINT64 length = 0;
//	unsigned char* pstring = NULL;
	unsigned char c = '"';

	numberoflstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (numberoflstrings < 1)
	{
		dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            22,
            (unsigned char*)"string stack is empty\n");

		dg_forthprintstring(pBHarrayhead);

		return;
	}

	for (i = 0; i < numberoflstrings; i++)
	{
		dg_writestdout(
            pBHarrayhead,
            &c,
            1);

		dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            numberoflstrings - (i+1));

		dg_forthpickstring(pBHarrayhead);

		dg_forthprintstring(pBHarrayhead);

		dg_writestdout(
            pBHarrayhead,
            &c,
            1);

		dg_forthcr(pBHarrayhead);
	}
}


void dg_forthstrippathfromfilenamestring (Bufferhandle* pBHarrayhead)
//        ( path\filename$ -$- filename$ )
{
	UINT64 x;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
	
	// get start offset
	dg_forthlengthstring(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}
	
	dg_pushdatastack(
        pBHarrayhead,
        (UINT64)'\\');
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}	
	
	dg_forthminuscscanstring(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}
	
	x = dg_popdatastack(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}	
	
	if (x != (UINT64)largestunsignedint)
	{
		// need to drop everything from position x and before from string
		dg_pushdatastack(
            pBHarrayhead,
            x+1);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthsplitstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthswapstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthdropstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
	}
	
	// get start offset
	dg_forthlengthstring(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}
	
	dg_pushdatastack(
        pBHarrayhead,
        (UINT64)'/');
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}	
	
	dg_forthminuscscanstring(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}
	
	x = dg_popdatastack(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
		return;
	}	
	
	if (x != (UINT64)largestunsignedint)
	{
		// need to drop everything from position x and before from string
		dg_pushdatastack(
            pBHarrayhead,
            x+1);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthsplitstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthswapstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
		
		dg_forthdropstring(pBHarrayhead);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthstrippathfromfilenamestringname);
			return;
		}
	}
}


void dg_forthvariableflstring (Bufferhandle* pBHarrayhead)
{
	UINT64 cdata = 0;

    unsigned char* pname;
	UINT64 namelength = 0;
    
    UINT64 newvariablelstringid;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvariableflstringname);
        return;
    }

	if (namelength == 0)
	{
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
		dg_pusherror(pBHarrayhead, dg_forthvariableflstringname);
		return;
	}
    
    newvariablelstringid = dg_newfreeablelstring (
        pBHarrayhead,
        DG_VARIABLEFLSTR_HEADER_BUFFERID); // freeindexbuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthvariableflstringname);
		return;
	}

	dg_createdconstantdef (
        pBHarrayhead,
        DG_VARIABLEFLSTR_HEADER_BUFFERID, // databufid,
        newvariablelstringid, // databufoffset,
        pname,
        namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthvariableflstringname);
		return;
	}
}


void dg_forthfillnewstring(Bufferhandle* pBHarrayhead)
// ( char n -- )
// ( -$- a$ )
{
    UINT64 stringstackdepth;
    INT64 c;
    UINT64 length;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    length = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfillnewstringname);
		return;
	}
    
    c = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfillnewstringname);
		return;
	}
    
    dg_forthnewstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfillnewstringname);
		return;
	}
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfillnewstringname);
		return;
	}
    
    dg_insertwithcfillinlstringn (
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        0, // offset,
        length, // length,
        c); // cvalue)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfillnewstringname);
		return;
	}
}

void dg_forthpzerostrtonewstr (Bufferhandle* pBHarrayhead)
{
    unsigned char* pzerostring;

    UINT64 u1 = (UINT64)largestunsignedint;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pzerostring = (unsigned char*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthpzerostrtonewstrname);
		return;
	}
    
    dg_pzerostringtonewstring(
        pBHarrayhead,
        pzerostring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthpzerostrtonewstrname);
		return;
	}
}


void dg_forthnglufilestring (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthloadfilestring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnglufilestringname);
		return;
	}
    
    dg_forthunpackhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnglufilestringname);
		return;
	}
    
    dg_forthnglu(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthnglufilestringname);
		return;
	}
}

void dg_forthglufilestring (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthloadfilestring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthglufilestringname);
		return;
	}
    
    dg_forthunpackhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthglufilestringname);
		return;
	}
    
    dg_forthglu(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthglufilestringname);
		return;
	}
}


void dg_forthwordsstringquotes (Bufferhandle* pBHarrayhead )
{
    unsigned char* pword;
    UINT64 wordlength;
    
    UINT64 numberofwords = 0;
    
    UINT64 foundendflag = FORTH_FALSE;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    while (foundendflag == FORTH_FALSE)
    {
        pword = dg_parsewords(
            pBHarrayhead,
            &wordlength,
            '"', // enddelimiter
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
          dg_pusherror(pBHarrayhead, dg_forthwordsstringquotesname);
          return;
        }
        
        if (wordlength != 0) // no empty strings from this function
        {
            numberofwords++;
            
            dg_pushlstring(
                pBHarrayhead,
                DG_STRINGOFFSETSTACK_BUFFERID,
                DG_STRINGSTRINGSTACK_BUFFERID,
                wordlength,
                pword);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthwordsstringquotesname);
                return;
            }
        }
    }
        
    dg_pushdatastack(pBHarrayhead, numberofwords);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthwordsstringquotesname);
      return;
    }
}


void dg_forthwords0stringquotes (Bufferhandle* pBHarrayhead )
{
    unsigned char* pword;
    UINT64 wordlength;
    
    UINT64 numberofwords = 0;
    
    UINT64 foundendflag = FORTH_FALSE;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    while (foundendflag == FORTH_FALSE)
    {
        pword = dg_parsewords(
            pBHarrayhead,
            &wordlength,
            '"', // enddelimiter
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
          dg_pusherror(pBHarrayhead, dg_forthwords0stringquotesname);
          return;
        }
        
        if (wordlength != 0) // no empty strings from this function
        {
            numberofwords++;
            
            dg_pushlstring(
                pBHarrayhead,
                DG_STRINGOFFSETSTACK_BUFFERID,
                DG_STRINGSTRINGSTACK_BUFFERID,
                wordlength,
                pword);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthwords0stringquotesname);
                return;
            }
            
            dg_stotoplstring (
              pBHarrayhead,
              DG_STRINGOFFSETSTACK_BUFFERID,
              DG_STRINGSTRINGSTACK_BUFFERID,
              1,
              (unsigned char*)"\x00"); // technically there's a 0 after "" so I don't really need the \x00

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
              dg_pusherror(pBHarrayhead, dg_forthwords0stringquotesname);
              return;
            }
        }
    }
    
    dg_pushdatastack(pBHarrayhead, numberofwords);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthwords0stringquotesname);
      return;
    }
}

// ( n -- )
// ( $0 $1 ... $n-1 -$- $0 $1 ... $n-1 np$s )
//

// make a new string with (n + 1) * 8 length
// for each string 0 to n-1 getp$[i]
// and put into np$[i] where np$ is an array of uint64s
// np$[n] = 0

void dg_forthgetargsfromnstrings(Bufferhandle* pBHarrayhead)
{
    UINT64 n,i;
    unsigned char* pstring;
    unsigned char* plaststring;
    UINT64 stringlength, laststringlength;
    UINT64 stringstackdepth, firststringdepth;
    
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
    
    if (n == 0)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
        
    if (stringstackdepth < n)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
        return;
    }
    
    firststringdepth = stringstackdepth - n;
    
    dg_forthnewstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
    
    dg_growlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        (n+1)*8);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
        
    plaststring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth,
        &laststringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
    
    for (i = 0; i < n; i++)
    {
        pstring = dg_getplstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            firststringdepth + i,
            &stringlength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
          dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
          return;
        }
            
        ((UINT64*)plaststring)[i] = (UINT64)pstring;
    }
    
    ((UINT64*)plaststring)[n] = 0;
    
    dg_pushdatastack(pBHarrayhead, (UINT64)plaststring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthgetargsfromnstringsname);
      return;
    }
}

// ( u -- ) ( ule$ -- ule$b )
void dg_forthumulleutostring(Bufferhandle* pBHarrayhead)
{
    UINT64 u;
    UINT64 stringstackdepth;
    UINT64 localsstringstackdepth;
    UINT64 t;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
        return;
    }
    
    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
    
    t = 0;
    
    // push a new string holding 0 to the locals lstring stack
    dg_pushlstring(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        1,
        (unsigned char*)&t);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
    
    localsstringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
        
    dg_ulemulu64tolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        localsstringstackdepth - 1,
        u);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // just so everything is neat
        dg_droplstring(
            pBHarrayhead, 
            DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
            DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
    
    dg_droplstring(
        pBHarrayhead, 
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthumulleutostringname);
      return;
    }
}


// ( u -- ) ( ule$ -- u*ule$ )
void dg_forthtostarulestring(Bufferhandle* pBHarrayhead)
{
    UINT64 u;
    UINT64 stringstackdepth;
    UINT64 localsstringstackdepth;
    UINT64 t;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
      return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }
    
    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
      return;
    }
    
    t = 0;
    
    /*
    // move top string to locals stack
    plstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }
        
    dg_pushlstring(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        lstringlength,
        plstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }
    
    dg_droplstring(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_poplstringname);
		return;
	}
    */
    
    // push a new string holding 0 to the string stack
    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        8,
        (unsigned char*)&t);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
      return;
    }
    
    /*
    localsstringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
      return;
    }
    */
    
    // string stack depth should be one more
    stringstackdepth++;
        
    dg_mulu64bylstringnaddtolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID, // DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2,          // localsstringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        u);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // just so everything is neat
        // dg_droplstring(
        //    pBHarrayhead, 
        //    DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        //    DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
      dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
      return;
    }
    
    // dg_droplstring(
    //    pBHarrayhead, 
    //    DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
    //    DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //  dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
    //  return;
    // }
    
    // need to trim trailing u64 0s from result string
    //  could use scan for not byte reverse... then shorten string to the first non 0
    //  or look at uint64s.... and I can assume it's u64 aligned...
    plstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }
    
    t = lstringlength / sizeof(UINT64);
    while (t > 1)
    {
        if (((UINT64*)plstring)[t - 1] != 0)
        {
            break;
        }
        
        t = t - 1;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        lstringlength - (t * sizeof(UINT64)));
        
    dg_forthshortenstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }
    
    // DRIP$
    dg_deletelstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtostarulestringname);
        return;
    }    
}


// ( u -- remainder ) ( ule$ -- ule$/u )
void dg_forthtoslashulestring(Bufferhandle* pBHarrayhead)
{
    UINT64 u;
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 remainder;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtoslashulestringname);
      return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtoslashulestringname);
        return;
    }
    
    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthtoslashulestringname);
      return;
    }
    
    dg_divlstringnbyu64 (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        u,
        &remainder);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoslashulestringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        remainder);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoslashulestringname);
        return;
    }
}



// ( u -- )
// ( $0 $1 ... $u-1 -$- $0:u-1 )
//

/*
void dg_forthcatustrings(Bufferhandle* pBHarrayhead)
{
	UINT64 u;


	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	u = dg_popdatastack(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcatnstringsname);
		return;
	}

	dg_catulstrings(
		pBHarrayhead,
		DG_STRINGSTACKBUFFERID,
		u);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcatnstringsname);
		return;
	}
}
*/

/*
void dg_forthrunfileandwaitnoenvquotessub(Bufferhandle* pBHarrayhead)
{
	UINT64 n;
	UINT64* pstringptrs;
	const char* perror;
	const char* pfilename;
	UINT64 stringstackdepth;
	const char* pcommandline;
	UINT64 filenamelength;
	UINT64 commandlinelength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	n = dg_popdatastack(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	if (n < 1)
	{
		dg_pusherror(pBHarrayhead, (const char*)"file name missing");
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	dg_pushdatastack(pBHarrayhead, n);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	dg_forthgetargsfromnstrings(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	pstringptrs = (UINT64*)dg_popdatastack(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	pfilename = (const char*)pstringptrs[0];

	perror = dg_runfileandwait(
		pfilename,
		(char* const*)pstringptrs,  // argv[],       // for mac
		NULL,                        // pcommandline, // for windows
		NULL,                         // envp[],
		dg_success);               // forceerrorflag)

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_runfileandwaitname);
		// not returning here to drop the strings even if there is an error
	}

	olderrorcount = dg_geterrorcount(pBHarrayhead); // just in case there were errors from running file

	dg_dropnlstrings(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		n + 1);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}
}
*/
/*
void dg_forthrunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthwords0stringquotes(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    dg_forthrunfileandwaitnoenvquotessub(pBHarrayhead);
}
*/

void dg_forthlelshiftstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlelshiftstringname);
        return;
    }
    
    dg_lelshiftlstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftstringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftstringname);
        return;
    }
}


void dg_forthulershiftstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulershiftstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulershiftstringname);
        return;
    }
    
    dg_ulershiftlstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulershiftstringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulershiftstringname);
        return;
    }
}


void dg_forthslershiftstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryout;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslershiftstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthslershiftstringname);
        return;
    }
    
    dg_slershiftlstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslershiftstringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslershiftstringname);
        return;
    }
}

void dg_forthlelshiftcstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    carryinout = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftcstringname);
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftcstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlelshiftcstringname);
        return;
    }
    
    dg_lelshiftclstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &carryinout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftcstringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        carryinout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftcstringname);
        return;
    }
}


void dg_forthlershiftcstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    UINT64 carryinout;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    carryinout = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlershiftcstringname);
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlershiftcstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlershiftcstringname);
        return;
    }
    
    dg_lershiftclstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &carryinout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlershiftcstringname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        carryinout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlershiftcstringname);
        return;
    }
}

// I need ULE$>NUMBER$
//  push an empty answer string to... the top of the string stack?
//   (If I put it somewhere else, I'll only need to get a pointer to the source string once)
//  begin
//    get address length top string on string stack
//    scan for anything not 0 in top string
//  while something is not 0
//    divide top lstring on string stack by number base
//    convert the remainder to a character digit (add 0x30) and push to answer string
//  repeat
//  drop the source string from the string stack
//  reverse the answer string

void dg_forthulestringtonumberstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    UINT64 localsstringstackdepth;
    UINT64 t = 0;
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 base;
    UINT64 u64alignedlstringlength;
    const char* pError;
    UINT64 remainder;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
      return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
        dg_pusherror(pBHarrayhead, dg_forthbasename);
		dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
		return;
	}

	if (base < 2)
	{
        dg_pusherror(pBHarrayhead, dg_basetoolowerror);
		dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
		return;
	}
    
    // move top string to locals stack
    plstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
        
    dg_pushlstring(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        lstringlength,
        plstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
    
    dg_droplstring(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
		return;
	}
    
    // push a new empty string to the string stack
    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        (unsigned char*)&t);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
      return;
    }
    
    
    localsstringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
      return;
    }
    
    // need to align string to UINT64
    u64alignedlstringlength = dg_getnearesthighestmultiple (
        lstringlength,
        sizeof(UINT64));

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
		return;
	}
 
    dg_uleextendlstringntol (
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        localsstringstackdepth - 1,
        u64alignedlstringlength);
            
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }   
    
    // get address length of top string on the locals lstring stack
    //  only need to do this once since it won't move
    plstring = dg_getplstring(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        localsstringstackdepth - 1,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
    
    // if the ule$ is already 0, put a 0 into the answer and stop
    t = lstringlength;
    
    // a scan for not uint64 would be faster... but I don't have one yet 12/30/2021
    pError = dg_scanfornotbytereverse (
        (void*)plstring,
        &t, // plength,
        0); // value)
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanfornotbytereversename);
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
    
    if ((UINT64)largestunsignedint == t)
    {
        // was all 0s case
        t = '0';
        dg_stotoplstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            1,
            (unsigned char*)&t);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
            return;
        }
        
        // need to drop top localslstringstack string
        dg_droplstring(
            pBHarrayhead, 
            DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
            DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);    
            return;
        }
        
        return;
    }
    
    while(true)
    {
        t = lstringlength;
        
        pError = dg_scanfornotbytereverse (
            (void*)plstring,
            &t, // plength,
            0); // value)
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_scanfornotbytereversename);
            dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
            return;
        }
    
        if ((UINT64)largestunsignedint == t)
        {
            break;
        }
        
        pError = dg_divu64sbyu64 (
            (UINT64*)plstring,           
            &remainder,      
            base,                 
            lstringlength / sizeof(UINT64));
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_divu64sbyu64name);
            dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
            return;
        }
        
        // t = '0' + remainder;
        t = dg_digittochar(remainder);
        
        dg_stotoplstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            1,
            (unsigned char*)&t);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
            return;
        }
    }
    
    dg_forthreversestring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }

    dg_droplstring(
        pBHarrayhead, 
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID, 
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulestringtonumberstringname);
        return;
    }
}


void dg_forthreversestring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthreversestringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthreversestringname);
        return;
    }
    
    dg_reverselstringn (
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthreversestringname);
        return;
    }
}


void dg_forthnotstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnotstringname);
        return;
    }
    
    if (stringstackdepth == 0)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnotstringname);
        return;
    }
    
    dg_notlstringn (
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnotstringname);
        return;
    }
}


void dg_forthuleandstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleandstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleandstringname);
        return;
    }
    
    dg_uleandlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleandstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleandstringname);
        return;
    }
}


void dg_forthuleorstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleorstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleorstringname);
        return;
    }
    
    dg_uleorlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleorstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleorstringname);
        return;
    }
}


void dg_forthulexorstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexorstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulexorstringname);
        return;
    }
    
    dg_ulexorlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexorstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexorstringname);
        return;
    }
}


void dg_forthulenandstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenandstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulenandstringname);
        return;
    }
    
    dg_ulenandlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenandstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenandstringname);
        return;
    }
}


void dg_forthulenorstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenorstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulenorstringname);
        return;
    }
    
    dg_ulenorlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenorstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenorstringname);
        return;
    }
}


void dg_forthulexnorstring(Bufferhandle* pBHarrayhead)
{
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexnorstringname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        // underflow error
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulexnorstringname);
        return;
    }
    
    dg_ulexnorlstringntolstringn (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexnorstringname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexnorstringname);
        return;
    }
}

void dg_forthtofactorialulestring(Bufferhandle* pBHarrayhead)
{
    UINT64 u;
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtofactorialulestringname);
        return;
    }
    
    x = 1;
    
    dg_stonewstring (
        pBHarrayhead,
        (unsigned char*)&x,
        8);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtofactorialulestringname);
        return;
    }
    
    
    while (x < u)
    {
        x++;
        
        dg_pushdatastack(pBHarrayhead, x);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtofactorialulestringname);
            return;
        }
        
        dg_forthtostarulestring(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtofactorialulestringname);
            return;
        }
    }
}
