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


const char* dg_getlstringstartoffsetname =  "dg_getlstringstartoffset";

UINT64 dg_getlstringstartoffset (
    Bufferhandle *pBHarrayhead,
	UINT64 offsetbufferid,
    UINT64 stringid)
{
	UINT64 stringstartoffset = 0; // = 0 needs to be here
	UINT64 bufferlength;
    UINT64 numberofstringsonstack;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return(0);
    }

	bufferlength = dg_getbufferlength(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringstartoffsetname);
		return (0);
	}

	numberofstringsonstack = bufferlength / sizeof (UINT64); // 0-3 bytes = 0, 4-7 bytes = 1, etc.

	if (stringid >= numberofstringsonstack)
	{
        dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
		dg_pusherror(pBHarrayhead, dg_getlstringstartoffsetname);
		return (0);
	}

	// end of string is pushed onto the offset stack. The start of the first string is at 0, so that offset isn't pushed.
	if (stringid != 0)
	{
		stringstartoffset = (UINT64)dg_getbufferuint64(
            pBHarrayhead, 
            offsetbufferid, 
            (stringid - 1) * sizeof(UINT64));

		if (pBHarrayhead->errorcount != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_getlstringstartoffsetname);
			return (0);
		}
	}

	return (stringstartoffset);
}


const char* dg_getlstringlengthname = "dg_getlstringlength";

UINT64 dg_getlstringlength (
    Bufferhandle *pBHarrayhead,
	UINT64 offsetbufferid,
	UINT64 stringid)
{
	UINT64 stringstartoffset;
	UINT64 stringendoffset = 0;
//	UINT64 bufferlength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (0);
    }

	stringstartoffset = dg_getlstringstartoffset(pBHarrayhead, offsetbufferid, stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringlengthname);
		return (0);
	}

	stringendoffset = (UINT64)dg_getbufferuint64(
        pBHarrayhead, 
        offsetbufferid, 
        stringid * sizeof(UINT64));

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringlengthname);
		return (0);
	}


	if (stringendoffset < stringstartoffset)
	{
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
		dg_pusherror(pBHarrayhead, dg_getlstringlengthname);
		return (0);
	}

	return (stringendoffset - stringstartoffset);
}


const char* dg_getnumberoflstringsonstackname = "dg_getnumberoflstringsonstack";

UINT64 dg_getnumberoflstringsonstack(
    Bufferhandle* pBHarrayhead,
	UINT64 offsetbufferid)
{
    UINT64 bufferlength = 0;
	UINT64 numberofstringsonstack = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (0);
    }

	bufferlength = dg_getbufferlength(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getnumberoflstringsonstackname);
		return (0);
	}

	if (bufferlength % sizeof(UINT64) != 0)
	{
        dg_pusherror(pBHarrayhead, dg_lstringstackdepthcorrupt);
		dg_pusherror(pBHarrayhead, dg_getnumberoflstringsonstackname);
		return(0);
	}

	numberofstringsonstack = bufferlength / sizeof (UINT64); // 0 bytes = 0, 4 bytes = 1, etc.

	return(numberofstringsonstack);
}


const char* dg_getplstringname = "dg_getplstring";

unsigned char* dg_getplstring(
    Bufferhandle* pBHarrayhead,
	UINT64  offsetbufferid,
	UINT64  stringbufferid,
	UINT64  stringid,
	UINT64* pstringlength)
{
	UINT64 stringstartoffset;
	unsigned char* plstring;
    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((unsigned char*)badbufferhandle);
    }
    
    // dg_printzerostring(pBHarrayhead, (unsigned char*)" entering dg_getplstring\n");

    perror = dg_putuint64(pstringlength, 0);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        return ((unsigned char*)badbufferhandle);
    }

	stringstartoffset = dg_getlstringstartoffset(
        pBHarrayhead, 
        offsetbufferid, 
        stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getplstringname);
		return ((unsigned char*)badbufferhandle);
	}

	*pstringlength = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferid, 
        stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getplstringname);
		return ((unsigned char*)badbufferhandle);
	}

	plstring = dg_getpbuffersegment(
        pBHarrayhead, 
        stringbufferid, 
        stringstartoffset, 
        *pstringlength);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		*pstringlength = 0;
		dg_pusherror(pBHarrayhead, dg_getplstringname);
		return ((unsigned char*)badbufferhandle);
	}
 
   // dg_printzerostring(pBHarrayhead, (unsigned char*)" exiting dg_getplstring\n");

	return (plstring);
}


const char* dg_getlstringname = "dg_getlstring";

void dg_getlstring (
    Bufferhandle* pBHarrayhead,
	UINT64 offsetbufferid,
	UINT64 stringbufferid,
	UINT64 stringid,
	UINT64 maxlength,
	unsigned char* pdest)
{
	UINT64 stringstartoffset = 0;
	UINT64 stringlength = 0;
    
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	stringstartoffset = dg_getlstringstartoffset(
        pBHarrayhead, 
        offsetbufferid, 
        stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringname);
		return;
	}

	stringlength = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferid, 
        stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringname);
		return;
	}

	if (stringlength > maxlength)
	{
        dg_pusherror(pBHarrayhead, dg_toobigfordesterror);
		dg_pusherror(pBHarrayhead, dg_getlstringname);
		return;
	}

	dg_getbuffersegment(pBHarrayhead, 
		stringbufferid, 
		stringstartoffset, 
		stringlength, 
		pdest);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlstringname);
	}
}


const char* dg_poplstringname  = "dg_poplstring";

void dg_poplstring (
    Bufferhandle* pBHarrayhead,
	UINT64 offsetbufferid,
	UINT64 stringbufferid,
	UINT64 maxlength,
	unsigned char* pdest)
{
	UINT64 stringid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	stringid = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_poplstringname);
		return;
	}

	// check to see if no strings on stack
	if (stringid == 0)
	{
        dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_poplstringname);
		return;
	}

	stringid--;

	// get the string
	dg_getlstring(
        pBHarrayhead,
		offsetbufferid,
		stringbufferid,
		stringid,
		maxlength,
		pdest);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_poplstringname);
		return;
	}

	// dg_droplstring should work no problem
	dg_droplstring(pBHarrayhead, offsetbufferid, stringbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_poplstringname);
		return;
	}
}


const char* dg_pushlstringname   = "dg_pushlstring";

void dg_pushlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 length,
    unsigned char* psrc)
{
	const char* pError;
	UINT64 oldoffsetbufferlength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	oldoffsetbufferlength =
		dg_getbufferlength(pBHarrayhead, stringbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushlstringname);
		return;
	}

	dg_pushbuffersegment(pBHarrayhead, stringbufferid, length, psrc);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushlstringname);
		return;
	}

	dg_pushbufferuint64(pBHarrayhead, offsetbufferid, oldoffsetbufferlength + length);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_shrinkbuffer(pBHarrayhead, stringbufferid, length, &pError);
		dg_pusherror(pBHarrayhead, dg_pushlstringname);
		return;
	}
}


const char* dg_growlstringname  = "dg_growlstring";

void dg_growlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 length)
{
	UINT64* poffsetbuffer;
	UINT64* poffsetlength;

	const char* pError;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	poffsetbuffer = (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_growlstringname);
		return;
	}

	if (*poffsetlength < sizeof (UINT64))
	{
        dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_growlstringname);
		return;
	}

	dg_growbuffer(pBHarrayhead, stringbufferid, length, &pError, FORTH_FALSE);

	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
		dg_pusherror(pBHarrayhead, dg_growlstringname);
		return;
	}

	*(poffsetbuffer + (((*poffsetlength) / sizeof(UINT64)) - 1)) += length;
}


const char dg_catlstringname[] = "dg_catlstring";

void dg_catlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid)
{
	UINT64* poffsetlength;
	unsigned char* poffsetstack;

	UINT64* pints;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	poffsetstack = dg_getpbuffer(
        pBHarrayhead,
        offsetbufferid,
        &poffsetlength);

	if (poffsetstack == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_catlstringname);
		return;
	}

	if (*poffsetlength < (2 * sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_catlstringname);
		return;
	}

	// could check for misaligned offset stack here

	pints = (UINT64*)(poffsetstack + *poffsetlength - 2*sizeof(UINT64));
	
	pints[0] = pints[1];

	*poffsetlength -= sizeof (UINT64);
}

const char dg_catulstringsname[] = "dg_catulstrings";

void dg_catulstrings(
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 u)
{
    UINT64 i;
    UINT64 stringstackdepth;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    if (u == 0)
    {
        return;
    }

    // check string stack depth...
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_catulstringsname);
        return;
    }

    if (stringstackdepth < u)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_catulstringsname);
        return;
    }

    for (i = 0; i < u; i++)
    {
        dg_catlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_catulstringsname);
            return;
        }

        return;
    }
}

const char* dg_stotoplstringname = "dg_stotoplstring";

void dg_stotoplstring (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 length,
    unsigned char* psrc)
{
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_pushlstring(pBHarrayhead, offsetbufferid, stringbufferid, length, psrc);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_stotoplstringname);
		return;
	}

	dg_catlstring(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_stotoplstringname);
		return;
	}
}


const char* dg_picklstringname  = "dg_picklstring";

