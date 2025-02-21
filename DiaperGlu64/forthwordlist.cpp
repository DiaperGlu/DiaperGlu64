// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2025 James Patrick Norris
//
//    This file is part of DiaperGlu v5.14.
//
//    DiaperGlu v5.14 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.14 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.14; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 20, 2025          //
// version 5.14               //
// /////////////////////////////



#include "diapergluforth.h"


void dg_forthnewdefinition (Bufferhandle* pBHarrayhead)
//    ( compilebufoffset compilebufid databufoffset databufid pname namelength -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthnewdefinitionname);
        return;
    }

    if (*pbuflength < (6 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewdefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    pints[0] = dg_newwordcopyname(
        pBHarrayhead, 
        pints[1], 
        pints[0], 
        pints[3], 
        pints[2], 
        DG_CORE_BUFFERID,
        pints[4], 
        pints[5]);

    *pbuflength = *pbuflength - (5 * sizeof(UINT64));
    
    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthnewdefinitionname);
    }
}


void dg_forthgetswordhead (Bufferhandle* pBHarrayhead)
//     ( executiontoken -- pdefinition definitionlength )
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
        dg_pusherror(pBHarrayhead, dg_forthgetswordheadname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetswordheadname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = (UINT64)dg_getpdefinition(
        pBHarrayhead,
        pints[0]);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetswordheadname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        sizeof(Definitionheader));

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetswordheadname);
        return;
    }
}


void dg_forthtohead (Bufferhandle* pBHarrayhead)
//     ( executiontoken -- pwordhead )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthgetswordhead(pBHarrayhead);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthtoheadname);
        return;
    }

    dg_forthdrop(pBHarrayhead);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthtoheadname);
        return;
    }
}

void dg_forthlinkdefinition (Bufferhandle* pBHarrayhead)
//                   ( executiontoken wordlistid -- )
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
        dg_pusherror(pBHarrayhead, dg_forthlinkdefinitionname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlinkdefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_linkdefinition(
        pBHarrayhead,
        pints[1],
        pints[0]);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthlinkdefinitionname);
    }
}


void dg_forthnewsubroutinedefinition (Bufferhandle* pBHarrayhead)
//                       ( pname namelength -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthnewsubroutinedefinitionname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewsubroutinedefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_createsubthreaddef(
        pBHarrayhead,
        (unsigned char*)pints[0],
        pints[1]);

    *pbuflength = *pbuflength - sizeof(UINT64);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthnewsubroutinedefinitionname);
    }
}


void dg_forthnewvariabledefinition (Bufferhandle* pBHarrayhead)
//     ( pname namelength -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthnewvariabledefinitionname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewvariabledefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_createvariabledef(
        pBHarrayhead,
        (unsigned char*)pints[0],
        pints[1]);

    *pbuflength = *pbuflength - sizeof(UINT64);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthnewvariabledefinitionname);
    }
}


void dg_forthnewconstantdefinition (Bufferhandle* pBHarrayhead)
//                      ( constant pname namelength -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthnewconstantdefinitionname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewconstantdefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    pints[0] = dg_createconstantdef(
        pBHarrayhead,
        pints[0],
        (unsigned char*)pints[1],
        pints[2]);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthnewconstantdefinitionname);
    }
}


void dg_forthgetnewestdefinitioninwordlist (Bufferhandle* pBHarrayhead)
//     ( wordlistid -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthgetnewestdefinitioninwordlistname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetnewestdefinitioninwordlistname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = dg_getlatestdefinition(
        pBHarrayhead,
        pints[0]);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetnewestdefinitioninwordlistname);
    }
}


void dg_forthgetnextdefinition (Bufferhandle* pBHarrayhead)
//     ( executiontoken -- nextexecutiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthgetnextdefinitionname);
        return;
    }

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgetnextdefinitionname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = dg_getnextdefinition(
        pBHarrayhead,
        pints[0]);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetnextdefinitionname);
    }
}


void dg_forthfinddefinitioninwordlist (Bufferhandle* pBHarrayhead)
//     ( wordlistid pname namelength -- executiontoken )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    
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
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninwordlistname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninwordlistname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    pints[0] = dg_finddefinwordlist(
        pBHarrayhead,
        pints[0],
        (unsigned char*)pints[1],
        pints[2]);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninwordlistname);
    }
}


void dg_forthfinddefinitioninsearchorder (Bufferhandle* pBHarrayhead)
//     ( pname namelength -- executiontoken )
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
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninsearchordername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninsearchordername);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_finddefinsearchorder(
        pBHarrayhead,
        (unsigned char*)pints[0],
        pints[1]);

    *pbuflength = *pbuflength - sizeof(UINT64);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthfinddefinitioninsearchordername);
    }
}


