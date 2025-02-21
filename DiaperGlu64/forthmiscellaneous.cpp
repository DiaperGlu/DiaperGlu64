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

void dg_forthevaluatebuffer (Bufferhandle* pBHarrayhead)
//      ( bufferid -- )
{
    UINT64 bufferid;

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

    bufferid = pints[0];

    *pbuflength = *pbuflength - sizeof(UINT64);

    dg_evaluatebuffer(
        pBHarrayhead,
        bufferid);

    // not returning error here on purpose
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


//////////////////////////////////////////////////////////////////////
// dg_forthcompilesafecallbuffer is in each processor specific file //
//////////////////////////////////////////////////////////////////////



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
    unsigned char* pcolorok = (unsigned char*)"\nCOLOR-OK>"; 

    unsigned char* perrorsok = (unsigned char*)"items on error stack, error(s) with trace.\n use SHOW-ERRORS or .ES to see\n use EMPTY-ERRORS or EES to clear\n use .ERRORLINE or .EL to see the line that caused the error\n\nOK>"; 

    const char* pstate;
    UINT64 colorstate;

    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        // got an error - force interpret state and display error prompt
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colorstate,
            DG_COLORSTATE_INTERPRET);

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

        colorstate = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colorstate);
    
        if (dg_geterrorcount(pBHarrayhead) != 0)
        {
            dg_pusherror(pBHarrayhead, dg_forthdopromptname);
            return;
        }

        // if in interpret state, need to display OK>
        if ( (colorstate == DG_COLORSTATE_INTERPRET) && (pstate == dg_stateexecute) )
        {
            dg_printzerostring(
                pBHarrayhead,
                pok);
        }

        // if in color execute state, need to display COLOR-OK>
        if (colorstate == DG_COLORSTATE_EXECUTE)
        {
            dg_printzerostring(
                pBHarrayhead,
                pcolorok);
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

/*
// moved to a compile type routine to be compatible with color states for v5.14
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
*/

/*
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
*/


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


void dg_forthulo1bits (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthulo1bitsname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulo1bitsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
    
    pints[0] = dg_getulowestsetbits(pints[0], pints[1]);

    (*pdatastacklength) -= sizeof(UINT64);
}


void dg_forthulo1bitpos (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthulo1bitposname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulo1bitposname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
    
    pints[0] = dg_scanforuthsetbit(pints[0], pints[1]);

    (*pdatastacklength) -= sizeof(UINT64);
}


void dg_forthulobits (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthulobitsname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulobitsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
    
    pints[0] = dg_getulowestbits(pints[0], pints[1]);

    (*pdatastacklength) -= sizeof(UINT64);
}


void dg_forthulomask (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthulomaskname);
        return;
    }

    if ( *pdatastacklength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulomaskname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (1 * sizeof(UINT64)));
    
    pints[0] = dg_getulowestbitsmask(pints[0]);
}


void dg_forthtwototheu (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthtwototheuname);
        return;
    }

    if ( *pdatastacklength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwototheuname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (1 * sizeof(UINT64)));
    
    if (pints[0] > 0x3F)
    {
        pints[0] = largestunsignedint;
        return;
    }
   
    pints[0] = dg_twototheu(pints[0]);
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


// ( u bitoffset -- u' )
void dg_forthbitset (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthbitsetname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbitsetname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    pints[0] = dg_setbit(pints[0], pints[1]);

    *pdatastacklength -= sizeof(UINT64);
}


// ( u bitoffset -- u' )
void dg_forthbitclr (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthbitclrname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbitclrname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    pints[0] = dg_clrbit(pints[0], pints[1]);

    *pdatastacklength -= sizeof(UINT64);
}


// ( u bitoffset -- u' )
void dg_forthbitnot (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthbitnotname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthbitnotname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    pints[0] = dg_notbit(pints[0], pints[1]);

    *pdatastacklength -= sizeof(UINT64);
}


// ( u1 u2 -- u1oru2 )
void dg_forthumax (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthumaxname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthumaxname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    if (pints[1] > pints[0])
    {
        pints[0] = pints[1];
    }

    *pdatastacklength -= sizeof(UINT64);
}


// ( u1 u2 -- u1oru2 )
void dg_forthumin (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthuminname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthuminname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    if (pints[1] < pints[0])
    {
        pints[0] = pints[1];
    }

    *pdatastacklength -= sizeof(UINT64);
}