void dg_picklstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 n)
{
	const char* pError;

	UINT64 length = 0;
	UINT64 depth;
	UINT64 startoffset = 0;

	UINT64 oldslength;

	UINT64 index;

	UINT64* poffsetbuffer;
	UINT64* poffsetbufferlength;

//	UINT64 i = 0;

//	UINT64 stringbufferlength = 0;
	unsigned char* pstringbuffer = NULL;
	UINT64* pstringbufferlength = NULL;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	poffsetbuffer = (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetbufferlength);

	if ((UINT64*)badbufferhandle == poffsetbuffer)
	{
		dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	depth = (*poffsetbufferlength) / sizeof(UINT64);
	
	if (n >= depth)  // this covers the n = -1 case and depth = 0 case
	{
		dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	index = depth - (n+1);

	// start offset set to 0 at the top
	if (index != 0)
	{
		startoffset = poffsetbuffer[index - 1];
	}

	// check for bad length
	if (startoffset > poffsetbuffer[index])
	{
		dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
        dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	length = poffsetbuffer[index] - startoffset;

	// grow string buffer
	oldslength = dg_growbuffer(pBHarrayhead, stringbufferid, length, &pError, false);

	if (pError != dg_success)
	{
		dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	// could check to make sure current end of offset buffer is correct
	if (poffsetbuffer[depth - 1] != oldslength)
	{
		dg_pusherror(pBHarrayhead, dg_lstringtopoffsetwasbad);
        dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	// push new end offset to offset buffer
	dg_pushbufferuint64(pBHarrayhead, offsetbufferid, oldslength + length);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	// get pointer to string buffer
	pstringbuffer = dg_getpbuffer(pBHarrayhead, stringbufferid, &pstringbufferlength);

	if (pstringbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_picklstringname);
		return;
	}

	// blockmove - we know memory is ok
    dg_movebytes(
        pstringbuffer + startoffset, 
        pstringbuffer + (*pstringbufferlength) - length, 
        length);

	//for (i = 0; i < length; i++)
	//{
	//	*(pstringbuffer + (*pstringbufferlength) - length + i) = *(pstringbuffer + startoffset + i);
	//}	
}


const char* dg_droplstringname = "dg_droplstring";

void dg_droplstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid)
{
	UINT64 lstringlength;
	UINT64 stringid;
	const char* pError;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	stringid = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_droplstringname);
		return;
	}

	// check to see if no strings on stack
	if (stringid == 0)
	{
		dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_droplstringname);
		return;
	}

	stringid--;

	lstringlength = dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);
	// could just set the string buffer length to the last offset in the buffer...
	//  would be more reliable

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_droplstringname);
		return;
	}

	// dg_shrinkbuffer should work no problem
	dg_shrinkbuffer(pBHarrayhead, offsetbufferid, sizeof(UINT64), &pError);

	// but just in case
	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        // would be nice to push buffer name here
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
		dg_pusherror(pBHarrayhead, dg_droplstringname);
		return;
	}

	dg_shrinkbuffer(pBHarrayhead, stringbufferid, lstringlength, &pError);

	if (pError != dg_success)
	{
		// don't really need to put the grow in, but just to be thorough
		dg_growbuffer(pBHarrayhead, offsetbufferid, sizeof(UINT64), &pError, false);
        dg_pusherror(pBHarrayhead, pError);
        // would be nice to push buffer name here
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
		dg_pusherror(pBHarrayhead, dg_droplstringname);
	}
}


const char* dg_dropnlstringsname = "dg_dropnlstrings";

void dg_dropnlstrings (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 n) // number of strings to drop
{
    UINT64 lstringlength;
    UINT64 stringid;
    const char* pError;
    UINT64 newlaststringendoffset = 0; // needed for exactly enough strings case
    UINT64 oldlaststringendoffset = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (n == 0)
    {
        return;
    }

    // need to get stringid of last string
    stringid = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        offsetbufferid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dropnlstringsname);
        return;
    }

    // check to see if there are enough strings on stack
    if (stringid < n)
    {
        dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_dropnlstringsname);
        return;
    }
    
    oldlaststringendoffset =
    dg_getbufferuint64(
        pBHarrayhead,
        offsetbufferid,
        (stringid-1) * sizeof(UINT64));

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dropnlstringsname);
        return;
    }
    
    if ((stringid - n) > 0)
    {
        newlaststringendoffset =
        dg_getbufferuint64(
            pBHarrayhead,
            offsetbufferid,
            ((stringid-1) - n) * sizeof(UINT64));
    }

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dropnlstringsname);
        return;
    }

    // dg_shrinkbuffer should work no problem
    dg_shrinkbuffer(pBHarrayhead, offsetbufferid, n*sizeof(UINT64), &pError);

    // but just in case
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        // would be nice to push buffer name here
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_droplstringname);
        return;
    }
    
    if (newlaststringendoffset > oldlaststringendoffset)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
        dg_pusherror(pBHarrayhead, dg_dropnlstringsname);
        return;
    }

    // could just set the string buffer length to the offset...
    dg_shrinkbuffer(
        pBHarrayhead,
        stringbufferid,
        oldlaststringendoffset - newlaststringendoffset,
        &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        // would be nice to push buffer name here
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_droplstringname);
    }
}


const char* dg_deletelstringname = "dg_deletelstring";

void dg_deletelstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid)
{
	UINT64 lstringlength;
	UINT64 numonstack;
	const char* pError;
	UINT64 lstringstartoffset;
	UINT64 i;
	UINT64* poffsetlength;
	UINT64* poffsetbuffer;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	numonstack = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}

	// check to see if desired string is on stack
	if ( stringid >= numonstack)
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}

	lstringlength = dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}

	lstringstartoffset = dg_getlstringstartoffset(pBHarrayhead,
		offsetbufferid,
		stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}

	dg_deleteinbuffer(pBHarrayhead, 
		stringbufferid,
		lstringstartoffset,
		lstringlength);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}
	
	if (numonstack > 1)
	{
		poffsetbuffer = 
		    (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

		if (poffsetbuffer == (UINT64*)badbufferhandle)
		{
		    dg_pusherror(pBHarrayhead, dg_deletelstringname);
		    return;
		}

		// now we need to update all end of string offsets,
		//  delete the one for the string deleted, and then subtract length from all the ones after
		for (i=stringid; i < numonstack - 1; i++)
		{
			poffsetbuffer[i] = poffsetbuffer[i+1] - lstringlength;
		}
	}


	// shrinks should work no problem
	dg_shrinkbuffer(pBHarrayhead, offsetbufferid, sizeof(UINT64), &pError);

	// but just in case
	if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
		dg_pusherror(pBHarrayhead, dg_deletelstringname);
		return;
	}
}


const char* dg_insertlstringname = "dg_insertlstring";

void dg_insertlstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 length)
{
	UINT64 numonstack;
	UINT64 lstringstartoffset;
	UINT64 i;
	UINT64* poffsetlength;
	UINT64* poffsetbuffer;
    UINT64 n;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	numonstack = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertlstringname);
		return;
	}

	// check to see if desired position for new string is on l$stack
	//   pushing to end of l$stack is ok
	if ( stringid > numonstack)
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_insertlstringname);
		return;
	}

	// if pushing to end then this is just pushlstring
	//if (numonstack == stringid)
	//{
	//	dg_pushlstring(pBHarrayhead, offsetbufferid, stringbufferid, length, psrc);

	//	if (pBHarrayhead->errorcount != olderrorcount)
	//	{
	//		dg_pusherror(pBHarrayhead, dg_insertlstringname);
	//		return;
	//	}

	//	return;
	//}

	// grow offset buffer (push empty string onto end of l$ stack)
	dg_pushlstring(pBHarrayhead, offsetbufferid, stringbufferid, 0, (unsigned char*)"");

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertlstringname);
		return;
	}

	// get offset of insert in l$stack string buffer
	lstringstartoffset = dg_getlstringstartoffset(pBHarrayhead,
		offsetbufferid,
		stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertlstringname);
		return;
	}

	// grow string buffer 
	dg_insertinbuffer(pBHarrayhead, 
		stringbufferid,
		lstringstartoffset,
		length);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		// dropping the empty string
		dg_droplstring(pBHarrayhead, offsetbufferid, stringbufferid);
		dg_pusherror(pBHarrayhead, dg_insertlstringname);
		return;
	}

	//dg_putbuffersegment(pBHarrayhead, stringbufferid, lstringstartoffset, length, psrc);

	// should be impossible to get this error
	//if (pBHarrayhead->errorcount != olderrorcount)
	//{
		// dropping the empty string
	//	dg_droplstring(pBHarrayhead, offsetbufferid, stringbufferid);
	//	dg_pusherror(pBHarrayhead, dg_insertlstringname);
	//	return;
	//}

	poffsetbuffer = 
	    (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

	if (poffsetbuffer == (UINT64*)badbufferhandle)
	{
	    dg_pusherror(pBHarrayhead, dg_insertlstringname);
	    return;
	}

	// now we need to update all end of string offsets,
	//  add length from all the ones after backwards
    //  then go back and set length of first one
    if (numonstack < stringid)
    {
        return;
    }

    for (i=0; i < ((numonstack + 1) - stringid); i++)
	{
        n = numonstack - i;

        if (n > 0)
        {
            poffsetbuffer[n] = poffsetbuffer[n-1] + length;
        }
        else
        {
            poffsetbuffer[n] = length;
            break;
        }
	}	
}


const char* dg_deleteinlstringname = "dg_deleteinlstring";

void dg_deleteinlstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 offset,
    UINT64 length)
{
	UINT64 lstringlength;
	UINT64 numonstack;
	UINT64 lstringstartoffset;
	UINT64 i;
	UINT64* poffsetlength;
	UINT64* poffsetbuffer;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	numonstack = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
	}

	// check to see if desired string is on stack
	if ( stringid >= numonstack)
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
	}

	lstringlength = dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
	}

    if (offset + length > lstringlength)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
        
    }

	lstringstartoffset = dg_getlstringstartoffset(pBHarrayhead,
		offsetbufferid,
		stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
	}

    // this should work
	dg_deleteinbuffer(pBHarrayhead, 
		stringbufferid,
		lstringstartoffset + offset,
		length);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
		return;
	}
	
    // this should work
	poffsetbuffer = 
	    (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

	if (poffsetbuffer == (UINT64*)badbufferhandle)
	{
	    dg_pusherror(pBHarrayhead, dg_deleteinlstringname);
	    return;
	}

	// now we need to update all end of string offsets,
	//  subtract length from lstring stringid and all the ones after
	for (i=stringid; i < numonstack; i++)
	{
		poffsetbuffer[i] = poffsetbuffer[i] - length;
	}
}


const char* dg_insertinlstringname = "dg_insertinlstring";

void dg_insertinlstring (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 offset,
    UINT64 length)
{
	UINT64 lstringlength;
	UINT64 numonstack;
	UINT64 lstringstartoffset;
	UINT64 i;
	UINT64* poffsetlength;
	UINT64* poffsetbuffer;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	numonstack = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
	}

	// check to see if desired string is on stack
	if ( stringid >= numonstack)
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
	}

	lstringlength = dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
	}

    if (offset > lstringlength)
    {
        dg_pusherror(pBHarrayhead, dg_lstringoffsetpastenderror);
        dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
        
    }

	lstringstartoffset = dg_getlstringstartoffset(pBHarrayhead,
		offsetbufferid,
		stringid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
	}

    // this should work
	dg_insertinbuffer(
        pBHarrayhead, 
		stringbufferid,
		lstringstartoffset + offset,
		length);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_insertinlstringname);
		return;
	}
	
    // this should work
	poffsetbuffer = 
	    (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

	if (poffsetbuffer == (UINT64*)badbufferhandle)
	{
	    dg_pusherror(pBHarrayhead, dg_insertinlstringname);
	    return;
	}

	// now we need to update all end of string offsets,
	//  subtract length from lstring stringid and all the ones after
	for (i=stringid; i < numonstack; i++)
	{
		poffsetbuffer[i] = poffsetbuffer[i] + length;
	}
}


const char* dg_catlstringnname = "dg_catlstringn";

