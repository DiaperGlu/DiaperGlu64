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


void dg_forthocfetch (Bufferhandle* pBHarrayhead)
//     ( offset bufferid -- byte )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char c;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthocfetchname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthocfetchname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    // FreeBSD core dumps if I cast the returned byte as a UINT64 so doing it in 2 steps
    //pints[0] = (UINT64)dg_getbufferbyte(pBHarrayhead, pints[1], pints[0]);

    c = dg_getbufferbyte(
        pBHarrayhead,
        pints[1],
        pints[0]);
    
    pints[0] = (UINT64)c;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthocfetchname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthofetch (Bufferhandle* pBHarrayhead)
//     ( offset bufferid -- dword)
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthofetchname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthofetchname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_getbufferuint64(
        pBHarrayhead,
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthofetchname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthostonewstring (Bufferhandle* pBHarrayhead)
//     ( offset bufferid length -- )
//     ( -$- string )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    unsigned char* pbuffersegment = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthostonewstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthostonewstringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 3*sizeof(UINT64));

    pbuffersegment = dg_getpbuffersegment(
        pBHarrayhead,
        pints[1],
        pints[0],
        pints[2]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthostonewstringname);
        return;
    }

    dg_pushlstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        pints[2], 
        pbuffersegment);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthostonewstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthocstore (Bufferhandle* pBHarrayhead)
//     ( byte offset bufferid -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthocstorename);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthocstorename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_putbufferbyte(
        pBHarrayhead,
        pints[2],
        pints[1],
        (unsigned char)pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthocstorename);
        return;
    }

    *pbuflength -= (3 * sizeof(UINT64));
}


void dg_forthostore (Bufferhandle* pBHarrayhead)
//     ( dword offset bufferid -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthostorename);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthostorename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_putbufferuint64(
        pBHarrayhead,
        pints[2],
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthostorename);
        return;
    }

    *pbuflength -= (3 * sizeof(UINT64));
}


void dg_forthotwostore (Bufferhandle* pBHarrayhead)
//     ( u128lo u128hi offset bufferid -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthotwostorename);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthotwostorename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_putbufferuint64(
        pBHarrayhead,
        pints[3],
        pints[2] + sizeof(UINT64),
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthotwostorename);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        pints[3],
        pints[2],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthotwostorename);
        return;
    }

    *pbuflength -= (4 * sizeof(UINT64));
}


void dg_forthctobuf (Bufferhandle* pBHarrayhead)
//     ( byte bufferid -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthctobufname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthctobufname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_pushbufferbyte(
        pBHarrayhead,
        pints[1],
        (unsigned char)pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthctobufname);
        return;
    }

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthtobuf (Bufferhandle* pBHarrayhead)
//     ( uint64 bufferid -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtobufname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtobufname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_pushbufferuint64(
        pBHarrayhead,
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtobufname);
        return;
    }

    *pbuflength -= (2 * sizeof(UINT64));
    
}


void dg_forthstringtobuf (Bufferhandle* pBHarrayhead)
//     ( bufferid -- )
//     ( string -$- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    unsigned char* plstring = NULL;
    UINT64 length = 0;
    UINT64 numberofstrings = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    numberofstrings = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    if (numberofstrings == 0)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    plstring = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        numberofstrings - 1,
        &length);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        pints[0],
        length,
        plstring);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    dg_droplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtobufname);
        return;
    }

    *pbuflength -= sizeof(UINT64);
}


void dg_forthbuftoc (Bufferhandle* pBHarrayhead)
//     ( bufferid -- byte )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    unsigned char c;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftocname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftocname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    //pints[0] = (UINT64)dg_popbufferbyte(pBHarrayhead, pints[0]);
    c = dg_popbufferbyte(
        pBHarrayhead,
        pints[0]);
    
    pints[0] = (UINT64)c;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftocname);
        return;
    }
}


void dg_forthbufto (Bufferhandle* pBHarrayhead)
//                   ( bufferid -- dword )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftoname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftoname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = dg_popbufferuint64(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftoname);
        return;
    }
}