void dg_forthputnewestdefinitioncompiletype (Bufferhandle* pBHarrayhead)
//     ( compilebuffoffset compilebufid -- )
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
        dg_pusherror(pBHarrayhead, dg_forthputnewestdefinitioncompiletypename);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthputnewestdefinitioncompiletypename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    dg_changelatestcompileroutine(
        pBHarrayhead,
        pints[1],
        pints[0]);

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthputnewestdefinitioncompiletypename);
    }
}


void dg_forthcreateov (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -masterdefinitionarray- newovdefinition )
//     ( -currentnewwordwordlist- newovdefinition )
{
    UINT64 cdata;

    unsigned char* pname;
    UINT64 namelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateovname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthcreateovname);
        return;
    }

    dg_createovariablebufdef(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateovname);
        return;
    }
}


void dg_forthcreateoc (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -masterdefinitionlist- newovdefinition )
//     ( -currentnewwordwordlist- newovdefinition )
{
    UINT64 cdata;

    unsigned char* pname;
    UINT64 namelength;


    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateocname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthcreateocname);
        return;
    }

    dg_createocompilebufdef(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateocname);
        return;
    }
}


/*
void dg_forthtooname (Bufferhandle* pBHarrayhead)
{
    UINT32 executetoken;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    Definitionheader* pdefinition;

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    executetoken = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoonamename);
        return;
    }

    pdefinition = dg_getpdefinition(pBHarrayhead, executetoken);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoonamename);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, pdefinition->nameoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoonamename);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, pdefinition->namebufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoonamename);
        return;
    }
}
*/


void dg_forthlatest (Bufferhandle* pBHarrayhead)
{
    UINT64 executetoken;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    executetoken = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_latestnewword);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlatestname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        executetoken);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlatestname);
        return;
    }
}


void dg_forthbracketlatest (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthlatest(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketlatestname);
        return;
    }

    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketlatestname);
        return;
    }
}


/*
void dg_forthbracketcolononame (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthlatest(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcolononamename);
        return;
    }

    dg_forthtooname(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcolononamename);
        return;
    }

    dg_forthswap(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcolononamename);
        return;
    }

    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcolononamename);
        return;
    }

    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcolononamename);
        return;
    }
}
*/


void dg_forthgetcompileroutine (Bufferhandle* pBHarrayhead)
//       ( executetoken -- compileroutineoffset compileroutinebufferid )
{
    UINT64 executetoken;
    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    executetoken = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        executetoken);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->compileroutineoffset);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->compileroutinebuf);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }
}


void dg_forthsetcompileroutine (Bufferhandle* pBHarrayhead)
//       ( offset bufferid executetoken -- )
{
    UINT64 executetoken;
    Definitionheader* pdefinition;
    UINT64 definitionbufferid;
    UINT64 definitionoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    executetoken = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    definitionbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    definitionoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        executetoken);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetcompileroutinename);
        return;
    }

    pdefinition->compileroutineoffset = definitionoffset;
    pdefinition->compileroutinebuf = definitionbufferid;
}


void dg_forthgetodf (Bufferhandle* pBHarrayhead)
//     ( executetoken -- datafieldoffset datafieldbufferid )
{
    UINT64 executetoken;
    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    executetoken = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetodfname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        executetoken);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetodfname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->dataoffset);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetodfname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->databuf);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetodfname);
        return;
    }
}


void dg_forthsetodf (Bufferhandle* pBHarrayhead)
//       ( datafieldoffset datafieldbufferid executetoken -- )
{
    UINT64 executetoken;
    Definitionheader* pdefinition;
    UINT64 definitionbufferid;
    UINT64 definitionoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    executetoken = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthsetodfname);
        return;
    }

    definitionbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthsetodfname);
        return;
    }

    definitionoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthsetodfname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        executetoken);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthsetodfname);
        return;
    }

    pdefinition->dataoffset = definitionoffset;
    pdefinition->databuf = definitionbufferid;
}

void dg_forthtoorder (Bufferhandle* pBHarrayhead)
{
    UINT64 wordlistid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    wordlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtoordername);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        wordlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchorderstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtoordername);
        return;
    }
}


void dg_forthorderfrom (Bufferhandle* pBHarrayhead)
{
    UINT64 wordlistid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    wordlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthorderfromname);
        dg_pusherror(pBHarrayhead, dg_forthtoordername);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wordlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthorderfromname);
        dg_pusherror(pBHarrayhead, dg_forthtoordername);
        return;
    }
}


