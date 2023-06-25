// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.12.
//
//    DiaperGlu v5.12 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.12 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.12; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 24, 2023              //
// version 5.12               //
// /////////////////////////////



#include "diapergluforth.h"


void dg_forthdepthlstring(Bufferhandle* pBHarrayhead)
//                              ( stringoffsetbufferid -- n );
//                              ( endoffset$1 endoffset$2 ... endoffset$n -offsetbuffer- 
//                                  endoffset$1 endoffset$2 ... endoffset$n ) 
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

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdepthlstringname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdepthlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    // FreeBSD can't do this in one step, so doing it in two.
    pints[0] = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        pints[0]);
    
    //depth = dg_getnumberoflstringsonstack(pBHarrayhead, pints[0]);
    //pints[0] = depth;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdepthlstringname);
        return;
    }
}


void dg_forthstartoffsetlstring (Bufferhandle *pBHarrayhead)
//                          ( stringid stringoffsetbufferid -- lstringstartoffset )
//                          ( endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n -offsetbuffer- 
//                              endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthstartoffsetlstringname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstartoffsetlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_getlstringstartoffset(
        pBHarrayhead,
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstartoffsetlstringname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthlengthlstring (Bufferhandle *pBHarrayhead)
//                     ( stringid stringoffsetbufferid -- lstringlength )
//                          ( endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n -offsetbuffer- 
//                              endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n )                     
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlengthlstringname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlengthlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_getlstringlength(
        pBHarrayhead,
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlengthlstringname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthgetslstringn(Bufferhandle* pBHarrayhead)
//               ( stringid offsetbufferid stringbufferid -- plstring lstringlength )
//               ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $stringid ... $n )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    unsigned char* plstring;
    UINT64 lstringlength;

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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetslstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetslstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    plstring = dg_getplstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0],
        &lstringlength);

    pints[0] = (UINT64)plstring;
    pints[1] = lstringlength;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetslstringnname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthgetlstring (Bufferhandle* pBHarrayhead)
//               ( stringid offsetbufferid stringbufferid pdest maxlength -- ) // may need length returned
//               ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $stringid ... $n )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetlstringname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    dg_getlstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0],
        pints[4],
        (unsigned char*)(pints[3]));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgetlstringname);
        return;
    }

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}


void dg_forthlstringtos (Bufferhandle* pBHarrayhead)
//               ( offsetbufferid stringbufferid pdest maxlength -- )
//               ( l$ -offsetbuffer&stringbuffer- )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlstringtosname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlstringtosname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_poplstring(
        pBHarrayhead,
        pints[0],
        pints[1],
        pints[3],
        (unsigned char*)(pints[2]));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlstringtosname);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthstolstring (Bufferhandle* pBHarrayhead)
//                ( psrc length offsetbufferid stringbufferid -- )
//                ( -offsetbuffer&stringbuffer- l$ )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthstolstringname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstolstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_pushlstring(
        pBHarrayhead,
        pints[2],
        pints[3],
        pints[1],
        (unsigned char*)(pints[0]));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstolstringname);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthgrowlstring (Bufferhandle* pBHarrayhead)
//                ( n offsetbufferid stringbufferid -- )
//                ( L$ -offsetbuffer&stringbuffer- L$' )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgrowlstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgrowlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_growlstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgrowlstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthpicklstring (Bufferhandle* pBHarrayhead)
//                ( n offsetbufferid stringbufferid -- )
//                ( -offsetbuffer&stringbuffer- L$ )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthpicklstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthpicklstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_picklstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpicklstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthdroplstring (Bufferhandle* pBHarrayhead)
//                ( offsetbufferid stringbufferid -- )
//                ( l$ -offsetbuffer&stringbuffer- )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdroplstringname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdroplstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_droplstring(
        pBHarrayhead,
        pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdroplstringname);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthdeletelstring (Bufferhandle* pBHarrayhead)