void dg_forthbuftostring (Bufferhandle* pBHarrayhead)
//     ( bufferid length -- )
//     ( -$- string )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 bufferlength = 0;
    unsigned char* pbuffersegment = NULL;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    if (pints[1] > bufferlength)
    {
        dg_pusherror(pBHarrayhead, dg_bufferunderflow);
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    pbuffersegment = dg_getpbuffersegment(
        pBHarrayhead,
        pints[0],
        bufferlength - pints[1],  
        pints[1]); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        pints[1],
        pbuffersegment); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    dg_shrinkbuffer(
        pBHarrayhead,
        pints[0],
        pints[1],
        &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftostringname);
        return;
    }

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthosstore (Bufferhandle* pBHarrayhead)
//     ( offset bufferid length pdest -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosstorename);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosstorename);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_getbuffersegment(
        pBHarrayhead,
        pints[1],
        pints[0],
        pints[2],
        (unsigned char*)pints[3]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosstorename);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthosfetch (Bufferhandle* pBHarrayhead)
//     ( psrc offset bufferid length -- )
{
    UINT64* pbuflength = NULL; 
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosfetchname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosfetchname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_putbuffersegment(
        pBHarrayhead,
        pints[2],
        pints[1],
        pints[3],
        (unsigned char*)pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosfetchname);
        return;
    }

    // check for error here?

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthstobuf (Bufferhandle* pBHarrayhead)
//     ( psrc length bufferid -- )  // should be psrc bufferid length?
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstobufname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstobufname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_pushbuffersegment(
        pBHarrayhead,
        pints[2],
        pints[1],
        (unsigned char*)pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstobufname);
        return;
    }

    // check for error here?

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthbuftos (Bufferhandle* pBHarrayhead)
//     ( bufferid pdest length -- );
{
    UINT64* pbuflength = NULL; 
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftosname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftosname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_popbuffersegment(
        pBHarrayhead,
        pints[0],
        pints[2],
        (unsigned char*)pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftosname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthlengthbuf (Bufferhandle* pBHarrayhead)
//     ( bufferid -- bufferlength )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlengthbufname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlengthbufname);
        return;
    }

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    // could check for misaligned data stack pointer here

    pints[0] = dg_getbufferlength(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlengthbufname);
        return;
    }
}


void dg_forthgetsbufferhandlearrayhead (Bufferhandle* pBHarrayhead)
//     ( -- pBHarrayhead sizeofBufferhandle )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlearrayheadname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        sizeof(Bufferhandle));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlearrayheadname);
        return;
    }
}


void dg_forthgetsbufferhandle (Bufferhandle* pBHarrayhead)
//     ( bufferid -- pBufferheader sizeofBufferhandle )
{
    UINT64* pbuflength; 
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 pbufferhandle;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlename);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlename);
        return;
    }

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    // could check for misaligned data stack pointer here

    // FreeBSD can't handle this in one step, so doing it in 2
    //pints[0] = (UINT64)dg_getpbufferhandle(pBHarrayhead, pints[0]);
    pbufferhandle = (UINT64)dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);
    
    pints[0] = pbufferhandle;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        sizeof(Bufferhandle));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbufferhandlename);
        return;
    }
}