void dg_forthdotwordname (Bufferhandle* pBHarrayhead)
//     ( executiontoken -- )
{
    UINT64 definition;

    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    definition = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdotwordnamename);
        return;
    }

    /*
    pdefinition = dg_getpdefinition(pBHarrayhead, definition);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdotwordnamename);
        return;
    }

    pname = dg_getpbufferoffset(pBHarrayhead, pdefinition->namebufid, pdefinition->nameoffset);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdotwordnamename);
        return;
    }
    */
    
    pname = dg_getshlistelementnom (
        pBHarrayhead,
        0, // hlistheaderid, hlist 0 reserved for wordlist
        definition, // elementid,
        &namelength);
        
    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdotwordnamename);
        return;
    }

    dg_writestdout(
        pBHarrayhead,
        pname,
        namelength);
}


void dg_forthshowwordlist (Bufferhandle* pBHarrayhead)
//     ( wordlistid -- )
{
    UINT64 wordlist = 0;

    UINT64 definition = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    wordlist = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        wordlist);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
        return;
    }

    while (definition != DG_ENDOFWORDLIST)
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            definition);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthdotwordname(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthspace(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthspace(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        definition = dg_getnextdefinition(
            pBHarrayhead,
            definition);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
    }
}


void dg_forthshowsortedwordlist (Bufferhandle* pBHarrayhead)
//     ( wordlistid -- )
{
    UINT64 wordlist = 0;

    UINT64 definition = 0;
    UINT64 previousdefinition = 0;
    
    UINT64 numberofsortedchildren = 0;
    
    unsigned char* pname;
    unsigned char* ppreviousname;
    
    UINT64 namelength;
    UINT64 previousnamelength;
    
    const char* pError;
    INT64 compareflag;
    
    UINT64 i;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    wordlist = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthshowsortedwordlistname);
        return;
    }

    numberofsortedchildren = dg_getnumberofsortedchildren(
        pBHarrayhead,
        0, // hlistheaderid,
        wordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
        return;
    }
        
    if (0 == numberofsortedchildren)
    {
        return;
    }
    
    dg_printzerostring(
        pBHarrayhead,
        (unsigned char*)"\n");
        
    for (i = 0; i <  numberofsortedchildren; i++)
    {                   
        definition = dg_getidofsortedhlistchildn(
            pBHarrayhead,
            0, // hlistheaderid,
            wordlist,
            i);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
    
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            definition);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthdotwordname(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthspace(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }

        dg_forthspace(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
        
        if (i > 0)
        {
            pname = dg_getshlistelementnom (
                pBHarrayhead,
                0, // hlistheaderid, hlist 0 reserved for wordlist
                definition, // elementid,
                &namelength);
                
            ppreviousname = dg_getshlistelementnom (
                pBHarrayhead,
                0, // hlistheaderid, hlist 0 reserved for wordlist
                previousdefinition, // elementid,
                &previousnamelength);
                
            pError = dg_comparebytes (
                pname, 
                namelength,
                ppreviousname,
                previousnamelength,
                &compareflag);
                
            if ((INT64)largestunsignedint == compareflag)
            {
                dg_printzerostring(
                    pBHarrayhead,
                    (unsigned char*)" <<**outoforder**");
            }
            if (0 == compareflag)
            {
                dg_printzerostring(
                    pBHarrayhead,
                    (unsigned char*)" <<**duplicate**");
            }
        }
        
        previousdefinition = definition;
        
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"\n");
    }
}


void dg_forthshowallwords (Bufferhandle* pBHarrayhead)
//                ( -- )
{
    UINT64 numberofwordlists = 0;
    
    UINT64 wordlist = 0;
    
    UINT64 i;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    numberofwordlists = dg_getnumberofsortedchildren(
        pBHarrayhead,
        0, // hlistheaderid
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
        return;
    }
    
    dg_printzerostring(
        pBHarrayhead,
        (unsigned char*)"\n");
    
    for (i = 0; i < numberofwordlists; i++)
    {
        wordlist = dg_getidofsortedhlistchildn(
            pBHarrayhead,
            0, // hlistheaderid,
            0,
            i);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
        
        dg_pushdatastack(
            pBHarrayhead,
            wordlist);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
        
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"WORDLIST ");
        
        dg_writestdoutuinttodec(
            pBHarrayhead,
            wordlist);
        
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)":\n");
        
        dg_forthshowsortedwordlist(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthshowwordlistname);
            return;
        }
        
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"\n");
    }
}