//                  ( stringid offsetbufferid stringbufferid -- )
//                  ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $n )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdeletelstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdeletelstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_deletelstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeletelstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthinsertlstring (Bufferhandle* pBHarrayhead)
//                ( length n offsetbufferid stringbufferid -- )
//                ( L$0 L$1 L$2 ... L$N ... L$TOP -offsetbuffer&stringbuffer- 
//                    L$0 L$1 L$2 ... copyL$psrc L$N ... L$TOP )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthinsertlstringname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthinsertlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_insertlstring(
        pBHarrayhead,
        pints[2],
        pints[3],
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertlstringname);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthcscanlstring (Bufferhandle* pBHarrayhead)
//  ( l$offsetbufferid l$stringbufferid l$stackindex offset value -- offset' )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 offset;
    unsigned char* caddr1 = NULL;

    UINT64 u1 = 0;
    UINT64 value = 0;
    UINT64 stringstackdepth;

    UINT64 offsetbufferid;
    UINT64 stringbufferid;
    UINT64 stackindex;

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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    offsetbufferid = (UINT64)(pints[0]);
    stringbufferid = (UINT64)(pints[1]);
    stackindex = (UINT64)(pints[2]);
    offset = (UINT64)(pints[3]);
    value =  (UINT64)(pints[4]);

    // need to get depth of string stack first
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        offsetbufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
        return;
    }

    if (stringstackdepth <= stackindex)
    {
        // stack index off end of lstring stack
        dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
        return;
    }

    caddr1 = (unsigned char*)dg_getplstring(
        pBHarrayhead, 
        offsetbufferid, 
        stringbufferid,
        stackindex,
        &u1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
    }

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
            dg_pusherror(pBHarrayhead, dg_scanforbytename);
            dg_pusherror(pBHarrayhead, dg_forthcscanlstringname);
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


void dg_forthscanlstring (Bufferhandle* pBHarrayhead)
//  ( l$offsetbufferid l$stringbufferid stackindex offset value -- offset' )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 offset;
    unsigned char* caddr1 = NULL;

    UINT64 u1 = 0;
    UINT64 value = 0;
    UINT64 stringstackdepth;

    UINT64 offsetbufferid;
    UINT64 stringbufferid;
    UINT64 stackindex;

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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    offsetbufferid = (UINT64)(pints[0]);
    stringbufferid = (UINT64)(pints[1]);
    stackindex = (UINT64)(pints[2]);
    offset = (UINT64)(pints[3]);
    value =  (UINT64)(pints[4]);

    // need to get depth of string stack first
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        offsetbufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
        return;
    }

    if (stringstackdepth <= stackindex)
    {
        dg_pusherror(pBHarrayhead, dg_lstringidtoohigherror);
        dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
        return;
    }

    caddr1 = (unsigned char*)dg_getplstring(
        pBHarrayhead, 
        offsetbufferid, 
        stringbufferid,
        stackindex,
        &u1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
    }

    if (offset < (u1 / sizeof(UINT64)))
    {
        u1 = u1 - offset;
        caddr1 = caddr1 + offset;

        flag = dg_scanforuint64(
            (void*)caddr1,
            &u1,
            value);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_scanforuint64name);
            dg_pusherror(pBHarrayhead, dg_forthscanlstringname);
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


void dg_forthshortenlstring ( Bufferhandle* pBHarrayhead )
//     ( $1 -l$- $1' )
//     ( n l$stackoffsetbufferid l$stackstringbufferid -- )
{
    UINT64* poffsetlength;
    UINT64* poffsetstack;

    UINT64 lssoffsetbufid;
    UINT64 lssstringbufid;

    UINT64 n;
    UINT64 depth;
    UINT64 slength;

    UINT64 startoffset = 0;

    const char* pError;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    lssstringbufid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    lssoffsetbufid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthshortenlstringname);
        return;
    }

    poffsetstack = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        lssoffsetbufid,
        &poffsetlength);

    if (poffsetstack == (UINT64*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthshortenlstringname);
        return;
    }

    depth = *poffsetlength / sizeof (UINT64);

    if (depth < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthshortenlstringname);
        return;
    }

    // could check for misaligned offset stack here

    if (depth >= 2)
    {
        startoffset = poffsetstack[depth-2];
    }

    if (poffsetstack[depth-1] < startoffset)
    {
        dg_pusherror(pBHarrayhead, dg_lstringsoffsetscorrupt);
        dg_pusherror(pBHarrayhead, dg_forthshortenlstringname);
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
        lssstringbufid,
        n,
        &pError);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_forthshortenlstringname);
    }
}