// ( u1 u2 -- flag )
void dg_forthulessthanequals (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthulessthanequalsname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulessthanequalsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    if (pints[0] <= pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pdatastacklength -= sizeof(UINT64);
}


// ( u1 u2 -- flag )
void dg_forthugreaterthanequals (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthugreaterthanequalsname);
        return;
    }

    if ( *pdatastacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthugreaterthanequalsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)));
   
    if (pints[0] >= pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pdatastacklength -= sizeof(UINT64);
}


// ( -$- post$ )
void dg_forthgetpoststring (Bufferhandle* pBHarrayhead)
{
    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        DG_POST_BUFFERID,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthgetpoststringname);
        return;
    }

    dg_stonewstring(
        pBHarrayhead,
        pbuffer,
        *pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthgetpoststringname);
        return;
    }
}


void dg_forthtoxtpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_compilecallcore (
        pBHarrayhead,
        (UINT64)&dg_popdatastack);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthtoxtpcommaname);
        return;
    }

    dg_compilejumptorax (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthtoxtpcommaname);
        return;
    }
}


void dg_forthci (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colorstate,
        DG_COLORSTATE_INTERPRET);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthciname);
        return;
    }
}


void dg_forthcleftbracket (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colorstate,
        DG_COLORSTATE_EXECUTE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcleftbracketname);
        return;
    }
}


void dg_forthcrightbracket (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colorstate,
        DG_COLORSTATE_COMPILE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcrightbracketname);
        return;
    }
}


void dg_forthcp (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colorstate,
        DG_COLORSTATE_POSTPONE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcpname);
        return;
    }
}


void dg_forthcleftparen (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colorstate,
        DG_COLORSTATE_COMMENT);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcleftparenname);
        return;
    }
}


void dg_forthcodemescomma (Bufferhandle* pBHarrayhead)
{
    UINT64 afterbranchoffset;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        dg_codemes_sys);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescommaname);
        return;
    }

}


void dg_forthcodemecomma (Bufferhandle* pBHarrayhead)
{
    UINT64 blockcount;
    UINT64 blocksysmarker;
    UINT64 afterbranchoffset;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    blocksysmarker = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    if (blocksysmarker != dg_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEME-SYS missing\n");
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    blockcount = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        blockcount + 1); // gonna assume it won't overflow

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        dg_codemes_sys);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemecommaname);
        return;
    }

}


void dg_forthendcodemescomma (Bufferhandle* pBHarrayhead)
{
    UINT64 blockcount;
    UINT64 blocksysmarker;
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    blocksysmarker = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    if (blocksysmarker != dg_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-SYS missing\n");
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    blockcount = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        blockcount); // gonna assume it won't overflow

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        0); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        dg_end_codemes_sys);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthendcodemescommaname);
        return;
    }
}


void dg_forthquerynotequals (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthquerynotequalsname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthquerynotequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    if (pints[0] != pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthqueryugreaterthan (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthqueryugreaterthanname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthqueryugreaterthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    if (pints[0] > pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthquerygreaterthan (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

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
        dg_pusherror(pBHarrayhead, dg_forthquerygreaterthanname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthquerygreaterthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2*sizeof(INT64)));

    if (pints[0] > pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(INT64);
    }
}


void dg_forthqueryugreaterthanequals (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthqueryugreaterthanequalsname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthqueryugreaterthanequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    if (pints[0] >= pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthquerygreaterthanequals (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

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
        dg_pusherror(pBHarrayhead, dg_forthquerygreaterthanequalsname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthquerygreaterthanequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2*sizeof(INT64)));

    if (pints[0] >= pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthqueryulessthan (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    if (pints[0] < pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthquerylessthan (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

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
        dg_pusherror(pBHarrayhead, dg_forthquerylessthanname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthquerylessthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2*sizeof(INT64)));

    if (pints[0] < pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthqueryulessthanequals (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanequalsname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    if (pints[0] <= pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthquerylessthanequals (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

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
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanequalsname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthqueryulessthanequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2*sizeof(INT64)));

    if (pints[0] <= pints[1])
    {
        pints[1] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthbeginsystopcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 ccbufid;
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
        dg_pusherror(pBHarrayhead, dg_forthbeginsystopcommaname);
        return;
    }

    dg_compilepushntodatastack(
        pBHarrayhead,
        ccbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbeginsystopcommaname);
        return;
    }

    dg_compilecallcore (
        pBHarrayhead,
        (UINT64)&dg_forthgetpbufferoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthbeginsystopcommaname);
        return;
    }
}


void dg_forthnumbercodemes (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthnumbercodemesname);
        return;
    }

    if (*pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnumbercodemesname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3*sizeof(UINT64)));

    dg_pushdatastack(
        pBHarrayhead,
        pints[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnumbercodemesname);
        return;
    }
}


void dg_forthcodemescurrentplusplus (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthcodemescurrentplusplusname);
        return;
    }

    if (*pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemescurrentplusplusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

    (pints[0])++;
}


void dg_forthquerycodemescurrent (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthquerycodemescurrentname);
        return;
    }

    if (*pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthquerycodemescurrentname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3*sizeof(UINT64)));

    if (pints[2] >= pints[1])
    {
        dg_pusherror(pBHarrayhead, (const char*)"Current block is not in blocks table. (Probably too many CODEMES-OF,)");
        dg_pusherror(pBHarrayhead, dg_forthquerycodemescurrentname);
        return;
    }
}