void dg_catlstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid)
//     ( n -- )
//     ( l$0 ... l$n-1 l$n l$n+1 l$n+2 ... l$top -l$- 
//         l$0 ... l$n-1 l$n+l$n+1 l$n+2 ... l$top )
{
	UINT64 numonstack;
	UINT64 i;
	UINT64* poffsetlength;
	UINT64* poffsetbuffer;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	// need to get stringid of last string
	numonstack = dg_getnumberoflstringsonstack(pBHarrayhead, offsetbufferid);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_catlstringnname);
		return;
	}

	// check to see if desired string is on stack
	if ( stringid + 1 >= numonstack)
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_catlstringnname);
		return;
	}
	
    // this should work
	poffsetbuffer = 
	    (UINT64*)dg_getpbuffer(pBHarrayhead, offsetbufferid, &poffsetlength);

	if (poffsetbuffer == (UINT64*)badbufferhandle)
	{
	    dg_pusherror(pBHarrayhead, dg_catlstringnname);
	    return;
	}

	// now we need to update all end of string offsets,
	//  subtract length from lstring stringid and all the ones after
	for (i=stringid; i < numonstack - 1; i++)
	{
		poffsetbuffer[i] = poffsetbuffer[i+1];
	}

    *poffsetlength -= sizeof(UINT64);
}


const char* dg_copystolstringnname = "dg_copystolstringn";

void dg_copystolstringn (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 offset,
    unsigned char* psrc,
    UINT64 length)
{
    UINT64 stringbufferstartoffset;
    UINT64 lstringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    stringbufferstartoffset = ::dg_getlstringstartoffset(
        pBHarrayhead,
        offsetbufferid,
        stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copystolstringnname);
		return;
	}

    lstringlength = ::dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copystolstringnname);
		return;
	}

    if (offset + length > lstringlength)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_copystolstringnname);
		return;
    }

    dg_putbuffersegment(
        pBHarrayhead,
        stringbufferid,
        stringbufferstartoffset + offset,
        length,
        psrc);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copystolstringnname);
		return;
	}
}


const char* dg_pushstolstringnname = "dg_pushstolstringn";

void dg_pushstolstringn (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    unsigned char* psrc,
    UINT64 length)
{
    UINT64 stringbufferstartoffset;
    UINT64 lstringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    stringbufferstartoffset = ::dg_getlstringstartoffset(
        pBHarrayhead,
        offsetbufferid,
        stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushstolstringnname);
		return;
	}

    lstringlength = ::dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushstolstringnname);
		return;
	}
 
    dg_insertinlstring (
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        lstringlength, // inserting at end of lstring just to be neat
        length);  
        
    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushstolstringnname);
		return;
	}

    dg_putbuffersegment(
        pBHarrayhead,
        stringbufferid,
        stringbufferstartoffset + lstringlength,
        length,
        psrc);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushstolstringnname);
		return;
	}
}


const char* dg_copysfromlstringnname = "dg_copysfromlstringn";

void dg_copysfromlstringn (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 offset,
    UINT64 length,
    unsigned char* pdest)
{
    UINT64 stringbufferstartoffset;
    UINT64 lstringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    stringbufferstartoffset = ::dg_getlstringstartoffset(
        pBHarrayhead,
        offsetbufferid,
        stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copysfromlstringnname);
		return;
	}

    lstringlength = ::dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copysfromlstringnname);
		return;
	}

    if (offset + length > lstringlength)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_copysfromlstringnname);
		return;
    }

    dg_getbuffersegment(
        pBHarrayhead,
        stringbufferid,
        stringbufferstartoffset + offset,
        length,
        pdest);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copysfromlstringnname);
		return;
	}
}


const char* dg_setlengthlstringnname = "dg_setlengthlstringn";

void dg_setlengthlstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 newlength)
{
    UINT64 stringbufferstartoffset;
    UINT64 lstringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    stringbufferstartoffset = ::dg_getlstringstartoffset(
        pBHarrayhead,
        offsetbufferid,
        stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_setlengthlstringnname);
		return;
	}

    lstringlength = ::dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_setlengthlstringnname);
		return;
	}

	if (newlength==lstringlength)
	{
		// nothing to be done
		return;
	}

	if (newlength<lstringlength)
	{
		dg_deleteinlstring (
            pBHarrayhead,
            offsetbufferid,
            stringbufferid,
            stringid,
            newlength, // deleting from new end of lstring just to be neat
            lstringlength - newlength);

        if (pBHarrayhead->errorcount != olderrorcount)
	    {
		    dg_pusherror(pBHarrayhead, dg_setlengthlstringnname);
	    }

        return;
	}

    dg_insertinlstring (
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        lstringlength, // inserting at end of lstring just to be neat
        newlength - lstringlength);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_setlengthlstringnname);
	}
}


const char* dg_replacelstringnname = "dg_replacelstringn";

void dg_replacelstringn (Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    unsigned char* psrc,
    UINT64 length)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    dg_setlengthlstringn (
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        length);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_replacelstringnname);
        return;
	}

    dg_copystolstringn (
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        0, // offset = start of lstring
        psrc,
        length);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_replacelstringnname);
        return;
	}
}


const char* dg_copylstringntoreplacelstringnname = "dg_copylstringntoreplacelstringn";

void dg_copylstringntoreplacelstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 srcoffsetbufferid,
	UINT64 srcstringbufferid,
	UINT64 srcstringid,
    UINT64 destoffsetbufferid,
    UINT64 deststringbufferid,
    UINT64 deststringid)
{
    UINT64 srclstringlength;
    unsigned char* psrclstring;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // resizing destination lstring first to cover case where source and destination
    //  lstrings are on the same lstring stack and growing destination may cause the
    //  buffer to move.

    // source lstring stack underflow checked in this call
    srclstringlength = ::dg_getlstringlength(pBHarrayhead, srcoffsetbufferid, srcstringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copylstringntoreplacelstringnname);
		return;
	}

    // destination lstring stack underflow checked in this call.

    // calling this function may cause destination lstring buffers to move.
    //  which could invalidate pointers to the source lstring if it is in the
    //  same stack as the destination lstring.
    dg_setlengthlstringn(
        pBHarrayhead,
        destoffsetbufferid,
        deststringbufferid,
        deststringid,
        srclstringlength);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copylstringntoreplacelstringnname);
        return;
	}

    // getting pointer to source lstring
    psrclstring = dg_getplstring(
        pBHarrayhead,
        srcoffsetbufferid,
        srcstringbufferid,
        srcstringid,
        &srclstringlength);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copylstringntoreplacelstringnname);
        return;
	}

    dg_copystolstringn (
        pBHarrayhead,
        destoffsetbufferid,
        deststringbufferid,
        deststringid,
        0, // offset = start of lstring
        psrclstring,
        srclstringlength);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_copylstringntoreplacelstringnname);
        return;
	}
}


const char* dg_copytoinsertlstrntomname = "dg_copytoinsertlstrntom";

void dg_copytoinsertlstrntom (
    Bufferhandle* pBHarrayhead,
    UINT64 srcoffsetbufferidn,
	UINT64 srcstringbufferidn,
	UINT64 srcstringidn,
    UINT64 srcoffsetn,
    UINT64 destoffsetbufferidm,
    UINT64 deststringbufferidm,
    UINT64 deststringidm,
    UINT64 destoffsetm,
    UINT64 length)
{
    unsigned char* psrcn;
    UINT64 srclengthn;
    
    unsigned char* pdestm;
    UINT64 destlengthm;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get pointer to source
    psrcn = dg_getplstring(
        pBHarrayhead,
        srcoffsetbufferidn,
		srcstringbufferidn,
		srcstringidn,
        &srclengthn);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
    
    // make sure source segment is in lstring
    if ( srcoffsetn > ((UINT64)(0-(INT64)length)) )
    {
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
    
    if ((srcoffsetn + length) > srclengthn)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsegmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
    
    dg_insertinlstring (
        pBHarrayhead,
		destoffsetbufferidm,
		deststringbufferidm,
		deststringidm,
        destoffsetm,
        length);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
    
    // get pointer to destination
    pdestm = dg_getplstring(
        pBHarrayhead,
        destoffsetbufferidm,
		deststringbufferidm,
		deststringidm,
        &destlengthm);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
    
    // copy source to destination
        // this copy handles the case where the source overlaps the destination
    pError = dg_movebytesskipdestination (
        psrcn + srcoffsetn, 
        pdestm + destoffsetm, 
        length);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_movebytesskipdestinationname);
        dg_pusherror(pBHarrayhead, dg_copytoinsertlstrntomname);
        return;
    }
}


const char* dg_makesurelstringnexistsname = "dg_makesurelstringnexists";

void dg_makesurelstringnexists (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringoffsetbufferid,
    UINT64 lstringstringbufferid,
    UINT64 n)
{
    unsigned char* poffsetbuffer;
    UINT64* poffsetbufferlength;
    
    UINT64 depth;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

	poffsetbuffer = dg_getpbuffer(pBHarrayhead, lstringoffsetbufferid, &poffsetbufferlength);

	if ((unsigned char*)badbufferhandle == poffsetbuffer)
	{
		dg_pusherror(pBHarrayhead, dg_makesurelstringnexistsname);
		return;
	}

	depth = (*poffsetbufferlength) / sizeof(UINT64);
    
    while (depth <= n)
    {
        dg_pushlstring(
            pBHarrayhead, 
            lstringoffsetbufferid, 
            lstringstringbufferid, 
            0, 
            (unsigned char*)"");
            
        if ((unsigned char*)badbufferhandle == poffsetbuffer)
        {
            dg_pusherror(pBHarrayhead, dg_makesurelstringnexistsname);
            return;
        }
        
        depth++;
    }
}

/////////
//  Freeable lstrings should have gaps between with allocated and used amounts like buffers
//   this would improve the speed
const char* dg_freefreeablelstringarrayname = "dg_freefreeablelstringarray";

void dg_freefreeablelstringarray(
        Bufferhandle* pBHarrayhead, 
        UINT64 freeindexbuffer)
{
	struct Freeablelstringarrayheader myflstrheader;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
	
	dg_getbuffersegment(pBHarrayhead, freeindexbuffer, 0, sizeof(Freeablelstringarrayheader), (unsigned char*)(&myflstrheader));
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// not freeing this buffer because we don't know what it is
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringarrayname);
		return;
	}
	
	// it's not a freeable lstring array
	if (myflstrheader.magic != dg_freeablelstringheadermagic)
	{
		dg_pusherror(pBHarrayhead, dg_badmagicerror);
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringarrayname);
		return;
	}		
	
	dg_freebuffer(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
	dg_freebuffer(pBHarrayhead, myflstrheader.lstringstringbufferid);
	dg_freebuffer(pBHarrayhead, freeindexbuffer); 
	
	/*
	// dg_freebuffer does not return errors
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringarrayname);
		return;
	}
	*/
}

// allocates an lstring array's offset and string buffers
//  then allocates a free index linked list array buffer
//
//  the free index linked list array has a header which has:
//   a magic id
//   lstring offset buffer id
//   lstring string buffer id
//   first free lstring index
//  the array of lstring status attributes follows 
//  each lstring index has a value in this array which indicates:
//   it is not free (in use)
//   or it is in the linked list of free indexes, 
//    in which case the value is the index of the next free lstring in the linked list
//
 
