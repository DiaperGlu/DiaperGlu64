// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.6.
//
//    DiaperGlu v5.6 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.6 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.6; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// August 1, 2022             //
// version 5.6                //
// /////////////////////////////



#include "diapergluforth.h"

void dg_forthevaluatebuffer (Bufferhandle* pBHarrayhead)
//      ( bufferid -- )
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
        dg_pusherror(pBHarrayhead, dg_forthevaluatebuffername);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthevaluatebuffername);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    dg_evaluatebuffer(
        pBHarrayhead,
        pints[0]);

    // not returning error here on purpose

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthqueryendevaluate (Bufferhandle* pBHarrayhead)
//                     (  flag -- )
{
    UINT64 flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    flag = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthqueryendevaluatename);
        return;
    }

    if (flag != FORTH_FALSE)
    {
        dg_forthsource(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryendevaluatename);
            return;
        }

        dg_forthtoin(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryendevaluatename);
            return;
        } 

        dg_forthstore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryendevaluatename);
            return;
        }

        dg_forthdrop(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryendevaluatename);
            return;
        }
    }
}


void dg_forthtype0string (Bufferhandle* pBHarrayhead)
//             ( c-addr -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char* caddr;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtype0stringname);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtype0stringname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 1* sizeof(UINT64));

    caddr = (unsigned char*)(pints[0]);

    dg_printzerostring(
        pBHarrayhead,
        caddr);
    // does not return an error
    
    *pbuflength -= sizeof(UINT64);
}


void dg_forthshowlicense (Bufferhandle* pBHarrayhead)
//               ( -- )
{
    UINT64 bufferid;
    unsigned char* pbuf;
    UINT64* plength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        8,
        (unsigned char*)"gpl.doc");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        return;
    }
    
    dg_forthloadfilestring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        return;
    }

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (bufferid == 0)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        return;
    }

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &plength);

    if (pbuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        dg_freebuffer(pBHarrayhead, bufferid);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pbuf);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        dg_freebuffer(pBHarrayhead, bufferid);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        *plength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
        dg_freebuffer(pBHarrayhead, bufferid);
        return;
    }

    dg_forthtype(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowlicensename);
    }

    dg_freebuffer(
        pBHarrayhead,
        bufferid);
}


void dg_forthcrlf (Bufferhandle* pBHarrayhead)
{
    dg_printzerostring(
        pBHarrayhead,
        (unsigned char*)"\r\n");
}


void dg_forthgethstdin (Bufferhandle* pBHarrayhead)
{
    UINT64 myfileid;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    flag = dg_gethstdin(
        pBHarrayhead,
        &myfileid, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthgethstdinname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myfileid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethstdinname);
    }
}


void dg_forthgethstdout (Bufferhandle* pBHarrayhead)
{
    UINT64 fileid;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    flag = dg_gethstdout(
        pBHarrayhead,
        &fileid, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthgethstdoutname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)fileid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethstdoutname);
    }
}

void dg_forthgethstderror (Bufferhandle* pBHarrayhead)
{
    UINT64 myfileid;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    flag = dg_gethstderror(
        pBHarrayhead,
        &myfileid, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthgethstderrorname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myfileid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethstderrorname);
    }
}


void dg_forthgetfilelength (Bufferhandle* pBHarrayhead)
//     ( handle -- filelength )
{
    UINT64 myhandle;
    UINT64 filelength;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    myhandle = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgetfilelengthname);
        return;
    }

    flag = dg_getfilelength(
        pBHarrayhead,
        myhandle, 
        &filelength, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthgetfilelengthname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        filelength);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthgetfilelengthname);
        return;
    }
}


// need a read routine... read whats available and push it to buffer
void dg_forthreadavailabletobuffer (Bufferhandle* pBHarrayhead)
//     ( filehandle bufferid -- )
//     ( -bufferid- availabledata )
{
    UINT64 myhandle;
    UINT64 bufferid;
    UINT64 filelength;
    const char* flag;
    UINT64 oldlength;
    unsigned char* pbuf;
    UINT64 numread;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }

    myhandle = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }

    flag = dg_getfilelength(
        pBHarrayhead,
        myhandle, 
        &filelength, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }

    oldlength = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        filelength,
        &flag,
        FORTH_FALSE);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }

    pbuf = dg_getpbuffersegment(
        pBHarrayhead,
        bufferid,
        oldlength,
        filelength);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }

    flag = dg_readfile(
        pBHarrayhead,
        myhandle, 
        pbuf, 
        filelength, 
        0, 
        &numread, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthreadavailabletobuffername);
        return;
    }
}


//   and wait and read x and push it to buffer (don't like the idea waiting forever for the OS)
void dg_forthreadwaitforntobuffer(Bufferhandle* pBHarrayhead)
//     ( filehandle n timeout bufferid -- )
//     ( -bufferid- uptondata )
{
    UINT64 myhandle;
    UINT64 bufferid;
    UINT64 timeout;
    UINT64 n;
    const char* flag;
    UINT64 oldlength;
    unsigned char* pbuf;
    UINT64 numread;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    timeout = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    n = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    myhandle = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    oldlength = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        n,
        &flag,
        FORTH_FALSE);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    pbuf = dg_getpbuffersegment(
        pBHarrayhead,
        bufferid,
        oldlength,
        n);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    flag = dg_readfile(
        pBHarrayhead,
        myhandle, 
        pbuf, 
        n, 
        timeout, 
        &numread, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_readfilename);
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    // In this routine numread could very well be less than what you asked for
    //  If you asked for more than 0 and got nothing back it means whatever
    //  you are reading from is done.

    if (numread > n)
    {
        // os just over ran the buffer and has serious issues
        dg_pusherror(pBHarrayhead, dg_oserror);
        dg_pusherror(pBHarrayhead, dg_readfilename);
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    // need to shrink buffer down to actual amount read
    dg_shrinkbuffer(
        pBHarrayhead,
        bufferid,
        n - numread,
        &flag);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        numread);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthreadwaitforntobuffername);
        return;
    }
}