void dg_forthcodemeuifsys (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    UINT64 codemetopick;
    UINT64 x;
    UINT64 depth;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemeuifsysname);
        return;
    }

    if (*pbuflength < (4*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemeuifsysname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4*sizeof(UINT64)));

    numberofcodemes = pints[0];
    codemetopick = pints[3];

    if ( (codemetopick >= numberofcodemes) && (codemetopick != (UINT64)-1) )
    {
        dg_pusherror(pBHarrayhead, (const char*)"- codeme index too high");
        dg_pusherror(pBHarrayhead, dg_forthcodemeuifsysname);
        return;
    }

    depth = (*pbuflength)/sizeof(UINT64);
    
    pints[3] = ((UINT64*)pdatastack)[(depth + codemetopick) - (numberofcodemes+4)];   
}


void dg_forthcodemeubeginsys (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    UINT64 codemetopick;
    UINT64 x;
    UINT64 depth;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemeubeginsysname);
        return;
    }

    if (*pbuflength < (4*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemeubeginsysname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4*sizeof(UINT64)));

    numberofcodemes = pints[0];
    codemetopick = pints[3];

    if (codemetopick >= numberofcodemes)
    {
        dg_pusherror(pBHarrayhead, (const char*)"- codeme index too high");
        dg_pusherror(pBHarrayhead, dg_forthcodemeubeginsysname);
        return;
    }

    depth = (*pbuflength)/sizeof(UINT64);
    
    pints[3] = ((UINT64*)pdatastack)[(depth + codemetopick) - (numberofcodemes+5)];   
}


void dg_forthcodemesdrop (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    UINT64 depth;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemesdropname);
        return;
    }

    if (*pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesdropname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3*sizeof(UINT64)));

    numberofcodemes = pints[0];

    depth = (*pbuflength)/sizeof(UINT64);
    
    if ((numberofcodemes + 4) > depth)
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesdropname);
        return;
    }  

    (*pbuflength) -= ((numberofcodemes + 4) * sizeof(UINT64));  
}


void dg_forthcodemesresolvestart (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushdatastack(
        pBHarrayhead, 
        (UINT64)-1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolvestartname);
        return;
    }

    dg_forthcodemeuifsys(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolvestartname);
        return;
    }

    dg_forththen(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolvestartname);
        return;
    }
}


void dg_forthcodemesresolveends (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    
    UINT64 x, i;
    UINT64 depth;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolveendsname);
        return;
    }

    if (*pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolveendsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3*sizeof(UINT64)));

    numberofcodemes = pints[0];

    depth = (*pbuflength)/sizeof(UINT64);

    if ((numberofcodemes + 3) > depth)
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesresolveendsname);
        return;
    }
    
    pints = (UINT64*)(pdatastack + *pbuflength - ((numberofcodemes +3)*sizeof(UINT64)));

    for (i = 0; i < numberofcodemes; i++)
    {
        x = pints[i];

        dg_pushdatastack(
            pBHarrayhead,
            x);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {       
            dg_pusherror(pBHarrayhead, dg_forthcodemesresolveendsname);
            return;
        }

        dg_forththen(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {       
            dg_pusherror(pBHarrayhead, dg_forthcodemesresolveendsname);
            return;
        }
    } 
}