// the order of the buffer allocations in this routine must match the order of the #defines for
//  the variable string freeable lstring buffer declarations in diapergluforth.h
const char* dg_newfreeablelstringarrayname = "dg_newfreeablelstringarray";

UINT64 dg_newfreeablelstringarray(Bufferhandle* pBHarrayhead)
{
	struct Freeablelstringarrayheader myflstrheader;
	UINT64 myflstrheaderbufferid = (UINT64)dg_badbufferid;
	const char* pError;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return((UINT64)dg_badbufferid);
	}
	
	myflstrheader.magic = dg_freeablelstringheadermagic;
	myflstrheader.firstfreeid = (UINT64)dg_freeablelstringlastfreeid;
	
	myflstrheader.lstringoffsetbufferid = dg_newbuffer(pBHarrayhead,
													   dg_defaultbuffergrowby,
													   dg_defaultbuffermaxsize,
													   &pError,
													   FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringarrayname);
		return((UINT64)dg_badbufferid);
	}
	
	myflstrheader.lstringstringbufferid = dg_newbuffer(pBHarrayhead,
													   dg_defaultbuffergrowby,
													   dg_defaultbuffermaxsize,
													   &pError,
													   FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_freebuffer(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringarrayname);
		return((UINT64)dg_badbufferid);
	}
	
	myflstrheaderbufferid = dg_newbuffer(pBHarrayhead,
										 dg_defaultbuffergrowby,
										 dg_defaultbuffermaxsize,
										 &pError,
										 FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_freebuffer(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
		dg_freebuffer(pBHarrayhead, myflstrheader.lstringstringbufferid);
		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringarrayname);
		return((UINT64)dg_badbufferid);
	}
	
	dg_pushbuffersegment(pBHarrayhead, myflstrheaderbufferid, sizeof(Freeablelstringarrayheader), (unsigned char*)(&myflstrheader));
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_freebuffer(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
		dg_freebuffer(pBHarrayhead, myflstrheader.lstringstringbufferid);
		dg_freebuffer(pBHarrayhead, myflstrheaderbufferid);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringarrayname);
		return((UINT64)dg_badbufferid);
	}
	
	return(myflstrheaderbufferid);
}


const char* dg_freefreeablelstringname = "dg_freefreeablelstring";

void dg_freefreeablelstring(
   Bufferhandle* pBHarrayhead,
   UINT64 freeindexbuffer,
   UINT64 lstringindex)
{
	struct Freeablelstringarrayheader myflstrheader;
	
	UINT64 lstringoffsetbufferlength;
	UINT64 freeindexbufferlength;
	
	UINT64 isfreenextfreeflag;
	
	UINT64 lstringlength;
	
	const char* pError;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
	
	// check freeable lstring array buffers for correct magic id and buffer lengths
	dg_getbuffersegment(pBHarrayhead, freeindexbuffer, 0, sizeof(Freeablelstringarrayheader), (unsigned char*)(&myflstrheader));
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	if (myflstrheader.magic != dg_freeablelstringheadermagic)
	{
		dg_pusherror(pBHarrayhead, dg_badmagicerror);
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}	
	
	freeindexbufferlength = dg_getbufferlength(pBHarrayhead, freeindexbuffer);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	if ( ((freeindexbufferlength - sizeof(Freeablelstringarrayheader)) % sizeof(UINT64)) != 0 )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror); 
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	lstringoffsetbufferlength = dg_getbufferlength(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}	
	
	// if array corrupt throw error -- doing it this way to prevent possibility of overflow
	if (lstringoffsetbufferlength != (freeindexbufferlength - sizeof(Freeablelstringarrayheader)) )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	// if lstring index off end throw error
	if (lstringindex >= (lstringoffsetbufferlength / sizeof(UINT64)) )
	{
		dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
		
	// if already free then throw error
		// addition can't overflow since index is in array
	isfreenextfreeflag = dg_getbufferuint64(pBHarrayhead,
										   freeindexbuffer,
										   (lstringindex * sizeof(UINT64)) + sizeof(Freeablelstringarrayheader) );
		
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
    if (isfreenextfreeflag != (UINT64)dg_freeablelstringisnotfreeid)
	{
		dg_pusherror(pBHarrayhead, dg_alreadyfreeerror);
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
		
	// if lstring is last in array then just drop it and the free flag for it
		// +1 can't overflow because of previous < x*sizeof(UINT64) calculation
	if ( (lstringindex + 1) == (lstringoffsetbufferlength / sizeof(UINT64)) )
	{
		// drop last lstring
		dg_droplstring(pBHarrayhead, myflstrheader.lstringoffsetbufferid, myflstrheader.lstringstringbufferid);
		
		// shouldnt get an error dropping...
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
			return;
		}
		
		// shorten free buffer by sizeof (UINT64)
		dg_shrinkbuffer(pBHarrayhead, freeindexbuffer, sizeof(UINT64), &pError);
		
		// can't really get an error shrinking since buffer is large enough
		if (pError != dg_success)
		{
			//allocate a newlstring so array won't be misaligned
			dg_pushlstring(pBHarrayhead,
						   myflstrheader.lstringoffsetbufferid, 
						   myflstrheader.lstringstringbufferid,
						   0,
						   (unsigned char*)"");
			
			dg_pusherror(pBHarrayhead, pError);
			dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
			dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		}
		
		return;
	}
			
	// otherwise, shorten lstring length to 0, add it to free list
	// shorten lstring to 0
	lstringlength = dg_getlstringlength (pBHarrayhead,
										 myflstrheader.lstringoffsetbufferid,
										 lstringindex);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	dg_deleteinlstring (pBHarrayhead,
						myflstrheader.lstringoffsetbufferid, 
						myflstrheader.lstringstringbufferid,
						lstringindex,
						0,
						lstringlength);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
    // go from firstfree -> a -> b -> lastinlist
	// firstfree -> n -> a -> b -> lastinlist
	dg_putbufferuint64(pBHarrayhead, freeindexbuffer, (lstringindex * sizeof(UINT64)) + sizeof(Freeablelstringarrayheader), myflstrheader.firstfreeid);
	
	// this error can't really happen
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// but if it does then lstring gets leaked... 
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
	
	myflstrheader.firstfreeid = lstringindex;
	
	dg_putbuffersegment(pBHarrayhead, 
						freeindexbuffer, 
						0,
						sizeof(myflstrheader),
	                    (unsigned char*)(&myflstrheader));
	
	// this error can't really happen
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// but if it does then freed lstring gets leaked...  but you have a bigger problem, somehow your computer hardware lost bits :-)
		dg_pusherror(pBHarrayhead, dg_freefreeablelstringname);
		return;
	}
}


const char* dg_newfreeablelstringname = "dg_newfreeablelstring";

UINT64 dg_newfreeablelstring (
   Bufferhandle* pBHarrayhead,
   UINT64 freeindexbuffer)
{
	struct Freeablelstringarrayheader myflstrheader;
	
	UINT64 isfreenextfreeflag;
	UINT64 isfreenextfreeflagtemp;
	
	UINT64 freeindexbufferlength;
	UINT64 lstringoffsetbufferlength;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return((UINT64)(dg_badlstringid));
	}
	
	// check freeable lstring array buffers for correct magic id and buffer lengths
	dg_getbuffersegment(pBHarrayhead, freeindexbuffer, 0, sizeof(Freeablelstringarrayheader), (unsigned char*)(&myflstrheader));
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	if (myflstrheader.magic != dg_freeablelstringheadermagic)
	{
		dg_pusherror(pBHarrayhead, dg_badmagicerror);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	freeindexbufferlength = dg_getbufferlength(pBHarrayhead, freeindexbuffer);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	if ( ((freeindexbufferlength - sizeof(Freeablelstringarrayheader)) % sizeof(UINT64)) != 0 )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror); 
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	lstringoffsetbufferlength = dg_getbufferlength(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}	
	
	// if array corrupt throw error -- doing it this way to prevent possibility of overflow
	if (lstringoffsetbufferlength != (freeindexbufferlength - sizeof(Freeablelstringarrayheader)) )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	if ((UINT64)dg_freeablelstringlastfreeid == myflstrheader.firstfreeid)
		// or any invalid index, which is > number of lstrings
	{
		//since no lstrings are in the free list, allocate a newlstring
		dg_pushlstring(pBHarrayhead,
					   myflstrheader.lstringoffsetbufferid,
					   myflstrheader.lstringstringbufferid,
					   0,
					   (unsigned char*)"");
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
			return((UINT64)(dg_badlstringid));
		}
											 											 
		//mark the newlstring as allocated
		dg_pushbufferuint64(pBHarrayhead, 
						   freeindexbuffer,
						   (UINT64)dg_freeablelstringisnotfreeid);
		
		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_droplstring(pBHarrayhead, myflstrheader.lstringoffsetbufferid, myflstrheader.lstringstringbufferid);
			// not checking error from this droplstring because: a) we just pushed this lstring and b) we are already erroring out
			dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
			return((UINT64)(dg_badlstringid));
		}
		
		// return the new lstring index
		return (lstringoffsetbufferlength / sizeof(UINT64));
	}
	
	isfreenextfreeflag = dg_getbufferuint64(
	    pBHarrayhead,
		freeindexbuffer,
		(myflstrheader.firstfreeid * sizeof(UINT64)) + sizeof(Freeablelstringarrayheader) );
	
	if ((UINT64)dg_freeablelstringisnotfreeid == isfreenextfreeflag)
	{
		dg_pusherror(pBHarrayhead, dg_wasnottrulyfreeerror);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	// unlink lstring from free list
	// go from firstfree -> a -> b -> c -> lastfree
	
	// to firstfree -> b -> c -> lastfree
	isfreenextfreeflagtemp = myflstrheader.firstfreeid;
	myflstrheader.firstfreeid = isfreenextfreeflag;
	
	dg_putbuffersegment(pBHarrayhead, 
						freeindexbuffer, 
						0,
						sizeof(myflstrheader),
	                    (unsigned char*)(&myflstrheader));
	
	// this error can't really happen
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// but if it does then freed lstring gets leaked...  but you have a bigger problem, somehow your computer hardware lost bits :-)
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
		return((UINT64)(dg_badlstringid));
	}
	
	// and a -> isnotfree
	dg_putbufferuint64(pBHarrayhead,
					  freeindexbuffer,
					  (isfreenextfreeflagtemp * sizeof(UINT64)) + sizeof(Freeablelstringarrayheader),
					  (UINT64)dg_freeablelstringisnotfreeid);
	
	// this error can't really happen
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// we just did getbufferdword from this buffer offset and it worked so something is wrong with computer hardware
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringname);
	}

    return(isfreenextfreeflagtemp);
}


const char* dg_isfreeablelstringfreename = "dg_isfreeablelstringfree";

