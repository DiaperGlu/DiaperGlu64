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

  
#include "../diapergluforth.h"

const UINT64 dg_localsregs[] = { 
  dg_r8, dg_r9, dg_r10, dg_r11, dg_r12, dg_r13, dg_r14, dg_r15, 
  dg_rax, dg_rcx, dg_rdx, dg_rbx, dg_rsp, dg_rbp, dg_rsi, dg_rdi,
  dg_xmm0, dg_xmm1, dg_xmm2, dg_xmm3, dg_xmm4, dg_xmm5, dg_xmm6, dg_xmm7,
  dg_xmm8, dg_xmm9, dg_xmm10, dg_xmm11, dg_xmm12, dg_xmm13, dg_xmm14, dg_xmm15  
};

const UINT64 dg_paramintregs[] = {
    dg_rcx,
    dg_rdx,
    dg_r8,
    dg_r9
};

const UINT64 dg_paramfloatregs[] = {
    dg_xmm0,
    dg_xmm1,
    dg_xmm2,
    dg_xmm3
};

const UINT64 dg_paramintregslocalsindex[] = {
    dg_localsrcxindex,
    dg_localsrdxindex,
    dg_localsr8index,
    dg_localsr9index
};

const UINT64 dg_paramfloatregslocalsindex[] = {
    dg_localsxmm0index,
    dg_localsxmm1index,
    dg_localsxmm2index,
    dg_localsxmm3index
};

// RBX, RBP, RDI, RSI, RSP, R12, R13, R14, R15, and XMM6-XMM15 must be preserved.

const unsigned char dg_localsintregallocationorder[] = {
    dg_localsr11index,
    dg_localsr10index,
    dg_localsr9index,
    dg_localsr8index,
    dg_localsrdxindex,
    dg_localsrcxindex,
    dg_localsrdiindex,
    dg_localsrsiindex,
    dg_localsrbxindex,
    dg_localsr15index,
    dg_localsr14index,
    dg_localsr13index,
    dg_localsr12index
};


const unsigned char dg_localsfloatregallocationorder[] = {
    dg_localsxmm2index,
    dg_localsxmm3index,
    dg_localsxmm4index,
    dg_localsxmm5index,
    dg_localsxmm1index,
    dg_localsxmm0index,
    dg_localsxmm6index,
    dg_localsxmm7index,
    dg_localsxmm8index,
    dg_localsxmm9index,
    dg_localsxmm10index,
    dg_localsxmm11index,
    dg_localsxmm12index,
    dg_localsxmm13index,
    dg_localsxmm14index,
    dg_localsxmm15index
};

// +00 saved rbp
// -08 saved flags
// -10 pBHarrayhead (RDI)
// -18 old error count
// -20 end of locals (change this to mark where subroutine's return stack stuff is)

// -28 RAX
// -30 safe return offset
// -38 safe return bufferid
// -40 jump buffer address (pBHarrayhead + sizeof(Bufferhandle))

void dg_compileinitlocals (Bufferhandle* pBHarrayhead)
{
    // this is ridiculously complicated
    unsigned char pbuf[24] = "\x55\x48\x8B\xEC\x9C\x9C\x48\x81\x65\xF0\xFF\xFF\xFB\xFF\x9D\x51\xFF\x31\x51\x48\x89\x65\xE0";
    // unsigned char pbuf[14] =    "\x55\x48\x8B\xEC\x9C\x57\xFF\x37\x57\x48\x89\x65\xE0";
    // unsigned char pbuf[6] = "\x55\x48\x8B\xEC\x9C";

    UINT64 currentcompilebufferid;
    UINT64 currentcompilebufferlength;
    
    // rcx = pBHarrayhead
    
    // pushq rbp;            0x55             (0x50+rd)
    // movq rbp<-rsp;       ( 0x48 ) 0x8B 0xEC   (0x8B /r)  r/m32 -> r32 = 11 101 100
    
    // pushfq                0x9C
    
    // this clears the alignment check flag which disables exceptions 
    //  which can happen if an unaligned memory access occurs
    // pushfq                0x9C
    // andq [rbp-0x10]<-[rbp-0x10]&$^(0x0000000000040000)  // clear aligment check flag
    //                       0x48 0x81 0x65 0xF0 0xFF 0xFF 0xFB 0xFF    (0x81 /4) // 01 100 101
    // popfq                 0x9D
    
    // pushq pBHarrayhead
    //  pushq rcx            0x51 // 0x57             (0x50+rd)  // push rdi on mac
    // pushq old error count
    //  pushq [rcx]          0xFF 0x31 // 0xFF 0x37        (0xff /6) (error count) // 00 110 111  push [rdi] on mac
    // pushq rcx             0x51 // 0x57             // for end of locals variable // push rcx on mac although it doesn't matter
    
    
    // rsp holds end of locals, this is used during alignment code calculations for subroutine calls
    // movq rsp->[rbp-0x20]  0x48 0x89 0x65 0xE0

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_compilesegment (
        pBHarrayhead,
        (const char*)pbuf,
        23);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompileentername);
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonreturnstackdepth,
        4); // for -0x20

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompileentername);
    }
}


const char dg_pushhctwotobuffername[] = "dg_pushhctwotobuffer";

void dg_pushhctwotobuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64* pud) // really UINT128*
{
    UINT64 hclength;
    unsigned char* pbuffer;
    UINT64 oldbufferlength;
    UINT64* pnewbufferlength;
    const char* perror;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    if (DG_ERRORSTACK_BUFFERID == bufferid)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }

    hclength = dg_gethctwolength(pud);

    oldbufferlength = dg_growbuffer(
        pBHarrayhead,
        bufferid,
        hclength,  // in bytes
        &perror,
        FORTH_FALSE);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }

    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pnewbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }

    perror = dg_hctwostore(pbuffer + oldbufferlength, pud);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_hctwostorename);
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }
}


void dg_forthfindlibrarysymbol (Bufferhandle* pBHarrayhead)
//    ( libraryhandle -- symboladdress|NULL )
//    ( symbolname$ -$- )
{
    UINT64 libraryhandle;
    
    UINT64 numberofstringsonstack = 0;
    unsigned char* pnametofind = NULL;
    UINT64 nametofindlength = 0;
    const char* flag;
    INT64 compareflag;
    
    UINT64 numberofnames;

    UINT64 j = 0;
    UINT64 namestart = 0;
    UINT64 nameend = 0;

    UINT64 namelength = 0;

    FARPROC procaddress = NULL;

    LPCSTR pname = NULL;

    const char* symboltype;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    libraryhandle = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    numberofstringsonstack = dg_getnumberoflstringsonstack(pBHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    if (numberofstringsonstack < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    dg_forthturnstringinto0string(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    pnametofind = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        numberofstringsonstack - 1,
        &nametofindlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    __try
    {
        procaddress = GetProcAddress(
            (HMODULE)libraryhandle,
            (LPCSTR)pnametofind);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        procaddress = NULL;
    }

    dg_pushdatastack(pBHarrayhead, (UINT64)procaddress);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }
}


void dg_forthcallprocaddress (Bufferhandle* pBHarrayhead)
//                     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
{
    UINT64* address;
    UINT64 n;

    UINT64* plength;
    unsigned char* pbuffer;

    UINT64* pints;

    UINT64 returnvalue;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
        return;
    }

    n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    if (((*plength) / sizeof(UINT64)) < n+2 ) // pretty sure overflow indexing is caught by this
    {
        dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
        return;
    }

    pints = (UINT64*)(pbuffer + *plength - (n+2)*sizeof(UINT64));

    __try  
    {
        // I put this code in a subroutine because VC6.0 doesn't like jumps inside a try block
        //***align16*** in case this function is used to call 64bit dll
        returnvalue = dg_callprocaddress(pints, n, plength, address);

    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        dg_pusherror(pBHarrayhead, dg_osexception);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    // moving drop data stack to out here so we can see the stack frame when there is an error
    //*plength -= (n+2) * sizeof(UINT32);

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
        return;
    }
}



// for linux/freebsd/macosx compatibility
void dg_forthcallprocaddressretuint128 (Bufferhandle* pBHarrayhead)
//                     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvaluelo returnvaluehi )
{
    UINT64* address;
    UINT64 n;

    UINT64* plength;
    unsigned char* pbuffer;

    UINT64* pints;

    UINT64 returnvalue, hireturnvalue;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
        return;
    }

    n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    if (((*plength) / sizeof(UINT64)) < (n+2) ) // pretty sure overflow indexing is caught by this
    {
        dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
        return;
    }

    pints = (UINT64*)(pbuffer + *plength - (n+2)*sizeof(UINT64));

    __try  
    {
        // I put this code in a subroutine because VC6.0 doesn't like jumps inside a try block
        //***align16*** in case this function is used to call 64bit dll
        returnvalue = dg_callprocaddressretuint128(pints, n, plength, address, &hireturnvalue);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        dg_pusherror(pBHarrayhead, dg_osexception);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    // moving drop data stack to out here so we can see the stack frame when there is an error
    //*plength -= (n+2) * sizeof(UINT32);

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, hireturnvalue);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
        return;
    }
}

void dg_forthcalldfpprocaddress(Bufferhandle* pBHarrayhead)
//     ( dfparamn dfparamn-1 ... dfparam1
//       paramn paramn-1 paramn-2 ... param1
//       nfloats n procaddress -- uint64returnvalue dfpreturnvalue )
{
    UINT64* address;
    UINT64 n, nfloats;

    UINT64* plength;
    unsigned char* pbuffer;

    UINT64* pints;

    FLOAT64 result;
    FLOAT64* presult = &result;

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
        dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
        return;
    }

    if (*plength < (3 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
        return;
    }

    nfloats = *((UINT64*)(pbuffer + *plength - (3 * sizeof(UINT64))));
    n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
    address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

    if (((*plength) / sizeof(UINT64)) < (n + nfloats + 3)) // pretty sure overflow indexing is caught by this
    {
        dg_pusherror(pBHarrayhead, dg_dfpprocparamsmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
        return;
    }

    pints = (UINT64*)(pbuffer + *plength - ((n + nfloats + 3) * sizeof(UINT64)));

    result = dg_calldfpprocaddress(
        pints,
        n,
        plength,
        address,
        nfloats);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushdatastack(
        pBHarrayhead,
        *((UINT64*)presult));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
    }
}

/*
void dg_forthcallcppmemberfunction (Bufferhandle* pBHarrayhead)
//     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
//     ( param1 is the object handle )
{
    UINT32* address;
    UINT32 n;

    UINT32* plength;
    unsigned char* pbuffer;

    UINT32* pints;

    UINT32 returnvalue;

    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

    pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
        return;
    }

    if (*plength < 2 * sizeof (UINT32))
    {
        dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
        return;
    }

    n = *((UINT32*)(pbuffer + *plength - (2 * sizeof(UINT32))));
    address = *((UINT32**)(pbuffer + *plength - (sizeof(UINT32))));

    if (((*plength) / sizeof(UINT32)) < n+2 ) // pretty sure overflow indexing is caught by this
    {
        dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
        return;
    }

    if (0 == n) // checking missing object handle case
    {
        dg_pusherror(pBHarrayhead, dg_missingobjecthandleerror);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
        return;
    }

    pints = (UINT32*)(pbuffer + *plength - (n+2)*sizeof(UINT32));

    __try  
    {
        //***align16*** in case this function is used to call 64bit dll
        returnvalue = dg_callcppmemberwin32(pints, n, plength, address);

    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        dg_pusherror(pBHarrayhead, dg_osexception);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
    }

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushbufferdword(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
        return;
    }
}
*/