void dg_forthcodemescasecomma (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    x = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescasecommaname);
        return;
    }

    if (x != dg_end_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"END-CODEMES-SYS missing.");
        dg_pusherror(pBHarrayhead, dg_forthcodemescasecommaname);
        return;
    }

    dg_pushdatastack(
        pBHarrayhead, 
        dg_codemes_case_sys);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescasecommaname);
        return;
    }

    dg_forthcodemesresolvestart(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemescasecommaname);
        return;
    }
}


const char* dg_codemesquerybranchcommaname = "dg_codemesquerybranchcomma";

void dg_codemesquerybranchcomma (
    Bufferhandle* pBHarrayhead,
    UINT64 branchcode)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    
    UINT64 x, i;
    UINT64 depth;
    UINT64 codemestablestate;
    UINT64 codemescurrent;
    UINT64 casevalue;

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
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }

    if (*pbuflength < (4*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4*sizeof(UINT64)));

    numberofcodemes = pints[0];
    codemescurrent = pints[1];
    codemestablestate = pints[2];
    casevalue = pints[3];

    depth = (*pbuflength)/sizeof(UINT64);

    if ((numberofcodemes + 4) > depth)
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }
    
    if (codemestablestate != dg_codemes_case_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"BLOCKS-CASE-SYS missing");
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }

    if (codemescurrent >= numberofcodemes)
    {
        dg_pusherror(pBHarrayhead, (const char*)"Current codeme not in table. (too many CODEMES-OF,s)");
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }

    // can do the next couple more efficiently in assembler
    //   put codemescurrent on top for dg_forthcodemeubeginsys
    pints[3] = codemescurrent;

    dg_forthcodemeubeginsys(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }

    dg_compilequeryuequalsbranch (
        pBHarrayhead,
        casevalue,
        branchcode,
        pints[3]); // pints[3] now holds begin-sys

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_codemesquerybranchcommaname);
        return;
    }
    
    // increment current block
    pints[1]++;

    // drop casevalue
    *pbuflength -= sizeof(UINT64);
}


void dg_forthcodemesofcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_codemesquerybranchcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesofcommaname);
        return;
    }
}


void dg_forthcodemesendcasecomma (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    x = dg_getuint64stackelement (
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesendcasecommaname);
        return;
    }

    if (x != dg_codemes_case_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-CASE-SYS missing.");
        dg_pusherror(pBHarrayhead, dg_forthcodemesendcasecommaname);
        return;
    }

    dg_forthcodemesresolveends(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesendcasecommaname);
        return;
    }

    dg_forthcodemesdrop(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthcodemesendcasecommaname);
        return;
    }
}


void dg_forthcodemescasescomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 numberofcodemes;
    UINT64 numberofcases;
    
    
    UINT64 x, i;
    UINT64 depth;

    UINT64 ccbufid;
    UINT64 ccbuflength;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    if ( *pbuflength < (1*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    numberofcases = pints[depth-1];

    if ( ((2*numberofcases) + 5) > depth)
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    if (pints[depth - (numberofcases + 2)] != dg_end_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"END-BLOCKS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }
    
    numberofcodemes = pints[depth - (numberofcases + 4)];

    if (numberofcodemes != numberofcases)
    {
        dg_pusherror(pBHarrayhead, (const char*)"number of codemes does not equal number of cases");
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    // need to resolve start
    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }
    
    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    // 11 10 9 8   7 6      5 4 3 2   1 0
    // -1  0 1 2 u=3 i marker 0 1 2 u=3
    dg_resolvecompiledbranch (
        pBHarrayhead,
        pints[depth - ((numberofcases*2)+ 5)], // afterbranchoffset,
        ccbuflength); // targetoffset)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    // get switch value into iret reg
    dg_compilecallcoretwouparams (
        pBHarrayhead, 
        (UINT64)&dg_popbufferuint64, 
        DG_DATASTACK_BUFFERID,
        0); // get stack top

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    for (i = 0; i < numberofcases; i++)
    {
        x = numberofcases - (i+1);

        dg_compilecompareiretu64branch (
            pBHarrayhead,
            pints[depth - (x+2)], // casevalue
            DG_BRANCHTYPE_EQUAL,
            pints[depth - (x+numberofcases+6)]); // begin-sys

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
            return;
        }
    }

    dg_compilemovregtoreg(
         pBHarrayhead,
         dg_iretreg,
         dg_param2reg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    dg_compilecallcore (
        pBHarrayhead, 
        (UINT64)&dg_pushdatastack); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemescasescommaname);
        return;
    }

    *pbuflength -= (numberofcases + 1)*sizeof(UINT64);
    depth -= (numberofcases + 1);

    // need to make top of stack codemes-case-sys
    pints[depth - 1] = dg_codemes_case_sys;
}


