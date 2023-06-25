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

void dg_forthstore (Bufferhandle* pBHarrayhead)
//         ( u addr -- )
{
    UINT64* address = NULL;
    UINT64 data = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthstorename);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        *plength = 0;
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstorename);
        return;
    }

    data = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    (*plength) -= (2*sizeof(UINT64));

    perror = dg_putuint64(
        address,
        data);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_forthstorename);
    }
}


void dg_forthnumbersign (Bufferhandle* pBHarrayhead)
//     ( ud1 -- ud1/base )
//     ( number$ -hold- number$2 )
{
    UINT64 base;
    UINT64 remainder;
    
    UINT64* pbuflength;
    unsigned char* pdatastack;
    UINT64* pints;              

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
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    if (base < 2)
    {
        dg_pusherror(pBHarrayhead, dg_basetoolowerror);
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    if (base > (0x100 - 0x37))
    {
        dg_pusherror(pBHarrayhead, dg_basetoohigherror);
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        base);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    // dg_forthudmslashmod(pBHarrayhead);

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    
    dg_udmslashmod(pints);

    remainder = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
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

    dg_insertinbuffer(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        0,
        1);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
        return;
    }

    dg_putbufferbyte(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        0,
        remainder);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersignname);
    }
}


void dg_forthnumbersigngreater (Bufferhandle* pBHarrayhead)
//     ( ud1 -- pnumber$ length )
//     ( number$ -hold- number$ )
{
    unsigned char* pdatastack;
    UINT64* pdatastacklength;

    unsigned char* ppad;
    UINT64* ppadlength;

//    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersigngreatername);
        return;
    }

    if (*pdatastacklength < 2 * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
         dg_pusherror(pBHarrayhead, dg_forthnumbersigngreatername);
         return;
    }

    ppad = dg_getpbuffer(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        &ppadlength);

    if (ppad == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthnumbersigngreatername);
        return;
    }
    
    *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) = *ppadlength;
    *((unsigned char**)(pdatastack + *pdatastacklength - (2 * sizeof(UINT64)))) = ppad;    
}


void dg_forthnumbersigns (Bufferhandle* pBHarrayhead)
//               ( ud1 -- 0 0 )
//               ( number$ -hold- number$2 )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    UINT64 flag = FORTH_TRUE;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // should always do 1 digit
    while ( flag )
    {
        dg_forthnumbersign(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthnumbersignsname);
            return;
        }

        // dg_forthnumbersign increases the length of the data stack so there is a small chance it could move
        //  so to be safe, we need to get the pointer to the data stack every time
        // another option would be to increase size of data stack to amount dg_forthnumbersign would use before calling it...

        pdatastack = dg_getpbuffer(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            &pdatastacklength);

        if (pdatastack == (unsigned char*)badbufferhandle)
        {
            dg_pusherror(pBHarrayhead, dg_forthnumbersignsname);
            return;
        }

        if (*pdatastacklength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
            dg_pusherror(pBHarrayhead, dg_forthnumbersignsname);
            return;
        }

        if ( (*((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) |
             *((UINT64*)(pdatastack + *pdatastacklength - 2*(sizeof(UINT64)))) )
            == 0 )
        {
            flag = FORTH_FALSE;
        }
    }
}


void dg_forthtick (Bufferhandle* pBHarrayhead)
//             ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff")
//             ( -- executiontoken )
{
    UINT64 namelength = 0;
    unsigned char* pname = NULL;

    UINT64 definition;

    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtickname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthtickname);
        return;
    }

    definition = dg_finddefinsearchorder(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtickname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtickname);
        return;
    }
}


void dg_forthparen (Bufferhandle* pBHarrayhead) // ( ( ) comment
//         ( "somestuff<rightparen>morestuff" -currentinputbuffer- "morestuff" )
{
    UINT64 length;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_parsemultiline(
        pBHarrayhead,
        &length,
        ')');
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparenname);
        return;
    }
}


void dg_forthstar (Bufferhandle* pBHarrayhead)      
//        ( n1 n2 -- n1*n2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthstarname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstarname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    pints[0] = pints[0] * pints[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthstarslash (Bufferhandle* pBHarrayhead)
//            ( n1 n2 n3 -- n1*n2/n3)
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
        dg_pusherror(pBHarrayhead, dg_forthstarslashname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstarslashname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    // ( n1    n2    denom )
    // ( eax   edx   ecx   )
    
    dg_mstar(pints[0], pints[1], (INT64*)pints);
    
    //dg_fmslashmod(pints);
    dg_smslashrem(pints);
    
    pints[0] = pints[1];

    *pbuflength -= 2 * sizeof(UINT64);
}


void dg_forthstarslashmod (Bufferhandle* pBHarrayhead) 
//               ( n1 n2 n3 -- remainder n1*n2/n3 )
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
        dg_pusherror(pBHarrayhead, dg_forthstarslashmodname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthstarslashmodname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - 3*sizeof(UINT64));
    // ( a     b     denom )
    // ( eax   edx   ecx   )
    
    
    dg_mstar(pints[0], pints[1], (INT64*)pints);
    
    //dg_fmslashmod(pints);
    dg_smslashrem(pints);

    *pbuflength -= sizeof(UINT64);
}


void dg_forthplus (Bufferhandle* pBHarrayhead)
//        ( n1 n2 -- n1+n2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthplusname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthplusname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    pints[0] = pints[0] + pints[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthplusstore (Bufferhandle* pBHarrayhead)
//             ( n1 address -- )
{
    UINT64* address;
    UINT64 data;
    UINT64 data2;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthplusstorename);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthplusstorename);
        return;
    }

    data = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_getuint64(
        address,
        &data2);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_forthplusstorename);
    }
    else
    {
        // we know address is ok
        *address = data + data2;
    }
    
    *plength -= 2* sizeof(UINT64);
}


UINT64 dg_checkplusloopdone (Bufferhandle* pBHarrayhead)
//                             ( index limit -r- | index limit )
//                             ( loopstep -- )
{
    unsigned char* prstack = NULL;
    UINT64* prstacklength = NULL;

    UINT64* pints = NULL;

    UINT64 loopstep = 0;

    // UINT64 olderrorcount = 0;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (FORTH_TRUE);
    }

    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (prstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    if (*prstacklength < 2* sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    loopstep = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        return(FORTH_TRUE);
    }

    pints = (UINT64*)(prstack + *prstacklength - (2 * sizeof(UINT64)));

    // if 0 < limit - index <= loopstep, loop is finished
    if ((pints[1] - pints[0]) != 0)
    {
        if ((INT64)loopstep >= 0)
        {
            if ((pints[1] - pints[0]) <= loopstep) // unsigned comparison
            {
                return (FORTH_TRUE);
            }
        }
        else
        {
            if ((pints[1] - pints[0]) >= loopstep) // unsigned comparison
            {
                return (FORTH_TRUE);
            }
        }
    }
    
    pints[0] += loopstep;
    return (FORTH_FALSE);
}


void dg_forthplusloop (Bufferhandle* pBHarrayhead)
//            ( do-sys -- )
//            ( compiles code that does: ) ( loopstep -- ) 
//            ( loop-sys1 -controlflowstack- ) if loop ends
//            ( loop-sys1 -controlflowstack- loop-sys1' ) if loop does not end
{
    UINT64* pleavebuf;
    UINT64* pleavebuflength;

    UINT64 beginoffset;

    UINT64 u;
    UINT64 i;
    UINT64 leaveoffset;

    UINT64 afterbranchoffset = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    beginoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
    
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_checkplusloopdone));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
    
    dg_compilecompare(
        pBHarrayhead,
        FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        beginoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
        
    // need to resolve leavestack for leaveoffsets with here >= leaveoffset >= dooffset
    pleavebuf = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_LEAVESTACK_BUFFERID,
        &pleavebuflength);

    if (pleavebuf == (UINT64*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthleavebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }

    u = (*pleavebuflength) / sizeof(UINT64);

    for (i = 0; i < u; i++)
    {
        leaveoffset = pleavebuf[u - (i+1)];

        if (leaveoffset >= beginoffset)
        {
            dg_pushbufferuint64(
                pBHarrayhead,
                DG_DATASTACK_BUFFERID,
                leaveoffset);
            // can't get error because we popped a number from data stack above

            dg_forththen(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthplusloopname);
                return;
            }

            // need to check error

            *pleavebuflength = (u - (i+1)) * sizeof(UINT64);     // drop this one and everything after it
        }
        else
        {
            break;
        }
    }
    
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)&dg_forthunloop);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthunloopname);
        dg_pusherror(pBHarrayhead, dg_forthplusloopname);
        return;
    }
}


void dg_forthcomma (Bufferhandle* pBHarrayhead)
//         ( n1 -- )
//         ( -currentdataspacebuffer- n1 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    UINT64 n1 = 0;
    UINT64 olderrorcount = 0;
    UINT64 dsbufid = 0;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcommaname);
        return;
    }

    if (*pbuflength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcommaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 1*sizeof(UINT64));

    n1 = pints[0];

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    dsbufid = dg_getbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthcommaname);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead,dsbufid, n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // error pushing to current new variable buffer
        dg_pusherror(pBHarrayhead, dg_forthcommaname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthminus(Bufferhandle* pBHarrayhead)
//     ( n1 n2 -- n1-n2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthminusname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthminusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    pints[0] = pints[0] - pints[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthdot (Bufferhandle* pBHarrayhead)
//     ( n -- )
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
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthdup(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthabs(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthnumbersigns(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthrot(pBHarrayhead); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthsign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthnumbersigngreater(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthtype(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }

    dg_forthspace(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotname);
        return;
    }
}


void dg_forthdotr (Bufferhandle* pBHarrayhead)
//     ( n1 n2 -- )
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
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthlessthannumbersign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthdup(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthabs(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthnumbersigns(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthrot(pBHarrayhead); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthsign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }

    dg_forthnumbersigngreater(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
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
        dg_pusherror(pBHarrayhead, dg_forthdotrname);
        return;
    }
}


void dg_forthdotquotes (Bufferhandle* pBHarrayhead) // compiling routine
//     ( "stuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
{
    UINT64 state;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    state = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
    }

    if (state == (UINT64)dg_stateexecute)
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)'"');

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
            return;
        }

        dg_forthparse(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
            return;
        }

        dg_forthtype(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
            return;
        }

        return;
    }

    dg_forthsquotes(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)&dg_forthtype);
    
    // dg_pushbufferuint64(
    //    pBHarrayhead,
    //    DG_DATASTACK_BUFFERID,
    //    (UINT64)(&dg_forthtype));

    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
    //    dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
    //    return;
    // }

    // dg_forthcompilecallcore(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotquotesname);
        return;
    }
}


void dg_forthslash (Bufferhandle* pBHarrayhead)         
//         ( n1 n2 -- n1/n2 )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthslashmod(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslashname);
        return;
    }
    
    dg_forthswap(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslashname);
        return;
    }
    
    dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslashname);
        return;
    }
}


void dg_forthslashmod (Bufferhandle* pBHarrayhead)      
//            ( n1 n2 -- remainder quotient )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, 0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthslashmodname);
        return;
    }

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthslashmodname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthslashmodname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - 3*sizeof(UINT64));
    // ( numlo denom )
    // ( eax   ecx   )
    
    pints[2] = pints[1];

    pints[1] = dg_isnegative(pints[0]);
    
    //dg_fmslashmod(pints);
    dg_smslashrem(pints);
    
    *pbuflength -= sizeof(UINT64);
}