void dg_forthnewlstring (Bufferhandle* pBHarrayhead)
//             ( offsetbufferid stringbufferid -- )
//             ( -l$- empty$ )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthnewlstringname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_pushlstring(pBHarrayhead,
        pints[0],
        pints[1],
        0,
        (unsigned char*)"");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewlstringname);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthrolllstring (Bufferhandle* pBHarrayhead)
//             ( nd offsetbufferid stringbufferid -- )
//             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
//                 l$depth-1{bottom} ... l$nd+1 l$nd-1 ... l$1 l$0 l$nd )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 numlstringsonstack;

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
        dg_pusherror(pBHarrayhead, dg_forthrolllstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrolllstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    numlstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrolllstringname);
        return;
    }

    dg_picklstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrolllstringname);
        return;
    }
    
    dg_deletelstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        numlstringsonstack - (pints[0] + 1));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrolllstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthminusrolllstring (Bufferhandle* pBHarrayhead)
//             ( nd offsetbufferid stringbufferid -- )
//             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
//                 l$depth-1{bottom} ... l$nd+1 l$0{top} l$nd l$nd-1 ... l$1 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 numlstringsonstack;
    UINT64 lengthlstring;
    unsigned char* plstring;

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
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    numlstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    // check l$stack depth error
    if (numlstringsonstack <= pints[0])
    {
        dg_pusherror(pBHarrayhead, dg_lstringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    // at least one lstring on stack garaunteed
    lengthlstring = dg_getlstringlength(
        pBHarrayhead,
        pints[1],
        numlstringsonstack - 1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    // nd + 1 <= numlstringsonstack checked above
    dg_insertlstring(
        pBHarrayhead, 
        pints[1], 
        pints[2], 
        numlstringsonstack - (pints[0] + 1), 
        lengthlstring);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    plstring = dg_getplstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        numlstringsonstack - (pints[0] + 1),
        &lengthlstring);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }
    
    // poplstring does copy before drop in case shrink with possible move added in future
    dg_poplstring(
        pBHarrayhead,
        pints[1],
        pints[2],
        lengthlstring,
        plstring);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthminusrolllstringname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthdeleteinlstring (Bufferhandle* pBHarrayhead)
//             ( offset length n offsetbufferid stringbufferid -- )
//             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
//                 l$depth-1{bottom} ... l$nd+1 l$nd' l$nd-1 ... l$1 l$0{top} )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdeleteinlstringname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdeleteinlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    dg_deleteinlstring(pBHarrayhead,
        pints[3],
        pints[4],
        pints[2],
        pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdeleteinlstringname);
        return;
    }    

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}


void dg_forthinsertinlstring (Bufferhandle* pBHarrayhead)
//             ( offset length n offsetbufferid stringbufferid -- )
//             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
//                 l$depth-1{bottom} ... l$nd+1 l$nd' l$nd-1 ... l$1 l$0{top} )
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthinsertinlstringname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthinsertinlstringname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (5 * sizeof(UINT64)));

    dg_deleteinlstring(pBHarrayhead,
        pints[3],
        pints[4],
        pints[2],
        pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthinsertinlstringname);
        return;
    }

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}


void dg_forthcatlstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcatlstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcatlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_catlstringn(
        pBHarrayhead,
        pints[1],
        pints[2],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcatlstringnname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthcopystolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcopystolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcopystolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_copystolstringn(
        pBHarrayhead,
        pints[4],
        pints[5],
        pints[3],
        pints[2],
        (unsigned char*)pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcopystolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthcopysfromlstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcopysfromlstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcopysfromlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_copysfromlstringn(
        pBHarrayhead,
        pints[2],
        pints[3],
        pints[1],
        pints[0],
        pints[5],
        (unsigned char*)pints[4]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcopysfromlstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthsetlengthlstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetlengthlstringnname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsetlengthlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_setlengthlstringn (
        pBHarrayhead,
        pints[2],
        pints[3],
        pints[1],
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetlengthlstringnname);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthcopystoreplacelstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcopystoreplacelstringnname);
        return;
    }

    if (*pbuflength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcopystoreplacelstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - 5*sizeof(UINT64));

    dg_replacelstringn (
        pBHarrayhead,
        pints[3],
        pints[4],
        pints[2],
        (unsigned char*)pints[0],
        pints[1]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcopystoreplacelstringnname);
        return;
    }

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}


void dg_forthcopylstringntoreplacelstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcopylstringntoreplacelstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcopylstringntoreplacelstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_copylstringntoreplacelstringn (
        pBHarrayhead,
        pints[2],  // srcoffsetbufferid
        pints[0],  // srcstringbufferid
        pints[1],  // srcstringid
        pints[5],  // destoffsetbufferid
        pints[3],  // deststringbufferid
        pints[4]); // deststringid

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcopylstringntoreplacelstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthnewfreeablelstringarray (Bufferhandle* pBHarrayhead)
{
    UINT64 myfreeablelstringarrayid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    myfreeablelstringarrayid = dg_newfreeablelstringarray(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewfreeablelstringarrayname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        myfreeablelstringarrayid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewfreeablelstringarrayname);
        return;
    }
}


void dg_forthfreefreeablelstringarray (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfreefreeablelstringarrayname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfreefreeablelstringarrayname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    dg_freefreeablelstringarray (
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreefreeablelstringarrayname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthpacklstring(Bufferhandle* pBHarrayhead)
{
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    lstringstringbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
    
    lstringoffsetbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
    
    dg_packlstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
}


void dg_forthunpacklstring(Bufferhandle* pBHarrayhead)
{
    UINT64 lstringoffsetbufferid;
    UINT64 lstringstringbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    lstringstringbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
    
    lstringoffsetbufferid = dg_unpacklstring (
        pBHarrayhead,
        lstringstringbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        lstringoffsetbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpacklstringname);
        return;
    }
}


void dg_forthnotlstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthnotlstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnotlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_notlstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferid, 
        pints[2],  // lstringstringbufferid,
        pints[0]); // lstringindex)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnotlstringnname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthu8reverselstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthu8reverselstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu8reverselstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_reverselstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferid, 
        pints[2],  // lstringstringbufferid,
        pints[0]); // lstringindex)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthu8reverselstringnname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthuleextendlstringntol (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthuleextendlstringntolname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleextendlstringntolname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_uleextendlstringntol (
        pBHarrayhead, 
        pints[2],  // lstringoffsetbufferid, 
        pints[3],  // lstringstringbufferid,
        pints[1],  // lstringindex,
        pints[0]); // newlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleextendlstringntolname);
        return;
    }

    *pbuflength = *pbuflength - (4 * sizeof(UINT64));
}


void dg_forthuleandlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthuleandlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleandlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_uleandlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleandlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthuleorlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthuleorlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleorlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_uleorlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleorlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthulexorlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthulexorlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulexorlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_ulexorlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexorlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthulenandlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthulenandlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulenandlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_ulenandlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenandlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthulenorlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthulenorlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulenorlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_ulenorlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulenorlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthulexnorlstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthulexnorlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulexnorlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_ulexnorlstringntolstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferida, 
        pints[2],  // lstringstringbufferida,
        pints[0],  // lstringindexa,
        pints[4],  // lstringoffsetbufferidb, 
        pints[5],  // lstringstringbufferidb,
        pints[3]); // lstringindexb);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulexnorlstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthuleaddlstringntolstringn (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 carryout;

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
        dg_pusherror(pBHarrayhead, dg_forthuleaddlstringntolstringnname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleaddlstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    dg_uleaddlstringntolstringn (
        pBHarrayhead, 
        pints[1],   // lstringoffsetbufferida, 
        pints[2],   // lstringstringbufferida,
        pints[0],   // lstringindexa,
        pints[4],   // lstringoffsetbufferidb, 
        pints[5],   // lstringstringbufferidb,
        pints[3],   // lstringindexb,
        &carryout); // pcarryout - you can probably pass in pints...

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleaddlstringntolstringnname);
        return;
    }
    
    pints[0] = carryout; 

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
}