UINT64 dg_isfreeablelstringfree (
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64 flstringid)
{
    UINT64 isfreeflag = FORTH_TRUE;
    UINT64 bufferlength;
    UINT64 magic;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return(isfreeflag);
	}
    
    bufferlength = dg_getbufferlength(pBHarrayhead, freeindexbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_isfreeablelstringfreename);
		return(isfreeflag);
	}
    
    if (bufferlength < sizeof(Freeablelstringarrayheader))
    {
        dg_pusherror(pBHarrayhead, dg_outsideofbuffererror);       // need a better error than this, one that says flstring header is missing
        dg_pusherror(pBHarrayhead, dg_isfreeablelstringfreename);
    }
    
    // checking magic
    magic = dg_getbufferuint64(
	    pBHarrayhead,
		freeindexbuffer,
		0);
        
    if (magic != dg_freeablelstringheadermagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_isfreeablelstringfreename);
    }
    
    if ( flstringid >= ((bufferlength - sizeof(Freeablelstringarrayheader)) >> 3) )
    {
        return(isfreeflag);
    }
    
    // off end of buffer is ok since buffer can shrink when doing a free
    isfreeflag = dg_getbufferuint64(
	    pBHarrayhead,
		freeindexbuffer,
		(flstringid << 3) + sizeof(Freeablelstringarrayheader) );
        
    if (isfreeflag != (UINT64)dg_freeablelstringisnotfreeid)
    {
        isfreeflag = FORTH_TRUE;
    }
    else
    {
        isfreeflag = FORTH_FALSE;
    }
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_isfreeablelstringfreename);
	}

    return(isfreeflag);
}


const char* dg_getsflstrheadername = "dg_getsflstrheader";

Freeablelstringarrayheader* dg_getsflstrheader(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64* pflstrheaderlength)
{
    Freeablelstringarrayheader* pflstrheader = (Freeablelstringarrayheader*)badbufferhandle;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return(pflstrheader);
	}
    
    pError = dg_putuint64(pflstrheaderlength, (UINT64)sizeof(Freeablelstringarrayheader));
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getsflstrheadername);
        return(pflstrheader);
    }
    
    pflstrheader = (Freeablelstringarrayheader*)dg_getpbuffersegment (
        pBHarrayhead,
        freeindexbuffer,
        0,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getsflstrheadername);
    }
    
    return(pflstrheader);
}


const char* dg_copyflstrheadertosname = "dg_copyflstrheadertos";

void dg_copyflstrheadertos(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    Freeablelstringarrayheader* pflstrheader,
    UINT64 flstrheaderlength)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
    
    dg_getbuffersegment (
        pBHarrayhead,
        freeindexbuffer,
        0,
        flstrheaderlength,
        (unsigned char*)pflstrheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copyflstrheadertosname);
        return;
    }
    
    if (pflstrheader->magic != dg_freeablelstringheadermagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_copyflstrheadertosname);
        return;
    }
}


const char* dg_insertsintoflstrnname = "dg_insertsintoflstrn";

void dg_insertsintoflstrn(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64 flstringid,
    UINT64 offset,
    unsigned char* psrc,
    UINT64 length)
{
    struct Freeablelstringarrayheader myflstrheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}

    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbuffer,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_insertsintoflstrnname);
        return;
    }
    
    dg_insertinlstring (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		flstringid,
        offset,
        length);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_insertsintoflstrnname);
        return;
    }
    
    dg_copystolstringn (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		flstringid,
        offset,
        psrc,
        length);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_insertsintoflstrnname);
    }
}


const char* dg_copysfromflstrnname = "dg_copysfromflstrn";

void dg_copysfromflstrn(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64 flstringid,
    UINT64 offset,
    UINT64 length,
    unsigned char* pdest)
{
    struct Freeablelstringarrayheader myflstrheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}

    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbuffer,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copysfromflstrnname);
        return;
    }
    
    dg_copysfromlstringn (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		flstringid,
        offset,
        length,
        pdest);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copysfromflstrnname);
    }
}


//  same array will already work
//  3 cases:
//    copy to insert in same string after source segment
//      don't need to do anything special

//    copy to insert in same string in middle of source segment
//      insert either just before or after string and do two copies
//      abcdefgh -> abcdedeffgh -> (abc   defgh -> abc  deffgh -> abcdedeffgh)
//      or (abcdef   gh -> abcdedef gh -> abcdeffgh) 
//      or (abc   defgh -> abcdefdefgh -> abcdedeffgh)
//      or (abcde   fgh -> abcdede fgh -> abcdedeffgh) ** this one makes most sense - beginning is same, just need extra copy at end 

//    copy to insert in same string before source segment
//      insert at right spot and do copy from adjusted offset 
//      abcdefgh -> abdefcdefgh -> (ab   cdefgh -> abdefcdefgh)

const char* dg_copytoinsertflstrntomname = "dg_copytoinsertflstrntom";

void dg_copytoinsertflstrntom(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffern,
    UINT64 flstringnid,
    UINT64 offsetn,
    UINT64 freeindexbufferm,
    UINT64 flstringmid,
    UINT64 offsetm,
    UINT64 length)
{
    struct Freeablelstringarrayheader myflstrheadern;
    struct Freeablelstringarrayheader myflstrheaderm;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}
    
    // get source header
    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbuffern,
        &myflstrheadern,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertflstrntomname);
        return;
    }
    
    // get dest header
    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbufferm,
        &myflstrheaderm,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertflstrntomname);
        return;
    }
    
    // do copy
    dg_copytoinsertlstrntom (
        pBHarrayhead,
        myflstrheadern.lstringoffsetbufferid,
        myflstrheadern.lstringstringbufferid,
        flstringnid,
        offsetn,
        myflstrheaderm.lstringoffsetbufferid,
        myflstrheaderm.lstringstringbufferid,
        flstringmid,
        offsetm,
        length);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copytoinsertflstrntomname);
        return;
    }
}


const char* dg_deleteinflstringnname = "dg_deleteinflstringn";

void dg_deleteinflstringn(
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64 flstringid,
    UINT64 offset,
    UINT64 length)
{
    struct Freeablelstringarrayheader myflstrheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return;
	}

    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbuffer,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_deleteinflstringnname);
        return;
    }

    dg_deleteinlstring (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		flstringid,
        offset,
        length);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_deleteinflstringnname);
    }
}


const char* dg_getlengthflstringnname = "dg_getlengthflstringn";

UINT64 dg_getlengthflstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 freeindexbuffer,
    UINT64 flstringid)
{
    struct Freeablelstringarrayheader myflstrheader;
    
    UINT64 length = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return (length);
	}

    dg_copyflstrheadertos(
        pBHarrayhead,
        freeindexbuffer,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getlengthflstringnname);
        return (length);
    }
    
    length = dg_getlstringlength (
        pBHarrayhead,
        myflstrheader.lstringoffsetbufferid,
        flstringid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getlengthflstringnname);
    }
    
    return (length);
}


const char* dg_newfreeablelstringonendname = "dg_newfreeablelstringonend";

UINT64 dg_newfreeablelstringonend (
   Bufferhandle* pBHarrayhead,
   UINT64 freeindexbuffer,
   unsigned char* plstring,
   UINT64 lstringlength)
{
	struct Freeablelstringarrayheader myflstrheader;
		
	UINT64 freeindexbufferlength;
	UINT64 lstringoffsetbufferlength;
	
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return((UINT64)(dg_badlstringid));
	}
	
	// check freeable lstring array buffers for correct magic id and buffer lengths
	dg_getbuffersegment(pBHarrayhead, freeindexbuffer, 0, sizeof(Freeablelstringarrayheader), (unsigned char*)(&myflstrheader));
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}
	
	if (myflstrheader.magic != dg_freeablelstringheadermagic)
	{
		dg_pusherror(pBHarrayhead, dg_badmagicerror);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}
	
	freeindexbufferlength = dg_getbufferlength(pBHarrayhead, freeindexbuffer);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}
	
	if ( ((freeindexbufferlength - sizeof(Freeablelstringarrayheader)) % sizeof(UINT64)) != 0 )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror); 
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}
	
	lstringoffsetbufferlength = dg_getbufferlength(pBHarrayhead, myflstrheader.lstringoffsetbufferid);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}	
	
	// if array corrupt throw error -- doing it this way to prevent possibility of overflow
	if (lstringoffsetbufferlength != (freeindexbufferlength - sizeof(Freeablelstringarrayheader)) )
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
		return((UINT64)(dg_badlstringid));
	}
	
    //ignoring the free list and allocating a newlstring
    dg_pushlstring(pBHarrayhead,
        myflstrheader.lstringoffsetbufferid,
        myflstrheader.lstringstringbufferid,
        lstringlength,
        plstring);
		
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
        return((UINT64)(dg_badlstringid));
    }
											 											 
    //mark the newlstring as allocated
    dg_pushbufferuint64(pBHarrayhead, 
        freeindexbuffer,
        (UINT64)dg_freeablelstringisnotfreeid);
		
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_droplstring(pBHarrayhead, myflstrheader.lstringoffsetbufferid, myflstrheader.lstringstringbufferid);
        // not checking error from this droplstring because: a) we just pushed this lstring and b) we are already erroring out
        dg_pusherror(pBHarrayhead, dg_newfreeablelstringonendname);
        return((UINT64)(dg_badlstringid));
    }
		
    // return the new lstring index
    return (lstringoffsetbufferlength / sizeof(UINT64));
}


const char* dg_comparestolstringnname = "dg_comparestolstringn";

INT64 dg_comparestolstringn (
  Bufferhandle* pBHarrayhead,
  unsigned char* ps,
  UINT64 slength,
  UINT64 lstringoffsetbufferid, 
  UINT64 lstringstringbufferid,
  UINT64 n)
{
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;
    
    INT64 compareflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((INT64)(-2));
    }
    
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        n,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_comparestolstringnname);
        return ((INT64)(-2));
    }
    
    pError = dg_comparebytes(ps, slength, plstring, lstringlength, &compareflag);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        dg_pusherror(pBHarrayhead, dg_comparestolstringnname);
        return ((INT64)(-2));
    }
    
    return (compareflag);
}


const char* dg_deleteuint64inlstringnname = "dg_deleteuint64inlstringn";
  