void dg_forthzeroless (Bufferhandle* pBHarrayhead)     
//            ( n1 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthzerolessname);
        return;
    }

    // ifpdatastack or pbuflength (unsigned char*)badbufferhandle thats an error

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthzerolessname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    if (((INT64)(pints[0])) < 0)
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }
}


void dg_forthzeroequals (Bufferhandle* pBHarrayhead)    
//              ( n1 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthzeroequalsname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthzeroequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    if (pints[0] == 0)
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }
}


void dg_forthoneplus (Bufferhandle* pBHarrayhead)       
//           ( n1 -- n1+1 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthoneplusname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthoneplusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0]++;
}


void dg_forthoneminus (Bufferhandle* pBHarrayhead)      
//            ( n1 -- n1-1 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthoneminusname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthoneminusname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0]--;
}


void dg_forthtwostore (Bufferhandle* pBHarrayhead)
//            ( n1 n2 addr -- )
{
    UINT64* address = NULL;
    UINT64 data1 = 0;
    UINT64 data2 = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* flag;


    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwostorename);
        return;
    }

    if (*plength < 3 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwostorename);
        return;
    }

    data1 = *((UINT64*)(pbuffer + *plength - (3 * sizeof(UINT64)))); // n1 lo
    data2 = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64)))); // n2 hi
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));  // addr

    flag = dg_putuint64(address, data2);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_forthtwostorename);
    }
    else
    {
        flag = dg_putuint64(address + 1, data1);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_forthtwostorename);
        }
    }
    
    *plength -= 3 * sizeof(UINT64);
}


void dg_forthtwostar(Bufferhandle* pBHarrayhead)
//          ( n1 -- n1*2)
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwostarname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwostarname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    pints[0] = 2*pints[0];
}


void dg_forthtwoslash (Bufferhandle* pBHarrayhead)     
//            ( n1 -- n1/2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwoslashname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwoslashname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - sizeof(UINT64));
    
    pints[0] = dg_twoslash(pints[0]);
}


void dg_forthtwofetch (Bufferhandle* pBHarrayhead)
//            ( addr -- n1 n2 )
{
    UINT64* address = NULL;
    UINT64 n1 = 0;
    UINT64 n2 = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    const char* pError = NULL;

    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
        return;
    }

    address = *( (UINT64**)(pbuffer + *plength - sizeof(UINT64)) );

    dg_growbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, sizeof(UINT64), &pError, false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
        return;
    }

    // this should work if grow was dg_successful
    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength); 

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
        return;
    }

    pError = dg_getuint64(address, &n2);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
    }
    else
    {
        pError = dg_getuint64(address + 1, &n1);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_getuint64name);
            dg_pusherror(pBHarrayhead, dg_forthtwofetchname);
        }
    }

    *((UINT64*)(pbuffer + *plength - 2*sizeof(UINT64))) = n1;  // lo
    *((UINT64*)(pbuffer + *plength - sizeof(UINT64)))  = n2; // hi
}


void dg_forthtwodrop (Bufferhandle* pBHarrayhead)       
//           ( n1 n2 -- )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;


    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwodropname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwodropname);
        return;
    }

    // could check for misaligned data stack here

    *pbuflength = *pbuflength - (2 * sizeof(UINT64));
}


void dg_forthtwodup (Bufferhandle* pBHarrayhead)        
//          ( n1 n2 -- n1 n2 n1 n2 )
{
    const char* pError = NULL;

    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwodupname);
        return;
    }

    if (*pbuflength < 2 * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwodupname);
        return;
    }

    dg_growbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, 2 * sizeof(UINT64), &pError, false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtwodupname);
        return;
    }

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwodupname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    pints[2] = pints[0];
    pints[3] = pints[1];
}


void dg_forthtwoover (Bufferhandle* pBHarrayhead)
//           ( n1 n2 n3 n4 -- n1 n2 n3 n4 n1 n2 )
{
    const char* pError = NULL;

    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwoovername);
        return;
    }

    if (*pbuflength < 4 * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwoovername);
        return;
    }

    dg_growbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, 2 * sizeof(UINT64), &pError, false);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtwoovername);
        return;
    }

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwoovername);
        return;
    }

    // could check for misaligned data stack

    pints = (UINT64*)(pdatastack + *pbuflength - (6 * sizeof(UINT64)));

    pints[4] = pints[0];
    pints[5] = pints[1];
}


void dg_forthtwoswap (Bufferhandle* pBHarrayhead)       
//           ( n1 n2 n3 n4 -- n3 n4 n1 n2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    UINT64 t = 0;


    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwoswapname);
        return;
    }

    if (*pbuflength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtwoswapname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (4 * sizeof(UINT64)));

    t = pints[0];
    pints[0] = pints[2];
    pints[2] = t;
    t = pints[1];
    pints[1] = pints[3];
    pints[3] = t;    
}


void dg_forthcolon (Bufferhandle* pBHarrayhead)
//     ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -- executiontoken colonsys )
{
    UINT64 definition = 0;

    UINT64 namelength = 0;
    unsigned char* pname = NULL;
    
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
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }

    definition = dg_createsubthreaddef(
        pBHarrayhead, 
        pname, 
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }

    dg_forthrightbracket(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        colonsysmarker);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
        return;
    }
    
    dg_compileinitlocals (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
    }

    dg_putbufferuint64(
        pBHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        coloncallssafeflag, 
        FORTH_FALSE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonname);
    }
}


void dg_forthsemicolon (Bufferhandle* pBHarrayhead)
//                  ( colonsys -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64 isdefaultsafe;

    INT64* pints;

    UINT64 ccwordlist;


    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthqueryclearlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    dg_compileexitlocals(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    dg_forthleftbracket(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if ((pints[1] != (INT64)colonsysmarker) && 
        (pints[1] != (INT64)colonnonamemarker))   
    {
        dg_pusherror(pBHarrayhead, dg_colonsysmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    // not checking the definition?
 
    if (pints[1] == (INT64)colonsysmarker)
    {
        ccwordlist = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            currentcompilewordlist);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
            dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
            return;
        }

        dg_linkdefinition(
            pBHarrayhead,
            ccwordlist,
            pints[0]);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
            return;
        }

        *pbuflength -= (2 * sizeof(UINT64));
    }
    else
    {
        *pbuflength -= (1 * sizeof(UINT64));
    }

    isdefaultsafe = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        coloncallssafeflag);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcoloncallssafeflagname);
        dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
        return;
    }

    if (FORTH_FALSE != isdefaultsafe)
    {
        dg_forthsafe(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthsemicolonname);
            return;
        }
    }
}


void dg_forthlessthan (Bufferhandle* pBHarrayhead)      
//     ( n1 n2 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;


    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlessthanname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlessthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] < pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthlessthannumbersign (Bufferhandle* pBHarrayhead)
//     ( -- )
//     ( number$ -hold- )
{
    unsigned char* ppad;
    UINT64*  ppadlength;

    ppad = dg_getpbuffer(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        &ppadlength);

    if (ppad == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthholdbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlessthannumbersignname);
        return;
    }

    *ppadlength = 0;
}


void dg_forthequals (Bufferhandle* pBHarrayhead)        
//          ( n1 n2 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;


    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthequalsname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthequalsname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] == pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthgreaterthan (Bufferhandle* pBHarrayhead)   
//      ( n1 n2 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;


    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthgreaterthanname);
        return;
    }


    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthgreaterthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] > pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthtobody (Bufferhandle* pBHarrayhead) 
//          ( executiontoken -- address )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;

    Definitionheader* pdefinition = NULL;

    UINT64 dataaddr = 0;

    UINT64 olderrorcount = 0;


    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtobodyname);
        return;
    }


    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtobodyname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (sizeof(UINT64)));

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        pints[0]);

    pints[0] = 0;

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtobodyname);
        return;
    }

    // I don't like the name dg_getpbufferoffset
    dataaddr = (UINT64)dg_getpbufferoffset(
        pBHarrayhead,
        pdefinition->databuf,
        pdefinition->dataoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtobodyname);
        return;
    }

    pints[0] = dataaddr;
}


void dg_forthtoin (Bufferhandle* pBHarrayhead)
//        (  -- addressofcurrentoffset )
{
    unsigned char* pcib = NULL;
    UINT64* pciblength = NULL;
    UINT64* pcibcurrentoffset = NULL;

    UINT64 cibid = 0;
    UINT64 olderrorcount = 0;

    Bufferhandle* pBH = NULL;

    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    const char* pError = NULL;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtoinname);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtoinname);
        return;
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;

    // could check validity of current offset here..

    dg_growbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        sizeof(UINT64),
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtoinname);
        return;
    }
    
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtoinname);
        return;
    }

    *((UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64))) = (UINT64)pcibcurrentoffset;
}


void dg_forthtonumber (Bufferhandle* pBHarrayhead)
//     ( ud1 c-addr1 u1 -- ud2 c-addr2 u2)
{
    UINT64* pdatastacklength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;

    UINT64 base = 0;
    UINT64 olderrorcount = 0;

    UINT64 ud1 = 0;
    unsigned char* caddr1 = NULL;
    UINT64 u1 = 0;

    char c = 0;

    const char* perror;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtonumbername);
        return;
    }

    if (*pdatastacklength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtonumbername);
        return;
    }

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthtonumbername);
        return;
    }

    if (base < 2)
    {
        dg_pusherror(pBHarrayhead, dg_basetoolowerror);
        dg_pusherror(pBHarrayhead, dg_forthtonumbername);
        return;
    }

    pints = (INT64*)(pdatastack + *pdatastacklength - (4 * sizeof(UINT64)));

    ud1 = *((UINT64*)(&(pints[0])));
    caddr1 = (unsigned char*)(pints[2]);
    u1 = pints[3];

    while(u1 > 0)
    {
        perror = dg_getbyte(caddr1, (unsigned char*)&c);

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_getbytename);
            dg_pusherror(pBHarrayhead, dg_forthtonumbername);
            break;
        }

        if (c < 0x30)
        {
            break;
        }
        if (( c > 0x39) && (c < 0x41))
        {
            break;
        }
            
        // might want to check for max allowed base here

        if (c <= 0x39)
        {
            c = c - 0x30;
        }
        else if (c <= 0x61) // upper case
        {
            c = c - 0x37;
        }
        else                // lower case
        {
            c = c - 0x57;
        }

        if ((UINT64)c >= base)
        {
            break;
        }

        ud1 = ud1 * base;
        ud1 = ud1 + c;

        caddr1++;
        u1--;
    }

    *((UINT64*)(&(pints[0]))) = ud1;
    pints[2] = (UINT64)caddr1;
    pints[3] = u1;
}


void dg_forthtor (Bufferhandle* pBHarrayhead)
//       ( x1 -- )
//       ( -r- x1 )
{
    UINT64 x1 = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    x1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtorname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        x1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtorname);
    }
}


void dg_forthquestion (Bufferhandle* pBHarrayhead)
//             ( a-addr -- )
{
    UINT64 c;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_forthcfetch(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquestionname);
        return;
    }

    dg_forthudot(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquestionname);
        return;
    }
}