void dg_forthfixpathstring(Bufferhandle* pBHarrayhead)
//     ( filename$ -$- filename$' )
{
    UINT64 stringstackdepth;

    unsigned char* scriptpath;
    UINT64* pscriptpathlength;

    const char* result;
    unsigned char c = ' ';

    unsigned char* pnamelstring;
    UINT64 namelength;

    UINT64 scanlength;
    UINT64 i = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
        return;
    }

    if (stringstackdepth < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
        return;
    }

    // check to see if in cgi/isapi mode
      // it seems I don't use this

    // if there is a colon in filename string, do not need to fix path
    pnamelstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &namelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
        return;
    }

    scanlength = namelength;

    result = dg_scanforbyte(pnamelstring, &scanlength, ':');

    if (result != dg_success)
    {
        dg_pusherror(pBHarrayhead, result);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
    }

    // if : was found...
    if (scanlength < namelength)
    {
        return;
    }

    // get script file's full path from args buffer
    scriptpath = dg_getpbuffer(pBHarrayhead, DG_ARGS_BUFFERID, &pscriptpathlength);

    // need to scan back from end of string for \
    // then need to push everything from beginning up to and including \ 
    //  to string stack

    i = *pscriptpathlength;

    while (i > 0)
    {
        c = scriptpath[i - 1];

        if ('\\' == c)
        {
            break;
        }

        i--;
    }

    if (i < 1)
    {
        return;
    }

    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        i,
        scriptpath);

    dg_forthswapstring(pBHarrayhead);

    dg_forthcatstring(pBHarrayhead);
}


void dg_forthopenlibrarystring (Bufferhandle* pBHarrayhead)
//                 ( libraryname$ -$- )
//                 ( -openlibraryhandlestack- libraryhandle )
//                 ( -- wordlistid libraryhandle )
{
    UINT64 libraryhandle;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_forthloadlibrarystringsub(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // error is pushed in subroutine
        return;
    }

    libraryhandle = dg_popbufferuint64(pBHarrayhead, DG_LIBHANDLE_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
        return;
    }

    dg_pushbufferuint64(pBHarrayhead, DG_LIBHANDLE_BUFFERID, libraryhandle);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
        return;
    }

    dg_forthwordlist(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
        return;
    }

    dg_pushdatastack(pBHarrayhead, libraryhandle);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
        return;
    }

    // dg_forthdropstring(pBHarrayhead);
    return;
}


void dg_forthrunfileandwait(Bufferhandle* pBHarrayhead)
{
    const char* perror;
    unsigned char* pfilename;
    char** argv;
    char** envp;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pfilename = (unsigned char*)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
        return;
    }

    envp = (char**)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
        return;
    }

    argv = (char**)dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
        return;
    }

    perror = dg_runfileandwait(
        pBHarrayhead,
        pfilename,
        argv,
        envp,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_runfileandwaitname);
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
        return;
    }

    return;
}


void dg_forthrunfileandwaitnoenvstring(Bufferhandle* pBHarrayhead)
{
    const char* perror;
    unsigned char* pstring;
    UINT64 stringlength;
    UINT64 stringstackdepth;
    UINT64 myrsp;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
        return;
    }

    if (stringstackdepth < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
        return;
    }

    dg_forthturnstringinto0string(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
        return;
    }

    // get a pointer to the string
    pstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &stringlength);

    if (stringlength == 0)
    {
        return;
    }

    // myrsp = (UINT64)dg_getretstackpointer();

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"Return stack pointer just before calling a subroutine before dg_runfileandwait = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, myrsp);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    perror = dg_runfileandwait(
        pBHarrayhead,
        pstring,    // pfilename,   really the command line
        NULL,       // argv[],
        NULL,       // envp[],
        dg_success);


    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);
}

void dg_forthrunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
{
    const char* perror;
    const char* pcommandline;
    UINT64 commandlinelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"got there\n");

    // get a pointer to the command line
    pcommandline = (const char*)dg_parse(
        pBHarrayhead,
        &commandlinelength,
        '"');

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
        return;
    }

    if (commandlinelength == 0)
    {
        return;
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"trying command line='");
    // dg_writestdout(pBHarrayhead, (unsigned char*)pcommandline, commandlinelength);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"'\n");

    // copying string to string stack so I can append a null terminator
    dg_stonewstring(
        pBHarrayhead,
        (unsigned char*)pcommandline,
        commandlinelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
        return;
    }

    dg_forthrunfileandwaitnoenvstring(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
        return;
    }
}

void dg_forthdocompiletyperunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
    const char* state;
    const char* pstring;
    UINT64 stringlength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthtwodrop(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
        return;
    }

    state = (const char*)dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        statevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstatename);
        dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
        return;
    }

    if (state == dg_stateexecute)
    {
        dg_forthrunfileandwaitnoenvquotes(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
            return;
        }

    }
    else
    {
        if (state == dg_statecompile)
        {
            // get a pointer to the command line
            pstring = (const char*)dg_parse(
                pBHarrayhead,
                &stringlength,
                '"');

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
                return;
            }

            if (stringlength == 0)
            {
                return;
            }

            dg_compilecopystonewstring(
                pBHarrayhead,
                pstring,
                stringlength);
            
            // I need to compile a call to a function that uses a string on the top of the string stack
            dg_compilecallcore(
                pBHarrayhead,
                (UINT64)(&dg_forthrunfileandwaitnoenvstring));

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
                return;
            }
        }
        else
        {
            // unknown state do nothing
        }
    }
}


const char* dg_callbuffername = "dg_callbuffer";

UINT64 dg_callbuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    // UINT64 myrsp;
    unsigned char* addr;
    UINT64 result = (UINT64)-1;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return(result);
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"got here...\n");

    addr = dg_getpbufferoffset(pBHarrayhead, bufferid, offset);

    if (dg_geterrorcount(pBHarrayhead) == olderrorcount)
    {
        __try
        {
            // myrsp = (UINT64)dg_getretstackpointer();

            // dg_printzerostring(pBHarrayhead, (unsigned char*)"Return stack pointer just before calling a forth buffer routine = ");
            // dg_writestdoutuint64tohex(pBHarrayhead, myrsp);
            // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

            result = dg_callcoreforthroutine(pBHarrayhead, (UINT64)addr);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
           dg_pusherror(pBHarrayhead, dg_osexception);
           dg_pusherror(pBHarrayhead, dg_callbuffername);
        }
    }
    else
    {
        dg_pusherror(pBHarrayhead, dg_callbuffername);
    }

    return(result); // making this function return a value for testing purposes


    // dg_printzerostring(pBHarrayhead, (unsigned char*)"and here...\n");
}


const char dg_pushsymboltowin64coffsymboltablename[] = " dg_pushsymboltowin64coffsymboltable";

void  dg_pushsymboltowin64coffsymboltable(
    Bufferhandle* pBHarrayhead,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    unsigned char* psymbolname,
    UINT64 symbolnamelength,
    DWORD value,
    SHORT sectionnumber,
    WORD type,
    BYTE storageclass,
    BYTE numberofauxsymbols)
{
    const char* perror;
    UINT64 oldoversizebufferlength;

    IMAGE_SYMBOL myimagesymbol;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    if (symbolnamelength > 8)
    {
        oldoversizebufferlength = dg_getbufferlength(
            pBHarrayhead,
            oversizesymbolnamebufferid);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
            return;
        }

        dg_pushbuffersegment(
            pBHarrayhead,
            oversizesymbolnamebufferid,
            symbolnamelength,
            psymbolname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
            return;
        }

        // null terminator
        dg_pushbufferbyte(
            pBHarrayhead,
            oversizesymbolnamebufferid,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
            return;
        }

        myimagesymbol.N.LongName[0] = 0;
        myimagesymbol.N.LongName[1] = oldoversizebufferlength;
    }
    else
    {
        // unused bytes of short name are supposed to be 0 I think
        myimagesymbol.N.LongName[0] = 0;
        myimagesymbol.N.LongName[1] = 0;

        perror = dg_movebytes(
            psymbolname,
            (unsigned char*)myimagesymbol.N.ShortName,
            symbolnamelength);

        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_movebytesname);
            dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
            return;
        }
    }

    myimagesymbol.Value = value;
    myimagesymbol.SectionNumber = sectionnumber;
    myimagesymbol.Type = type;
    myimagesymbol.StorageClass = storageclass;
    myimagesymbol.NumberOfAuxSymbols = numberofauxsymbols;

    dg_pushbuffersegment(
        pBHarrayhead,
        symboltablebufferid,
        sizeof(myimagesymbol),
        (unsigned char*)&myimagesymbol);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
        return;
    }
}

const char dg_pushsectionlengthtowin64coffsymboltablename[] = "dg_pushsectionlengthtowin64coffsymboltable";

void dg_pushsectionlengthtowin64coffsymboltable(
    Bufferhandle * pBHarrayhead,
    UINT64 symboltablebufferid,
    UINT64 sectionlength)
{
    IMAGE_SYMBOL myimagesymbol;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    myimagesymbol.N.LongName[0] = sectionlength;
    myimagesymbol.N.LongName[1] = 0;
    myimagesymbol.Value = 0;
    myimagesymbol.SectionNumber = 0;
    myimagesymbol.Type = 0;
    myimagesymbol.StorageClass = 0;
    myimagesymbol.NumberOfAuxSymbols = 0;

    dg_pushbuffersegment(
        pBHarrayhead,
        symboltablebufferid,
        sizeof(myimagesymbol),
        (unsigned char*)&myimagesymbol);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushsectionlengthtowin64coffsymboltablename);
        return;
    }
}

const char dg_pushexportsymbolstowin64coffbuffersname[] = "dg_pushexportsymbolstowin64coffbuffers";

void dg_pushexportsymbolstowin64coffbuffers(
    Bufferhandle* pBHarrayhead,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    UINT64 dotdrectvebufferid,
    UINT64 dottextsectionnumber)
{
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 value;
    UINT64 storageclass;

    Hlistheader myexportsymbolhlistheader;
    UINT64 exportsymbolsortedkeyslstringlength = 0;
    unsigned char* pexportsymbolsortedkeyslstring;
    UINT64 numberofexportsymbols = 0;

    UINT64 srcchildelementid;
        UINT64 foundflag;
        UINT64 indexofkeyaftermatch;
        UINT64 sortkey;

    UINT64 i;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // need to check for the not using export hlist case
    if (exportsymbollisthlistid == (UINT64)-1)
    {
        return;
    }

    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        exportsymbollisthlistid,
        &myexportsymbolhlistheader,
        sizeof(Hlistheader));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
        return;
    }

    // export symbol list
    pexportsymbolsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myexportsymbolhlistheader.sortedchildidslstroffsetbufid,
        myexportsymbolhlistheader.sortedchildidslstrstringbufid,
        exportsymbollistparentelementid,
        &exportsymbolsortedkeyslstringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
        return;
    }

    if ((exportsymbolsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
        return;
    }

    numberofexportsymbols = exportsymbolsortedkeyslstringlength >> 3;


    //if (0 == numberofexportsymbols)
    //{
    //    return;
    // }

    // calculate length of all export directives
    //  and build export directive string table
    // totallengthofsymbolnames = 0;

    // this goes through children alphabetically
    for (i = 0; i < numberofexportsymbols; i++)
    {
        srcchildelementid = ((UINT64*)pexportsymbolsortedkeyslstring)[i];

                // need to see if element has a child named 'ENTRY'
                foundflag = dg_findsortedhlistchild (
                    pBHarrayhead,
                    (unsigned char*)"ENTRY", // pname
                    5, // namelength,  
                    exportsymbollisthlistid, 
                    srcchildelementid, // parentelementid,      
                    &indexofkeyaftermatch, // index in sort key lstring after match
                    &sortkey); 

        if (foundflag != 0)
        {
            storageclass = 0x02; // is an export symbol

                    // push string onto end of export directives
                    dg_pushbuffersegment(
                        pBHarrayhead,
                        dotdrectvebufferid,
                        8,
                        (unsigned char*)"/EXPORT:");

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
                        return;
                    }
        }
        else
        {
            storageclass = 0x02; // is the entry symbol e.g. main

                    // push string onto end of export directives
                    dg_pushbuffersegment(
                        pBHarrayhead,
                        dotdrectvebufferid,
                        7,
                        (unsigned char*)"/ENTRY:");

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
            }
        }

        // find the child's name in the source hlist
        pname = dg_getshlistelementnom(
            pBHarrayhead,
            exportsymbollisthlistid,
            srcchildelementid,
            &namelength);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        dg_pushbuffersegment(
            pBHarrayhead,
            dotdrectvebufferid,
            namelength,
            pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        dg_pushbuffersegment(
            pBHarrayhead,
            dotdrectvebufferid,
            1,
            (unsigned char*)" ");

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        pvalue = dg_getshlistelementvalue(
            pBHarrayhead,
            exportsymbollisthlistid,
            srcchildelementid,
            &valuelength);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        if (valuelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        value = *((UINT64*)pvalue);

        // could make sure value fits into a UINT32...
        if (value > 0xFFFFFFFF)
        {
            dg_pusherror(pBHarrayhead, dg_toobigfordesterror);
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }

        // totallengthofsymbolnames += namelength;
        dg_pushsymboltowin64coffsymboltable(
            pBHarrayhead,
            symboltablebufferid,
            oversizesymbolnamebufferid,
            pname,
            namelength,
            (DWORD)value,
            dottextsectionnumber,
            0x20, // WORD type,
            storageclass, // BYTE storageclass,
            0);   //  BYTE numberofauxsymbols);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
            return;
        }
    }
}