void dg_forthcodemesjumpscomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;

    UINT64 ccbufid;
    UINT64 ccbuflength;

    UINT64 numberofcases;

    UINT64 rsdepth;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    if ( *pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 1] != dg_end_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"END-CODEMES-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    // need to resolve start
    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }
    
    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    numberofcases = pints[depth - 3];

    //  7  6 5 4   3 2      1 0
    // -1  0 1 2 u=3 i marker
    dg_resolvecompiledbranch (
        pBHarrayhead,
        pints[depth - (numberofcases + 4)], // afterbranchoffset,
        ccbuflength); // targetoffset)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    rsdepth = dg_compileaddnlocalstocallsubsframe (
        pBHarrayhead,
        1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    // get switch value into new return stack local variable
    // rsdepth = dg_getbufferuint64(
    //    pBHarrayhead,
    //    DG_DATASPACE_BUFFERID,
    //    dg_returnstackdepth);

    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
    //    return;
    // }

    // if there is any chance the rsdepth might change.... like for instance
    //   if you nest block-jump statements... need to save it
    pints[depth - 2] = rsdepth * (-1) * sizeof(UINT64);

    dg_compilecallcoretwouparams (
        pBHarrayhead, 
        (UINT64)&dg_popbufferuint64,
        DG_DATASTACK_BUFFERID,
        0); // get stack top

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    dg_compilemovregtobracketrbpd (
        pBHarrayhead,
        dg_iretreg,
        rsdepth * (-1) * sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumpscommaname);
        return;
    }

    // need to make top of stack blocks-case-sys
    pints[depth - 1] = dg_codemes_jump_sys;
}


const char* dg_xcodemeconditionjumpcommaname = "dg_xcodemeconditionjumpcomma";

void dg_xcodemeconditionjumpcomma (
    Bufferhandle* pBHarrayhead,
    UINT64 branchtype)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;

    UINT64 numberofcodemes;
    INT64 switchvaluedisplacement;
    UINT64 destinationcodeme;
    UINT64 casevalue;

    UINT64 afterbranchoffset;
    UINT64 beginoffset;
    UINT64 x;

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
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    if ( *pbuflength < (5*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 3] != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-JUMPS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    
    destinationcodeme = pints[depth - 1];
    casevalue = pints[depth-2];
    switchvaluedisplacement = pints[depth - 4];
    numberofcodemes = pints[depth - 5];

/*
    dg_compilemovntoreg(
        pBHarrayhead,
        casevalue,
        dg_iretreg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    // once I add compare [rbp + n] with reg, I can combine these
    dg_compilemovbracketrbpdtoreg (
        pBHarrayhead,
        dg_param1reg,
        switchvaluedisplacement);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    dg_compilecompareir64ir64(
        pBHarrayhead,
        dg_iretreg,    // srcreg,
        dg_param1reg); // destreg)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }
*/

    dg_compilecomparenbracketrbpplusn (
        pBHarrayhead,
        casevalue, //nsrc,
        switchvaluedisplacement); // ndisplacement)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        branchtype);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    // -9  -8  -7  -6  -5                -4 -3     -2        -1                0
    // bo0 bo1 bo2 eo2 numberofcodemes=3 i  marker casevalue destinationcodeme

    if (destinationcodeme >= numberofcodemes)
    {
        dg_pusherror(pBHarrayhead, (const char*)"destination codeme is not in codeme table");
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    } 

    if ((numberofcodemes + 6) > depth)
    {
        dg_pusherror(pBHarrayhead, (const char*)"data stack depth seems too small to hold the whole codeme table");
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    x = ( (numberofcodemes + 6) - destinationcodeme );

    dg_resolvecompiledbranch (
        pBHarrayhead,
        afterbranchoffset,
        pints[depth - x]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    *pbuflength -= 2*sizeof(UINT64);
}


void dg_forthcodemealwaysjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;

    UINT64 numberofcodemes;
    UINT64 destinationcodeme;

    UINT64 afterbranchoffset;
    UINT64 beginoffset;
    UINT64 x;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    if ( *pbuflength < (5*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 2] != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-JUMPS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    destinationcodeme = pints[depth - 1];
    numberofcodemes = pints[depth - 4];

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    // -8  -7  -6  -5  -4                -3 -2     -1                0
    // bo0 bo1 bo2 eo2 numberofcodemes=3 i  marker destinationcodeme

    if (destinationcodeme >= numberofcodemes)
    {
        dg_pusherror(pBHarrayhead, (const char*)"destination codeme is not in codeme table");
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    } 

    if ((numberofcodemes + 5) > depth)
    {
        dg_pusherror(pBHarrayhead, (const char*)"data stack depth seems too small to hold the whole codeme table");
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    x = ( (numberofcodemes + 5) - destinationcodeme );

    dg_resolvecompiledbranch (
        pBHarrayhead,
        afterbranchoffset,
        pints[depth - x]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemealwaysjumpcommaname);
        return;
    }

    *pbuflength -= 1*sizeof(UINT64);
}



void dg_forthxcodemevsjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_OVERFLOW);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemevsjumpcommaname);
        return;
    }
}