void dg_forthquestiondup (Bufferhandle* pBHarrayhead)   
//               ( n1 -- n1 ) if n1 = 0 or 
//               ( n1 -- n1 n1 ) if n1 != 0
{
    UINT64 data = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    data = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthquestiondupname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        data);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthquestiondupname);
        return;
    }

    if (data != 0)
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            data);
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthquestiondupname);
        return;
    }
}


void dg_forthfetch (Bufferhandle* pBHarrayhead)
//         ( address -- data )
{
    UINT64* address = NULL;
    UINT64 n1 = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthfetchname);
        return;
    }

    if (*plength < 1 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfetchname);
        return;
    }

    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_getuint64(
        address,
        &n1);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getuint64name);
        dg_pusherror(pBHarrayhead, dg_forthfetchname);
    }

    *((UINT64*)(pbuffer + *plength - (sizeof(UINT64)) )) = n1;
}


void dg_forthabort (Bufferhandle* pBHarrayhead)
//              ( nx ... n2 n1 n0 -- )
//              ( mx ... m2 m1 m0 -r- )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_clearbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthabortname);
        // not returning here on purpose
    }

    dg_forthquit(pBHarrayhead);

    // dg_forthquit does not return so there is no point in checking for errors
}


void dg_forthabortquotes (Bufferhandle* pBHarrayhead)
//                    ( flag -- ) if flag = FALSE
//                    ( nx ... n2 n1 n0 flag -- ) if flag = TRUE
//                    ( mx ... m2 m1 m0 -r- ) if flag = TRUE 
{
    UINT64 bufferid = 0;
    

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthif(pBHarrayhead);  // compiling word

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }

    dg_forthdotquotes(pBHarrayhead);  // compiling word

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }

    bufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }

    // compile call to QUIT
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)&dg_forthquit);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }

    dg_forthcompilecallcore(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }

    dg_forththen(pBHarrayhead); // compiling word

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthabortquotesname);
        return;
    }
}


void dg_forthabs (Bufferhandle* pBHarrayhead)   
//               ( n1 -- u1 )
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
        dg_pusherror(pBHarrayhead, dg_forthabsname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthabsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (sizeof(UINT64)));

    if (pints[0] == (INT64)largestnegativeint)
    {
        pints[0] = largestsignedint;
    }
    else
    {
        if (pints[0] < 0)
        {
            pints[0] = 0 - pints[0];
        }        
    }
}


void dg_forthaccept (Bufferhandle* pBHarrayhead)
//               ( caddr +n1 -- +n2 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    unsigned char* caddr;
    INT64 n1;
    INT64 i;

    unsigned char c = 0;
    UINT64 stdinfileid;
    UINT64 numread;
    const char* perror;

    INT64* pints;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    perror = dg_gethstdin(
        pBHarrayhead,
        &stdinfileid, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_gethstdinname);
        dg_pusherror(pBHarrayhead, dg_forthacceptname); // this one was commented out, don't know why
        return;
    }

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthacceptname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthacceptname);
        return;
    }

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    caddr = (unsigned char*)(pints[0]);
    n1 = pints[1]; 

    if (n1 <= 0)
    {
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthacceptname);
        return;
    }

    i = 0;
    
    // get all characters from user until they press cr
    while((c != 10) && (i < n1))
    {
        perror = dg_readfile(
            pBHarrayhead,
            stdinfileid,
            &c, 
            1,
            0,
            &numread,
            dg_success);

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_readfilename);
            dg_pusherror(pBHarrayhead, dg_forthacceptname);
            c = 10;
        }

        if (0 == numread)
        {
            // connection was closed, force end of loop
            // this is not an error
            c = 10;
        }

        if (c != 10) // end of buffer is a delimiter so we don't need to push the end of line character
        {
            if (c != 13) // throw away carriage return
            {
                perror = dg_putbyte(caddr, c);

                if (perror != dg_success)
                {
                    dg_pusherror(pBHarrayhead, perror);
                    dg_pusherror(pBHarrayhead, dg_putbytename);
                    dg_pusherror(pBHarrayhead, dg_forthacceptname);
                    c = 10;
                }
                caddr++;
                i++;
            }
        }
    }

    if (dg_geterrorcount(pBHarrayhead) == olderrorcount)
    {
        pints[0] = i;
        *pbuflength = *pbuflength - sizeof(UINT64);
    }
}


void dg_forthalign (Bufferhandle* pBHarrayhead)
//              ( -- )
{
    unsigned char* pdataspacebuf = NULL;
    UINT64* pdataspacelength = NULL;

    UINT64 remainder = 0;
    UINT64 amounttogrow = 0;

    UINT64 cdsbufid = 0;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    cdsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthalignname);
        return;
    }

    pdataspacebuf = dg_getpbuffer(
        pBHarrayhead,
        cdsbufid,
        &pdataspacelength);

    if (pdataspacebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthalignname);
        return;
    }

    remainder = *pdataspacelength % sizeof(UINT64);
    
     // amounttogrow will be 8 when remainder is 0, but we will catch this below
    amounttogrow = sizeof(UINT64) - remainder;

    if (remainder != 0)
    {
        dg_growbuffer(
            pBHarrayhead,
            cdsbufid,
            amounttogrow,
            &pError,
            false);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
            dg_pusherror(pBHarrayhead, dg_forthalignname);
        }
    }
}


void dg_forthaligned (Bufferhandle* pBHarrayhead)
//                ( addr -- a-addr )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    UINT64 addr = 0;

    UINT64 remainder = 0;
    UINT64 amounttogrow = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthalignedname);
        return;
    }

    if ((*pdatastacklength) < (sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthalignedname);
        return;
    }

    addr = *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64))));

    remainder = addr % sizeof(UINT64);
    
     // amounttogrow will be 8 when remainder is 0, but we will catch this below
    amounttogrow = sizeof(UINT64) - remainder;

    if (remainder != 0)
    {
        addr += amounttogrow;
        *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) = addr;
    }
}


void dg_forthallot (Bufferhandle* pBHarrayhead)
//     ( n1 -- )
//     ( -currentnewvariablebuffer- +n1bytes )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    const char* pError = NULL;

    INT64 n1 = 0;
    UINT64 dsbufid = 0;
    UINT64 olderrorcount = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthallotname);
        return;
    }

    if (*pdatastacklength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthallotname);
        return;
    }

    n1 = *((INT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64))));

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthallotname);
        return;
    }

    if (n1 > 0)
    {
        dg_growbuffer(
            pBHarrayhead,
            dsbufid,
            n1,
            &pError,
            false);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
            dg_pusherror(pBHarrayhead, dg_forthallotname);
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
            dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
            dg_pusherror(pBHarrayhead, dg_forthallotname);
            return;
        }
    }

    *pdatastacklength = *pdatastacklength - sizeof(UINT64);
}


void dg_forthand (Bufferhandle* pBHarrayhead)    
//     ( u1 u2 -- u1&u2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    

    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthandname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthandname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = pints[0] & pints[1];

    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthbase (Bufferhandle* pBHarrayhead)
//     ( -- a-addr )
{
    UINT64* pbase = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pbase  = (UINT64*)dg_getpbuffersegment(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable,
        sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pbase);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthbasename);
    }
}


void dg_forthbegin (Bufferhandle* pBHarrayhead)
//     ( -- beginoffset )
{
    UINT64 compilebufid = 0;;

    unsigned char* pcompilebuf = NULL;
    UINT64* pcompilebuflength = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    compilebufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthbeginname);
        return;
    }

    pcompilebuf = dg_getpbuffer(
        pBHarrayhead,
        compilebufid,
        &pcompilebuflength);

    if (pcompilebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthbeginname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        *pcompilebuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthbeginname);
    }
}


void dg_forthbl  (Bufferhandle* pBHarrayhead)    
//     ( -- space ) a.k.a. bl
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        0x20);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthblname);
    }
}


void dg_forthcstore (Bufferhandle* pBHarrayhead)
//     ( char c-addr -- )
{
    unsigned char* address = NULL;
    UINT64 data = 0;

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
        dg_pusherror(pBHarrayhead, dg_forthcstorename);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcstorename);
        return;
    }

    data = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((unsigned char**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_putbyte(
        address,
        data);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putbytename);
        dg_pusherror(pBHarrayhead, dg_forthcstorename);
    }
    
    *plength -= 2 * sizeof(UINT64);
}


void dg_forthccomma (Bufferhandle* pBHarrayhead)
//          ( char -- )
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
        dg_pusherror(pBHarrayhead, dg_forthccommaname);
        return;
    }

    if (*pbuflength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthccommaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 1*sizeof(UINT64));

    n1 = pints[0];

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthccommaname);
        return;
    }

    dg_pushbufferbyte(
        pBHarrayhead,
        dsbufid,
        (unsigned char)n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthccommaname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthcfetch (Bufferhandle* pBHarrayhead)
//          ( address -- char )
{
    unsigned char* address;
    unsigned char c;

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
        dg_pusherror(pBHarrayhead, dg_forthcfetchname);
        return;
    }

    if (*plength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcfetchname);
        return;
    }

    address = *((unsigned char**)(pbuffer + *plength - (sizeof(UINT64))));

    perror = dg_getbyte(
        address,
        &c);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getbytename);
        dg_pusherror(pBHarrayhead, dg_forthcfetchname);
    }

    *((UINT64*)(pbuffer + *plength - (sizeof(UINT64)))) = (UINT64)c;
}


void dg_forthcellplus (Bufferhandle* pBHarrayhead)
//            ( a-addr1 -- a-addr2 )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcellplusname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcellplusname);
        return;
    }

    *((UINT64*)(pbuffer + *plength - sizeof(UINT64))) += sizeof(UINT64);
}


void dg_forthcells (Bufferhandle* pBHarrayhead)
//         ( n1 -- n2 )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcellsname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcellsname);
        return;
    }

    *((UINT64*)(pbuffer + *plength - sizeof(UINT64))) *= sizeof(UINT64); // c sets overflow to 0 I think
    // but in normal use there won't be an overflow
}


void dg_forthchar (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -- firstcharofword )
{
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcharname);
        return;
    }
    
    if (0 == namelength)
    {
        dg_pusherror(pBHarrayhead, dg_nowordfounderror);
        dg_pusherror(pBHarrayhead, dg_forthcharname);
        return;
    }
        
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pname[0]);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcharname);
    }
}


void dg_forthcharplus (Bufferhandle* pBHarrayhead)
//     ( c-addr1 -- c-addr2 )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcharplusname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcharplusname);
        return;
    }

    (*((UINT64*)(pbuffer + *plength - sizeof(UINT64))) )++;
}


void dg_forthchars (Bufferhandle* pBHarrayhead)
//         ( n1 -- n2 )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcharsname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcharsname);
        return;
    }
    
    // nothing needs to be done, so just checking data stack to make sure value is there
}


void dg_forthcmove (Bufferhandle* pBHarrayhead)
//     ( addr1 addr2 u -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char* addr1;
    unsigned char* addr2;
    INT64 u = 0;
    
    const char* flag;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcmovename);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcmovename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    addr1 = (unsigned char*)(pints[0]); // source
    addr2 = (unsigned char*)(pints[1]); // destination
    u = (signed int)(pints[2]);         // length

    if (u <=0)
    {
        // I think I want to push a length to big error here
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthcmovename);
        return;
    }

    flag = dg_movebytesforward(
        addr1,
        addr2,
        u);

    if (flag != dg_success)
    {
        dg_pusherror(
            pBHarrayhead,
            flag);

        dg_pusherror(pBHarrayhead, dg_movebytesforwardname);

        dg_pusherror(pBHarrayhead, dg_forthcmovename);
    }
    
    *pbuflength -= (3* sizeof(UINT64));
}