const char dg_pushimportymbolstowin64coffbuffersname[] = "dg_pushimportsymbolstowin64coffbuffers";

UINT64 dg_pushimportsymbolstowin64coffbuffers(
    Bufferhandle* pBHarrayhead,
    UINT64 importsymbollisthlistid,
    UINT64 importsymbollistparentelementid,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    UINT64 relocationtablebufferid)
{
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 value;

    unsigned char* plastimportname = (unsigned char*)"";
    UINT64 lastimportnamelength = (UINT64)-1;  // making this -1 in case someone defines an empty string
                                               //  as the first import symbol name... so that the empty
                                               //  string will be seen as a new import symbol name

    // UINT64 totallengthofsymbolnames;

    UINT64 i, srcchildelementid;
    UINT64 srcsortedkeyslstringlength;

    Hlistheader myimportsymbolhlistheader;
    UINT64 importsymbolsortedkeyslstringlength = 0;
    unsigned char* pimportsymbolsortedkeyslstring;
    UINT64 numberofrelocationentries = 0;
    UINT64 numberofsymbols = 0;

    INT64 compareflag;

    const char* pError;

    IMAGE_RELOCATION myrelocationarrayelement;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return(numberofrelocationentries);
    }

    // import symbol list
    // need to check for the not using import hlist case
    if (importsymbollisthlistid == (UINT64)-1)
    {
        return(numberofrelocationentries);
    }

    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        importsymbollisthlistid,
        &myimportsymbolhlistheader,
        sizeof(Hlistheader));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
        return(numberofrelocationentries);
    }

    pimportsymbolsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myimportsymbolhlistheader.sortedchildidslstroffsetbufid,
        myimportsymbolhlistheader.sortedchildidslstrstringbufid,
        importsymbollistparentelementid,
        &srcsortedkeyslstringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
        return(numberofrelocationentries);
    }

    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
        return(numberofrelocationentries);
    }

    numberofrelocationentries = srcsortedkeyslstringlength >> 3;

    // it should already be clear, but just in case
    dg_clearbuffer(
        pBHarrayhead,
        relocationtablebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
        return(numberofrelocationentries);
    }

    // this goes through children alphabetically
    //  if numberofimportsymbols is 0, this for loop should not go....
    for (i = 0; i < numberofrelocationentries; i++)
    {
        // if this is a new import symbol name, then this symbol name
        //   needs to get added to the import symbol list

        srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];

        // find the child's name in the source hlist
        pname = dg_getshlistelementnom(
            pBHarrayhead,
            importsymbollisthlistid,
            srcchildelementid,
            &namelength);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
            return(numberofrelocationentries);
        }

        pError = dg_comparebytes(
            (unsigned char*)pname,
            namelength,
            (unsigned char*)plastimportname,
            lastimportnamelength,
            &compareflag);

        // this shouldn't happen
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, dg_comparebytesname);
            dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
            return(numberofrelocationentries);
        }

        // if they don't match then we need to add a symbol to the symbol table
        if (0 != compareflag)
        {
            // we have a new symbol name
            plastimportname = pname;
            lastimportnamelength = namelength;

            dg_pushsymboltowin64coffsymboltable(
                pBHarrayhead,
                symboltablebufferid,
                oversizesymbolnamebufferid,
                pname,
                namelength,
                0, // DWORD value,
                0, // sectionnumber, import symbols have a section number of 0
                0, // WORD type,
                2, // BYTE storageclass,
                0); //  numberofauxsymbols);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
                return(numberofrelocationentries);
            }

            if ((dg_getbufferlength(
                pBHarrayhead,
                symboltablebufferid) % sizeof(IMAGE_SYMBOL)) != 0)
            {
                dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
                dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
                return(numberofrelocationentries);
            }

            numberofsymbols = dg_getbufferlength(
                pBHarrayhead,
                symboltablebufferid) / sizeof(IMAGE_SYMBOL);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
                return(numberofrelocationentries);
            }
        }

        // need to add the relocation entry
        // srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];

        // get the source child element's value. This is the offset in the buffer to be patched.
        pvalue = dg_getshlistelementvalue(
            pBHarrayhead,
            importsymbollisthlistid,
            srcchildelementid,
            &valuelength);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
            return(numberofrelocationentries);
        }

        if (valuelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
            return(numberofrelocationentries);
        }

        value = *((UINT64*)pvalue);

        // could make sure that value fits into an UINT32
        myrelocationarrayelement.VirtualAddress = (DWORD)value;
        myrelocationarrayelement.SymbolTableIndex = numberofsymbols - 1; // 0 based
        myrelocationarrayelement.Type = IMAGE_REL_AMD64_ADDR64; // IMAGE_REL_AMD64_REL32;
        
        // need to push this to a temporary buffer...
        dg_pushbuffersegment(
            pBHarrayhead,
            relocationtablebufferid,
            sizeof(myrelocationarrayelement),
            (unsigned char*)&myrelocationarrayelement);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
            return(numberofrelocationentries);
        }
    }

    return(numberofrelocationentries);
}


const char dg_makedototobufsubname[] = "dg_makedototobufsub";