////////////////////////////////////////////////////
// dg_forthcompilesafecallbuffer is in cpux86.cpp //
////////////////////////////////////////////////////


void dg_forthcscan (Bufferhandle* pBHarrayhead)
//                 ( caddr1 u1 value -- index )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    unsigned char* caddr1 = NULL;
    UINT64 u1 = 0;
    UINT64 value = 0;

    const char* flag;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcscanname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcscanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    caddr1 = (unsigned char*)(pints[0]);
    u1 =     (UINT64)(pints[1]);
    value =  (UINT64)(pints[2]);

    flag = dg_scanforbyte(
        (void*)caddr1,
        &u1,
        value);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_forthcscanname);
    }

    pints[0] = (UINT64)u1;

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthscan (Bufferhandle* pBHarrayhead)
//                ( caddr1 u1 value -- index )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    unsigned char* caddr1 = NULL;
    UINT64 u1 = 0;
    UINT64 value = 0;

    const char* flag;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthscanname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthscanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    caddr1 = (unsigned char*)(pints[0]);
    u1 =     (UINT64)(pints[1]);
    value =  (UINT64)(pints[2]);

    flag = dg_scanforuint64(
        (void*)caddr1,
        &u1,
        value);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_scanforuint64name);
        dg_pusherror(pBHarrayhead, dg_forthscanname);
    }

    pints[0] = (UINT64)u1;

    *pbuflength -= (2 * sizeof(UINT64));
}


void dg_forthdoprompt (Bufferhandle* pBHarrayhead)
{
    unsigned char* pok = (unsigned char*)"\nOK>"; 

    unsigned char* perrorsok = (unsigned char*)"items on error stack, error(s) with trace.\n use SHOW-ERRORS or .ES to see\n use EMPTY-ERRORS or EES to clear\n use .ERRORLINE or .EL to see the line that caused the error\n\nOK>"; 

    const char* pstate;
    

    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        // got an error - force interpret state and display error prompt
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            statevariable,
            (UINT64)dg_stateexecute);

        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            dg_geterrorcount(pBHarrayhead));

        dg_forthcr(pBHarrayhead);

        dg_forthudot(pBHarrayhead); 

        dg_printzerostring(
            pBHarrayhead,
            perrorsok);
    }
    else
    {
        pstate = (const char*)dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            statevariable);
    
        if (dg_geterrorcount(pBHarrayhead) != 0)
        {
            dg_pusherror(pBHarrayhead, dg_forthstatename);
            dg_pusherror(pBHarrayhead, dg_forthdopromptname);
            return;
        }

        // if in interpret state, need to display OK>
        if (pstate == dg_stateexecute)
        {
            dg_printzerostring(
                pBHarrayhead,
                pok);
        }
    }
}


void dg_forthbswap (Bufferhandle* pBHarrayhead)
//         ( u -- u' )
{
    UINT64 u = 0;
    
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;
    
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);
    
    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthbswapname);
        return;
    }
    
    if (*plength < sizeof(UINT64))
    {
        *plength = 0;
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbswapname);
        return;
    }
    
    u = *((UINT64*)(pbuffer + *plength - sizeof(UINT64)));

    *((UINT64*)(pbuffer + *plength - sizeof(UINT64))) = dg_bswap(u);
}


void dg_forthcompilebranch (Bufferhandle* pBHarrayhead)
//      ( branchtype -- afterbranchoffset )
{
    UINT64 branchtype;
    UINT64 afterbranchoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    branchtype = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilebranchname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        branchtype);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilebranchname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        afterbranchoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilebranchname);
        return;
    }
}


void dg_forthresolvecompiledbranch(Bufferhandle* pBHarrayhead)
//   ( targetoffset afterbranchoffset -- )
{
    UINT64 afterbranchoffset;
    UINT64 targetoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    afterbranchoffset = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthresolvecompiledbranchname);
        return;
    }
    
    targetoffset = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthresolvecompiledbranchname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        targetoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthresolvecompiledbranchname);
        return;
    }
}


void dg_forthosquotes (Bufferhandle* pBHarrayhead) // ( OS" )
//     ( "somestuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
//     ( compiletime: -- )
//     ( runtime: -- offset bufferid length )
{
    
    
    UINT64 bufferid;
    
    unsigned char* psqstr;   
    UINT64 sqstrlen;
    
    const char* state;
    
    UINT64 afterbranchoffset;
    
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
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    // now have beginoffset and length, time to compile code to push addr u for string
    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)psqstr,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        afterbranchoffset + sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    state = (const char*)dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthosquotesname);
        return;
    }
    
    if (state == dg_statecompile)
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            afterbranchoffset);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_forthliteral(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            bufferid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_forthliteral(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            sqstrlen);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_forthliteral(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
    }
    else
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            afterbranchoffset);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            bufferid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            sqstrlen);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthosquotesname);
            return;
        }
    }
    // could compile check for errors here
}


void dg_fortho0quotes (Bufferhandle* pBHarrayhead) // ( O0" )
//     ( "somestuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
//     ( compiletime: -- )
//     ( runtime: -- offset bufferid )
{
    UINT64 bufferid;
    
    unsigned char* psqstr;   
    UINT64 sqstrlen;
    
    const char* state;
    
    UINT64 afterbranchoffset;
    
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
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    // now have beginoffset and length, time to compile code to push addr u for string
    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)psqstr,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    dg_pushbufferbyte(
        pBHarrayhead,
        bufferid,
        0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        afterbranchoffset + sqstrlen + 1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
        return;
    }
    
    state = (const char*)dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable);
    
    if (state == dg_statecompile)
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            afterbranchoffset);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }
        
        dg_forthliteral(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            bufferid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }
        
        dg_forthliteral(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }
    }
    else
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            afterbranchoffset);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }

        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            bufferid);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_fortho0quotesname);
            return;
        }
    }
}