void dg_forthcmoveto (Bufferhandle* pBHarrayhead)
//     ( addr1 addr2 u -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char* addr1;
    unsigned char* addr2;
    INT64 u = 0;
    
    const char* flag;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcmovetoname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcmovetoname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    addr1 = (unsigned char*)(pints[0]); // source
    addr2 = (unsigned char*)(pints[1]); // destination
    u = (signed int)(pints[2]);         // length

    if (u <=0)
    {
        // I think I want to push a length to big error here
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthcmovetoname);
        return;
    }

    flag = dg_movebytesreverse(
        addr1,
        addr2,
        u);

    if (flag != dg_success)
    {
        dg_pusherror(
            pBHarrayhead,
            flag);

        dg_pusherror(pBHarrayhead, dg_movebytesreversename);

        dg_pusherror(pBHarrayhead, dg_forthcmovetoname);
    }
    
    *pbuflength -= (3* sizeof(UINT64));
}


void dg_forthconstant (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthconstantname);
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthconstantname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthconstantname);
        return;
    }

    dg_createconstantdef(
        pBHarrayhead,
        data,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthconstantname);
        return;
    }
}

void dg_forthcount (Bufferhandle* pBHarrayhead)
//     ( c-addr1 -- c-addr2 u )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;

    unsigned char u = 0;
    unsigned char* addr = NULL;

    UINT64 olderrorcount = 0;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcountname);
        return;
    }

    if (*plength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcountname);
        return;
    };

    addr = *((unsigned char**)(pbuffer + *plength - sizeof(UINT64)));

    perror = dg_getbyte(
        addr,
        &u);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getbytename);
        dg_pusherror(pBHarrayhead, dg_forthcountname);
    }

    addr++;

    *((unsigned char**)(pbuffer + *plength - sizeof(UINT64))) = addr;

    olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)u);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcountname);
        return;
    }
}


void dg_forthcr (Bufferhandle* pBHarrayhead)       
// ( -- )
{
    unsigned char c = '\n';

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_writestdout(pBHarrayhead, &c, 1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcrname);
    }
}


void dg_forthcreate (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthcreatename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthcreatename);
        return;
    }

    dg_createvariabledef(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatename);
        return;
    }
}


void dg_forthdecimal (Bufferhandle* pBHarrayhead)
//       ( -- )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable,
        10);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthdecimalname);
        return;
    }
}


void dg_forthdepth (Bufferhandle* pBHarrayhead)
//     ( nx ... n2 n1 -- nx ... n2 n1 x )
{
    UINT64 length;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    length = dg_getbufferlength(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdepthname);
        return;
    }

    // could check for misaligned data stack here

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        length / sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdepthname);
        return;
    }
}


void dg_forthdo (Bufferhandle* pBHarrayhead)
//     ( -- do-sys )
// Compiles code that does ( index limit -- ) ( -r- limit index )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_forthtor));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoname);
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_forthtor));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoname);
        return;
    }

    // could compile check for error here

    dg_forthbegin(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoname);
        return;
    }
}


void dg_forthdoes (Bufferhandle* pBHarrayhead)
{
    // compile call to dg_changelatestcompileroutine with current compile bufid, and offset after return
    // compile return
    // compile call to dg_getpbufferoffset (parameters are on data stack already)
    
    UINT64 bufferid;
    
    UINT64 mytargetoffset = 0;
    
    UINT64 myendofbufferoffset = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthqueryclearlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
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
    
    // need offset of compile buffer after this is compiled
    // mytargetoffset = dg_compilepushntoret(pBHarrayhead, 0);
    
    dg_compilentoparameter (
        pBHarrayhead,
        0,
        2);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
     mytargetoffset = dg_getbufferlength (
        pBHarrayhead,
        bufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    // dg_compilepushntoret(pBHarrayhead, bufferid);
    
    dg_compilentoparameter (
        pBHarrayhead,
        bufferid,
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    // dg_compilepushparametertoret(pBHarrayhead, 0); // pBHarrayhead
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
    
    // this makes assumptions about how ntoparameter is compiled...
    //  expects the UINT64 constant to be just before target offset
    dg_putbufferuint64(
        pBHarrayhead,
        bufferid,
        mytargetoffset - sizeof(UINT64),
        myendofbufferoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }

    // DOES compile type routine uses standard dglu frame and must end with standard dglu exit
    dg_compileinitlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
    
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)&dg_forthgetpbufferoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdoesname);
        return;
    }
}


void dg_forthdrop(Bufferhandle* pBHarrayhead)
//     ( n -- )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdropname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdropname);
        return;
    }

    *plength -= sizeof(UINT64);    
}


void dg_forthdup(Bufferhandle* pBHarrayhead)
//     ( n1 -- n1 n1) 
{
    UINT64* plength;
    unsigned char* pbuffer;
    UINT64 data;

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
        dg_pusherror(pBHarrayhead, dg_forthdupname);
        return;
    }

    if (*plength < sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdupname);
        return;
    }

    // need temporary storage because pointer becomes invalid during push
    data = *((UINT64*)(pbuffer + (*plength) - sizeof(UINT64)));

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        data);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdupname);
        return;
    }
}


void dg_forthelse (Bufferhandle* pBHarrayhead)
//             ( ifoffset -- elseoffset )
{
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthelsename);
        return;
    }

    dg_forththen(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthelsename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthelsename);
    }
}


void dg_forthemit (Bufferhandle* pBHarrayhead)          
//     ( n1 -- )
{
    INT64 c = 0;

    UINT64 fileid;
    const char* flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    flag = ::dg_gethstdout(
        pBHarrayhead,
        &fileid, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        return;
    }

    c = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthemitname);
        return;
    }

    // assumes little endian
    dg_writestdout(
        pBHarrayhead,
        (unsigned char*)&c,
        1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthemitname);
    }
}


void dg_forthenvironmentquery (Bufferhandle* pBHarrayhead)
//     ( c-addr u -- false | i*x true )
{
    UINT64 flag;
    UINT64 enviromentwid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    enviromentwid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_environmentwordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthenvironmentqueryname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        enviromentwid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthenvironmentqueryname);
        return;
    }

    dg_forthsearchwordlist(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthenvironmentqueryname);
        return;
    }

    flag = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    // can't really get an error here

    if (flag == FORTH_TRUE)
    {
        dg_forthexecute(pBHarrayhead);
        // not checking for errors here... but probably should since these usually aren't user routines

        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            FORTH_TRUE);
        // can't really get an error here
    }
    else
    {
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            FORTH_FALSE);
        // can't really get an error here
    }
}


void dg_forthevaluate (Bufferhandle* pBHarrayhead)
//     ( c-addr u -- )
{
    unsigned char* pdstack = NULL;
    UINT64* pdstacklength = NULL;

    unsigned char* caddr = NULL;
    UINT64 u = 0;

    UINT64* pints = 0;

    UINT64 evalbufferid = 0;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if ((UINT64)baderrorcount == olderrorcount)
    {
        return;
    }

    pdstack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdstacklength);

    if (pdstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthevaluatename);
        return;
    }

    if (*pdstacklength < (2  * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthevaluatename);
        return;
    }

    pints = (UINT64*)(pdstack + *pdstacklength - (2*sizeof(UINT64)));

    caddr = (unsigned char*)(pints[0]);
    u = pints[1];

    *pdstacklength -= (2 * sizeof(UINT64));


    evalbufferid = dg_newbuffer(
        pBHarrayhead,
        u,
        u,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_forthevaluatename);
        return;
    }

    // after this point, all paths must free evalbufferid before exiting
    dg_pushbuffersegment(
        pBHarrayhead,
        evalbufferid,
        u,
        caddr);

    // if new buffer worked with growby = maxsize, you really can't get an error here since the memory is already allocated
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthevaluatename);
        dg_freebuffer(pBHarrayhead, evalbufferid);
        return;
    }

    dg_evaluatebuffer(
        pBHarrayhead,
        evalbufferid);

    // not pushing an error here because it could be from an interpreted routine and that would be redundant

    dg_freebuffer(
        pBHarrayhead,
        evalbufferid);
}


void dg_forthexecute (Bufferhandle* pBHarrayhead)
//     ( executiontoken -- )
{
    UINT64 executetoken;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    executetoken = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthexecutename);
        return;
    }

    dg_executedefinition(pBHarrayhead, executetoken);
    
    // should we really check for an error here?
    //if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    //{
    //    dg_pusherror(pBHarrayhead, dg_forthexecutename);
    //    return;
    //}
}


void dg_forthexit (Bufferhandle* pBHarrayhead)
//             ( -- )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
            return;
    }
    
    dg_forthquerycompileunnestlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthexitname);
        return;
    }
    
    dg_compileexitlocals(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthexitname);
        return;
    }
}



void dg_forthfill (Bufferhandle* pBHarrayhead)
//     ( c-addr n char -- )
{
    unsigned char* address;
    INT64 n;
    unsigned char c;

    UINT64* plength;
    unsigned char* pbuffer;

    const char* perror;


    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfillname); 
        return;
    }

    if (*plength < 3 * sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfillname); 
        return;
    }

    c = (unsigned char)(*((UINT64*)(pbuffer + *plength - (sizeof(UINT64)))));
    n = *((int*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((unsigned char**)(pbuffer + *plength - (3 * sizeof(UINT64)))); 

    if (n <= 0)
    {
        return;
    }

    perror = dg_fillwithbyte (
        address,
        (UINT64)n,
        (UINT64)c);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_forthfillname); 
    }
    
    *plength -= (3 * sizeof(UINT64));
}


void dg_forthfind (Bufferhandle* pBHarrayhead)
//     ( c-addr -- c-addr 0 ) if word not found
//     ( c-addr -- xt 1 ) if word found and it is immediate
//     ( c-addr -- xt -1 ) if word found and it is not immediate
{
    unsigned char* pname = NULL;
    UINT64 namelength = 0;

    UINT64 definition = 0;

    Definitionheader* pdefinition = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthcount(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindname);
        return;
    }

    // wont get error because count worked
    namelength = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
    pname = (unsigned char*)dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);

    definition = dg_finddefinsearchorder(pBHarrayhead, pname, namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindname);
        return;
    }

    if (definition == DG_ENDOFWORDLIST)
    {
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(pname - 1));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthfindname);
            return;
        }

        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthfindname);
        }

        return;
    }
    
    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // probably can't get this one
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfindname);
        return;
    }

    pdefinition = dg_getpdefinition(pBHarrayhead, definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindname);
        return;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)(&dg_forthdocompiletypealwaysexecute)))
    {
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, 1);
    }
    else
    {
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(largestunsignedint));
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfindname);
    }
}


void dg_forthfmslashmod (Bufferhandle* pBHarrayhead)
//              ( d1 n1 -- n2 n3 )
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
        dg_pusherror(pBHarrayhead, dg_forthfmslashmodname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfmslashmodname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - 3*sizeof(UINT64));
    // ( numlo numhi denom )
    // ( eax   edx   ecx   )
    
    dg_fmslashmod(pints);

    *pbuflength -= sizeof(UINT64);
}