void dg_makedototobufsub(
    Bufferhandle* pBHarrayhead,
    unsigned char* pcode,
    UINT64 codelength,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 importsymbollisthlistid,
    UINT64 importsymbollistparentelementid,
    UINT64 destbuf,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    UINT64 relocationtablebufferid,
    UINT64 dotdrectvebufferid)
{
    IMAGE_FILE_HEADER myimagefileheader;
    IMAGE_SECTION_HEADER mytextsectionheader;
    IMAGE_SECTION_HEADER mydatasectionheader;
    IMAGE_SECTION_HEADER mydotdrectvesectionheader;
    UINT64 numberofrelocationentries = 0;
    UINT64 dotdrectvelength = 0;
    UINT64 x;
    UINT64 textsectionpadding = 0; // to align to UINT16
    UINT64 dotdrectvesectionpadding = 0; // to align to UINT16

    ULARGE_INTEGER mysecondssince1601jan01;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    textsectionpadding = (codelength % 1);

    // need to make room for the length of the oversize symbol name buffer
    dg_pushbufferuint32(
        pBHarrayhead,
        oversizesymbolnamebufferid,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // need to push the section symbol names along with their lengths...

    // push .text$mn symbol
    dg_pushsymboltowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        (unsigned char*)".text$mn", // pname,
        8,                          // namelength,
        0,                          // (DWORD)value,
        1,                          // dottextsectionnumber,
        0, // WORD type,
        0x03, // BYTE storageclass,
        1);   //  BYTE numberofauxsymbols);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push extra symbol data for text section length
    dg_pushsectionlengthtowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        codelength); // sectionlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push .data symbol
    // push extra symbol data for data section length
    dg_pushsymboltowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        (unsigned char*)".data", // pname,
        5,                          // namelength,
        0,                          // (DWORD)value,
        2,                          // dottextsectionnumber,
        0, // WORD type,
        0x03, // BYTE storageclass,
        1);   //  BYTE numberofauxsymbols);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushsectionlengthtowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        0); // sectionlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push the import symbols
    numberofrelocationentries = dg_pushimportsymbolstowin64coffbuffers(
        pBHarrayhead,
        importsymbollisthlistid,
        importsymbollistparentelementid,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        relocationtablebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push the export symbols
    dg_pushexportsymbolstowin64coffbuffers(
        pBHarrayhead,
        exportsymbollisthlistid,
        exportsymbollistparentelementid,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        dotdrectvebufferid,
        1); //  dottextsectionnumber);

    x = dg_getbufferlength(
        pBHarrayhead,
        dotdrectvebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push .drectve symbol
    // push extra symbol data for .drectve section length
    dg_pushsymboltowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        (unsigned char*)".drectve", // pname,
        8,                          // namelength,
        0,                          // (DWORD)value,
        3,                          // dottextsectionnumber,
        0, // WORD type,
        0x03, // BYTE storageclass,
        1);   //  BYTE numberofauxsymbols);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushsectionlengthtowin64coffsymboltable(
        pBHarrayhead,
        symboltablebufferid,
        x); // sectionlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // set the oversize symbol name buffer length variable
    x = dg_getbufferlength(
        pBHarrayhead,
        oversizesymbolnamebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_putbufferuint32(
        pBHarrayhead,
        oversizesymbolnamebufferid,
        0, //  offset,
        x); // data);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // setting up section header 1
    perror = dg_movebytes(
        (unsigned char*)".text$mn",
        mytextsectionheader.Name,
        8);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // text section is first after section headers
    mytextsectionheader.Misc.PhysicalAddress = 0;
    mytextsectionheader.VirtualAddress = 0;
    mytextsectionheader.SizeOfRawData = codelength;
    mytextsectionheader.PointerToRawData = sizeof(IMAGE_FILE_HEADER) + (3 * sizeof(IMAGE_SECTION_HEADER)); // fileheadersize + 3 * sectionheader size
    mytextsectionheader.PointerToRelocations = mytextsectionheader.PointerToRawData + codelength + textsectionpadding; // aligning to 2 byte boundary because that's what ML64.exe does
    mytextsectionheader.NumberOfRelocations = numberofrelocationentries;
    mytextsectionheader.NumberOfLinenumbers = 0;
    mytextsectionheader.Characteristics = 0x60500020;

    // setting up section header 2
    perror = dg_movebytes(
        (unsigned char*)".data\0\0\0",
        mydatasectionheader.Name,
        8);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // text relocations are next

    mydatasectionheader.Misc.PhysicalAddress = 0;
    mydatasectionheader.VirtualAddress = 0;
    mydatasectionheader.SizeOfRawData = 0;
    mydatasectionheader.PointerToRawData = 0;  
    mydatasectionheader.PointerToRelocations = 0; 
    mydatasectionheader.NumberOfRelocations = 0;
    mydatasectionheader.NumberOfLinenumbers = 0;
    mydatasectionheader.Characteristics = 0xC0500040;

    // there is no data section

    // setting up section header 3
    // .drectve section is next
    dotdrectvelength = dg_getbufferlength(
        pBHarrayhead,
        dotdrectvebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dotdrectvesectionpadding = dotdrectvelength % 1;

    perror = dg_movebytes(
        (unsigned char*)".drectve",
        mydotdrectvesectionheader.Name,
        8);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    mydotdrectvesectionheader.Misc.PhysicalAddress = 0;
    mydotdrectvesectionheader.VirtualAddress = 0;
    mydotdrectvesectionheader.SizeOfRawData = dotdrectvelength;
    mydotdrectvesectionheader.PointerToRawData = mytextsectionheader.PointerToRelocations + (numberofrelocationentries * sizeof(IMAGE_RELOCATION)); // probaby need to align this to an even byte
    mydotdrectvesectionheader.PointerToRelocations = 0;
    mydotdrectvesectionheader.NumberOfRelocations = 0;
    mydotdrectvesectionheader.NumberOfLinenumbers = 0;
    mydotdrectvesectionheader.Characteristics = 0xA00;

    x = dg_getbufferlength(
        pBHarrayhead,
        symboltablebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    if ((x % IMAGE_SIZEOF_SYMBOL) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    mysecondssince1601jan01.QuadPart = dg_getmicrosecondssince1970Jan01() / 1000000;

    // soo do we have to worry about mysecondssince1601jan01 not fitting into a 32 bit integer in about 80 years?
    
    // setting up the file header
    myimagefileheader.Machine = IMAGE_FILE_MACHINE_AMD64; // 0x8664
    myimagefileheader.NumberOfSections = 3;
    myimagefileheader.TimeDateStamp = mysecondssince1601jan01.LowPart;
    myimagefileheader.PointerToSymbolTable = mydotdrectvesectionheader.PointerToRawData + dotdrectvelength + dotdrectvesectionpadding; // aligning to 2 byte boundary
    myimagefileheader.NumberOfSymbols = x / IMAGE_SIZEOF_SYMBOL; // total number of entries in table, not just the symbols
    myimagefileheader.SizeOfOptionalHeader = 0;
    myimagefileheader.Characteristics = 0;

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        sizeof(IMAGE_FILE_HEADER),
        (unsigned char*)&myimagefileheader);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        sizeof(IMAGE_SECTION_HEADER),
        (unsigned char*)&mytextsectionheader);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        sizeof(IMAGE_SECTION_HEADER),
        (unsigned char*)&mydatasectionheader);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        sizeof(IMAGE_SECTION_HEADER),
        (unsigned char*)&mydotdrectvesectionheader);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        codelength,
        pcode);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    if (textsectionpadding != 0)
    {
        dg_pushbufferbyte(
            pBHarrayhead,
            destbuf,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }

    // push relocation buffer to destbuf
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        relocationtablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        *pbufferlength,
        pbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // there is no data section to push
    
    // push dotdrectve buffer to destbuf
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        dotdrectvebufferid,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        *pbufferlength,
        pbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    if (dotdrectvesectionpadding != 0)
    {
        dg_pushbufferbyte(
            pBHarrayhead,
            destbuf,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }

    // push symbol table buffer to destbuf
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        *pbufferlength,
        pbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // push oversize symbol name buffer to destbuf
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        oversizesymbolnamebufferid,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment(
        pBHarrayhead,
        destbuf,
        *pbufferlength,
        pbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
}


// looks like Windows no longer requires the .drectve buffer, but it still works if you leave it in
//  J.N. 2022 May 22
const char dg_makedototobufname[] = "dg_makedototobuf";

void dg_makedototobuf(
    Bufferhandle* pBHarrayhead,
    unsigned char* pcode,
    UINT64 codelength,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 importsymbollisthlistid,          // largestunsignedint means not using imports
    UINT64 importsymbollistparentelementid,
    UINT64 destbufid)
{
    const char* pError;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    UINT64 symboltablebufferid;
    UINT64 oversizesymbolnamebufferid;
    UINT64 relocationtablebufferid;
    UINT64 dotdrectvebufferid;

    symboltablebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        return;
    }

    oversizesymbolnamebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )

    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, symboltablebufferid);

        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        return;
    }

    relocationtablebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )

    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, symboltablebufferid);
        dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);

        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        return;
    }

    dotdrectvebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )

    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, symboltablebufferid);
        dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);
        dg_freebuffer(pBHarrayhead, relocationtablebufferid);

        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        return;
    }

    dg_makedototobufsub(
        pBHarrayhead,
        pcode,
        codelength,
        exportsymbollisthlistid,
        exportsymbollistparentelementid,
        importsymbollisthlistid,
        importsymbollistparentelementid,
        destbufid,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        relocationtablebufferid,
        dotdrectvebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        // not returning here on purpose so the buffers will be freed
    }

    // if the buffer wasn't allocated, the id should be dg_badbufferid
      // dg_freebuffer will not give an error or try to free dg_badbufferid
    dg_freebuffer(pBHarrayhead, symboltablebufferid);
    dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);
    dg_freebuffer(pBHarrayhead, relocationtablebufferid);
    dg_freebuffer(pBHarrayhead, dotdrectvebufferid);
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* lpECB)
{
    Bufferhandle* pBHarrayhead = NULL;
    char strStatus[20] = "200 OK\r\n\r\n";
    char strMoreStatus[20] = "";
    char strHeader[1] = "";

    HSE_SEND_HEADER_EX_INFO myhsesendheaderexinfo;

    BOOL flag = true;;
    UINT32 errorcode;
    UINT32 gotexception = FORTH_FALSE;

    UINT64 hfile;
    // const char* perror;

    // ::MessageBeep(0xFFFFFFFF);

    pBHarrayhead = dg_init(0, (char**)-1);

    if (badbufferhandle == (void*)pBHarrayhead)
    {
        return(HSE_STATUS_ERROR);
    }

    pBHarrayhead->pisapiecb = lpECB;

    // Apache doesn't use PATH_TRANSLATED so you can't assume 
      // lpszPathTranslated will always be there. (found this one out the hard way)
      // actually, it's supposed to be there... looked in Apache source code
      // for some reason Apache is not initializing correctly in the latest version
      // I have. 6/27/2013

    dg_clearbuffer(pBHarrayhead, DG_ARGS_BUFFERID);

    if (0 != lpECB->lpszPathTranslated)
    {
        dg_push0stringtobuffersegment(
            pBHarrayhead,
            DG_ARGS_BUFFERID,
            (unsigned char*)lpECB->lpszPathTranslated);

        // error count should be 0 here since we just started
        if (dg_geterrorcount(pBHarrayhead) != 0)
        {
            return(HSE_STATUS_ERROR);
        }
    }

    // dg_openfileforwritenew((const char*)"c:\\Users\\thain\\desktop\\gothere.txt", &hfile, dg_success);
    // dg_writefile(pBHarrayhead, hfile, (unsigned char*)"got here", 8, dg_success);
    // dg_closefile(hfile, dg_success);

        // Send HTTP headers back to the client
        // Windows will send a default header unless you call this function with a pointer to a header string
        //  an empty string works.
        // The default header is a problem because in CGI mode a default header is not sent so
        //  the scripts would have to be different for ISAPI and CGI if this function call were not here.
        // Still sending the response "200 OK" because that is sent in CGI mode.

        //***align16here***
        // flag = lpECB->ServerSupportFunction(
        //  lpECB->ConnID,
        //  HSE_REQ_SEND_RESPONSE_HEADER,
        //  (char*)strStatus,
        //  0,
        //  NULL);

    if (0 == lpECB->ServerSupportFunction)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<html><head></head><body>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<p>The server's ServerSupportFunction is missing! Diaperglu needs this function so that you can use the same scripts in CGI and ISAPI mode.</p>");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

        dg_cleanup(pBHarrayhead);
    }

    gotexception = FORTH_FALSE;

    myhsesendheaderexinfo.pszStatus = strStatus;
    myhsesendheaderexinfo.pszHeader = strHeader;
    myhsesendheaderexinfo.cchStatus = 7;
    myhsesendheaderexinfo.cchHeader = 0;
    myhsesendheaderexinfo.fKeepConn = false;


    __try
    {
        // flag = dg_callprocaddressalign16(
        //    (UINT32*)(lpECB->ServerSupportFunction), // apparently & not required
        //    5,
        //    lpECB->ConnID,
        //    HSE_REQ_SEND_RESPONSE_HEADER,
        //    strStatus,
        //    7, // length of strStatus including null terminator, supposedly not used
        //    strMoreStatus); // required for Apache to work I think

        lpECB->ServerSupportFunction(
            lpECB->ConnID,
            HSE_REQ_SEND_RESPONSE_HEADER,
            (LPDWORD)strStatus,
            NULL, 
            (LPDWORD)strMoreStatus);

        // lpECB->ServerSupportFunction(
        //    lpECB->ConnID,
        //    HSE_REQ_SEND_RESPONSE_HEADER_EX,
        //    &myhsesendheaderexinfo,
        //    0, 
        //    NULL);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        gotexception = FORTH_TRUE;
    }

    if (gotexception != FORTH_FALSE)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<html><head></head><body>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<p>Got an exception trying to call the server's ServerSupportFunction with the code to send the response header.</p>");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

        dg_cleanup(pBHarrayhead);
    }

    if (false == flag)
    {
        errorcode = ::GetLastError();

        // could not send response header
          // something is really wrong with the server
          // sending error page
        dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<html><head></head><body>");
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"<p>Got an error trying to call the server's ServerSupportFunction with the code to send the response header.</p>");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

        dg_cleanup(pBHarrayhead);

        return (HSE_STATUS_ERROR);
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>test2<br>");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>path =");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszPathTranslated);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>url =");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszQueryString);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>method =");
    // dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszMethod);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

    dg_forthquit(pBHarrayhead);

    dg_cleanup(pBHarrayhead);

    return(HSE_STATUS_SUCCESS);
}


// on win64 and mac os x for x86 you need to align the stack to a 16 byte boundary before calling any gcc compiled code or
//   any operating system or 3rd party library function due to the strong possibility the called routine will
//   use the new x86 instructions requiring 16 byte alignment

// stack pointer from before aligment already saved in subroutine frame
// so to call a subroutine requiring aligment you do:
//   align stack for number of parameters you are going to push
//   push parameters for subroutine
//     stack should now be 16 byte aligned
//   call subroutine
//   (drop parameters from subroutine not needed because undoing alignment will drop them)
//   undo aligment using saved stack pointer in subroutine frame
//
// (esp - (n*4) - x)&0x0f = 0 // n = number of parameters, x = alignment in bytes
// (esp - (n*4))&0x0f = x     // assuming & is distributive, which it is, just choosing which bits

// movl esp -> eax
// subl eax - (4*n)&(0x0f) -> eax   // use signed or unsigned 8 bit because 0 < (4*(n+1))&(0x0f) < 0x10
// andl eax & 0x0f -> eax               // use signed or unsigned 8 bit because 0 < x < 0x10
// subl esp - eax -> esp                // 

// what if I put how many bytes I'm subtracting or adding onto the frame?
//   If you know where you currently are...
//   If we know how much local storage has been allocated then we can use just subl,
//    but if we don't we have to do what we have below...

// this alignment code does not affect any registers except the return stack pointer of course
//  it affects flags at this time
// this aligment code allows for local variable space to be added to the return stack at run time
//  just push to return stack or subtract from esp and then and movl esp -> [ebp -0x30]

const char* dg_compilealignretstackname = "dg_compilealignretstack";

void dg_compilealignretstack(
    Bufferhandle* pBHarrayhead,
    UINT64 numberofparameters)
{
    // movq  [rbp-0x20] -> rsp                0x48 0x8B 0x65 0xE0  // seems rex is needed
    // andq  rsp & 0xfffffffffffffff0 -> rsp  0x48 0x83 0xE4 0xF0
    // subq  rsp - 0x0n -> rsp                0x48 0x83 0xEC 0x00
    unsigned char mycode[13] = "\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08";
    
    UINT64 length = 8;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (numberofparameters > 4)
    {
        if ((numberofparameters & 1) == 1)
        {
            length = 12;
        }
    }
    
    dg_compilesegment (
        pBHarrayhead,
        (const char*)mycode,
        length);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilealignretstackname);
    }
}