void dg_forthpagesize(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        dg_getpagesize());
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpagesizename);
    }
}


void dg_forthroundup (Bufferhandle* pBHarrayhead)
//      ( n unitsize -- )
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
        dg_pusherror(pBHarrayhead, dg_forthroundupname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthroundupname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = dg_getnearesthighestmultiple(
        pints[0],
        pints[1]);

    // dg_calcnearesthighestmultiple does not generate errors

    *pbuflength = *pbuflength - sizeof(UINT64);
}


////////////////////////////////////////
// located in osapi files:            //
// dg_forthcallprocaddress            //
// dg_forthcallprocaddressretuint64   //
// dg_forthcallcppmemberfunction      //
////////////////////////////////////////

/*
void dg_forthudmslashmod (Bufferhandle* pBHarrayhead)
//     ( ud u1 -- ud2 rem )
{
    UINT64* pbuflength;         // -0x04
    unsigned char* pdatastack;  // -0x08
    UINT64* pints;              // -0x0C

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthudmslashmodname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthudmslashmodname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    
    dg_udmslashmod(pints);
}
*/


void dg_forthodoes (Bufferhandle* pBHarrayhead)
{
    UINT64 bufferid;
    
    UINT64 mytargetoffset = 0;
    
    UINT64 myendofbufferoffset = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilealignretstack(
        pBHarrayhead,
        3);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilentoparameter (
        pBHarrayhead,
        0, // need offset of compile buffer after this is compiled
        2);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilentoparameter (
        pBHarrayhead,
        bufferid,
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilepushpBHarrayheadtoret(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilecalladdress(
        pBHarrayhead,
        (UINT64)&dg_changelatestcompileroutine);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compileexitlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    myendofbufferoffset = dg_getbufferlength(
        pBHarrayhead,
        bufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        bufferid,
        mytargetoffset,
        myendofbufferoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }

    // ODOES compile type routine uses standard dglu frame and must end with standard dglu exit
    dg_compileinitlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
}


void dg_forthpackdf (Bufferhandle* pBHarrayhead)
//     ( mantissa exponent-n sign-f -- df )
{
    UINT64 mantissa;
    INT64 exponent;
    INT64 sign;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    sign = (INT64)dg_popdatastack(pBHarrayhead);
    
    exponent = (INT64)dg_popdatastack(pBHarrayhead);
    
    mantissa = dg_popdatastack(pBHarrayhead);
    
    // not worring about mantissas that are too big
    mantissa = mantissa & 0x000fffffffffffff;
    
    if (sign < 0)
    {
        mantissa = mantissa | 0x8000000000000000;
    }
    
    exponent += 1023;
    
    if (exponent < 0) 
    { 
        exponent = 0; 
    }
    
    exponent = exponent & 0x7ff;
    
    mantissa = mantissa | (exponent << 52);
    
    dg_pushdatastack(pBHarrayhead, mantissa);
}


void dg_forthunpackdf (Bufferhandle* pBHarrayhead)
//     ( df -- mantissa exponent-n sign-f )
{
    UINT64 mantissa;
    INT64 exponent;
    INT64 sign;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // double float format is lo hi
    mantissa = dg_popdatastack(pBHarrayhead);
        
    if ( (mantissa & 0x8000000000000000) != 0 )
    {
        sign = 0xffffffff;
    }
    else
    {
        sign = 0;
    }
    
    exponent = (mantissa >> 52) & 0x7ff;
    exponent -= 1023;
    
    mantissa = mantissa & 0x000fffffffffffff;
    
    dg_pushdatastack(pBHarrayhead, mantissa);
    
    dg_pushdatastack(pBHarrayhead, (UINT64)exponent);
    
    dg_pushdatastack(pBHarrayhead, (UINT64)sign);
}

/*
void dg_forthdfplus (Bufferhandle* pBHarrayhead)
//     ( df1 df2 -- df1+df2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    
    double x1;
    double x2;
    double x3;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdfplusname);
        return;
    }

    if ( *pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdfplusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    x1 = *((double*)&pints[0]);
    x2 = *((double*)&pints[1]);
    
    x3 = x2 + x1;
    
    *((double*)&pints[0]) = x3;

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthdfminus (Bufferhandle* pBHarrayhead)
//     ( df1 df2 -- df1-df2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    double * pdoubles;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdfminusname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdfminusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    pdoubles = (double*)pints;
    
    pdoubles[0] = pdoubles[0] - pdoubles[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthdfstar (Bufferhandle* pBHarrayhead)
//     ( df1 df2 -- df1*df2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    double* pdoubles;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdfstarname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdfstarname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    pdoubles = (double*)pints;
    
    pdoubles[0] = pdoubles[0] * pdoubles[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}



void dg_forthdfslash (Bufferhandle* pBHarrayhead)
//     ( df1 df2 -- df1/df2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    double* pdoubles;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdfslashname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdfslashname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    pdoubles = (double*)pints;
    
    pdoubles[0] = pdoubles[0] / pdoubles[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}
*/

void dg_forthcodescomma (Bufferhandle* pBHarrayhead)
//     ( addr length -- )
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
        dg_pusherror(pBHarrayhead, dg_forthcodescommaname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodescommaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)pints[0],
        pints[1]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodescommaname);
        return;
    }

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthcodeu8comma (Bufferhandle* pBHarrayhead)
//     ( u -- )
{
    UINT64 u;
    unsigned char c;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu8commaname);
        return;
    }
    
    // doing it this way to make porting to big endian platform easier
    c = (unsigned char)(u & 0xFF); 
    
    
    dg_compilesegment(
        pBHarrayhead, 
        (const char*)&c, 
        sizeof(unsigned char));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu8commaname);
        return;
    }
}