void dg_forthxcodemenvjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_NOOVERFLOW);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemenvjumpcommaname);
        return;
    }
}

void dg_forthxcodemeulessthanjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_ULESSTHAN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemeulessthanjumpcommaname);
        return;
    }
}

void dg_forthxcodemeugreaterthanequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_UGREATERTHANOREQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemeugreaterthanequaljumpcommaname);
        return;
    }
}

void dg_forthxcodemeequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemeequaljumpcommaname);
        return;
    }
}

void dg_forthxcodemenotequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_NOTEQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemenotequaljumpcommaname);
        return;
    }
}

void dg_forthxcodemeulessthanequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_ULESSTHANOREQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemeulessthanequaljumpcommaname);
        return;
    }
}

void dg_forthxcodemeugreaterthanjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_UGREATERTHAN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemeugreaterthanjumpcommaname);
        return;
    }
}

void dg_forthxcodememijumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_MINUS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodememijumpcommaname);
        return;
    }
}

void dg_forthxcodemepljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_PLUS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemepljumpcommaname);
        return;
    }
}

void dg_forthxcodemepsjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_PARITYEVEN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemepsjumpcommaname);
        return;
    }
}

void dg_forthxcodemenpjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_PARITYODD);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemenpjumpcommaname);
        return;
    }
}

void dg_forthxcodemelessthanjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_LESSTHAN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemelessthanjumpcommaname);
        return;
    }
}

void dg_forthxcodemegreaterthanjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_GREATERTHAN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemegreaterthanjumpcommaname);
        return;
    }
}

void dg_forthxcodemelessthanequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_LESSTHANOREQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemelessthanequaljumpcommaname);
        return;
    }
}

void dg_forthxcodemegreaterthanequaljumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_xcodemeconditionjumpcomma (
        pBHarrayhead,
        DG_BRANCHTYPE_GREATERTHANOREQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxcodemegreaterthanequaljumpcommaname);
        return;
    }
}


void dg_forthcodemesendjumpscomma (Bufferhandle* pBHarrayhead)
{
    UINT64 codemesstatemarker;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    codemesstatemarker = dg_getuint64stackelement(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesendjumpscommaname);
        return;
    }

    if (codemesstatemarker != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES_JUMP_SYS state marker missing");
        dg_pusherror(pBHarrayhead, dg_forthcodemesendjumpscommaname);
        return;
    }

    dg_forthcodemesresolveends(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesendjumpscommaname);
        return;
    }

    dg_forthcodemesdrop(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesendjumpscommaname);
        return;
    }
}