void dg_forthhere (Bufferhandle* pBHarrayhead)
//     ( -- addr )
{
    UINT64 dsbufid;
    unsigned char* pdataspace;
    UINT64* pdataspacelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthherename);
        return;
    }

    pdataspace = dg_getpbuffer(
        pBHarrayhead,
        dsbufid,
        &pdataspacelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthherename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)(pdataspace + *pdataspacelength));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthherename);
        return;
    }    
}


void dg_forthhold (Bufferhandle* pBHarrayhead)
//     ( char -- )
{
    UINT64 c;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    c = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthholdname);
        return;
    }

    dg_insertinbuffer(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        0,
        1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthholdbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthholdname);
        return;
    }

    dg_putbufferbyte(
        pBHarrayhead,
        DG_HOLD_BUFFERID,
        0,
        (unsigned char)c);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthholdbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthholdname);
    }
}


void dg_forthi (Bufferhandle* pBHarrayhead)
//     ( index limit -rstack- index limit )
//     ( -- index )
{
    unsigned char* pcfstack;
    UINT64* pcfstacklength;

    UINT64 n1;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pcfstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &pcfstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthiname);
        return;
    }

    if (*pcfstacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthiname);
        return;
    }

    n1 = *((UINT64*)(pcfstack + *pcfstacklength - (2 * sizeof(UINT64))));

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthiname);
        return;
    }
}


void dg_forthif (Bufferhandle* pBHarrayhead)
//           ( -- ifoffset )
{
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)&dg_popdatastack);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthifname);
        return;
    }

    dg_compilecompare(
        pBHarrayhead,
        FORTH_FALSE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthifname);
        return;
    }

    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthifname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthifname);
        return;
    }
}



void dg_forthimmediate (Bufferhandle* pBHarrayhead)
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
        dg_pusherror(pBHarrayhead, dg_forthimmediatename);
        return;
    }

    definition = dg_getlatestdefinition(
        pBHarrayhead,
        vocab);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthimmediatename);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthimmediatename);
        return;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)&dg_forthdocompiletypesubroutine))
    {
        pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypealwaysexecute;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)&dg_forthdocompiletypesafesubroutine))
    {
        pdefinition->compileroutineoffset = (UINT64)&dg_forthdocompiletypealwaysexecute;
    }
}


void dg_forthinvert (Bufferhandle* pBHarrayhead)
//     ( x1 -- x2 )
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
        dg_pusherror(pBHarrayhead, dg_forthinvertname);
        return;
    }

    // ifpdatastack or pbuflength (unsigned char*)badbufferhandle thats an error

    if (*pbuflength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthinvertname);
        return;
    }

    // could check for corrupt buflength here
    pints = (UINT64*)(pdatastack + *pbuflength - (sizeof(UINT64)));

    pints[0] = pints[0] ^ (UINT64)largestunsignedint;
}


void dg_forthj (Bufferhandle* pBHarrayhead)
//     ( index2 limit2 index1 limit1 -rstack- index2 limit2 index1 limit1 )
//     ( -- index2 )
{
    unsigned char* pcfstack = NULL;
    UINT64* pcfstacklength = NULL;

    UINT64 n1 = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pcfstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &pcfstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthjname);
        return;
    }

    if (*pcfstacklength < (4 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthjname);
        return;
    }

    n1 = *((UINT64*)(pcfstack + *pcfstacklength - (4 * sizeof(UINT64))));

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthjname);
        return;
    }
}


void dg_forthkey (Bufferhandle* pBHarrayhead)
//     ( -- char )
{
    UINT64 key;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    key = dg_getch();

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        key);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthkeyname);
        return;
    }
}


void  dg_forthleave (Bufferhandle* pBHarrayhead)
//               ( compile: ) ( -- ) ( -leavestack- leaveoffset )
//               ( compiled code does: ) ( loopsys -rstack- )
{
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthleavename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LEAVESTACK_BUFFERID,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthleavebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthleavename);
        return;
    }
}


void dg_forthliteral (Bufferhandle* pBHarrayhead)
//                ( n1 -- )
{
    // compile push n1 to the data stack
    UINT64 data;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    data = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthliteralname);
        return;
    }
    
    // dg_compilemovntoreg(pBHarrayhead, data, dg_rsi);
    // dg_compilepushdatastack(pBHarrayhead);
    
    // this way is more portable
    dg_compilepushntodatastack (
        pBHarrayhead,
        data);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthliteralname);
        return;
    }
}


UINT64 dg_checkloopdone (Bufferhandle* pBHarrayhead)
//       ( index limit -r- index limit | index+1 limit )
{
    unsigned char* prstack;
    UINT64* prstacklength;
    UINT64* pints;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (FORTH_TRUE);
    }


    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_checkloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    if (*prstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_checkloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    pints = (UINT64*)(prstack + *prstacklength - (2 * sizeof(UINT64)));

    // if 0 < limit - index <= loopstep, loop is finished
    if ((pints[1] - pints[0]) == 1)
    {
        // *prstacklength -= 2* sizeof(UINT64); // doing unloop
        return (FORTH_TRUE);
    }
    
    pints[0] += 1;
    return (FORTH_FALSE);
}


void dg_forthloop (Bufferhandle* pBHarrayhead)
//               ( do-sys -- )
//               ( compiled code does: ) ( -- )
//               ( loop-sys1 -controlflowstack- ) if loop ends
//               ( loop-sys1 -controlflowstack- loop-sys1' ) if loop does not end
{
    UINT64* pleavebuf;
    UINT64* pleavebuflength;

    UINT64 beginoffset;

    UINT64 i;
    UINT64 u;
    UINT64 leaveoffset;
    
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    beginoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }
    
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_checkloopdone));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }
    
    dg_compilecompare(
        pBHarrayhead,
        FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        beginoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }
    
    // need to resolve leavestack for leaveoffsets with here >= leaveoffset >= dooffset
    pleavebuf = (UINT64*)dg_getpbuffer(
        pBHarrayhead,
        DG_LEAVESTACK_BUFFERID,
        &pleavebuflength);

    if (pleavebuf == (UINT64*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthleavebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthloopname);
        return;
    }

    u = (*pleavebuflength) / sizeof (UINT64);

    for (i = 0; i < u; i++  )
    {
        leaveoffset = pleavebuf[u - (i+1)];

        if (leaveoffset >= beginoffset)
        {
            dg_pushbufferuint64(
                pBHarrayhead,
                DG_DATASTACK_BUFFERID,
                leaveoffset);
            // can't get error because we popped a number from data stack above

            dg_forththen(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthloopname);
                return;
            }

            *pleavebuflength = (u - (i+1)) * sizeof (UINT64);     // drop this one and everything after it    
        }
        else
        {
            break;
        }
    }
    
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_forthunloop));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloopname);
    }
}


void dg_forthlshift (Bufferhandle* pBHarrayhead)
//               ( x1 u -- x2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlshiftname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthlshiftname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2*sizeof(UINT64)));

        pints[0] = dg_lshift(pints[0], pints[1]);

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthmstar (Bufferhandle* pBHarrayhead)
//         ( n1 n2 -- d )
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
        dg_pusherror(pBHarrayhead, dg_forthmstarname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthmstarname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    dg_mstar(pints[0], pints[1], (INT64*)pints);
}


void dg_forthmax (Bufferhandle* pBHarrayhead)     
//     ( n1 n2 -- n3 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    INT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthmaxname);
        return;
    }

    // ifpdatastack or pbuflength (unsigned char*)badbufferhandle thats an error

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthmaxname);
        return;
    }

    // could check for corrupt buflength here
    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[1] > pints[0])
    {
        pints[0] = pints[1];
    }
    
    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthmin (Bufferhandle* pBHarrayhead)     
//     ( n1 n2 -- n3 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthminname);
        return;
    }

    // ifpdatastack or pbuflength (unsigned char*)badbufferhandle thats an error

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthminname);
        return;
    }

    // could check for corrupt buflength here
    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[1] < pints[0])
    {
        pints[0] = pints[1];
    }
    
    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthmod (Bufferhandle* pBHarrayhead)
//            ( n1 n2 -- n3 )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthslashmod(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthmodname);
        return;
    }
    
    dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthmodname);
        return;
    }
}


void dg_forthmove (Bufferhandle* pBHarrayhead)
//     ( addr1 addr2 u -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char* addr1;
    unsigned char* addr2;
    INT64 u = 0;
    
    const char* flag;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthmovename);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthmovename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    addr1 = (unsigned char*)(pints[0]); // source
    addr2 = (unsigned char*)(pints[1]); // destination
    u = (signed int)(pints[2]);         // length

    if (u <=0)
    {
        // I think I want to push a length to big error here
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthmovename);
        return;
    }

    flag = dg_movebytes(
        addr1,
        addr2,
        u);

    if (flag != dg_success)
    {
        dg_pusherror(
            pBHarrayhead,
            flag);
        
        if (addr2 < addr1)
        {
            dg_pusherror(pBHarrayhead, dg_forthplusname);
        }
        else
        {
            dg_pusherror(pBHarrayhead, dg_forthminusname);
        }

        dg_pusherror(pBHarrayhead, dg_movebytesname);

        dg_pusherror(pBHarrayhead, dg_forthmovename);
    }
    

    *pbuflength -= (3* sizeof(UINT64));
}


void dg_forthnegate (Bufferhandle* pBHarrayhead) 
//     ( n1 -- 0-n1 ) 
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
        dg_pusherror(pBHarrayhead, dg_forthnegatename);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnegatename);
        return;
    }

    // could check for misaligned data stack here

    pints = (INT64*)(pdatastack + *pbuflength - (sizeof(UINT64)));

    pints[0] = 0 - pints[0];
}


void dg_forthor (Bufferhandle* pBHarrayhead)
//     ( x1 x2 -- x3 )             
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
        dg_pusherror(pBHarrayhead, dg_forthorname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthorname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = pints[0] | pints[1];

    *pbuflength = *pbuflength - (sizeof(UINT64));
}


void dg_forthover (Bufferhandle* pBHarrayhead)          
//     ( n1 n0 -- n1 n0 n1 )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 n1;

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
        dg_pusherror(pBHarrayhead, dg_forthovername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthovername);
        return;
    }

    // could check for misaligned data stack here
    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    n1 = pints[0];


    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthovername);
    }
}


void dg_forthpostpone (Bufferhandle* pBHarrayhead)
//     (compile mode)
//       ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
{
    
    Definitionheader* pdefinition;

    UINT64 definitionid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthtick(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    // should not be possible if tick worked
    definitionid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    if (definitionid == DG_ENDOFWORDLIST)
    {
        dg_pusherror(pBHarrayhead, dg_wordnotfoundinsearchordererror);
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definitionid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->dataoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->databuf);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }

    if ((pdefinition->compileroutinebuf == DG_CORE_BUFFERID) &&
        (pdefinition->compileroutineoffset == (UINT64)&dg_forthdocompiletypealwaysexecute))
    {
        // not all of them have to be safe... just the ones that compile
        //   but for now treating all of them as safe
        dg_forthdocompiletypesafesubroutine(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthpostponename);
            return;
        }

        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            coloncallssafeflag,
            FORTH_TRUE);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthpcoloncallssafeflagname);
            dg_pusherror(pBHarrayhead, dg_forthpostponename);
            return;
        }
    }
    else
    {
        dg_callbuffer(
            pBHarrayhead,
            pdefinition->compileroutinebuf, 
            pdefinition->compileroutineoffset);
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpostponename);
        return;
    }
}