void dg_forthcodeu16comma (Bufferhandle* pBHarrayhead)
//     ( u -- )
{
    UINT64 u;
    UINT16 w;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu16commaname);
        return;
    }
    
    // doing it this way to make porting to big endian platform easier
    w = (UINT16)(u & 0xFFFF); 
    
    
    dg_compilesegment(
        pBHarrayhead, 
        (const char*)&w, 
        sizeof(UINT16));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu16commaname);
        return;
    }
}


void dg_forthcodeu32comma (Bufferhandle* pBHarrayhead)
//     ( u32 -- )
{
    UINT64 u, x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu32commaname);
        return;
    }
    
    // doing it this way to make porting to big endian platform easier
    x = (UINT32)(u & 0xFFFFFFFF);
    
    dg_compilesegment(
        pBHarrayhead, 
        (const char*)&x,
        sizeof(UINT32));  // assumes little endian
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu32commaname);
        return;
    }
}


void dg_forthcodeu64comma (Bufferhandle* pBHarrayhead)
//     ( u64 -- )
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
        dg_pusherror(pBHarrayhead, dg_forthcodeu64commaname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead, 
        (const char*)&u, 
        sizeof(UINT64));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodeu64commaname);
        return;
    }
}


void dg_forthcodeallot (Bufferhandle* pBHarrayhead)
//     ( n1 -- )
//     ( -currentcompilebuffer- +n1bytes )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    const char* pError = NULL;

    INT64 n1 = 0;
    UINT64 dsbufid = 0;
    
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
        dg_pusherror(pBHarrayhead, dg_forthcodeallotname);
        return;
    }

    if (*pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodeallotname);
        return;
    }

    n1 = *((INT64*)(pdatastack + *pdatastacklength - sizeof(UINT64)));

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthcodeallotname);
        return;
    }

    if (n1 > 0)
    {
        dg_growbuffer(
            pBHarrayhead,
            dsbufid,
            n1,
            &pError,
            FORTH_FALSE);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
            dg_pusherror(pBHarrayhead, dg_forthcodeallotname);
            return;
        }
    }
    else
    {
        n1 = 0 - n1;

        dg_shrinkbuffer(
            pBHarrayhead,
            dsbufid,
            n1,
            &pError);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_shrinkbuffername);
            dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
            dg_pusherror(pBHarrayhead, dg_forthcodeallotname);
            return;
        }
    }

    *pdatastacklength = *pdatastacklength - sizeof(UINT64);
}

/*
void dg_forthsftodf (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
    FLOAT64 y;
    
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
        dg_pusherror(pBHarrayhead, dg_forthsftodfname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsftodfname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    y = dg_f32tof64(*((FLOAT32*)pints)); // assumes little endian
    
    *((FLOAT64*)pints) = y;
}


void dg_forthdftosf (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
    FLOAT32 y;
    
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
        dg_pusherror(pBHarrayhead, dg_forthdftosfname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdftosfname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    y = dg_f64tof32(*((FLOAT64*)pints)); // should be no error possible I think...
    
    pints[0] = 0;
    
    *((FLOAT32*)pints) = y; // assumes little endian
}
*/
/*
void dg_forthftod (Bufferhandle* pBHarrayhead)
{
    FLOAT32 x;
    INT64 y;
    
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
    
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
        dg_pusherror(pBHarrayhead, dg_forthdftosfname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdftosfname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    y = dg_ftod(*((FLOAT32*)pints)); // should be no error possible I think...
    pints[0] = (UINT64)y;
}
*/
/*
void dg_forthdftod (Bufferhandle* pBHarrayhead)
{
    INT64 y;
    
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
    
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
        dg_pusherror(pBHarrayhead, dg_forthdftodname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdftodname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    y = dg_f64toi64(*((FLOAT64*)pints)); // should be no error possible I think...
    
    pints[0] = (UINT64)y;
}



void dg_forthdtodf (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    INT64 y;
    
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
    
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
        dg_pusherror(pBHarrayhead, dg_forthdftodname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdftodname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    x = dg_dtodf((INT64)(pints[0])); // should be no error possible I think...
    
    *((FLOAT64*)pints) = x;
}
*/


void dg_forthdoterrorline(Bufferhandle* pBHarrayhead)
{
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    UINT64 linenumber;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_ERRORLINE_BUFFERID,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Something is really wrong. Couldn't get the pointer to the buffer holding the error line. Did something free all the buffers?\n");
        return;
    }
    
    olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    linenumber = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_errorlinenumber);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Something is really wrong. Couldn't get the error line number\n");
        return;
    }
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    dg_writestdout(
        pBHarrayhead,
        pbuffer,
        *pbufferlength);
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"line number = ");
    dg_writestdoutuinttodec(pBHarrayhead, linenumber + 1); // error line number is 0 based
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
}


void dg_forthohere(Bufferhandle* pBHarrayhead)
{
    UINT64 ccbufid;
    UINT64 ccbuflength;
    
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
        dg_pusherror(pBHarrayhead, dg_forthoherename);
    }
    
    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthoherename);
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        ccbuflength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthoherename);
    }
}

void dg_forthdglibstring(Bufferhandle* pBHarrayhead)
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
        DG_DIAPERGLU_LIB_NAME_LENGTH,
        (unsigned char*)DG_DIAPERGLU_LIB_NAME);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdglibstringname);
    }
}

// ///////////////////////////////////////////////
// dg_forthfsfrom  is in the x86 assembler file //
// dg_forthf32from is in the x86 assembler file //
// ///////////////////////////////////////////////



void dg_forthfunctblofn (Bufferhandle* pBHarrayhead)
{
    UINT64 n = NULL;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthfunctblofnname);
        return;
    }

    if (*plength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfunctblofnname);
        return;
    }

    n = *((UINT64*)(pbuffer + *plength - (sizeof(UINT64))));
    
    if (n >= DG_NUMBEROFFUNCTIONTABLEIDS)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthfunctblofnname);
    }
    
    *((UINT64*)(pbuffer + *plength - (sizeof(UINT64)))) = dg_functiontable[n];
}