void dg_forthforthwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_corewordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_fortherrorwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_errorwordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthenvironmentwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_environmentwordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthbufferwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_bufferwordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthstringwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_stringwordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthlibrarywords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_oswordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthuserwords (Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_userwordlistid);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthsafe (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthsafename);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsafename);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsafename);
        return;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)&dg_forthdocompiletypesubroutine))
    {
        pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypesafesubroutine;
    }
    
    // pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    // pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypesafesubroutine;

}


void dg_forthiscolon (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthiscolonname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscolonname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscolonname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypesubroutine;
}


void dg_forthisoto (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthisotoname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisotoname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisotoname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypedpushn;
}


void dg_forthisobto (Bufferhandle* pBHarrayhead)
//     ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthisobtoname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisobtoname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisobtoname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypedpushdn;
}


void dg_forthispto (Bufferhandle* pBHarrayhead)
//     ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthisptoname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisptoname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthisptoname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypedpushp;
}


void dg_forthiscallproc (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthiscallprocname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscallprocname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscallprocname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypecdecl;
}


void dg_forthiscallprocretuint64 (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthiscallprocretuint64name);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscallprocretuint64name);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscallprocretuint64name);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypecdeclretuint128;
}



void dg_forthiscompilecall (Bufferhandle* pBHarrayhead)
//                  ( -- )
{
    UINT64 vocab;

    UINT64 definition;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    vocab = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthiscompilecallname);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscompilecallname);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthiscompilecallname);
        return;
    }
    
    pdefinition->compileroutinebuf = DG_CORE_BUFFERID;
    pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypecall;
}


const char dg_stringtonewwordforherename[] = "dg_stringtonewwordforhere";

void dg_stringtonewwordforhere(
    Bufferhandle* pBHarrayhead,
    UINT64 compileroutineoffset,
    UINT64 compileroutinebufid)
{
    UINT64 wordlistid;
    UINT64 currentoffset;
    UINT64 stringstackdepth;
    UINT64 stringstartoffset;
    UINT64 stringlength;
    UINT64 ccbufid;
    UINT64 wordid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    wordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    currentoffset = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }

    if (stringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    stringstartoffset = dg_getlstringstartoffset (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        stringstackdepth - 1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    stringlength = dg_getlstringlength (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        stringstackdepth - 1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    wordid = dg_newwordcopyname (
        pBHarrayhead,
        compileroutinebufid, // compilebufid,
        compileroutineoffset, // compilebufoffset,
        ccbufid,       // UINT32 databufid,
        currentoffset, // UINT32 databufoffset,
        DG_STRINGSTRINGSTACK_BUFFERID, // namebufid,
        stringstartoffset,
        stringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
    
    dg_linkdefinition(
        pBHarrayhead,
        wordlistid,
        wordid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtonewwordforherename);
        return;
    }
}


void dg_forthstringtonewprocword(Bufferhandle* pBHarrayhead)
// ( wordname$ -$- ) ( -currentnewwordwordlist- procwordforHERE )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_stringtonewwordforhere(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypecdecl,
        (UINT64)DG_CORE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtonewprocwordname);
        return;
    }
}


void dg_forthstringtonewobword(Bufferhandle* pBHarrayhead)
// ( wordname$ -$- ) ( -currentnewwordwordlist- procwordforHERE )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_stringtonewwordforhere(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypedpushdn,
        (UINT64)DG_CORE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstringtonewprocwordname);
        return;
    }
}

void dg_forthemptywordlist(Bufferhandle* pBHarrayhead)
{
    UINT64 wid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    wid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthemptywordlistname);
        return;
    }
    
    dg_emptywordlist(
        pBHarrayhead,
        wid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthemptywordlistname);
        return;
    }
}

void dg_forthtocurrent(Bufferhandle* pBHarrayhead)
{
    UINT64 currentwordlist;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    currentwordlist = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtocurrentname);
        return;
    }
    
    dg_tocurrent(
        pBHarrayhead,
        currentwordlist);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtocurrentname);
        return;
    }
}

void dg_forthcurrentfrom(Bufferhandle* pBHarrayhead)
{
    UINT64 currentwordlist;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    currentwordlist = dg_currentfrom(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurrentfromname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        currentwordlist);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurrentfromname);
        return;
    }
}

void dg_forthsearchorderdrop(Bufferhandle* pBHarrayhead)
{    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_popbufferuint64(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchorderdropname);
        return;
    }
}

