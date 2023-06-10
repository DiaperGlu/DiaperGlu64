// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.11.
//
//    DiaperGlu v5.11 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.11 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.11; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 10, 2023              //
// version 5.11               //
// /////////////////////////////



#include "diapergluforth.h"


void dg_forthdots (Bufferhandle* pBHarrayhead)
{
    UINT64 numberonstack;
    UINT64 i;
    UINT64 data;

    numberonstack = dg_getbufferlength(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID) / sizeof(UINT64);

    dg_writestdout(
        pBHarrayhead,
        (unsigned char*)"[",
        1);
    
    dg_forthspace(pBHarrayhead);

    for (i=0; i< numberonstack; i++)
    {    
        data = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            i * sizeof(UINT64));

        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            data);

        dg_forthdot(pBHarrayhead);
    }

    dg_writestdout(
        pBHarrayhead,
        (unsigned char*)"]",
        1);
    
    dg_forthcr(pBHarrayhead);
}


void dg_forthdumphex (Bufferhandle* pBHarrayhead)
//     ( addr length -- )
{
    UINT64 length = 0;
    unsigned char* addr = 0;

    UINT64 i = 0;
    UINT64 j = 0;
    unsigned char b = ' ';

    UINT64 oldbase = 0;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    length = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdumpname);
        return;
    }

    addr = (unsigned char*)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdumpname);
        return;
    }

    oldbase = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthdumpname);
        return;
    }

    dg_forthhex(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdumpname);
        return;
    }

    i = 0;

    while (i < length)
    {
        dg_forthcr(pBHarrayhead);

        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)addr + i);

        dg_forthudot(pBHarrayhead);

        dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);

        dg_forthspace(pBHarrayhead);


        for (j=0; j < 16; j++)
        {
            if (i + j >= length)
            {
                break;
            }

            perror = dg_getbyte(addr + i + j, &b);

            if (perror != dg_success)
            {
                dg_pusherror(pBHarrayhead, perror);
                dg_pusherror(pBHarrayhead, dg_forthdumpname);
                break;
            }
            
            dg_pushbufferuint64(
                pBHarrayhead,
                DG_DATASTACK_BUFFERID,
                (UINT64)b);

            if (b < 16)
            {
                dg_writestdout(pBHarrayhead, (unsigned char*)"0", 1);
            }
            
            dg_forthudot(pBHarrayhead);
        }

        // return for bad address
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            break;  // doing break instead of return so base gets restored
        }

        dg_forthspace(pBHarrayhead);

        for (j=0; j < 16; j++)
        {
            if (i + j >= length)
            {
                break;
            }

            // bad address is caught above
            b = addr[i+j];

            dg_writestdoutraw(pBHarrayhead, &b, 1);
        }
        i += 16;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable,
        oldbase);
}


void dg_forthwords (Bufferhandle* pBHarrayhead)
//              ( -- )
{
    UINT64* psearchorder = NULL;
    UINT64* psolength = NULL;

    UINT64 wordlist = 0;

    // would be nice to have a word that gets the top word list in the searchorder
    psearchorder = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID,
        &psolength);

    if (psearchorder == (UINT64*)badbufferhandle)
    {
        return;
    }

    if (*psolength < sizeof(UINT64))
    {
        return;
    }

    wordlist = *(psearchorder + ((*psolength / sizeof(UINT64)) - 1));

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        wordlist);

    dg_forthshowwordlist(pBHarrayhead);
}


void dg_forthbye (Bufferhandle* pBHarrayhead)
{
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        exitmainflag,
        FORTH_TRUE);
    
    // could force a QUIT here... hmmm
}

void dg_forthsynonym (Bufferhandle* pBHarrayhead)
{
    unsigned char* poldname;
    UINT64 oldnamelength;
    unsigned char* pnewname;
    UINT64 newnamelength;
    UINT64 newwordid;
    UINT64 currentnewwordwordlist;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    poldname = dg_parseword(
        pBHarrayhead,
        &oldnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
        
    pnewname = dg_parseword(
        pBHarrayhead,
        &newnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
    
    newwordid = dg_findcopyandrenameword (
        pBHarrayhead,
        poldname,
        oldnamelength,
        pnewname,
        newnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
    
    if (newwordid == DG_ENDOFWORDLIST)
    {
        // not sure if this is the right error... but technically you shouldn't
        //  get DG_ENDOFWORDLIST unless there was an error...
        dg_pusherror(pBHarrayhead, dg_wordnotfoundinsearchordererror);
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
    
    currentnewwordwordlist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
    
    dg_linkdefinition (
        pBHarrayhead,
        currentnewwordwordlist,
        newwordid);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsynonymname);
        return;
    }
}