void dg_forthu32comma (Bufferhandle* pBHarrayhead)
//         ( n1 -- )
//         ( -currentdataspacebuffer- n1 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 n1 = 0;
    UINT64 olderrorcount = 0;
    UINT64 dsbufid = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthu32commaname);
        return;
    }

    if (*pbuflength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthu32commaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    n1 = pints[0];

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthu32commaname);
        return;
    }

    dg_pushbufferuint32(
        pBHarrayhead,
        dsbufid,
        (UINT32)(n1 & 0xFFFFFFFF));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // error pushing to current new variable buffer
        dg_pusherror(pBHarrayhead, dg_forthu32commaname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthlobit (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
        dg_pusherror(pBHarrayhead, dg_forthlobitname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlobitname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    pints[0] = dg_lobit(pints[0]);
}



void dg_forthhibit (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
        dg_pusherror(pBHarrayhead, dg_forthhibitname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthhibitname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    pints[0] = dg_hibit(pints[0]);
}


void dg_forthcountbits (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
        dg_pusherror(pBHarrayhead, dg_forthcountbitsname);
        return;
    }

    if ( *pdatastacklength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcountbitsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    pints[0] = dg_countbits(pints[0]);
}


void dg_forthmicrosecondssince1970jan01 (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, dg_getmicrosecondssince1970Jan01());
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthmicrosecondssince1970jan01name);
        return;
    }
}


void dg_forthtouleb128 (Bufferhandle* pBHarrayhead)
{
    UINT64 u;
    UINT64 pconverteduleb128[2];
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    u = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtouleb128name);
        return;
    }
    
    dg_touleb128(u, pconverteduleb128);
    
    dg_pushdatastack(pBHarrayhead, pconverteduleb128[0]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtouleb128name);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, pconverteduleb128[1]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtouleb128name);
        return;
    }
}


void dg_forthhctwostore (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    const char* perror;
    
    UINT64* pints;
    
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
        dg_pusherror(pBHarrayhead, dg_forthhctwostorename);
        return;
    }

    if ( *pdatastacklength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthhctwostorename);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));
    
    perror = dg_hctwostore((unsigned char*)(pints[2]), pints);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_hctwostorename);
        dg_pusherror(pBHarrayhead, dg_forthhctwostorename);
        return;
    }

    *pdatastacklength = *pdatastacklength - (3 * sizeof(UINT64));
}


void dg_forthdrshift (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
            dg_pusherror(pBHarrayhead, dg_forthdrshiftname);
            return;
        }

        if ( *pdatastacklength < (3 * sizeof(UINT64)) )
        {
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
            dg_pusherror(pBHarrayhead, dg_forthdrshiftname);
            return;
        }
    
        pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));
    
        dg_shrd(
            pints, 
            pints[2]);

        *pdatastacklength = *pdatastacklength - sizeof(UINT64);
}


void dg_forthdlshift (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
            dg_pusherror(pBHarrayhead, dg_forthdlshiftname);
            return;
        }

        if ( *pdatastacklength < (3 * sizeof(UINT64)) )
        {
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
            dg_pusherror(pBHarrayhead, dg_forthdlshiftname);
            return;
        }
    
        pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));
    
        dg_shld(
            pints, 
            pints[2]);

        *pdatastacklength = *pdatastacklength - sizeof(UINT64);
}

void dg_forthdarshift (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    
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
            dg_pusherror(pBHarrayhead, dg_forthdarshiftname);
            return;
        }

        if ( *pdatastacklength < (3 * sizeof(UINT64)) )
        {
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
            dg_pusherror(pBHarrayhead, dg_forthdarshiftname);
            return;
        }
    
        pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));
    
        dg_ashrd(
            (INT64*)pints, 
            pints[2]);

        *pdatastacklength = *pdatastacklength - sizeof(UINT64);
}

// ( codebufid exportsymbollisthlistid, exportsymbollistelementid -- codebufid )
void dg_forthbuftodotobuf (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    const char* pError;

    unsigned char* pcodebuf;
    UINT64* pcodebuflength;

    UINT64 destbufid, codebufid, symbollisthlistid, symbollistparentelementid;
    
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
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    if ( *pdatastacklength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (3 * sizeof(UINT64)));
    
    codebufid = pints[0];
    symbollistparentelementid = pints[1];
    symbollisthlistid = pints[2];
    

    destbufid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    pcodebuf = dg_getpbuffer(
        pBHarrayhead,
        codebufid,
        &pcodebuflength);

    if (pcodebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }
    
    dg_makedototobuf (
        pBHarrayhead,
        pcodebuf,
        *pcodebuflength,
        symbollisthlistid,
        symbollistparentelementid,
        largestunsignedint,
        largestunsignedint,
        destbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }
    
    pints[0] = destbufid;

    *pdatastacklength = *pdatastacklength - (2 * sizeof(UINT64));
}

void dg_forthbuftodotofilestring (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthbuftodotobuf(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotofilestringname);
        return;
    }
    
    dg_forthdup(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotofilestringname);
        return;
    }

    dg_forthsavefilestring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotofilestringname);
        return;
    }
    
    dg_forthfreebuffer(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotofilestringname);
        return;
    }
}