void dg_forthuleadclstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthuleadclstringntolstringnname);
        return;
    }

    if (*pbuflength < (7 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuleadclstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (7 * sizeof(UINT64)));

    dg_uleadclstringntolstringn (
        pBHarrayhead, 
        pints[2],  // lstringoffsetbufferida, 
        pints[3],  // lstringstringbufferida,
        pints[1],  // lstringindexa,
        pints[5],  // lstringoffsetbufferidb, 
        pints[6],  // lstringstringbufferidb,
        pints[4],  // lstringindexb,
        pints);    // pcarryinout

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuleadclstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthulesbblstringntolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthulesbblstringntolstringnname);
        return;
    }

    if (*pbuflength < (7 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulesbblstringntolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (7 * sizeof(UINT64)));

    dg_ulesbblstringntolstringn (
        pBHarrayhead, 
        pints[2],  // lstringoffsetbufferida, 
        pints[3],  // lstringstringbufferida,
        pints[1],  // lstringindexa,
        pints[5],  // lstringoffsetbufferidb, 
        pints[6],  // lstringstringbufferidb,
        pints[4],  // lstringindexb,
        pints);    // pborrowinout

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulesbblstringntolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (6 * sizeof(UINT64));
}


void dg_forthlelshiftlstringn (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 carryout;

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
        dg_pusherror(pBHarrayhead, dg_forthlelshiftlstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlelshiftlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_lelshiftlstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferid, 
        pints[2],  // lstringstringbufferid,
        pints[0],  // lstringindex,
        &carryout);    // pcarryout  // can probably just pass in pints...

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftlstringnname);
        return;
    }
    
    pints[0] = carryout;

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthulershiftlstringn (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
 
    UINT64 carryout = 0;   

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
        dg_pusherror(pBHarrayhead, dg_forthulershiftlstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulershiftlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_ulershiftlstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferid, 
        pints[2],  // lstringstringbufferid,
        pints[0],  // lstringindex,
        &carryout);  // pcarryout  // can probably just pass in pints

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthulershiftlstringnname);
        return;
    }
    
    pints[0] = carryout;

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthslershiftlstringn (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
 
    UINT64 carryout = 0;   

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
        dg_pusherror(pBHarrayhead, dg_forthslershiftlstringnname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthslershiftlstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    dg_slershiftlstringn (
        pBHarrayhead, 
        pints[1],  // lstringoffsetbufferid, 
        pints[2],  // lstringstringbufferid,
        pints[0],  // lstringindex,
        &carryout);    // pcarryout

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslershiftlstringnname);
        return;
    }
    
    pints[0] = carryout;

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthlelshiftclstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlelshiftclstringnname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlelshiftclstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_lelshiftclstringn (
        pBHarrayhead, 
        pints[2],  // lstringoffsetbufferid, 
        pints[3],  // lstringstringbufferid,
        pints[1],  // lstringindex,
        pints);    // pcarryinout

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlelshiftclstringnname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


void dg_forthlershiftclstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlershiftclstringnname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlershiftclstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    dg_lershiftclstringn (
        pBHarrayhead, 
        pints[2],  // lstringoffsetbufferid, 
        pints[3],  // lstringstringbufferid,
        pints[1],  // lstringindex,
        pints);    // pcarryinout

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlershiftclstringnname);
        return;
    }

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}


// MULU64BYL$[N]ADD>L$[N]
// U64*L$[N]+>L$[N]
void dg_forthu64starlstringnplustolstringn (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthu64starlstringnplustolstringnname);
        return;
    }

    if (*pbuflength < (7 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu64starlstringnplustolstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (7 * sizeof(UINT64)));
 
    dg_mulu64bylstringnaddtolstringn (
        pBHarrayhead,
        pints[2], // offsetbufferida,
        pints[3], // stringbufferida,
        pints[1], // stringida,
        pints[5], // offsetbufferidb,
        pints[6], // stringbufferidb,
        pints[4], // stringidb,
        pints[0]); // u)   

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthu64starlstringnplustolstringnname);
        return;
    }

    *pbuflength = *pbuflength - (7 * sizeof(UINT64));
}


// >/ULEL$[N]
void dg_forthtoslashulelstringn (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 remainder;   

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
        dg_pusherror(pBHarrayhead, dg_forthtoslashulelstringnname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtoslashulelstringnname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));
 
    dg_divlstringnbyu64 (
        pBHarrayhead,
        pints[2], // offsetbufferida,
        pints[3], // stringbufferida,
        pints[1], // stringida,
        pints[0], // u,
        &remainder);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoslashulelstringnname);
        return;
    }
    
    pints[0] = remainder;

    *pbuflength = *pbuflength - (3 * sizeof(UINT64));
}