void dg_forthwordlistdot(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    UINT64 wordlistid;
    UINT64 definitionid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    wordlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
        return;
    }
    
    if (0 == namelength)
    {
        dg_pusherror(pBHarrayhead, dg_nowordfounderror);
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
        return;
    }
    
    definitionid = dg_finddefinwordlist (
        pBHarrayhead,
        wordlistid,
        pname,
        namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
        return;
    }
    
    // word not found is an error
    if (DG_ENDOFWORDLIST == definitionid)
    {
        if (namelength > maxwordlength)
        {
            namelength = maxwordlength;
        }
                            
        dg_putbuffersegment(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            lastnotfoundword,
            namelength,
            pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {    
            dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
            return;
        }

        dg_putbufferbyte(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            lastnotfoundword + namelength,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {    
            dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
            return;
        }

        // word is not found - standard says we can do what we want in this case so...
        //  I want the script to stop what it's doing and tell me which word wasn't found
        //  Copying last word not found to a buffer as a 0 string and pushing pointer
        //  to copy to error stack so it will show up on error stack.
        dg_pusherror(pBHarrayhead, dg_evaluatebufferwordnotfounderror);
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
            
        return;
    }
    
    dg_interpretdefinition(
        pBHarrayhead,
        definitionid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordlistdotname);
        return;
    }
}

void dg_forthcreatebracketwordlistdot(Bufferhandle* pBHarrayhead)
{
    UINT64 currentcreatewordlistid;
    UINT64 wordlistid;
    UINT64 wordid;
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    wordlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatebracketwordlistdotname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatebracketwordlistdotname);
        return;
    }
 
    if (namelength != 0)
    {   
        currentcreatewordlistid = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            currentcompilewordlist);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketwordlistdotname);
            return;
        }
    
        wordid = dg_newwordcopyname (
            pBHarrayhead,
            DG_CORE_BUFFERID,  // compilebufid,
            (UINT64)&dg_forthdocompiletypebracketwordlistdot, // compilebufoffset,
            0,                 // databufid,
            wordlistid,        // databufoffset,
            DG_CORE_BUFFERID,  // namebufid,
            (UINT64)pname,
            namelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketwordlistdotname);
            return;
        }
    
        dg_linkdefinition(
            pBHarrayhead,
            currentcreatewordlistid,
            wordid);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketwordlistdotname);
            return;
        }
    }   
       
}

void dg_forthlibdot(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    // UINT64 dylibhandle;
    // UINT64 definitionid;
    UINT64 symbolvalue;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // dylibhandle = dg_popdatastack(pBHarrayhead);
    
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
        // dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        // return;
    // }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
    
    if (0 == namelength)
    {
        dg_pusherror(pBHarrayhead, dg_nowordfounderror);
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
    
    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        namelength,
        pname);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
        
    // dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, dylibhandle);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_forthlibdotname);
    //    return;
    // }
        
    // do the dlsym
    dg_forthfindlibrarysymbol(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
        
    // get the symbol value from the data stack
    symbolvalue = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
        
    // need to handle the not found case - dlsym returns null when symbol not found
    if (0 == symbolvalue)
    {
        // The symbol wasn't found. This is an error.
        if (namelength > maxwordlength)
        {
            namelength = maxwordlength;
        }

        dg_putbuffersegment(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, namelength, pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlibdotname);
            return;
        }

        dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword + namelength, 0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlibdotname);
            return;
        }
            
        dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
            
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
    
    // could just leave symbol value on the data stack
    //  if there was a simple way to get the top value without popping
    dg_pushdatastack(
        pBHarrayhead,
        symbolvalue);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibdotname);
        return;
    }
}


void dg_forthcreatebracketlibdot(Bufferhandle* pBHarrayhead)
{
    UINT64 currentcreatewordlistid;
    UINT64 wordlistid;
    UINT64 wordid;
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    wordlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatebracketlibdotname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatebracketlibdotname);
        return;
    }
 
    if (namelength != 0)
    {   
        currentcreatewordlistid = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            currentcompilewordlist);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketlibdotname);
            return;
        }
    
        wordid = dg_newwordcopyname (
            pBHarrayhead,
            DG_CORE_BUFFERID,  // compilebufid,
            (UINT64)&dg_forthdocompiletypebracketlibdot, // compilebufoffset,
            0,                 // databufid,
            wordlistid,        // databufoffset,
            DG_CORE_BUFFERID,  // namebufid,
            (UINT64)pname,
            namelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketlibdotname);
            return;
        }
    
        dg_linkdefinition(
            pBHarrayhead,
            currentcreatewordlistid,
            wordid);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcreatebracketlibdotname);
            return;
        }
    }   
       
}


void dg_forthcodecreate (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodecreatename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthcodecreatename);
        return;
    }

    dg_createcodepointerdef(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodecreatename);
        return;
    }
}


// $>PROCWORD $>OBWORD $>OWORD $>:WORD $>COMPILECALLWORD $>IMMEDIATEWORD
// really only need the first 2 or 3

// $>JMPNLINK,
// $>RETNLINK,