// ( codebufid exportsymbollisthlistid, exportsymbollistelementid
//   importsymbollisthlistid importsymbollistelementid -- codebufid )
void dg_forthbuftomachodotobuf (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;
    
    UINT64* pints;
    const char* pError;

    unsigned char* pcodebuf;
    UINT64* pcodebuflength;

    UINT64 destbufid, codebufid;
    UINT64 exportsymbollisthlistid, exportsymbollistparentelementid;
    UINT64 importsymbollisthlistid, importsymbollistparentelementid;
    
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
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    if ( *pdatastacklength < (5 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (5 * sizeof(UINT64)));
    
    codebufid = pints[0];
    exportsymbollistparentelementid = pints[1];
    exportsymbollisthlistid = pints[2];
    importsymbollistparentelementid = pints[3];
    importsymbollisthlistid = pints[4];
    

    destbufid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    pcodebuf = dg_getpbuffer(
        pBHarrayhead,
        codebufid,
        &pcodebuflength);

    if (pcodebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    dg_makedototobuf (
        pBHarrayhead,
        pcodebuf,
        *pcodebuflength,
        exportsymbollisthlistid,
        exportsymbollistparentelementid,
        importsymbollisthlistid,
        importsymbollistparentelementid,
        destbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbuftodotobufname);
        return;
    }

    pints[0] = destbufid;

    *pdatastacklength = *pdatastacklength - (4 * sizeof(UINT64));
}


// ( -- dotobufid )
void dg_forthosymbolbuftonewdotobuf (Bufferhandle* pBHarrayhead)
{
    unsigned char* pehstack = NULL;
    UINT64* pehstacklength = NULL;
    
    UINT64* pints;
    const char* pError;

    unsigned char* pcodebuf;
    UINT64* pcodebuflength;

    UINT64 destbufid, codebufid;
    UINT64 exportsymbollisthlistid, exportsymbollistparentelementid;
    UINT64 importsymbollisthlistid, importsymbollistparentelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    codebufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }

    pehstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &pehstacklength);

    if (pehstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }

    if ( *pehstacklength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }
    
    pints = (UINT64*)(pehstack + *pehstacklength - (4 * sizeof(UINT64)));

    importsymbollistparentelementid = pints[0];
    importsymbollisthlistid = pints[1];
    exportsymbollistparentelementid = pints[2];
    exportsymbollisthlistid = pints[3];
    
    destbufid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }

    pcodebuf = dg_getpbuffer(
        pBHarrayhead,
        codebufid,
        &pcodebuflength);

    if (pcodebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }

    dg_makedototobuf (
        pBHarrayhead,
        pcodebuf,
        *pcodebuflength,
        exportsymbollisthlistid,
        exportsymbollistparentelementid,
        importsymbollisthlistid,
        importsymbollistparentelementid,
        destbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        destbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotobufname);
        return;
    }
}


void dg_forthosymbolbuftonewdotofilestring (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthosymbolbuftonewdotobuf(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotofilestringname);
        return;
    }
    
    dg_forthdup(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotofilestringname);
        return;
    }

    dg_forthsavefilestring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotofilestringname);
        return;
    }
    
    dg_forthfreebuffer(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolbuftonewdotofilestringname);
        return;
    }
}


void dg_forthtestfindnumber (Bufferhandle* pBHarrayhead)
{
    UINT64 n;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtestfindnumbername);
        return;
    }
    
    n = dg_getfinddefinsearchordermetrics(
        pBHarrayhead,
        (unsigned char*)"123",
        3,
        n);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtestfindnumbername);
    }
    
    dg_pushdatastack(pBHarrayhead, n);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtestfindnumbername);
    }
}

void dg_forthminusrot (Bufferhandle* pBHarrayhead)           
//       ( n1 n2 n3 -- n3 n1 n2   )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 data = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthminusrotname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthminusrotname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    data = pints[0];
    pints[0] = pints[2];
    pints[2] = pints[1];
    pints[1] = data;
    
}

void dg_forthrandom(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        dg_random());
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_randomname);
        return;
    }
    
    return;
}

void dg_forthcompileu8s (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthcompileu8sname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)';',
            &foundendflag,
            FORTH_TRUE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcompileu8sname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors
                
            if (flag == FORTH_FALSE)
            {
                dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                dg_pusherror(pBHarrayhead, dg_forthcompileu8sname);
                return;
            }
            
            dg_compilesegment (
                pBHarrayhead, 
                (const char*)&data, // assumes data is little endian 
                1);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcompileu8sname);
                return;
            }
        }
    }
}

void dg_forthcompileu8scurly (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthcompileu8scurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcompileu8scurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors
                
            if (flag == FORTH_FALSE)
            {
                dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                dg_pusherror(pBHarrayhead, dg_forthcompileu8scurlyname);
                return;
            }
            
            dg_compilesegment (
                pBHarrayhead, 
                (const char*)&data, // assumes data is little endian 
                1);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcompileu8scurlyname);
                return;
            }
        }
    }
}

void dg_forthconstantscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthconstantscurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthconstantscurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthconstantscurlyname);
                    return;
                }
            }
            else
            {
                data = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthconstantscurlyname);
                    return;
                }
                
                dg_createconstantdef(
                    pBHarrayhead,
                    data,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthconstantscurlyname);
                    return;
                }
            }
        }
    }
}

void dg_forthconstants (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthconstantsname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)';',
            &foundendflag,
            FORTH_TRUE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthconstantsname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthconstantsname);
                    return;
                }
            }
            else
            {
                data = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthconstantsname);
                    return;
                }
                
                dg_createconstantdef(
                    pBHarrayhead,
                    data,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthconstantsname);
                    return;
                }
            }
        }
    }
}

void dg_forthfconstantscurly (Bufferhandle* pBHarrayhead)
{
    FLOAT64 fnumber;
    // UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    /*
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthfconstantscurlyname);
        return;
    }
    */
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthfconstantscurlyname);
            return;
        }

        if (namelength != 0)
        {
            // if (base == 10)
            // {
                fnumber = dg_pchartof64 (
                    pname,        // pnumber,
                    namelength,   // length,
                    &flag);
            // }
            // else
            // {
            //    flag = FORTH_FALSE;
            // }
                    
            if (flag != FORTH_FALSE)
            {
                // we have a floating point number, need to do the number
                // push the number to the data stack
                // if in compile mode, do literal
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_F64STACK_BUFFERID,
                    *((UINT64*)(&fnumber))); // cast used to avoid conversion

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthfconstantscurlyname);
                    return;
                } 
            }
            else
            {
                fnumber = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_F64STACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthf64stackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthfconstantscurlyname);
                    return;
                }
                
                dg_createfconstantdef(
                    pBHarrayhead,
                    fnumber,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthfconstantscurlyname);
                    return;
                }
            }
        }
    }
}