void dg_forthquit (Bufferhandle* pBHarrayhead)
{    
    UINT64 wasquitinitflag;
    void* pquitsavedstate;

    UINT64 firsttimethrough = FORTH_TRUE;
    UINT64 arepromptsoffflag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    wasquitinitflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        quitwasinitializedflag);

    if (dg_geterrorcount(pBHarrayhead) != 0) // should this be 0?
    {
        dg_pusherror(pBHarrayhead, dg_forthpquitwasinitflagname);
        dg_pusherror(pBHarrayhead, dg_forthquitname);
        return;
    }

    arepromptsoffflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        promptsoffflag);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpnopromptsflagname);
        dg_pusherror(pBHarrayhead, dg_forthquitname);
        return;
    }

    pquitsavedstate = (void*)dg_getpbufferoffset(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_quitsavedstate);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        //dg_pusherror(pBHarrayhead, dg_forthquitsavedstatename);
        dg_pusherror(pBHarrayhead, dg_forthquitname);
        return;
    }

    if (wasquitinitflag != 0xFF7344D9696E6974)
    {
        dg_savequitstate(pquitsavedstate);

        // can't really get errors here
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            quitwasinitializedflag,
            0xFF7344D9696E6974);
    }

    else
    {
        dg_restorequitstate(pquitsavedstate);
    }
    
    dg_clearbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthquitname); // so you see the error when the program exits
        return;
    }
    
    dg_forthleftbracket(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquitname);
        return;
    }
    
    dg_doinputstuff(
        pBHarrayhead,
        &firsttimethrough);
}


void dg_forthrfrom (Bufferhandle* pBHarrayhead)
//     ( x1 -r- )
//     ( -- x1 )
{
    UINT64 x1;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    x1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_RSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthrfromname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        x1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthrfromname);
        return;
    }
}


void dg_forthrfetch (Bufferhandle* pBHarrayhead)
//          ( x1 -r- x1 )
//          ( -- x1 )
{
    UINT64 x1;

    unsigned char* prstack;
    UINT64* prstacklength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (prstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthrfetchname);
        return;
    }

    if (*prstacklength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrfetchname);
        return;
    }

    x1 = *((UINT64*)(prstack + *prstacklength - sizeof(UINT64)));
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        x1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthrfetchname);
    }
}



void dg_forthrecurse (Bufferhandle* pBHarrayhead)
//     ( -- )
{

    UINT64 definition;

    unsigned char* state;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    definition = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_latestnewword);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrecursename);
        return;
    }
    
    if (DG_ENDOFWORDLIST == definition)
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrecursename);
        return;
    }

    // need to force compile mode so this word can be used inside assembler compilations without the brackets
    state = (unsigned char*)dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthrecursename);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable,
        (UINT64)dg_statecompile);

    // if getstate worked, pushstate should work

    dg_executedefinition(
        pBHarrayhead,
        definition);

    // check error - but don't return, still need to restore state

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable,
        (UINT64)state);

    // if getstate and putstate above worked, this putstate should work

    //if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    //{
        //dg_pusherror(pBHarrayhed, dg_forthstatename);
        //dg_pusherror(pBHarrayhead, dg_forthrecursename);
    //}
}


void dg_forthrepeat (Bufferhandle* pBHarrayhead)
//               ( whileoffset beginoffset -- )
{
    UINT64 beginoffset;
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    beginoffset = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepeatname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(pBHarrayhead, DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepeatname);
        return;
    }
    
    dg_resolvecompiledbranch(pBHarrayhead, afterbranchoffset, beginoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepeatname);
        return;
    }

    dg_forththen(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepeatname);
        return;
    }
}


void dg_forthrot (Bufferhandle* pBHarrayhead)           
//       ( n1 n2 n3 -- n2 n3 n1 )
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
        dg_pusherror(pBHarrayhead, dg_forthrotname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrotname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));

    data = pints[0];
    pints[0] = pints[1];
    pints[1] = pints[2];
    pints[2] = data;
}


void dg_forthrshift (Bufferhandle* pBHarrayhead)
//               ( x1 u -- x2 )
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
        dg_pusherror(pBHarrayhead, dg_forthrshiftname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrshiftname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    pints[0] = dg_rshift(pints[0], pints[1]);

    *pbuflength = *pbuflength - sizeof(UINT64);
}


// This word does not return caddr u in the execute state like OS" because if it did,
//   the caddr pointer would become invalid the next time anything else is compiled
// Use OS" or $" if you need this functionality
void dg_forthsquotes (Bufferhandle* pBHarrayhead) // ( S" )
//           ( "somestuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
//           ( compiletime: -- )
//           ( runtime: -- caddr u  )
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
        dg_pusherror(pBHarrayhead, dg_forthsquotesname);
        return;
    }

    dg_compileacopyofsscopyto(
        pBHarrayhead,
        psqstr,
        sqstrlen);

    // This wasn't in but it probably should be 2022 July 14
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {
    //    dg_pusherror(pBHarrayhead, dg_forthsquotesname);
    //    return;
    // }

    /*
    
    dg_compilecalloffset(
        pBHarrayhead,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsquotesname);
        return;
    }
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)psqstr,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsquotesname);
        return;
    }

    // start addr of string will be on return stack already
    // need to move it to
    
    dg_compilepushdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsquotesname);
        return;
    }
    
    
    dg_compilepushntodatastack(
        pBHarrayhead,
        sqstrlen);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsquotesname);
        return;
    }
    */
    
}



void dg_forthstod (Bufferhandle* pBHarrayhead)
//     ( n -- d )
{
    INT64 nlo;
    INT64 nhi;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    nlo = (INT64)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthstodname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        nlo); // shouldn't be an error
    
    if (nlo < 0)
    {
        nhi = largestunsignedint;
    }
    else
    {
        nhi = 0;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        nhi);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthstodname);
        return;
    }
}


void dg_forthsign (Bufferhandle* pBHarrayhead)
//             ( n -- )
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
        dg_pusherror(pBHarrayhead, dg_forthsignname);
        return;
    }

    if (n < 0)
    {
        dg_insertinbuffer(
            pBHarrayhead,
            DG_HOLD_BUFFERID,
            0,
            1);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthholdbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthsignname);
            return;
        }

        dg_putbufferbyte(pBHarrayhead, DG_HOLD_BUFFERID, 0, '-');

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthholdbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthsignname);
        }
    }
}


void dg_forthsmslashrem (Bufferhandle* pBHarrayhead)
//              ( d1 n1 -- n2 n3 )
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
        dg_pusherror(pBHarrayhead, dg_forthsmslashremname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsmslashremname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - 3*sizeof(UINT64));
    // ( numlo numhi denom )
    // ( eax   edx   ecx   )
    
    dg_smslashrem(pints);

    *pbuflength -= sizeof(UINT64);
}


void dg_forthsource (Bufferhandle* pBHarrayhead)
//     ( -- caddr u )
{
    unsigned char* pcib;
    UINT64* pciblength;

    UINT64 cibid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthsourcename);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthsourcename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pcib);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsourcename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        *pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsourcename);
        return;
    }
}


void dg_forthspace (Bufferhandle* pBHarrayhead)         // ( -- )
{
    unsigned char c = ' ';
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_writestdout(
        pBHarrayhead,
        &c,
        1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthspacename);
    }
}


void dg_forthspaces (Bufferhandle* pBHarrayhead)        
//               ( n -- )
{
    INT64 i;
    INT64 n;

    UINT64 olderrorcount  = dg_geterrorcount(pBHarrayhead);
    
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
        dg_pusherror(pBHarrayhead, dg_forthspacesname);
        return;
    }

    if (n > 0)
    {
        // this is the slow way to do it, better to build a string and do only 1 write
        for (i = 0; i < n; i++)
        {
            dg_forthspace(pBHarrayhead);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthspacesname);
                return;
            }
        }
    }
}


void dg_forthstate (Bufferhandle* pBHarrayhead)
//              ( -- a-addr )
{
    unsigned char* pstate;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pstate = dg_getpbuffersegment(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable,
        sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstate);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthstatename);
    }
}


void dg_forthswap(Bufferhandle* pBHarrayhead)
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;
    UINT64 temp;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthswapname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthswapname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    // could do asm xchg here
    temp = pints[0];
    pints[0] = pints[1];
    pints[1] = temp;
}


void dg_forththen (Bufferhandle* pBHarrayhead)
//     ( ifoffset -- )
{
    UINT64 currentcbuf;

    unsigned char* pcbuf;
    UINT64* pcbuflength;

    UINT64 bufferlength;
    UINT64 oldoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    currentcbuf = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forththenname);
        return;
    }
    
    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        currentcbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forththenname);
        return;
    }
    
    oldoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forththenname);;
        return;
    }
    
    dg_resolvecompiledbranch (
        pBHarrayhead,
        oldoffset, // after branch offset
        bufferlength); // target offset
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forththenname);;
        return;
    }
}


void dg_forthtype (Bufferhandle* pBHarrayhead)
//             ( c-addr u -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64* pints;

    unsigned char* caddr;
    INT64 u;

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
        dg_pusherror(pBHarrayhead, dg_forthtypename);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtypename);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    caddr = (unsigned char*)(pints[0]);

    u = (INT64)(pints[1]);

    if (u < 0)
    {
        dg_pusherror(pBHarrayhead, dg_signedlengthlessthan0error);
        dg_pusherror(pBHarrayhead, dg_forthtypename);
        return;
    }

    if (u != 0)
    {
        dg_writestdout(
            pBHarrayhead,
            caddr,
            u);

        if (olderrorcount != dg_geterrorcount(pBHarrayhead))
        {
            dg_pusherror(pBHarrayhead, dg_forthtypename);
        }
    }
    
    *pbuflength -= 2*sizeof(UINT64);
}


void dg_forthudot (Bufferhandle* pBHarrayhead)
//        ( u -- )
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
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }

    dg_forthlessthannumbersign(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }

    dg_forthnumbersigns(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }

    dg_forthnumbersigngreater(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }

    dg_forthtype(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }

    dg_forthspace(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthudotname);
        return;
    }
}


void dg_forthulessthan (Bufferhandle* pBHarrayhead)     
//             ( u1 u2 -- flag )
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
        dg_pusherror(pBHarrayhead, dg_forthulessthanname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthulessthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] < pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (1 * sizeof(UINT64));
}


void dg_forthumstar (Bufferhandle* pBHarrayhead)
//          ( u1 u2 -- ud )
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
        dg_pusherror(pBHarrayhead, dg_forthumstarname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthumstarname);
        return;
    }

    // could check for misaligned data stack pointer here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    dg_umstar(pints[0], pints[1], pints);
}


void dg_forthumslashmod (Bufferhandle* pBHarrayhead)
//              ( ud u1 -- u2 u3 )
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
        dg_pusherror(pBHarrayhead, dg_forthumslashmodname);
        return;
    }

    if (*pbuflength < (3 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthumslashmodname);
        return;
    }

    // could check for misaligned datastack here

    pints = (UINT64*)(pdatastack + *pbuflength - (3 * sizeof(UINT64)));
    // ( numlo numhi denom )
    // ( eax   edx   ecx   )

    dg_umslashmod(pints);
    
    *pbuflength -= sizeof(UINT64);
}