void dg_deleteuint64inlstringn (
  Bufferhandle* pBHarrayhead, 
  UINT64 lstringoffsetbufferid, 
  UINT64 lstringstringbufferid,
  UINT64 lstringindex,
  UINT64 uint64toremove)
  {
    const char* pError;
    
    unsigned char* psortedkeys;
    UINT64 sortedkeyslength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return; // probably should return a bad find index
    }
    
    psortedkeys = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        &sortedkeyslength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_deleteuint64inlstringnname);
        return;
    }
    
    if ((sortedkeyslength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_deleteuint64inlstringnname);
        return;
    }
    
    // one cycle per key scan on x86 - could limit scan by doing find for beginning 
    //  and end of matching keys... current find only finds end of matching
    //  keys though
    pError = dg_scanforuint64 (
        psortedkeys, 
        &sortedkeyslength, 
        uint64toremove);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforuint64name);
        dg_pusherror(pBHarrayhead, dg_deleteuint64inlstringnname);
        return;
    }
    
    if (sortedkeyslength != ((UINT64)largestunsignedint))
    {
        dg_deleteinlstring (
            pBHarrayhead,
			lstringoffsetbufferid, // lstring holding sort key array
            lstringstringbufferid,
            lstringindex,
            sortedkeyslength << 3,
            sizeof(UINT64));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_deleteuint64inlstringnname);
            return;
        }        
    }
}


const char* dg_insertwithcfillinlstringnname = "dg_insertwithcfillinlstringn";

void dg_insertwithcfillinlstringn (
    Bufferhandle* pBHarrayhead, 
    UINT64 lstringoffsetbufferid, 
    UINT64 lstringstringbufferid,
    UINT64 lstringindex,
    UINT64 offset,
    UINT64 length,
    unsigned char cvalue)
{
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return; // probably should return a bad find index
    }
    
    dg_insertinlstring (
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        offset,
        length);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_insertwithcfillinlstringnname);
        return;
    }
        
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_insertwithcfillinlstringnname);
        return;
    }
    
    pError = dg_fillwithbyte(plstring + offset, length, (UINT64)cvalue);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_insertwithcfillinlstringnname);
        return;
    }
}

// pushes a new lstring onto the lstring stack containing
//   the packed lstring magic which is 8 bytes equal to 'packlstr"
//   followed by what the offset array is after the push
// what this means is:
//   the lstring's string buffer array
//     now contains all the information needed to recreate
//     the lstring array
//   the last UINT64 of the lstring's string buffer array
//      is the string buffer's length
//   the second to last UINT64 of the lstring's string buffer
//      array is the start offset of the packed lstring magic

const char* dg_packedlstringmagicstring = "PACK";
const UINT64 dg_packedlstringmagicstringlength = 4;

const char* dg_packlstringname = "dg_packlstring";

void dg_packlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringoffsetbufferid,
    UINT64 lstringstringbufferid)
{
    UINT64 offsetbufferlength;
    UINT64 stringbufferlength;
    
    UINT64 newoffsetbufferlength;
    UINT64 newstringbufferlength;
    
    unsigned char* pstring;
    UINT64* pstringlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    offsetbufferlength = dg_getbufferlength(
        pBHarrayhead,
        lstringoffsetbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
    
    stringbufferlength = dg_getbufferlength(
        pBHarrayhead,
        lstringstringbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
    
    // add room for new lstring's end offset
    newoffsetbufferlength = offsetbufferlength + sizeof(UINT64);
    
    // add room for magic and final offset array
    newstringbufferlength =
        stringbufferlength +
        (UINT64)dg_packedlstringmagicstringlength +
        newoffsetbufferlength;
    
    // push the string buffer's new end offset to the lstring array's offset buffer
    dg_pushbufferuint64(pBHarrayhead, lstringoffsetbufferid, newstringbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
    
    // push pack magic to the lstring array's string buffer
    dg_pushbuffersegment (
        pBHarrayhead,
        lstringstringbufferid,
        (UINT64)dg_packedlstringmagicstringlength,
        (unsigned char*)dg_packedlstringmagicstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
    
    // push final offset buffer onto string buffer
    pstring = dg_getpbuffer (
        pBHarrayhead,
        lstringoffsetbufferid,
        &pstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        lstringstringbufferid,
        *pstringlength,
        pstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packlstringname);
        return;
    }
}

const char* dg_isbufferapackedlstringname = "dg_isbufferapackedlstring";

UINT64 dg_isbufferapackedlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringstringbufferid)
{
    UINT64 magicoffset;
    
    unsigned char* pstring;
    UINT64* pstringlength;
    
    const char* pError;
    INT64 compareflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(dg_badbufferid);
    }
    
    // get s string buffer
    pstring = dg_getpbuffer (
        pBHarrayhead,
        lstringstringbufferid,
        &pstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_isbufferapackedlstringname);
        return(FORTH_FALSE);
    }
    
    // need to make sure stringbufferlength is of minimum size here
    if (*pstringlength <
        ((UINT64)dg_packedlstringmagicstringlength + sizeof(UINT64)))
    {
        return(FORTH_FALSE);
    }
    
    // check length at end of string buffer
    if ((*pstringlength) != *((UINT64*)(pstring + (*pstringlength) - sizeof(UINT64))) )
    {
        return(FORTH_FALSE);
    }
    
    // eheck empty lstring stack case
    //  packed empty lstring arrays don't have the start offset of the magic string
    //   under the buffer length at the end of the buffer
    //   instead the magic string is at the start of the buffer
    if (*pstringlength ==
        ((UINT64)dg_packedlstringmagicstringlength + sizeof(UINT64)))
    {
        magicoffset = 0;
    }
    else
    {
        magicoffset = *((UINT64*)(pstring + ((*pstringlength) - (2*sizeof(UINT64)))));
    }
    
    // need to check to make sure magic offset is in the buffer.
    //  this check assumes length of magic string is sizeof(UINT64)
    if (magicoffset >= ((*pstringlength) - sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return (dg_badbufferid);
    }
    
    pError = dg_comparebytes(
        pstring + magicoffset,
        (UINT64)dg_packedlstringmagicstringlength,
        (unsigned char*)dg_packedlstringmagicstring,
        (UINT64)dg_packedlstringmagicstringlength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_isbufferapackedlstringname);
        return (FORTH_FALSE);
    }
    
    if (compareflag != 0)
    {
        return (FORTH_FALSE);
    }
    
    return (FORTH_TRUE);
}

// unpacklstring
//  if the buffer to be unpacked is exactly the length of the magic string +
//   the length one UINT64, then this is the empty lstring stack case
//   otherwise
//  the last 2 UINT64 in the buffer to be unpacked are the magic start offset
//   and length of the buffer to be unpacked

const char* dg_unpacklstringname = "dg_unpacklstring";

UINT64 dg_unpacklstring (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringstringbufferid)
{
    UINT64 lstringoffsetbufferid;
    
    UINT64 magicoffset;
    UINT64 offsetbufferlength;
    
    unsigned char* pstring;
    UINT64* pstringlength;
    
    const char* pError;
    INT64 compareflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(dg_badbufferid);
    }
    
    // get s string buffer
    pstring = dg_getpbuffer (
        pBHarrayhead,
        lstringstringbufferid,
        &pstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return(dg_badbufferid);
    }
    
    // need to make sure stringbufferlength is of minimum size here
    if (*pstringlength <
        ((UINT64)dg_packedlstringmagicstringlength + sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_outsideofbuffererror);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return(dg_badbufferid);
    }
    
    // check length at end of string buffer
    if ((*pstringlength) != *((UINT64*)(pstring + (*pstringlength) - sizeof(UINT64))) )
    {
        dg_pusherror(pBHarrayhead, dg_lstringtopoffsetwasbad);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return(dg_badbufferid);
    }
    
    // eheck empty lstring stack case
    //  packed empty lstring arrays don't have the start offset of the magic string
    //   under the buffer length at the end of the buffer
    //   instead the magic string is at the start of the buffer
    if (*pstringlength ==
        ((UINT64)dg_packedlstringmagicstringlength + sizeof(UINT64)))
    {
        magicoffset = 0;
    }
    else
    {
        magicoffset = *((UINT64*)(pstring + ((*pstringlength) - (2*sizeof(UINT64)))));
    }
    
    // need to check to make sure magic offset is in the buffer.
    //  this check assumes length of magic string is sizeof(UINT64)
    if (magicoffset >= ((*pstringlength) - sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return (dg_badbufferid);
    }
    
    pError = dg_comparebytes(
        pstring + magicoffset,
        (UINT64)dg_packedlstringmagicstringlength,
        (unsigned char*)dg_packedlstringmagicstring,
        (UINT64)dg_packedlstringmagicstringlength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return (dg_badbufferid);
    }
    
    if (compareflag != 0)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return (dg_badbufferid);
    }
    
    offsetbufferlength =
        *pstringlength - (magicoffset + (UINT64)dg_packedlstringmagicstringlength + sizeof(UINT64));
    
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"offset buffer length ");
    // dg_writestdoutuinttodec(pBHarrayhead, offsetbufferlength);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    lstringoffsetbufferid = dg_newbuffer(
        pBHarrayhead,
        dg_defaultbuffergrowby,
        dg_defaultbuffermaxsize,
        &pError,
        FORTH_FALSE);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return(dg_badbufferid);
    }
    
    if (0 != offsetbufferlength)
    {
        // copy the offset buffer to a new buffer
        dg_pushbuffersegment (
            pBHarrayhead,
            lstringoffsetbufferid,
            offsetbufferlength,
            pstring + magicoffset + dg_packedlstringmagicstringlength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_unpacklstringname);
            return(dg_badbufferid);
        }
    }
    
    // shrink the string buffer to drop the magic, offset buffer, (and length)
    dg_shrinkbuffer (
        pBHarrayhead,
        lstringstringbufferid,
        dg_packedlstringmagicstringlength + offsetbufferlength + sizeof(UINT64),
        &pError);
    
    // can't get error here really
    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, lstringoffsetbufferid);
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_unpacklstringname);
        return(dg_badbufferid);
    }
    
    return(lstringoffsetbufferid);
}



const char dg_urlencodelstringname[] = "dg_urlencodelstring";

void dg_urlencodelstring (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringoffsetbufferid,
    UINT64 lstringstringbufferid)
// ( decodedurl$ -l$- url$ )
// everything that is not in the reserved set is changed to %xx where xx is the hex ascii code
// reserved set is alpha, numeric, and - _ ~ .  changed 4/16/2020 J.N.