void dg_forthgetoarrayelement (Bufferhandle* pBHarrayhead)
//     ( elementindex bufferid elementsize -- oarrayelement )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    unsigned char* pbuffer = NULL;
    UINT64* pbufferlength = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetoarrayelementname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetoarrayelementname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        pints[1],
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetoarrayelementname);
        return;
    }

    if ((pints[0]) >= *pbufferlength / (pints[2]))  
    {
        //index is off end - should we return -1 on datastack or leave data stack unchanged?
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthgetoarrayelementname);

        pints[0] = (UINT64)largestunsignedint;

        *pbuflength = *pbuflength - (2 * sizeof(UINT64));

        return;
    }

    pints[0] = pints[0] * pints[2];

    // check for error here?

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthgetparrayelement (Bufferhandle* pBHarrayhead)
//     ( elementindex bufferid elementsize-- parrayelement )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack;

    UINT64* pints = NULL;

    unsigned char* pbuffer = NULL;
    UINT64* pbufferlength = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetparrayelementname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetparrayelementname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        pints[1],
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetparrayelementname);
        return;
    }

    if ((pints[0]) >= *pbufferlength / (pints[2]))
    {
        //index is off end - should we return -1 on datastack or leave data stack unchanged?
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthgetparrayelementname);

        pints[0] = 0; // NULL

        *pbuflength = *pbuflength - (2 * sizeof(UINT64));

        return;
    }

    pints[0] = (UINT64)(pbuffer + (pints[0] * pints[2]));

    // check for error here?

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthgetbuffersize (Bufferhandle* pBHarrayhead)
//     ( bufferid -- buffersize )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffersizename);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetbuffersizename);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffersizename);
        return;
    }
    
    pints[0] = (UINT64)(pBH->size);
}


void dg_forthgetbuffermaxsize (Bufferhandle* pBHarrayhead)
//     ( bufferid -- buffermaxsize )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffermaxsizename);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetbuffermaxsizename);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffermaxsizename);
        return;
    }
    
    pints[0] = (UINT64)(pBH->maxsize);
    
}


void dg_forthgetbuffergrowby (Bufferhandle* pBHarrayhead)
//     ( bufferid -- buffergrowby )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffergrowbyname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetbuffergrowbyname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffergrowbyname);
        return;
    }
    
    pints[0] = (UINT64)(pBH->growby);
}


void dg_forthgetbuffercurrentoffset (Bufferhandle* pBHarrayhead)
//     ( bufferid -- buffercurrentoffset )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffercurrentoffsetname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetbuffercurrentoffsetname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetbuffercurrentoffsetname);
        return;
    }
    
    pints[0] = (UINT64)(pBH->currentoffset);
}


void dg_forthputbuffercurrentoffset (Bufferhandle* pBHarrayhead)
//     ( currentoffset bufferid -- )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthputbuffercurrentoffsetname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthputbuffercurrentoffsetname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthputbuffercurrentoffsetname);
        return;
    }
    
    if (pints[0] <= pBH->nextunusedbyte)
    {
        pBH->currentoffset = pints[0];
    }
    else
    {
        pBH->currentoffset = pBH->nextunusedbyte;
    }

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthgetpbufferlength (Bufferhandle* pBHarrayhead)
//     ( bufferid -- pbufferlength )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferlengthname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferlengthname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferlengthname);
        return;
    }
    
    pints[0] = (UINT64)(&(pBH->nextunusedbyte));
}


void dg_forthgetpbuffercurrentoffset (Bufferhandle* pBHarrayhead)
//     ( bufferid -- pbuffercurrentoffset )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffercurrentoffsetname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffercurrentoffsetname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pBH = dg_getpbufferhandle(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffercurrentoffsetname);
        return;
    }
    
    pints[0] = (UINT64)(&(pBH->currentoffset));
}


void dg_forthinsertinbuffer (Bufferhandle* pBHarrayhead)
//     ( offset bufferid length -- )  // ***!!!*** this should be length offset bufferid
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertinbuffername);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthinsertinbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_insertinbuffer(
        pBHarrayhead,
        pints[1],
        pints[0],
        pints[2]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertinbuffername);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
    
}


void dg_forthdeleteinbuffer (Bufferhandle* pBHarrayhead)
//     ( offset bufferid length -- )  // ***!!!*** this should be length offset bufferid
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeleteinbuffername);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdeleteinbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_deleteinbuffer(
        pBHarrayhead,
        pints[1],
        pints[0],
        pints[2]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeleteinbuffername);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthreplaceinbuffer (Bufferhandle* pBHarrayhead)
//     ( psrc srclength destoffset destbufferid destlength -- )  
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthreplaceinbuffername);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthreplaceinbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    dg_replacebuffersegment (
        pBHarrayhead,
        pints[3],   // bufferid,
        pints[2],   // destoffset,
        pints[4],   // destlength,
        (unsigned char*)(pints[0]),   // psrc,
        pints[1]);  // srclength)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthreplaceinbuffername);
        return;
    }

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}