void dg_forthfconstants (Bufferhandle* pBHarrayhead)
{
    FLOAT64 fnumber;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)';',
            &foundendflag,
            FORTH_TRUE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthfconstantsname);
            return;
        }

        if (namelength != 0)
        {
            fnumber = dg_pchartof64 (
                pname,        // pnumber,
                namelength,   // length,
                &flag);

            if (flag != FORTH_FALSE)
            {
                // we have a floating point number, need to do the number
                // push the number to the data stack
                // if in compile mode, do literal
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_F64STACK_BUFFERID,
                    *((UINT64*)(&fnumber))); // cast used to avoid conversion

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthfconstantsname);
                    return;
                } 
            }
            else
            {
                fnumber = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_F64STACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthf64stackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthfconstantsname);
                    return;
                }
                
                dg_createfconstantdef(
                    pBHarrayhead,
                    fnumber,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthfconstantsname);
                    return;
                }
            }
        }
    }
}

void dg_forthlocalconstants (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 localswordlistid;
    UINT64 localwordid;

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
        dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)';',
            &foundendflag,
            FORTH_TRUE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
                    return;
                }
            }
            else
            {
                data = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
                    return;
                }
                
                /*
                dg_createconstantdef(
                    pBHarrayhead,
                    data,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
                */
                
                localwordid = dg_newwordcopyname (
                    pBHarrayhead,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)&dg_forthdocompiletypedpushn,
                    0, // databufid,
                    data, // databufoffset,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)pname,
                    namelength);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
                    return;
                }
                    
                dg_linkdefinition(
                    pBHarrayhead,
                    localswordlistid,
                    localwordid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantsname);
                    return;
                }
            }
        }
    }
}

void dg_forthlocalconstantscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;

    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 localswordlistid;
    UINT64 localwordid;

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
        dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
            }
            else
            {
                data = dg_popbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
                
                /*
                dg_createconstantdef(
                    pBHarrayhead,
                    data,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
                */
                
                localwordid = dg_newwordcopyname (
                    pBHarrayhead,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)&dg_forthdocompiletypedpushn,
                    0, // databufid,
                    data, // databufoffset,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)pname,
                    namelength);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
                    
                dg_linkdefinition(
                    pBHarrayhead,
                    localswordlistid,
                    localwordid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalconstantscurlyname);
                    return;
                }
            }
        }
    }
}


void dg_forthvariablescurly (Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 dsbufid;
    const char* pError;
    UINT64 oldlength, currentlength;
    UINT64 data, base, flag;
    
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
        dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
        return;
    }
    
    oldlength = dg_getbufferlength(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    while (foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
            return;
        }
        
        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
                    return;
                }
            }
            else
            {
                dg_createvariabledef(
                    pBHarrayhead,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
                    return;
                }
                
                dsbufid = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    currentvariablebuffer);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
                    dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
                    return;
                }
                
                currentlength = dg_getbufferlength(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);
                
                if (currentlength > oldlength)
                {
                    data = dg_popbufferuint64(
                        pBHarrayhead,
                        DG_DATASTACK_BUFFERID);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                        dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
                        return;
                    }
                }
                else
                {
                    data = 0;
                }
                
                dg_pushbufferuint64 (
                    pBHarrayhead,
                    dsbufid,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
                    dg_pusherror(pBHarrayhead, dg_forthvariablescurlyname);
                    return;
                }
                
            }
        }
    }
    
    return;
}

void dg_forthvariables (Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 dsbufid;
    const char* pError;
    UINT64 oldlength, currentlength;
    UINT64 data, base, flag;
    
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
        dg_pusherror(pBHarrayhead, dg_forthvariablesname);
        return;
    }
    
    oldlength = dg_getbufferlength(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    while (foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)';',
            &foundendflag,
            FORTH_TRUE);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthvariablesname);
            return;
        }
        
        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                dg_pushbufferuint64(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                    dg_pusherror(pBHarrayhead, dg_forthvariablesname);
                    return;
                }
            }
            else
            {
                dg_createvariabledef(
                    pBHarrayhead,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthvariablesname);
                    return;
                }
                
                dsbufid = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    currentvariablebuffer);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
                    dg_pusherror(pBHarrayhead, dg_forthvariablesname);
                    return;
                }
                
                currentlength = dg_getbufferlength(
                    pBHarrayhead,
                    DG_DATASTACK_BUFFERID);
                
                if (currentlength > oldlength)
                {
                    data = dg_popbufferuint64(
                        pBHarrayhead,
                        DG_DATASTACK_BUFFERID);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                        dg_pusherror(pBHarrayhead, dg_forthvariablesname);
                        return;
                    }
                }
                else
                {
                    data = 0;
                }
                
                dg_pushbufferuint64 (
                    pBHarrayhead,
                    dsbufid,
                    data);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
                    dg_pusherror(pBHarrayhead, dg_forthvariablesname);
                    return;
                }
                
            }
        }
    }
    
    return;
}


const char* dg_forthloadlibrarystringsubname = "dg_forthloadlibrarystringsub";

void dg_forthloadlibrarystringsub(Bufferhandle* pBHarrayhead)
//     ( libraryname$ -$- )
//     ( -openlibraryhandlestack- libraryhandle )
{
    UINT64 numberofstringsonstack = 0;
    unsigned char* pnamelstring = NULL;
    UINT64 namelength = 0;
    const char* flag;

    UINT64 libraryhandle = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }

    if (numberofstringsonstack < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }

    dg_forthturnstringinto0string(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }

    pnamelstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        numberofstringsonstack - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }

    flag = dg_loadlibrary(
        (const char*)pnamelstring,
        &libraryhandle,
        dg_success);

    if (flag != dg_success)
    {
        // libraryhandle is -1, want to still return a value
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            libraryhandle);

        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_loadlibraryname);
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;

    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID,
        libraryhandle);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibhandlebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
        return;
    }
}