void dg_forthunloop (Bufferhandle* pBHarrayhead)
//     ( limit index -rstack- )
{
    unsigned char* pcfstack;
    UINT64* pcfstacklength;


    pcfstack = dg_getpbuffer(
        pBHarrayhead, 
        DG_RSTACK_BUFFERID, 
        &pcfstacklength);

    if (pcfstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthunloopname);
        return;
    }

    if (*pcfstacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthunloopname);
        return;
    }

    *pcfstacklength -= 2* sizeof(UINT64);
}


void dg_forthuntil (Bufferhandle* pBHarrayhead)
//     ( beginoffset -- )
{
    UINT64 beginoffset;
    
    UINT64 afterbranchoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    beginoffset = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthuntilname);
        return;
    }
    
    dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_popdatastack));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuntilname);
        return;
    }
    
    dg_compilecompare(pBHarrayhead, FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuntilname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(pBHarrayhead, DG_BRANCHTYPE_EQUAL);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuntilname);
        return;
    }
    
    dg_resolvecompiledbranch(pBHarrayhead, afterbranchoffset, beginoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthuntilname);
    }
}


void dg_forthvariable (Bufferhandle* pBHarrayhead)
//     ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//     ( -currentnewvariablebuffer- +sizeofunsignedint )
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
        dg_pusherror(pBHarrayhead, dg_forthvariablename);
        return;
    }

    dsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthvariablename);
        return;
    }

    dg_growbuffer(
        pBHarrayhead,
        dsbufid,
        sizeof(UINT64),
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthvariablename);
        return;
    }
}


void dg_forthwhile (Bufferhandle* pBHarrayhead)
//     ( beginoffset -- whileoffset beginoffset )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthif(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwhilename);
        return;
    }

    dg_forthswap(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwhilename);
        return;
    }
}


void dg_forthword (Bufferhandle* pBHarrayhead)
//     ( "<chars>word<char>morestuff" -currentinputbuffer- "<char>morestuff")
//     ( char -- c-addr )
//     ( -wordbuffer- "word" )
{
    unsigned char* pcib;
    UINT64* pciblength;

    UINT64* pcibcurrentoffset;
    UINT64 ciboldoffset;

    unsigned char c;

    UINT64 namelength;
    unsigned char* pname;

    unsigned char* pwordbuf;
    UINT64* pwordbuflength;

    Bufferhandle* pBH;

    const char* pError;

    UINT64 i;

    UINT64 cibid;

    unsigned char delimiter;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    delimiter = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (pcib == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;

    //getting off the delimiters
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if (c != delimiter)
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

    ciboldoffset = *pcibcurrentoffset;

    //getting to the next delimiter after the word
    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + *pcibcurrentoffset);
        
        if ((c == delimiter) || dg_islineterminator(c)) // word is current line only 2022 July 11
        {
            break;
        }

        (*pcibcurrentoffset)++;
    }

    namelength = *pcibcurrentoffset - ciboldoffset;
    
    // getting off first delimiter, forth standard requirement
    if(*pcibcurrentoffset < *pciblength)
    {
        (*pcibcurrentoffset)++;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    if (namelength > maxwordlength)  
    {
        dg_pusherror(pBHarrayhead, dg_maxwordlengthexceedederror);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    pname = pcib + ciboldoffset;

    pwordbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_WORD_BUFFERID,
        &pwordbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    *pwordbuflength = 0; // clear the buffer - actually if I could just force it to be maxsize and return a pointer, that would be a lot simpler

    dg_growbuffer(
        pBHarrayhead,
        DG_WORD_BUFFERID,
        namelength + 1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthwordbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    // unless someone changed the default max size of the buffer, it shouldn't have moved, but just in case
    pwordbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_WORD_BUFFERID,
        &pwordbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwordbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
        return;
    }

    pwordbuf[0] = (unsigned char)namelength; // this assumes maxwordlength is 255 or less

    for (i = 0; i < namelength; i++)
    {
        pwordbuf[1 + i] = pname[i];
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pwordbuf);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwordname);
    }
}


void dg_forthxor (Bufferhandle* pBHarrayhead)
//     ( x1 x2 -- x3 )
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
        dg_pusherror(pBHarrayhead, dg_forthxorname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthxorname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    pints[0] = pints[0] ^ pints[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthleftbracket (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable,
        (UINT64)dg_stateexecute);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthleftbracketname);
        return;
    }
}


void dg_forthbrackettick (Bufferhandle* pBHarrayhead)
// ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
// ( -- )
// ( compiled code does: ) ( -- executiontokenofname )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthtick(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbrackettickname);
        return;
    }

    dg_forthliteral(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbrackettickname);
        return;
    }
}


void dg_forthbracketchar (Bufferhandle* pBHarrayhead)
// ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
// ( -- )
// ( compiled code does: ) ( -- firstcharofname )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthchar(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcharname);
        return;
    }

    dg_forthliteral(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketcharname);
        return;
    }
}


void dg_forthrightbracket (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable,
        (UINT64)dg_statecompile);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthrightbracketname);
        return;
    }
}


// //////////////////////////////////
// Forth Standard Core Extensions  //
// //////////////////////////////////

void dg_forthnumbertib (Bufferhandle* pBHarrayhead)
// ( -- a-addr )
{
    unsigned char* pcib;
    UINT64* pciblength;

    UINT64 cibid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthnumbertibname);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthnumbertibname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthnumbertibname);
        return;
    }
}


void dg_forthzeronotequals (Bufferhandle* pBHarrayhead)    
//              ( n1 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthzeronotequalsname);
        return;
    }

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthzeronotequalsname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    if (pints[0] != 0)
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }
}


void dg_forthzerogreater (Bufferhandle* pBHarrayhead)     
//            ( n1 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthzerogreatername);
        return;
    }

    // ifpdatastack or pbuflength (unsigned char*)badbufferhandle thats an error

    if (*pbuflength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthzerogreatername);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));

    if (((INT64)(pints[0])) > 0)
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }
}

void dg_forthdotparen (Bufferhandle* pBHarrayhead) // ( ( ) comment
//         ( "somestuff<rightparen>morestuff" -currentinputbuffer- "morestuff" )
{
    unsigned char* pstring;
    UINT64 stringlength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pstring = dg_parse(
        pBHarrayhead,
        &stringlength,
        ')');
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotparenname);
        return;
    }
    
    if (0 == stringlength)
    {
        return;
    }
    
    // length will be greater than 0...
    dg_writestdout(
        pBHarrayhead,
        pstring,
        stringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdotparenname);
        return;
    }
}


void dg_forthnotequals (Bufferhandle* pBHarrayhead)        
//          ( n1 n2 -- flag )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    INT64* pints = NULL;


    pdatastack = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthnotequalsname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnotequalsname);
        return;
    }

    // could check for misaligned data stack

    pints = (INT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] != pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - (sizeof(UINT64));
}

void dg_forthtwotor (Bufferhandle* pBHarrayhead)
//       ( x1 x2 -- )
//       ( -r- x1 x2 )
{
    UINT64 x1, x2;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwotorname);
        return;
    }

    x1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwotorname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        x1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwotorname);
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        x2);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtwotorname);
    }
}



void dg_forthtworfetch (Bufferhandle* pBHarrayhead)
//                             ( n1 n2 -r- n1 n2 )
//                             ( -- n1 n2 )
{
    unsigned char* prstack = NULL;
    UINT64* prstacklength = NULL;

    INT64* pints = NULL;

    UINT64 n = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (prstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtworfetchname);
        return; 
    }

    if (*prstacklength < 2* sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtworfetchname);
        return;
    }

    pints = (INT64*)(prstack + *prstacklength - (2* sizeof(UINT64)));

    dg_pushdatastack(pBHarrayhead, pints[0]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtworfetchname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, pints[1]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtworfetchname);
        return;
    }
    
    return;
}


void dg_forthtworfrom (Bufferhandle* pBHarrayhead)
//     ( x1 x2 -r- )
//     ( -- x1 x2 )
{
    unsigned char* prstack = NULL;
    UINT64* prstacklength = NULL;

    INT64* pints = NULL;

    UINT64 n = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (prstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtworfromname);
        return; 
    }

    if (*prstacklength < 2* sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtworfromname);
        return;
    }

    pints = (INT64*)(prstack + *prstacklength - (2* sizeof(UINT64)));

    dg_pushdatastack(pBHarrayhead, pints[0]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtworfromname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, pints[1]);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtworfromname);
        return;
    }
    
    *prstacklength -= (2* sizeof(UINT64));
    
    return;
}


void dg_forthcolonnoname (Bufferhandle* pBHarrayhead)
//     ( -- executiontoken colonsys )
{

    UINT64 definition = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    definition = dg_createsubthreaddef(
        pBHarrayhead, 
        (unsigned char*)"NONAME", 
        6);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
        return;
    }

    dg_forthrightbracket(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        colonnonamemarker);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
        return;
    }
    
    dg_compileinitlocals (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
    }

    dg_putbufferuint64(
        pBHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        coloncallssafeflag, 
        FORTH_FALSE);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcolonnonamename);
    }
}


// C" parse " , if string too long give error, compile length, compile string
void dg_forthcquote (Bufferhandle* pBHarrayhead)
//              ( "string<char>morestuff" -currentinputbuffer- "morestuff" )
//              ( -- addr )
{
    unsigned char* pstring;
    UINT64 stringlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pstring = dg_parse(
        pBHarrayhead,
        &stringlength,
        '"');
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    } 
    
    if (stringlength > 255)
    {
        dg_pusherror(pBHarrayhead, dg_countlengthexceedederror);
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    }
    
    dg_compilecalloffset (pBHarrayhead, stringlength + 1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    }    
    
    dg_compilesegment (
        pBHarrayhead,
        (const char*)&stringlength, // assumes little endian
        1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    }  
    
    dg_compilesegment (
        pBHarrayhead,
        (const char*)pstring,
        stringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    }    
    
    // address of string is now on return stack    
    dg_compilepushdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcquotename);
        return;
    }
}


void dg_forthagain (Bufferhandle* pBHarrayhead)
//     ( beginoffset -- )
{
    UINT64 beginoffset;
    
    UINT64 afterbranchoffset;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    beginoffset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthagainname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthagainname);
        return;
    }
    
    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        beginoffset);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthagainname);
    }
}


// FALSE defined as a UINT64 constant 
void dg_fortherase (Bufferhandle* pBHarrayhead)
{
    unsigned char* address;
    INT64 length;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    length = (INT64)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_fortherasename);
        return;
    }
    
    address = (unsigned char*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_fortherasename);
        return;
    }
    
    // making it 1 instead of 0 in case dg_fillwithbyte treats 0 as 0x100000000
    //  forth standard says if length is 0 or less, nothing is done
    if (length < 1)
    {
        // not sure if this should be an error but it is in standard that length < 0 not done.
        return;
    }
    
    perror = dg_fillwithbyte (
        address,
        (UINT64)length,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_fortherasename);
        return;
    }
}


// FALSE is implemented as a constant

void dg_forthhex (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable,
        16);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthhexname);
        return;
    }
}


void dg_forthnip (Bufferhandle* pBHarrayhead)
//         ( n1 n2 -- n2 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthnipname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnipname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - 2*sizeof(UINT64));

    pints[0] = pints[1];

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthpad(Bufferhandle* pBHarrayhead)
//            ( -- ppad )
{
    unsigned char* ppad;
    UINT64*  ppadlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    ppad = dg_getpbuffer(
        pBHarrayhead,
        DG_PAD_BUFFERID,
        &ppadlength);

    if (ppad == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpadbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthpadname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, (UINT64)ppad);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpadname);
        return;
    }
}