const char* dg_subparamsnotbalanced = " - parameters not balanced. If before function call, need one >IPARAM or >FPARAM or >IFPARAM or P>IPARAM after each parameter. If after function call, need one IPARAM> or FPARAM> before each parameter.";

// const char dg_forthendsubparamscommaname[] = ")),";

void dg_forthendsubparamscomma(Bufferhandle* pBHarrayhead)
{
    UINT64 numberofintparameters;
    UINT64 numberoffloatparameters;
    UINT64 numberofparametersonstack;

    UINT64 i = 0;
    UINT64 x;

    UINT64 numberofparameters;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // could check for misaligned datastack here

    numberofintparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_callsubnumberofints);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }

    numberoffloatparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_callsubnumberoffloats);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }

    if (numberoffloatparameters > (largestunsignedint - numberofintparameters))
    {
        // calculation would overflow
        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }

    numberofparameters = numberofintparameters + numberoffloatparameters;

    dg_compilealignretstack(
        pBHarrayhead,
        numberofparameters);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }

    numberofparametersonstack = 4;

    if
    (
        (numberofparameters) > (sizeof(intparameterslookuptable) / sizeof(UINT64))
    )
    {
        numberofparametersonstack = 4 + // adding 4 for shadow regs
            (numberofparameters) - (sizeof(intparameterslookuptable) / sizeof(UINT64));
    }

    // compile room for parameters on stack
 
    if (numberofparametersonstack != 0)  // will always be doing this on Windows
    {
        if (numberofparametersonstack > (largestsignedint / sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_invalidparametererror);
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }

        dg_compilesubnfromrsp(
            pBHarrayhead,
            numberofparametersonstack * sizeof(UINT64));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }
    }

    i = numberofparameters;

    while (i > 0)
    {
        if (0 == i)
        {
            dg_pusherror(pBHarrayhead, dg_invalidparametererror);
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }

        // predecrement
        i--;

        // data stack doesn't move, but BHarray does... so the length pointer
        //  might become invalid
        x = dg_popdatastack(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }

        // the top number on the stack should be one of >IPARAM >FPARAM IPARAM> FPARAM>
        switch (x)
        {
            
            case dg_istointsubparam:

                if (i < (sizeof(intparameterslookuptable) / sizeof(UINT64)))
                {
                    // it's in a register
                    dg_pushdatastack(
                        pBHarrayhead,
                        intparameterslookuptable[i]);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthmovcomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }
                else
                {

                    dg_pushdatastack(pBHarrayhead, dg_rsp);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_pushdatastack(
                        pBHarrayhead,
                        ((i+ 4) - (sizeof(intparameterslookuptable) / sizeof(UINT64))) * sizeof(UINT64)
                    );

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthbracketrplusd(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    // dg_forthdots(pBHarrayhead);

                    dg_forthmovcomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }

                break;

            case dg_isptointsubparam: 

                if (i < (sizeof(intparameterslookuptable) / sizeof(UINT64)))
                {
                    // it's in a register
                    dg_pushdatastack(
                        pBHarrayhead,
                        intparameterslookuptable[i]);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthleacomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }
                else
                {

                    dg_pushdatastack(pBHarrayhead, dg_rsp);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_pushdatastack(
                        pBHarrayhead,
                        ((i+ 4) - (sizeof(intparameterslookuptable) / sizeof(UINT64))) * sizeof(UINT64)
                    );

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthbracketrplusd(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    // dg_forthdots(pBHarrayhead);

                    dg_forthleacomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }

                break;


            case dg_istofloatsubparam:

                if (i < (sizeof(floatparameterslookuptable) / sizeof(UINT64)) )
                {
                    dg_pushdatastack(
                        pBHarrayhead,
                        floatparameterslookuptable[i]);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthmovqcomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }
                else
                {
            
                    dg_pushdatastack(pBHarrayhead, dg_rsp);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_pushdatastack(
                        pBHarrayhead,
                        ((i + 4) - (sizeof(intparameterslookuptable) / sizeof(UINT64))) * sizeof(UINT64)
                    );

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    dg_forthbracketrplusd(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }

                    // dg_forthdots(pBHarrayhead);

                    // xmm or m to xmm... sooo not movq2... want movq
                    dg_forthmovqcomma(pBHarrayhead);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }

                break;

        case dg_istointfloatsubparam:

            if (i < (sizeof(intparameterslookuptable) / sizeof(UINT64)))
            {
        
                dg_pushdatastack(
                    pBHarrayhead,
                    floatparameterslookuptable[i]);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
 
                dg_forthmovqcomma(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                // now need to compile mov from float param to int param
                dg_pushdatastack(
                    pBHarrayhead,
                    floatparameterslookuptable[i]);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
                
                dg_pushdatastack(
                    pBHarrayhead,
                    intparameterslookuptable[i]);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_forthmovq2comma(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
            }
            else
            {
                dg_pushdatastack(pBHarrayhead, dg_rsp);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_pushdatastack(
                    pBHarrayhead,
                    (sizeof(UINT64) *
                        (
                            numberofparametersonstack +
                            ((i+ 4) - (sizeof(floatparameterslookuptable) / sizeof(UINT64)))
                            // not checking for overflow
                            )
                        )
                );

                // dg_printzerostring(pBHarrayhead, (unsigned char*)" - displacement = ");
                // dg_writestdoutuint64tohex(pBHarrayhead, ( sizeof(UINT64) *
                //        (
                //            ( whichfloatparameter  - (sizeof(floatparameterslookuptable)/sizeof(UINT64)) )
                //            + numberofintparametersonstack // not checking for overflow
                //        ) 
                //    ));
                // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_forthbracketrplusd(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_forthmovqcomma(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
            }

            break;

        case dg_isfromintsubparam:

            if (i < (sizeof(intreturnparameterstable) / sizeof(UINT64)))
            {
                // it's an int register
                dg_pushdatastack(
                    pBHarrayhead,
                    intreturnparameterstable[i]);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_pushdatastack(
                    pBHarrayhead,
                    dg_isreverse);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_forthmovcomma(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
            }
            else
            {
                // only two int return parameters are specified
                dg_pusherror(pBHarrayhead, (const char*)"too many integer return parameters (only two are allowed on mac, one on win)");
                dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                return;
            }

            break;

        case dg_isfromfloatsubparam:

            if (i < (sizeof(floatparameterslookuptable) / sizeof(UINT64)))
            {
                dg_pushdatastack(
                    pBHarrayhead,
                    floatparameterslookuptable[i]);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_pushdatastack(
                    pBHarrayhead,
                    dg_isreverse);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }

                dg_forthmovqcomma(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
            }
            else
            {
                // only two float return parameters are specified, but I'll allow 8
                dg_pusherror(pBHarrayhead, (const char*)"too many float return parameters (mac allows 2, win 1... but I allow 8 on mac 4 on win");
                dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                return;
            }

            break;

        default:

            dg_pusherror(pBHarrayhead, (const char*)" - expected an >IPARAM or >FPARAM or >IFPARAM or IPARAM> or FPARAM> marker on top of the data stack for each parameter. Anything else is an error.");
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);

            return;
        }
    }

    // next on the stack should be the marker
    i = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }

    if (i != dg_subparamscommamarker)
    {
        dg_pusherror(pBHarrayhead, dg_subparamsnotbalanced);
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }
}


const char dg_forthshadowcommaname[] = "dg_forthshadowcomma";

void dg_forthshadowcomma (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // for the 4 Win64 shadow regs
    dg_compilesubn8fromrsp(
        pBHarrayhead,
        0x20);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshadowcommaname);
        return;
    }
}


const char* dg_compilentoparametername = "dg_compilentoparameter";

void dg_compilentoparameter (
    Bufferhandle* pBHarrayhead,
    UINT64 n,
    UINT64 parameter) // 0 based, 0 = first parameter
{
    UINT64 regparametertable[4] =
    {
        dg_rcx, // dg_rdi,
        dg_rdx, // dg_rsi,
        dg_r8,  // dg_rdx,
        dg_r9,  // dg_rcx,
        // dg_r8,
        // dg_r9
    };
    
    if (parameter < 4)
    {
        dg_compilemovntoreg(
            pBHarrayhead,
            n,
            regparametertable[parameter]);
        
        return;
    }
    
    dg_compilepushntoret(
        pBHarrayhead,
        n);
}


void dg_forthcompilesafecallbuffer (Bufferhandle* pBHarrayhead)
//     ( bufferoffset bufferid -- )
{
    UINT64* pbuflength;
    unsigned char* pdatastack;
    
    UINT64* pints;
    
    UINT64 compilebufid;
    
    UINT64 ccbuflength;
    UINT64 finalccbuflength;
    
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);
    
    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    // could check for misaligned data stack here
    
    pints = (UINT64*)(pdatastack + *pbuflength - (2 * sizeof(UINT64)));
    
    compilebufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcompilebuffername);
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    // safe call to forth routine
//  rcx <- pBHarrayhead    0x48 0x8B 0x7D 0xF0
//  push return offset (don't know it yet...)
//  push return bufferid
//  rsp <- rsp - 20   // for shadow regs
//  push address of jump buffer (this is where forth routine returns)
//  r8 <- target offset
//  rdx <- target bufferid
//  rax <- &getpbufferoffset
//  jmp rax OR do the RIP [R] JMP, thing

    dg_compilealignretstack(
        pBHarrayhead,
        6);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }

    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        compilebufid);

    // push offset
    dg_compilemovntorax ( // "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        0); // return offset
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);  // return offset
    
    // push bufferid
    dg_compilemovntorax ( // "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        compilebufid); // return bufferid (which is current compile bufferid)
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);   // return bufferid 

    // allocate space for 4 shadow regs
    dg_compilesubn8fromrsp(
        pBHarrayhead,
        0x20);

    // stack is 16 byte aligned
    
    // push address of jump buffer as return address
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rax,
        -0x10); // -0x10
    
    dg_compileaddn32torax (
        pBHarrayhead,
        sizeof(Bufferhandle));
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);  // push pBHarrayhead + sizeof(Bufferhandle) .. this is the return address to the jump buffer

    // call forth routine at offset and bufferid on the data stack

    dg_compilemovntoreg ( // "\x48\xBE\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        pints[1],
        dg_rdx); // target bufferid  // was rsi
    
    dg_compilemovntoreg ( // "\x48\xBA\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        pints[0],
        dg_r8); // target offset  // was rdx
    /*
    // show the compiled code so far
    finalccbuflength = dg_getbufferlength(
        pBHarrayhead,
        compilebufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }

    dg_hexdumpsegment(
        pBHarrayhead,
        (unsigned char*)dg_getpbuffer(pBHarrayhead, compilebufid, &pbuflength),
        finalccbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"target bufferid = ");
    dg_writestdoutuint64tohex(pBHarrayhead, pints[1]);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"target offset = ");
    dg_writestdoutuint64tohex(pBHarrayhead, pints[0]);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"dg_forthgrowbuffer address = ");
    dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)&dg_forthgrowbuffer);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"address from compile time dg_getpbufferoffset = ");
    dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)dg_getpbufferoffset(pBHarrayhead, DG_CORE_BUFFERID, (UINT64)&dg_forthgrowbuffer));
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    */
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rcx,  // was rdi
        -0x10); // pBHarrayhead from frame

    dg_compilesubn8fromrsp(
        pBHarrayhead,
        0x28); // for 4 shadow regs and +1 to align otherwise dg_getpbufferoffset call will trash the stack

    dg_compilecalladdress ( 
        pBHarrayhead,
        (UINT64)&dg_getpbufferoffset); // target address

    dg_compileaddn8torsp(
        pBHarrayhead,
        0x28); // drop shadow regs so that the stack pointer point to the return to jump buffer return address
    
    /*
    // show calculated address
    dg_compilemovntoreg(
        pBHarrayhead,
        dg_rax,
        dg_rdx);

    dg_compilemovbracketrbpd8toreg(
        pBHarrayhead,
        dg_rcx,  // was rdi
        -0x10); // pBHarrayhead from frame

    dg_compilesubn8fromrsp(
        pBHarrayhead,
        0x20); // for 4 shadow regs otherwise dg_getpbufferoffset call will trash the stack

    dg_compilecalladdress(
        pBHarrayhead,
        (UINT64)&dg_writestdoutuint64tohex); // target address

    dg_compileaddn8torsp(
        pBHarrayhead,
        0x20); // drop shadow regs so that the stack pointer point to the return to jump buffer return address

    dg_compilemovbracketrbpd8toreg(
        pBHarrayhead,
        dg_rcx,  // was rdi
        -0x10); // pBHarrayhead from frame

    dg_compilesubn8fromrsp(
        pBHarrayhead,
        0x20); // for 4 shadow regs otherwise dg_getpbufferoffset call will trash the stack

    dg_compilecalladdress(
        pBHarrayhead,
        (UINT64)&dg_forthcr); // target address

    dg_compileaddn8torsp(
        pBHarrayhead,
        0x20); // drop shadow regs so that the stack pointer point to the return to jump buffer return address
    */
    // setting 1st parameter to pBHarrayhead
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rcx,  // was rdi
        -0x10); // pBHarrayhead from frame
    
    dg_compilejumptorax(pBHarrayhead); // "\xFF\xE0" 2 bytes
    
    // could put here to targetoffset location
    finalccbuflength = dg_getbufferlength(
        pBHarrayhead,
        compilebufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        compilebufid,
        ccbuflength+2,
        finalccbuflength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    (*pbuflength) -= (2 * sizeof(UINT64));
}