void dg_forthbrackettoorderconstant (Bufferhandle* pBHarrayhead)
//                 ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//                 ( n1 -- )
{
    UINT64 data = 0;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    data = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthbrackettoorderconstantname);
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbrackettoorderconstantname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthbrackettoorderconstantname);
        return;
    }

    dg_createbrackettoorderconstantdef(
        pBHarrayhead,
        data,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbrackettoorderconstantname);
        return;
    }
}


void dg_forthsizedconstantscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 data = 0;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 defaultvalue = 0;
    UINT64 defaultsize = 1;
    UINT64 gotnewsizealready = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthsizedconstantscurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthsizedconstantscurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                if (FORTH_FALSE == gotnewsizealready)
                {
                    defaultsize = data;
                    gotnewsizealready = FORTH_TRUE;
                }
                else
                {
                    defaultvalue = defaultsize;
                    defaultsize = data;
                }
            }
            else
            {
                gotnewsizealready = FORTH_FALSE;
                
                dg_createdconstantdef(
                    pBHarrayhead,
                    defaultvalue, // nlo
                    defaultsize,  // nhi
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthsizedconstantscurlyname);
                    return;
                }
                
                defaultvalue += defaultsize;
            }
        }
    }
}


void dg_forthenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;        
    UINT64 stepsize; 
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    value = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
        return;
    }
    
    stepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
                        return;
                }
                
                numbersinarow++;
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                dg_createconstantdef(
                    pBHarrayhead,
                    value,
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthenumcurlyname);
        return;
    }
}


void dg_forthlocalenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;
    UINT64 stepsize; 
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;
    
    UINT64 localwordid;
    UINT64 localswordlistid;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    value = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
        return;
    }
    
    stepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
                        return;
                }
                
                numbersinarow++; 
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                localwordid = dg_newwordcopyname (
                    pBHarrayhead,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)&dg_forthdocompiletypedpushn,
                    0, // databufid,
                    value, // databufoffset,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
                    return;
                }
                
                dg_linkdefinition(
                    pBHarrayhead,
                    localswordlistid,
                    localwordid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {       
                    dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthlocalenumcurlyname);
        return;
    }
}


void dg_forthbracketlocalenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;
    UINT64 stepsize; 
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;
    
    UINT64 localwordid;
    UINT64 localswordlistid;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    value = 0;
    stepsize = 1;
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
                        return;
                }
                
                numbersinarow++; 
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                localwordid = dg_newwordcopyname (
                    pBHarrayhead,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)&dg_forthdocompiletypedpushn,
                    0, // databufid,
                    value, // databufoffset,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
                    return;
                }
                
                dg_linkdefinition(
                    pBHarrayhead,
                    localswordlistid,
                    localwordid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {       
                    dg_pusherror(pBHarrayhead, dg_forthbracketlocalenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
}


void dg_forthtypedenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;        
    UINT64 stepsize;
    
    UINT64 type; 
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    type = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
        return;
    }
    
    value = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
        return;
    }
    
    stepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    case 2:
                        type = data;
                        break;
                        
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
                        return;
                }
                
                numbersinarow++;
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                dg_createdconstantdef(
                    pBHarrayhead,
                    value, // nlo
                    type,  // nhi
                    pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthtypedenumcurlyname);
        return;
    }
}

void dg_forthtypedlocalenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;
    UINT64 stepsize; 
    
    UINT64 type;
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;
    
    UINT64 localwordid;
    UINT64 localswordlistid;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    type = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
    
    value = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
    
    stepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    case 2:
                        type = data;
                        break;
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
                        return;
                }
                
                numbersinarow++; 
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                localwordid = dg_newwordcopyname (
                    pBHarrayhead,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)&dg_forthdocompiletypedpushdn,
                    type, // databufid,
                    value, // databufoffset,
                    (UINT64)DG_CORE_BUFFERID,
                    (UINT64)pname,
                    namelength);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
                    return;
                }
                
                dg_linkdefinition(
                    pBHarrayhead,
                    localswordlistid,
                    localwordid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {       
                    dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthtypedlocalenumcurlyname);
        return;
    }
}

void dg_forthbenchmark(Bufferhandle* pBHarrayhead)
// ( coreroutineaddr durationinmicroseconds -- finaldurationinmicroseconds numberdone )
{
    UINT64 durationinmicroseconds;
    UINT64 numberdone = 0;
    UINT64 starttime;
    UINT64 endtime;
    void (*coreroutineaddr)(Bufferhandle*);

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    durationinmicroseconds = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
        return;
    }

    coreroutineaddr = (void (*)(Bufferhandle*))dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
        return;
    }

    starttime = dg_getmicrosecondssince1970Jan01();

    while(dg_getmicrosecondssince1970Jan01() < (starttime + durationinmicroseconds))
    {
        coreroutineaddr(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {       
            dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
            return;
        }

        numberdone++;
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
        return;
    }

    endtime = dg_getmicrosecondssince1970Jan01();

    dg_pushdatastack(
        pBHarrayhead,
        endtime - starttime);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        numberdone);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbenchmarkname);
        return;
    }
}


void dg_forthn8tocell (Bufferhandle* pBHarrayhead)
//      ( n8 -- n64 )
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
        dg_pusherror(pBHarrayhead, dg_forthn8tocellname);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthn8tocellname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = (UINT64)dg_n8ton64(pints[0]);

    // no error possible
}


void dg_forthn16tocell (Bufferhandle* pBHarrayhead)
//      ( n16 -- n64 )
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
        dg_pusherror(pBHarrayhead, dg_forthn16tocellname);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthn16tocellname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = (UINT64)dg_n16ton64(pints[0]);

    // no error possible
}


void dg_forthn32tocell (Bufferhandle* pBHarrayhead)
//      ( n32 -- n64 )
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
        dg_pusherror(pBHarrayhead, dg_forthn32tocellname);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthn32tocellname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = (UINT64)dg_n32ton64(pints[0]);

    // no error possible
}