void dg_forthinsertsintobuffer (Bufferhandle* pBHarrayhead)
//     ( psrc srclength destoffset destbufferid -- )  
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertsintobuffername);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthinsertsintobuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_replacebuffersegment (
        pBHarrayhead,
        pints[3],   // bufferid,
        pints[2],   // destoffset,
        0,   // destlength,
        (unsigned char*)(pints[0]),   // psrc,
        pints[1]);  // srclength)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertsintobuffername);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}

void dg_forthgrowbuffer (Bufferhandle* pBHarrayhead)
//     ( length bufferid -- )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgrowbuffername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgrowbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_growbuffer(
        pBHarrayhead,
        pints[1],
        pints[0],
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthgrowbuffername);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthshrinkbuffer (Bufferhandle* pBHarrayhead)
//     ( length bufferid -- )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshrinkbuffername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthshrinkbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_shrinkbuffer(
        pBHarrayhead,
        pints[1],
        pints[0],
        &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_forthshrinkbuffername);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthemptybuffer (Bufferhandle* pBHarrayhead)
//     ( bufferid -- )
{
    UINT64 bufferid = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthemptybuffername);
        return;
    }

    dg_clearbuffer(
        pBHarrayhead,
        bufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthemptybuffername);
        return;
    }
}


void dg_forthnewbuffer (Bufferhandle* pBHarrayhead)
//     ( growby maxsize -- bufferid )
{
    UINT64* pbuflength = NULL; // why didn't I call this pdatastacklength? too long?
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewbuffername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_newbuffer(
        pBHarrayhead,
        pints[0],
        pints[1],
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_forthnewbuffername);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthfreebuffer (Bufferhandle* pBHarrayhead)
//     ( bufferid -- )
{
    UINT64 bufferid = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreebuffername);
        return;
    }

    if (bufferid <= dg_lastdiaperglubufferid)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisfordglubuffer);
        dg_pusherror(pBHarrayhead, dg_forthfreebuffername);
        return;
    }

    dg_freebuffer(
        pBHarrayhead,
        bufferid);

    // no errors returned from dg_freebuffer (for now)
}


void dg_forthgetpbufferoffset (Bufferhandle* pBHarrayhead)
//     ( offset bufferid -- address )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    UINT64 pbufferoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferoffsetname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferoffsetname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    // FreeBSD can't handle this in one step so doing it in two - probably a compiler flag setting
    //pints[0] = (UINT64)dg_getpbufferoffset(pBHarrayhead, pints[1], pints[0]);
    pbufferoffset = (UINT64)dg_getpbufferoffset(
        pBHarrayhead,
        pints[1],
        pints[0]);
    
    pints[0] = pbufferoffset;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbufferoffsetname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthgetpbuffer (Bufferhandle* pBHarrayhead)
//     ( bufferid -- pbuffer plength )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 bufferid = 0;
    unsigned char* pbuffer = NULL;
    UINT64* plength = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffername);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    bufferid = pints[0];

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &plength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffername);
    }

    pints[0] = (UINT64)pbuffer;

    olderrorcount = dg_geterrorcount(pBHarrayhead); // has to be here because there could be an error from dg_getpbuffer
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)plength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffername);
    }
}


void dg_forthgetsbuffer (Bufferhandle* pBHarrayhead)
//               ( bufferid -- pbuffer length )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 bufferid = 0;
    unsigned char* pbuffer = NULL;
    UINT64* plength = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbuffername);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetsbuffername);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    bufferid = pints[0];

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &plength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getpbuffername);
        dg_pusherror(pBHarrayhead, dg_forthgetsbuffername);
        // need to exit to prevent dereferencing of invalid plength pointer
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);
        return;
    }

    pints[0] = (UINT64)pbuffer;

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        *plength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetsbuffername);
    }
}