void dg_forthxycodemewithinjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;

    UINT64 numberofcodemes;
    INT64 switchvaluedisplacement;
    UINT64 destinationcodeme;
    UINT64 casevaluelo;
    UINT64 casevaluehi;

    UINT64 afterbranchoffset;
    UINT64 beginoffset;
    UINT64 x;

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
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    if ( *pbuflength < (6*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 4] != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-JUMPS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    
    destinationcodeme = pints[depth - 1];
    casevaluehi = pints[depth-2];
    casevaluelo = pints[depth-3] - 1;
    switchvaluedisplacement = pints[depth - 5];
    numberofcodemes = pints[depth - 6];

    dg_compilemovntoreg(
        pBHarrayhead,
        casevaluelo,
        dg_param1reg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    dg_compilesubbracketrbpplusnreg (
        pBHarrayhead,
        switchvaluedisplacement,
        dg_param1reg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    dg_compilecomparenreg(
        pBHarrayhead,
        (UINT64)(casevaluelo - casevaluehi),   // srcn,
        dg_param1reg);               // destreg)

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthxycodemewithinjumpcommaname);
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_UGREATERTHAN);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    // -10 -9  -8  -7  -6                -5 -4     -3          -2                -1                0
    // bo0 bo1 bo2 eo2 numberofcodemes=3 i  marker casevaluelo casevaluehi       destinationcodeme

    if (destinationcodeme >= numberofcodemes)
    {
        dg_pusherror(pBHarrayhead, (const char*)"destination codeme is not in codeme table");
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    } 

    if ((numberofcodemes + 7) > depth)
    {
        dg_pusherror(pBHarrayhead, (const char*)"data stack depth seems too small to hold the whole codeme table");
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    x = ( (numberofcodemes + 7) - destinationcodeme );

    dg_resolvecompiledbranch (
        pBHarrayhead,
        afterbranchoffset,
        pints[depth - x]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_xcodemeconditionjumpcommaname);
        return;
    }

    *pbuflength -= 3*sizeof(UINT64);
}


void dg_forthdefaultjumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;

    INT64 switchvaluedisplacement;

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
        dg_pusherror(pBHarrayhead, dg_forthdefaultjumpcommaname);
        return;
    }

    if ( *pbuflength < (2*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdefaultjumpcommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 1] != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-JUMPS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthdefaultjumpcommaname);
        return;
    }

    switchvaluedisplacement = pints[depth - 2];

    dg_compilemovbracketrbpdtoreg(
        pBHarrayhead,
        dg_param2reg,
        switchvaluedisplacement);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdefaultjumpcommaname);
        return;
    }

    dg_compilecallcore (
        pBHarrayhead,
        (UINT64)&dg_pushdatastack);  // shouldn't trash dg_param2reg

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdefaultjumpcommaname);
        return;
    }
}


void dg_forthdefaultdropjumpcomma (Bufferhandle* pBHarrayhead)
{
    // does nothing since the DiaperGlu version does the drop during CODEMES-JUMPS,
}

void dg_forthcodemesjumptablecomma (Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    UINT64 depth;
    UINT64 numberofcodemes;
    UINT64 u, x;
    UINT64 ccbufid;
    UINT64 ohere;

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
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }

    if ( *pbuflength < (3*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 1] != dg_end_codemes_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"END-CODEMES-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }

    numberofcodemes = pints[depth-3];

    if ((numberofcodemes + 5) > depth)
    {
        dg_pusherror(pBHarrayhead, (const char*)"data stack depth seems too small to hold the whole codeme table");
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }

    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }

    ohere = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }
    
    // -7     -6     -5     -4   -3         -2 -1                      0
    // begin0 begin1 begin2 end2 #codemes=3 0  codemetablestateemarker
    for (u = 0; u < numberofcodemes; u++)
    {
        x = numberofcodemes - (u + 1);

        dg_pushbufferuint64(
            pBHarrayhead,
            ccbufid,
            pints[depth - (x+5)]);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
            return;
        }
    }

    dg_pushdatastack(
        pBHarrayhead,
        ohere);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesjumptablecommaname);
        return;
    }    
}