const char* dg_initjumpbuffername = "dg_initjumpbuffer";

// jump buffer code assumes it is being called from a subroutine that did init locals
void dg_initjumpbuffer (Bufferhandle* pBHarrayhead)
{
    const char* pError;

    // rsp should be 16 byte aligned on entry
    
    // add   rsp + 20 ->                      0x48 0x83 0xC4 0x20                    // to undo the shadow regs                    
    // popq  rdx // rsi                       0x5A // 0x5E // bufferid
    // popq  r8  // rdx                       0x41 0x58 // 0x5A // offset
    // movq  [rbp-0x10] -> rcx // rdi         0x48 0x8B 0x4D 0xF0 // 0x48 0x8B 0x7D 0xF0  // pBHarrayhead
    // movq  [rbp-0x20] -> rsp                0x48 0x8B 0x65 0xE0  // seems rex is needed
    // andq  rsp & 0xfffffffffffffff0 -> rsp  0x48 0x83 0xE4 0xF0
    // subq  rsp - 0x20n -> rsp               0x48 0x83 0xEC 0x20 // alignment + 4 shadow regs
    //  stack is aligned to 16 byte boundary
    // movq  &dg_getpbufferoffset -> rax      0x48 0xB8 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn
    // call  rax                              0xFF 0xD0
    //  stack is still aligned to 16 byte boundary... BUT will not be when it does the jump...
    //  however the next thing should be a subroutine call... which will realign the stack
    // jump  rax                              0xFF 0xE0
    
    // unsigned char pbuf[34] = "\x5A\x41\x58\x48\x8B\x4D\xF0\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xD0\xFF\xE0";
    unsigned char pbuf[38] = "\x48\x83\xC4\x20\x5A\x41\x58\x48\x8B\x4D\xF0\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x20\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xD0\xFF\xE0";
    // unsigned char pbuf[39] = "\x48\x8B\x55\xD0\x48\x8B\x75\xC8\x48\x8B\x7D\xF0\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xD0\xFF\xE0";

    *((UINT64*)(pbuf + 25)) = (UINT64)(&dg_getpbufferoffset);

    // *((UINT64*)(pbuf + 25)) = (UINT64)(&dg_forthgothere);
    
    pError = dg_movebytes(
        pbuf,
        ((unsigned char*)pBHarrayhead) + sizeof(Bufferhandle),
        37); // 33);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_initjumpbuffername);
    }
}


UINT64 intparameterslookuptable[4] =
{
    dg_rcx,
    dg_rdx,
    dg_r8,
    dg_r9
};

UINT64 floatparameterslookuptable[4] =
{
    dg_xmm0,
    dg_xmm1,
    dg_xmm2,
    dg_xmm3
};

UINT64 intreturnparameterstable[1] =
{
    dg_rax
};

UINT64 floatreturnparameterstable[1] =
{
    dg_xmm0
};

const char* dg_determineparameterregistername = "dg_determineparameterregister";

UINT64 dg_determineparameterregister(
    Bufferhandle* pBHarrayhead,
    UINT64 parameterindex)
{
    UINT64 x;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return((UINT64)-1);
    }

    if (parameterindex < dg_cparameterregisterslength)
    {
        // it's in a register with the specified type
        x = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_cparameterregisters + (sizeof(UINT64) * parameterindex));

        switch (x)
        {
            case 0:
                return(intparameterslookuptable[parameterindex]);
            case 1:
                return(floatparameterslookuptable[parameterindex]);
            // case 2:
            //    return(parameterindex | dg_cparameterpassinbothflag);
        }

        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
        return((UINT64)-1);
    }

    // it's on the stack
    x = parameterindex - dg_cparameterregisterslength;

    // I doubt this is possible but... you never know... someone inputs a ton of parameters...
    if (x > dg_cparameteronstackflag)
    {
        dg_pusherror(pBHarrayhead, dg_parametersovermaxsizeerror);
        dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
        return((UINT64)-1);
    }

    return(x | dg_cparameteronstackflag);
}


const char* dg_pulloneaddressingmodename = "dg_pulloneaddressingmode";