void dg_forthgetpbuffersegment (Bufferhandle* pBHarrayhead)
//     ( offset bufferid length -- address )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    UINT64 pbuffersegment;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffersegmentname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffersegmentname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    //pints[0] = (UINT64)dg_getpbuffersegment(pBHarrayhead, pints[1], pints[0], pints[2]);
    pbuffersegment = (UINT64)dg_getpbuffersegment(
        pBHarrayhead,
        pints[1],
        pints[0],
        pints[2]);

    pints[0] = pbuffersegment;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpbuffersegmentname);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthmaxusedbuffers (Bufferhandle* pBHarrayhead)
{
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle) );
}


void dg_forthinusebuffers (Bufferhandle* pBHarrayhead)
{
    UINT64 bharraydepth = 0;

    UINT64 i = 0;
    UINT64 nob = 0;
    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;

    bharraydepth = pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle);

    for (i = 0; i < bharraydepth; i++)
    {
        pBH = &( ( (Bufferhandle*)(pBHarrayhead->pbuf) )[i] );

        if (pBH->pbuf != (Bufferhandle*)badbufferhandle)
        {
            nob++;
        }
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        nob);
}


void dg_forthinusebytes (Bufferhandle* pBHarrayhead)
{
    UINT64 bharraydepth = 0;

    UINT64 i = 0;
    UINT64 tiub = 0;
    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;

    bharraydepth = pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle);

    for (i = 0; i < bharraydepth; i++)
    {
        pBH = &( ( (Bufferhandle*)(pBHarrayhead->pbuf) )[i] );

        if (pBH->pbuf != (Bufferhandle*)badbufferhandle)
        {
            tiub += pBH->nextunusedbyte; // probably be a good idea to check for overflow
        }
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        tiub);
}


void dg_forthallocatedbytes (Bufferhandle* pBHarrayhead)
{
    UINT64 bharraydepth = 0;

    UINT64 i = 0;
    UINT64 tab = 0;
    Bufferhandle* pBH = (Bufferhandle*)badbufferhandle;

    bharraydepth = pBHarrayhead->nextunusedbyte / sizeof (Bufferhandle);

    for (i = 0; i < bharraydepth; i++)
    {
        pBH = &( ( (Bufferhandle*)(pBHarrayhead->pbuf) )[i] );

        if (pBH->pbuf != (Bufferhandle*)badbufferhandle)
        {
            tab += pBH->size; // probably be a good idea to check for overflow
        }
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        tab);
}


void dg_forthcscanbuf (Bufferhandle* pBHarrayhead)
//                    ( bufferid offset value -- index )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 bufferid;
    UINT64 offset;
    unsigned char* caddr1 = NULL;
    UINT64* pu1;
    UINT64 u1 = 0;
    UINT64 value = 0;

    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcscanbufname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcscanbufname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    bufferid = (UINT64)(pints[0]);
    offset = (UINT64)(pints[1]);
    value =  (UINT64)(pints[2]);

    caddr1 = (unsigned char*)dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pu1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcscanbufname);
    }

    u1 = *pu1;

    if (offset < u1)
    {
        u1 = u1 - offset;
        caddr1 = caddr1 + offset;

        flag = dg_scanforbyte(
            (void*)caddr1,
            &u1,
            value);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_forthcscanbufname);
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

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthscanbuf (Bufferhandle* pBHarrayhead)
//     ( bufferid offset value -- index )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 bufferid;
    UINT64 offset;
    unsigned char* caddr1 = NULL;
    UINT64* pu1;
    UINT64 u1 = 0;
    UINT64 value = 0;

    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscanbufname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthscanbufname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    bufferid = (UINT64)(pints[0]);
    offset = (UINT64)(pints[1]);
    value =  (UINT64)(pints[2]);

    caddr1 = (unsigned char*)dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pu1);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscanbufname);
    }

    u1 = (*pu1) / sizeof(UINT64);

    if (offset < u1)
    {
        u1 = u1 - offset;
        caddr1 = caddr1 + (offset * sizeof(UINT64));

        flag = dg_scanforuint64(
            (void*)caddr1,
            &u1,
            value);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_forthscanbufname);
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

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthshowbuffers(Bufferhandle* pBHarrayhead)
{
    UINT64 i;
    
    UINT64 n = pBHarrayhead->nextunusedbyte / sizeof(Bufferhandle);
    
    Bufferhandle* pBuffers = (Bufferhandle*)(pBHarrayhead->pbuf);
    
    if (NULL == pBuffers)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nno buffers\n\n");
        return;
    }
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\naddr userlength oslength endaddress\n\n");
    
    for (i = 0; i < n; i++)
    {
        dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)pBuffers[i].pbuf);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"   ");
        dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)pBuffers[i].nextunusedbyte);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"   ");
        dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)pBuffers[i].size);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"   ");
        dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)(pBuffers[i].pbuf) + ((UINT64)pBuffers[i].size));
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    }
}