void dg_forthlinesparse (Bufferhandle* pBHarrayhead)
//              ( "string<endchar>morestuff" -currentinputbuffer- "morestuff" )
//              ( endchar -- addr length )
{
    unsigned char* pstring;
    UINT64 stringlength;
    
    unsigned char endchar;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    endchar = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlinesparsename);
        return;
    }

    pstring = dg_parsemultiline(
        pBHarrayhead,
        &stringlength,
        endchar);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinesparsename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinesparsename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlinesparsename);
        return;
    }
}


void dg_forthparse (Bufferhandle* pBHarrayhead)
//              ( "string<endchar>morestuff" -currentinputbuffer- "morestuff" )
//              ( endchar -- addr length )
{
    unsigned char* pstring;
    UINT64 stringlength;
    
    unsigned char endchar;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    endchar = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsename);
        return;
    }

    pstring = dg_parse(
        pBHarrayhead,
        &stringlength,
        endchar);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsename);
        return;
    }
}


void dg_forthparsebuffer (Bufferhandle* pBHarrayhead)
//              ( "string<endchar>morestuff" -currentinputbuffer- "morestuff" )
//              ( endchar -- addr length )
{
    unsigned char* pstring;
    UINT64 stringlength;
    
    unsigned char endchar;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    endchar = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsebuffername);
        return;
    }

    pstring = dg_parsemultiline(
        pBHarrayhead,
        &stringlength,
        endchar);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsebuffername);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsebuffername);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsebuffername);
        return;
    }
}


// mentioned in appendix for word PARSE
void dg_forthparseword (Bufferhandle* pBHarrayhead)
//     ( "<delimeters>word<delimeters>morestuff" -currentinputbuffer- "morestuff" )
//     ( -- addr length )
{
    UINT64 namelength = 0;
    unsigned char* pname = NULL;


    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsewordname);
        return;
    }
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_nowordfounderror);
        dg_pusherror(pBHarrayhead, dg_forthparsewordname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pname);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsewordname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsewordname);
        return;
    }
}

void dg_forthparsewords (Bufferhandle* pBHarrayhead)
//              ( "<delimeters>word<delimeters>morestuff"morestuff" | 
//                "string<endchar>morestuff" -currentinputbuffer- "morestuff" )
//              ( char -- foundendflag addr length )
{
    unsigned char* pstring;
    UINT64 stringlength;
    
    unsigned char endchar;
    UINT64 foundendflag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    endchar = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsewordsname);
        return;
    }

    pstring = dg_parsewords(
        pBHarrayhead,
        &stringlength,
        endchar, // enddelimiter,
        &foundendflag,
        FORTH_TRUE); // singlelineonlyflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsewordsname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        foundendflag);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsewordsname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparsewordsname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthparsewordsname);
        return;
    }
}


void dg_forthlinesparsenames (Bufferhandle* pBHarrayhead)
//              ( "<delimeters>word<delimeters>morestuff"morestuff" | 
//                "string<endchar>morestuff" -currentinputbuffer- "morestuff" )
//              ( char -- foundendflag addr length )
{
    unsigned char* pstring;
    UINT64 stringlength;
    
    unsigned char endchar;
    UINT64 foundendflag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    endchar = (unsigned char)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlinesparsenamesname);
        return;
    }

    pstring = dg_parsewords(
        pBHarrayhead,
        &stringlength,
        endchar, // enddelimiter,
        &foundendflag,
        FORTH_FALSE); // singlelineonlyflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinesparsenamesname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        foundendflag);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlinesparsenamesname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinesparsenamesname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        stringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthlinesparsenamesname);
        return;
    }
}


void dg_forthparseline (Bufferhandle* pBHarrayhead)
//     ( "characters<terminator>morestuff" -currentinputbuffer- "morestuff" )
//     ( -- addr length )
{
    UINT64 linelength = 0;
    unsigned char* pline = NULL;


    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pline = dg_parseline(
        pBHarrayhead,
        &linelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparselinename);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pline);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparselinename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        linelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthparselinename);
        return;
    }
}


void dg_forthpick(Bufferhandle* pBHarrayhead)
//     ( nidx ... n2 n1 n0 idx -- n2 n1 n0 nidx )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;

    UINT64 numberonstack;
    UINT64 idx;

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
        dg_pusherror(pBHarrayhead, dg_forthpickname);
        return;
    }

    if ( ((*pbuflength) % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_datastackmisalignederror);
        dg_pusherror(pBHarrayhead, dg_forthpickname);
        return;
    }

    numberonstack = (*pbuflength) / sizeof(UINT64);

    if (numberonstack < 1)
    {
        dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthpickname);
        return;
    }

    numberonstack--;

    // this check is needed so calculation below doesn't overflow
    if (numberonstack < 1) 
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthpickname);
        return;
    }

    idx = ((UINT64*)pdatastack)[numberonstack];

    if (idx > (numberonstack - 1)) 
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthpickname);
        return;
    }

    ((UINT64*)pdatastack)[numberonstack] = ((UINT64*)pdatastack)[(numberonstack - 1) - idx];
}


void dg_forthroll (Bufferhandle* pBHarrayhead)      
//     ( nu nu-1 ... n2 n1 n0 u -- nu-1 ... n2 n1 n0 nu )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    UINT64 u;
    UINT64 nu;
    UINT64 i;
    

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthrollname);
        return;
    }

    if (*pbuflength < sizeof(UINT64) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrollname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - sizeof(UINT64));
    
    u = pints[0];
    
    // making 0 ROLL not an error when technically there should be at least 1 on the stack
    if (u > 0)
    {
        if (*pbuflength < ((u+2) * sizeof(UINT64)) )
        {
            dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
            dg_pusherror(pBHarrayhead, dg_forthrollname);
            return;
        }
    
        pints = (UINT64*)(pdatastack + *pbuflength - ((u+2)*sizeof(UINT64)));

        nu = pints[0];
    
        for (i = 0; i < u; i++)
        {
            pints[i] = pints[i+1];
        }
    
        pints[u] = nu;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthscreate (Bufferhandle* pBHarrayhead)
//     ( c-addr u --  )
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    namelength = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscreatename);
        return;
    }

    pname = (unsigned char*)dg_popdatastack(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscreatename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthscreatename);
        return;
    }

    dg_createvariabledef(
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthscreatename);
        return;
    }
}


void dg_forthtib (Bufferhandle* pBHarrayhead)
// ( -- a-addr )
{
    unsigned char* pcib;
    UINT64* pciblength;

    UINT64 cibid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtibname);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtibname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pcib);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthtibname);
        return;
    }
}

// TRUE defined as a UINT64 constant

void dg_forthtuck (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_forthswap (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtuckname);
        return;
    }
    
    dg_forthover(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtuckname);
        return;
    }
}


void dg_forthugreaterthan (Bufferhandle* pBHarrayhead)     
//     ( u1 u2 -- flag )
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
        dg_pusherror(pBHarrayhead, dg_forthugreaterthanname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthugreaterthanname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));

    if (pints[0] > pints[1])
    {
        pints[0] = FORTH_TRUE;
    }
    else
    {
        pints[0] = FORTH_FALSE;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}


void dg_forthlinecomment (Bufferhandle* pBHarrayhead)
//              ( "string<char>morestuff" -currentinputbuffer- "morestuff" )
//              ( char -- addr length )
{
    // unsigned char* pcib = NULL;
    // UINT64* pciblength = NULL;
    // UINT64* pcibcurrentoffset = NULL;

    // UINT64 cibid = 0;

    // unsigned char c = 0;
    UINT64 linelength;


    Bufferhandle* pBH = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    dg_parse(
        pBHarrayhead,
        &linelength,
        '\n'); // this or a character that can't be in the line...
               //  dg_parse also checks for all line terminators in addition to the endchar

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinecommentname);
        return;
    }


/*
    cibid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinecommentname);
        return;
    }

    pcib = dg_getpbuffer(
        pBHarrayhead,
        cibid,
        &pciblength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlinecommentname);
        return;
    }

    // because dg_getpbuffer worked, I know the buf header for pcib is there
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[cibid] );
    pcibcurrentoffset = &pBH->currentoffset;


    while(*pcibcurrentoffset < *pciblength)
    {
        c = *(pcib + (*pcibcurrentoffset)); 

        if (FORTH_TRUE==dg_islineterminator(c))
        {        
            (*pcibcurrentoffset)++; // to get off end character - dont want to include end character in string
            break;
        }

        (*pcibcurrentoffset)++;
    }
*/
}


void dg_forthudmslashmod (Bufferhandle* pBHarrayhead)
//     ( ud u1 -- ud2 rem )
{
    UINT64* pbuflength;         // -0x08
    unsigned char* pdatastack;  // -0x10
    UINT64* pints;              // -0x18

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


UINT64 dg_checkloopdonenoinc (Bufferhandle* pBHarrayhead)
//       ( index limit -r- index limit | index limit )
{
    unsigned char* prstack;
    UINT64* prstacklength;
    UINT64* pints;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (FORTH_TRUE);
    }

    prstack = dg_getpbuffer(
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        &prstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_checkloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    if (*prstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_rstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_checkloopdonename);
        return (FORTH_TRUE); // on error abort loop
    }

    pints = (UINT64*)(prstack + *prstacklength - (2 * sizeof(UINT64)));

    // if 0 < limit - index <= loopstep, loop is finished
    if (pints[1] == pints[0])
    {
        // *prstacklength -= 2* sizeof(UINT64); // doing unloop
        return (FORTH_TRUE);
    }
    
    return (FORTH_FALSE);
}


void dg_forthquerydo (Bufferhandle* pBHarrayhead)
//     ( -- do-sys )
// Compiles code that does ( index limit -- ) ( -r- limit index )
{
    UINT64 afterbranchoffset;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_forthtor));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }

    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_forthtor));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }

    // compile compare with 0...
    // compile branchne over leave
    // leave
    dg_compilecallcore(
        pBHarrayhead,
        (UINT64)(&dg_checkloopdonenoinc));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_checkplusloopdonename);
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }
    
    dg_compilecompare(
        pBHarrayhead,
        FORTH_FALSE);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }
    
    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_NOTEQUAL);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LEAVESTACK_BUFFERID,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthleavebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }
    
    dg_forthbegin(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerydoname);
        return;
    }
    
    // note: the afterbranchoffset is equal to the begin offset
    //  which is why the leave is considered part of this ?do loop
}


// This word does not return caddr u in the execute state like OS" because if it did,
//   the caddr pointer would become invalid the next time anything else is compiled
void dg_forthsbackslashquotes (Bufferhandle* pBHarrayhead) // ( S\" )
//           ( "somestuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
//           ( compiletime: -- )
//           ( runtime: -- caddr u  )
{
    unsigned char* psqstr;
    UINT64 sqstrlen;
    UINT64 topstringid;

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
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }

    dg_stonewstring(
        pBHarrayhead,
        psqstr,
        sqstrlen);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }

    dg_fescdecodelstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }

    topstringid = dg_getnumberoflstringsonstack(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }

    psqstr = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        topstringid - 1,
        &sqstrlen);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }

    dg_compileacopyofsscopyto(
        pBHarrayhead,
        psqstr,
        sqstrlen);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsbackslashquotesname);
        return;
    }
}