{
    UINT64 src;
	UINT64 dest;
	unsigned char* pstring = NULL;

	UINT64 stringlength = 0;
	UINT64 stringstackdepth;


	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	unsigned char c;

	// need to get depth of string stack first
	stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        lstringoffsetbufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_urlencodelstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_urlencodelstringname);
		return;
	}

	pstring = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		lstringoffsetbufferid,
		lstringstringbufferid,
		stringstackdepth - 1,
		&stringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_urlencodelstringname);
        return;
	}
 
    // old way which had a bug where both <space> and + become +
	// if src = <space>, change to +, src+1, dest+1
	// if src = %, change to %25, src+3 dest+3
    // if src = /, change to %2F, src+3 dest+3
    // if src = <, change to %3C, src+3 dest+3
    // if src = >, change to %3E, src+3 dest+3
	// if src < 0x20, insert 2 1 after src, change src to %xx src+3, dest+3
    // if src >= 0x7F, insert 2 1 after src, change src to %xx src+3, dest+3
    
    // what this should be:
    //  2D left alone  -
    //  2E left alone  .
    //  30-39 left alone  numeric
    //  41-5A left alone  upper case alpha
    //  5F left alone  _
    //  61-7A left alone  lower case alpha
    //  7E left alone  ~
    
    //  everything else converted to %xx where xx is the hex ascii code...

	if (stringlength == 0)
	{
		return;
	}

	src=0; 
	dest=0;

	while (src < stringlength)
	{
		c = pstring[src];
        
        if (
            (c < 0x2D) ||
            (c == 0x2F) ||
            ((c > 0x39) && (c < 0x41)) ||
            ((c > 0x5A) && (c < 0x5F)) ||
            ((c > 0x5F) && (c < 0x61)) ||
            ((c > 0x7A) && (c < 0x7E)) ||
            (c > 0x7E)
           )
            // (c >= 0x7F) || ('%' == c) || ('/' == c) || ('<' == c) || ('>' == c) )
        {
            dg_insertinlstring (
                pBHarrayhead,
                lstringoffsetbufferid,
                lstringstringbufferid,
                stringstackdepth - 1,
                dest+1,
                2);
                    
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_urlencodelstringname);
                return;
            }
                
            pstring = (unsigned char*)dg_getplstring(
                pBHarrayhead, 
                lstringoffsetbufferid,
                lstringstringbufferid,
                stringstackdepth - 1,
                &stringlength);
                
            pstring[dest]='%';
            pstring[dest+1]= dg_digittochar(c >> 4);
            pstring[dest+2]= dg_digittochar(c & 0x0F);
            src = src + 3;
            dest = dest + 3;
        }
        
        else 
        {
            /*
            if (' ' == c)
            {
                pstring[dest]='+';
            }
            */
            
            src = src + 1;
            dest = dest + 1;
        }
	}
}


const char dg_urldecodelstringname[] = "dg_urldecodelstring";

void dg_urldecodelstring (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringoffsetbufferid,
    UINT64 lstringstringbufferid)
//                           ( url$ -l$- decodedurl$ )
//  %xx changed to character for xx hex ascii code
//  + changed to space.... leaving this in because + should be %encoded...
//   and if you see a + then it's a mistake and they must want the space...
//   in short, leaving this routine alone 4/16/2020 J.N.
{
	UINT64 src;
	UINT64 dest;
	unsigned char* pstring = NULL;

	UINT64 stringlength = 0;
	UINT64 stringstackdepth;

	UINT64 t1;
	UINT64 t2;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	unsigned char c;

	// need to get depth of string stack first
	stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        lstringoffsetbufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		//dg_pusherror(pBHarrayhead, dg_urldecodelstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		// not enough strings to do compare, will push error and push not equal
		//dg_pusherror(pBHarrayhead, dg_forthurldecodestringssunderflowerror);
		return;
	}

	pstring = (unsigned char*)dg_getplstring(
		pBHarrayhead, 
		lstringoffsetbufferid,
		lstringstringbufferid,
		stringstackdepth - 1,
		&stringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		//dg_pusherror(pBHarrayhead, dg_urldecodelstringname);
	}

	// if src = + change to <space>, src+1, dest+1
	// if src = %, try to convert using next to characters, move src+3 dest+1
	// if src = anything else, move src to dest, src+1, dest+1

	// when src hits end of string, shrink string to dest

	if (stringlength == 0)
	{
		return;
	}

	src=0; 
	dest=0;

	while (src < stringlength)
	{
		c = pstring[src];

		if (c == '+')
		{
			pstring[dest]=' ';
			src = src + 1;
			dest = dest + 1;
		}
		else
		{
			if (c != '%')
			{
		 	    pstring[dest]=c;
			    src = src + 1;
			    dest = dest + 1;
			}
			else
			{
				if ((src + 2) >= stringlength)
				{
					pstring[dest] = '-';
				}
				else
				{
					t1 = dg_chartodigitlowertoo(pstring[src+1]);
					t2 = dg_chartodigitlowertoo(pstring[src+2]);

					if ((t1 == (UINT64)largestunsignedint) || ( t2 == (UINT64)largestunsignedint))
					{
						pstring[dest] = '-';
					}
					else
					{
						pstring[dest] = t1 * 0x10 + t2;
					}
				}

				src = src + 3;
				dest = dest + 1;

			}
		}
	}

	if (dest < stringlength)
	{
		// dg_pushbufferdword(
        //    pBHarrayhead,
        //    DG_DATASTACK_BUFFERID,
        //    stringlength - dest);
        
		// dg_forthshortenstring(pBHarrayhead);
        
        dg_setlengthlstringn (
            pBHarrayhead,
            lstringoffsetbufferid,
            lstringstringbufferid,
            stringstackdepth - 1,
            dest);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            //dg_pusherror(pBHarrayhead, dg_urldecodelstringname);
            return;
        }
	}
}


void dg_stonewstring (
    Bufferhandle* pBHarrayhead,
    unsigned char* pstring,
    UINT64 stringlength)
{
    dg_pushlstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringlength,
		pstring);
}

const char* dg_stonew0stringname = "dg_stonew0string";

void dg_stonew0string (
    Bufferhandle* pBHarrayhead,
    unsigned char* pstring,
    UINT64 stringlength)
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
        stringlength,
        pstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stonew0stringname);
        return;
    }
        
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        (unsigned char*)"\x00"); // don't really need the \x00 since cstrings come with one by default
                                 // but it does make it obvious what the intent is...
                                 
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stonew0stringname);
        return;
    }
}


const char dg_pzerostringtonewstringname[] = "dg_pzerostringtonewstring";

void dg_pzerostringtonewstring(
    Bufferhandle* pBHarrayhead,
    unsigned char* pzerostring)
{
    const char* flag;
    UINT64 u1 = (UINT64)largestunsignedint;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    flag = ::dg_scanforbyte((void*)pzerostring, &u1, 0);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_pzerostringtonewstringname);
    }
    
    dg_pushlstring(pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		u1,
		pzerostring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pzerostringtonewstringname);
		return;
	}
}


const char dg_uleextendlstringntolname[] = "dg_uleextendlstringn";

void dg_uleextendlstringntol (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64 newlength)
{
    UINT64 stringbufferstartoffset;
    UINT64 lstringlength;
    const char* pError;
    unsigned char* plstring;
    UINT64 growamount;
    UINT64 insertoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // lstring stack underflow checked in this call
    stringbufferstartoffset = ::dg_getlstringstartoffset(
        pBHarrayhead,
        offsetbufferid,
        stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleextendlstringntolname);
		return;
	}

    lstringlength = ::dg_getlstringlength(pBHarrayhead, offsetbufferid, stringid);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleextendlstringntolname);
		return;
	}

	if (newlength==lstringlength)
	{
		// nothing to be done
		return;
	}

    // nothing needs to be done
	if (newlength<lstringlength)
	{
        return;
	}
 
    growamount = newlength - lstringlength;
    insertoffset = lstringlength;

    dg_insertinlstring (
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        insertoffset, 
        growamount);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleextendlstringntolname);
	}
 
    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleextendlstringntolname);
        return;
    }
    
    pError = dg_fillwithbyte(
        plstring + insertoffset, 
        growamount, 
        0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_uleextendlstringntolname);
        return;
    }   
}

const char dg_uleaddlstringntolstringnname[] = "dg_uleaddlstringntolstringn";

void dg_uleaddlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64* pcarryout)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
        return;
    }
    
    pError = dg_addbytes (
        plstringa, 
        plstringb,
        lstringlengtha,
        pcarryout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_addbytesname);
        dg_pusherror(pBHarrayhead, dg_uleaddlstringntolstringnname);
        return;
    } 
}

const char dg_uleadclstringntolstringnname[] = "dg_uleadclstringntolstringn";

void dg_uleadclstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64* pcarryinout)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
        return;
    }
    
    pError = dg_adcbytes (
        plstringa, 
        plstringb,
        lstringlengtha,
        pcarryinout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_adcbytesname);
        dg_pusherror(pBHarrayhead, dg_uleadclstringntolstringnname);
        return;
    } 
}

const char dg_ulesbblstringntolstringnname[] = "dg_ulesbblstringntolstringn";

void dg_ulesbblstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64* pborrowinout)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
        return;
    }
    
    pError = dg_sbbbytes (
        plstringa, 
        plstringb,
        lstringlengtha,
        pborrowinout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_sbbbytesname);
        dg_pusherror(pBHarrayhead, dg_ulesbblstringntolstringnname);
        return;
    } 
}

const char dg_lelshiftlstringnname[] = "dg_lelshiftlstringn";

void dg_lelshiftlstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64* pcarryout)
{
    UINT64 lstringlength;
    unsigned char* plstring;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_lelshiftlstringnname);
        return;
    }
    
    pError = dg_shlbytes ( 
        plstring,
        lstringlength,
        pcarryout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shlbytesname);
        dg_pusherror(pBHarrayhead, dg_lelshiftlstringnname);
        return;
    } 
}


const char dg_ulershiftlstringnname[] = "dg_ulershiftlstringn";

void dg_ulershiftlstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64* pcarryout)
{
    UINT64 lstringlength;
    unsigned char* plstring;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulershiftlstringnname);
        return;
    }
    
    pError = dg_shrbytes ( 
        plstring,
        lstringlength,
        pcarryout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrbytesname);
        dg_pusherror(pBHarrayhead, dg_ulershiftlstringnname);
        return;
    } 
}


const char dg_slershiftlstringnname[] = "dg_slershiftlstringn";

void dg_slershiftlstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64* pcarryout)
{
    UINT64 lstringlength;
    unsigned char* plstring;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_slershiftlstringnname);
        return;
    }
    
    pError = dg_sarbytes ( 
        plstring,
        lstringlength,
        pcarryout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_sarbytesname);
        dg_pusherror(pBHarrayhead, dg_slershiftlstringnname);
        return;
    } 
}


const char dg_lelshiftclstringnname[] = "dg_lelshiftclstringn";

void dg_lelshiftclstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64* pcarryinout)
{
    UINT64 lstringlength;
    unsigned char* plstring;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_lelshiftclstringnname);
        return;
    }
    
    pError = dg_rclbytes ( 
        plstring,
        lstringlength,
        pcarryinout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_rclbytesname);
        dg_pusherror(pBHarrayhead, dg_lelshiftclstringnname);
        return;
    } 
}


const char dg_lershiftclstringnname[] = "dg_lershiftclstringn";

void dg_lershiftclstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferid,
    UINT64 stringbufferid,
    UINT64 stringid,
    UINT64* pcarryinout)
{
    UINT64 lstringlength;
    unsigned char* plstring;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        offsetbufferid,
        stringbufferid,
        stringid,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_lershiftclstringnname);
        return;
    }
    
    pError = dg_rcrbytes ( 
        plstring,
        lstringlength,
        pcarryinout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_rcrbytesname);
        dg_pusherror(pBHarrayhead, dg_lershiftclstringnname);
        return;
    } 
}