// JUMPTABLE-UJUMP,
void dg_forthjumptableujumpcomma (Bufferhandle* pBHarrayhead)
{
    unsigned char* pdatastack;
    UINT64* pbuflength;
    UINT64 depth;
    INT64 switchvaluedisplacement;
    UINT64* pints;

    UINT64 numberofcodemes;
    UINT64 afterbranchoffset;

    UINT64 otable;
    UINT64 ccbufid;
    UINT64 ccbuflength;

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
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    if ( *pbuflength < (4*sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    // could check for misaligned data stack here
    
    depth = (*pbuflength)/sizeof(UINT64);
    pints = (UINT64*)pdatastack;

    if (pints[depth - 2] != dg_codemes_jump_sys)
    {
        dg_pusherror(pBHarrayhead, (const char*)"CODEMES-JUMPS-SYS marker missing");
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    otable = pints[depth-1];
    switchvaluedisplacement = pints[depth - 3];
    numberofcodemes = pints[depth-4];

    // need to check if u >= #codemes
    dg_compilemovbracketrbpdtoreg (
        pBHarrayhead,
        dg_iretreg,
        switchvaluedisplacement);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    dg_compilecomparenreg (
        pBHarrayhead,
        numberofcodemes,
        dg_iretreg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    afterbranchoffset = dg_compilebranch (
        pBHarrayhead,
        DG_BRANCHTYPE_UGREATERTHANOREQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    // pccbufid->param1reg
    dg_compileotor(
        pBHarrayhead,
        0,
        dg_param1reg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 

    // [param1reg + 8*iretreg + otable] -> iretreg 
    dg_compilemovbracketrplussrplusd32tor(
        pBHarrayhead,
        dg_param1reg,
        3, // scale8*
        dg_iretreg,
        otable,
        dg_iretreg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 
 
    dg_compileaddregtoreg(
        pBHarrayhead,
        dg_param1reg,
        dg_iretreg);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 

    dg_compilejumptorax(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 

    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 

    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    } 

    dg_resolvecompiledbranch (
        pBHarrayhead,
        afterbranchoffset,
        ccbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthjumptableujumpcommaname);
        return;
    }

    *pbuflength -= sizeof(UINT64);
}

void dg_forthcodemesujumpcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthcodemesjumptablecomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesujumpcommaname);
        return;
    }

    dg_forthtor(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesujumpcommaname);
        return;
    }

    dg_forthcodemesjumpscomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesujumpcommaname);
        return;
    }

    dg_forthrfrom(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesujumpcommaname);
        return;
    }

    dg_forthjumptableujumpcomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcodemesujumpcommaname);
        return;
    }
}

void dg_forthquerywin (Bufferhandle* pBHarrayhead)
{
    UINT64 flag;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // doing it this way to gaurantee result is FORTH_TRUE or FORTH_FALSE
    if (dg_shadowsize != 0)
    {
        flag = FORTH_TRUE;
    }
    else
    {
        flag = FORTH_FALSE;
    }

    dg_pushdatastack(pBHarrayhead, flag);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerywinname);
        return;
    }
}


void dg_forthscommatoos (Bufferhandle* pBHarrayhead) // ( S,>OS )
//     ( addr length -- offset bufferid length )
{
    UINT64 bufferid;
    
    unsigned char* psqstr;   
    UINT64 sqstrlen;
    
    UINT64 afterbranchoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    sqstrlen = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
    
    psqstr = (unsigned char*)dg_popdatastack(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
    
    // now have beginoffset and length, time to compile code to copy string
    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)psqstr,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        afterbranchoffset + sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        afterbranchoffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufferid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        sqstrlen);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthscommatoosname);
        return;
    }
}

// need to rename this to ob or just o
void dg_forths0commatoob (Bufferhandle* pBHarrayhead) // ( S0,>OS )
//     ( addr length -- offset bufferid length )
{
    UINT64 bufferid;
    
    unsigned char* psqstr;   
    UINT64 sqstrlen;
    
    UINT64 afterbranchoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    sqstrlen = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    psqstr = (unsigned char*)dg_popdatastack(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    // now have beginoffset and length, time to compile code to copy string
    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)psqstr,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }

    dg_compilesegment(
        pBHarrayhead,
        (const char*)"\x00",
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        afterbranchoffset + sqstrlen + 1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        afterbranchoffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufferid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
        return;
    }
    
    // don't need length with a zero string    
    // dg_pushbufferuint64(
    //    pBHarrayhead,
    //    DG_DATASTACK_BUFFERID,
    //    sqstrlen + 1);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
    //    dg_pusherror(pBHarrayhead, dg_forths0commatoobname);
    //    return;
    // }
}


