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


void dg_forthdefinitions (Bufferhandle* pBHarrayhead)
//     ( -- )
{
    unsigned char* psobuf;
    UINT64* psobuflength;

    UINT64 ccwordlist;

    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    psobuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        &psobuflength);

    if (psobuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchorderstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname);
        return;
    }

    if (*psobuflength < sizeof(UINT64))
    {
        // search order stack is empty
        dg_pusherror(pBHarrayhead, dg_searchorderemptyerror);
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname);
        return;
    }
    
    // current compile word list gets set to word list on top of search order stack
    ccwordlist = *( (UINT64*)(psobuf + *psobuflength - sizeof(UINT64)) );
    

    // checking to see if this wordlist exists
    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        ccwordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname);
        return;
    }
    
    /*
    pwlabuf = dg_getpbuffer(pBHarrayhead, DG_WORDLISTHEADERARRAY_BUFFERID, &pwlabuflength);

    if (pwlabuf == (unsigned char*)badbufferhandle)
    {
        // no word list header array buffer so...
        dg_pusherror(pBHarrayhead, dg_forthwordlistbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname); 
        return;
    }
    
    if (*pwlabuflength <= ccwordlist * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_wordlistidtoobigerror); // not sure this is the best error
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname);
        return;
    }
    */    

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        ccwordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthdefinitionsname);
    }
}


void dg_forthgetcurrent (Bufferhandle* pBHarrayhead)
//     ( -- currentcompilewordlistid )
{
    UINT64 wid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    wid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthgetcurrentname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetcurrentname);
        return;
    }
}


void dg_forthgetorder (Bufferhandle* pBHarrayhead)
//     ( -- wordlistidn ... wordlistid1 n )
{
    UINT64* psolength;
    unsigned char* psobuffer;

    UINT64 n;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    psobuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        &psolength);

    if (psobuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchorderstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetordername);
        return;
    }

    if ((*psolength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_buffernubcorrupt); // could have a better error here, like stack misaligned
        dg_pusherror(pBHarrayhead, dg_forthgetordername);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        *psolength,
        psobuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetordername);
        return;
    }

    n = *psolength / sizeof(UINT64);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        n);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetordername);
        return;
    }
}


void dg_forthsearchwordlist (Bufferhandle* pBHarrayhead)
//     ( c-addr u wid -- 0 ) if word not found
//     ( c-addr u wid -- xt 1 ) if word found and it is immediate
//     ( c-addr u wid -- xt -1 ) if word found and it is not immediate
{
    unsigned char* pname;

    UINT64 namelength;

    UINT64 wid;

    UINT64 definition;

    Definitionheader* pdefinition;

    unsigned char* pdatastack;
    UINT64* pdatastacklength;

    UINT64* pints;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // pop c-addr u wid
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsearchwordlistname);
        return;
    }

    if (*pdatastacklength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsearchwordlistname);
        return;
    }

    pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));

    pname = (unsigned char*)(pints[0]);
    namelength = pints[1];
    wid = pints[2];


    // finddefinvocab checks for namelength = 0, namelength too long, pname null
    definition = dg_finddefinwordlist(
        pBHarrayhead,
        wid,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchwordlistname);
        return;
    }

    if (definition == DG_ENDOFWORDLIST)
    {
        pints[0] = 0;
        *pdatastacklength -= (2 * sizeof(UINT64));
    
        return;
    }

    pints[0] = definition;


    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchwordlistname);
        return;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)(&dg_forthdocompiletypealwaysexecute)))
    {
        // immediate
        pints[1] = 1;
    }
    else
    {
        // not immediate
        pints[1] = (UINT64)(largestunsignedint);
    }

    *pdatastacklength -= sizeof(UINT64);
}


void dg_forthsetcurrent (Bufferhandle* pBHarrayhead)
//              ( wordlistid -- )
{
    UINT64 wid;
    
    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    wid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }
    
    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        wid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }


    // checking to see if this word list exists
    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        wid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }
    
    /*
    pwlabuf = dg_getpbuffer(pBHarrayhead, DG_WORDLISTHEADERARRAY_BUFFERID, &pwlabuflength);

    if (pwlabuf == (unsigned char*)badbufferhandle)
    {
        // no word list header array buffer so... cant set word list
        dg_pusherror(pBHarrayhead, dg_forthwordlistbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }
    
    if (*pwlabuflength <= wid * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_wordlistidtoobigerror);
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }
    */
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist,
        wid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_forthsetcurrentname);
        return;
    }
}


void dg_forthsetorder (Bufferhandle* pBHarrayhead)
//     ( wordlistidn ... wordlistid1 n -- )
// - dpans94 16.6.1.2197
{
    unsigned char* pdatastack;
    UINT64* pdatastacklength;

    unsigned char* psobuf;
    UINT64* psobuflength;

    INT64 n;
    UINT64 corewid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
        return;
    }

    if (*pdatastacklength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
        return;
    }

    psobuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        &psobuflength);

    if (psobuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthsearchorderstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
        return;
    }
    
    corewid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_corewordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
    }
    

    // pop n from data stack
    n = *((INT64*)(pdatastack + *pdatastacklength - sizeof(UINT64)));

    *pdatastacklength -= sizeof(UINT64);
    
    // minimum search order case
    if (n == (INT64)largestunsignedint)
    {
        *psobuflength = 0;
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_SEARCHORDERSTACK_BUFFERID,
            corewid);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthsearchorderstackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthsetordername);
        }

        return;
    }
    
    if (n < (INT64)largestunsignedint)
    {
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
        return;
    }

    if (((*pdatastacklength) / sizeof(UINT64)) < (UINT64)n)
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
        return;
    }
    
    // empty search order
    *psobuflength = 0;

    // empty search order case. This locks out the user, but it is in the standard
    if (n == 0)
    {
        return;
    }

    // this does not check for valid wordlist ids
    dg_pushbuffersegment(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        (UINT64)(n * sizeof(UINT64)),
        (pdatastack + *pdatastacklength - (UINT64)(n * sizeof(UINT64))));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // Aug 11, 2009 search order buffer in dg_initbuffers is currently of fixed size so this
        //   shouldn't happen unless user somehow increases max size of search order buffer and
        //   puts in a very large search order
        // attempt to set up minimum search order so user is not locked out
        *psobuflength = 0;
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_SEARCHORDERSTACK_BUFFERID,
            corewid);

        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsetordername);
    }

    *pdatastacklength -= (UINT64)(n * sizeof(UINT64));
}


void dg_forthwordlist (Bufferhandle* pBHarrayhead)
//               ( -- wordlistid )
{
    UINT64 wid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }


    wid = dg_newwordlist(
        pBHarrayhead,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordlistname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordlistname);
    }
}