void dg_pulloneaddressingmode(
    Bufferhandle* pBHarrayhead,
    dg_Sibformatter* psf)
{
    UINT64 addresssize;
    UINT64 parametertype;
    UINT64 notdoneflag = FORTH_TRUE;

    UINT64 subroutineregspreserved;
    UINT64 parameterreglocalsregindex;
    UINT64 parameterregpreservedregindex;
    UINT64 regspreserveddepth;
    UINT64 currentreturnstackdepth;
    INT64 parameterregreturnstackoffset;

    UINT64 rstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    addresssize = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_x86asmaddresssize);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
        return;
    }

    
    while (notdoneflag != FORTH_FALSE)
    {
        parametertype = dg_popdatastack(pBHarrayhead);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
            return;
        }
    
        switch (parametertype) {
                
            case dg_isdatasize:
                psf->size = dg_popdatastack(pBHarrayhead);
            
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
            
                break;
            
            case dg_isforward:
                break;
        
            case dg_isreverse:
                psf->direction = 1;
                break;

            case dg_isimmediate:
                // pull smallest allowed byte size
                  // this allows you to force 32 bits when 8 bits or 0 is available
                psf->immediatesize = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                // can remove this when everything is 64 bits
                if ( (8 == psf->immediatesize) &&
                     (4 == addresssize) )
                {
                    psf->immediatevaluehi = dg_popdatastack(pBHarrayhead);
            
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }
                    
                    psf->immediatevalue = dg_popdatastack(pBHarrayhead);
            
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }
                }
                else
                {
                    psf->immediatevalue = dg_popdatastack(pBHarrayhead);
            
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }
                }
                
                notdoneflag = FORTH_FALSE;
                
                psf->memmode = dg_memmodeimmediate;
            
                break;
            
            case dg_isbasedisplacement:
            
                dg_pullmemusingrslashm (
                    pBHarrayhead,
                    psf);
                    
                notdoneflag = FORTH_FALSE;
                
                dg_checkbasereg(pBHarrayhead, psf->basereg);
                
                break;
            
            case dg_isbasescaleindexdisplacement:
            
                dg_pullmemusingsib (
                    pBHarrayhead,
                    psf);
                
                notdoneflag = FORTH_FALSE;
                
                dg_checkbasereg(pBHarrayhead, psf->basereg);
                dg_checkindexreg(pBHarrayhead, psf->indexreg);
                
                break;
                
            case dg_isbasescalevindexdisplacement:
                dg_pullmemusingvsib (
                    pBHarrayhead,
                    psf);
                
                notdoneflag = FORTH_FALSE;
                
                dg_checkbasereg(pBHarrayhead, psf->basereg);
                dg_checkvindexreg(pBHarrayhead, psf->indexreg);  // must be ymmr (will allow xmmr)
                
                break;
            
                
            case dg_ishereplusdisplacement:
            
                psf->displacement = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->displacementsize = 4;
                psf->basereg = dg_eip; // probably have to change this to dg_rip and check addresssize;
                psf->memmode = dg_memmodeeipplusn; 
                
                notdoneflag = FORTH_FALSE;

                break;
                
            case dg_isbufferoffset:
            
                psf->bufferid = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->offset = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->memmode = dg_memmodebufferoffset;
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_iscurrentcompilebufferoffset:
            
                psf->bufferid = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    currentcompilebuffer);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->offset = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->memmode = dg_memmodebufferoffset;
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_isccbufferoffsetnobracket:
            
                psf->bufferid = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    currentcompilebuffer);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->offset = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->memmode = dg_memmodebufferoffsetnobracket;
                
                notdoneflag = FORTH_FALSE;
            
                break;
            
            case dg_isreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodereg;
                }
                
                psf->size = dg_getsizefromreg (psf->basereg);
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_isfloatingpointstackreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodefpsreg;
                }
                
                // psf->size = dg_getsizefromreg (psf->basereg);
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_isxmmreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodexmmreg;
                }
                
                if ((psf->basereg >= dg_ymm0) &&
                    (psf->basereg <= dg_ymm15))
                {
                    psf->size = 32;
                }
                else
                {
                    psf->size = 16;
                }
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_isymmreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodexmmreg;
                }
                
                if ((psf->basereg >= dg_xmm0) &&
                    (psf->basereg <= dg_xmm15))
                {
                    psf->size = 16;
                }
                else
                {
                    psf->size = 32;
                }
                
                notdoneflag = FORTH_FALSE;
            
                break;
            
            case dg_iscontrolreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodecontrolreg;
                }
                
                psf->size = 4; // size is ignored for the MOVCR, instruction 3/17/2020
                
                notdoneflag = FORTH_FALSE;
            
                break;
            
            case dg_issegmentreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodesegmentreg;
                }
            
                psf->size = 2; // for the mov sr to r opcode, it seems size is ingored,
                // but the docs say you can put the 0x66 and 0x48 prefix but it seems in all
                // cases the move gets 0 extended to 64 bits in 64 bit mode...
                // but to allow the user the flexibility to choose the prefixes, I'm going to
                // make the n SR size different from the SRn
                // if the user chooses n SR, then the size of the reg will be used
                // if the user chooses SRn, then size is ignored and no prefix is used. 3/17/2020
                
                notdoneflag = FORTH_FALSE;
            
                break;
            
            case dg_isdebugreg:
            
                psf->basereg = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodedebugreg;
                }
                
                psf->size = 4; // size is ignored for the MOVDR, instruction 3/17/2020
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            case dg_isthreebytevex:
                psf->usesthreebytevex = (UINT64)-1;
                break;

            case dg_isdgluforthframelocal:
                // it's on the stack relative to the frame register
                //  going to make 0 be local variable 0
                //  1 local variable 1, etc...
                //  [rbp - 0x28] = local 0  (there are 4 things...)
                //  [rbp - 0x30] = local 1 etc

                // *** need to change this to not use dg_dgluframelocaloffset...
                parametertype = dg_popdatastack(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                // psf->displacement = -1 * (parametertype + dg_dgluframelocaloffset) * sizeof(UINT64); // not checking for overflow...
                psf->displacement = -1 * (parametertype) * sizeof(UINT64); 
                psf->basereg = dg_rbp;
                psf->memmode = dg_memmodemodrslashm;

                notdoneflag = FORTH_FALSE;

                break;


            case dg_isparamusingnoframe:
                // determine parameter type, reg or stack
                // do parameter type
                parametertype = dg_popdatastack(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                parametertype = dg_determineparameterregister(
                    pBHarrayhead,
                    parametertype);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                if (dg_cparameteronstackflag == (parametertype & dg_cparameteronstackmask))
                {
                    // it's on the stack...
                    // need rstack offset to parameters
                    rstackdepth = dg_defaultnoframerstackdepth; 

                    // need to add the current depth too....
                        
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }   

                    currentreturnstackdepth = dg_getbufferuint64(
                        pBHarrayhead,
                        DG_DATASPACE_BUFFERID,
                        dg_returnstackdepth);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }
                     
                    psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                    psf->displacement = ((parametertype & (~dg_cparameteronstackmask)) + (rstackdepth + currentreturnstackdepth)) * sizeof(UINT64); 
                        // can't overflow because of mask
                        // + 1 because function return is at 0... assumes stack pointer
                        // going to need to track stack pointer offset and adjust...
                    psf->basereg = dg_rsp;       
                    psf->memmode = dg_memmodemodrslashm;
                    // psf->size = sizeof(UINT64); // xmm registers may not work if you do this..
                    
                    notdoneflag = FORTH_FALSE;
                
                    break;
                }

                // parameter is a reg... need to check if it is a preserved reg  
                //   get dg_subroutineregspreserved
                subroutineregspreserved = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    dg_subroutineregspreserved); // this is misnamed...

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                //   get localsregsmask of reg preserved
                parameterreglocalsregindex = dg_regtolocalsregindex(parametertype);

                if (parameterreglocalsregindex >= dg_localscpux86regsmaxindex)
                {
                    dg_pusherror(pBHarrayhead, (const char*)"reg is not a locals reg error\n");
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                //   if paramreg was preserved (and of regspreserved with reg's localsregsmask != 0)
                if (0 != (dg_twototheu(parameterreglocalsregindex) & subroutineregspreserved))
                {
                    // parameter reg was preserved which means it was moved to the return stack
                    //     generating [RSP+N] using current return stack state variable data

                    // getulowestbits of regspreserved where u is paramreg's localsregsindex + 1
                    //     get which preserved reg the paramreg is (countsetbits in ulowestbits)
                    parameterregpreservedregindex = 
                        dg_countbits(dg_getulowestbits(
                                         subroutineregspreserved, 
                                         parameterreglocalsregindex + 1)) - 1;

                    regspreserveddepth = dg_getbufferuint64(
                        pBHarrayhead,
                        DG_DATASPACE_BUFFERID,
                        dg_regspreserveddepth);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }

                    currentreturnstackdepth = dg_getbufferuint64(
                        pBHarrayhead,
                        DG_DATASPACE_BUFFERID,
                        dg_returnstackdepth);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }

                    //     calculate offset of preserved reg
                    //       get depth of regs preserved dg_regspreserveddepth 
                    //       get current depth dg_returnstackdepth
                    //       offset (whichpreservedreg + (currentdepth - depth)) * sizeof(UINT64)

                    parameterregreturnstackoffset = sizeof(UINT64) *
                        (parameterregpreservedregindex + (currentreturnstackdepth - regspreserveddepth));

                    psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                    psf->displacement = parameterregreturnstackoffset;
                    psf->basereg = dg_rsp;
                    psf->memmode = dg_memmodemodrslashm;

                    notdoneflag = FORTH_FALSE;

                    break;                
                }

                // parameter is passed in a reg
                psf->basereg = parametertype;

                if ((parametertype >= dg_xmm0) &&
                    (parametertype <= dg_xmm15))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodexmmreg;
                    }

                    psf->size = 16;

                    notdoneflag = FORTH_FALSE;

                    break;
                }

                // promote memmode to defaultreg if not already higher
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodedefaultreg;
                }

                psf->size = dg_getsizefromreg(psf->basereg);

                notdoneflag = FORTH_FALSE;

                break;



            case dg_isparamusingframe:
                // determine parameter type, reg or stack
                // do parameter type
                parametertype = dg_popdatastack(pBHarrayhead);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                parametertype = dg_determineparameterregister(
                    pBHarrayhead,
                    parametertype);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                if (dg_cparameteronstackflag == (parametertype & dg_cparameteronstackmask))
                {
                    // it's on the stack...
                    // need to determine if using rbp as base reg or not and adjust
                    psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                    psf->displacement = ((parametertype & (~dg_cparameteronstackmask)) + dg_paramusingframeoffset) * sizeof(UINT64);
                    // can't overflow because of mask
                    // + 1 because function return is at 0... assumes stack pointer
                    // going to need to track stack pointer offset and adjust...
                    psf->basereg = dg_rbp;
                    psf->memmode = dg_memmodemodrslashm;
                    // psf->size = addresssize; // leaving it on default size so xmm registers work

                    notdoneflag = FORTH_FALSE;

                    break;
                }

                // parameter is a reg... need to check if it is a preserved reg  
                //   get dg_subroutineregspreserved
                subroutineregspreserved = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    dg_subroutineregspreserved); // this is misnamed...

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                //   get localsregsmask of reg preserved
                parameterreglocalsregindex = dg_regtolocalsregindex(parametertype);

                if (parameterreglocalsregindex >= dg_localscpux86regsmaxindex)
                {
                    dg_pusherror(pBHarrayhead, (const char*)"reg is not a locals reg error\n");
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                //   if paramreg was preserved (and of regspreserved with reg's localsregsmask != 0)
                if (0 != (dg_twototheu(parameterreglocalsregindex) & subroutineregspreserved))
                {
                    // parameter reg was preserved which means it was moved to the return stack
                    //     generating [RBP-N]

                    // getulowestbits of regspreserved where u is paramreg's localsregsindex + 1
                    //     get which preserved reg the paramreg is (countsetbits in ulowestbits)
                    // parameterregpreservedregindex = 
                    //    dg_countbits(dg_getulowestbits(
                    //                     subroutineregspreserved, 
                    //                     parameterreglocalsregindex + 1)) - 1;

                    // regspreserveddepth = dg_getbufferuint64(
                    //    pBHarrayhead,
                    //    DG_DATASPACE_BUFFERID,
                    //    dg_regspreserveddepth);

                    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    // {
                    //    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    //    return;
                    // }

                    //     calculate offset of preserved reg
                    //       get depth of regs preserved dg_regspreserveddepth 
                    //       offset = ((0 - currentdepth) + whichpreservedreg) * sizeof(UINT64)

                    // parameterregreturnstackoffset = sizeof(UINT64) *
                    //    (parameterregpreservedregindex + (0 - currentreturnstackdepth));

                    parameterregreturnstackoffset = dg_getcallsubsframepreservedregoffset(
                        pBHarrayhead,
                        parameterreglocalsregindex);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }
                
                    psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                    psf->displacement = parameterregreturnstackoffset;
                    psf->basereg = dg_rbp;
                    psf->memmode = dg_memmodemodrslashm;

                    notdoneflag = FORTH_FALSE;

                    break;                
                }

                psf->basereg = parametertype;

                if ((parametertype >= dg_xmm0) &&
                    (parametertype <= dg_xmm15))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodexmmreg;
                    }

                    psf->size = 16;

                    notdoneflag = FORTH_FALSE;

                    break;
                }

                // promote memmode to defaultreg if not already higher
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodedefaultreg;
                }

                psf->size = dg_getsizefromreg(psf->basereg);

                notdoneflag = FORTH_FALSE;

                break;
                
            default:
                // assuming it is a reg of some type
                psf->basereg = parametertype;
                
                if ((parametertype >= dg_st0) &&
                    (parametertype <= dg_st7))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodefpsreg;
                    }
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
                
                if ((parametertype >= dg_xmm0) &&
                    (parametertype <= dg_xmm15))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodexmmreg;
                    }
                    
                    psf->size = 16;
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
                
                if ((parametertype >= dg_ymm0) &&
                    (parametertype <= dg_ymm15))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodexmmreg;
                    }
                    
                    psf->size = 32;
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
            
                if ((parametertype >= dg_cr0) &&
                    (parametertype <= dg_cr15))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodecontrolreg;
                    }
                    
                    psf->size = 4; // size is ignored for the MOVCR, instruction 3/17/2020
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
            
                if ((parametertype >= dg_dr0) &&
                    (parametertype <= dg_dr7))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodedebugreg;
                    }
                    
                    psf->size = 4; // size is ignored for the MOVDR, instruction 3/17/2020
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
            
                if ((parametertype >= dg_segregcs) &&
                    (parametertype <= dg_segreggs))
                {
                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodesegmentreg;
                    }
                    
                    // for the mov sr to r opcode, it seems size is ingored,
                    // but the docs say you can put the 0x66 and 0x48 prefix but it seems in all
                    // cases the move gets 0 extended to 64 bits in 64 bit mode...
                    // but to allow the user the flexibility to choose the prefixes, I'm going to
                    // make the n SR size different from the SRn
                    // if the user chooses n SR, then the size of the reg will be used
                    // if the user chooses SRn, then size is ignored and no prefix is used. 3/17/2020
                    psf->size = 4;
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }
            
                // promote memmode to defaultreg if not already higher
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodedefaultreg;
                }
                
                psf->size = dg_getsizefromreg (psf->basereg);
                
                notdoneflag = FORTH_FALSE;
            
                break;
        }
    }
}

/*
UINT64 cparameterslookuptable[6] = 
{
    dg_rdi,
    dg_rsi,
    dg_rdx,
    dg_rcx,
    dg_r8,
    dg_r9
};


const char dg_forthcparameterscurlyname[] = "CPARAMETERS<";

void dg_forthcparameterscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;
    UINT64 data;
    UINT64 compiletype;
    
    UINT64 numberofcparameters;
    UINT64 numberofcfparameters;
    
    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    numberofcparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
    
    if (numberofcparameters != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"Number of c floating point parameters was not 0. Did you forget to do ?CLEAR-LOCALS ?");
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
    
    numberofcfparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
    
    if (numberofcfparameters != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"Number of c floating point parameters was not 0. You have to do the integer parameters first in case both use the return stack. Did you forget to do ?CLEAR-LOCALS ?");
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
        
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
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
            
        if (namelength != 0)
        {
            if (numberofcparameters < 6)
            {
                data = cparameterslookuptable[numberofcparameters];
                compiletype = (UINT64)&dg_forthdocompiletypedpushn;
            }
            else
            {
                // this assumes you are using RBP PUSH, RSP RBP MOV, at the entry of your subroutine
                data = ((numberofcparameters - 6) * 8) + 0x10;
                compiletype = (UINT64)&dg_forthdocompiletypedpushbracketrbpplusn;
            }
            
            localwordid = dg_newwordcopyname (
                pBHarrayhead,
                (UINT64)DG_CORE_BUFFERID,
                compiletype,
                0, // databufid,
                data, // databufoffset,
                (UINT64)DG_CORE_BUFFERID,
                (UINT64)pname,
                namelength);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
                return;
            }
            
            dg_linkdefinition(
                pBHarrayhead,
                localswordlistid,
                localwordid);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
                return;
            }
            
            numberofcparameters++;
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters,
        numberofcparameters);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
}
*/