void dg_forthgetpnewbuffer(Bufferhandle* pBHarrayhead)
{
    unsigned char* pnewbuffer;
    UINT64 bufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    bufferlength = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpnewbuffername);
        return;
    }

    pnewbuffer = dg_getpnewbuffer(
        pBHarrayhead,
        bufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpnewbuffername);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pnewbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetpnewbuffername);
        return;
    }
}

void dg_forthu16store (Bufferhandle* pBHarrayhead)
//     ( u addr -- )
{
    UINT16* address = NULL;
    UINT16 data = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthu16storename);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        *plength = 0;
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu16storename);
        return;
    }

    data = *((UINT16*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT16**)(pbuffer + *plength - (sizeof(UINT64))));

    (*plength) -= (2*sizeof(UINT64));

    perror = dg_putuint16(
        address,
        data);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint16name);
        dg_pusherror(pBHarrayhead, dg_forthu16storename);
    }
}

void dg_forthu32store (Bufferhandle* pBHarrayhead)
//     ( u addr -- )
{
    UINT32* address = NULL;
    UINT32 data = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthu32storename);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        *plength = 0;
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu32storename);
        return;
    }

    data = *((UINT32*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT32**)(pbuffer + *plength - (sizeof(UINT64))));

    (*plength) -= (2*sizeof(UINT64));

    perror = dg_putuint32(
        address,
        data);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint32name);
        dg_pusherror(pBHarrayhead, dg_forthu32storename);
    }
}

void dg_forthu16fetch (Bufferhandle* pBHarrayhead)
//         ( address -- data )
{
    UINT16* address = NULL;
    UINT16 n1 = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthu16fetchname);
        return;
    }

    if (*plength < 1 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu16fetchname);
        return;
    }

    address = *((UINT16**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_getuint16(
        address,
        &n1);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getuint16name);
        dg_pusherror(pBHarrayhead, dg_forthu16fetchname);
    }

    *((UINT64*)(pbuffer + *plength - (sizeof(UINT64)) )) = n1;
}

void dg_forthu32fetch (Bufferhandle* pBHarrayhead)
//         ( address -- data )
{
    UINT32* address = NULL;
    UINT32 n1 = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthu32fetchname);
        return;
    }

    if (*plength < 1 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu32fetchname);
        return;
    }

    address = *((UINT32**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_getuint32(
        address,
        &n1);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getuint32name);
        dg_pusherror(pBHarrayhead, dg_forthu32fetchname);
    }

    *((UINT64*)(pbuffer + *plength - (sizeof(UINT64)) )) = n1;
}


void dg_forthof64store (Bufferhandle* pBHarrayhead)
//     ( offset bufferid -- ) ( x -f64- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

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

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthof64storename);
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthof64storename);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthof64storename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_putbufferuint64(
        pBHarrayhead,
        pints[0],
        pints[1],
        x);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthof64storename);
        return;
    }

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthubufalign (Bufferhandle* pBHarrayhead)
//     ( u bufferid -- ) 
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthubufalignname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthubufalignname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_ubufferalign(
        pBHarrayhead,
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthubufalignname);
        return;
    }

    *pbuflength -= (2 * sizeof(UINT64));
}