const char dg_partialulemulu64tolstringnname[] = "dg_partialulemulu64tolstringn";

void dg_partialulemulu64tolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64* px)
{
    UINT64 n;
    const char* pError;
    UINT64 carryout = 0;
    UINT64 t = 1;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // checking memory at px
    pError = dg_getuint64(px, &n);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_partialulemulu64tolstringnname);
        return;
    }
    
    if ((n & 1) == 1)
    {
        dg_uleaddlstringntolstringn (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            &carryout);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_partialulemulu64tolstringnname);
            return;
        }
        
        if (carryout != 0)
        {
            // push a 0x01 onto the end of stringb
            dg_stotoplstring (
                pBHarrayhead,
                offsetbufferidb,
                stringbufferidb,
                1,
                (unsigned char*)&t);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_partialulemulu64tolstringnname);
                return;
            }
        }
    }
    
    *px = *px / 2;
    
    dg_lelshiftlstringn (
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &carryout);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_partialulemulu64tolstringnname);
        return;
    }
    
    if (carryout != 0)
    {
        // push a 0x01 onto the end of stringa
        dg_stotoplstring (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            1,
            (unsigned char*)&t);
                
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_partialulemulu64tolstringnname);
            return;
        }
    }
}


const char dg_ulemulu64tolstringnname[] = "dg_ulemulu64tolstringn";

void dg_ulemulu64tolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64 x)
{
    unsigned char* plstring;
    UINT64 lstringlength;
    UINT64 carryout;
    UINT64 n = x;
    const char* pError;
    UINT64 t = 1;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // set lstringb to 0
    plstring = dg_getplstring(
        pBHarrayhead,
	    offsetbufferidb,
	    stringbufferidb,
	    stringidb,
	    &lstringlength);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulemulu64tolstringnname);
        return;
    }
    
    pError = dg_fillwithbyte (
        plstring,
        lstringlength,
        0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_ulemulu64tolstringnname);
        return;
    }
    
    // while x != 0
    //  partialumulleu64tolstringn
    while (n != 0)
    {
        dg_partialulemulu64tolstringn (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            &n);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulemulu64tolstringnname);
            return;
        }
    }
    
    // copy lstringb to lstringa
    dg_copylstringntoreplacelstringn (
		pBHarrayhead,
		offsetbufferidb,
		stringbufferidb,
		stringidb,
		offsetbufferida,
		stringbufferida,
		stringida);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulemulu64tolstringnname);
        return;
    }
}


const char dg_notlstringnname[] = "dg_notlstringn";

void dg_notlstringn (
    Bufferhandle* pBHarrayhead, 
    UINT64 lstringoffsetbufferid, 
    UINT64 lstringstringbufferid,
    UINT64 lstringindex)
{
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return; // probably should return a bad find index
    }
        
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_notlstringnname);
        return;
    }
    
    pError = dg_notbytes ( 
        plstring,
        lstringlength);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_notbytesname);
        dg_pusherror(pBHarrayhead, dg_notlstringnname);
        return;
    }
}


const char dg_reverselstringnname[] = "dg_reverselstringn";

void dg_reverselstringn (
    Bufferhandle* pBHarrayhead, 
    UINT64 lstringoffsetbufferid, 
    UINT64 lstringstringbufferid,
    UINT64 lstringindex)
{
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return; // probably should return a bad find index
    }
        
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringindex,
        &lstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_reverselstringnname);
        return;
    }
    
    pError = dg_reversebytes ( 
        plstring,
        lstringlength);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_reversebytesname);
        dg_pusherror(pBHarrayhead, dg_reverselstringnname);
        return;
    }
}

const char dg_uleandlstringntolstringnname[] = "dg_uleandlstringntolstringn";

void dg_uleandlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
        return;
    }
    
    pError = dg_andbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_andbytesname);
        dg_pusherror(pBHarrayhead, dg_uleandlstringntolstringnname);
        return;
    } 
}


const char dg_uleorlstringntolstringnname[] = "dg_uleorlstringntolstringn";

void dg_uleorlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
        return;
    }
    
    pError = dg_orbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_orbytesname);
        dg_pusherror(pBHarrayhead, dg_uleorlstringntolstringnname);
        return;
    } 
}


const char dg_ulexorlstringntolstringnname[] = "dg_ulexorlstringntolstringn";

void dg_ulexorlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
        return;
    }
    
    pError = dg_xorbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_xorbytesname);
        dg_pusherror(pBHarrayhead, dg_ulexorlstringntolstringnname);
        return;
    } 
}


const char dg_ulenandlstringntolstringnname[] = "dg_ulenandlstringntolstringn";

void dg_ulenandlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
        return;
    }
    
    pError = dg_nandbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_nandbytesname);
        dg_pusherror(pBHarrayhead, dg_ulenandlstringntolstringnname);
        return;
    } 
}


const char dg_ulenorlstringntolstringnname[] = "dg_ulenorlstringntolstringn";

void dg_ulenorlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
        return;
    }
    
    pError = dg_norbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_norbytesname);
        dg_pusherror(pBHarrayhead, dg_ulenorlstringntolstringnname);
        return;
    } 
}


const char dg_ulexnorlstringntolstringnname[] = "dg_ulexnorlstringntolstringn";

void dg_ulexnorlstringntolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb)
{
    UINT64 lstringlengtha;
    UINT64 lstringlengthb;
    unsigned char* plstringa;
    unsigned char* plstringb;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengtha = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
		return;
	}
 
    lstringlengthb = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
		return;
	}   

	if (lstringlengtha < lstringlengthb)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthb);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
            return;
        }
	}
 
    if (lstringlengthb < lstringlengtha)
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            lstringlengtha);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
            return;
        }
	}   

    plstringa = dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengtha);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
        return;
    }
    
    plstringb = dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthb);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
        return;
    }
    
    pError = dg_xnorbytes (
        plstringa, 
        plstringb,
        lstringlengtha);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_xnorbytesname);
        dg_pusherror(pBHarrayhead, dg_ulexnorlstringntolstringnname);
        return;
    } 
}


const char dg_mulu64bylstringnaddtolstringnname[] = "dg_mulu64bylstringnaddtolstringn";

void dg_mulu64bylstringnaddtolstringn (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 offsetbufferidb,
    UINT64 stringbufferidb,
    UINT64 stringidb,
    UINT64 u)
{
    UINT64 lstringlengthainbytes;
    UINT64 lstringlengthbinbytes;
    UINT64 lstringlengthainu64s;
    UINT64 lstringlengthbinu64s;
    UINT64* plstringa; // src
    UINT64* plstringb; // dest
    const char* pError;
    UINT64 carryout;
    UINT64 x = 1;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengthainbytes = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
		return;
	}
 
    lstringlengthainu64s = dg_getnearesthighestmultiple (
        lstringlengthainbytes,
        sizeof(UINT64)) / sizeof(UINT64);
 
    lstringlengthbinbytes = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferidb, 
        stringidb);
        
    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
		return;
	}
        
    lstringlengthbinu64s = dg_getnearesthighestmultiple (
        lstringlengthbinbytes,
        sizeof(UINT64)) / sizeof(UINT64);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
		return;
	}
 
    // align lstring to a multiple of sizeof(u64) if needed
    if (lstringlengthainbytes < lstringlengthainu64s * sizeof(UINT64))
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferida,
            stringbufferida,
            stringida,
            lstringlengthainu64s * sizeof(UINT64));
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
            return;
        }
	}   
 
    // destination length must be at least 1 more than source length
    if (lstringlengthbinbytes < ((lstringlengthainu64s + 1)*sizeof(UINT64)))
	{
		dg_uleextendlstringntol (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            ((lstringlengthainu64s + 1)*sizeof(UINT64)));
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
            return;
        }
	}   

    plstringa = (UINT64*)dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengthainbytes);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
        return;
    }
    
    plstringb = (UINT64*)dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthbinbytes);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
        return;
    }
    
    pError = dg_mulu64tou64s (
        plstringb,
        plstringa, 
        u,
        lstringlengthainu64s,
        &carryout);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_mulu64tou64sname);
        dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
        return;
    }
    
    if (0 == carryout)
    {
        return;
    }
    
    if (lstringlengthainu64s + 1 == lstringlengthbinu64s)
    {
        // push a 1 onto the end of lstringb
        dg_pushstolstringn (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            (unsigned char*)&x,
            sizeof(UINT64));
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
            return;
        }
        
        return;
    }
    
    // inc the rest of the string
    
    plstringb = (UINT64*)dg_getplstring(
        pBHarrayhead,
        offsetbufferidb,
        stringbufferidb,
        stringidb,
        &lstringlengthbinbytes);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
        return;
    }
    
    // if I had a dg_incu64s, I could use that instead
    pError = dg_incbytes ( 
        (unsigned char*)plstringb + lstringlengthainbytes + sizeof(UINT64),
        lstringlengthbinbytes - (lstringlengthainbytes + sizeof(UINT64)), 
        &carryout);
        
    if (carryout != 0)
    {
        // push a 1 onto the end of lstringb
        dg_pushstolstringn (
            pBHarrayhead,
            offsetbufferidb,
            stringbufferidb,
            stringidb,
            (unsigned char*)&x,
            sizeof(UINT64));
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_mulu64bylstringnaddtolstringnname);
            return;
        }
    }
}



const char dg_divlstringnbyu64name[] = "dg_divlstringnbyu64";

void dg_divlstringnbyu64 (
    Bufferhandle* pBHarrayhead,
    UINT64 offsetbufferida,
    UINT64 stringbufferida,
    UINT64 stringida,
    UINT64 u,
    UINT64* premainder)
{
    UINT64 lstringlengthainbytes;
    UINT64 lstringlengthainu64s;
    UINT64* plstringa; // dest
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lstringlengthainbytes = dg_getlstringlength(
        pBHarrayhead, 
        offsetbufferida, 
        stringida);

    if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_divlstringnbyu64name);
		return;
	}
 
    lstringlengthainu64s = dg_getnearesthighestmultiple (
        lstringlengthainbytes,
        sizeof(UINT64)) / sizeof(UINT64);
 
    dg_uleextendlstringntol (
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        lstringlengthainu64s * sizeof(UINT64));
            
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_divlstringnbyu64name);
        return;
    }

    plstringa = (UINT64*)dg_getplstring(
        pBHarrayhead,
        offsetbufferida,
        stringbufferida,
        stringida,
        &lstringlengthainbytes);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_divlstringnbyu64name);
        return;
    }
    
    pError = dg_divu64sbyu64 (
        plstringa,
        premainder, 
        u,
        lstringlengthainu64s);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_divu64sbyu64name);
        dg_pusherror(pBHarrayhead, dg_divlstringnbyu64name);
        return;
    }
}