/*
UINT64 cfparameterslookuptable[8] = 
{
    dg_xmm0,
    dg_xmm1,
    dg_xmm2,
    dg_xmm3,
    dg_xmm4,
    dg_xmm5,
    dg_xmm6,
    dg_xmm7
};


const char dg_forthcfparameterscurlyname[] = "CFPARAMETERS<";

void dg_forthcfparameterscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;
    UINT64 data;
    UINT64 compiletype;
    
    UINT64 numberofcparameters;
    UINT64 numberofcfparameters;
    UINT64 numberofcparametersonstack = 0;
    
    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    numberofcparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcfparameterscurlyname);
        return;
    }
    
    if (numberofcparameters > 6)
    {
        numberofcparametersonstack = numberofcparameters - 6;
    }
    
    numberofcfparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcfparameterscurlyname);
        return;
    }
    
    if (numberofcfparameters != 0)
    {
        dg_pusherror(pBHarrayhead, (const char*)"Number of c floating point parameters was not 0. Did you forget to do ?CLEAR-LOCALS ?");
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
        
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcfparameterscurlyname);
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
            
        if (namelength != 0)
        {
            if (numberofcparameters < 8)
            {
                data = cfparameterslookuptable[numberofcparameters];
                compiletype = (UINT64)&dg_forthdocompiletypedpushn;
            }
            else
            {
                // this assumes you are using RBP PUSH, RSP RBP MOV, at the entry of your subroutine
                data = ((numberofcfparameters - 8) * 8) + (numberofcparametersonstack * 8) + 0x10;
                compiletype = (UINT64)&dg_forthdocompiletypedpushbracketrbpplusn;
            }
            
            localwordid = dg_newwordcopyname (
                pBHarrayhead,
                (UINT64)DG_CORE_BUFFERID,
                compiletype,
                0, // databufid,
                data, // databufoffset,
                (UINT64)DG_CORE_BUFFERID,
                (UINT64)pname,
                namelength);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcfparameterscurlyname);
                return;
            }
            
            dg_linkdefinition(
                pBHarrayhead,
                localswordlistid,
                localwordid);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthcfparameterscurlyname);
                return;
            }
            
            numberofcfparameters++;
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters,
        numberofcfparameters);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcparameterscurlyname);
        return;
    }
}
*/

void dg_forthframeparamscurly(Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;

    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;

    INT64 compareflag;
    UINT64 parsingfloatsflag = FORTH_FALSE; // start out parsing ints

    UINT64 i = 0;
    UINT64 reg;
    UINT64 stringstackdepth;

    UINT64 numberofintparameters = 0;
    UINT64 numberoffloatparameters = 0;

    UINT64 myparamregsused = 0;

    const char* pError;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }

    // localsregsmask for which regs were preserved on the return stack
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }


    // depth in UINT64s at which the regs in localsregsmask are saved on the return stack
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }


    // assuming standard enter call subs frame was done...
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        dg_callsubsframesize); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }

    i = 0;

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
            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
            return;
        }

        if (namelength != 0)
        {

            pError = dg_comparebytes(
                pname,                 // pstring1, 
                namelength,            // string1length,
                (unsigned char*)"INT", //  pstring2,
                3,                     // string2length,
                &compareflag);         // pflag);

            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_comparebytesname);
                dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                return;
            }

            if (0 == compareflag)
            {
                parsingfloatsflag = FORTH_FALSE;
            }
            else
            {
                pError = dg_comparebytes(
                    pname,                 // pstring1, 
                    namelength,            // string1length,
                    (unsigned char*)"FLOAT", //  pstring2,
                    5,                     // string2length,
                    &compareflag);         // pflag);

                if (pError != dg_success)
                {
                    dg_pusherror(pBHarrayhead, pError);
                    dg_pusherror(pBHarrayhead, dg_comparebytesname);
                    dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                    return;
                }

                if (0 == compareflag)
                {
                    parsingfloatsflag = FORTH_TRUE;
                }
                else
                {
                    // it's a parameter name
                    if (parsingfloatsflag != FORTH_FALSE)
                    {
                        // it's a float
                        reg = 1;
                        numberoffloatparameters++; 
                    }
                    else
                    {
                        // it's an int
                        reg = 0;
                        numberofintparameters++;
                    }

                    //  if it's the first 4, it goes in a register
                    //  if it's after the first 4, it goes onto the stack
                    if (i < dg_cparameterregisterslength)
                    {
                        dg_putbufferuint64(
                            pBHarrayhead,
                            DG_DATASPACE_BUFFERID,
                            dg_cparameterregisters + (i * sizeof(UINT64)),
                            reg);

                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                            return;
                        }

                        myparamregsused = dg_setbit(
                            myparamregsused, 
                            dg_paramregsindextolocalsregindex(
                            i, 
                            reg));
                        
                    }
                    
                    // add the symbol name - it's a constant
                    localwordid = dg_createdconstantdef(
                        pBHarrayhead,
                        i, // databufoffset
                        dg_isparamusingframe, // databufid,
                        pname,
                        namelength);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                        return;
                    }
                   
                    dg_linkdefinition(
                        pBHarrayhead,
                        localswordlistid,
                        localwordid);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                        return;
                    }

                    i++;
                }
            }
        }
    }

    // fill out the rest of the regs with the type
    //  windows docs say varargs always go in int regs...
    //  since this is for incoming parameters... not calling other functions...
    //  going to let the programmer choose... it'll be whatever it was doing...
    if (FORTH_FALSE == parsingfloatsflag)
    {
        reg = 0;
    }
    else
    {
        reg = 1;
    }

    while (i < dg_cparameterregisterslength)
    {
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_cparameterregisters + (i * sizeof(UINT64)),
            reg);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
            return;
        }

        i++;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters,
        numberofintparameters);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters,
        numberoffloatparameters);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_paramregsused,
        myparamregsused);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
       return;
    }

    // this initializes which regs are already used in the current subroutine
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        myparamregsused | dg_mustbepreservedregsmask);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
       return;
    }
}


void dg_forthnoframeparamscurly(Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;

    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;

    INT64 compareflag;
    UINT64 parsingfloatsflag = FORTH_FALSE; // start out parsing ints

    UINT64 i = 0;
    UINT64 reg;
    UINT64 stringstackdepth;

    UINT64 numberofintparameters = 0;
    UINT64 numberoffloatparameters = 0;

    UINT64 myparamregsused = 0;

    const char* pError;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // localsregsmask for which regs were preserved on the return stack
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }


    // depth in UINT64s at which the regs in localsregsmask are saved on the return stack
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }

    // depth in UINT64s of return stack from base...
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }


    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }

    i = 0;

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
            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
            return;
        }

        if (namelength != 0)
        {

            pError = dg_comparebytes(
                pname,                 // pstring1, 
                namelength,            // string1length,
                (unsigned char*)"INT", //  pstring2,
                3,                     // string2length,
                &compareflag);         // pflag);

            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_comparebytesname);
                dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                return;
            }

            if (0 == compareflag)
            {
                parsingfloatsflag = FORTH_FALSE;
            }
            else
            {
                pError = dg_comparebytes(
                    pname,                 // pstring1, 
                    namelength,            // string1length,
                    (unsigned char*)"FLOAT", //  pstring2,
                    5,                     // string2length,
                    &compareflag);         // pflag);

                if (pError != dg_success)
                {
                    dg_pusherror(pBHarrayhead, pError);
                    dg_pusherror(pBHarrayhead, dg_comparebytesname);
                    dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                    return;
                }

                if (0 == compareflag)
                {
                    parsingfloatsflag = FORTH_TRUE;
                }
                else
                {
                    // it's a parameter name
                    if (parsingfloatsflag != FORTH_FALSE)
                    {
                        // it's a float
                        reg = 1;
                        numberoffloatparameters++;
                    }
                    else
                    {
                        // it's an int
                        reg = 0;
                        numberofintparameters++;
                    }

                    //  if it's the first 4, it goes in a register
                    //  if it's after the first 4, it goes onto the stack
                    if (i < dg_cparameterregisterslength)
                    {
                        dg_putbufferuint64(
                            pBHarrayhead,
                            DG_DATASPACE_BUFFERID,
                            dg_cparameterregisters + (i * sizeof(UINT64)),
                            reg); // setting parameter type: 0 = reg, 1 = float

                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                            return;
                        }

                        myparamregsused = dg_setbit(
                            myparamregsused, 
                            dg_paramregsindextolocalsregindex(
                            i, 
                            reg));
                        
                    }

                    // add the symbol name - it's a constant
                    localwordid = dg_createdconstantdef(
                        pBHarrayhead,
                        i, // databufoffset
                        dg_isparamusingnoframe, // databufid,
                        pname,
                        namelength);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                        return;
                    }

                    dg_linkdefinition(
                        pBHarrayhead,
                        localswordlistid,
                        localwordid);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                        return;
                    }

                    i++;
                }
            }
        }
    }

    // fill out the rest of the regs with the type
    //  windows docs say varargs always go in int regs...
    //  since this is for incoming parameters... not calling other functions...
    //  going to let the programmer choose... it'll be whatever it was doing...
    if (FORTH_FALSE == parsingfloatsflag)
    {
        reg = 0;
    }
    else
    {
        reg = 1;
    }

    while (i < dg_cparameterregisterslength)
    {
        // it's both reg and float... on Windows, they want you to pass varargs
        //  in both ints and floats just in case the called function doesn't follow
        //  the convention of passing float var args in ints
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_cparameterregisters + (i * sizeof(UINT64)),
            reg); 

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
            return;
        }

        i++;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters,
        numberofintparameters);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters,
        numberoffloatparameters);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_paramregsused,
        myparamregsused);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }

    // this initializes which regs are already used in the current subroutine
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        myparamregsused | dg_mustbepreservedregsmask);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
    }
}


// )), is probably specific too...

void dg_forthimp(Bufferhandle* pBHarrayhead)
{
    dg_pushdatastack(pBHarrayhead, dg_rip);
    dg_pushdatastack(pBHarrayhead, 5);  // displacement  // on Windows you need 5 for the branch always,  
    dg_pushdatastack(pBHarrayhead, 4);  // displacement size  
    dg_pushdatastack(pBHarrayhead, dg_isbasedisplacement); 
}


const char* dg_compileosymbolimportstuffname = "dg_compileosymbolimportstuff";

// on windows you need to branch over where the import link will go
//  the displacement of the previous instruction should already be set with the IMP command...
UINT64 dg_compileosymbolimportstuff(Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)-1);
    }

    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_ALWAYS);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compileosymbolimportstuffname);
        return ((UINT64)-1);
    }

    x = 0;

    dg_compilesegment(
        pBHarrayhead,
        (const char*)&x,
        sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compileosymbolimportstuffname);
        return ((UINT64)-1);
    }

    dg_resolvecompiledbranch(
        pBHarrayhead,
        afterbranchoffset,
        afterbranchoffset + sizeof(UINT64));  // branch target offset

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthoherename);
    }

    return (afterbranchoffset);
}


const char* dg_compilecodelinkname = "dg_compilecodelink";

UINT64 dg_compilecodelink(Bufferhandle* pBHarrayhead)
{
    // on mac you do this:
    // dg_compilejmpbracketoffset(
    //    pBHarrayhead,
    //    0);

    UINT64 x = 0;
    UINT64 ccbufid;
    UINT64 ccbuflength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)-1);
    }

    // on windows you do this:
    dg_compilejmpbracketoffset(
        pBHarrayhead,
        0); // link goes immediately after this, so 0

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilecodelinkname);
    }

    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilecodelinkname);
    }

    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilecodelinkname);
    }

    x = 0;

    dg_compilesegment(
        pBHarrayhead,
        (const char*)&x,
        sizeof(UINT64));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilecodelinkname);
    }

    return(ccbuflength);
}


void dg_forthoimportcodelink(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // on windows, the address is at the offset, so you can just use [O]
    //  and the offset is already correct
    dg_pushdatastack(pBHarrayhead, dg_iscurrentcompilebufferoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_isoimportcodelinkname);
        return;
    }
}
